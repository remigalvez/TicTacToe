#include <stdio.h>
#define SCREEN_HEIGHT 50
#define true 1
#define false 0
typedef int bool;

/* Array of BOARD */
char BOARD[9];
/* Binary variable to keep track of players turns */
/* 1 - X */
/* 0 - O */
int PLAYER; 
/* Variable to store keyboard input */
char IN;
/* Boolean variable to define state of game */
bool PLAYING = false; 
/* Variable to store game output */
int OUT;

/**
 * Prints a certain number of lines to the console defined by macro
 * SCREEN_HEIGHT to clear the console.
 *
 * @params
 * return
 */
void clearScreen() {
    int i;
    for (i = 0; i < SCREEN_HEIGHT; i++) 
        printf("\n");
}

/**
 * Requests single character input from user between '1' and '9' inclusive, 
 * or 'q' to quit the game.
 * The input is stored as an integer in the global variable IN.
 *
 * @params 
 * return 
 */
void getValidInput() {
    bool invalid = false;

    do {
        /* Set input to valid */
        invalid = false;
        /* Get user input */
        printf("%c - Which square? [1-9] : ", PLAYER == 0 ? 'O' : 'X');
        scanf(" %c", &IN);
        /* Process user input */
        if (IN == 'q') {
            /* quit */
            PLAYING = false;
            return;
        } else {
            /* Convert user input to number */
            IN = IN - '0';
            /* If user input is out of range */
            if (IN <= 0 || IN > 9 || getchar() != '\n') {
                /* Clear input buffer */
                while (getchar() != '\n');
                /* Inform user of invalid input */
                printf("Invalid input\n");
                /* Start over function */
                invalid = true;
                continue;
            }
            /* Check if IN is available */
            if (BOARD[IN-1] == 'X' || BOARD[IN-1] == 'O') {
                /* Inform user of occupied space */
                printf("Space occupied\n");
                /* Start over function */
                invalid = true;
                continue;
            }
            /* Otherwise, clear screen & break */
            clearScreen();
            invalid = false;
            break;
        }   
    } while (invalid);
}

/**
 * Updates character in tic tac toe board array to appropriate
 * character (ie. 'X' or 'O').
 *
 * @params
 * return
 */
void updateBoard() {
    char player;
    switch (PLAYER) {
        case 0:
            player = 'O';
            break;
        case 1:
            player = 'X';
            break;
        default:
            player = '-';
    } 
    BOARD[IN-1] = player;
}

/**
 * Renders formatted ASCII board to the console to simulate refresh.
 * Called after each move.
 * 
 * @params
 * return
 */
void drawBoard() {
    int i;
    printf("\n⌜-----------------⌝\n");
    printf("|     |     |     |\n|");
    /* Iterate through BOARD values and format appropriately */
    for (i = 0; i < 9; i++) {
        if (i > 0 && i%3 == 0) {
            printf("\n|     |     |     |");
            printf("\n|-----------------|\n");
            printf("|     |     |     |\n|");
        }
        printf("  %c  |", BOARD[i]);
    }
    printf("\n|     |     |     |");
    printf("\n⌞-----------------⌟\n\n");
}

/**
 * Displays a message to the console to inform the user of the winner
 * of the game based on value stored in global variable OUT.
 *
 * @params
 * return
 */
void printOutcome() {
    switch (OUT) {
        case 0:
            break;
        case 1:
            printf("\nX wins!\n");
            break;
        case 2: 
            printf("\nO wins!\n");
            break;
        case 3:
            printf("\nCat game!\n");
            break;
        default:
            printf("Invalid game output\n");
            break;
    }
}

/*
 *  Checks through each possibility to see if the game is over
 *  and defines a winner, or a tie.
 *  The output of the game is stored in global variable OUT,
 *  and the running loop PLAYING, is set to false.
 *
 *  @params
 *  return
 */
