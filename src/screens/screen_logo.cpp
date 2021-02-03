#include "raylib.h"
#include "screens.hpp"


static int framesCounter = 0;
static int finishScreen = 0;

static Texture2D texLogo;

//----------------------------------------------------------------------------------
// Logo Screen Functions Definition
//----------------------------------------------------------------------------------

// Logo Screen Initialization logic
void InitLogoScreen(void)
{
    texLogo = LoadTexture("../resources/raylib_logo.png");

    framesCounter = 0;
    finishScreen = 0;
    
    screenWidth = GetScreenWidth();
    screenHeight =  GetScreenHeight();
}

// Logo Screen Update logic
void UpdateLogoScreen(void)
{
    UpdateMusicStream(music);
    
    framesCounter++;
                
    if (framesCounter > 680) {
        finishScreen = 1;
        framesCounter = 0;
    }
}

// Logo Screen Draw logic
void DrawLogoScreen(void)
{
    if(framesCounter<=250){
        DrawTexture(texLogo,screenWidth/2 - texLogo.width/2,screenHeight/2 - texLogo.height/2,(Color){ 255, 255, 255, framesCounter});
    }else if(framesCounter>370 && framesCounter<=620){
        DrawTexture(texLogo,screenWidth/2 - texLogo.width/2,screenHeight/2 - texLogo.height/2,(Color){ 255, 255, 255, 620-framesCounter});
    }else if(framesCounter>250 && framesCounter<=370){
        DrawTexture(texLogo,screenWidth/2 - texLogo.width/2,screenHeight/2 - texLogo.height/2,WHITE);
    }
}

// Logo Screen Unload logic
void UnloadLogoScreen(void)
{
    UnloadTexture(texLogo);
    
}

// Logo Screen should finish?
int FinishLogoScreen(void)
{
    return finishScreen;
}



