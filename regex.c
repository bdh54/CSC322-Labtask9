#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

//define max string length 
#define MAX_LENGTH 1024

void RegularExpressionTest(char string[], char regEx[]) {
//Make sure regular expression can compile
    regex_t expression;
    if(regcomp(&expression, regEx, REG_EXTENDED) != 0) {
        printf("Error, failed to compile regular expression.\n");
        exit(EXIT_FAILURE);
    }

//create a sentence array and a save ptr for strtok_r so we can extract sentences and know where the next one begins
    char *sentence, *savePtr;

//initialize the first sentence in the string
    sentence = strtok_r(string, ".!?", &savePtr);

//loop to get all the sentences and run regex on them
    while(sentence != NULL) {
//skip the leading whitespace
        sentence += strspn(sentence, " \t");
        printf("%s\n", sentence);

//check if regex is in the sentence, if it is print Yes
        if(regexec(&expression,sentence, 0, NULL, 0) == 0) {
            printf("Yes");
        } else {
            printf("No");
        }
//create same pointers we made for sentence, but now for words to count them
        char *word, *wordPtr;
//create a word count var
        int count = 0;

        word = strtok_r(sentence, " ", &wordPtr);
 //while loop to count the words
        while(word != NULL) {
            count++;
            word = strtok_r(NULL, " ", &wordPtr);
        }   

//print the word count
        printf("%4d words\n", count);
//get the next sentence
        sentence = strtok_r(NULL, ".!?", &savePtr);
    }

//Free the expression
    regfree(&expression);

}

int main(void) {

//define the regular expression and the string
    char string[MAX_LENGTH] = "";
    char regEx[MAX_LENGTH] = "";

//get the input string and the regular expression from the user 
    printf("Please enter the string to analyse\n");
    fgets(string, sizeof(string), stdin);
    printf("Please enter the regular expression : ");
    fgets(regEx, sizeof(regEx), stdin);

//delete the newline character from string

    string[strlen(string) - 1] = '\0';

//delete the newline character from the regEx
    regEx[strlen(regEx) - 1] = '\0';    

//Run regular expression method to see what sentences it matches to
    RegularExpressionTest(string, regEx);

    return(EXIT_SUCCESS);
}