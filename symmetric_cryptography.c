#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define ALPHABET_SIZE 26

// Cryptpage/Décryptage de césar
void caesarEnc(char* message, short key, char** ciphertext);
void caesarDec(char* ciphertext, short key, char** plaintext);

// Cryptpage/Décryptage de viginere
void vigenereEnc(char* text, char* key, char** ciphertext);
void vigenereDec(char* ciphertext, char* key, char** plaintext);

// Cryptpage/Décryptage par substitution
void SubstitutionEnc(char* message, char* ciphertext, char* shuffledAlphabet);
void SubstitutionDec(char *ciphertext, char *decryptedText, char *shuffledAlphabet);

// Cryptpage/Décryptage par transposition
void TranspositionEnc(char* message, char* ciphertext, int key);
void TranspositionDec(char* ciphertext, char* decryptedText, int key);

int getch();

int main() {
	
    char message[100];
    int key; // Variable to store the key value
    char Vkey[10];
    char* cryptedMessage = NULL;
    char* decryptedMessage = NULL;
    char encryptedMessagesub[ALPHABET_SIZE];
    char decryptedMessagesub[ALPHABET_SIZE];
    char shuffledAlphabetsub[ALPHABET_SIZE * 2];  // To store the permutation
    char ciphertext[100];
    char decryptedText[100];
    int choice;
        
    printf("Donner un message pour crypter:");
    scanf("%[^\n]",message);
        
	while(1){
        system("cls");
        printf("------Symmetric cryptography----------\n");
        printf("1.Cryptage de Cesar\n");
        printf("2.Decryptage de Cesar\n");
        printf("3.Cryptage de Viginere\n");
        printf("4.Decryptage de Viginere\n");
        printf("5.Cryptage par Substitution\n");
        printf("6.Decryptage par Substitution\n");
        printf("7.Cryptage par Transposition\n");
        printf("8.Decryptage par Transposition\n");
	printf("9.Exit\n");
        printf("--------------------------------------\n");
        printf("Enter your choice:");
        scanf("%d",&choice);
        switch(choice){
            case 1: printf("Enter the key (an integer): ");
                    scanf("%d", &key);
		    caesarEnc(message, key, &cryptedMessage);
		    printf("Original message: %s\n", message);
		    printf("Encrypted message: %s\n", cryptedMessage);
            break;
                
            case 2: printf("Enter the key (an integer): ");
                    scanf("%d", &key);
		    caesarDec(cryptedMessage, key, &decryptedMessage);
	            printf("Encrypted message: %s\n", cryptedMessage);
	   	    printf("Decrypted message: %s\n", decryptedMessage);
		    free(cryptedMessage);
		    free(decryptedMessage);
            break;
		
	    case 3: printf("Enter the key (an string): ");
                    scanf("%s", &Vkey);
                    vigenereEnc(message, Vkey, &cryptedMessage);
                    printf("Original message: %s\n", message);
		    printf("Encrypted message: %s\n", cryptedMessage);
	    break;
			
	    case 4: printf("Enter the key (an string): ");
                    scanf("%s", &Vkey);
		    vigenereDec(cryptedMessage, Vkey, &decryptedMessage);
		    printf("Encrypted message: %s\n", cryptedMessage);
		    printf("Decrypted message: %s\n", decryptedMessage);
		    free(cryptedMessage);
		    free(decryptedMessage);
	    break;
			
	    case 5: SubstitutionEnc(message, encryptedMessagesub,shuffledAlphabetsub);
		    printf("Original Message: %s\n", message);
		    printf("Encrypted Message: %s\n", encryptedMessagesub);		
            break;
			
	    case 6: SubstitutionDec(encryptedMessagesub, decryptedMessagesub, shuffledAlphabetsub);
		    printf("Encrypted Message: %s\n", encryptedMessagesub);
		    printf("Decrypted Message: %s\n", decryptedMessagesub);
            break;
			
	    case 7: printf("Enter the key (an integer): ");
                    scanf("%d", &key);
	   	    TranspositionEnc(message, ciphertext, key);
		    printf("Message original: %s\n", message);
		    printf("Message crypte: %s\n", ciphertext);
            break;
			
	    case 8: printf("Enter the key (an integer): ");
                    scanf("%d", &key);
                    TranspositionDec(ciphertext, decryptedText, key);
	            printf("Ciphertext: %s\n", ciphertext);
		    printf("Decrypted Text: %s\n", decryptedText);
            break;
			    
	    case 9: exit(0);
            break;
						   
            default: printf("Wrong Choice\n");
            break;
        }
                
        getch();
    }
	
	return 0;
}

