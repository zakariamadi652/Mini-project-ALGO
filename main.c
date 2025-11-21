#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
    int choice;
    
    printf("=== WORDLE GAME ===\n");
    printf("1.  play Wordle\n");
    printf("2. start solver\n");
    printf("3. exit\n");
    printf("Choix: ");
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
            printf("invalid choice\n");
    }
    
    return 0;
}
