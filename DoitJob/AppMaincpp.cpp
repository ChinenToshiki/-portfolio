#include"DxLib.h"
#include"Utility/ProjectManager.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrebInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	ProjectManager PM;
	PM.	Initialize() ;
	PM.	Update()	 ;
	PM.	Finalize()	 ;

	//Dxライフらりの使用の終了処理
	DxLib_End();

	return 0;
}