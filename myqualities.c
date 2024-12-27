#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//define max length
#define MAX_LENGTH 1024
//define sentence and quality length
#define SENTENCE_LENGTH 200
#define QUALITY_LENGTH 100


void ReadInQualities(char qualities[]) {
//define a sentence array that will be used to read in sentences
    char sentence[SENTENCE_LENGTH] = ""; 
//define a variable to keep track of what quality we're on
    int qualityCount = 1;
//define quality to be extracted from sentence
    char quality[QUALITY_LENGTH];
    //open the file MyQualities.txt for writing and check if it was opened
    FILE *myqualities = fopen("MyQualities.txt", "w");

    if (myqualities == NULL) {
        printf("Error: Failed to open file.\n");
        exit(EXIT_FAILURE);
    }

    printf("    Please enter sentences, . to end.\n");

//loop to keep getting qualities until a . is entered
    while(fgets(sentence, sizeof(sentence),stdin) != NULL) {
//check if a . was entered
        if (strcmp(sentence, ".\n") == 0) {
            break;
        }
//check if the sentence starts with I am
        char *iAm = strstr(sentence, "I am ");
        if (iAm != NULL) {
            iAm = sentence + 5;
//copy the quality from the sentence into quality
            strncpy(quality, iAm, sizeof(quality) - 1);

//remove new line from the quality if it exists
            if(quality[strlen(quality)-1] == '\n') {
                quality[strlen(quality)-1] = '\0';
            }

//add the quality to qualites, use quality count to make sure last quality doesn't end with a comma
            if(qualityCount == 1) {
                strncat(qualities, quality, MAX_LENGTH - strlen(qualities) - 1);
                qualityCount++;
            } else {
                strncat(qualities, ", ", MAX_LENGTH - strlen(qualities) - 1);
                strncat(qualities, quality, MAX_LENGTH - strlen(qualities) - 1);
            }

//write the new quality to the file
            fprintf(myqualities, "%s\n", quality);
        }
    }

//Close the myqualities file and make sure its successfully closed
    if (fclose(myqualities) != 0) {
        printf("Error: unable to close the file.\n");
        exit(EXIT_FAILURE);
    }

//add a . to the end of the qualities array
    strncat(qualities, ".", MAX_LENGTH - strlen(qualities) - 1);
}

void PrintQualities(char qualities[]) {

//create sentence variable to hold each quality

char sentence[SENTENCE_LENGTH];

//print qualities array
    printf("The qualities are %s\n", qualities);

//reopen the file to confirm saved qualities
    FILE *myqualities = fopen("MyQualities.txt", "r");

    if (myqualities == NULL) {
        printf("Error: Failed to open file.\n");
        exit(EXIT_FAILURE);
    }

    printf("\nConfirming the saved qualities ...\n");

//loop to get all of the saved qualities
    while(fgets(sentence, sizeof(sentence), myqualities)) {
        printf("%s", sentence);
    }

//check and close file
    if (fclose(myqualities) != 0) {
        printf("Error: unable to close the file.\n");
        exit(EXIT_FAILURE);
    }
}

//main
int main(void) {

//define empty qualities array
    char qualities[MAX_LENGTH] = "";

//call ReadInQualities
    ReadInQualities(qualities);

//call PrintQualities
    PrintQualities(qualities);

//delete the file
    remove("MyQualities.txt");

    return(EXIT_SUCCESS);
    
}



