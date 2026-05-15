#include"ProjectManager.h"
#include"ResourceManager.h"
#include "GameData.h"

ProjectManager::ProjectManager()
{

}

ProjectManager::~ProjectManager()
{
}

 void ProjectManager::Initialize()
{
	// ウィンドウモードで起動する
	ChangeWindowMode(TRUE);

	// ウィンドウサイズの設定
	SetGraphMode(D_WIN_MAX_X, D_WIN_MAX_Y, D_COLOR_BIT);

	// ウィンドウタイトルの設定
	SetWindowText("KBC_GameJam-2026");

	// 垂直同期を行わない
	SetWaitVSyncFlag(FALSE);

	// Log.txtファイルの生成制御（Debugモードのみ生成する）
#if _DEBUG
	SetOutApplicationLogValidFlag(TRUE);
#else
	SetOutApplicationLogValidFlag(FALSE);
#endif // _DEBUG

	// Dxライブラリの初期化
	if (DxLib_Init() == -1)
	{
		throw std::string("Dxライブラリの初期化に失敗しました！\n");
	}

	// 描画先を表画面に反映する
	SetDrawScreen(DX_SCREEN_BACK);

	// シーンマネージャーを生成する
	SceneManager& manager = SceneManager::GetInstance();

	// 初期化処理
	manager.Initialize();

	// 非アクティブ状態でも動作させる
	SetAlwaysRunFlag(TRUE);
}

void ProjectManager::Update()
{
	// シーンマネージャーを生成する
	SceneManager& manager = SceneManager::GetInstance();

	// メインループ
	while (ProcessMessage() == 0)
	{
		Update_DeltaTime();
		// 実行処理
		bool finish_flag = manager.Update(delta_time);

		//SceneManagerの更新処理が失敗したら
		if (!finish_flag)
		{
			//メインループを抜ける
			break;
		}
	}
}

void ProjectManager::Update_DeltaTime()
{
	//現在の時間取得
	now_time = GetNowHiPerformanceCount();

	// 開始時間から現在時間までに経過した時間を計算する（μ秒）
	// 分解能をμ秒→秒に変換する
	delta_time = (float)(now_time - start_time) * 1.0e-6f;

	// 計測開始時間を更新する
	start_time = now_time;

	//リフレッシュレートを取得する
	refresh_rate = (float)GetRefreshRate();

	//１フレームあたり時間が1/refresh_rate秒を超えたら調整する
	if (delta_time >= (1.0f / refresh_rate))
	{
		delta_time = (1.0f / refresh_rate);
	}
}

void ProjectManager::Finalize()
{
	// シーンマネージャーを生成する
	SceneManager& manager = SceneManager::GetInstance();

	// 終了時処理
	manager.Finalize();

	// リソースマネージャーを生成する
	ResourceManager& r_manager = ResourceManager::GetInstance();

	// リソース終了処理
	r_manager.UnloadAllResourceData();

	// ゲームデータ終了処理
	GameData::DeleteInstance();

	// Dxライブラリの使用を終了する
	DxLib_End();
}
