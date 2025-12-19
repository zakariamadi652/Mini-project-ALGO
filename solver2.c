#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "wordle.h"

void filter_words(int *candidates, int *count, const char *guess, const char *feedback) {
    int new_list[MAX_WORDS];
    int new_count = 0;

    for (int i = 0; i < *count; i++) {
        const char *word = dictionary[candidates[i]];
        char fb[WORD_LENGTH + 1];
        generate_feedback(guess, word, fb);

        if (strcmp(fb, feedback) == 0) {
            new_list[new_count++] = candidates[i];
        }
    }

    memcpy(candidates, new_list, new_count * sizeof(int));
    *count = new_count;
}

const char* pick_unique_word(int *candidates, int count) {
    if (count == 0)
        return NULL;

    int best_idx = candidates[0];
    int best_unique = 0;

    for (int i = 0; i < count; i++) {
        const char *word = dictionary[candidates[i]];
        int seen[26] = {0};
        int unique = 0;

        for (int j = 0; j < WORD_LENGTH; j++) {
            char ch = tolower(word[j]);
            if (ch >= 'a' && ch <= 'z') {
                int c = ch - 'a';
                if (!seen[c]) {
                    seen[c] = 1;
                    unique++;
                }
            }
        }

        if (unique > best_unique) {
            best_unique = unique;
            best_idx = candidates[i];
        }
    }

    return dictionary[best_idx];
}

void run_unique_solver() {
    int candidates[MAX_WORDS];
    int count = word_count;

    for (int i = 0; i < word_count; i++)
        candidates[i] = i;

    char target[WORD_LENGTH + 1];
    printf("Enter secret word: ");
    scanf("%5s", target);
    for (int i = 0; i < WORD_LENGTH; i++)
        target[i] = tolower(target[i]);

    char guess[WORD_LENGTH + 1];
    char feedback[WORD_LENGTH + 1];

    printf("\n=== UNIQUE-LETTER SOLVER ===\n");

    for (int attempt = 1; attempt <= MAX_ATTEMPTS; attempt++) {
        const char *g = pick_unique_word(candidates, count);
        if (g == NULL) {
            printf("No candidates left. Solver failed.\n");
            return;
        }

        strcpy(guess, g);
        printf("\nAttempt %d: %s\n", attempt, guess);

        generate_feedback(guess, target, feedback);
        print_colored_feedback(guess, feedback);

        if (strcmp(guess, target) == 0) {
            printf("Solver found the word!\n");
            return;
        }

        filter_words(candidates, &count, guess, feedback);
        printf("Remaining candidates: %d\n", count);
    }

    printf("Solver failed.\n");
}

void auto_solve2() {
    run_unique_solver();
}
