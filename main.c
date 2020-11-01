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
        Color obstacle_color;
        Color background_color;
        Color texte_color;
        char * name;
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
    player.position = (Vector2){(float)100, (float)320};
    player.taille=30;
    bool pause=false;
    player.jumpState=0;
    player.jumpFrame=0;
    player.state=0;
    int colisionOrNot=0;
    
    
    //Menu demarrer
    Rectangle level1={screenWidth/2-90,screenHeight/2-40,80,80};
    Rectangle level2={screenWidth/2+10,screenHeight/2-40,80,80};
    
    
    //menu GAME OVER
    Rectangle playAgain={screenWidth/2-90,screenHeight/2+20,180,50};
    Rectangle playAgainautreniveau={190,300,470,60};
    
    //menu Bravo
    Rectangle ceNiveau={80,220,300,40};
    Rectangle autreNiveau={80,290,300,45};
    int sourisOn=0;
    
    
    //CHoix du level ----------------------------------------------------------------------
    Level lvl1;
    generateLevel(&lvl1,2);
    
//-----------------------------------------------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        mousePosition = GetMousePosition();
        
        if(menu_state==0){ //menu choix du niveau
            if(CheckCollisionPointRec(mousePosition,level1) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                menu_state=1; generateLevel(&lvl1,1);
            }
            if(CheckCollisionPointRec(mousePosition,level2) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){ 
            menu_state=1;
            generateLevel(&lvl1,2);
            }
            if(CheckCollisionPointRec(mousePosition,level1)){
                sourisOn=1;
            }
            else if(CheckCollisionPointRec(mousePosition,level2)){
                sourisOn=2;
            }
            else {
                sourisOn=0;
            }
        }
        
        if(menu_state==1){ //en jeu
            if (IsKeyPressed(KEY_ENTER)) pause = !pause;
            if (pause==false)gameRun(&lvl1);
            surObstacle(&player, &lvl1);
            jump(&player);
            colisionOrNot=colision(&player,&lvl1);
            if(colisionOrNot==1)menu_state=2;
            if(checkWin(&lvl1)==1)menu_state=3;
        }
        
        if(menu_state==2){ //menu game over
            if(CheckCollisionPointRec(mousePosition,playAgain) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                menu_state=1;
                generateLevel(&lvl1,lvl1.number);
            }
            if(CheckCollisionPointRec(mousePosition,playAgainautreniveau) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                menu_state=0;
   
            }
            if(CheckCollisionPointRec(mousePosition,playAgain)){
                sourisOn=1;
            }
            else if(CheckCollisionPointRec(mousePosition,playAgainautreniveau)){
                sourisOn=2;
            }
            else{
                sourisOn=0;
            }
        }
        
        if(menu_state==3){ //menu niveau terminé
            if(CheckCollisionPointRec(mousePosition,ceNiveau) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                menu_state=1;
                generateLevel(&lvl1,lvl1.number);
            }
            if(CheckCollisionPointRec(mousePosition,autreNiveau) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                menu_state=0;
            }
            if(CheckCollisionPointRec(mousePosition,ceNiveau)){
                sourisOn=1;
            }
            else if(CheckCollisionPointRec(mousePosition,autreNiveau)){
                sourisOn=2;
            }
            else{
                sourisOn=0;
            }
        }
        
        
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        //Menu entrée
        if(menu_state==0){ //choix niveau
            ClearBackground(RAYWHITE);
            DrawText(TextFormat("Choose level" ), 240,100,50,RED);
            if(sourisOn==1){
                DrawRectangleRec(level1,GRAY);
            }
            if(sourisOn==2){
                DrawRectangleRec(level2,GRAY);
            }
            DrawRectangleLinesEx(level1,5,BLACK);
            DrawRectangleLinesEx(level2,5,BLACK);
            DrawText(TextFormat("1"), 343,200,60,RED);
            DrawText(TextFormat("2"), 433,200,60,RED);
        }
        
        else if(menu_state==1){ //En jeu
            //background
            ClearBackground(lvl1.background_color);
  
            
            //Player
            DrawCircle(player.position.x, player.position.y, player.taille, DARKBLUE);
            
            //Sol
            DrawLine(0,350, screenWidth,350, lvl1.obstacle_color);
            DrawRectangle(0,350,screenWidth,screenHeight,lvl1.obstacle_color);
            
            //Niveau
            for(obstacle_counter=0;obstacle_counter<lvl1.number_of_obstacle;obstacle_counter++){
                DrawRectangleRec(lvl1.obstacles[obstacle_counter].rect,lvl1.obstacle_color);
                }
            //Barre d'avancée
             DrawRectangleLines(40,40,lvl1.longueur/10,20,lvl1.texte_color);
             DrawRectangle(40,40,lvl1.avancee/10,20,lvl1.texte_color);
        }
        else if(menu_state==2){ // Menu Game Over
            ClearBackground(RAYWHITE);
            DrawText(TextFormat("GAME OVER"), 125,90,90, RED);
            DrawText(TextFormat("%.0f %%",lvl1.avancee/lvl1.longueur*100), 350,170,60, RED);
            DrawText(TextFormat("Ressayer"), 340,250,30, RED);
            DrawText(TextFormat("Ressayer un autre niveau"), 230,300,30, RED);
            if(sourisOn==1){
                DrawTriangle((Vector2){(float)330,(float)260},(Vector2){(float)315,(float)250},(Vector2){(float)315,(float)270},RED);
            }
            if(sourisOn==2){
                DrawTriangle((Vector2){(float)220,(float)310},(Vector2){(float)205,(float)300},(Vector2){(float)205,(float)320},RED);
            }
        }
        
        else if(menu_state==3){ //Menu niveau terminé
            ClearBackground(RAYWHITE);
            DrawText(TextFormat("Bravo !"), 250,90,90, RED);
            DrawText(TextFormat("Rejouer ce niveau"), 90,230,20, RED);
            DrawText(TextFormat("Rejouer sur un autre niveau"), 90,300,20, RED);
            if(sourisOn==1){
                DrawTriangle((Vector2){(float)80,(float)240},(Vector2){(float)70,(float)235},(Vector2){(float)70,(float)245},RED);
            }
            else if(sourisOn==2){
                DrawTriangle((Vector2){(float)80,(float)310},(Vector2){(float)70,(float)305},(Vector2){(float)70,(float)315},RED);
            }
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



void gameRun(Level * lvl){ //Fait avancer les obstacles et la progression du joueur dans le niveau
    int obstacle_counter;
    for(obstacle_counter=0;obstacle_counter<lvl->number_of_obstacle;obstacle_counter++){
    lvl->obstacles[obstacle_counter].rect.x =lvl->obstacles[obstacle_counter].rect.x-2*lvl->obstacles[obstacle_counter].speed;
    }
    lvl->avancee+=2;
}

void jump(Player * player){ //Gère le saut du joueur 
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

void surObstacle(Player * player, Level * lvl){ //Gère le fait que le joueur se trouve sur un obstacle
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

int checkWin(Level * lvl){ //Vérifie si le joueur a terminer le niveau
    int win=0;
    if(lvl->longueur==lvl->avancee)win=1;
    return win;
}

void generateLevel(Level * lvl1,int numero){
    int obstacle_counter;
    Obstacle obstacle1;
    Obstacle obstacle2;
    Obstacle obstacle3;
    Obstacle obstacle4;
    Obstacle obstacle5;
    Obstacle obstacle6; 
    if(numero==1){ //choix niveau 1
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
        
        lvl1->obstacles[0]=obstacle1;
        lvl1->obstacles[1]=obstacle2;
        lvl1->obstacles[2]=obstacle3;
        lvl1->obstacles[3]=obstacle4;
        lvl1->obstacles[4]=obstacle5;
        lvl1->obstacles[5]=obstacle6;
        lvl1->number_of_obstacle=6;
        lvl1->number=1;
        lvl1->avancee=0;
        lvl1->longueur=2300;
        
        for(obstacle_counter=0;obstacle_counter<lvl1->number_of_obstacle;obstacle_counter++){
        lvl1->obstacles[obstacle_counter].speed=1;
        lvl1->obstacles[obstacle_counter].playerOn=false;
        }
        
        lvl1->background_color=WHITE;
        lvl1->texte_color=RED;
        lvl1->obstacle_color=GREEN;
    }
    else if(numero==2){ //choix niveau 2
        obstacle1.rect.x=550;
        obstacle1.rect.width=50;
        obstacle1.rect.height=10;
        obstacle2.rect.x=650;
        obstacle2.rect.width=50;
        obstacle2.rect.height=10;
        obstacle3.rect.x=750;
        obstacle3.rect.width=50;
        obstacle3.rect.height=10;
        obstacle4.rect.x=850;
        obstacle4.rect.width=50;
        obstacle4.rect.height=10;
        obstacle5.rect.x=950;
        obstacle5.rect.width=50;
        obstacle5.rect.height=10;
        obstacle6.rect.x=1100;
        obstacle6.rect.width=50;
        obstacle6.rect.height=10;
        obstacle1.rect.y=350- obstacle1.rect.height;
        obstacle2.rect.y=330- obstacle2.rect.height;
        obstacle3.rect.y=310- obstacle3.rect.height;
        obstacle4.rect.y=290- obstacle4.rect.height;
        obstacle5.rect.y=270- obstacle5.rect.height;
        obstacle6.rect.y=250- obstacle6.rect.height;
        
        lvl1->obstacles[0]=obstacle1;
        lvl1->obstacles[1]=obstacle2;
        lvl1->obstacles[2]=obstacle3;
        lvl1->obstacles[3]=obstacle4;
        lvl1->obstacles[4]=obstacle5;
        lvl1->obstacles[5]=obstacle6;
        lvl1->number_of_obstacle=6;
        lvl1->number=2;
        lvl1->avancee=0;
        lvl1->longueur=100;
        
        for(obstacle_counter=0;obstacle_counter<lvl1->number_of_obstacle;obstacle_counter++){
        lvl1->obstacles[obstacle_counter].speed=1;
        lvl1->obstacles[obstacle_counter].playerOn=false;
        }
        
        lvl1->background_color=BLACK;
        lvl1->texte_color=YELLOW;
        lvl1->obstacle_color=YELLOW;
    }
}
