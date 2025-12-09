#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "wordle.h"

int match_feedback(const char *word, const char *guess, const char *fb_expected) {
    char fb[WORD_LENGTH + 1];
    generate_feedback(guess, word, fb);
    return strcmp(fb, fb_expected) == 0;
}

void filter_candidates(int *candidates, int *count,
                       const char *guess, const char *feedback) {

    int new_list[MAX_WORDS];
    int new_count = 0;

    for (int i = 0; i < *count; i++) {
        const char *w = dictionary[candidates[i]];
        if (match_feedback(w, guess, feedback)) {
            new_list[new_count++] = candidates[i];
        }
    }

    memcpy(candidates, new_list, new_count * sizeof(int));
    *count = new_count;
}

const char* select_next_guess(int *candidates, int count) {
    int freq[26] = {0};

    for (int i = 0; i < count; i++) {
        const char *w = dictionary[candidates[i]];
        for (int j = 0; j < WORD_LENGTH; j++)
            freq[w[j] - 'a']++;
    }

    int best = candidates[0];
    int best_score = -1;

    for (int i = 0; i < count; i++) {
        const char *w = dictionary[candidates[i]];
        int score = 0;
        int used[26] = {0};

        for (int j = 0; j < WORD_LENGTH; j++) {
            int c = w[j] - 'a';
            if (!used[c]) {
                used[c] = 1;
                score += freq[c];
            }
        }

        if (score > best_score) {
            best_score = score;
            best = candidates[i];
        }
    }

    return dictionary[best];
}

void run_solver() {
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

    for (int attempt = 1; attempt <= MAX_ATTEMPTS; attempt++) {
        const char *g = select_next_guess(candidates, count);
        strcpy(guess, g);

        printf("\nAttempt %d: %s\n", attempt, guess);

        generate_feedback(guess, target, feedback);
        print_colored_feedback(guess, feedback);

        if (strcmp(guess, target) == 0) {
            printf("Solver found the word!\n");
            return;
        }

        filter_candidates(candidates, &count, guess, feedback);
        printf("Remaining candidates: %d\n", count);
    }

    printf("Solver failed.\n");
}

void auto_solve() {
    run_solver();
}
