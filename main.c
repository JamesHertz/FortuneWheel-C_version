#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "wheel.h"
//#include <termios.h> 

// errors:



// -> ask for name
#define MAX_LINE 1024

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
    // clear the buffer
    // fflush(stdin); // will it work?
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
    char * guess = strtok(NULL, "\n");    
    guess = strtrim(guess); // think about strtrim
    if(!guess || !strlen(guess)){
        printf("puzzle: NULL\n");
    }else{
        printf("puzzle: %s\n", guess);
    }
}

void displayPanel(fwheel w){
    player p = fw_player(w);
    printf("panel: %s\n", fw_panel(w));
    printf("Player: \vname: %.50s; points: %d\n", player_name(p), player_points(p));
}

int main(void){
    fwheel w;
    int err = 0;
    if(w = buildWheel()){
        printf("'%s' Welcome to Fortune Wheel!!\n", player_name(fw_player(w)));
        while(!fw_gameIsOver(w)){
            prompt();
            readLine();
            //  handle panel something else :)
            char * cmd = strtok(buf, "\n\r \t");
            if(!cmd); // do nothing :)
            else if(!strcmp(cmd, "puzzle")){
                runPuzzle(w);
            }else if(!strcmp(cmd, "rollete")){
                printf("executing rollete\n");
            }else if(!strcmp(cmd, "panel")){
                displayPanel(w);
            }else if(!strcmp(cmd, "help")){
                printf("listing commands\n");
            }else if(!strcmp(cmd, "exit")){
                break;
            }else{
                printf("Unknown command: %s\n", cmd);
            }
        }
        


	// puzzle ->
	// rollete ->
	// points ->
	// help ->
    }

    printf("Bye\n");
    return 0;
}
