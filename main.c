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
    Vector2 position;
    Vector2 taille;
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
    int menu_state; //0:Menu demarrage 1:Debut 2:Run 3:GAME OVER
    int obstacle_counter;
    
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
    
    
    obstacle1.taille= (Vector2){(float)50, (float)80};
    obstacle1.position= (Vector2){(float)750, (float)350-obstacle1.taille.y};
    obstacle2.taille= (Vector2){(float)50, (float)20};
    obstacle2.position= (Vector2){(float)950, (float)350-obstacle2.taille.y};
    obstacle3.taille= (Vector2){(float)50, (float)100};
    obstacle3.position= (Vector2){(float)1200, (float)350-obstacle3.taille.y};
    obstacle4.taille= (Vector2){(float)50, (float)40};
    obstacle4.position= (Vector2){(float)1450, (float)350-obstacle4.taille.y};
    obstacle5.taille= (Vector2){(float)50, (float)30};
    obstacle5.position= (Vector2){(float)1800, (float)350-obstacle5.taille.y};
    obstacle6.taille= (Vector2){(float)50, (float)10};
    obstacle6.position= (Vector2){(float)2000, (float)350-obstacle6.taille.y};
    
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
    lvl1.obstacles[obstacle_counter].speed=1.5;
    lvl1.obstacles[obstacle_counter].alwaysjump=false;
    }
    
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
        if (IsKeyPressed(KEY_ENTER)) pause = !pause;
        if (pause==false)gameRun(&lvl1);
        jump(&player);
        surObstacle(&player, &lvl1);
        colisionOrNot=colision(&player,&lvl1);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        //Menu entrée
        if(menu_state==0){
            DrawRectangle
        }
        
      
            ClearBackground(RAYWHITE);
            //if(colisionOrNot==0){
            DrawText(TextFormat("Run! %d %d",colisionOrNot,player.jumpState), 350,40,50, RED);
            DrawCircle(player.position.x, player.position.y, player.taille, DARKBLUE);
            DrawLine(0,350, screenWidth,350, BLACK);
            for(obstacle_counter=0;obstacle_counter<lvl1.number_of_obstacle;obstacle_counter++){
                DrawRectangle(lvl1.obstacles[obstacle_counter].position.x,lvl1.obstacles[obstacle_counter].position.y,lvl1.obstacles[obstacle_counter].taille.x,lvl1.obstacles[obstacle_counter].taille.y,BLACK);
                }
            //Barre d'avancée
             DrawRectangleLines(40,40,200,20,BLACK);
             DrawRectangle(40,40,lvl1.avancee/10,20,BLUE);
            //}
            //else{
             //   DrawText(TextFormat("t'a perdu"), 350,40,50, RED);
            //}
            
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
    lvl->obstacles[obstacle_counter].position.x =lvl->obstacles[obstacle_counter].position.x-2*lvl->obstacles[obstacle_counter].speed;
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

int colision(Player * player,Level * lvl){
    int obstacle_counter;
    int retour=0;
    for(obstacle_counter=0;obstacle_counter<lvl->number_of_obstacle;obstacle_counter++){
        if(player->position.x+player->taille > lvl->obstacles[obstacle_counter].position.x &&
            player->position.x-player->taille < lvl->obstacles[obstacle_counter].position.x+lvl->obstacles[obstacle_counter].taille.x &&
            player->position.y+player->taille > lvl->obstacles[obstacle_counter].position.y &&
            player->position.y-player->taille <lvl->obstacles[obstacle_counter].position.y+lvl->obstacles[obstacle_counter].taille.y)
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
        if(player->position.y+player->taille == lvl->obstacles[obstacle_counter].position.y &&
        player->position.x-player->taille < lvl->obstacles[obstacle_counter].position.x+lvl->obstacles[obstacle_counter].taille.x &&
        player->position.x+player->taille > lvl->obstacles[obstacle_counter].position.x &&
        player->jumpState!=0 &&
        lvl->obstacles[obstacle_counter].alwaysjump==false){
            player->jumpState=0;
            player->jumpFrame=0;
            player->state=4;
            lvl->obstacles[obstacle_counter].alwaysjump=true;
        }
        else if((player->position.x-player->taille > lvl->obstacles[obstacle_counter].position.x+lvl->obstacles[obstacle_counter].taille.x || player->position.x+player->taille < lvl->obstacles[obstacle_counter].position.x)&&
        player->position.y+player->taille == lvl->obstacles[obstacle_counter].position.y &&
        player->state==4
        ){
            player->jumpState=2;
            player->jumpFrame=25;
        }
    }
}