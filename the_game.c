#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void check_the_word(char random_word[],FILE *words,char word_from_the_user[])
{
        char word[6];
        words = fopen("data.txt", "r");
        if (words == NULL) {
        printf("Error opening file!\n");
        return;
    }
    
}
void select_random_word(char random_word[]){//this function return a random word from a file called data
        FILE *words = fopen("data.txt", "r");
        if (words == NULL) {
        printf("Error opening file!\n");
        return;
    }
        int random_line_number=rand() % 2315;

    for( int i=0;i<random_line_number;i++)
    {
         fscanf(words,"%5s",random_word);
    }
    
fclose(words);
}
void comparing_letter_by_letter(char random_word[],char word_from_the_user[]){

        
        for(int i=0;i<5;i++)
        {
                int found=0;
                for(int j=0;j<5;j++){
                        if(word_from_the_user[i]==random_word[j]){
                        found=1;
                        if(i==j){
                                printf("the letter number %d '%c' exesist in the right possition\n",i,word_from_the_user[i]);
                        }else{
                                printf("the letter %d '%c' exesist but in the wrong possition\n",i,word_from_the_user[i]);
                        }
                       }
                      }
               if(found==0){
                printf("the letter %d %c does't exist in the word chosen\n",i,word_from_the_user[i]);
              }
             }
            }

void play_wordle() { // what i modified 
    char random_word[6];
    char word_from_the_user[6];
    srand(time(NULL));  
    printf("Enter a 5 letter word:\n");
    scanf("%5s", word_from_the_user);  
    select_random_word(random_word);
    printf("The random word is: %s\n", random_word);
    comparing_letter_by_letter(random_word, word_from_the_user);
}
