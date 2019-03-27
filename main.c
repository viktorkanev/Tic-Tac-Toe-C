#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <windows.h>

void PrintBoard();
int winner();
void InitializeBoard();
int TicTacToeGame();
int t[100],n,a;

//Initializing the 1D array
char TicTacToe[9] =  { '1', '2', '3', '4', '5', '6', '7', '8', '9' };

//initializing the stack structure
struct Stack
{
    int top;
    unsigned capacity;
    char* array;
};

//creating stack
struct Stack* createStack(unsigned capacity)
{
    struct Stack* stack = (struct Stack*) malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (char*) malloc(stack->capacity * sizeof(char));
    return stack;
}
//changes the color of the text
void textcolor (int color)
{
    static int __BACKGROUND;

    HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;


    GetConsoleScreenBufferInfo(h, &csbiInfo);

    SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE),
                             color + (__BACKGROUND << 4));
}

// Stack is full when top is equal to the last index
int isFull(struct Stack* stack)
{
    return stack->top == stack->capacity - 1;
}

// Stack is empty when top is equal to -1
int isEmpty(struct Stack* stack)
{
    return stack->top == -1;
}

// Function to add an item to stack.  It increases top by 1
void push(struct Stack* stack, char item)
{
    if (isFull(stack))
        return;
    stack->array[++stack->top] = item;

}

// Function to remove an item from stack.  It decreases top by 1
int pop(struct Stack* stack)
{
    return stack->array[stack->top--];
}


//function to remove all elements from a stack
void removeAllElements(struct Stack * moves)
{
    int i = moves->top;
    while(i >= 0)
    {
        moves->array[i] = pop(moves);
        i--;
    }
}

//removes choices and marks from the undo stack and adds them to the redo stack
void undo(struct Stack * undoneM, struct Stack * undoneCh, struct Stack * redoneM, struct Stack * redoneCh)
{
    char mark = pop(undoneM);
    char choice = pop(undoneCh);
    push(redoneM, mark);
    push(redoneCh, choice);

    if(choice == '1')
    {
        TicTacToe[0] = '1';
    }
    else if(choice == '2')
    {
        TicTacToe[1] = '2';
    }
    else if(choice == '3')
    {
        TicTacToe[2] = '3';
    }
    else if(choice == '4')
    {
        TicTacToe[3] = '4';
    }
    else if(choice == '5')
    {
        TicTacToe[4] = '5';
    }
    else if(choice == '6')
    {
        TicTacToe[5] = '6';
    }
    else if(choice == '7')
    {
        TicTacToe[6] = '7';
    }
    else if(choice == '8')
    {
        TicTacToe[7] = '8';
    }
    else if(choice == '9')
    {
        TicTacToe[8] = '9';
    }
}

//removes choices and marks from the redo stack and adds them to redo stack
void redo(struct Stack * undoneM, struct Stack * undoneCh, struct Stack * redoneM, struct Stack * redoneCh)
{
    char mark = pop(redoneM);
    char choice = pop(redoneCh);
    push(undoneM, mark);
    push(undoneCh, choice);
    if(choice == '1')
    {
        TicTacToe[0] = mark;
    }
    else if(choice == '2')
    {
        TicTacToe[1] = mark;
    }
    else if(choice == '3')
    {
        TicTacToe[2] = mark;
    }
    else if(choice == '4')
    {
        TicTacToe[3] = mark;
    }
    else if(choice == '5')
    {
        TicTacToe[4] = mark;
    }
    else if(choice == '6')
    {
        TicTacToe[5] = mark;
    }
    else if(choice == '7')
    {
        TicTacToe[6] = mark;
    }
    else if(choice == '8')
    {
        TicTacToe[7] = mark;
    }
    else if(choice == '9')
    {
        TicTacToe[8] = mark;
    }
}



