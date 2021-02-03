#include "screens.hpp"
#include <iostream>
#include <math.h>
#include "raylib.h"

using namespace std;

extern "C" {
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
} 


static int framesCounter;
static int finishScreen;

static Vector2 mousePoint;

static Rectangle frameRec;

static int frameRecCounter;


static Player player;

static Texture2D texHearts;        
static Texture2D texPlayer;
static Texture2D texBullet;
static Texture2D texEnemy;

//----------------------------------------------------------------------------------
// Gameplay Screen Functions Definition
//----------------------------------------------------------------------------------

vector<Bullet>::iterator findNotActiveBullet(vector<Bullet>::iterator first,vector<Bullet>::iterator last){
  while (first!=last) {
    if (first->active == false) return first;
    ++first;
  }
  return last;
    
}

vector<Enemy>::iterator findNotActiveEnemy(vector<Enemy>::iterator first,vector<Enemy>::iterator last){
  while (first!=last) {
    if (first->active == false) return first;
    ++first;
  }
  return last;
    
}

//Player fire to mouse position
void ShotPlayer(){
    vector<Bullet>::iterator it = findNotActiveBullet(bullets.begin(), bullets.end());
            if (it != bullets.end())
            {
                it->radius = 2.0f;
                it->active = true;
                it->position = (Vector2){player.position.x + player.size.x / 2, player.position.y - it->radius * 5};
                it->speed = 4.0f * ((screenHeight+screenWidth)/(min_screenHeight+min_screenWidth));
                it->owner = "Player";
                // Calculate the straight line between the bullet position and mouse position.
                Recta recta = {0};
                recta.a = (mousePoint.y - it->position.y);
                recta.b = -(mousePoint.x - it->position.x);
                recta.c = (mousePoint.y - it->position.y) * it->position.x - (mousePoint.x - it->position.x) * it->position.y;

                if (mousePoint.x < it->position.x)
                {
                    recta.dir = -1;
                }
                else if (mousePoint.x > it->position.x)
                {
                    recta.dir = 1;
                }
                else
                {
                    recta.dir = 0;
                }
                it->dst = recta;

                lastShotFrame = framesCounter;

                
            }
            else
            {
                
                Bullet bullet = {0};
                bullet.radius = 2.0f;
                bullet.active = true;
                bullet.position = (Vector2){player.position.x + player.size.x / 2, player.position.y - bullet.radius * 5};
                bullet.speed = 4.0f * ((screenHeight+screenWidth)/(min_screenHeight+min_screenWidth));
                bullet.owner = "Player";

                // Calculate the straight line between the bullet position and mouse position.
                Recta recta = {0};
                recta.a = (mousePoint.y - bullet.position.y);
                recta.b = -(mousePoint.x - bullet.position.x);
                recta.c = (mousePoint.y - bullet.position.y) * bullet.position.x - (mousePoint.x - bullet.position.x) * bullet.position.y;

                if (mousePoint.x < bullet.position.x)
                {
                    recta.dir = -1;
                }
                else if (mousePoint.x > bullet.position.x)
                {
                    recta.dir = 1;
                }
                else
                {
                    recta.dir = 0;
                }
                bullet.dst = recta;

                bullets.push_back(bullet);
                lastShotFrame = framesCounter;
            }
}

// Enemy fire to player
void ShotEnemy(Enemy enemy){
    vector<Bullet>::iterator it = findNotActiveBullet(bullets.begin(), bullets.end());
            if (it != bullets.end())
            {
                it->radius = 2.0f;
                it->active = true;
                it->position = (Vector2){enemy.position.x + enemy.size.x / 2, enemy.position.y + it->radius * (35 * screenHeight / min_screenHeight) };
                it->speed = 4.0f * ((screenHeight+screenWidth)/(min_screenHeight+min_screenWidth));
                it->owner = "Enemy";
                
                // Calculate the straight line between the player position and bullet position.
                Recta recta = {0};
                recta.a = (player.position.y - it->position.y);
                recta.b = -(player.position.x - it->position.x);
                recta.c = (player.position.y - it->position.y) * it->position.x - (player.position.x - it->position.x) * it->position.y;

                if (player.position.x < it->position.x)
                {
                    recta.dir = -1;
                }
                else if (player.position.x > it->position.x)
                {
                    recta.dir = 1;
                }
                else
                {
                    recta.dir = 0;
                }
                it->dst = recta;

                

                
            }
            else
            {
                
                Bullet bullet = {0};
                bullet.radius = 2.0f;
                bullet.active = true;
                bullet.position = (Vector2){enemy.position.x + enemy.size.x / 2, enemy.position.y + bullet.radius * (35 * screenHeight / min_screenHeight)};
                bullet.speed = 4.0f * ((screenHeight+screenWidth)/(min_screenHeight+min_screenWidth));
                bullet.owner = "Enemy";

                // Calculate the straight line between the player position and bullet position.
                Recta recta = {0};
                recta.a = (player.position.y - bullet.position.y);
                recta.b = -(player.position.x - bullet.position.x);
                recta.c = (player.position.y - bullet.position.y) * bullet.position.x - (player.position.x - bullet.position.x) * bullet.position.y;

                if (player.position.x < bullet.position.x)
                {
                    recta.dir = -1;
                }
                else if (player.position.x > bullet.position.x)
                {
                    recta.dir = 1;
                }
                else
                {
                    recta.dir = 0;
                }
                bullet.dst = recta;

                bullets.push_back(bullet);
                
            }
}





