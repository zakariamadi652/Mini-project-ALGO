#ifndef WORDLE_H
#define WORDLE_H
#include <stdio.h>
#define WORD_LENGTH 5
#define MAX_ATTEMPTS 6
#define MAX_WORDS 3000  
//
extern char dictionary[MAX_WORDS][WORD_LENGTH + 1];
extern int word_count;

// Load dictionary from file into global dictionary array
int load_words(const char *filename);

// Choose a random secret word from dictionary
void select_random_word(char target[]);

// Check if a guessed word exists in the dictionary
int is_valid_word(const char *guess);

// 'G' = green (correct position)
// 'Y' = yellow (wrong position but exists)
// '_' = gray (not in word)
void generate_feedback(const char *guess, const char *target, char *feedback);

// Print feedback with ANSI colors (optional but recommended)
void print_colored_feedback(const char *guess, const char *feedback);

// Run the game normally (user guesses)
void play_wordle();

// Automatically solve Wordle using dictionary and feedback
void auto_solve();

// Check if a candidate word matches feedback from a guess
int match_feedback(const char *word, const char *guess, const char *feedback);

// Filter the list of candidates based on feedback information
void filter_candidates(int *candidates, int *count, const char *guess, const char *feedback);

// Main solver function using an elimination strategy
void run_solver();

#endif
