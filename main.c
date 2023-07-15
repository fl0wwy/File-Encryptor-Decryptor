#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void encrypt(char filepath[]);
void change_dir();
void decrypt(char filepath[]);

int main(){
    printf("Welcome to the Encryption/Decryption command line tool.\n");
    printf("-e for encryption || -d for decryption\n");
    char command[2];
    char path[20];
    while (1){
        memset(command,0,2);
        while (command[0] != '-' || (command[1] != 'e' && command[1] != 'd')){
            scanf("%s", &command);
            if (command[0] != '-' || (command[1] != 'e' && command[1] != 'd')){
                printf("Invalid command! please try again...\n");
            }
        }    
        
        if (command[1] == 'e'){
            change_dir();
            printf("\nenter filename: ");
            scanf("%s", &path);
            encrypt(path);
            printf("\n %s encrypted successfully.\n", path);
        }
        else{
            change_dir();
            printf("\nenter filename: ");
            scanf("%s", &path);
            decrypt(path);
            printf("\n %s decrypted successfully.\n", path);
        }
    }    
    return 0;
}

void encrypt(char filepath[]){
    FILE *input, *output;
    // retreving original file contents
    input = fopen(filepath, "rb");
    if (input == NULL){
        printf("Failed");
        exit(1);
    }
    output = fopen("temp.txt", "wb");
    if (output == NULL){
        printf("Failed_2");
        exit(1);
    }
    char ch = fgetc(input);
    while (ch != EOF){
        ch += strlen("hello world") * 10;
        fputc(ch, output);
        ch = fgetc(input);
    } 
    fclose(input);
    fclose(output);
    
    // replacing and deleteting temp file with original file
    input = fopen(filepath, "wb");
    if (input == NULL){
        printf("Failed");
        exit(1);
    }
    output = fopen("temp.txt", "rb");
    if (output == NULL){
        printf("Failed_2");
        exit(1);
    }
    ch = fgetc(output);
    while (ch != EOF){
        fputc(ch, input);
        ch = fgetc(output);
    } 
    fclose(input);
    fclose(output);
    remove("temp.txt");
}

void decrypt(char filepath[]){
    FILE *input, *output;
    // retreving original file contents
    input = fopen(filepath, "rb");
    if (input == NULL){
        printf("Failed");
        exit(1);
    }
    output = fopen("temp.txt", "wb");
    if (output == NULL){
        printf("Failed_2");
        exit(1);
    }
    char ch = fgetc(input);
    while (ch != EOF){
        ch -= strlen("hello world") * 10;
        fputc(ch, output);
        ch = fgetc(input);
    } 
    fclose(input);
    fclose(output);
    
    // replacing and deleteting temp file with original file
    input = fopen(filepath, "wb");
    if (input == NULL){
        printf("Failed");
        exit(1);
    }
    output = fopen("temp.txt", "rb");
    if (output == NULL){
        printf("Failed_2");
        exit(1);
    }
    ch = fgetc(output);
    while (ch != EOF){
        fputc(ch, input);
        ch = fgetc(output);
    } 
    fclose(input);
    fclose(output);
    remove("temp.txt");

}

void change_dir(){
    char dir[200];
    char curr[200];
    printf("Please enter the directory in which the file is stored (any key if file in current dir): ");
    scanf("%s", &dir);
    chdir(dir);
    if (strcmp(getcwd(curr, sizeof(curr)), dir) == 0){
        printf("switched to directory: %s\n", dir);
    }
    else{
       printf("directory change failed or aborted...\n"); 
    }    
}
