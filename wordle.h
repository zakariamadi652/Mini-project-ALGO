#ifndef WORDLE_H
#define WORDLE_H

#include <stdio.h>

#define WORD_LENGTH 5
#define MAX_ATTEMPTS 6
#define MAX_WORDS 3000

extern char dictionary[MAX_WORDS][WORD_LENGTH + 1];
extern int word_count;

int load_words(const char *filename);

void select_random_word(char target[]);
int is_valid_word(const char *guess);

void generate_feedback(const char *guess, const char *target, char *feedback);
void print_colored_feedback(const char *guess, const char *feedback);

int play_wordle(void);

int match_feedback(const char *word, const char *guess, const char *feedback);
void filter_candidates(int *candidates, int *count,
                       const char *guess, const char *feedback);
void auto_solve(void);
void run_solver(void);

#endif

