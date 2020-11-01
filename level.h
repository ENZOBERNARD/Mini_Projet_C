#include "raylib.h"


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
    
Level generateLevel(int numero);