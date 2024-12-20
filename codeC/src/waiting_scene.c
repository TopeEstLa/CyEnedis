#include <waiting_scene.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void slowPrint(char *words, int speed) {
    while (*words) {
        putchar(*words);
        fflush(stdout);
        usleep(speed);
        words++;
    }
    putchar('\n');
}

void init_waiting_scene() {
    //if we use ncurses lol
}

void *draw_waiting_scene(void *varg) {
    int value = 1;
    int progress_state = 0;
    while (1) {
        if (value) {
            printf("   _____      ______                _ _     \n"
                   "  / ____|    |  ____|              | (_)    \n"
                   " | |    _   _| |__   _ __   ___  __| |_ ___          O     \n"
                   " | |   | | | |  __| | '_ \\ / _ \\/ _` | / __|        /|\\    \n"
                   " | |___| |_| | |____| | | |  __/ (_| | \\__ \\        / \\    \n"
                   "  \\_____\\__, |______|_| |_|\\___|\\__,_|_|___/      _/   \\_\n"
                   "         __/ |                              \n"
                   "        |___/     ");
            value = 0;
        } else {
            printf("   _____      ______                _ _     \n"
                   "  / ____|    |  ____|              | (_)    \n"
                   " | |    _   _| |__   _ __   ___  __| |_ ___        \\ O /   \n"
                   " | |   | | | |  __| | '_ \\ / _ \\/ _` | / __|         |    \n"
                   " | |___| |_| | |____| | | |  __/ (_| | \\__ \\        / \\    \n"
                   "  \\_____\\__, |______|_| |_|\\___|\\__,_|_|___/      _/   \\_\n"
                   "         __/ |                              \n"
                   "        |___/                 \n");
        }

        printf("\n");
        printf("                     Loading please wait...             \n");


        printf("               ");
        for (int i = 0; i < progress_state; i++) {
            printf("═");
        }
        printf("▰▰");
        for (int i = progress_state + 1; i < 30; i++) {
            printf("═");
        }
        printf("                 ");
        printf("\n");


        progress_state++;
        if (progress_state >= 30) {
            progress_state = 0;
        }

        usleep(300000);

        printf("\033[2J\033[H");
    }
}