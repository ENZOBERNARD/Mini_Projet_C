 #include "raylib.h"
 
 typedef struct Player { //structure du joueur 
    Vector2 position;
    int taille;
    float speed;
    int state; //0:sur le sol 1:Saute 2:tombe 3:Sur un obstacle
    int jumpState;
    int jumpFrame;
    Color couleur;
    } Player;
    
    typedef struct Obstacle { //structure d'un obstacle
    Rectangle rect;
    float speed;
    bool playerOn;
    } Obstacle;
    
    typedef struct Level { //structure d'un niveau qui est un ensemble d'obstacle
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
    
    void gameRun(Level * lvl);
    void jump(Player * player);
    int collision(Player * player,Level * lvl);
    void surObstacle(Player * player, Level * lvl);
    int checkWin(Level * lvl);
    void generateLevel(Level * lvl1,int numero);