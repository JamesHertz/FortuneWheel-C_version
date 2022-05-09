#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "wheel.h"
#include "player.h"

#define UPPUZZLE    1000
#define DOWNPUZZLE    2000
#define RSIGN   '-'

struct fw{
    secret secret, panel;
    player player;
};

static void build_panel(fwheel w){
    int i;
    for(i = 0; w->secret[i]; i++){
        if(islower(w->secret[i]))
            w->panel[i] = RSIGN;
        else
            w->panel[i] = w->secret[i];
    }
    w->panel[i] = '\0';
}

bool fw_validSecret(char * secret){
    int len = strlen(secret);
    return len > 0 || len <= MAX_NAME_LEN;
}

// think about secret :)
int fw_init(fwheel *w, char * secret, char * player_name){
    int err;
    player p;
    if((err = player_init(&p, player_name)) < 0) return err;
    if(!fw_validSecret(secret)) return -2;
    // think about this later; 
    fwheel fw = malloc(sizeof(struct fw));
    fw->player = p;
    strcpy(fw->secret, secret);
    build_panel(fw);
    *w = fw;
    return 0;
}

char * fw_panel(fwheel w){
    return w->panel;
}

bool fw_gameIsOver(fwheel w){
    return !strcmp(w->panel, w->secret);
}

// seaches for the guess in w->secret 
// if it appears in w->secret and in w->panel returns -1
    // it appears in w->secret
static int solve_guess(fwheel w, char guess){
    int count = 0;
    char *panel = w->panel, * secret = w->secret;
    for(int i = 0; secret[i]; i++){
        if(secret[i] == guess){
            if(panel[i] == guess) return 0;
            count++;
            panel[i] = guess;
        }
    }
    return count;
}

// bugs
void fw_rollete(fwheel w, char guess, int points){
    int times = solve_guess(w, guess);
    if(!times) player_takePoints(w->player, points);
    else player_addPoints(w->player, times*points);
}

void fw_puzzle(fwheel w, char * guess){
   if(!strcmp(w->secret, guess)){
       strcpy(w->panel, w->secret);
       player_addPoints(w->player,UPPUZZLE);
   }else{
       player_takePoints(w->player, DOWNPUZZLE);
   }
}

char * fw_secret(fwheel w){
    return w->secret;
}

player fw_player(fwheel w){
    return w->player;
}