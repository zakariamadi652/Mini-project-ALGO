#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define WORD_LENGTH 5
#define MAX_ATTEMPTS 6
#define DICTIONARY_SIZE 1000
char dictionary[DICTIONARY_SIZE][WORD_LENGTH + 1];
int word_count = 0;

//   Charger le dictionnaire
void load_dictionary(const char *filename) {
    FILE *file = fopen(filename, "r");  // Ouvre le fichier contenant les mots
    if (!file) {
        perror("Failed to open dictionary file");
        exit(EXIT_FAILURE);
    }

    // Lire chaque mot ligne par ligne
    while (fgets(dictionary[word_count], sizeof(dictionary[word_count]), file)) {

        // Retirer le '\n' à la fin du mot si présent
        dictionary[word_count][strcspn(dictionary[word_count], "\n")] = 0;

        // Passer au mot suivant
        word_count++;
    }

    fclose(file);
}
//   Choisir un mot au hasard
char* select_random_word() {
    srand(time(NULL));  // intialise l'aleatoire
    return dictionary[rand() % word_count];  // retourne un mot au hasard
}

void provide_feedback(const char *guess, const char *target) {
    char feedback[WORD_LENGTH + 1] = {0}; // contien les couleurs G/Y/X

    for (int i = 0; i < WORD_LENGTH; i++) {

        if (guess[i] == target[i]) {
            // Bonne lettre et bonne position
            feedback[i] = 'G';

        } else if (strchr(target, guess[i])) {
            // lettre persente mais pas  la bonne place
            feedback[i] = 'Y';

        } else {
            // lettre absente du mot
            feedback[i] = 'X';
        }
    }

    printf("Feedback: %s\n", feedback);
}

//   verifier si le mot proposé existe
int is_valid_guess(const char *guess) {

    for (int i = 0; i < word_count; i++) {

        if (strcmp(guess, dictionary[i]) == 0) {
            return 1; 
        }
    }

    return 0;  
}




void play_wordle() {
    char *target_word = select_random_word();  // Choisir le mot secret
    char guess[WORD_LENGTH + 1];
    int attempts = 0;

    printf("Welcome to Wordle! You have %d attempts to guess the word.\n", MAX_ATTEMPTS);

   
    while (attempts < MAX_ATTEMPTS) {

        printf("Enter your guess: ");
        scanf("%s", guess);

       
        if (!is_valid_guess(guess)) {
            printf("Invalid guess. Please enter a valid 5-letter word.\n");
            continue;
        }

        // Donner un feedback G/Y/X
        provide_feedback(guess, target_word);

        attempts++;

        // Vérifier si le mot est correct
        if (strcmp(guess, target_word) == 0) {
            printf("Congratulations! You've guessed the word!\n");
            return; // Fin du jeu
        }
    }

  
    printf("Sorry, you've used all attempts. The word was: %s\n", target_word);
}



//   Programme principal
int main() {
    load_dictionary("words.txt");  
    play_wordle();                  
    return 0;
}
