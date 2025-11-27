#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "wordle.h"

int main() {
    int choice;
    if (!load_words("data.txt")) {
        printf("error could not load dictionary file 'data.txt'\n");
        return 1;
    }
    srand(time(NULL));
    printf("=== WORDLE GAME ===\n");
    printf("1. Play Wordle\n");
    printf("2. Start solver\n");
    printf("3. Exit\n");
    printf("Choice: ");
    scanf("%d", &choice);
    switch(choice) {
        case 1:
            play_wordle();  
            break;
        case 2:
            auto_solve();   
            break;
        case 3:
            printf("Goodbye!!\n");
            break;
        default:
            printf("invalide choice\n");
    }
    return 0;
}
