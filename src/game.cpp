#include "raylib.h"
#include "screens/screens.hpp"    
#include <iostream>
#include <vector>

#define RAYGUI_IMPLEMENTATION
#include "screens/raygui.h"

using namespace std;



GameScreen currentScreen;
Font font = { 0 };
Music music = { 0 };
Sound fxCoin = { 0 };



int monitorWidth;
int monitorHeight;

const int min_screenHeight = 450;
const int min_screenWidth = 800;

int screenWidth = 800;
int screenHeight = 450;

int score = 0;
int maxScore = 0;
int lastShotFrame = -60;

bool endGame = false;
bool optionsButton = false;
bool windowedButton = false;
bool gamePaused = false;

float masterVolume = 100.0f;


vector<Bullet> bullets;
vector<Enemy> enemies;


//----------------------------------------------------------------------------------
// Main entry point
//----------------------------------------------------------------------------------
int main(void)
{
    
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT);
    
    InitWindow(min_screenWidth, min_screenHeight, "PEC 1 - Alejandro Díaz Sadoc");

    
    
    
    InitAudioDevice();
    screenWidth = GetScreenWidth();
    screenHeight =  GetScreenHeight();

    monitorWidth = GetMonitorHeight(0);
    monitorHeight = GetMonitorWidth(0);

    //Loading global resources
    font = LoadFont("../resources/setback.png");
    music = LoadMusicStream("../resources/8bit.ogg");
    
    
    // Setup and Init first screen
    currentScreen = LOGO;
    InitLogoScreen();
    

    SetMasterVolume(masterVolume);
    PlayMusicStream(music);

    SetTargetFPS(60);   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!endGame)    
    {
        
        if(WindowShouldClose()) // Detect window close button or ESC key
            endGame = true;
            
        screenWidth = GetScreenWidth();
        screenHeight =  GetScreenHeight();

        

        switch(currentScreen) 
        {
            case LOGO: 
            {
                UpdateLogoScreen();
                
                if (FinishLogoScreen())
                {
                    InitTitleScreen();
                    UnloadLogoScreen();
                    currentScreen = TITLE;
                    //InitTitleScreen();
                }
            } break;
            case TITLE:
            {
                UpdateTitleScreen();

                if (FinishTitleScreen() == 1){
                    
                    currentScreen = OPTIONS;
                    InitOptionsScreen();
                } 
                else if (FinishTitleScreen() == 2) {
                    UnloadTitleScreen();
                    currentScreen = GAMEPLAY;
                    InitGameplayScreen();

                }
            }break;
            case OPTIONS:
            {
                UpdateOptionsScreen();
                if(FinishOptionsScreen() == 1){
                    UnloadOptionsScreen();
                    currentScreen = TITLE;
                }

            }break;
            case GAMEPLAY:
            {   
                UpdateGameplayScreen();

                if(FinishGameplayScreen() == 1){
                    currentScreen = PAUSE;
                    InitPauseScreen();
                }else if(FinishGameplayScreen() == 2){
                    UnloadGameplayScreen();
                    currentScreen = ENDING;
                    InitEndingScreen();
                }
                
            }break;
            case PAUSE:
            {
                UpdatePauseScreen();
                if(FinishPauseScreen() == 1){
                    currentScreen = GAMEPLAY;
                }
            }break;
            case ENDING:
            {
                
                UpdateEndingScreen();
                if(FinishEndingScreen() == 1){
                    
                    currentScreen = TITLE;
                    InitTitleScreen();
                    
                }else if(FinishEndingScreen() == 2){
                    currentScreen = GAMEPLAY;
                    InitGameplayScreen();
                }
            }
            default: break;
        }
        
        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        
            ClearBackground(RAYWHITE);
            
            switch(currentScreen) 
            {
                case LOGO: DrawLogoScreen(); break;
                case TITLE: DrawTitleScreen(); break;
                case OPTIONS: DrawOptionsScreen(); break;
                case GAMEPLAY: DrawGameplayScreen(); break;
                case PAUSE: DrawPauseScreen(); break;
                case ENDING: DrawEndingScreen(); break;
                
                default: break;
            }
            
            // Uncomment this to show FPS in game
            //DrawFPS(10, 10);
        
        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    
        // De-Initialization
    //--------------------------------------------------------------------------------------
    
    // Unload
    UnloadFont(font);
    UnloadMusicStream(music);
    
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;


}