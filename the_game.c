#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include <ctype.h>

#define MAX_WORDS 2130
#define WORD_LENGTH 5
#define MAX_TRIES 6
   int word_count = 0;
   char dictionary[MAX_WORDS][WORD_LENGTH + 1];
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

/* ------------------------------------------
    GENERATE FEEDBACK (GREEN/YELLOW/GRAY)
------------------------------------------- */
void generate_feedback(const char *guess, const char *word, char *fb) {
    int used[WORD_LENGTH] = {0};

    // GREEN PASS
    for (int i = 0; i < WORD_LENGTH; i++) {
        if (guess[i] == word[i]) {
            fb[i] = 'G';
            used[i] = 1;
        } else {
            fb[i] = '_';
        }
    }

    // YELLOW PASS
    for (int i = 0; i < WORD_LENGTH; i++) {
        if (fb[i] == 'G') continue;

        int found = 0;
        for (int j = 0; j < WORD_LENGTH; j++) {
            if (!used[j] && guess[i] == word[j]) {
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

int check_the_word(char word_from_the_user[]) {
    FILE *words = fopen("data.txt", "r");
    if (!words) return 0;

    char buffer[WORD_LENGTH+1];
    while (fscanf(words,"%5s", buffer) == 1) {
        if (strcmp(buffer, word_from_the_user) == 0) {
            fclose(words);
            return 1;
        }
    }
    fclose(words);
    return 0;
}

void select_random_word(char random_word[]){
    FILE *words = fopen("data.txt", "r");
    if (!words) return;

    int total_words = 2315;
    int random_line_number = rand() % total_words;

    for(int i = 0; i <= random_line_number; i++){
        fscanf(words,"%5s", random_word);
    }
    fclose(words);
}

void display_colored_guess(char random_word[], char guess[]){
    int used[WORD_LENGTH] = {0};
    for(int i=0;i<WORD_LENGTH;i++){
        if(guess[i]==random_word[i]){
            printf("\033[1;32m%c\033[0m ", guess[i]);
            used[i] = 1;
        } else {
            int found = 0;
            for(int j=0;j<WORD_LENGTH;j++){
                if(!used[j] && guess[i]==random_word[j]){
                    found = 1;
                    used[j] = 1;
                    break;
                }
            }
            if(found){
                printf("\033[1;33m%c\033[0m ", guess[i]);
            } else {
                printf("\033[1;90m%c\033[0m ", guess[i]);
            }
        }
    }
    printf("\n");
}

int play_wordle(void) {
    char random_word[WORD_LENGTH+1];
    char guess[WORD_LENGTH+1];
    char previous_guesses[MAX_TRIES][WORD_LENGTH+1];
    int tries = 0;
    int word_found = 0;

    srand(time(NULL));
    select_random_word(random_word);

    printf("Welcome to Wordle!\n");
    printf("You have %d tries to guess the %d-letter word.\n", MAX_TRIES, WORD_LENGTH);
    printf("Green = correct letter & position, Yellow = correct letter wrong position, Grey = letter not in word\n\n");

    while(tries < MAX_TRIES && !word_found){
        printf("Try %d/%d - Enter your guess: ", tries+1, MAX_TRIES);
        scanf("%5s", guess);

        for(int i=0;i<WORD_LENGTH;i++)
            guess[i] = tolower(guess[i]);

        if(!check_the_word(guess)){
            printf("Word not in dictionary. Try again.\n\n");
            continue;
        }

        strcpy(previous_guesses[tries], guess);
        for(int t=0;t<=tries;t++)
            display_colored_guess(random_word, previous_guesses[t]);

        if(strcmp(random_word, guess)==0){
            printf("\n🎉 Congratulations! You found the word!\n");
            word_found = 1;
            break;
        }

        tries++;
        printf("\n");
    }

    if(!word_found){
        printf("❌ You lost! The word was: %s\n", random_word);
    }

    return 0;
}
