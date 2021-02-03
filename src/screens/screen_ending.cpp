#include "raylib.h"
#include "screens.hpp"
#include <iostream>

using namespace std;

extern "C" {
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
} 
//----------------------------------------------------------------------------------
// Global Variables Definition (local to this module)
//----------------------------------------------------------------------------------

// Ending screen global variables
static int framesCounter;
static int finishScreen;

static Music endMusic;
//----------------------------------------------------------------------------------
// Ending Screen Functions Definition
//----------------------------------------------------------------------------------

// Ending Screen Initialization logic
void InitEndingScreen(void)
{
    endMusic = LoadMusicStream("../resources/Farewell_ogg.ogg");
    framesCounter = 0;
    finishScreen = 0;
    PlayMusicStream(endMusic);
}

// Ending Screen Update logic
void UpdateEndingScreen(void)
{
    UpdateMusicStream(endMusic);
    framesCounter++;
}

// Ending Screen Draw logic
void DrawEndingScreen(void)
{
    
    if ((framesCounter / 30) % 2 == 0)
        DrawTextEx(font, "GAME OVER", (Vector2){GetScreenWidth() / 2.0f - MeasureText("GAME OVER", 60) / 2.0f, GetScreenHeight() / 2.0f - 200.0f * (GetScreenHeight() / 450.0f)}, 60, 3, GRAY);

    DrawTextEx(font, ("Score: " + to_string(score)).c_str(), (Vector2){GetScreenWidth() / 2 - MeasureText(("Score: " + to_string(score)).c_str(), 30) / 2 - 200 * (GetScreenWidth() / 850.0f), GetScreenHeight() / 2 - 100 * (GetScreenHeight() / 450.0f)}, 30, 3, BLACK);
    DrawTextEx(font, ("Max Score: " + to_string(maxScore)).c_str(), (Vector2){GetScreenWidth() / 2 - MeasureText(("Max Score: " + to_string(score)).c_str(), 30) / 2 + 100 * (GetScreenWidth() / 850.0f), GetScreenHeight() / 2 - 100 * (GetScreenHeight() / 450.0f)}, 30, 3, BLACK);

    if (GuiButton((Rectangle){GetScreenWidth() / 2.0f - GetScreenWidth() / 15.0f,
                              GetScreenHeight() / 2.0f + GetScreenHeight() / 15.0f, GetScreenWidth() / 15.0f, GetScreenHeight() / 15.0f},
                  "Menu"))
    {
        framesCounter = 0;
        finishScreen = 1;
        bullets.clear();
        enemies.clear();
        lastShotFrame = -60;
        score = 0;
    }

    if (GuiButton((Rectangle){GetScreenWidth() / 2.0f - GetScreenWidth() / 15.0f,
                 GetScreenHeight() / 2.0f + 2.5f * GetScreenHeight() / 15.0f, GetScreenWidth() / 15.0f, GetScreenHeight() / 15.0f},
                  "Retry"))
    {

        framesCounter = 0;
        finishScreen = 2;
        bullets.clear();
        enemies.clear();
        lastShotFrame = -60;
        score = 0;
    }

    if (GuiButton((Rectangle){GetScreenWidth() / 2.0f - GetScreenWidth() / 15.0f,
                              GetScreenHeight() / 2.0f + 4.0f * GetScreenHeight() / 15.0f, GetScreenWidth() / 15.0f, GetScreenHeight() / 15.0f},
                  "Exit"))
        endGame = true;
}

// Ending Screen Unload logic
void UnloadEndingScreen(void)
{
    StopMusicStream(endMusic);
    UnloadMusicStream(endMusic);
}

// Ending Screen should finish?
int FinishEndingScreen(void)
{
    return finishScreen;
}