void evalBoard() {
    int i;
    char player;

    /* Check verticals and horizontals */
    for (i = 0; i < 3; i++) {
        player = BOARD[i];
        if (BOARD[i+3] == player && BOARD[i+6] == player) {
            OUT = (player == 'X') ? 1 : 2;
            PLAYING = false;
            return;
        }

        player = BOARD[3*i];
        if (BOARD[3*i + 1] == player && BOARD[3*i + 2] == player) {
            OUT = (player == 'X') ? 1 : 2;
            PLAYING = false;
            return;
        }
    }
    /* Check diagonals */
    player = BOARD[0];
    if (BOARD[4] == player && BOARD[8] == player) {
        OUT = (player == 'X') ? 1 : 2;
        PLAYING = false;
        return;
    }

    player = BOARD[2];
    if (BOARD[4] == player && BOARD[6] == player) {
        OUT = (player == 'X') ? 1 : 2;
        PLAYING = false;
        return;
    }
    /* Check cats game */
    for (i = 0; i < 9; i++) {
        /* If space not occupied, keep playing */
        if (BOARD[i] != 'X' && BOARD[i] != 'O') {
            OUT = 0;
            return;
        }
    }
    /* Else, cats game */
    OUT = 3;
    PLAYING = false;

}

/**
 * Initializes the board with integer values 1 through 9.
 * This funciton is called before the beginning of a new game.
 *
 * @params
 * return
 */
void initBoard() {
    int i;
    /* Set board values to their index */
    for (i = 0; i < 9; i++) {
        BOARD[i] = (i+1) + '0';
    }
}

/**
 * Prints a welcome message to the console at the beginning
 * of each game.
 *
 * @params
 * return
 */
void printWelcome() {
    printf("==================================\n");
    printf("===== Welcome to Tic Tac Toe =====\n");
    printf("==================================\n\n");
    /* Print TIC */
    printf("XXXXXXXXXXXXXX                      \n    XX    XX  XXXXXX                \n    XX        XX                    \n    XX    XX  XX                    \n    XX    XX  XX                    \n    XX    XX  XXXXXXXXXXXXXXXXX     \n\n");
    /* Print TAC */
    printf("    OOOOOOOOOOOOOO                      \n        OO    OOOO       OOOOO          \n        OO   OO   OO   OOO   OOO        \n        OO  OO    OO  OOO               \n        OO   OO   OO   OOO         OO   \n        OO    OOOO  OO  OOOOOOOOOOOO    \n\n");
    /* Print TOE */
    printf("        CCCCCCCCCCCCCC                      \n            CC    CCCC      CCCCC           \n            CC   CC  CC   CCC   CCC         \n            CC  CC    CC CCCCCCCCCC         \n            CC   CC  CC   CCC            CC \n            CC    CCCC     CCCCCCCCCCCCCCC  \n\n");
}

/**
 * Prints a goodbye message to the console at the end of each game.
 *
 * @params
 * return
 */
void printGoodbye() {
    printf("\nThanks for playing! Goodbye!\n");
}

/**
 * Begins a game of tic tac toe by clearing console, printing a welcome
 * message, initializing the game board, and starting a running game loop,
 * each loop consisting of one turn. 
 * The winner is displayed to the console at the end of the game, and a goodbye
 * message is printed to the console.
 *
 * @params
 * return
 */
void game() {
    /* Clear screen */
    clearScreen();
    /* Print welcome message */
    printWelcome();
    /* Start game */
    PLAYING = true;
    PLAYER = 1;
    /* Initialize board */
    initBoard();
    /* Draw board */
    drawBoard();
    /* Evaluate board */
    evalBoard();
    /* While game is playing */
    while (PLAYING) {
        getValidInput();
        updateBoard();
        drawBoard();
        evalBoard(); /* Evaluate board */
        PLAYER = !PLAYER; /* Switch players */
    }
    
    /* Print outcome of game & goodbye message */
    printOutcome();     
    printGoodbye();
}

int main() {
    char playAgain = 'n';
    const bool loopGames = false;
    do {
        game();
        if (loopGames) {
            printf("Would you like ot play again? (y/n) ");
            scanf(" %c", &playAgain);
        }
    } while (playAgain == 'y');
    return 0;
}
