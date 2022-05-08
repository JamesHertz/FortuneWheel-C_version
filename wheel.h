#ifndef _FW_

#include <stdbool.h>
#include "player.h"

#define _FW_
#define MAX_SECRET_LEN 255
//255

typedef struct fw * fwheel;

typedef char secret[MAX_SECRET_LEN + 1];

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