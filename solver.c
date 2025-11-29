#include <stdio.h>
#include <string.h>
#include "wordle.h"

int match_feedback(const char *word, const char *guess, const char *feedback) {
    char fb[WORD_LENGTH + 1];
    generate_feedback(guess, word, fb);
    return strcmp(fb, feedback) == 0;
}
void filter_candidates(int *candidates, int *count, const char *guess, const char *feedback) {
    int new_list[MAX_WORDS];
    int new_count = 0;

    for (int i = 0; i < *count; i++) {
        const char *candidate_word = dictionary[candidates[i]];

        if (match_feedback(candidate_word, guess, feedback)) {
            new_list[new_count++] = candidates[i];
        }
    }

    for (int i = 0; i < new_count; i++)
        candidates[i] = new_list[i];

    *count = new_count;
}

const char* select_next_guess(int *candidates, int count) {
    int freq[26] = {0};
    for (int i = 0; i < count; i++) {
        const char *w = dictionary[candidates[i]];
        for (int j = 0; j < WORD_LENGTH; j++) {
            freq[w[j] - 'a']++;
        }
    }

    int best_index = candidates[0];
    int best_score = -1;
    for (int i = 0; i < count; i++) {
        const char *w = dictionary[candidates[i]];
        int score = 0;
        int used[26] = {0};
        for (int j = 0; j < WORD_LENGTH; j++) {
            char c = w[j];
            if (!used[c - 'a']) {
                used[c - 'a'] = 1;
                score += freq[c - 'a'];
            }
        }

        if (score > best_score) {
            best_score = score;
            best_index = candidates[i];
        }
    }

    return dictionary[best_index];
}

void run_solver() {
    int candidates[MAX_WORDS];
    int count = word_count;

    for (int i = 0; i < word_count; i++)
        candidates[i] = i;

    char target[WORD_LENGTH + 1];
    char guess[WORD_LENGTH + 1];
    char feedback[WORD_LENGTH + 1];

    printf("Enter the secret word (for solver testing): ");
    scanf("%5s", target);

    printf("\nSolver starting...\n");

    for (int attempt = 1; attempt <= MAX_ATTEMPTS; attempt++) {

        strcpy(guess, select_next_guess(candidates, count));

        printf("\nAttempt %d: %s\n", attempt, guess);

        generate_feedback(guess, target, feedback);
        print_colored_feedback(guess, feedback);

        if (strcmp(guess, target) == 0) {
            printf("\n🎉 Solver found the word in %d attempts!\n", attempt);
            return;
        }

        filter_candidates(candidates, &count, guess, feedback);
        printf("Remaining candidates: %d\n", count);
    }

    printf("\n Solver failed within %d attempts\n", MAX_ATTEMPTS);
}

void auto_solve() {
    run_solver();
}
