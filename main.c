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

int main() {

    int bContinueGame = 1, mistakes = 0;
    string20 secretWord, guessedWord;
    char availableLetters[27] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};

    getRandomWord(secretWord);

    while (bContinueGame == 1) {

        displayScreen(availableLetters);
        displayHangman(mistakes);
        _getch();
        
    }

    return 0;

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

    printf("\n   _______    ");
    printf("\n  |       |   ");
    printf("\n  |       O   ");
    printf("\n  |      /|\\ ");
    printf("\n  |       |   ");
    printf("\n  |      / \\ ");
    printf("\n__|__         ");

}
