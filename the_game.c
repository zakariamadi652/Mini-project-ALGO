#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int check_the_word(char random_word[],FILE *words,char word_from_the_user[])
{
        char word[6];
        words = fopen("data.txt", "r");
        if (words == NULL) {
        printf("Error opening file!\n");
        return;
    }
    while(strcmp(fgets(,fscanf(words,"%s",wordword_from_the_user)!=0)){
        if()
    }
}
void select_random_word(char random_word[],FILE *words){//this function return a random word from a file called data
        words = fopen("data.txt", "r");
        if (words == NULL) {
        printf("Error opening file!\n");
        return;
    }
        int random_line_number=rand() % 6;

    for( int i=0;i<random_line_number;i++)
    {
        fscanf(words,"%s",random_word);
    }
    
fclose(words);
}
void camparing_letter_by_letter(char random_word[],char word_from_the_user[]){
        int i,j;
        for(int i=1;i<7;i++)
        {
                for(int j=1;j<7;j++){
                        if(word_from_the_user[i]==random_word[j])//this check if the letters are the same 
                                                                //
                        {
                                printf("the letter number %d in the word that the user entered is the same as the word with number %d in the word from the dictionary\n",i,j);
                                if(i==j){
                                        printf("the two letter are the same in same spot\n");
                                }
                        }
                }
        }

}
int main(void){

        char random_word[6],word_from_the_user[6];
        FILE *words;        //this is the file that contain the 5 letters words
        srand(time(NULL));
        scanf("%s",word_from_the_user);
        select_random_word(random_word,words);
        printf("the random word is %s\n",random_word);
        camparing_letter_by_letter(random_word, word_from_the_user);

} 