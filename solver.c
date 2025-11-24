#include <stdio.h>
#include <string.h>
#include "wordle.h"

char dictionary[MAX_WORDS][WORD_LENGTH + 1];
int word_count;
int match_feedback(const char *word, const char *guess, const char *feedback) {
    char fb[WORD_LENGTH + 1];
    generate_feedback(guess, word, fb);
    return strcmp(fb, feedback) == 0;
}
void filter_candidates(int *candidates, int *count, const char *guess, const char *feedback) {
    int new_list[MAX_WORDS];
    int new_count = 0;
    for (int i = 0; i < *count; i++) {
        int idx = candidates[i];
        const char *word = dictionary[idx];

        if (match_feedback(word, guess, feedback)) {
            new_list[new_count++] = idx;
        }
    }

    for (int i = 0; i < new_count; i++) {
        candidates[i] = new_list[i];
    }
    *count = new_count;
}
void run_solver() {
    int candidates[MAX_WORDS];
    int count = word_count;

    for (int i = 0; i < word_count; i++) {
        candidates[i] = i;
    }
    char guess[WORD_LENGTH + 1];
    char feedback[WORD_LENGTH + 1];
    char target[WORD_LENGTH + 1];
    printf("Enter the secret word (for testing): ");
    scanf("%5s", target);
    int attempts = 0;
    while (attempts < MAX_ATTEMPTS && count > 0) {
        strcpy(guess, dictionary[candidates[0]]);
        printf("\nAttempt %d: %s\n", attempts + 1, guess);
        generate_feedback(guess, target, feedback);
        print_colored_feedback(guess, feedback);

        if (strcmp(guess, target) == 0) {
            printf("\nSolver found the word in %d attempts!\n", attempts + 1);
            return;
        }

        filter_candidates(candidates, &count, guess, feedback);
        attempts++;
    }

    printf("\nSolver failed. Remaining candidates: %d\n", count);
}

void auto_solve() {
    run_solver();
}
