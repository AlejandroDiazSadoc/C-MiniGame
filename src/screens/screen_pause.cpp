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

// Pause screen global variables
static int framesCounter;
static int finishScreen;

//----------------------------------------------------------------------------------
// Pause Screen Functions Definition
//----------------------------------------------------------------------------------

// Pause Screen Initialization logic
void InitPauseScreen(void)
{
    framesCounter = 0;
    finishScreen = 0;
}

// Pause Screen Update logic
void UpdatePauseScreen(void)
{
    framesCounter++;

    // Check if player want to unpause the game
    if (IsKeyPressed('P')){
        finishScreen = 1;
        gamePaused = !gamePaused;
    }
}


void DrawPauseScreen(void){

    //Draw also the gameplay screen
    DrawGameplayScreen();

    DrawRectangle(screenWidth / 2.0f - screenWidth / 4.0f, screenHeight / 2.0f - screenHeight / 4.0f, screenWidth / 2.0f, screenHeight / 2.0f, LIGHTGRAY);
    DrawTextEx(font, "GAME PAUSED", (Vector2){screenWidth / 2.0f - MeasureText("GAME PAUSED", 40) / 2.0f, screenHeight / 2.0f - screenHeight / 4.0f}, 40, 2, GRAY);

    masterVolume = GuiSliderBar((Rectangle){screenWidth / 2.0f + screenWidth / 4.0f - screenWidth / 5.0f,
                                            screenHeight / 2.0f + screenHeight / 4.0f - screenHeight / 3.0f,
                                            screenWidth / 10.0f, screenHeight / 50.0f},
                                "Volume: ", ("" + to_string(masterVolume).substr(0, to_string(masterVolume).find(".") + 3)).c_str(),
                                masterVolume, 0, 100);
    SetMasterVolume(masterVolume / 100.0f);

    if (GuiButton((Rectangle){screenWidth / 2.0f - screenWidth / 15.0f,
                              screenHeight / 2.0f + screenHeight / 4.0f - screenHeight / 13.0f,
                              screenWidth / 15.0f, screenHeight / 15.0f},
                  "Exit"))
        endGame = true;

    if (windowedButton == false)
    {
        windowedButton = GuiButton((Rectangle){screenWidth / 2.0f - screenWidth / 4.0f + screenWidth / 10.0f,
                                               screenHeight / 2.0f + screenHeight / 4.0f - screenHeight / 3.0f, screenWidth / 10.0f, screenHeight / 10.0f},
                                   "FullScreen");
    }
    else
    {

        if (!IsWindowFullscreen())
        {

            screenWidth = GetMonitorWidth(0);
            screenHeight = GetMonitorHeight(0);
            SetWindowSize(screenWidth, screenHeight);
            ToggleFullscreen();
            SetWindowMonitor(1);
        }

        if (GuiButton((Rectangle){screenWidth / 2.0f - screenWidth / 4.0f + screenWidth / 10.0f,
                                  screenHeight / 2.0f + screenHeight / 4.0f - screenHeight / 3.0f, screenWidth / 10.0f, screenHeight / 10.0f},
                      "Windowed"))
        {

            ToggleFullscreen();
            windowedButton = false;
            screenWidth = 800;
            screenHeight = 450;
            SetWindowSize(screenWidth, screenHeight);
        }
    }
}





// Pause Screen Unload logic
void UnloadPauseScreen(void)
{
    // Nothing to unload in this screen.
}

// Pause Screen should finish?
int FinishPauseScreen(void)
{
    return finishScreen;
}
