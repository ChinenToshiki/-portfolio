#pragma once
#include "SceneBase.h"
#include "../Utility/Singleton.h"

class SceneManager : public Singleton<SceneManager>
{
	friend class Singleton<SceneManager>;

private:
	SceneBase* currentScene;			// 現在のシーン情報
	GameObject* gameObject = new GameObject();

public:
	// コンストラクタ
	SceneManager();
	// デストラクタ
	~SceneManager() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// 引数<delta_time>：ワンフレームの秒数
	/// </summary>
	bool Update(float delta_time);

	/// <summary>
	/// 終了時処理
	/// </summary>
	void Finalize();

private:
	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() const;

	/// <summary>
	/// シーン切り替え処理
	/// </summary>
	/// <param name="nextType">次のシーンタイプ</param>
	void ChangeScene(SceneType nextType);
};