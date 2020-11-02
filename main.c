
#include "geo.h"

   

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int menu_state=0; //0:Menu demarrage 1:Run 2:GAME OVER 3:Win 4:choix skin
    
    int obstacle_counter; //POur compter les obstzcles dans une boucle for
    
    Vector2 mousePosition = { 0 }; // vecteur position de la souris
    
    const int screenWidth = 800; 
    const int screenHeight = 450;
    
    int collisionOrNot=0;
    
    Player player; //initialisation des variables de player
    player.position = (Vector2){(float)100, (float)320};
    player.taille=30;
    bool pause=false;
    player.jumpState=0;
    player.jumpFrame=0;
    player.state=0;
    player.couleur=BLUE;
    
    //Menu Pause
    Rectangle reprendre={screenWidth/2-100,180,200,50};
    Rectangle quitter={screenWidth/2-100,260,200,50};
    
    
    //Menu demarrer
    Rectangle level1={screenWidth/2-90,screenHeight/2-40,80,80};
    Rectangle level2={screenWidth/2+10,screenHeight/2-40,80,80};
    Rectangle choixskin={460,340,100,40};
    
    
    //menu GAME OVER
    Rectangle playAgain={screenWidth/2-90,screenHeight/2+20,180,50};
    Rectangle playAgainautreniveau={190,300,470,60};
    
    //menu Bravo
    Rectangle ceNiveau={80,220,300,40};
    Rectangle autreNiveau={80,290,300,45};
    int sourisOn=0;
    
    //menu choix couleur perso
    Rectangle Bleu={125,50,150,150};
    Rectangle Violet={325,50,150,150};
    Rectangle Rose={525,50,150,150};
    Rectangle Orange={125,250,150,150};
    Rectangle Jaune={325,250,150,150};
    Rectangle Vert={525,250,150,150};
    
    //CHoix du level ----------------------------------------------------------------------
    Level lvl1;
    generateLevel(&lvl1,2); //generation du niveau
    
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
        //on regarde si il y a collision pour les animations et on check si il y a click pour changer de menu
            if(CheckCollisionPointRec(mousePosition,level1) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                menu_state=1; generateLevel(&lvl1,1);
            }
            if(CheckCollisionPointRec(mousePosition,level2) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){ 
            menu_state=1;
            generateLevel(&lvl1,2);
            }
            if(CheckCollisionPointRec(mousePosition,choixskin) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){ 
            menu_state=4;
            }
            if(CheckCollisionPointRec(mousePosition,level1)){
                sourisOn=1;
            }
            else if(CheckCollisionPointRec(mousePosition,level2)){
                sourisOn=2;
            }
            if(CheckCollisionPointRec(mousePosition,choixskin)){
                sourisOn=3;
            }
            else {
                sourisOn=0;
            }
        }
        
        if(menu_state==1){ //en jeu
            if (IsKeyPressed(KEY_ENTER)) pause = !pause; //appuyer sur ENTREE pour faire pause
            if(pause==false){
                if (pause==false)gameRun(&lvl1);
                surObstacle(&player, &lvl1); //les obstacles avance
                jump(&player); //le player peut sauter
                collisionOrNot=collision(&player,&lvl1); //check des collisions
                if(collisionOrNot==1)menu_state=2; //Si collision GAME OVER
                if(checkWin(&lvl1)==1)menu_state=3; //check si le joueur a fini le niveau si oui, menu fin du niveau
            }
            else{
                if(CheckCollisionPointRec(mousePosition,reprendre) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                    pause= !pause;
                }
                if(CheckCollisionPointRec(mousePosition,quitter) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                    menu_state=0;
                }
                if(CheckCollisionPointRec(mousePosition,reprendre)){
                    sourisOn=1;
                }
                else if(CheckCollisionPointRec(mousePosition,quitter)){
                    sourisOn=2;
                }
                else{
                    sourisOn=0;
                }
            }
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
        
        if(menu_state==4){//Menu pour changer la couleur du player
             if(CheckCollisionPointRec(mousePosition,Bleu) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                player.couleur=BLUE;
                menu_state=0;
            }
             if(CheckCollisionPointRec(mousePosition,Orange) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                player.couleur=ORANGE;
                menu_state=0;
            }
             if(CheckCollisionPointRec(mousePosition,Jaune) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                player.couleur=YELLOW;
                menu_state=0;
            }
             if(CheckCollisionPointRec(mousePosition,Vert) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                player.couleur=GREEN;
                menu_state=0;
            }
             if(CheckCollisionPointRec(mousePosition,Rose) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                player.couleur=PINK;
                menu_state=0;
            } 
            if(CheckCollisionPointRec(mousePosition,Violet) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                player.couleur=PURPLE;
                menu_state=0;
            }
            
            
            if(CheckCollisionPointRec(mousePosition,Bleu)){
                sourisOn=1;
            }
            else if(CheckCollisionPointRec(mousePosition,Jaune)){
                sourisOn=2;
            }
            else if(CheckCollisionPointRec(mousePosition,Vert)){
                sourisOn=3;
            }
            else if(CheckCollisionPointRec(mousePosition,Violet)){
                sourisOn=4;
            }
            else if(CheckCollisionPointRec(mousePosition,Rose)){
                sourisOn=5;
            }
            else if(CheckCollisionPointRec(mousePosition,Orange)){
                sourisOn=6;
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
            if(sourisOn==1){ //animation si passage d ela souris
                DrawRectangleRec(level1,GRAY);
            }
            if(sourisOn==2){
                DrawRectangleRec(level2,GRAY);
            }
            DrawRectangle(460,340,100,40,player.couleur);
            DrawRectangleLinesEx(level1,5,BLACK);
            DrawRectangleLinesEx(level2,5,BLACK);
            DrawRectangleLinesEx(choixskin,5,BLACK);
            DrawText(TextFormat("1"), 343,200,60,RED);
            DrawText(TextFormat("2"), 433,200,60,RED);
            DrawText(TextFormat("apparence"),270,340,30,RED);
        }
        
        else if(menu_state==1){ //En jeu
            //background
            ClearBackground(lvl1.background_color);
  
            
            //Player
            DrawCircle(player.position.x, player.position.y, player.taille, player.couleur);
            
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
             
             if(pause==true){ //Menu Pause
                 DrawRectangle(screenWidth/2-100,screenHeight/2-150,200,300,WHITE);
                 DrawRectangleLines(screenWidth/2-100,screenHeight/2-150,200,300,BLACK);
                 DrawText(TextFormat("Pause" ), 325,100,50,RED);
                 DrawText(TextFormat("Reprendre" ), 325,185,30,RED);
                 DrawText(TextFormat("Quitter" ), 345,265,30,RED);
                 if(sourisOn==1){
                     DrawTriangle((Vector2){(float)315,(float)200},(Vector2){(float)305,(float)190},(Vector2){(float)305,(float)210},RED);
                 }
                 if(sourisOn==2){
                     DrawTriangle((Vector2){(float)335,(float)275},(Vector2){(float)325,(float)265},(Vector2){(float)325,(float)285},RED);
                 }
                 
             }
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
        
        if(menu_state==4){
            ClearBackground(RAYWHITE);
            DrawRectangleRec(Bleu,BLUE);
            DrawRectangleRec(Jaune,YELLOW);
            DrawRectangleRec(Violet,PURPLE);
            DrawRectangleRec(Rose,PINK);
            DrawRectangleRec(Vert,GREEN);
            DrawRectangleRec(Orange,ORANGE);
            DrawRectangleLinesEx(Bleu,5,BLACK);
            DrawRectangleLinesEx(Jaune,5,BLACK);
            DrawRectangleLinesEx(Violet,5,BLACK);
            DrawRectangleLinesEx(Rose,5,BLACK);
            DrawRectangleLinesEx(Vert,5,BLACK);
            DrawRectangleLinesEx(Orange,5,BLACK);
            if(sourisOn==1){
                DrawRectangleLinesEx(Bleu,10,BLACK);
            }
            if(sourisOn==2){
                DrawRectangleLinesEx(Jaune,10,BLACK);
            }
            if(sourisOn==3){
                DrawRectangleLinesEx(Vert,10,BLACK);
            }
            if(sourisOn==4){
                DrawRectangleLinesEx(Violet,10,BLACK);
            }
            if(sourisOn==5){
                DrawRectangleLinesEx(Rose,10,BLACK);
            }
            if(sourisOn==6){
                DrawRectangleLinesEx(Orange,10,BLACK);
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
    for(obstacle_counter=0;obstacle_counter<lvl->number_of_obstacle;obstacle_counter++){ //fait avancer les obstacles d el'ensemble du niveau
    lvl->obstacles[obstacle_counter].rect.x =lvl->obstacles[obstacle_counter].rect.x-2*lvl->obstacles[obstacle_counter].speed;
    }
    lvl->avancee+=2;
}

void jump(Player * player){ //Gère le saut du joueur 
    switch (player->jumpState){
        case 0 ://le joueur est au sol
            if(IsKeyDown(KEY_SPACE)){
                player->jumpState=1;
                player->state=1;
            }
            break;
        case 1 ://le joueur est entrain de monter
            if(player->jumpFrame<=20){
                player->position.y -=5;
                player->jumpFrame++;
            }
            else{
                player->jumpState=2;
                player->state=2;
            }
            break;
        case 2://le joueur est entrain de retomber
            if(player->position.y<320){//Le joueur encore dans les airs
                player->position.y +=5;
                player->jumpFrame++;
            }
            else{ //Le joueur est au sol
                player->jumpState=0;
                player->jumpFrame=0;
                player->state=0;
            }
            break;
    }
}

int collision(Player * player,Level * lvl){ //J'ai créer cette fonction en pensant que raylib n'avait pas de fonction gérant les collisions
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
        lvl1->longueur=1500;
        
        for(obstacle_counter=0;obstacle_counter<lvl1->number_of_obstacle;obstacle_counter++){
        lvl1->obstacles[obstacle_counter].speed=1;
        lvl1->obstacles[obstacle_counter].playerOn=false;
        }
        
        lvl1->background_color=BLACK;
        lvl1->texte_color=YELLOW;
        lvl1->obstacle_color=YELLOW;
    }
}
