#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>
#include "wheel.h"
//#include <termios.h> 

// errors:

#define MAX_LINE 1024
#define DELIMITERS  "\n\t\r "

#define MAX_GUESS  250

// outputs amount of points gained or lost after a commad
#define outV(w, cmd)  \
     do{ \
            player _p = fw_player(w);\
            int _pts = player_points(_p);\
            cmd; \
            _pts = player_points(_p) - _pts;\
            if(_pts > 0)  \
                printf("+%d\n", _pts); \
            else \
                printf("%d\n", _pts); \
        }while(0)

char buf[MAX_LINE];

char * strtrim(char *s){
    if(!s) return NULL; // just because

    while(*s && isspace(*s)) s++;

    char * end = s + strlen(s) - 1;
    while(*end && end > s && isspace(*end)) end--;


    end[1] = '\0';
    return s;
}


/*
void clearBuf(){
	int c;
	while((c = getchar()) != '\n' && c != EOF);
}
*/

void readLine(){
    if(!fgets(buf, MAX_LINE, stdin)){
        //printf("something went wrong\n");
        exit(-1);
    }
}
char * getStr(int maxSize){
    readLine();
    char * str = strtrim(buf);
    int len = strlen(str);
    if(!len || len > maxSize) return NULL;
    return str;
}


bool confirm(){
    printf("Do you wanna try again? [Y/n]");
    readLine();
    char *a = strtrim(buf); // answer
    printf("confirm: %s\n", a);
    return !(strcmp(a, "Y") && strcmp(a, "y"));
}

fwheel buildWheel(){
    char *ptr, player_name[MAX_NAME_LEN];

    printf("choose a player name (it should be up to %d character): ", MAX_NAME_LEN);
    while(!(ptr = getStr(MAX_NAME_LEN))) {
        printf("Invalid name.\n");
        if(!confirm()) return NULL;
        printf("> ");
    }

    strcpy(player_name, ptr);
    printf("choose the secret (it should be up to %d character): ", MAX_SECRET_LEN);
    while(!(ptr= getStr(MAX_SECRET_LEN))){
        printf("Invalid secret.\n");
        if(!confirm()) return NULL;
        printf("> ");
    }
    

    //printf("p_name = %s\n", player_name);
    //printf("secret = %s\n", ptr);
    fwheel w;
    fw_init(&w, ptr, player_name);
    return w;
}

// commands

// hi there
void prompt(void){
    printf(">> ");
    fflush(stdout);
}

void runPuzzle(fwheel w){
    char * guess = strtrim(strtok(NULL, "\n"));
    if(!(guess && strlen(guess))){
        printf("Invalid guess.\n");
        return;
    }

    if(fw_gameIsOver(w)){
        printf("The game is over!\n");
        return;
    }

    outV(w, fw_puzzle(w, guess));

}

bool getInt(char *s, int * value){
    char *err;
    *value = strtol(s, &err, 0);
    return !*err && !errno; 
}

bool validPGuess(int value){
    return value > 0 && value <= MAX_GUESS;
}
bool validLetter(char *s){
    return strlen(s) == 1 && islower(*s);
}

void runRollete(fwheel w){
    char *ptr;
    int value;
    ptr = strtok(NULL, DELIMITERS);
    
    if(!(ptr && getInt(ptr, &value) && validPGuess(value))){
        printf("Invalid value!\n");
        return;
    }
        
    ptr = strtrim(strtok(NULL, "\n"));
    if(!(ptr && validLetter(ptr))){
        printf("Invalid letter!\n");
        return;
    }
    
    if(fw_gameIsOver(w)){
        printf("The game is over!\n");
        return;
    }

    outV(w, fw_rollete(w, *ptr, value));

}

void displayPanel(fwheel w){
    player p = fw_player(w);
    printf("panel: %s\n", fw_panel(w));
    printf("Player: \vname: %.50s; points: %d\n", player_name(p), player_points(p));
}


void help(){
    printf("commads:\n");
    printf(" * rollete <value> <character> - if such character appear in the secret and wasn't\ndiscovered yet the player gains (the number of times the character appears the secret) x (value) points\n");
    printf(" * puzzle <guess> - tries to guess the secret. If the player does it, the player gains %d points else it loses %d points\n", UPPUZZLE, DOWNPUZZLE);
// the rest ...

}

int main(void){
    fwheel w;
    int err = 0;
    if(w = buildWheel()){
        printf("'%s' Welcome to Fortune Wheel!!\n", player_name(fw_player(w)));
        printf("panel: %s\n",fw_panel(w));
        bool exit = false;
        while(!exit){
            prompt();
            readLine();
            //  handle panel something else :)
            char * cmd = strtok(buf, DELIMITERS);
            if(!cmd); // do nothing :)
            else if(!strcmp(cmd, "puzzle")){
                runPuzzle(w);
            }else if(!strcmp(cmd, "rollete")){
                runRollete(w);
            }else if(!strcmp(cmd, "panel")){
                displayPanel(w);
            }else if(!strcmp(cmd, "help")){
                help();
            }else if(!strcmp(cmd, "exit")){
                exit=true;
            }else{
                printf("Unknown command!\n");
            }
        }
        
    }

    printf("Bye\n");
    return 0;
}
