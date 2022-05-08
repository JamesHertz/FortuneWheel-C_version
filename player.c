#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "player.h"

struct player{
    char name[MAX_NAME_LEN + 1];
    int points;
};

bool player_validName(char * name){
    int len = strlen(name);
    return len > 0 && len <= MAX_NAME_LEN;
}

int player_init(player *pp, char * name){
    if(!player_validName(name)) return -1; //  AED teacher's talking 
    player p = malloc(sizeof(struct player));
    strcpy(p->name, name);
    p->points = 0;
    *pp = p;
    return 0;
}

char * player_name(player p){
    return p->name;
}

int player_points(player p){
    return p->points;
}

void player_addPoints(player p, int points){
    p->points+=points;
}

void player_takePoints(player p, int points){
    p->points-=points;
}

void player_resetPoints(player p){
    p->points=0;
}