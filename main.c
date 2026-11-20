#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

//============================== ENTITY ==============================

typedef enum EntityType {
   PLAYER,
   MONSTER,
} EntityType;

typedef struct Entity
{
   int id;
   char name[50];
   int MAX_HP;
   int hp;
   int strength;
   int X;
   int Y;
   EntityType entityType;
} Entity;

Entity createEntity(
   int id, 
   const char *name,
   int MAX_HP,
   int strength,
   EntityType entityType
){
   
   Entity entity;
   entity.id = id;
   strcpy(entity.name, name);
   entity.MAX_HP = MAX_HP;
   entity.hp = MAX_HP;
   entity.strength = strength;
   entity.entityType = entityType;
   entity.X = 0;
   entity.Y = 0;
   return entity;
}

void printEntity(Entity entity) {
    printf("%-13s %-10d\n", "Id:", entity.id);
    printf("%-13s %-10s\n", "Name:", entity.name);
    printf("%-13s %-10d\n", "MAX HP:", entity.MAX_HP);
    printf("%-13s %-10d\n", "HP:", entity.hp);
    printf("%-13s %-10d\n", "Strength:", entity.strength);
    printf("%-13s %-10d\n", "X:", entity.X);
    printf("%-13s %-10d\n", "Y:", entity.Y);
    printf("%-13s %-10s\n", "EntityType:",
        entity.entityType == PLAYER ? "PLAYER" : "MONSTER");
}

//============================== GAME MAP ==============================

const char playerSymbol = 'P';
const char monsterSymbol = 'M';
const char wallSymbol = '#';
const char groundSymbol = ' ';

typedef struct Level{
    Entity* monsters;
    int height;
    int width;
    char** level;
} Level;

typedef struct Map{
    Level* levels;
    int currentLevel;
} Map;

void printLevel(Level level){
    for(int i = 0; i < level.height; i++){
        for(int j = 0; j < level.width; j++){    
            printf("%c", level.level[i][j]);
        }
        printf("\n");
    }
}

Level inicializeEmptyLevel(int height, int width){
    Level level;
    level.level = malloc(height * sizeof(char*));
    level.height = height;
    level.width = width;

    for (int i = 0; i < height; i++) {
        level.level[i] = malloc(width * sizeof(char));
    }

    for(int i = 0; i < level.height; i++){
        for(int j = 0; j < level.width; j++){
            
            if(i == 0 || i == level.height - 1|| j == 0 || j == level.width - 1){
                level.level[i][j] = wallSymbol;
            }
            else{
                level.level[i][j] = groundSymbol;
            }
        }
    }

    return level;
}

Level inicializeStartLevel(int height, int width){

    Level level = inicializeEmptyLevel(height, width);

    level.level[height/2][width/2] = playerSymbol;

    return level;
}

Level inicializeRandomLevel(int height, int width){
    Level level = inicializeEmptyLevel(height, width);
    
    return level;
}

Map inicializeMap(Level startLevel){

    Map map;
    map.levels = malloc(1 * sizeof(Level));
    map.currentLevel = 0;

    map.levels[0] = startLevel;

    return map;
}

void move(Map *map, Entity *player, int oldX, int oldY, int newX, int newY){
    if(map->levels[map->currentLevel].level[newY][newX] == wallSymbol){
        return;
    }
    map->levels[map->currentLevel].level[oldY][oldX] = groundSymbol;
    player->X = newX;
    player->Y = newY;
    map->levels[map->currentLevel].level[player->Y][player->X] = playerSymbol;
}

void startGame() {
    Entity player = createEntity(1, "Bro", 9, 1, PLAYER);

    Level startLevel = inicializeStartLevel(13, 31);
    Map map = inicializeMap(startLevel);

    player.Y = 13 / 2;
    player.X = 31 / 2;

    system("cls");
    printLevel(map.levels[map.currentLevel]);

    while (1) {
        char key = _getch();
        int oldX = player.X;
        int oldY = player.Y;
        switch (key) {
            case 'w':
                move(&map, &player, oldX, oldY, player.X, player.Y - 1);
                break;

            case 's':
                //moveDown(&map, &player);
                move(&map, &player, oldX, oldY, player.X, player.Y + 1);
                break;

            case 'a':
                move(&map, &player, oldX, oldY, player.X - 1, player.Y);
                break;

            case 'd':
                move(&map, &player, oldX, oldY, player.X + 1, player.Y);
                break;

            case 'q':
                return;
        }

        system("cls");
        printLevel(map.levels[map.currentLevel]);
    }
}

int main(void) {
    

    startGame();

}