#include "raylib.h"
#include <vector>
#include <iostream>

using namespace std;
#ifndef SCREENS_H
#define SCREENS_H



//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
typedef enum GameScreen { LOGO = 0, TITLE, OPTIONS, GAMEPLAY, PAUSE, ENDING } GameScreen;



typedef struct Recta{
    float a;
    float b;
    float c;
    int dir;
} Recta;

typedef struct Player {
    Vector2 position;
    Vector2 speed;
    Vector2 size;
    Rectangle bounds;
    int lifes;
} Player;

// Ball structure
typedef struct Bullet {
    Vector2 position;
    float speed;
    Recta dst;
    int radius;
    bool active;
    string owner;
} Bullet;

typedef struct Enemy {
    Vector2 position;
    Vector2 size;
    float speed;
    Rectangle bounds;
    bool active;
    int lastFrameShot;
} Enemy;

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
#define PLAYER_LIFES             5
#define CD_SHOT 1
#define CD_SHOT_ENEMY 8


extern GameScreen currentScreen;
extern Font font;
extern Music music;
extern Sound fxCoin;
//extern Texture2D texLogo;


extern bool endGame;
extern bool optionsButton;
extern bool windowedButton;
extern bool gamePaused;

extern float masterVolume;

extern int monitorWidth;
extern int monitorHeight; 

extern const int min_screenWidth;
extern const int min_screenHeight;

extern int screenWidth;
extern int screenHeight;

extern int score;
extern int maxScore;
extern int lastShotFrame;


extern std::vector<Bullet> bullets;
extern std::vector<Enemy> enemies;


#ifdef __cplusplus
extern "C" {            // Prevents name mangling of functions
#endif

//----------------------------------------------------------------------------------
// Logo Screen Functions Declaration
//----------------------------------------------------------------------------------
void InitLogoScreen(void);
void UpdateLogoScreen(void);
void DrawLogoScreen(void);
void UnloadLogoScreen(void);
int FinishLogoScreen(void);

//----------------------------------------------------------------------------------
// Title Screen Functions Declaration
//----------------------------------------------------------------------------------
void InitTitleScreen(void);
void UpdateTitleScreen(void);
void DrawTitleScreen(void);
void UnloadTitleScreen(void);
int FinishTitleScreen(void);

//----------------------------------------------------------------------------------
// Options Screen Functions Declaration
//----------------------------------------------------------------------------------
void InitOptionsScreen(void);
void UpdateOptionsScreen(void);
void DrawOptionsScreen(void);
void UnloadOptionsScreen(void);
int FinishOptionsScreen(void);

//----------------------------------------------------------------------------------
// Pause Screen Functions Declaration
//----------------------------------------------------------------------------------
void InitPauseScreen(void);
void UpdatePauseScreen(void);
void DrawPauseScreen(void);
void UnloadPauseScreen(void);
int FinishPauseScreen(void);

//----------------------------------------------------------------------------------
// Gameplay Screen Functions Declaration
//----------------------------------------------------------------------------------
void InitPauseScreen(void);
void UpdatePauseScreen(void);
void DrawPauseScreen(void);
void UnloadPauseScreen(void);
int FinishPauseScreen(void);

//----------------------------------------------------------------------------------
// Gameplay Screen Functions Declaration
//----------------------------------------------------------------------------------
void InitGameplayScreen(void);
void UpdateGameplayScreen(void);
void DrawGameplayScreen(void);
void UnloadGameplayScreen(void);
int FinishGameplayScreen(void);

//----------------------------------------------------------------------------------
// Ending Screen Functions Declaration
//----------------------------------------------------------------------------------
void InitEndingScreen(void);
void UpdateEndingScreen(void);
void DrawEndingScreen(void);
void UnloadEndingScreen(void);
int FinishEndingScreen(void);

#ifdef __cplusplus
}
#endif

#endif // SCREENS_H