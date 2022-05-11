#ifndef _FW_

#define _FW_

#include <stdbool.h>
#include "player.h"

#define UPPUZZLE    1000
#define DOWNPUZZLE    2000

#define MAX_SECRET_LEN 255
//255

typedef struct fw * fwheel;


int fw_init(fwheel *w, char * secret, char * player_name);

char * fw_panel(fwheel w);

bool fw_gameIsOver(fwheel w);

void fw_rollete(fwheel w, char guess, int points);

void fw_puzzle(fwheel w, char *guess);

char * fw_secret(fwheel w);

player fw_player();

bool fw_validSecret(char * secret);
// player

#endif