void caesarEnc(char* message, short key, char** ciphertext){
    
    unsigned int i = 0;
    int rang;

    *ciphertext = (char *)malloc(strlen(message) + 1);

    while(message[i] != '\0'){
        if ((message[i] >= 'a') && (message[i] <= 'z')){
			rang = (message[i] - 'a' + key) % 26;
			if (rang < 0){
            	rang += 26;
			}
			(*ciphertext)[i] = 'a' + rang;
        }else if((message[i] >= 'A') && (message[i] <= 'Z')){
            rang = (message[i] - 'A' + key) % 26;
            if (rang < 0){
            	rang += 26;
			}
            (*ciphertext)[i] = 'A' + rang;
        }else{
            (*ciphertext)[i] = message[i];
        }
        
        i++;
    }
    
    (*ciphertext)[i] = '\0';
}

void caesarDec(char* ciphertext, short key, char** plaintext){
    caesarEnc(ciphertext, -key, plaintext);
}

void vigenereEnc(char* text,char* key, char** ciphertext){
	
    unsigned int i, size = strlen(key);

    *ciphertext = (char *)malloc(strlen(text) + 1); // Allocate memory for the encrypted text
    if (*ciphertext == NULL) {
        printf("Memory allocation error for the encrypted text.\n");
        exit(1);
    }

    for (i = 0; text[i] != '\0'; i++) {
        if ((text[i] >= 'a') && (text[i] <= 'z')) {
            int rang = (text[i] + key[i % size] - 2 * 'a') % 26;
            (*ciphertext)[i] = 'a' + rang;
        } else if ((text[i] >= 'A') && (text[i] <= 'Z')) {
            int rang = (text[i] + key[i % size]) % 26;
            (*ciphertext)[i] = 'A' + rang;
        } else {
            (*ciphertext)[i] = text[i];
        }
    }
    (*ciphertext)[i] = '\0';
}

void vigenereDec(char* ciphertext, char* key, char** plaintext){
    
    unsigned int i, size = strlen(key);

    *plaintext = (char *)malloc(strlen(ciphertext) + 1); // Allocate memory for the decrypted text
    if (*plaintext == NULL) {
        printf("Memory allocation error for the decrypted text.\n");
        exit(1);
    }

    for (i = 0; ciphertext[i] != '\0'; i++) {
        if ((ciphertext[i] >= 'a') && (ciphertext[i] <= 'z')) {
            int rang = (ciphertext[i] - key[i % size] + 26) % 26;
            (*plaintext)[i] = 'a' + rang;
        } else if ((ciphertext[i] >= 'A') && (ciphertext[i] <= 'Z')) {
            int rang = (ciphertext[i] - key[i % size] + 26) % 26;
            (*plaintext)[i] = 'A' + rang;
        } else {
            (*plaintext)[i] = ciphertext[i];
        }
    }
    (*plaintext)[i] = '\0';
}