//replay function that reads txt file and replays the moves with 2 sec delay
int replayTTT()
{
    char filename[50];
    printf("Please enter the name of the file you want to replay:");
    scanf("%s",filename);

    //checks if the file you are trying to open exists
    if(getArray(filename)==NULL)
    {
        textcolor(4);
        printf("\nThe file you are trying to open does not exist!\n");
        textcolor(7);
        fflush(stdin);
    }
    else
    {
        int i;
        int starting = 0;
        int player = 1;
        int choice;
        char mark;
        do
        {
            printf("\n\n");
            PrintBoard();
            player = (player % 2) ? 1 : 2;
            mark = (player == 1) ? 'X' : 'O';
            choice = t[starting];
            if(choice == 1 && TicTacToe[0] == '1')
            {
                TicTacToe[0] = mark;
            }
            else if(choice == 2 && TicTacToe[1] == '2')
            {
                TicTacToe[1] = mark;
            }
            else if(choice == 3 && TicTacToe[2] == '3')
            {
                TicTacToe[2] = mark;
            }
            else if(choice == 4 && TicTacToe[3] == '4')
            {
                TicTacToe[3] = mark;
            }
            else if(choice == 5 && TicTacToe[4] == '5')
            {
                TicTacToe[4] = mark;
            }
            else if(choice == 6 && TicTacToe[5] == '6')
            {
                TicTacToe[5] = mark;
            }
            else if(choice == 7 && TicTacToe[6] == '7')
            {
                TicTacToe[6] = mark;
            }
            else if(choice == 8 && TicTacToe[7] == '8')
            {
                TicTacToe[7] = mark;
            }
            else if(choice == 9 && TicTacToe[8] == '9')
            {
                TicTacToe[8] = mark;
            }
            else if(choice == 10)
            {
                textcolor(9);
                printf("The game has been undone here.");
                textcolor(7);
            }
            else if(choice == 11)
            {
                textcolor(10);
                printf("The game has been redone here.");
                textcolor(7);
            }
            player++;
            starting++;
            delay(2);
            i = winner();

        }
        while(i == -1);  //While the game has no result, it keeps taking input for the board

        //Updates the grid one last time to show the result
        PrintBoard();

        //if i is returned from the function end the game
        if(i == 1)
        {
            printf("Finding the winner...\n");
            textcolor(2);
            printf("Player %d (%c) won!\n", player-1, mark);
            textcolor(7);
            fflush(stdin);
        }
        else
        {
            textcolor(14);
            printf("It's a tie!\n");    //Otherwise, it's a tie
            textcolor(7);
        }

    }

}

