
#include "screens.hpp"
#include "raylib.h"
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

// Title screen global variables
static int framesCounter;
static int finishScreen;

static Texture2D texTitleLogo;

//----------------------------------------------------------------------------------
// Title Screen Functions Definition
//----------------------------------------------------------------------------------

// Title Screen Initialization logic
void InitTitleScreen(void)
{
    //if(!IsMusicPlaying(music))
      //  PlayMusicStream(music);

    texTitleLogo = LoadTexture("../resources/cute.png");

    framesCounter = 0;
    finishScreen = 0;
}

// Title Screen Update logic
void UpdateTitleScreen(void)
{
    UpdateMusicStream(music);

    // Press enter or tap to change to GAMEPLAY screen
    finishScreen = 0;

    framesCounter++;
    if (IsKeyPressed(KEY_ENTER))
    {
         
        finishScreen = 2;   // GAMEPLAY

    }
    if(optionsButton)
        finishScreen = 1; // OPTIONS
    
}

// Title Screen Draw logic
void DrawTitleScreen(void)
{
    

    if (framesCounter < screenHeight - 25)
    {
        DrawTexture(texTitleLogo, screenWidth / 2 - texTitleLogo.width / 2, screenHeight - framesCounter, WHITE);

        GuiButton((Rectangle){screenWidth / 2.0f - 150.0f, screenHeight - framesCounter + texTitleLogo.height + 100.0f, 100.0f, 50.0f}, "Options");
        GuiButton((Rectangle){screenWidth / 2.0f + 40.0f, screenHeight - framesCounter + texTitleLogo.height + 100.0f, 100.0f, 50.0f}, "Exit");

        if ((framesCounter / 30) % 2 == 0)
            DrawTextEx(font, "PRESS [ENTER] to START",
                       (Vector2){(screenWidth) / 2.0f - MeasureText("PRESS [ENTER] to START", 20) / 2, screenHeight - framesCounter + texTitleLogo.height + 50.0f}, 20, 2, DARKGRAY);
    }
    else
    {
        DrawTexture(texTitleLogo, screenWidth / 2 - texTitleLogo.width / 2, 25, WHITE);
        if (!optionsButton)
        {
            optionsButton = GuiButton((Rectangle){GetScreenWidth() / 2.0f - 150.0f, texTitleLogo.height + 125.0f, 100.0f, 50.0f}, "Options");
            if (GuiButton((Rectangle){GetScreenWidth() / 2.0f + 40.0f, texTitleLogo.height + 125.0f, 100.0f, 50.0f}, "Exit"))
                endGame = true;
        }
        else
        {

            GuiButton((Rectangle){GetScreenWidth() / 2.0f - 150.0f, texTitleLogo.height + 125.0f, 100.0f, 50.0f}, "Options");
            if (GuiButton((Rectangle){GetScreenWidth() / 2.0f + 40.0f, texTitleLogo.height + 125.0f, 100.0f, 50.0f}, "Exit"))
                endGame = true;
        }

        if ((framesCounter / 30) % 2 == 0)
            DrawTextEx(font, "PRESS [ENTER] to START",
                       (Vector2){screenWidth / 2.0f - MeasureText("PRESS [ENTER] to START", 20) / 2, 75.0f + texTitleLogo.height}, 20, 2, DARKGRAY);
    }
}



// Title Screen Unload logic
void UnloadTitleScreen(void)
{
    UnloadTexture(texTitleLogo);
    
}

// Title Screen should finish?
int FinishTitleScreen(void)
{
    return finishScreen;
}