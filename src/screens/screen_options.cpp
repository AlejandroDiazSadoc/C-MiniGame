#include "raylib.h"
#include "screens.hpp"
#include <iostream>
#include <string>

extern "C" {


#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
} 

using namespace std;
//----------------------------------------------------------------------------------
// Global Variables Definition (local to this module)
//----------------------------------------------------------------------------------

// Options screen global variables
static int framesCounter;
static int finishScreen;

//----------------------------------------------------------------------------------
// Options Screen Functions Definition
//----------------------------------------------------------------------------------

// Options Screen Initialization logic
void InitOptionsScreen(void)
{
    
    framesCounter = 0;
    finishScreen = 0;
}

// Options Screen Update logic
void UpdateOptionsScreen(void)
{
    UpdateMusicStream(music);
}

// Options Screen Draw logic
void DrawOptionsScreen(void)
{
    DrawTitleScreen();
    if (optionsButton)
    {
        DrawRectangle(GetScreenWidth() / 2.0f - GetScreenWidth() / 4.0f, GetScreenHeight() / 2.0f - GetScreenHeight() / 4.0f, GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f, LIGHTGRAY);
        DrawRectangle(GetScreenWidth() / 2.0f - GetScreenWidth() / 4.0f, GetScreenHeight() / 2.0f - GetScreenHeight() / 4.0f, GetScreenWidth() / 2.0f, GetScreenHeight() / 15.0f, WHITE);
        DrawTextEx(font, "Options", (Vector2){GetScreenWidth() / 2.0f - MeasureText("Options", 25) / 2.0f, GetScreenHeight() / 2.0f - GetScreenHeight() / 4.0f}, 25, 2, BLACK);

        if (GuiButton((Rectangle){GetScreenWidth() / 2.0f + GetScreenWidth() / 4.0f - GetScreenWidth() / 15.0f, GetScreenHeight() / 2.0f - GetScreenHeight() / 4.0f, GetScreenWidth() / 15.0f, GetScreenHeight() / 15.0f}, "X")){
            optionsButton = false;
            finishScreen = 1;
        }


        masterVolume = GuiSliderBar((Rectangle){GetScreenWidth() / 2.0f + GetScreenWidth() / 4.0f - GetScreenWidth() / 5.0f,
                                                GetScreenHeight() / 2.0f + GetScreenHeight() / 4.0f - GetScreenHeight() / 15.0f,
                                                GetScreenWidth() / 10.0f, GetScreenHeight() / 50.0f},
                                    "Volume: ", ("" + to_string(masterVolume).substr(0, to_string(masterVolume).find(".") + 3)).c_str(),
                                    masterVolume, 0, 100);
        SetMasterVolume(masterVolume / 100.0f);

        if (windowedButton == false)
        {
            windowedButton = GuiButton((Rectangle){GetScreenWidth() / 2.0f - GetScreenWidth() / 4.0f + GetScreenWidth() / 10.0f,
                                                   GetScreenHeight() / 2.0f + GetScreenHeight() / 4.0f - GetScreenHeight() / 7.0f, GetScreenWidth() / 10.0f, GetScreenHeight() / 10.0f},
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
                SetTargetFPS(60);   // Set our game to run at 60 frames-per-second
                SetWindowMonitor(1);
            }

            if (GuiButton((Rectangle){GetScreenWidth() / 2.0f - GetScreenWidth() / 4.0f + GetScreenWidth() / 10.0f,
                                      GetScreenHeight() / 2.0f + GetScreenHeight() / 4.0f - GetScreenHeight() / 7.0f, GetScreenWidth() / 10.0f, GetScreenHeight() / 10.0f},
                          "Windowed"))
            {

                ToggleFullscreen();
                windowedButton = false;
                screenWidth = 800;
                screenHeight = 450;
                SetWindowSize(screenWidth, screenHeight);
                SetTargetFPS(60);   // Set our game to run at 60 frames-per-second
            }
        }
    }
}


// Options Screen Unload logic
void UnloadOptionsScreen(void)
{
    // Nothin to unload in this screen.
}

// Options Screen should finish?
int FinishOptionsScreen(void)
{
    return finishScreen;
}