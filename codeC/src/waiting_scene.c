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
    int value = 1;
    while (1) {
        printf("  _____                                _  _\n"
               " / ____|                              | |(_)\n"
               "| |      _   _   ___  _ __    ___   __| | _  ___\n"
               "| |     | | | | / _ \\| '_ \\  / _ \\ / _` || |/ __|\n"
               "| |____ | |_| ||  __/| | | ||  __/| (_| || |\\__ \\\n"
               " \\_____| \\__, | \\___||_| |_| \\___| \\__,_||_||___/\n"
               "          __/ |\n"
               "         |___/\n");


        if (value) {
            printf("     O     \n"
                   "    /|\\    \n"
                   "    / \\    \n"
                   "  _/   \\_                                ");
            value = 0;
        } else {
            printf("   \\ O /   \n"
                   "     |    \n"
                   "    / \\    \n"
                   "  _/   \\_                                 ");
            value = 1;
        }

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