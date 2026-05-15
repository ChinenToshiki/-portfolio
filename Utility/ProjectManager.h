#pragma once
#include"DxLib.h"
#include <string>
#include "../Scene/SceneManager.h"

#define DEBUG_ON

#ifdef DEBUG_ON
#define FullScreen TRUE

#else
#define FullScreen FALSE

#endif // DEBUG_ON

#define D_WIN_MAX_X 1280
#define D_WIN_MAX_Y 720
#define D_COLOR_BIT 32

class ProjectManager
{
private:
	float delta_time;
	LONGLONG start_time;
	LONGLONG now_time;
	float refresh_rate;

public:
	ProjectManager();
	~ProjectManager();

	void Initialize();
	void Update();
	void Update_DeltaTime();
	void Finalize();

};