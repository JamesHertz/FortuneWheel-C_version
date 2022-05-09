#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "wheel.h"
#include <ctype.h>

// player tests
#define run_test(t) t(); printf("%s(): SUCCESS\n", #t) 


void testPlayerInit(){
    char longName[300];
    memset(longName, 'j', 299);
    longName[299] = 0;
    player p;
    assert(player_init(&p, longName) < 0);
    longName[0] = '\0';
    assert(player_init(&p, longName) < 0);
    strcpy(longName, "James");
    assert(player_init(&p, longName) == 0); 
    assert(player_points(p) == 0);
    assert(!strcmp(player_name(p), longName));
}


void testPlayerPoints(){
    player p;
    int points = rand() % 100;
    player_init(&p, "James Hertz");
    player_addPoints(p, points);
    assert(player_points(p) == points);
    player_takePoints(p, 2*points);
    assert(player_points(p) == -points);
    player_resetPoints(p);
    assert(player_points(p) == 0);
}


char * boolToStr(bool b){
    return (b) ? "true":"false";
}

void miniTestW(){
    fwheel w;
    assert(!fw_init(&w, "i was here", "James Hertz"));
    player p = fw_player(w);
    printf("board: %s\n", fw_panel(w));
    printf("secret: %s\n", fw_secret(w));
    printf("player_name: %s\n", player_name(p));
    printf("isover: %s\n", boolToStr(fw_gameIsOver(w)));
    fw_puzzle(w, "was here");
    printf("puzzle.....\n");
    printf("board: %s\n", fw_panel(w));
    printf("player_points: %d\n", player_points(p));

    printf("puzzle.....\n");
    fw_puzzle(w, "i was here");
    printf("board: %s\n", fw_panel(w));
    printf("player_points: %d\n", player_points(p));
    printf("isover: %s\n", boolToStr(fw_gameIsOver(w)));


}


void miniTestW2(){
    fwheel w;
    assert(!fw_init(&w, "i was here", "James Hertz"));
    player p = fw_player(w);
}

int c_times(char *s, char c){
    int count = 0;
    for(; *s; s++)
        if(*s == c) count++;
   return count; 
}

void testRollete(){
    fwheel w;
    player p;
    char * secret = "hi there";
    assert(!fw_init(&w, secret, "James Hertz"));
    assert(!strcmp(fw_secret(w), secret));
    p = fw_player(w);
    // get all the chars + some others and try each one of them
    char g[] = {'a', 'e', 'i', 'o', 'u', 't', 'h', 't', 'r'};
    int points = 0;
    bool gained;
    for(int i = 0; i < sizeof(g); i++){
        gained = false;
        int stimes = c_times(secret, g[i]);
        int btimes = c_times(fw_panel(w), g[i]);
        int gpoints= 100 + (rand() % 900);
        fw_rollete(w, g[i], gpoints);
        if(stimes && !btimes){
            points += stimes * gpoints;
            btimes = c_times(fw_panel(w), g[i]);
            gained=true;
        }else
            points -= gpoints;

        assert(btimes == stimes);
        bool cond = player_points(p) == points;
        /* 
        DEBUG
        if(!cond){
            printf("gained: %s\n", boolToStr(gained));
            printf("board: %s\n", fw_panel(w));
            printf("secret: %s\n", fw_secret(w));
            printf("guess: %c\n", g[i]);
            printf("gpoints: %d\n", gpoints);
            printf("points: %d\n", points);
            printf("player_points: %d\n", player_points(p));
        }
        */
        assert(cond);
    }
    assert(fw_gameIsOver(w));
    // array of secrets ....
    // test each possible case ....

}

void initPW(fwheel *w, player * p, char *s){
    assert(!fw_init(w, s, "James Hertz"));
    assert(!strcmp(fw_secret(*w), s));
    *p = fw_player(*w);
}

void testPuzzle(){
    #define DP 2000
    #define UP 1000
    fwheel w;
    player p;
    char secret[] = "say something boy";
    initPW(&w, &p, secret);

    fw_puzzle(w, "nothing");
    assert(player_points(p) == -DP);

    free(w);
    free(p);

    
    strcpy(secret, "new secret!");
    initPW(&w, &p, secret);
    fw_puzzle(w, secret);
    assert(player_points(p) == UP);
    #undef DP
    #undef UP 
}

int main(void){

/*
    char s[] = {'a', 'b', ',', '.', '0'};
    for(int i = 0; i < sizeof(s); i++){
        printf("islower('%c') = %s\n", s[i], boolToStr(islower(s[i])));
    }
    */
    srand(time(NULL));
    run_test(testPlayerInit);
    run_test(testPlayerPoints);
    run_test(testRollete);
    run_test(testPuzzle);
    return 0;
}