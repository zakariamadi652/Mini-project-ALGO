#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define WORD_LENGTH 5
#define MAX_WORDS 2315
void load_all_words(char words[][WORD_LENGTH + 1], int *word_count) {
    FILE *file = fopen("data.txt", "r");
    if (file == NULL) {
        printf("rror opening data.txt!\n");
        *word_count = 0;
        return;
    }
    
    *word_count = 0;
    char word[WORD_LENGTH + 2];
    
    while (fscanf(file, "%5s", word) == 1 && *word_count < MAX_WORDS) {
        strcpy(words[*word_count], word);
        (*word_count)++;
    }
    
    fclose(file);
    printf("data.txt is loaded: %d words\n", *word_count);
}
