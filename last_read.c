#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#define MAX_STACK_SIZE 6040
#define MAX_LINES 1000
#define FILE_PATH "/home/output.txt"
#define FILE_PATH_NEW "/home/output_1.txt"

volatile int g_var_ins = -1;

typedef struct Node {
    char* directory;
} node;

node* directory_array[MAX_STACK_SIZE];

void executeShellScript(const char *newDirectory , char* indexing) {
    char scriptContent[1024];

    if(strcmp(indexing,"jp_push")==0){
    snprintf(scriptContent, sizeof(scriptContent),
        "#!/bin/bash\n"
        "cd %s\n"
        "exec $SHELL\n", newDirectory);

    execl("/bin/bash", "bash", "-c", scriptContent, NULL);
    perror("execl");}

    else{

        
          snprintf(scriptContent, sizeof(scriptContent),
        "#!/bin/bash\n"
        "sudo pop_helper\n"
        "cd %s\n"
        "exec $SHELL\n", newDirectory);

    execl("/bin/bash", "bash", "-c", scriptContent, NULL);
    perror("execl");
    }

}

void update_g_var_ins() {
    FILE *file = fopen(FILE_PATH, "r");
    if (file == NULL) {
        perror("Error opening input file");
        g_var_ins = -1;
        return;
    }

    char line[MAX_STACK_SIZE];
    int maxInt = -1;

    while (fgets(line, sizeof(line), file) != NULL) {
        int number;
        char path[MAX_STACK_SIZE];
        if (sscanf(line, "%d %[^\n]", &number, path) == 2) {
            if (number > maxInt) {
            maxInt = number;
            }
    }
    }

    g_var_ins = maxInt;
    fclose(file);
}


/*
void deleteHighestIntegerLine(const char *filePath) {
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        perror("fopen for reading");
        exit(EXIT_FAILURE);
    }

    char **lines = NULL;
    size_t lineCount = 0;
    char buffer[MAX_STACK_SIZE];

   
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        lines = realloc(lines, sizeof(char*) * (lineCount + 1));
        if (lines == NULL) {
            perror("realloc");
            fclose(file);
            exit(EXIT_FAILURE);
        }
        lines[lineCount] = strdup(buffer);
        if (lines[lineCount] == NULL) {
            perror("strdup");
            for (size_t i = 0; i < lineCount; i++) {
                free(lines[i]);
            }
            free(lines);
            fclose(file);
            exit(EXIT_FAILURE);
    }
        lineCount++;
    }
    fclose(file);

    if (lineCount == 0) {
        fprintf(stderr, "The file is empty.\n");
        return;
    }

    int highestInteger = -1;
    size_t highestIndex = 0;
    int foundInteger = 0;

   
    for (size_t i = 0; i < lineCount; i++) {
        int currentInteger;
    if (sscanf(lines[i], "%d", &currentInteger) == 1) {
            printf("Parsed integer %d from line %zu: %s", currentInteger, i, lines[i]);
    if (!foundInteger || currentInteger > highestInteger) {
                highestInteger = currentInteger;
                highestIndex = i;
                foundInteger = 1;
            }
        } 
        
    else {
            printf("No integer found in line %zu: %s", i, lines[i]);
    }
    }

    if (!foundInteger) {
        fprintf(stderr, "No integers found in the file.\n");
        for (size_t i = 0; i < lineCount; i++) {
            free(lines[i]);
        }
        free(lines);
        return;
    }

  
    printf("Highest integer found: %d at line %zu\n", highestInteger, highestIndex);

   
    file = fopen(filePath, "w");
    if (file == NULL) {
        perror("fopen for writing");
        for (size_t i = 0; i < lineCount; i++) {
            free(lines[i]);
        }
        free(lines);
        exit(EXIT_FAILURE);
    }

  
    for (size_t i = 0; i < lineCount; i++) {
        if (i != highestIndex) 
        {
            size_t len = strlen(lines[i]);
            if (fwrite(lines[i], 1, len, file) != len) {
                perror("fwrite");
                for (size_t j = 0; j <= i; j++) {
                    free(lines[j]);
                }
                free(lines);
                fclose(file);
                exit(EXIT_FAILURE);
        }
        }
        free(lines[i]);
    }
    free(lines);
    fclose(file);
}

*/




