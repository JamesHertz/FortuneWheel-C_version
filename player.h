#ifndef _WPLAYER_
#define _WPLAYER_

#include <stdbool.h> 
#define MAX_NAME_LEN 127 

typedef struct player *player;

int player_init(player *p, char * name);

int player_points(player p);

char * player_name(player p);

// think about this later :)
void player_addPoints(player p, int points);
void player_takePoints(player p, int points);
void player_resetPoints(player p);

bool player_validName(char * name);
#endif