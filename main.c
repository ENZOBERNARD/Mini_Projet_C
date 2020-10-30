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
    bool playerOn;
    } Obstacle;
    
    typedef struct Level {
        Obstacle obstacles[40];
        int number_of_obstacle;
        int number;
        float avancee;
        float longueur;
    } Level;
   

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int menu_state=0; //0:Menu demarrage 1:Run 2:GAME OVER 3:Win
    int obstacle_counter;
    Vector2 mousePosition = { 0 };
    
    
    Image image_fondH=LoadImage("background_haut.png");
    Texture2D backgroundH = LoadTextureFromImage(image_fondH);  
    UnloadImage(image_fondH); 
    float scrollingB = 0.0f;
    float scrollingH = 0.0f;
    
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
    
    
    obstacle1.rect.x=750;
    obstacle1.rect.width=50;
    obstacle1.rect.height=40;
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
    lvl1.longueur=2300;
    
    
    for(obstacle_counter=0;obstacle_counter<lvl1.number_of_obstacle;obstacle_counter++){
    lvl1.obstacles[obstacle_counter].speed=1;
    lvl1.obstacles[obstacle_counter].playerOn=false;
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
    
    //menu GAME OVER
    Rectangle playAgain={screenWidth/2-100,screenHeight/2+20,200,80};
    
    
    

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        mousePosition = GetMousePosition();
        
        if(menu_state==0){
            if(CheckCollisionPointRec(mousePosition,play) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) menu_state=1;
        }
        
        if(menu_state==1){
            if (IsKeyPressed(KEY_ENTER)) pause = !pause;
            if (pause==false)gameRun(&lvl1);
            surObstacle(&player, &lvl1);
            jump(&player);
            colisionOrNot=colision(&player,&lvl1);
            if(colisionOrNot==1)menu_state=2;
            if(checkWin(&lvl1)==1)menu_state=3;
        }
        
        
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        //Menu entrée
        if(menu_state==0){
            ClearBackground(RAYWHITE);
            DrawRectangleLinesEx(play,5,BLACK);
            DrawText(TextFormat("PLAY"), 322,200,60, RED);
        }
        
        else if(menu_state==1){
      
            ClearBackground(RAYWHITE);
            //if(colisionOrNot==0){
            //background
            DrawTexture(backgroundH,100,100, WHITE);
         
            //ATH
            DrawText(TextFormat("Run! %d %d %d",colisionOrNot,player.jumpState, player.state ), 250,40,50, RED);
            
            //Player
            DrawCircle(player.position.x, player.position.y, player.taille, DARKBLUE);
            
            //Sol
            DrawLine(0,350, screenWidth,350, BLACK);
            
            //Niveau
            for(obstacle_counter=0;obstacle_counter<lvl1.number_of_obstacle;obstacle_counter++){
                DrawRectangleRec(lvl1.obstacles[obstacle_counter].rect,BLACK);
                }
            //Barre d'avancée
             DrawRectangleLines(40,40,lvl1.longueur/10,20,BLACK);
             DrawRectangle(40,40,lvl1.avancee/10,20,BLUE);
            }
        else if(menu_state==2){
            ClearBackground(RAYWHITE);
            DrawRectangleLinesEx(playAgain,5,BLACK);
            DrawText(TextFormat("GAME OVER"), 125,90,90, RED);
            DrawText(TextFormat("%.0f %%",lvl1.avancee/lvl1.longueur*100), 350,170,60, RED);
        }
        
        else if(menu_state==3){
            ClearBackground(RAYWHITE);
            DrawText(TextFormat("Bravo !"), 125,90,90, RED);
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
        lvl->obstacles[obstacle_counter].playerOn==false){
            player->jumpState=0;
            player->jumpFrame=0;
            player->state=4;
            lvl->obstacles[obstacle_counter].playerOn=true;
        }
        else if(((player->position.x-player->taille > lvl->obstacles[obstacle_counter].rect.x+lvl->obstacles[obstacle_counter].rect.width) || (player->position.x+player->taille < lvl->obstacles[obstacle_counter].rect.x))&&
        player->position.y+player->taille == lvl->obstacles[obstacle_counter].rect.y &&
        player->state==4 &&
        lvl->obstacles[obstacle_counter].playerOn==true
        ){
            player->jumpState=2;
            player->jumpFrame=25;
            lvl->obstacles[obstacle_counter].playerOn=false;
        }
    }
}

int checkWin(Level * lvl){
    int win=0;
    if(lvl->longueur==lvl->avancee)win=1;
    return win;
}