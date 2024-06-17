#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#define MAX_STACK_SIZE 6040
#define MAX_LINES 1000
#define FILE_PATH "/home/output.txt"

void helper_delete(){

FILE *file = fopen(FILE_PATH, "r");
 if (file == NULL) {
        perror("Error opening file for reading");
        exit(EXIT_FAILURE);
    }



char lines[MAX_LINES][MAX_STACK_SIZE];
size_t lineCount = 0;
 
    while (fgets(lines[lineCount], sizeof(lines[lineCount]), file) != NULL) {
    if (++lineCount >= MAX_LINES) 
    {
        fprintf(stderr, "Exceeded maximum number of lines (%d)\n", MAX_LINES);
        fclose(file);
         return;
        }
    }
    fclose(file);



    if (lineCount == 0) {
        fprintf(stderr, "The file is empty try to use jp_push.\n");
        return;
    }
    int highestInteger = -1;
    size_t highestIndex = 0;
    int foundInteger = 0;



    for (size_t i = 0; i < lineCount; i++) {
        int currentInteger;
        if (sscanf(lines[i], "%d", &currentInteger) == 1) {
           // printf("Parsed integer %d from line %zu: %s", currentInteger, i, lines[i]);
            if (!foundInteger || currentInteger > highestInteger) {
                highestInteger = currentInteger;
                highestIndex = i;
                foundInteger = 1;
            }
        } 
        
        
        else 
        {
           // printf("No integer found in line %zu: %s", i, lines[i]);
        }
    }

    if (!foundInteger) {
        fprintf(stderr, "No integers found in the file.\n");
        return;
    }
    file = fopen(FILE_PATH, "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }
    for (size_t i = 0; i < lineCount; i++) {
        if (i != highestIndex) {
            fputs(lines[i], file);
    }
    }




    fclose(file);

   // printf("Deleted the line with the highest integer: %d\n", highestInteger);


}


int main(){

helper_delete();


}
