#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "wordle.h"

char dictionary[MAX_WORDS][WORD_LENGTH + 1];
int word_count = 0;

int load_words(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) return 0;

    while (fscanf(f, "%5s", dictionary[word_count]) == 1) {
        for (int i = 0; i < WORD_LENGTH; i++)
            dictionary[word_count][i] = tolower(dictionary[word_count][i]);

        dictionary[word_count][WORD_LENGTH] = '\0';
        word_count++;

        if (word_count >= MAX_WORDS)
            break;
    }

    fclose(f);
    return 1;
}

int check_the_word(const char *guess) {
    for (int i = 0; i < word_count; i++) {
        if (strcmp(dictionary[i], guess) == 0)
            return 1;
    }
    return 0;
}

void select_random_word(char target[]) {
    int r = rand() % word_count;
    strcpy(target, dictionary[r]);
}

void check_the_guess(const char *guess, const char *target, char *fb) {
    int used[WORD_LENGTH] = {0};

    for (int i = 0; i < WORD_LENGTH; i++) {
        if (guess[i] == target[i]) {
            fb[i] = 'G';
            used[i] = 1;
        } else fb[i] = '_';
    }

    for (int i = 0; i < WORD_LENGTH; i++) {
        if (fb[i] == 'G') continue;

        int found = 0;
        for (int j = 0; j < WORD_LENGTH; j++) {
            if (!used[j] && guess[i] == target[j]) {
                used[j] = 1;
                found = 1;
                break;
            }
        }
        fb[i] = found ? 'Y' : 'B';
    }

    fb[WORD_LENGTH] = '\0';
}

void print_colored_feedback(const char *guess, const char *fb) {
    for (int i = 0; i < WORD_LENGTH; i++) {
        if (fb[i] == 'G')
            printf("\033[1;32m%c\033[0m ", guess[i]);
        else if (fb[i] == 'Y')
            printf("\033[1;33m%c\033[0m ", guess[i]);
        else
            printf("\033[1;90m%c\033[0m ", guess[i]);
    }
    printf("\n");
}

int play_wordle(void) {
    char target[WORD_LENGTH + 1];
    char guess[WORD_LENGTH + 1];
    char fb[WORD_LENGTH + 1];

    srand(time(NULL));
    select_random_word(target);

    printf("Welcome to Wordle!\n");

    for (int attempt = 1; attempt <= MAX_ATTEMPTS; attempt++) {
        printf("Attempt %d/%d: ", attempt, MAX_ATTEMPTS);
        scanf("%5s", guess);

        for (int i = 0; i < WORD_LENGTH; i++)
            guess[i] = tolower(guess[i]);

        if (!check_the_word(guess)) {
            printf("Not a valid word.\n");
            attempt--;
            continue;
        }

        check_the_guess(guess, target, fb);
        print_colored_feedback(guess, fb);

        if (strcmp(guess, target) == 0) {
            printf("Correct!\n");
            return 1;
        }
    }

    printf("You lost Word was %s\n", target);
    return 0;
}
