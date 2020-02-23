/*********************************************
 * Project 1 - Ceasar Cipher
 * Kevin Smith
 * Due - 2/22/2019
 ********************************************/
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LETTERS 26
#define TRUE      1
#define FALSE     0


/************************************************************************
 * Remove duplicate letters in the array word.
 ***********************************************************************/
char * remDup(char word []);


/************************************************************************
 * Search for a target letter in list[] found at an index less than num.
 ***********************************************************************/
int found(char list[], int num, char target);


/***********************************************************************
 * Initialize the encrypt array.
 **********************************************************************/
void initializeEncryptArray(char key[], char encrypt[]);


/***********************************************************************
 * Initialize the decrypt array.
 **********************************************************************/
void initializeDecryptArray(char encypt[], char decrypt[]);


/***********************************************************************
 *Process data from an input file and write the result to an output file.
 **********************************************************************/
void processInput(FILE * inf, FILE * outf, char substitute[]);


/***********************************************************************
 * Main function to complete the encryption/decryption program.
 **********************************************************************/
int main(int argc, char* argv[]){
    int encrypting = TRUE;
    char *key, encrypt[LETTERS+1], decrypt[LETTERS+1];
    FILE *fin, *fout;
    if (argc != 5){
        printf ("\nPlease insert the information as:\n");
        printf ("Option 1 for encryption and 2 for decryption\n");
        printf ("followed by your word, infile, outfile\n\n");
        exit(1);
    }
    if(atoi(argv[1]) == 2)
        encrypting = FALSE;
    
    fin = fopen(argv[3], "r");
    fout = fopen(argv[4], "w");
    if (fin ==  NULL || fout == NULL){
        printf("File could not be opened\n");
        exit(1);
    }
    key = remDup(argv[2]);
    if(strlen(key) > LETTERS){
        fprintf(stdout, "\nSorry, but that key is too long, please try something under 26 characters.\n");
        exit(1);
    }
    initializeEncryptArray(key, encrypt);
    initializeDecryptArray(encrypt, decrypt);

    if(encrypting){
        processInput(fin, fout, encrypt);
        fprintf(stdout, "The encrypted file: %s, has been created\n\n", argv[4]);
    } else {
        processInput(fin, fout, decrypt);
        fprintf(stdout, "The decrypted file: %s, has been created\n\n", argv[4]);
    }
    fclose(fin);
    fclose(fout);
    free(key);
    return 0;
}

//Reading and writing of encryption and decryption.
void processInput(FILE * inf, FILE * outf, char substitute[]){
    char ch;
    int i = 0;
    while (fscanf(inf, "%c", &ch) != EOF){
        fprintf(outf, "%c", substitute[ch-'A']);
        i++;
    }
}

//Decrypt array initialization.
void initializeDecryptArray(char encrypt[], char decrypt[]){
    int i;
    for(i=0; i < LETTERS; i++){
        decrypt[encrypt[i]-'A'] = 'A' + i;
    }
    decrypt[i] = '\0';
    fprintf(stdout, "decrypted word: %s\n\n", decrypt);
}

//Encrypt array initialization.
void initializeEncryptArray(char key[], char encrypt[]){
    int i, k = 0;
    for(i=0; i < LETTERS; i++){
        if(i < strlen(key)){
            encrypt[i] = key[i];
        } else {
            if(!found(key, LETTERS + 1, 'Z' - k))
                encrypt[i] = 'Z' - k;
            else
                i--;
            k++;
        }
    }
    encrypt[i] = '\0';
    fprintf(stdout,"\nencrypted word: %s\n", encrypt);
}

//Helper to search array and find duplicate letter.
int found(char list[], int num, char target){
    int i;
    for(i=0; i < strlen(list); i++){
        if(i < num && list[i] == target)
            return TRUE;
    }
    return FALSE;
}

//Helper that removes any duplicates from the array.
char * remDup(char word []){
    char *lett = (char*) malloc(sizeof(char)*26);
    int i, k = 0;
    for(i=0; i < strlen(word); i++){
        if(!found(word, i, word[i])){
            lett[k++] = word[i];
        }
    }
    lett[k] = '\0';
    printf("\nword in: %s\nkey: %s\n", word, lett);
    return lett;
}
