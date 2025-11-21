#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define WORD_LENGTH 5
#define MAX_ATTEMPTS 6
#define DICTIONARY_SIZE 2500

char dictionary[DICTIONARY_SIZE][WORD_LENGTH + 1];
int word_count = 0;

void load_dictionary(const char *file_name) {
    FILE *file = fopen(data, "r");
    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier %s\n", data);
        exit(1);
    }
    while (fgets(dictionary[word_count], 20, file)) { 
        
        int len = strlen(dictionary[word_count]);
        if (len > 0 && dictionary[word_count][len -1] == '\n') {
            dictionary[word_count][len -1] = '\0';
        }
        word_count++;
        if (word_count >= DICTIONARY_SIZE) break; 
    }
    fclose(file);
}

char* pick_random_word() {
    srand(time(NULL)); 
    int r = rand() % word_count;
    return dictionary[r];
}

int is_valid_word(const char *w) {
    for (int i=0; i<word_count; i++) {
        if (strcmp(w, dictionary[i]) == 0) return 1;
    }
    return 0;
}

void give_feedback(const char *guess, const char *secret) {
    char fb[WORD_LENGTH+1];
    for (int i=0; i<WORD_LENGTH; i++) {
        if (guess[i] == secret[i]) fb[i] = 'G';
        else if (strchr(secret, guess[i]) != NULL) fb[i] = 'Y';
        else fb[i] = 'X';
    }
    fb[WORD_LENGTH] = '\0';
    printf("Resultat: %s\n", fb);
}

void play_wordle() {
    char *secret = pick_random_word();
    char guess[WORD_LENGTH+1];
    int tries = 0;

    printf("Devine le mot en %d essais !\n", MAX_ATTEMPTS);

    while (tries < MAX_ATTEMPTS) {
        printf("Ton mot: ");
        scanf("%s", guess);

        if (strlen(guess) != WORD_LENGTH) {
            printf("Pas le bon nombre de lettres !\n");
            continue;
        }
        if (!is_valid_word(guess)) {
            printf("Ce mot n'est pas dans la liste.\n");
            continue;
        }

        give_feedback(guess, secret);
        tries++;

        if (strcmp(guess, secret) == 0) {
            printf("Tu as gagneé !!\n");
            return;
        }
    }

    printf("Perdu :( Le mot etait: %s\n", secret);
}

int main() {
    load_dictionary("words.txt");
    play_wordle();
    return 0;
}
