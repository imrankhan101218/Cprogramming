#include <stdio.h>
#include <stdlib.h>
#define ROOMS 5
#define SAVE_FILE "savegame.txt"

void initRooms(char *desc[], int c1[], int c2[]);
void playGame(char *name, char *desc[], int c1[], int c2[]);
void saveGame(char *name, int health, int room);
int loadGame(char *name, int *health, int *room);

int main() {
    char *playerName;
    int choice;
    char *roomDesc[ROOMS];
    int choice1[ROOMS];
    int choice2[ROOMS];

    playerName = malloc(50 * sizeof(*playerName));
    if (playerName == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    initRooms(roomDesc, choice1, choice2);

    printf("1. New Game\n");
    printf("2. Load Game\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    if (choice == 2) {
        int health, room;
        if (loadGame(playerName, &health, &room)) {
            printf("\nWelcome back %s!\n", playerName);
            playGame(playerName, roomDesc, choice1, choice2);
        } else {
            printf("\nNo saved game found. Starting new game.\n");
            printf("Enter your name: ");
            scanf("%s", playerName);
            playGame(playerName, roomDesc, choice1, choice2);
        }
    } else {
        printf("Enter your name: ");
        scanf("%s", playerName);
        playGame(playerName, roomDesc, choice1, choice2);
    }

    free(playerName);
    return 0;
}
//function for initializing the rooms....
void initRooms(char *desc[], int c1[], int c2[]) {
    desc[0] = "You are in a dark dungeon. Two doors ahead.";
    desc[1] = "You enter a monster room. It attacks!";
    desc[2] = "You found a healing fountain.";
    desc[3] = "You reached the treasure chamber.";
    desc[4] = "You fell into a deadly trap.";

    c1[0] = 1; c2[0] = 2;
    c1[1] = 4; c2[1] = 2;
    c1[2] = 3; c2[2] = 1;
    c1[3] = -1; c2[3] = -1; 
    c1[4] = -2; c2[4] = -2;  
}
//function where the game is started....
void playGame(char *name, char *desc[], int c1[], int c2[]) {
    int health = 100;
    int room = 0;
    int choice;

    while (1) {
        printf("\n");
        printf("%s\n", desc[room]);
        printf("Health: %d\n", health);

        if (room == 3) {
            printf("\nCONGRACULATIONS, YOU WON THE GAME, %s!\n", name);
            break;
        }
        if (room == 4 || health <= 0) {
            printf("\nGAME OVER, %s!\n", name);
            break;
        }

        printf("1. Choice 1\n");
        printf("2. Choice 2\n");
        printf("3. Save & Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 3) {
            saveGame(name, health, room);
            printf("\nGame saved. Exiting...\n");
            return;
        }

        if (choice == 1){
            room = c1[room];
        }else if (choice == 2){
            room = c2[room];
        }else{
            printf("Invalid choice!\n");
            continue;
        }

        if (room == 1){
            health -= 30;
        }
        if (room == 2){
            health += 20;
        }
    }
}
//function to save game....
void saveGame(char *name, int health, int room) {
    FILE *fp = fopen(SAVE_FILE, "w");
    if (fp == NULL){
        return;
    }
    fprintf(fp, "%s %d %d", name, health, room);
    fclose(fp);
}
//function to continue the saved game....
int loadGame(char *name, int *health, int *room) {
    FILE *fp = fopen(SAVE_FILE, "r");
    if (fp == NULL){
        return 0;
    }
    fscanf(fp, "%s %d %d", name, health, room);
    fclose(fp);
    return 1;
}
