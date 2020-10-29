#include "raylib.h"

   typedef struct Player {
    Vector2 position;
    int taille;
    float speed;
    int state; //0:sur le sol 1:Saute 2:tombe 3:Sur un obstacle
    int jumpState;
    int jumpFrame;
    } Player;
    
    typedef struct Obstacle {
    Rectangle rect;
    float speed;
    bool alwaysjump;
    } Obstacle;
    
    typedef struct Level {
        Obstacle obstacles[40];
        int number_of_obstacle;
        int number;
        float avancee;
    } Level;
   

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int menu_state=0; //0:Menu demarrage 1:Debut 2:Run 3:GAME OVER
    int obstacle_counter;
    Vector2 mousePosition = { 0 };
    
    const int screenWidth = 800;
    const int screenHeight = 450;
    
    Player player;
    //Niveau 1
    Level lvl1;
    Obstacle obstacle1;
    Obstacle obstacle2;
    Obstacle obstacle3;
    Obstacle obstacle4;
    Obstacle obstacle5;
    Obstacle obstacle6;
    
    
    obstacle1.rect.x=100;
    obstacle1.rect.width=50;
    obstacle1.rect.height=80;
    obstacle2.rect.x=950;
    obstacle2.rect.width=50;
    obstacle2.rect.height=80;
    obstacle3.rect.x=1200;
    obstacle3.rect.width=50;
    obstacle3.rect.height=40;
    obstacle4.rect.x=1450;
    obstacle4.rect.width=50;
    obstacle4.rect.height=40;
    obstacle5.rect.x=1800;
    obstacle5.rect.width=50;
    obstacle5.rect.height=40;
    obstacle6.rect.x=2000;
    obstacle6.rect.width=50;
    obstacle6.rect.height=40;
    obstacle1.rect.y=350- obstacle1.rect.height;
    obstacle2.rect.y=350- obstacle2.rect.height;
    obstacle3.rect.y=350- obstacle3.rect.height;
    obstacle4.rect.y=350- obstacle4.rect.height;
    obstacle5.rect.y=350- obstacle5.rect.height;
    obstacle6.rect.y=350- obstacle6.rect.height;
    
    lvl1.obstacles[0]=obstacle1;
    lvl1.obstacles[1]=obstacle2;
    lvl1.obstacles[2]=obstacle3;
    lvl1.obstacles[3]=obstacle4;
    lvl1.obstacles[4]=obstacle5;
    lvl1.obstacles[5]=obstacle6;
    lvl1.number_of_obstacle=6;
    lvl1.number=1;
    lvl1.avancee=0;
    
    
    for(obstacle_counter=0;obstacle_counter<lvl1.number_of_obstacle;obstacle_counter++){
    lvl1.obstacles[obstacle_counter].speed=1;
    lvl1.obstacles[obstacle_counter].alwaysjump=false;
    }
    //Menu demarrer
    
    Rectangle play={screenWidth/2-100,screenHeight/2-40,200,80};
    
    
    player.position = (Vector2){(float)100, (float)320};
    player.taille=30;
    bool pause=true;
    player.jumpState=0;
    player.jumpFrame=0;
    player.state=0;
    int colisionOrNot=0;
    
    
    

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        mousePosition = GetMousePosition();
        
        if (IsKeyPressed(KEY_ENTER)) pause = !pause;
        if (pause==false)gameRun(&lvl1);
        surObstacle(&player, &lvl1);
        jump(&player);
        
        colisionOrNot=colision(&player,&lvl1);
        if(CheckCollisionPointRec(mousePosition,play) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) menu_state=1;
        
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        //Menu entrée
        ClearBackground(RAYWHITE);
        if(menu_state==0){
            DrawRectangleRec(play,BLACK);
        }
        else if(menu_state==1){
      
            ClearBackground(RAYWHITE);
            //if(colisionOrNot==0){
            DrawText(TextFormat("Run! %d %d %d",colisionOrNot,player.jumpState, player.state ), 250,40,50, RED);
            DrawCircle(player.position.x, player.position.y, player.taille, DARKBLUE);
            DrawLine(0,350, screenWidth,350, BLACK);
            for(obstacle_counter=0;obstacle_counter<lvl1.number_of_obstacle;obstacle_counter++){
                DrawRectangleRec(lvl1.obstacles[obstacle_counter].rect,BLACK);
                }
            //Barre d'avancée
             DrawRectangleLines(40,40,200,20,BLACK);
             DrawRectangle(40,40,lvl1.avancee/10,20,BLUE);
            //}
            //else{
             //   DrawText(TextFormat("t'a perdu"), 350,40,50, RED);
            //}
        }    
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}



void gameRun(Level * lvl){
    int obstacle_counter;
    for(obstacle_counter=0;obstacle_counter<lvl->number_of_obstacle;obstacle_counter++){
    lvl->obstacles[obstacle_counter].rect.x =lvl->obstacles[obstacle_counter].rect.x-2*lvl->obstacles[obstacle_counter].speed;
    }
    lvl->avancee+=2;
}

void jump(Player * player){
    switch (player->jumpState){
        case 0 :
            if(IsKeyDown(KEY_SPACE)){
                player->jumpState=1;
                player->state=1;
            }
            break;
        case 1 :
            if(player->jumpFrame<=20){
                player->position.y -=5;
                player->jumpFrame++;
            }
            else{
                player->jumpState=2;
                player->state=2;
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
                player->state=0;
            }
            break;
    }
}

int colision(Player * player,Level * lvl){ //J'ai créer cette fonction en pensant que raylib n'avait pas de fonction gérant les collisions
    int obstacle_counter;
    int retour=0;
    for(obstacle_counter=0;obstacle_counter<lvl->number_of_obstacle;obstacle_counter++){
        if(player->position.x+player->taille > lvl->obstacles[obstacle_counter].rect.x &&
            player->position.x-player->taille < lvl->obstacles[obstacle_counter].rect.x+lvl->obstacles[obstacle_counter].rect.width &&
            player->position.y+player->taille > lvl->obstacles[obstacle_counter].rect.y &&
            player->position.y-player->taille <lvl->obstacles[obstacle_counter].rect.y+lvl->obstacles[obstacle_counter].rect.height)
            {
            retour=1;
            break;
        }
    }
    return retour;
    
}

void surObstacle(Player * player, Level * lvl){
    int obstacle_counter;
    for(obstacle_counter=0;obstacle_counter<lvl->number_of_obstacle;obstacle_counter++){
        if(player->position.y+player->taille == lvl->obstacles[obstacle_counter].rect.y &&
        player->position.x-player->taille < lvl->obstacles[obstacle_counter].rect.x+lvl->obstacles[obstacle_counter].rect.width &&
        player->position.x+player->taille > lvl->obstacles[obstacle_counter].rect.x &&
        player->jumpState!=0 &&
        lvl->obstacles[obstacle_counter].alwaysjump==false){
            player->jumpState=0;
            player->jumpFrame=0;
            player->state=4;
            lvl->obstacles[obstacle_counter].alwaysjump=true;
        }
        else if(((player->position.x-player->taille > lvl->obstacles[obstacle_counter].rect.x+lvl->obstacles[obstacle_counter].rect.width) || (player->position.x+player->taille < lvl->obstacles[obstacle_counter].rect.x))&&
        player->position.y+player->taille == lvl->obstacles[obstacle_counter].rect.y &&
        player->state==4
        ){
            player->jumpState=0;
            player->jumpFrame=25;
        }
    }
}