void SubstitutionEnc(char* message, char* ciphertext, char* shuffledAlphabet){
	
    int i;
    int n = strlen(message);

    // Create a random permutation of the alphabet for both uppercase and lowercase letters
    char alphabet[ALPHABET_SIZE * 2];
    for (i = 0; i < ALPHABET_SIZE; i++) {
        alphabet[i] = 'A' + i;  // Uppercase
        alphabet[i + ALPHABET_SIZE] = 'a' + i;  // Lowercase
    }

    srand(time(NULL));
    for (i = 0; i < ALPHABET_SIZE * 2 - 1; i++) {
        int j = i + rand() % (ALPHABET_SIZE * 2 - i);
        // Swap alphabet[i] and alphabet[j]
        char temp = alphabet[i];
        alphabet[i] = alphabet[j];
        alphabet[j] = temp;
    }

    // Encrypt the input text
    for (i = 0; i < n; i++) {
        char letter = message[i];
        if (isalpha(letter)) {
            char offset = isupper(letter) ? 'A' : 'a';
            ciphertext[i] = alphabet[letter - offset];
        } else {
            ciphertext[i] = letter;  // Keep non-alphabetic characters unchanged
        }
    }
    ciphertext[n] = '\0';
    
    // Save the shuffled alphabet for decryption
    for (i = 0; i < ALPHABET_SIZE * 2; i++) {
        shuffledAlphabet[i] = alphabet[i];
    }
}

void SubstitutionDec(char* ciphertext, char* decryptedText, char* shuffledAlphabet){
	
    int i;
    int n = strlen(ciphertext);

    // Decrypt the input text
    for (i = 0; i < n; i++) {
        char letter = ciphertext[i];
        if (isalpha(letter)) {
            char offset = isupper(letter) ? 'A' : 'a';
            // Find the original character in the shuffled alphabet
            char originalChar = shuffledAlphabet[letter - offset];
            decryptedText[i] = originalChar;
        } else {
            decryptedText[i] = letter;  // Keep non-alphabetic characters unchanged
        }
    }
    decryptedText[n] = '\0';
}

void TranspositionEnc(char* message, char* ciphertext, int key){
	
    int messageLength = strlen(message);
    int numRows = (messageLength + key - 1) / key;
    char transpositionMatrix[numRows][key];

    // Initialiser la matrice avec le caractère 'X'
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < key; j++) {
            transpositionMatrix[i][j] = 'X';
        }
    }

    // Remplir la matrice avec le message original
    int row = 0, col = 0;
    for (int i = 0; i < messageLength; i++) {
        transpositionMatrix[row][col] = message[i];
        col++;
        if (col == key) {
            col = 0;
            row++;
        }
    }

    // Construire le message crypté à partir de la matrice transposée
    int index = 0;
    for (int j = 0; j < key; j++) {
        for (int i = 0; i < numRows; i++) {
            if (transpositionMatrix[i][j] != '\0') {
                ciphertext[index] = transpositionMatrix[i][j];
                index++;
            }
        }
    }
    ciphertext[index] = '\0';
}

void TranspositionDec(char* ciphertext, char* decryptedText, int key){
	
    int ciphertextLength = strlen(ciphertext);
    int numRows = (ciphertextLength + key - 1) / key;
    char transpositionMatrix[numRows][key];

    // Calculate the number of characters in the last row
    int lastRowLength = ciphertextLength % key;

    // Initialize the matrix with null characters
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < key; j++) {
            transpositionMatrix[i][j] = '\0';
        }
    }

    // Determine the number of characters in each row
    int fullRows = numRows - (lastRowLength == 0 ? 0 : 1);
    int fullRowLength = (lastRowLength == 0) ? key : lastRowLength;

    // Calculate the number of rows that are shorter
    int shorterRows = lastRowLength;

    // Fill the matrix with the ciphertext
    int index = 0;
    for (int j = 0; j < key; j++) {
        for (int i = 0; i < numRows; i++) {
            if (i < fullRows || (i == fullRows && j < fullRowLength)) {
                transpositionMatrix[i][j] = ciphertext[index];
                index++;
            }
        }
    }

    // Reconstruct the decrypted text from the matrix
    index = 0;
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < key; j++) {
            if (transpositionMatrix[i][j] != 'X') {
                decryptedText[index] = transpositionMatrix[i][j];
                index++;
            }
        }
    }
    decryptedText[index] = '\0';
}