int TicTacToeGame()
{
    int player = 1;
    int i;
    int choice;
    char mark;
    char buffer[10];
    char filename[40];
    struct tm *timenow;
    time_t now = time(NULL);
    timenow = gmtime(&now);
    sprintf(filename,"moves%d.txt",(int)now);
    FILE *fptr;
    fptr = fopen(filename,"w");
    struct Stack * undoneCh = createStack(9);
    struct Stack * undoneM = createStack(9);
    struct Stack * redoneCh = createStack(9);
    struct Stack * redoneM = createStack(9);

    do
    {
        printf("\n\n");
        PrintBoard();

        player = (player % 2) ? 1 : 2;

        textcolor(14);
        printf("To undo enter 10\t\t To redo enter 11\n");
        textcolor(7);
        printf("Player %d, enter a number from the grid:", player);
        fgets(buffer, 10, stdin);
        choice = atoi(buffer);
        //checks if the input is digit to avoid infinite loop
        if(choice == 0)
        {
            textcolor(4);
            printf("Please enter a choice between 1 and 11.\n");
            textcolor(7);
            player--;
        }
        else
        {
            fprintf(fptr,"%d,", choice);
            mark = (player == 1) ? 'X' : 'O';


            if(choice == 1 && TicTacToe[0] == '1')
            {
                TicTacToe[0] = mark;
                removeAllElements(redoneCh);
                removeAllElements(redoneM);
                push(undoneCh, '1');
                push(undoneM, mark);
            }
            else if(choice == 2 && TicTacToe[1] == '2')
            {
                removeAllElements(redoneCh);
                removeAllElements(redoneM);
                push(undoneCh, '2');
                push(undoneM, mark);
                TicTacToe[1] = mark;
            }
            else if(choice == 3 && TicTacToe[2] == '3')
            {
                removeAllElements(redoneCh);
                removeAllElements(redoneM);
                push(undoneCh, '3');
                push(undoneM, mark);
                TicTacToe[2] = mark;
            }
            else if(choice == 4 && TicTacToe[3] == '4')
            {
                removeAllElements(redoneCh);
                removeAllElements(redoneM);
                push(undoneCh, '4');
                push(undoneM, mark);
                TicTacToe[3] = mark;
            }
            else if(choice == 5 && TicTacToe[4] == '5')
            {
                removeAllElements(redoneCh);
                removeAllElements(redoneM);
                push(undoneCh, '5');
                push(undoneM, mark);
                TicTacToe[4] = mark;
            }
            else if(choice == 6 && TicTacToe[5] == '6')
            {
                removeAllElements(redoneCh);
                removeAllElements(redoneM);
                push(undoneCh, '6');
                push(undoneM, mark);
                TicTacToe[5] = mark;
            }
            else if(choice == 7 && TicTacToe[6] == '7')
            {
                removeAllElements(redoneCh);
                removeAllElements(redoneM);
                push(undoneCh, '7');
                push(undoneM, mark);
                TicTacToe[6] = mark;
            }
            else if(choice == 8 && TicTacToe[7] == '8')
            {
                removeAllElements(redoneCh);
                removeAllElements(redoneM);
                push(undoneCh, '8');
                push(undoneM, mark);
                TicTacToe[7] = mark;
            }
            else if(choice == 9 && TicTacToe[8] == '9')
            {
                removeAllElements(redoneCh);
                removeAllElements(redoneM);
                push(undoneCh, '9');
                push(undoneM, mark);
                TicTacToe[8] = mark;
            }
            else if(choice == 10)
            {
                if(!(isEmpty(undoneM)) && !(isEmpty(undoneCh)) && !(isFull(redoneM)) && !(isFull(redoneM)))
                {
                    undo(undoneM, undoneCh, redoneM, redoneCh);
                    PrintBoard();
                }
                else
                {
                    player--;
                    textcolor(4);
                    printf("Sorry you can't undo right now!");
                    textcolor(7);
                }

            }
            else if(choice == 11)
            {
                if(!(isEmpty(redoneM)) && !(isEmpty(redoneCh)) && !(isFull(undoneM)) && !(isFull(undoneCh)))
                {

                    redo(undoneM, undoneCh, redoneM, redoneCh);
                    PrintBoard();
                }
                else
                {
                    player--;
                    textcolor(4);
                    printf("Sorry you can't redo right now!");
                    textcolor(7);
                }
            }
            else if(choice == -1)
            {
                printf("Exiting the program...\n\n Thanks for playing!\n");
                break;
            }
            else
            {
                textcolor(4);
                printf("Invalid move! To exit the game, enter -1.\n\n");
                textcolor(7);
                player--;
            }
        }
        //adds all the moves to linked list
        player++;
        i = winner();

    }
    while(i == -1);  //While the game has no result, it keeps taking input for the board.

    //Updates the grid one last time to show the result
    PrintBoard();

    //if i is returned from the function end the game
    if(i == 1)
    {
        printf("Finding the winner...\n");
        textcolor(2);
        printf("Player %d (%c) won!\n", player-1, mark);
        textcolor(7);
    }
    else
    {
        textcolor(14);
        printf("It's a tie!\n");    //Otherwise, it's a tie
        textcolor(7);
    }
    fclose(fptr);
}

