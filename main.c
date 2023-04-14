#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <time.h>

typedef char string20[21];

void getRandomWord(string20 secretWord);
void displayScreen(char availableLetters[27]);
void displayHangman(int mistakes);
void displayWord(string20 secretWord, string20 guessedWord);
char getLetter(char availableLetters[27]);

int main() {

    string20 secretWord, guessedWord;
    int bContinueGame = 1, bIsGuessed = 0, mistakes = 0;
    char availableLetters[27] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};

    getRandomWord(secretWord);

    while (bContinueGame == 1) {

        char letter, bIsCorrect = 0;

        displayScreen(availableLetters);
        displayHangman(mistakes);
        displayWord(secretWord, guessedWord);

        letter = getLetter(availableLetters);

        for (int i = 0; i < 26; i++) {
            if (availableLetters[i] == letter) {
                availableLetters[i] = '\0';
                i = 26;
            }
        }

        for (int i = 0; i < strlen(secretWord); i++) {
            if (secretWord[i] == letter) {
                guessedWord[i] = letter;
                bIsCorrect = 1;
            }
        }

        if (bIsCorrect != 1) mistakes++;

        if (strlen(secretWord) == strlen(guessedWord) - 1) {
            strcat(guessedWord, "\0");
        }

        if (mistakes == 6) bContinueGame = 0;

        // DEBUG: The winning condition doesn't work.        
        if (strcmp(secretWord, guessedWord) == 0 && mistakes < 6) {
            bIsGuessed = 1;
            bContinueGame = 0;
        }
        
    }

    system("cls");

    printf("\n[Hangman Console] ");

    if (bIsGuessed == 1) printf("\033[32mCongratulations! \033[00mYou have guessed the word!\n");
    else printf("Oh no.. \033[31mYou hung the DJ\033[00m..\n");

    displayHangman(mistakes);
    displayWord(secretWord, guessedWord);

    printf("Press enter to continue..");
    _getch();

}

void getRandomWord(string20 secretWord) {

    int random, counter = 0;

    FILE *filePointer = fopen("words.txt", "r");

    while (fgets(secretWord, 21, filePointer)) {
        counter++;
    }

    srand(time(NULL));
    random = rand() % counter + 1;

    rewind(filePointer);

    for (int i = 0; i < random; i++) {
        fgets(secretWord, 21, filePointer);
    }

    fclose(filePointer);

    for (int i = 0; i < strlen(secretWord); i++) {
        secretWord[i] = toupper(secretWord[i]);
    }

}

void displayScreen(char availableLetters[27]) {

    system("cls");
    printf("\n[Hangman Console] Your available letters are:");

    for (int i = 0; i < 26; i++) {
        if (availableLetters[i] == '\0') printf(" \033[31m%c\033[00m", i + 65);
        else printf(" %c", availableLetters[i]);
    }

    printf(".\n");

}

void displayHangman(int mistakes) {

    switch (mistakes) {
        case 0: printf("\n   ______   ");
                printf("\n  |      |  ");
                printf("\n  |         ");
                printf("\n  |         ");
                printf("\n  |         ");
                printf("\n__|__       "); break;
        case 1: printf("\n   ______   ");
                printf("\n  |      |  ");
                printf("\n  |      O  ");
                printf("\n  |         ");
                printf("\n  |         ");
                printf("\n__|__       "); break;
        case 2: printf("\n   ______   ");
                printf("\n  |      |  ");
                printf("\n  |      O  ");
                printf("\n  |      |  ");
                printf("\n  |         ");
                printf("\n__|__       "); break;
        case 3: printf("\n   ______   ");
                printf("\n  |      |  ");
                printf("\n  |      O  ");
                printf("\n  |      |  ");
                printf("\n  |     /   ");
                printf("\n__|__       "); break;
        case 4: printf("\n   ______   ");
                printf("\n  |      |  ");
                printf("\n  |      O  ");
                printf("\n  |      |  ");
                printf("\n  |     / \\");
                printf("\n__|__       "); break;
        case 5: printf("\n   ______   ");
                printf("\n  |      |  ");
                printf("\n  |      O  ");
                printf("\n  |     /|  ");
                printf("\n  |     / \\");
                printf("\n__|__       "); break;
        case 6: printf("\n   ______   ");
                printf("\n  |      |  ");
                printf("\n  |      O  ");
                printf("\n  |     /|\\");
                printf("\n  |     / \\");
                printf("\n__|__       ");
    }

}

void displayWord(string20 secretWord, string20 guessedWord) {

    for (int i = 0 ; i < strlen(secretWord) - 1; i++) {
        if (secretWord[i] != guessedWord[i]) printf(" _");
        else printf(" %c", guessedWord[i]); 
    }

    printf("\n\n");

}

// DEBUG: It considers two inputs at once.
char getLetter(char availableLetters[27]) {

    char letter;
    int bIsValid = 0;

    while (bIsValid != 2) {

        printf("Enter Letter: ");
        scanf(" %c", &letter);

        if (isalpha(letter) != 0) {
            if (isalpha(letter) == 2) letter = toupper(letter);
            bIsValid++;
        }

        for (int i = 0; i < 26; i++) {
            if (availableLetters[i] == letter) bIsValid++;
        }

        if (bIsValid != 2) bIsValid = 0;

    }

    return letter;
    
}