void appendToFile(const char *filePath, int number, const char *str) {

    FILE *file = fopen(filePath, "a");
    if (file == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
  }

    fprintf(file, "%d %s\n", number, str);
    fclose(file);
}



void push(char* new_addr) 
{
    char buffer[MAX_STACK_SIZE];
    update_g_var_ins();
    if (g_var_ins == -1) {
        if (getcwd(buffer, sizeof(buffer)) == NULL) {
            perror("getcwd");
            exit(EXIT_FAILURE);
} } 
    
    else {
        FILE *file = fopen(FILE_PATH_NEW, "r");
        if (file == NULL) {
            perror("Error opening input file");
            exit(EXIT_FAILURE);
        } 
        char line[MAX_STACK_SIZE];
        while (fgets(line, sizeof(line), file) != NULL) {
            int number;
            char path[MAX_STACK_SIZE];
            if (sscanf(line, "%d %[^\n]", &number, path) == 2) {
                if (number == g_var_ins) {
                    strcpy(buffer, path);
                    break;
              }
          }
        }


        fclose(file);
    }

    g_var_ins++;
    if (g_var_ins >= MAX_STACK_SIZE) {
        fprintf(stderr, "Stack overflow\n");
        exit(EXIT_FAILURE);
    }
    node* new_node = (node*)malloc(sizeof(node));
    if (new_node == NULL)
     {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    new_node->directory = strdup(buffer);
    if (new_node->directory == NULL)
     {
        perror("strdup");
        free(new_node);
        exit(EXIT_FAILURE);
    }

    appendToFile(FILE_PATH, g_var_ins, buffer);
    
    appendToFile(FILE_PATH_NEW, g_var_ins, new_addr);
}

char* last_read_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    char buffer[1024];
    int maxInt = -1;
    char *resultStr = NULL;

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        char *line = strdup(buffer);
        if (line == NULL) {
            perror("strdup");
            fclose(file);
            return NULL;
    }

        char *token = strtok(line, " \t\n");
        while (token != NULL) 
        {
            int isInteger = 1;
            for (int i = 0; i < strlen(token); i++) 
            {
              if (!isdigit(token[i]) && !(i == 0 && token[i] == '-'))
                {
                    isInteger = 0;
                    break;
             }
         }

            if (isInteger) {
                int value = atoi(token);
                token = strtok(NULL, " \t\n");
                if (token != NULL && value > maxInt) 
                {
                    maxInt = value;

                    if (resultStr) 
                    {
                        free(resultStr);
                    }
                    resultStr = strdup(token);
                    if (resultStr == NULL) {
                        perror("strdup");

                        free(line);
                        fclose(file);
                        return NULL;
                    }
                }
               } 
            
            
            
            else
            {
                token = strtok(NULL, " \t\n");
            }
        }


        free(line);
    }

    fclose(file);
    return resultStr;
}

void pop() {

  

    update_g_var_ins();
    if (g_var_ins == -1)
    {
        printf("The stack is empty\n");
        return;
    }

    g_var_ins--;
    char* directory_to_pop = last_read_file(FILE_PATH);
    if (directory_to_pop == NULL)
    {
     fprintf(stderr, "Error: Failed to read directory to pop.\n");
        return;
    }
    executeShellScript(directory_to_pop,"pop");
    free(directory_to_pop);


}

void init_stack(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    fprintf(file, "-1\n");
    fclose(file);
}

int main(int arg_count, char* com_arr[]) {



    if (arg_count < 2) {
        printf("Invalid argument format\n");
        exit(EXIT_FAILURE);
    }

    if (strcmp(com_arr[1], "jp_push") == 0) {
        if (arg_count != 3) {
            printf("Invalid argument format\n");
            exit(EXIT_FAILURE);
        }
        push(com_arr[2]);
        executeShellScript(com_arr[2],com_arr[1]);

    } 

    
    if (strcmp(com_arr[1], "jp_pop") == 0) {
        if (arg_count != 2) {
            printf("Invalid argument format\n");
            exit(EXIT_FAILURE);
        }
        pop();

    } 
    
    
    else if (strcmp(com_arr[1], "JP_INIT") == 0) {
        if (arg_count != 2) {
            printf("Invalid argument format\n");
            exit(EXIT_FAILURE);
        }
        init_stack(FILE_PATH);
        init_stack(FILE_PATH_NEW);

    } 
    
    else {
        printf("Invalid command\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}