// Gameplay Screen Initialization logic
void InitGameplayScreen(void)
{
    if(IsMusicPlaying(music))
        StopMusicStream(music);

    texHearts = LoadTexture("../resources/Hearts.png");
    texPlayer = LoadTexture("../resources/Player.png");
    texBullet = LoadTexture("../resources/ball.png");
    texEnemy = LoadTexture("../resources/Enemy.png");


    framesCounter = 0;
    finishScreen = 0;
    mousePoint = {0.0f,0.0f};
    frameRec = { 0.0f, 0.0f, (float)texHearts.width/4, (float)texHearts.height };
    frameRecCounter = 0;
    gamePaused = false;

    player = { 0 };
    player.position = (Vector2){ screenWidth/2.0f, screenHeight*6.0f/8.0f};
    player.speed = (Vector2){ 7.0f, 0.0f };
    player.size = (Vector2){ (0.5f*(screenHeight+screenWidth)/(monitorWidth + monitorHeight))*188.0f,
    (0.5f*(screenHeight+screenWidth)/(monitorWidth + monitorHeight))*280.0f };
    player.lifes = PLAYER_LIFES;


    

}

// Gameplay Screen Update logic
void UpdateGameplayScreen(void)
{
    mousePoint = GetMousePosition();

    finishScreen = 0;
    
    if (framesCounter % 9 > 7)
    {
        

        frameRecCounter++;

        if (frameRecCounter > 3)
            frameRecCounter = 0;

        frameRec.x = (float)frameRecCounter * (float)texHearts.width / 4;
    }

    // Pause the game
    if (IsKeyPressed('P')){
        finishScreen = 1;
        gamePaused = !gamePaused;
    }

    if (!gamePaused)
    {

        player.size = (Vector2){(0.5f * (screenHeight + screenWidth) / (monitorWidth + monitorHeight)) * 188.0f,
                                (0.5f * (screenHeight + screenWidth) / (monitorWidth + monitorHeight)) * 280.0f};
        
        player.position.y = screenHeight*6.0f/8.0f;

        framesCounter++;

        //Movement of the player
        if (IsKeyDown(KEY_LEFT) || IsKeyDown('A'))
            player.position.x -= player.speed.x;
        else if (IsKeyDown(KEY_RIGHT) || IsKeyDown('D'))
            player.position.x += player.speed.x;
        else
            player.position = (Vector2){player.position.x, screenHeight * 6.0f / 8.0f};

        if ((player.position.x) <= 0)
            player.position.x = 0;
        if ((player.position.x + player.size.x) >= screenWidth)
            player.position.x = screenWidth - player.size.x;

        player.bounds = (Rectangle){player.position.x, player.position.y, player.size.x, player.size.y};

        if ((framesCounter - lastShotFrame) / 30 >= CD_SHOT && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            ShotPlayer();


        // Enemies Spawn
        if (framesCounter % 60 == 0)
        {

            vector<Enemy>::iterator it = findNotActiveEnemy(enemies.begin(), enemies.end());
            if (it != enemies.end())
            {
                it->size = (Vector2){(0.5f * (screenHeight + screenWidth) / (monitorWidth + monitorHeight)) * 188.0f,
                                     (0.5f * (screenHeight + screenWidth) / (monitorWidth + monitorHeight)) * 280.0f};
                it->position = (Vector2){(rand() % screenWidth - it->size.x) + 1, -10};
                it->bounds = (Rectangle){it->position.x, it->position.y, it->size.x, it->size.y};
                it->active = true;
                it->speed = 1.0f + score / 50.0f;
                it->lastFrameShot = 0;
            }
            else
            {

                Enemy enemy = {0};
                enemy.size = (Vector2){(0.5f * (screenHeight + screenWidth) / (monitorWidth + monitorHeight)) * 188.0f,
                                       (0.5f * (screenHeight + screenWidth) / (monitorWidth + monitorHeight)) * 280.0f};
                enemy.position = (Vector2){(rand() % screenWidth - enemy.size.x) + 1, -10};
                enemy.speed = 1.0f + score / 50.0f;
                enemy.bounds = (Rectangle){enemy.position.x, enemy.position.y, enemy.size.x, enemy.size.y};
                enemy.active = true;
                enemy.lastFrameShot = -60;

                enemies.push_back(enemy);
            }
        }

        // Update all bullets
        for (vector<Bullet>::iterator it = bullets.begin(); it != bullets.end(); it++)
        {
            if (it->active == true)
            {
                if (CheckCollisionCircleRec(it->position, it->radius, player.bounds) && it->owner=="Enemy")
                    {
                        it->active = false;
                        player.lifes--;
                    }

                if ((it->position.x + it->radius > screenWidth) || (it->position.x - it->radius < 0))
                    it->active = false;
                if ((it->position.y + it->radius > screenHeight) || (it->position.y - it->radius < 0))
                    it->active = false;
                
                it->speed = 4.0f * ((screenHeight+screenWidth)/(min_screenHeight+min_screenWidth));
                
                
                float x = it->speed * it->dst.dir;
                
                float y = -(it->position.x * it->dst.a - it->dst.c) / it->dst.b;
                y = y - it->position.y;
                float square = sqrt(x * x + y * y);

                

                it->position.x += (x / square) * it->speed;
                it->position.y += (y / square) * it->speed;

               
            }
        }

        // Update all enemies
        for (vector<Enemy>::iterator it = enemies.begin(); it != enemies.end(); it++)
        {
            if (it->active == true)
            {
                if((framesCounter - it->lastFrameShot)/30 >= CD_SHOT_ENEMY && 
                static_cast<float>(rand())/static_cast<float>(RAND_MAX) >= 0.5f &&
                it->position.y <= screenHeight/2)
                {

                    ShotEnemy(*it);
                    it->lastFrameShot = framesCounter;

                }
                it->position.x = (float)((int)it->position.x % screenWidth);
                it->size = (Vector2){(0.5f * (screenHeight + screenWidth) / (monitorWidth + monitorHeight)) * 188.0f,
                                     (0.5f * (screenHeight + screenWidth) / (monitorWidth + monitorHeight)) * 280.0f};
                it->position.y += it->speed;

                it->bounds = (Rectangle){it->position.x, it->position.y, it->size.x, it->size.y};

                if (CheckCollisionRecs(it->bounds, player.bounds))
                {
                    it->active = false;
                    player.lifes--;
                }

                for (vector<Bullet>::iterator it2 = bullets.begin(); it2 != bullets.end(); it2++)
                {
                    if (CheckCollisionCircleRec(it2->position, it2->radius, it->bounds) && it2->active)
                    {
                        it2->active = false;
                        it->active = false;
                        score++;
                    }
                }

                if ((it->position.x > screenWidth) || (it->position.x < 0))
                    it->active = false;
                    
                if (it->position.y > screenHeight)
                {
                    it->active = false;
                    player.lifes--;
                }
            }
        }

        // Player no lifes logic
        if (player.lifes <= 0)
        {
            finishScreen = 2;
            player.lifes = PLAYER_LIFES;
            framesCounter = 0;
            if (score > maxScore)
                maxScore = score;
        }
    }
}

// Gameplay Screen Draw logic
void DrawGameplayScreen(void)
{
    DrawTextureEx(texPlayer, player.position, 0.0f, 0.5f * (screenHeight + screenWidth) / (monitorWidth + monitorHeight), WHITE); // Draw player

    for (vector<Bullet>::iterator it = bullets.begin(); it != bullets.end(); it++)
    {
        if (it->active)
            if(it->owner == "Player")
                DrawTexture(texBullet, it->position.x - it->radius / 2, it->position.y - it->radius / 2, BLUE);
            else
                DrawTexture(texBullet, it->position.x - it->radius / 2, it->position.y - it->radius / 2, MAROON);
    }
    for (vector<Enemy>::iterator it = enemies.begin(); it != enemies.end(); it++)
    {
        if (it->active)
            DrawTextureEx(texEnemy, it->position, 0.0f, 0.5f * (screenHeight + screenWidth) / (monitorWidth + monitorHeight), WHITE);

        
    }

    DrawTextEx(font, ("Score: " + to_string(score)).c_str(), (Vector2){20.0f, screenHeight - 70.0f}, 30, 3, BLACK);

    for (int i = 0; i < player.lifes; i++)
    {
        DrawTextureRec(texHearts, frameRec, (Vector2){screenWidth - 50.0f - 50.0f * i, screenHeight - 70.0f}, WHITE);
    }
}

// Gameplay Screen Unload logic
void UnloadGameplayScreen(void)
{
    UnloadTexture(texBullet);
    UnloadTexture(texEnemy);
    UnloadTexture(texHearts);
    UnloadTexture(texPlayer);
}

// Gameplay Screen should finish?
int FinishGameplayScreen(void)
{
    return finishScreen;
}

