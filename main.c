#include <stdio.h>
#include "wordle.h"

int main() {
    if (!load_words("data.txt")) {
        printf("Error loading dictionary.\n");
        return 1;
    }
    
    int option;
    printf("=== Wordle Solver Menu ===\n");
    printf("1. Play Wordle\n");
    printf("2. Auto-solver\n");
    printf("3. auto solver 2\n");
    printf(">");
    scanf("%d", &option);
    if (option == 1) play_wordle();
    else if (option == 2) auto_solve();
    else if(option==3) auto_solve2();
    
    return 0;
}
