#include <waiting_scene.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void slowPrint(char* words,int speed){
    while(*words){
        putchar(*words);
        fflush(stdout);
        usleep(speed);
        words++;
    }
    putchar('\n');
}

void init_waiting_scene(){
    //if we use ncurses lol
}

void* draw_waiting_scene(void* varg) {
    while (1) {
        int random = rand() % 4;
        switch (random) {
            case 0:
                printf("Loading");
                slowPrint(" ....", 300000);
                break;
            case 1:
                printf("Data processing in progress");
                slowPrint(" ....", 300000);
                break;
            case 2:
                printf("Please wait");
                slowPrint(" ....", 300000);
                break;
            case 3:
                printf("It's almost over (or not :=))");
                slowPrint(" ....", 300000);
                break;
        }

        printf("\033[2J\033[H");
    }
}