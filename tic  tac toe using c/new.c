#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
void printboard();
int checkWinner();
char board[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
void main()
{
    int player = 1, input, status = -1;
    printboard();
    while (status == -1)
    {
        // checking which player is current player
        player = (player % 2 == 0) ? 2 : 1;

        // get the player mark
        char mark = (player == 1) ? 'X' : 'O';

        // get the user input for the position
        printf("\nPlease enter a number for player %d\n", player);
        scanf("%d", &input);

        // input should be within the range
        if (input < 1 || input > 9)
        {
            printf("invalid input");
            continue;
        }

        // if position is already filled, skip the iteration
        if (board[input] == 'X' || board[input] == 'O')
        {
            printf("Cell already taken, please choose another number.\n");
            continue;
        }

        // update the board
        board[input] = mark;

        // clear the console for the updated board
        system("cls");

        // print the updated board
        printboard();

        // check if the game has ended
        int result = checkWinner();

        // if result is 1, player has won the game. print the message and exit the game
        if (result == 1)
        {
            printf("player %d is the winner", player);
            break;
        }

        // if not, then the game is draw
        else if (result == 0)
        {
            printf("Draw");
            break;
        }

        // update the player counter to change the current player
        player++;
    }
}

// function to print the board state
void printboard()
{
    printf("\n\n");
    printf("=== TIC TAC TOE===\n\n");
    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c  \n", board[1], board[2], board[3]);
    printf("_____|_____|_____\n");
    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c  \n", board[4], board[5], board[6]);
    printf("_____|_____|_____\n");
    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c  \n", board[7], board[8], board[9]);
    printf("     |     |     \n");
}

// function to check the winner
int checkWinner()
{
    if (board[1] == board[2] && board[2] == board[3])
    {
        return 1;
    }

    if (board[1] == board[4] && board[4] == board[7])
    {
        return 1;
    }

    if (board[3] == board[6] && board[6] == board[9])
    {
        return 1;
    }

    if (board[7] == board[8] && board[8] == board[9])
    {
        return 1;
    }

    if (board[1] == board[5] && board[5] == board[9])
    {
        return 1;
    }

    if (board[3] == board[5] && board[5] == board[7])
    {
        return 1;
    }

    if (board[4] == board[5] && board[5] == board[6])
    {
        return 1;
    }

    if (board[2] == board[5] && board[5] == board[8])
    {
        return 1;
    }
    int count = 0;
    for (int i = 1; i <= 9; i++)
    {
        if (board[i] == 'X' || board[i] == 'O')
        {
            count++;
        }
    }
    if (count == 9)
    {
        return 0;
    }
    return -1;
}