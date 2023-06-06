#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// Student: Elon Hadad.
// ID: 034672139.
// Rotem Elimelech.
// ID: 313284606.

void guessing_game(){
    srand(time(NULL));
    int rand_num = rand()%1001;
    int attempts = 0;
    int player_guess = 0;
    while (true){
        printf("Enter a number (1-1000): ");
        scanf("%d", &player_guess);
        attempts ++;
        if (rand_num < player_guess)
            printf("Nope, too high!\n");
        else if (rand_num > player_guess)
            printf("Nope, too low!\n");
        else {
            printf("Correct, the number is %d ! You guessed it right after %d attempts\n",rand_num, attempts);
            break;
        }

    }
}

void is_arithmetic_progression(){
    int first, second;
    printf("Enter the first and second items separated by a comma: ");
    if (scanf("%d, %d", &first, &second) != 2) {
        printf("Error: Wrong input! goodbye\n");
        exit(0);
    }
    int difference = second - first;
    int a1 = first;
    int items = 2;
    bool flag = true;
    while (true) {
        printf("What is the next item? \n");
        first = 0;
        if (scanf("%d", &first)!= 1) {
            if (flag == true) {
                printf("This series of %d items is an arithmetic progression with a1=%d and diff=%d", items, a1,
                       difference);
                break;
            }
            else {
                printf("This series of %d items is not an arithmetic progression", items);
                break;
            }
        }
        if (first - second != difference) {
            flag = false;
        }
        second = first;
        items++;
    }
}

void ascii_art(){
    int user_input;
    printf("Would you like to draw a square (1) or a diamond (2)? ");
    if (scanf("%d", &user_input)!=1 || user_input != 1 && user_input !=2){
        printf("Wrong choice! good bye");
        exit(0);
    }
    if (user_input == 1) {
        int edge_size;
        printf("What should be the edge size? (1-30): ");
        scanf("%d", &edge_size);

        for (int i = 0; i < edge_size; i++) {
            for (int j = 0; j < edge_size; ++j)
                printf("*");

            printf("\n");
        }
    }
    else {
        int rows;
        printf("What should be the diagonal size? (odd, 1-29): ");
        scanf("%d", &rows);

        for (int i = 1; i <= (rows/2)+1; i++){
            for (int j = 1; j <= (rows-i); j++)
                printf(" ");

            for (int j = 1; j <= (2 * i)-1; j++)
                printf("*");

            printf("\n");
        }

        for (int i = 1; i <= (rows/2)+1; i++){
            for (int j = 1; j <= (rows/2)+i; j++)
                printf(" ");

            for (int j = 1 ; j <= (rows - (2 * i)); j++)
                printf("*");

            printf("\n");
        }
    }
}

int main() {
    ascii_art();
    return 0;
}