//checks if the game has ended and who the winner is
int winner()
{
    //Each if statement checks every possibility if the game is won by any user, or it's a tie
    if((TicTacToe[0] == TicTacToe[1]) && (TicTacToe[1] == TicTacToe[2]))
    {
        return 1;
    }
    else if((TicTacToe[0] == TicTacToe[3]) && (TicTacToe[3] == TicTacToe[6]))
    {
        return 1;
    }
    else if((TicTacToe[0] == TicTacToe[4]) && (TicTacToe[4] == TicTacToe[8]))
    {
        return 1;
    }
    else if((TicTacToe[1] == TicTacToe[4]) && (TicTacToe[4] == TicTacToe[7]))
    {
        return 1;
    }
    else if((TicTacToe[2] == TicTacToe[5]) && (TicTacToe[5] == TicTacToe[8]))
    {
        return 1;
    }
    else if((TicTacToe[2] == TicTacToe[4]) && (TicTacToe[4] == TicTacToe[6]))
    {
        return 1;
    }
    else if((TicTacToe[3] == TicTacToe[4]) && (TicTacToe[4] == TicTacToe[5]))
    {
        return 1;
    }
    else if((TicTacToe[6] == TicTacToe[7]) && (TicTacToe[7] == TicTacToe[8]))
    {
        return 1;
    }
    //If the board is filled and no user has won, it's a tie
    else if(TicTacToe[0] != '1' && TicTacToe[1] != '2' &&
            TicTacToe[2] != '3' && TicTacToe[3] != '4' &&
            TicTacToe[4] != '5' && TicTacToe[5] != '6' &&
            TicTacToe[6] != '7' && TicTacToe[7] != '8' &&
            TicTacToe[8] != '9')
    {
        return 0;
    }

    //If no result, return -1 so the next user can play the next turn
    else
    {
        return -1;
    }
}


//Prints the TicTacToe grid
void PrintBoard()
{
    //the grid
    printf("Player 1: X\tvs\tPlayer 2: O\n");

    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c  \n", TicTacToe[0], TicTacToe[1], TicTacToe[2]);
    printf("_____|_____|_____\n");
    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c \n", TicTacToe[3], TicTacToe[4], TicTacToe[5]);
    printf("_____|_____|_____\n");
    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c \n", TicTacToe[6], TicTacToe[7], TicTacToe[8]);
    printf("     |     |     \n\n");
}



//Clears the grid back to default
void InitializeBoard()
{

    TicTacToe[0]='1';
    TicTacToe[1]='2';
    TicTacToe[2]='3';
    TicTacToe[3]='4';
    TicTacToe[4]='5';
    TicTacToe[5]='6';
    TicTacToe[6]='7';
    TicTacToe[7]='8';
    TicTacToe[8]='9';

}

//loads the entries from the saved file and adds them to array
void getArray(char filename[50])
{

    char *token;
    char help[256];
    FILE *InputFile;
    InputFile = fopen(filename, "r");
    fscanf(InputFile, "%s", help);
    token=strtok(help,",");
    a = 0;
    while(token != NULL)
    {
        t[a]=atoi(token);
        token=strtok(NULL, ",");
        a++;
    }
}

//time delay function for the replay feature
void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;

    // Stroing start time
    clock_t start_time = clock();

    // looping till required time is not acheived
    while (clock() < start_time + milli_seconds);
}

int main()
{
    int menu_option;
    char buffer[10];
    printf("T i c  T a c  T o e\n\n");
    do
    {
        printf("MAIN MENU\n\n");
        printf("To play Tic-tac-toe enter 1\nTo replay previous game enter 2\nTo exit enter 3:");
        fgets(buffer, 10, stdin); // gets the user input as a char
        menu_option = atoi(buffer); // converts the char to int
        if(menu_option != 3 && menu_option!= 1 && menu_option != 2 && menu_option==0)
        {
            textcolor(4);
            printf("\nPlease enter a valid number and try again!\n\n");
            textcolor(7);

        }
        else
        {
            switch(menu_option)
            {
            case 3:
            {
                printf("Exiting...\n");
                break;
            }

            case 1:
            {
                InitializeBoard();
                TicTacToeGame();
                break;
            }

            case 2:
            {
                InitializeBoard();
                replayTTT();
                break;

            }

            default:
            {
                //If entered number for menu is not a valid input
                textcolor(4);
                printf("Unrecognized input, enter a valid number\n\n");
                textcolor(7);
                break;
            }
            }

        }

    }
    while(menu_option != 3);  //exits the program when number 3 is entered

    printf("Thanks for playing!\n");
    return 0;
}
