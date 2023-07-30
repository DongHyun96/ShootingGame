// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
#include <time.h>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

// Default 1280.f x 720.f

// 700 * 900
#define WIN_WIDTH		800.f
#define WIN_HEIGHT		900.f

#define WIN_CENTER		Point(WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f)

#define COLOR_BLACK		RGB(0, 0, 0)
#define COLOR_WHITE		RGB(255, 255, 255)

#define COLOR_RED		RGB(255, 0, 0)
#define COLOR_GREEN		RGB(0, 255, 0)
#define COLOR_BLUE		RGB(0, 0, 255)

#define COLOR_CYAN		RGB(0, 255, 255)
#define COLOR_MAGENTA	RGB(255, 0, 255)
#define COLOR_YELLOW	RGB(255, 255, 0)

#define COLOR_GRAY		RGB(128, 128, 128)
#define COLOR_ORANGE	RGB(255, 165, 0)
#define COLOR_PINK		RGB(255, 192, 203)


// Object
#include "Point.h"
#include "Vector2.h"

#include "Circle.h"
#include "Rect.h"
#include "Line.h"

// Utility
#include "Collision.h"
#include "Util.h"
#include "Time.h"

// Texture
#include "Texture.h"

// GameObject
#include "Poo.h"

#include "CannonBall.h"
#include "CannonBallManager.h"
#include "Tank.h"

#include "ArkaPlayer.h"
#include "ArkaBrick.h"
#include "ArkaBrickManager.h"
#include "ArkaBall.h"



#include "Shooting_PlayerBullet.h"
#include "Shooting_PBulletManager.h"

#include "Shooting_EnemyBullet.h"
#include "Shooting_EBulletManager.h"

#include "Shooting_Item.h"
#include "Shooting_ItemManager.h"

#include "Shooting_Player.h"
#include "Shooting_Enemy.h"

#include "Shooting_EnemyManager.h"

#include "Shooting_Background.h"

#include "Shooting_GameManager.h"


// Scene
#include "Scene.h"
#include "PaintScene.h"
#include "CollisionScene.h"
#include "AvoidScene.h"
#include "FortressScene.h"
#include "ArkanoidScene.h"
#include "ImageScene.h"
#include "TextureScene.h"
#include "ShootingScene.h"


#include "MainGame.h"

// extern - 전역변수를 뿌려주는 키워드
extern HWND			hWnd; // 어딘가 이게 있으니 여기에 전방선언 한다
extern Point		mousePos;
extern HDC			backDC;
extern HINSTANCE	hInst;