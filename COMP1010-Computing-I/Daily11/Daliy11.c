/***********************************************
 Author: Erdun E
 Date: 03-12-2018
 Purpose: Exclude all unrelated letters and Numbers and do a loop to know the characters that appear.
 Time Spent: half day
 ***********************************************/

#include <stdio.h>
#include <ctype.h>

int main(int argc, char* argv[])
{
    char player_1_input[10];
    char player_2_input[10];
    
    int do_continue_the_game = 1;
    while(do_continue_the_game) {
        printf("Player-1 it is your turn!\nPlease enter your chioce (p)aper, (r)ock, or (s)cissors:\n");
        scanf("%s", player_1_input);
        while ( ! (tolower(player_1_input[0]) == 'p' || tolower(player_1_input[0]) == 'r' || tolower(player_1_input[0]) == 's'))
        {
            printf("I'm sorry, I do not understand.\nPlease enter your chioce (p)aper, (r)ock, or (s)cissors:\n");
            scanf("%s", player_1_input);
        }
        
        printf("Player-2 it is your turn!\nPlease enter your chioce (p)aper, (r)ock, or (s)cissors:\n");
        scanf("%s", player_2_input);
        while ( ! (tolower(player_2_input[0]) == 'p' || tolower(player_2_input[0]) == 'r' || tolower(player_2_input[0]) == 's'))
        {
            printf("I'm sorry, I do not understand.\nPlease enter your chioce (p)aper, (r)ock, or (s)cissors:\n");
            scanf("%s", player_2_input);
        }
        
        if (player_1_input[0] == 'p') {
            if (player_2_input[0] == 's') {
                printf("player2 win! Scissors cuts Paper.\n");
            }
            else if (player_2_input[0] == 'r') {
                printf("player1 win! Paper covers Rock.\n");
            }
            else {
                printf("you guys tie!!\n");
            }
        }
        else if (player_1_input[0] == 'r') {
            if (player_2_input[0] == 's') {
                printf("player1 win! Rock breaks Scissors.\n");
            }
            else if (player_2_input[0] == 'p') {
                printf("player2 win! Paper covers Rock.\n");
            }
            else {
                printf("you guys tie!!\n");
            }
        }
        else if (player_1_input[0] == 's') {
            if (player_2_input[0] == 'p') {
                printf("player1 win! Scissors cuts Paper.\n");
            }
            else if (player_2_input[0] == 'r') {
                printf("player2 win! Rock breaks Scissors\n");
            }
            else {
                printf("you guys tie!!\n");
            }
        }
        
        printf("Do you wish to continue?(y/n):\n");
        scanf("%s",player_1_input);
        if (player_1_input[0] == 'y'){
            do_continue_the_game = 1;
        }
        else if (player_1_input[0] == 'n'){
            printf("Have a good day!\n");
            do_continue_the_game = 0;
        }
    }
    return 0;
}


