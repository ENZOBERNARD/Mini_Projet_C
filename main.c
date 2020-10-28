#include "raylib.h"

   typedef struct Player {
    Vector2 position;
    int taille;
    float speed;
    bool canJump;
    int jumpState;
    int jumpFrame;
    } Player;
    
    typedef struct Obstacle {
    Vector2 position;
    Vector2 taille;
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
    player.taille=30;
    obstacle.position= (Vector2){(float)155, (float)270};
    obstacle.taille= (Vector2){(float)50, (float)80};
    obstacle.speed=0.2;
    bool pause=true;
    player.jumpState=0;
    player.jumpFrame=0;
    int colisionOrNot=0;
    
    
    

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
        colisionOrNot=colision(&player,&obstacle);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText(TextFormat("Run! %d",colisionOrNot), 350,40,50, RED);
            DrawCircle(player.position.x, player.position.y, player.taille, DARKBLUE);
            DrawLine(0,350, screenWidth,350, BLACK);
            DrawRectangle(obstacle.position.x,obstacle.position.y,obstacle.taille.x,obstacle.taille.y,BLACK);
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

int colision(Player * player,Obstacle * obstacle){
    if(player->position.x+player->taille > obstacle->position.x &&
    player->position.x-player->taille < obstacle->position.x+obstacle->taille.x &&
    player->position.y+player->taille > obstacle->position.y &&
    player->position.y-player->taille < obstacle->position.y+obstacle->taille.y
    ){
        return 1;
    }
    else return 0;
    
}