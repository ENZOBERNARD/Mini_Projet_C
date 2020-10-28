#include "raylib.h"

   typedef struct Player {
    Vector2 position;
    float speed;
    bool canJump;
    int jumpState;
    int jumpFrame;
    } Player;
    
    typedef struct Obstacle {
    Vector2 position;
    float speed;
    } Obstacle;
   

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------


    const int screenWidth = 800;
    const int screenHeight = 450;
    
    Player player;
    Obstacle obstacle;
    player.position = (Vector2){(float)100, (float)320};
    obstacle.position= (Vector2){(float)700, (float)270};
    obstacle.speed=1;
    bool pause=true;
    player.jumpState=0;
    player.jumpFrame=0;
    
    
    

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        if (IsKeyPressed(KEY_ENTER)) pause = !pause;
        if (pause==false)gameRun(&obstacle);
        jump(&player);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Run!", 350,40,50, RED);
            DrawCircle(player.position.x, player.position.y, 30, DARKBLUE);
            DrawLine(0,350, screenWidth,350, BLACK);
            DrawRectangle(obstacle.position.x,obstacle.position.y,50,80,BLACK);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}



void gameRun(Obstacle * obstacle){
    obstacle->position.x =obstacle->position.x-2*obstacle->speed;
    
}

void jump(Player * player){
    switch (player->jumpState){
        case 0 :
            if(IsKeyDown(KEY_SPACE)){
                player->jumpState=1;
            }
            break;
        case 1 :
            if(player->jumpFrame<=20){
                player->position.y -=5;
                player->jumpFrame++;
            }
            else{
                player->jumpState=2;
            }
            break;
        case 2:
            if(player->position.y<320){
                player->position.y +=5;
                player->jumpFrame++;
            }
            else{
                player->jumpState=0;
                player->jumpFrame=0;
            }
            break;
    }
}