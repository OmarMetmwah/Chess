//Chess Game//

//Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

//Functions: (Usage of Each Function is written in a comment before its implementation)
    //Functions for the whole game
void printInterface();
void printRules();
void printWord(char piece);
void SetColorAndBackground(int ForC, int BackC);
void printBoard();
void printWordAvailabe(char piece);
void printAvailableBoard(int *available);
void blackOrWhite(char piece);
void blackOrWhiteAvailable(char piece);
int change( int r1 , int c1 , int r2 , int c2, int *available);
void sort(int size, char x[]);
int compareArray(char a[],char b[],int size);
void save();
void load();
void newGame();
void undo();
void redo();

    //White player function
int player1();
int checkWhite(int x , int y );
void promotion(int r2, int c2);
int *pawnWhite(int r1,int c1);
int *rook(int r1, int c1);
int *knight(int r1, int c1);
int *bishop(int r1, int c1);
int *queen(int r1, int c1);
int checkNearbyBKing(int r2, int c2);
int *king(int r1, int c1);
void printAvilable(int *available);
int check();
int checkmate();
int stalemate();

    //Black player functions
int player2();
int checkBlack(int x , int y );
void promotionB(int r2, int c2);
int *pawnBlack(int r1,int c1);
int *rookB(int r1, int c1);
int *knightB(int r1, int c1);
int *bishopB(int r1, int c1);
int *queenB(int r1, int c1);
int checkNearbyWKing(int r2, int c2);
int *kingB(int r1, int c1);
void printAvilableB(int *available);
int checkB();
int checkmateB();
int stalemateB();



//Variables used through the game
int turn;  //This variable use to determine which player turn is it and switch the turns (If it is divisible by 2 then it's white player turn, else it's black)
int checker; //Use in check functions to see whether the king is checked or not to print out the check message (if checker equals 1 then the king is checked)
char letters[]= {'A','B','C','D','E','F','G','H'}; //This array of letters is used to print available places on the screen for the user after choosing a piece
char board[8][8]; //The board of the chess which take its values from outer file
int takesIndex1; //The index of the pieces that have taken from white player
int takesIndex2; //The index of the pieces that have taken from black player
int indexes[4];  //Array of indexes that use in save and load functions
char player1TakenOutPieces[15];
char player2TakenOutPieces[15];
char temp; //Variable use during the game as a place holder to switch places
char history[5000]; //The moves of the game for the undo and redo
int undoIndex;


int main()
{
    while(1)
    {
        //Preparing The Main Menu Interface of The Game
        mainmenu:
        system("@cls||clear"); //Clear The Screen
        printInterface(); //Print The Shapes of The Main Menu
        printf("\x1b[31m"); printf("\t 1-");printf("\x1b[0m");printf("New Game\n\n");
        printf("\x1b[31m"); printf("\t 2-");printf("\x1b[0m");printf("Load Game\n\n");
        printf("\x1b[31m"); printf("\t 3-");printf("\x1b[0m");printf("Rules and User Manual\n\n");
        printf("\x1b[31m"); printf("\t 4-");printf("\x1b[0m");printf("Exit\n\n");
        printf("Input: ");
        char input[10];
        scanf("%s", &input);  //Take The option from the user
        //New Game
        if(strcmp(input, "1") == 0)
        {
                newGame();
                while(1)
                {
                    int s;  // Variable use to save the out put of player 1 and player 2 functions to test them
                    system("@cls||clear");//Clear The Screen
                    if( turn%2 ==0)
                    {
                        s = player1();
                        if(s == 1) //If player 1 functions returns 1 then the player choose to go back to the main menu
                        {
                            goto mainmenu;
                        }
                        else if(s==0) // If it returns 0 then the game ended in stalemate or checkmate
                        {
                            printf("U if you want to undo| 0 to Go To Mainmenu : ");
                            char r[10];
                            scanf("%s", &r);
                            if(strcmp(r, "U") == 0)
                            {
                                if (undoIndex != 0)
                                {
                                    if(history[undoIndex-3] != ' ')
                                    {
                                        takesIndex2--;
                                        player2TakenOutPieces[takesIndex2] = ' ';
                                    }
                                    undo();
                                    turn++;
                                }
                            }
                            else if (strcmp(r, "0") == 0) goto mainmenu;
                        }
                    }
                    else
                    {
                        s = player2();
                        if(s== 1) //If player 2 functions returns 1 then the player choose to go back to the main menu
                        {
                            goto mainmenu;
                        }
                        else if(s==0) // If it returns 0 then the game ended in stalemate or checkmate
                        {
                            printf("U if you want to undo| 0 to Go To Mainmenu : ");
                            char r[10];
                            scanf("%s", &r);
                            if(strcmp(r, "U") == 0)
                            {
                                if (undoIndex != 0)
                                {
                                    if(history[undoIndex-3] != ' ')
                                    {
                                        takesIndex1--;
                                        player1TakenOutPieces[takesIndex1] = ' ';
                                    }
                                    undo();
                                    turn++;
                                }
                            }
                            else if (strcmp(r, "0") == 0) goto mainmenu;

                        }
                    }
                }
        }
        //Load
        else if (strcmp(input, "2") == 0)
        {
                load();
                while(1)
                {
                    int s;
                    system("@cls||clear");//Clear The Screen
                    if( turn%2 ==0)
                    {
                        s = player1();
                        if(s== 1)
                        {
                            goto mainmenu;
                        }
                        else if(s==0)
                        {
                            printf("U if you want to undo| 0 to Go To Mainmenu : ");
                            char r[10];
                            scanf("%s", &r);
                            if(strcmp(r, "U") == 0)
                            {
                                if (undoIndex != 0)
                                {
                                    if(history[undoIndex-3] != ' ')
                                    {
                                        takesIndex2--;
                                        player2TakenOutPieces[takesIndex2] = ' ';
                                    }
                                    undo();
                                    turn++;
                                }
                            }
                            else if (strcmp(r, "0") == 0) goto mainmenu;
                        }
                    }
                    else
                    {
                        s = player2();
                        if(s== 1)
                        {
                            goto mainmenu;
                        }
                        else if(s==0)
                        {
                            printf("U if you want to undo| 0 to Go To Mainmenu : ");
                            char r[10];
                            scanf("%s", &r);
                            if(strcmp(r, "U") == 0)
                            {
                                if (undoIndex != 0)
                                {
                                    if(history[undoIndex-3] != ' ')
                                    {
                                        takesIndex1--;
                                        player1TakenOutPieces[takesIndex1] = ' ';
                                    }
                                    undo();
                                    turn++;
                                }
                            }
                            else if (strcmp(r, "0") == 0) goto mainmenu;
                        }
                    }
                }
        }
        //Open The Manual And The Rules
        else if (strcmp(input, "3") == 0)
        {
                system("@cls||clear");//Clear The Screen
                printRules();
                getch();
        }
        //Exit The Game
        else if (strcmp(input, "4") == 0)
        {
                return 0;
        }
        //If user choose invalid input
        else
        {
            goto mainmenu;
        }
    }
}


//This Function prints the interface of the main menu of the game
void printInterface()
{
        printf("\t       _\n");
        printf("\t   ___| |__  ");printf("\x1b[31m");printf(" ___");printf("\x1b[0m");printf("  ___ ___ \n");
        printf("\t  / __| '_ \\ ");printf("\x1b[31m");printf("/ _ \\");printf("\x1b[0m");printf("/ __/ __|\n");
        printf("\t | (__| | | |");printf("\x1b[31m");printf("  __/");printf("\x1b[0m");printf("\\__ \\__ \\\n");
        printf("\t  \\___|_| |_|");printf("\x1b[31m");printf("\\___|");printf("\x1b[0m");printf("|___/___/\n");
        printf("\t         ,....,\n");
        printf("\t      ,::::::<\n");
        printf("\t     ,::/^\"``.\n");
        printf("\t    ,::/, `   ");printf("\x1b[31m");printf("e");printf("\x1b[0m");printf("`.\n");
        printf("\t   ,::; |        '.\n");
        printf("\t   ,::|  \___,-.  c)\n");
        printf("\t   ;::|     \   '-'\n");
        printf("\t   ;::|      \\\n");
        printf("\t   ;::|   _.=`\\\n");
        printf("\t   `;:|.=` _.=`\\\n");
        printf("\t     '|_.=`   __\\\n");
        printf("\t     `\_..==`` /\n");
        printf("\t      .'.___.-'.\n");
        printf("\t     /          \\\n");
        printf("\x1b[31m");
        printf("\t    ('--......--')\n");
        printf("\t    /'--......--'\\\n");
        printf("\t    `'--......--'    \n");
        printf("\x1b[0m");
}

//This Function prints the rules and the manuals of the game if the user chooses so
void printRules()
{
    printf("First it is better for the user or the player to full screen for better use and to see the whole board without any missordering.\n");
    printf("The user could start a new game or resume last game from the main menu interface.\n");
    printf("The player chooses the coordinates of the piece that he wishes to move by typing the letter (capital or small) of the column followed by the number of the row.\n");
    printf("Ex. (A2)        | |  |        |        |        |  ");
    printf("\n\t\t+-+  +--------|--------|--------|--");
    printf("\n\t\t|3|  |        |        |        |  ");
    printf("\n\t\t| |  |        |        |        |  ");
    printf("\n\t\t+-+  +--------|--------|--------|--");
    printf("\n\t\t|2|  |  Pawn  |  Pawn  |  Pawn  |  ");
    printf("\n\t\t| |  |    W   |    W   |    W   |  ");
    printf("\n\t\t+-+  +--------|--------|--------|--");
    printf("\n\t\t|1|  |  Rook  | knight | Bishop |  ");
    printf("\n\t\t| |  |    W   |    W   |    W   |  ");
    printf("\n\t\t+-+  +--------|--------|--------|--");
    printf("\n\t\t     +--------+--------+--------+--");
    printf("\n\t\t     |    A   |    B   |    C   |  ");
    printf("\n\t\t     +--------+--------+--------+--");
    printf("\n\t\tEnter The First Position (U To Undo |R To Redo |0 To Go To Mainmenu): A2\n\n");
    printf("((Press Enter To Continue))");
    getch();
    system("@cls||clear");
    printf("\nThen the game shows the available positions for this piece if there is by showing these positions on the board and print them under the board");
    printf("\nAnd then you And then you enter the second position in same way.");
    printf("\n\t\t| |  |");printf("\x1b[31m"); printf("########"); printf("\x1b[0m");printf("|        |        |  ");
    printf("\n\t\t+-+  +--------|--------|--------|--");
    printf("\n\t\t|3|  |");printf("\x1b[31m"); printf("########"); printf("\x1b[0m");printf("|        |        |  ");
    printf("\n\t\t| |  |");printf("\x1b[31m"); printf("########"); printf("\x1b[0m");printf("|        |        |  ");
    printf("\n\t\t+-+  +--------|--------|--------|--");
    printf("\n\t\t|2|  |  Pawn  |  Pawn  |  Pawn  |  ");
    printf("\n\t\t| |  |    W   |    W   |    W   |  ");
    printf("\n\t\t+-+  +--------|--------|--------|--");
    printf("\n\t\t|1|  |  Rook  | knight | Bishop |  ");
    printf("\n\t\t| |  |    W   |    W   |    W   |  ");
    printf("\n\t\t+-+  +--------|--------|--------|--");
    printf("\n\t\t     +--------+--------+--------+--");
    printf("\n\t\t     |    A   |    B   |    C   |  ");
    printf("\n\t\t     +--------+--------+--------+--");
    printf("\n\t\tAvailable Moves Are:");
    printf("\n\t\t((A3))((A4))");
    printf("\n\t\tEnter The Second Position(Press 00 to change the piece):\n\n");
    printf("((Press Enter To Continue))");
    getch();
    system("@cls||clear");
    printf("\nThe game will refuse any trivial input or invalid input that crashes the rules of the game.");
    printf("\n\t\t| |  |");printf("\x1b[31m"); printf("########"); printf("\x1b[0m");printf("|        |        |  ");
    printf("\n\t\t+-+  +--------|--------|--------|--");
    printf("\n\t\t|3|  |");printf("\x1b[31m"); printf("########"); printf("\x1b[0m");printf("|        |        |  ");
    printf("\n\t\t| |  |");printf("\x1b[31m"); printf("########"); printf("\x1b[0m");printf("|        |        |  ");
    printf("\n\t\t+-+  +--------|--------|--------|--");
    printf("\n\t\t|2|  |  Pawn  |  Pawn  |  Pawn  |  ");
    printf("\n\t\t| |  |    W   |    W   |    W   |  ");
    printf("\n\t\t+-+  +--------|--------|--------|--");
    printf("\n\t\t|1|  |  Rook  | knight | Bishop |  ");
    printf("\n\t\t| |  |    W   |    W   |    W   |  ");
    printf("\n\t\t+-+  +--------|--------|--------|--");
    printf("\n\t\t     +--------+--------+--------+--");
    printf("\n\t\t     |    A   |    B   |    C   |  ");
    printf("\n\t\t     +--------+--------+--------+--");
    printf("\n\t\tAvailable Moves Are: ");
    printf("\n\t\t((A3))((A4))");
    printf("\n\t\tEnter The Second Position(Press 00 to change the piece): A5\n");
    printf("\x1b[31m"); printf("\n\t\tInvalid Position\n"); printf("\x1b[0m");
    printf("\n\t\tEnter The Second Position(Press 00 to change the piece):\n\n");
    printf("The player can change the piece he has chosen by enter 00\n");
    printf("The player can undo his move any time by entering U and can redo by entering U and note that the game can undo to the first move.");
    printf("\n((Press Enter To Go To main menu))");
}

//This Function prints the word on the board(In printBoard Function) instead of letter for better visual
void printWord(char piece)
{
   switch(piece)
    {
        case 'p':
        case 'P':
                  printf("  Pawn  ");
                  break;
        case 'r':
        case 'R':
                  printf("  Rook  ");
                  break;
        case 'n':
        case 'N':
                  printf(" knight ");
                  break;
        case 'b':
        case 'B':
                  printf(" Bishop ");
                  break;
        case 'k':
        case 'K':
                  printf("  King  ");
                  break;
        case 'q':
        case 'Q':
                  printf(" Queen  ");
                  break;
        default:
                  printf("        ");
    }
}

//This Function change colors of console and I use it to Highlight the console to show white places in board in suitable way(In printBoard Function)
void SetColorAndBackground(int ForC, int BackC)
{
     WORD wColor = ((BackC & 0x0F) << 4) + (ForC & 0x0F);;
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
     return;
}

//This Function prints letter B for black for W for white under the piece on the board(In printBoard Function)
void blackOrWhite(char piece)
{
    if (piece==' ') printf("        ");
    else if(piece >= 'A' && piece <= 'Z') printf("    B   ");
    else if(piece >= 'a' && piece <= 'z') printf("    W   ");
}

//This Function prints the board on the screen in suitable shape
void printBoard()
{
    int s =0;
    SetColorAndBackground(15,0);
    printf("     +--------+--------+--------+--------+--------+--------+--------+--------+           +-----------------+\n");
    printf("     |    A   |    B   |    C   |    D   |    E   |    F   |    G   |    H   |           |  Removed Pieces |\n");
    printf("     +--------+--------+--------+--------+--------+--------+--------+--------+           |-----------------|\n");
    printf("+-+  +--------|--------|--------|--------|--------|--------|--------|--------+  +-+      |                 |\n");
    int t = 0;
    for(int k=8 ; k>0 ; k-- )
    {
        printf("|%d|  " , k );
        for(int j=0 ; j<8 ; j++ )
            {
                SetColorAndBackground(15,0);
                printf("|");
                if(t%2==0){SetColorAndBackground(0,15); printWord(board[8-k][j]);}
                else{SetColorAndBackground(15,0); printWord(board[8-k][j]);}
                t++;
            }
        SetColorAndBackground(15,0);
        printf("|"); printf("  |%d|      |" , k );printWord(player1TakenOutPieces[s]);printf("|");printWord(player2TakenOutPieces[s]);printf("|\n");
        printf("| |  ");
        for(int j=0 ; j<8 ; j++ )
            {
                SetColorAndBackground(15,0);
                printf("|");
                if(t%2==0){SetColorAndBackground(0,15); blackOrWhite(board[8-k][j]);}
                else{SetColorAndBackground(15,0); blackOrWhite(board[8-k][j]);}
                t++;
            }
        SetColorAndBackground(15,0);
        printf("|"); printf("  | |      |");blackOrWhite(player1TakenOutPieces[s]);printf("|");blackOrWhite(player2TakenOutPieces[s]);printf("|\n");s++;
        printf("+-+  +--------|--------|--------|--------|--------|--------|--------|--------+  +-+      |-----------------|\n");
        t++;
    }

    printf("     +--------+--------+--------+--------+--------+--------+--------+--------+           ");printf("\x1b[31m");printf("*******************\n");printf("\x1b[0m");
    printf("     |    A   |    B   |    C   |    D   |    E   |    F   |    G   |    H   |           ");printf("\x1b[31m");printf("*"); if(turn%2==0){SetColorAndBackground(4,15); printf("White Player Turn"); ;} else{SetColorAndBackground(4,0); printf("Black Player Turn");} SetColorAndBackground(15,0); printf("\x1b[31m"); printf("*");printf("\x1b[0m"); printf("\n");
    printf("     +--------+--------+--------+--------+--------+--------+--------+--------+           ");printf("\x1b[31m");printf("*******************\n");printf("\x1b[0m");
    if (checkmate()==3 || checkmateB()==3)
    {
            MessageBox(0,"Checkmate","End Of The Game",0);
    }
    else if (stalemate()==3 || stalemateB()==3)
    {
        MessageBox(0,"Stalemat","End Of The Game",0);
    }
    else if (check()==1 || checkB()==1)
    {
        printf("\x1b[31m"); printf("****Check****\n"); printf("\x1b[0m");
    }
}


//This Function prints # on the board to show the player the available places after choosing the piece(In printAvailableBoard Function)
void printWordAvailabe(char piece)
{
    switch(piece)
    {
        case 'p':
        case 'P':
                  printf("\x1b[31m"); printf("##Pawn##"); printf("\x1b[0m");
                  break;
        case 'r':
        case 'R':
                  printf("\x1b[31m"); printf("##Rook##"); printf("\x1b[0m");
                  break;
        case 'n':
        case 'N':
                  printf("\x1b[31m"); printf("#knight#"); printf("\x1b[0m");
                  break;
        case 'b':
        case 'B':
                  printf("\x1b[31m"); printf("#Bishop#"); printf("\x1b[0m");
                  break;
        case 'k':
        case 'K':
                  printf("\x1b[31m"); printf("##King##"); printf("\x1b[0m");
                  break;
        case 'q':
        case 'Q':
                  printf("\x1b[31m"); printf("#Queen##"); printf("\x1b[0m");
                  break;
        default:
                  printf("\x1b[31m"); printf("########"); printf("\x1b[0m");
    }
}

//This Function prints letter B for black for W for white under the piece on the available board(In printAvilabeBoard Function)
void blackOrWhiteAvailable(char piece)
{
    if (piece==' ') { printf("\x1b[31m"); printf("########"); printf("\x1b[0m");}
    else if(piece >= 'A' && piece <= 'Z') { printf("\x1b[31m"); printf("####B###"); printf("\x1b[0m");}
    else if(piece >= 'a' && piece <= 'z') { printf("\x1b[31m"); printf("####W###"); printf("\x1b[31m");}
}

//This Function prints the board to show the player the available places after choosing the piece
void printAvailableBoard(int *available)
{
    SetColorAndBackground(15,0);
    int t =0;
    printf("     +--------+--------+--------+--------+--------+--------+--------+--------+\n");
    printf("     |    A   |    B   |    C   |    D   |    E   |    F   |    G   |    H   |\n");
    printf("     +--------+--------+--------+--------+--------+--------+--------+--------+\n");
    printf("+-+  +--------|--------|--------|--------|--------|--------|--------|--------+  +-+\n");
    for(int k=8 ; k>0 ; k-- )
    {
        printf("|%d|  " , k );
        for(int j=0 ; j<8 ; j++ )
            {
                int q=1;
                for(int i = 0 ; i<52; i+=2)
                {
                    if (available[i]==-1)
                    {
                        break;
                    }
                    else if (available[i]== 8-k && available[i+1]== j)
                    {
                        SetColorAndBackground(15,0);
                        printf("|");
                        if(t%2==1) SetColorAndBackground(0,15);
                        printWordAvailabe(board[8-k][j]);
                        q=0;
                        i+=2;
                        break;
                    }
                }
                if (q)
                {
                    SetColorAndBackground(15,0);
                    printf("|");
                    if(t%2==0){SetColorAndBackground(15,0); printWord(board[8-k][j]);}
                    else{SetColorAndBackground(0,15); printWord(board[8-k][j]);}
                }
                t++;
            }
        SetColorAndBackground(15,0);
        printf("|"); printf("  |%d|\n" , k );
        printf("| |  ");
        for(int j=0 ; j<8 ; j++ )
            {
                int q=1;
                for(int i = 0 ; i<52; i+=2)
                {
                    if (available[i]==-1)
                    {
                        break;
                    }
                    else if (available[i]== 8-k && available[i+1]== j)
                    {
                        SetColorAndBackground(15,0);
                        printf("|");
                        if(t%2==1) SetColorAndBackground(0,15);
                        blackOrWhiteAvailable(board[8-k][j]);
                        q=0;
                        i+=2;
                        break;
                    }
                }
                if (q)
                {
                    SetColorAndBackground(15,0);
                    printf("|");
                    if(t%2==0){SetColorAndBackground(15,0); blackOrWhite(board[8-k][j]);}
                    else{SetColorAndBackground(0,15); blackOrWhite(board[8-k][j]);}
                }
                t++;
            }
        SetColorAndBackground(15,0);
        printf("|"); printf("  | |\n");
        printf("+-+  +--------|--------|--------|--------|--------|--------|--------|--------+  +-+\n");
        t++;
    }

    printf("     +--------+--------+--------+--------+--------+--------+--------+--------+\n");
    printf("     |    A   |    B   |    C   |    D   |    E   |    F   |    G   |    H   |\n");
    printf("     +--------+--------+--------+--------+--------+--------+--------+--------+\n");

}

//This Function moves the chosen piece if the new position is valid for it according to the available positions parameter that it takes
int change( int r1 , int c1 , int r2 , int c2, int *available)
{
    for(int i = 0 ; i<52; i+=2)
    {
        if (available[i]==-1)
        {
            break;
        }
        else
        {
            if (r2==available[i] && c2==available[i+1])
            {
                temp = board[r2][c2];
                board[r2][c2] = board[r1][c1] ;
                board[r1][c1] = ' ' ;
                return 1;
            }
            if (available[i] == -1)
            {
                break;
            }
        }
    }
    return 0;
}

//This Function is used to sort array (used in stalemate functions)
void sort(int size, char x[])
   {
       int i, j, t;

       for(i = 1; i <= size-1; i++)
          for(j = 1; j <= size-i; j++)
             if(x[j-1] >= x[j])
             {
                t = x[j-1];
                x[j-1] = x[j];
                x[j] = t;
             }
   }

//This Function is used to compare two array (used in stalemate functions)
int compareArray(char a[],char b[],int size)
{
	int i;
	for(i=0;i<size;i++)
    {
		if(a[i]!=b[i])
			return 0;
	}
	return 1;
}

//This function saves each part of game in text files to load it later (including all moves to undo and redo the game any time)
void save()
{
    FILE *fp;
    fp = fopen("Load.txt", "wb");
    fwrite(board, sizeof(char),64,fp);
    fclose(fp);

    FILE *fk;
    fk = fopen("RemovedPiecesFromPlayer1.txt", "wb");
    fwrite(player1TakenOutPieces, sizeof(char),15,fk);
    fclose(fk);

    FILE *fl;
    fl = fopen("RemovedPiecesFromPlayer2.txt", "wb");
    fwrite(player2TakenOutPieces, sizeof(char),15,fl);
    fclose(fl);

    indexes[0] = turn;
    indexes[1] = takesIndex1;
    indexes[2] = takesIndex2;
    indexes[3] = undoIndex;
    FILE *fq;
    fq = fopen("Indexes.txt", "wb");
    fwrite(indexes, sizeof(int),3,fq);
    fclose(fq);


    FILE *fc;
    fc = fopen("History.txt", "wb");
    fwrite(history, sizeof(char),5000,fc);
    fclose(fc);
}

//This function load the game from last point
void load()
{
    FILE *fp;
    fp = fopen("Load.txt", "rb");
    fread(board, sizeof(char),64,fp);
    fclose(fp);

    FILE *fk;
    fk = fopen("RemovedPiecesFromPlayer1.txt", "rb");
    fread(player1TakenOutPieces, sizeof(char),15,fk);
    fclose(fk);

    FILE *fl;
    fl = fopen("RemovedPiecesFromPlayer2.txt", "rb");
    fread(player2TakenOutPieces, sizeof(char),15,fl);
    fclose(fl);

    FILE *fq;
    fq = fopen("Indexes.txt", "rb");
    fread(indexes, sizeof(int),3,fq);
    fclose(fq);

    FILE *fc;
    fc = fopen("History.txt", "rb");
    fread(history, sizeof(char),5000,fc);
    fclose(fc);

    turn = indexes[0];
    takesIndex1 = indexes[1];
    takesIndex2 = indexes[2];
    undoIndex = indexes[3];
}

//This function prepare the board and every index for new game
void newGame()
{
    turn = 0;
    FILE *fp;
    fp = fopen("NewGame.txt", "rb");
    fread(board, sizeof(char),64,fp);
    fclose(fp);
    for(int i =0; i<14; i++)
    {
        player1TakenOutPieces[i] = ' ';
        player2TakenOutPieces[i] = ' ';
    }

    for(int i =0; i<5000; i++)
    {
        history[i] = ' ';
    }
    takesIndex1=0;
    takesIndex2=0;
    undoIndex = 0;

}


void undo()
{
    board[history[undoIndex-5]-'0'][history[undoIndex-4]-'0'] = history[undoIndex-6];
    board[history[undoIndex-2]-'0'][history[undoIndex-1]-'0'] = history[undoIndex-3];
    undoIndex= undoIndex-6;

}

void redo()
{
    board[history[undoIndex+1]-'0'][history[undoIndex+2]-'0'] = ' ';
    board[history[undoIndex+4]-'0'][history[undoIndex+5]-'0'] = history[undoIndex];
    undoIndex= undoIndex+6;

}




//////Player 1 functions\\\\\\



//This function returns 1 if there is black piece in the available moves of the white piece to show that the white piece can eat it (used in all pieces functions)
int checkWhite(int x , int y )
{
    switch( board[x][y] )
    {
    case 'P': return 1 ; break ;
    case 'R': return 1 ; break ;
    case 'N': return 1 ; break ;
    case 'B': return 1 ; break ;
    case 'K': return 1 ; break ;
    case 'Q': return 1 ; break ;
    default: return 0 ;
    }
}


void promotion(int r2, int c2)
{
    MessageBox(0,"This pawn will promote","Promotion",0);
    printf("\x1b[31m"); printf("Choose Desired Piece( (Q)Queen | (B)Bishop | (N)Knight| (R)Rook ) : "); printf("\x1b[0m");
    char desired;
    again:
    scanf(" %c", &desired);
    switch(desired)
    {
        case 'R':
                  board[r2][c2] = 'r';
                  break;
        case 'N':
                  board[r2][c2] = 'n';
                  break;
        case 'B':
                  board[r2][c2] = 'b';
                  break;
        case 'Q':
                  board[r2][c2] = 'q';
                  break;
        default:
                  printf("\nInvalid Input Choose Again : ");
                  goto again;
    }
}

int *pawnWhite(int r1,int c1)
{
   int i = 0;
   static int arr[52];
   for(int j = 0; j<52; j++) arr[j] = -1;

   if( board[r1-1][c1] == ' ' && r1>0)
        {
            arr[i]= r1-1;
            arr[i+1]=c1;
            i+=2;
        }

   if(r1 == 6 && board[r1-1][c1] == ' ' && board[r1-2][c1] == ' ')
    {
            arr[i]= r1-2;
            arr[i+1]=c1;
            i+=2;
    }

    if(checkWhite(r1-1 , c1-1) && r1>0 && c1>0)
    {
        arr[i]= r1-1;
        arr[i+1]=c1-1;
        i+=2;
    }

    if(checkWhite(r1-1 , c1+1) && r1>0 && c1<7)
    {
        arr[i]= r1-1;
        arr[i+1]=c1+1;
        i+=2;
    }
    return arr;

}

int* rook( int r1 , int c1 )
{
    int i=0 , n;
    static int arr[52];
    for(int j = 0; j<52; j++) arr[j] = -1;
    n=c1;
    //Horizontal
    while( board[r1][n-1] == ' ' && n >0 )
    {
        arr[i]=r1;
        arr[i+1]=n-1;
        i+=2;
        n-- ;
    }

    if(checkWhite(r1 , (n==0)?0:n-1))
    {
        arr[i]= r1;
        arr[i+1]=n-1;
        i+=2;
    }


    n=c1 ;
    while( board[r1][n+1] == ' '  && n < 7 )
    {
        arr[i]= r1;
        arr[i+1]=n+1;
        n++ ;
        i+=2 ;
    }

    if(checkWhite(r1 , (n==7)?7:n+1))
    {
        arr[i]= r1;
        arr[i+1]=n+1;
        i+=2;
    }


    //Vertical
    n = r1 ;
    while( board[n-1][c1] == ' ' && n > 0 )
    {
        arr[i]=n-1;
        arr[i+1]=c1;
        n--;
        i+=2;
    }

    if(checkWhite((n==0)?0:n-1 , c1))
    {
        arr[i]= n-1;
        arr[i+1]=c1;
        i+=2;
    }


    n = r1 ;
    while( board[n+1][c1] == ' ' &&  n < 7  )
    {
        arr[i]= n+1;
        arr[i+1]=c1;
        i+=2;
        n++;
    }

    if(checkWhite((n==7)?7:n+1 , c1))
    {
        arr[i]= n+1;
        arr[i+1]=c1;
        i+=2;
    }

    return arr;
}

int *knight( int r1 , int c1 )
{
    int i=0;
    static int arr[52];
    for(int j = 0; j<52; j++) arr[j] = -1;

    //1
    if( (board[r1+2][c1+1] == ' ' || checkWhite(r1+2 , c1+1) ==1) && r1<6 && c1<7 )
    {
            arr[i]= r1+2;
            arr[i+1]=c1+1;
            i+=2;
    }

    //2
    if( (board[r1+2][c1-1] == ' ' || checkWhite(r1+2 , c1-1) ==1) && c1>0 && r1<6 )
    {
            arr[i]= r1+2;
            arr[i+1]=c1-1;
            i+=2;
    }

    //3
    if( (board[r1+1][c1+2] == ' ' || checkWhite(r1+1 , c1+2) ==1) && c1 <6 && r1<7 )
    {
            arr[i]= r1+1;
            arr[i+1]=c1+2;
            i+=2;
    }

    //4
    if( (board[r1-1][c1+2] == ' ' || checkWhite(r1-1 , c1+2) ==1) && c1 <6 && r1>0  )
    {
            arr[i]= r1-1;
            arr[i+1]=c1+2;
            i+=2;
    }

    //5
    if( (board[r1-2][c1-1] == ' ' || checkWhite(r1-2 , c1-1) ==1) && c1 >0 && r1>1 )
    {
            arr[i]= r1-2;
            arr[i+1]=c1-1;
            i+=2;
    }

    //6
    if( (board[r1-2][c1+1] == ' ' || checkWhite(r1-2 , c1+1) ==1) && c1 <7 && r1>1 )
    {
            arr[i]= r1-2;
            arr[i+1]=c1+1;
            i+=2;
    }

    //7
    if( (board[r1+1][c1-2] == ' ' || checkWhite(r1+1 , c1-2) ==1) && c1 >1 && r1<7 )
    {
            arr[i]= r1+1;
            arr[i+1]=c1-2;
            i+=2;
    }

    //8
    if( (board[r1-1][c1-2] == ' ' || checkWhite(r1-1 , c1-2) ==1) && c1 >1 && r1>0 )
    {
            arr[i]= r1-1;
            arr[i+1]=c1-2;
            i+=2;
    }
    return arr;
}

int *bishop(int r1, int c1)
{
    int i =0, a, b;
    static int arr[52];
    for(int j = 0; j<52; j++) arr[j] = -1;


    a = 1, b = 1 ;
    while( (board[r1-a][c1+b] == ' ' || checkWhite(r1-a, c1+b)==1) && r1-a>-1 && c1+b<8 )
    {
        arr[i]= r1-a;
        arr[i+1]=c1+b;
        i+=2;
        if(checkWhite(r1-a , c1+b)==1) break;
        a++ ;
        b++ ;
    }


    a = 1, b = 1 ;
    while( (board[r1+a][c1-b] == ' ' || checkWhite(r1+a, c1-b)==1) && r1+a<8 && c1-b>-1)
    {
        arr[i]= r1+a;
        arr[i+1]=c1-b;
        i+=2;
        if(checkWhite(r1+a , c1-b)==1) break;
        a++ ;
        b++ ;
    }

    a = 1, b = 1 ;
    while( (board[r1+a][c1+b] == ' ' || checkWhite(r1+a, c1+b)==1) && r1+a<8 && c1+b<8)
    {
        arr[i]= r1+a;
        arr[i+1]=c1+b;
        i+=2;
        if(checkWhite(r1+a , c1+b)==1) break;
        a++ ;
        b++ ;
    }

    a = 1, b = 1 ;
    while( (board[r1-a][c1-b] == ' ' || checkWhite(r1-a, c1-b)==1) && r1-a>-1 && c1-b>-1)
    {
        arr[i]= r1-a;
        arr[i+1]=c1-b;
        i+=2;
        if(checkWhite(r1-a , c1-b)==1) break;
        a++ ;
        b++ ;
    }

    return arr;
}

int *queen(int r1,int c1)
{
    int i =0, n, a, b;
    static int arr[52];
    for(int j = 0; j<52; j++) arr[j] = -1;

    n=c1;
    while( board[r1][n-1] == ' ' && n >0 )
    {
        arr[i]=r1;
        arr[i+1]=n-1;
        i+=2;
        n-- ;
    }
    if( checkWhite(r1 , (n==0)?0:n-1 ) )
    {
        arr[i]= r1;
        arr[i+1]=n-1;
        i+=2;
    }


    n=c1 ;
    while( board[r1][n+1] == ' '  && n < 7 )
    {
        arr[i]= r1;
        arr[i+1]=n+1;
        n++ ;
        i+=2 ;
    }
    if(checkWhite(r1 , (n==7)?7:n+1))
    {
        arr[i]= r1;
        arr[i+1]=n+1;
        i+=2;
    }


    n = r1 ;
    while( board[n-1][c1] == ' ' && n > 0 )
    {
        arr[i]=n-1;
        arr[i+1]=c1;
        n--;
        i+=2;
    }
    if(checkWhite((n==0)?0:n-1 , c1))
    {
        arr[i]= n-1;
        arr[i+1]=c1;
        i+=2;
    }

    n = r1 ;

    while( board[n+1][c1] == ' ' &&  n < 7  )
    {
        arr[i]= n+1;
        arr[i+1]=c1;
        i+=2;
        n++;
    }
    if(checkWhite((n==7)?7:n+1 , c1))
    {
        arr[i]= n+1;
        arr[i+1]=c1;
        i+=2;
    }

    a = 1, b = 1 ;
    while( (board[r1-a][c1+b] == ' ' || checkWhite(r1-a, c1+b)==1) && r1-a>-1 && c1+b<8 )
    {
        arr[i]= r1-a;
        arr[i+1]=c1+b;
        i+=2;
        if(checkWhite(r1-a , c1+b)==1) break;
        a++ ;
        b++ ;
    }


    a = 1, b = 1 ;
    while( (board[r1+a][c1-b] == ' ' || checkWhite(r1+a, c1-b)==1) && r1+a<8 && c1-b>-1)
    {
        arr[i]= r1+a;
        arr[i+1]=c1-b;
        i+=2;
        if(checkWhite(r1+a , c1-b)==1) break;
        a++ ;
        b++ ;
    }

    a = 1, b = 1 ;
    while( (board[r1+a][c1+b] == ' ' || checkWhite(r1+a, c1+b)==1) && r1+a<8 && c1+b<8)
    {
        arr[i]= r1+a;
        arr[i+1]=c1+b;
        i+=2;
        if(checkWhite(r1+a , c1+b)==1) break;
        a++ ;
        b++ ;
    }

    a = 1, b = 1 ;
    while( (board[r1-a][c1-b] == ' ' || checkWhite(r1-a, c1-b)==1) && r1-a>-1 && c1-b>-1)
    {
        arr[i]= r1-a;
        arr[i+1]=c1-b;
        i+=2;
        if(checkWhite(r1-a , c1-b)==1) break;
        a++ ;
        b++ ;
    }

    return arr;
}

//This Function checks all available positions for the white king to see if these positions are near to the black king if no this is place is valid (use in king function)
int checkNearbyBKing(int r2, int c2)
{
    if(board[r2][c2+1] == 'K' && c2<7 )
        {
            return 0;
        }
    else if(board[r2][c2-1] == 'K' && c2>0)
        {
            return 0;
        }
    else if(board[r2+1][c2] == 'K' && r2<7)
        {
            return 0;
        }
    else if(board[r2-1][c2] == 'K' && r2>0)
        {
            return 0;
        }
    else if(board[r2+1][c2+1] == 'K' && r2<7 && c2<7)
        {
            return 0;
        }
    else if(board[r2-1][c2-1] == 'K' && c2>0 && r2>0)
        {
            return 0;
        }
    else if(board[r2-1][c2+1] == 'K' && c2<7 &&r2>0)
        {
            return 0;
        }
    else if(board[r2+1][c2-1] == 'K' && r2<7 && c2>0)
        {
            return 0;
        }
    else
        {
            return 1;
        }

}

int *king(int r1, int c1)
{
    int i=0;
    static int arr[52];
    for(int j = 0; j<52; j++) arr[j] = -1;
    //1
    if( (board[r1][c1+1] == ' ' || checkWhite(r1, c1+1)== 1) && checkNearbyBKing(r1, c1+1)==1 && c1<7 )
        {
            arr[i]= r1;
            arr[i+1]=c1+1;
            i+=2;
        }
    //2
    if( (board[r1][c1-1] == ' ' || checkWhite(r1, c1-1)== 1) && checkNearbyBKing(r1, c1-1)==1 && c1>0 )
        {
            arr[i]= r1;
            arr[i+1]=c1-1;
            i+=2;
        }
    //3
    if( (board[r1+1][c1] == ' ' || checkWhite(r1+1, c1)== 1) && checkNearbyBKing(r1+1, c1)==1 && r1<7 )
        {
            arr[i]= r1+1;
            arr[i+1]=c1;
            i+=2;
        }
    //4
    if( (board[r1-1][c1] == ' ' || checkWhite(r1-1, c1)== 1) && checkNearbyBKing(r1-1, c1)==1 && r1>0)
        {
            arr[i]= r1-1;
            arr[i+1]=c1;
            i+=2;
        }
    //5
    if( (board[r1+1][c1+1] == ' ' || checkWhite(r1+1, c1+1)== 1) && checkNearbyBKing(r1+1, c1+1)==1 && r1<7 && c1<7)
        {
            arr[i]= r1+1;
            arr[i+1]=c1+1;
            i+=2;
        }
    //6
    if( (board[r1-1][c1-1] == ' ' || checkWhite(r1-1, c1-1)== 1) && checkNearbyBKing(r1-1, c1-1)==1 && c1>0 && r1>0)
        {
            arr[i]= r1-1;
            arr[i+1]=c1-1;
            i+=2;
        }
    //7
    if( (board[r1-1][c1+1] == ' ' || checkWhite(r1-1, c1+1)== 1) && checkNearbyBKing(r1-1, c1+1)==1 && c1<7 &&r1>0 )
        {
            arr[i]= r1-1;
            arr[i+1]=c1+1;
            i+=2;
        }
    //8
    if( (board[r1+1][c1-1] == ' ' || checkWhite(r1+1, c1-1)== 1) && checkNearbyBKing(r1+1, c1-1)==1 && r1<7 && c1>0)
        {
            arr[i]= r1+1;
            arr[i+1]=c1-1;
            i+=2;
        }

    return arr;
}

//This function print letters of the available moves for the chosen piece to player 1 (White)
void printAvailable(int *available)
{
    printf("Available Moves Are:\n");
    for(int i = 0 ; i<52; i+=2)
    {
        if (available[i]==-1)
        {
            break;
        }
        else
        {
             printf("((%c%i%s))" , letters[available[i+1]] ,8-(available[i]), (checkWhite(available[i] , available[i+1])==1)? "*":"");
        }
    }
}

//See if the white king is checked after each turn
int check()
{
    //find the position of the king
    int r;
    int c;
    for(int i =0; i< 8; i++)
    {
        for(int j =0; j<8 ; j++)
        {
            if(board[i][j]=='k')
            {
                r=i;
                c=j;
                break;
            }
        }
    }
    //Check if it is capture by pawn
    if(board[r-1][c+1] == 'P' || board[r-1][c-1]=='P')
    {
        return 1;
    }

    //Check if it is capture by knight
    if( board[r+2][c+1] == 'N' ||
        board[r+2][c-1] == 'N' ||
        board[r+1][c+2] == 'N' ||
        board[r-1][c+2] == 'N' ||
        board[r-2][c-1] == 'N' ||
        board[r-2][c+1] == 'N' ||
        board[r+1][c-2] == 'N' ||
        board[r-1][c-2] == 'N' )
    {
        return 1;
    }

    //Check if it is capture by rook or queen
    int n;
    n=c;
        //Horizontal
    while( board[r][n-1] == ' ' && n >0 )
    {
        n--;
    }
    if(board[r][(n==0)?0:n-1] =='R' || board[r][(n==0)?0:n-1] =='Q')
    {
        return 1;
    }

    n=c ;
    while( board[r][n+1] == ' '  && n < 7 )
    {
        n++ ;
    }
    if(board[r][(n==7)?7:n+1] == 'R' || board[r][(n==7)?7:n+1] == 'Q')
    {
        return 1;
    }

        //Vertical
    n = r;
    while( board[n-1][c] == ' ' && n > 0 )
    {
        n--;
    }
    if(board[(n==0)?0:n-1][c] == 'R' || board[(n==0)?0:n-1][c] == 'Q')
    {
        return 1;
    }

    n = r;
    while( board[n+1][c] == ' ' &&  n < 7  )
    {
        n++;
    }
    if(board[(n==7)?7:n+1][c]== 'R' || board[(n==7)?7:n+1][c]== 'Q')
    {
        return 1;
    }


    //Check if it is capture by bishop or queen
    int a, b;
    a = 1, b = 1 ;
    while( board[r-a][c+b] == ' ' && r-a>-1 && c+b<8 )
    {
        a++ ;
        b++ ;
    }
    if(board[r-a][c+b]=='B' || board[r-a][c+b]=='Q') return 1;


    a = 1, b = 1 ;
    while( board[r+a][c-b] == ' ' && r+a<8 && c-b>-1 )
    {
        a++ ;
        b++ ;
    }
    if(board[r+a][c-b]=='B' || board[r+a][c-b]=='Q') return 1;

    a = 1, b = 1 ;
    while( board[r+a][c+b] == ' ' && r+a<8 && c+b<8 )
    {
        a++ ;
        b++ ;
    }
    if(board[r+a][c+b]=='B' ||board[r+a][c+b]=='Q') return 1;

    a = 1, b = 1 ;
    while( board[r-a][c-b] == ' ' && r-a>-1 && c-b>-1 )
    {
        a++ ;
        b++ ;
    }
    if(board[r-a][c-b]=='B' || board[r-a][c-b]=='Q') return 1;




    return 0;




}

//See if the white king is checked and there is no way to escape so the game is end
int checkmate()
{
    char temp;
    int indicator;
    int c;
    int r[52]= { [ 0 ... 51 ] = -1 };
    if( check() == 1 )
    {
        checker = 1;
        for (int i = 0; i<8;i++)
        {
            for(int j =0; j<8; j++)
            {
                int *test = r;
                switch( board[i][j] )
                {
                    case 'p': test = pawnWhite(i,j);
                            break;
                    case 'r': test = rook(i,j);
                            break;
                    case 'n': test = knight(i,j);
                            break;
                    case 'b': test = bishop(i,j);
                            break;
                    case 'k': test = king(i,j);
                            break;
                    case 'q': test = queen(i,j);
                            break;
                    default : break;
                }
                for(int k =0; k<8; k++)
                {
                    for(int l =0; l<8; l++)
                    {
                        temp = board[k][l];
                        c = change(i,j,k,l, test);
                        if(c==1)
                        {
                            if (check()==1)
                            {
                                board[i][j] = board[k][l];
                                board[k][l] = temp;
                                indicator=3;
                            }
                            else
                            {
                                board[i][j] = board[k][l];
                                board[k][l] = temp;
                                indicator =2;
                                return indicator;
                                break;
                            }
                        }
                        else
                        {
                            indicator=3;
                        }
                    }
                }
            }
        }
        return indicator;
    }
    else
    {
        checker = 0;
    }
}

//See if the game ended stalemate
int stalemate()
{
    //Check all moves if the player is not in check and have no legal for move any piece then it is stalemate
    char temp;
    int indicator;
    int c;
    int r[52]= { [ 0 ... 51 ] = -1 };
    if( check() == 0 )
    {
        checker = 0;
        for (int i = 0; i<8;i++)
        {
            for(int j =0; j<8; j++)
            {
                int *test = r;
                switch( board[i][j] )
                {
                    case 'p': test = pawnWhite(i,j);
                            break;
                    case 'r': test = rook(i,j);
                            break;
                    case 'n': test = knight(i,j);
                            break;
                    case 'b': test = bishop(i,j);
                            break;
                    case 'k': test = king(i,j);
                            break;
                    case 'q': test = queen(i,j);
                            break;
                    default : break;
                }
                for(int k =0; k<8; k++)
                {
                    for(int l =0; l<8; l++)
                    {
                        temp = board[k][l];
                        c = change(i,j,k,l, test);
                        if(c==0)
                        {
                            indicator=3;
                        }
                        else if (c==1 && check()==1)
                        {
                            board[i][j] = board[k][l];
                            board[k][l] = temp;
                            indicator =3;
                        }
                        else
                        {
                            board[i][j] = board[k][l];
                            board[k][l] = temp;
                            indicator =2;
                        }
                        if(indicator ==2) break;
                    }
                    if(indicator ==2) break;
                }
                if(indicator ==2) break;
            }
            if(indicator ==2) break;
        }
    }

    //check if there are only (two kings  / two kings and one knight / two kings and one bishop)
    char remaining[3] ={' ', ' ', ' '};
    int pieces = 0;

    for(int i = 0; i<8; i++)
    {
        for(int j =0; j<8; j++)
        {
            if (board[i][j] != ' ')
            {
                if(pieces<4) {remaining[pieces] = board[i][j];}
                pieces++;
            }
        }
    }

    char case1[3] = {' ','K','k'};
    char case2[3] = {'K','k','n'};
    char case3[3] = {'K','N','k'};
    char case4[3] = {'B','K','k'};
    char case5[3] = {'K','b','k'};


    if (pieces<4)
    {
        sort(3,remaining);
        if(compareArray(remaining,case1,3) || compareArray(remaining,case2,3) || compareArray(remaining,case3,3)||compareArray(remaining,case4,3)||compareArray(remaining,case5,3))
            {
                indicator = 3;
            }

    }


    return indicator;

}




//////Player 2 functions\\\\\\


//This function returns 1 if there is white piece in the available moves of the black piece to show that the black piece can eat it (used in all pieces functions)
int checkBlack(int x , int y )
{
    switch( board[x][y] )
    {
    case 'p': return 1 ; break ;
    case 'r': return 1 ; break ;
    case 'n': return 1 ; break ;
    case 'b': return 1 ; break ;
    case 'k': return 1 ; break ;
    case 'q': return 1 ; break ;
    default: return 0 ;
    }
}


void promotionB(int r2, int c2)
{
    MessageBox(0,"This pawn will promote","Promotion",0);
    printf("\x1b[31m"); printf("Choose Desired Piece( (Q)Queen | (B)Bishop | (N)Knight| (R)Rook ) : "); printf("\x1b[0m");
    char desired;
    again:
    scanf(" %c", &desired);
    switch(desired)
    {
        case 'R':
                  board[r2][c2] = 'R';
                  break;
        case 'N':
                  board[r2][c2] = 'N';
                  break;
        case 'B':
                  board[r2][c2] = 'B';
                  break;
        case 'Q':
                  board[r2][c2] = 'Q';
                  break;
        default:
                  printf("\nInvalid Input Choose Again : ");
                  goto again;
    }
}

int *pawnBlack(int r1,int c1)
{
   int i = 0;
   static int arr[52];
   for(int j = 0; j<52; j++) arr[j] = -1;
   if( board[r1+1][c1] == ' ' && r1>0)
        {
            arr[i]= r1+1;
            arr[i+1]=c1;
            i+=2;
        }
   if(r1 == 1 && board[r1+1][c1] == ' ' && board[r1+2][c1] == ' ')
    {
            arr[i]= r1+2;
            arr[i+1]=c1;
            i+=2;
    }
    if(checkBlack(r1+1 , c1-1) && r1>0 && c1>0)
    {
        arr[i]= r1+1;
        arr[i+1]=c1-1;
        i+=2;
    }
    if(checkBlack(r1+1 , c1+1) && r1>0 && c1<7)
    {
        arr[i]= r1+1;
        arr[i+1]=c1+1;
        i+=2;
    }

    return arr;

}

int* rookB( int r1 , int c1 )
{
    int i=0 , n;
    static int arr[52];
    for(int j = 0; j<52; j++) arr[j] = -1;

    n=c1;
    //Horizontal
    while( board[r1][n-1] == ' ' && n >0 )
    {
        arr[i]=r1;
        arr[i+1]=n-1;
        i+=2;
        n-- ;
    }
    if(checkBlack(r1 , (n==0)?0:n-1))
    {
        arr[i]= r1;
        arr[i+1]=n-1;
        i+=2;
    }

    n=c1 ;
    while( board[r1][n+1] == ' '  && n < 7 )
    {

        arr[i]= r1;
        arr[i+1]=n+1;
        n++ ;
        i+=2 ;
    }
    if(checkBlack(r1 , (n==7)?7:n+1))
    {
        arr[i]= r1;
        arr[i+1]=n+1;
        i+=2;
    }

    //Vertical
    n = r1 ;
    while( board[n-1][c1] == ' ' && n > 0 )
    {
        arr[i]=n-1;
        arr[i+1]=c1;
        n--;
        i+=2;
    }
    if(checkBlack((n==0)?0:n-1 , c1))
    {
        arr[i]= n-1;
        arr[i+1]=c1;
        i+=2;
    }

    n = r1 ;

    while( board[n+1][c1] == ' ' &&  n < 7  )
    {
        arr[i]= n+1;
        arr[i+1]=c1;
        i+=2;
        n++;
    }
    if(checkBlack((n==7)?7:n+1 , c1))
    {
        arr[i]= n+1;
        arr[i+1]=c1;
        i+=2;
    }

    return arr;
}

int *knightB( int r1 , int c1 )
{
    int i=0;
    static int arr[52];
    for(int j = 0; j<52; j++) arr[j] = -1;

    //1
    if( (board[r1+2][c1+1] == ' ' || checkBlack(r1+2 , c1+1) ==1) && r1<6 && c1<7 )
    {
        arr[i]= r1+2;
        arr[i+1]=c1+1;
        i+=2;
    }

    //2
    if( (board[r1+2][c1-1] == ' ' || checkBlack(r1+2 , c1-1) ==1) && c1>0 && r1<6 )
    {
            arr[i]= r1+2;
            arr[i+1]=c1-1;
            i+=2;
    }

    //3
    if( (board[r1+1][c1+2] == ' ' || checkBlack(r1+1 , c1+2) ==1) && c1 <6 && r1<7 )
    {
            arr[i]= r1+1;
            arr[i+1]=c1+2;
            i+=2;
    }

    //4
    if( (board[r1-1][c1+2] == ' ' || checkBlack(r1-1 , c1+2) ==1) && c1 <6 && r1>0  )
    {
            arr[i]= r1-1;
            arr[i+1]=c1+2;
            i+=2;
    }

    //5
    if( (board[r1-2][c1-1] == ' ' || checkBlack(r1-2 , c1-1) ==1) && c1 >0 && r1>1 )
    {
            arr[i]= r1-2;
            arr[i+1]=c1-1;
            i+=2;
    }

    //6
    if( (board[r1-2][c1+1] == ' ' || checkBlack(r1-2 , c1+1) ==1) && c1 <7 && r1>1 )
    {
            arr[i]= r1-2;
            arr[i+1]=c1+1;
            i+=2;
    }

    //7
    if( (board[r1+1][c1-2] == ' ' || checkBlack(r1+1 , c1-2) ==1) && c1 >1 && r1<7 )
    {
            arr[i]= r1+1;
            arr[i+1]=c1-2;
            i+=2;
    }

    //8
    if( (board[r1-1][c1-2] == ' ' || checkBlack(r1-1 , c1-2) ==1) && c1 >1 && r1>0 )
    {
            arr[i]= r1-1;
            arr[i+1]=c1-2;
            i+=2;
    }

    return arr;
}

int *bishopB(int r1, int c1)
{
    int i =0, a, b;
    static int arr[52];
    for(int j = 0; j<52; j++) arr[j] = -1;

    a = 1, b = 1 ;
    while( (board[r1-a][c1+b] == ' ' || checkBlack(r1-a, c1+b)==1) && r1-a>-1 && c1+b<8 )
    {
        arr[i]= r1-a;
        arr[i+1]=c1+b;
        i+=2;
        if(checkBlack(r1-a , c1+b)==1) break;
        a++ ;
        b++ ;
    }


    a = 1, b = 1 ;
    while( (board[r1+a][c1-b] == ' ' || checkBlack(r1+a, c1-b)==1) && r1+a<8 && c1-b>-1)
    {
        arr[i]= r1+a;
        arr[i+1]=c1-b;
        i+=2;
        if(checkBlack(r1+a , c1-b)==1) break;
        a++ ;
        b++ ;
    }

    a = 1, b = 1 ;
    while( (board[r1+a][c1+b] == ' ' || checkBlack(r1+a, c1+b)==1) && r1+a<8 && c1+b<8)
    {
        arr[i]= r1+a;
        arr[i+1]=c1+b;
        i+=2;
        if(checkBlack(r1+a , c1+b)==1) break;
        a++ ;
        b++ ;
    }

    a = 1, b = 1 ;
    while( (board[r1-a][c1-b] == ' ' || checkBlack(r1-a, c1-b)==1) && r1-a>-1 && c1-b>-1)
    {
        arr[i]= r1-a;
        arr[i+1]=c1-b;
        i+=2;
        if(checkBlack(r1-a , c1-b)==1) break;
        a++ ;
        b++ ;
    }

    return arr;
}

int *queenB(int r1,int c1)
{
    int i =0, n, a, b;
    static int arr[52];
    for(int j = 0; j<52; j++) arr[j] = -1;

    n=c1;
    while( board[r1][n-1] == ' ' && n >0 )
    {
        arr[i]=r1;
        arr[i+1]=n-1;
        i+=2;
        n-- ;
    }
    if( checkBlack(r1 , (n==0)?0:n-1 ) )
    {
        arr[i]= r1;
        arr[i+1]=n-1;
        i+=2;
    }


    n=c1 ;
    while( board[r1][n+1] == ' '  && n < 7 )
    {

        arr[i]= r1;
        arr[i+1]=n+1;
        n++ ;
        i+=2 ;
    }
    if(checkBlack(r1 , (n==7)?7:n+1))
    {
        arr[i]= r1;
        arr[i+1]=n+1;
        i+=2;
    }

    n = r1 ;
    while( board[n-1][c1] == ' ' && n > 0 )
    {
        arr[i]=n-1;
        arr[i+1]=c1;
        n--;
        i+=2;
    }
    if(checkBlack((n==0)?0:n-1 , c1))
    {
        arr[i]= n-1;
        arr[i+1]=c1;
        i+=2;
    }

    n = r1 ;

    while( board[n+1][c1] == ' ' &&  n < 7  )
    {
        arr[i]= n+1;
        arr[i+1]=c1;
        i+=2;
        n++;
    }
    if(checkBlack((n==7)?7:n+1 , c1))
    {
        arr[i]= n+1;
        arr[i+1]=c1;
        i+=2;
    }

    a = 1, b = 1 ;
    while( (board[r1-a][c1+b] == ' ' || checkBlack(r1-a, c1+b)==1) && r1-a>-1 && c1+b<8 )
    {
        arr[i]= r1-a;
        arr[i+1]=c1+b;
        i+=2;
        if(checkBlack(r1-a , c1+b)==1) break;
        a++ ;
        b++ ;
    }


    a = 1, b = 1 ;
    while( (board[r1+a][c1-b] == ' ' || checkBlack(r1+a, c1-b)==1) && r1+a<8 && c1-b>-1)
    {
        arr[i]= r1+a;
        arr[i+1]=c1-b;
        i+=2;
        if(checkBlack(r1+a , c1-b)==1) break;
        a++ ;
        b++ ;
    }

    a = 1, b = 1 ;
    while( (board[r1+a][c1+b] == ' ' || checkBlack(r1+a, c1+b)==1) && r1+a<8 && c1+b<8)
    {
        arr[i]= r1+a;
        arr[i+1]=c1+b;
        i+=2;
        if(checkBlack(r1+a , c1+b)==1) break;
        a++ ;
        b++ ;
    }

    a = 1, b = 1 ;
    while( (board[r1-a][c1-b] == ' ' || checkBlack(r1-a, c1-b)==1) && r1-a>-1 && c1-b>-1)
    {
        arr[i]= r1-a;
        arr[i+1]=c1-b;
        i+=2;
        if(checkBlack(r1-a , c1-b)==1) break;
        a++ ;
        b++ ;
    }

    return arr;
}

//This Function checks all available positions for the black king to see if these positions are near to the white king if no this is place is valid (use in king function)
int checkNearbyWKing(int r2, int c2)
{
    if(board[r2][c2+1] == 'k' && c2<7 )
        {
            return 0;
        }
    else if(board[r2][c2-1] == 'k' && c2>0)
        {
            return 0;
        }
    else if(board[r2+1][c2] == 'k' && r2<7)
        {
            return 0;
        }
    else if(board[r2-1][c2] == 'k' && r2>0)
        {
            return 0;
        }
    else if(board[r2+1][c2+1] == 'k' && r2<7 && c2<7)
        {
            return 0;
        }
    else if(board[r2-1][c2-1] == 'k' && c2>0 && r2>0)
        {
            return 0;
        }
    else if(board[r2-1][c2+1] == 'k' && c2<7 &&r2>0)
        {
            return 0;
        }
    else if(board[r2+1][c2-1] == 'k' && r2<7 && c2>0)
        {
            return 0;
        }
    else
        {
            return 1;
        }

}

int *kingB(int r1, int c1)
{
    int i=0;
    static int arr[52];
    for(int j = 0; j<52; j++) arr[j] = -1;
    //1
    if( (board[r1][c1+1] == ' ' || checkBlack(r1, c1+1)== 1) && checkNearbyWKing(r1, c1+1)==1 && c1<7 )
        {
            arr[i]= r1;
            arr[i+1]=c1+1;
            i+=2;
        }
    //2
    if( (board[r1][c1-1] == ' ' || checkBlack(r1, c1-1)== 1) && checkNearbyWKing(r1, c1-1)==1 && c1>0 )
        {
            arr[i]= r1;
            arr[i+1]=c1-1;
            i+=2;
        }
    //3
    if( (board[r1+1][c1] == ' ' || checkBlack(r1+1, c1)== 1) && checkNearbyWKing(r1+1, c1)==1 && r1<7 )
        {
            arr[i]= r1+1;
            arr[i+1]=c1;
            i+=2;
        }
    //4
    if( (board[r1-1][c1] == ' ' || checkBlack(r1-1, c1)== 1) && checkNearbyWKing(r1-1, c1)==1 && r1>0)
        {
            arr[i]= r1-1;
            arr[i+1]=c1;
            i+=2;
        }
    //5
    if( (board[r1+1][c1+1] == ' ' || checkBlack(r1+1, c1+1)== 1) && checkNearbyWKing(r1+1, c1+1)==1 && r1<7 && c1<7)
        {
            arr[i]= r1+1;
            arr[i+1]=c1+1;
            i+=2;
        }
    //6
    if( (board[r1-1][c1-1] == ' ' || checkBlack(r1-1, c1-1)== 1) && checkNearbyWKing(r1-1, c1-1)==1 && c1>0 && r1>0)
        {
            arr[i]= r1-1;
            arr[i+1]=c1-1;
            i+=2;
        }
    //7
    if( (board[r1-1][c1+1] == ' ' || checkBlack(r1-1, c1+1)== 1) && checkNearbyWKing(r1-1, c1+1)==1 && c1<7 &&r1>0 )
        {
            arr[i]= r1-1;
            arr[i+1]=c1+1;
            i+=2;
        }
    //8
    if( (board[r1+1][c1-1] == ' ' || checkBlack(r1+1, c1-1)== 1) && checkNearbyWKing(r1+1, c1-1)==1 && r1<7 && c1>0)
        {
            arr[i]= r1+1;
            arr[i+1]=c1-1;
            i+=2;
        }


    return arr;
}

//This function print letters of the available moves for the chosen piece to player 2 (Black)
void printAvailableB(int *available)
{
    printf("Available Moves Are:\n");
    for(int i = 0 ; i<52; i+=2)
    {
        if (available[i]==-1)
        {
            break;
        }
        else
        {
             printf("((%c%i%s))" , letters[available[i+1]] ,8-(available[i]), (checkBlack(available[i] , available[i+1])==1)? "*":"");
        }
    }
}

//See if the white king is checked after each turn
int checkB()
{
    //find the position of the king
    int r;
    int c;
    for(int i =0; i< 8; i++)
    {
        for(int j =0; j<8 ; j++)
        {
            if(board[i][j]=='K')
            {
                r=i;
                c=j;
                break;
            }
        }
    }
    //Check if it is capture by pawn
    if(board[r+1][c+1] == 'p' || board[r+1][c-1]=='p')
    {
        return 1;
    }

    //Check if it is capture by knightB
    if( board[r+2][c+1] == 'n' ||
        board[r+2][c-1] == 'n' ||
        board[r+1][c+2] == 'n' ||
        board[r-1][c+2] == 'n' ||
        board[r-2][c-1] == 'n' ||
        board[r-2][c+1] == 'n' ||
        board[r+1][c-2] == 'n' ||
        board[r-1][c-2] == 'n' )
    {
        return 1;
    }

    //Check if it is capture by rook or queen
    int n;
    n=c;
        //Horizontal
    while( board[r][n-1] == ' ' && n >0 )
    {
        n--;
    }
    if(board[r][(n==0)?0:n-1] =='r' || board[r][(n==0)?0:n-1] =='q')
    {
        return 1;
    }

    n=c ;
    while( board[r][n+1] == ' '  && n < 7 )
    {
        n++ ;
    }
    if(board[r][(n==7)?7:n+1] == 'r' || board[r][(n==7)?7:n+1] == 'q')
    {
        return 1;
    }

        //Vertical
    n = r;
    while( board[n-1][c] == ' ' && n > 0 )
    {
        n--;
    }
    if(board[(n==0)?0:n-1][c] == 'r' || board[(n==0)?0:n-1][c] == 'q')
    {
        return 1;
    }

    n = r;
    while( board[n+1][c] == ' ' &&  n < 7  )
    {
        n++;
    }
    if(board[(n==7)?7:n+1][c]== 'r' || board[(n==7)?7:n+1][c]== 'q')
    {
        return 1;
    }


    //Check if it is capture by bishop or queen
    int a, b;
    a = 1, b = 1 ;
    while( board[r-a][c+b] == ' ' && r-a>-1 && c+b<8 )
    {
        a++ ;
        b++ ;
    }
    if(board[r-a][c+b]=='b' || board[r-a][c+b]=='q') return 1;


    a = 1, b = 1 ;
    while( board[r+a][c-b] == ' ' && r+a<8 && c-b>-1 )
    {
        a++ ;
        b++ ;
    }
    if(board[r+a][c-b]=='b' || board[r+a][c-b]=='q') return 1;

    a = 1, b = 1 ;
    while( board[r+a][c+b] == ' ' && r+a<8 && c+b<8 )
    {
        a++ ;
        b++ ;
    }
    if(board[r+a][c+b]=='b' ||board[r+a][c+b]=='q') return 1;

    a = 1, b = 1 ;
    while( board[r-a][c-b] == ' ' && r-a>-1 && c-b>-1 )
    {
        a++ ;
        b++ ;
    }
    if(board[r-a][c-b]=='b' || board[r-a][c-b]=='q') return 1;




    return 0;




}

//See if the white king is checked and there is no way to escape so the game is end
int checkmateB()
{
    char temp;
    int indicator;
    int c;
    int r[52]= { [ 0 ... 51 ] = -1 };
    if( checkB() == 1 )
    {
        checker = 1;
        for (int i = 0; i<8;i++)
        {
            for(int j =0; j<8; j++)
            {
                int *test = r;
                switch( board[i][j] )
                {
                    case 'P': test = pawnBlack(i,j);
                            break;
                    case 'R': test = rookB(i,j);
                            break;
                    case 'N': test = knightB(i,j);
                            break;
                    case 'B': test = bishopB(i,j);
                            break;
                    case 'K': test = kingB(i,j);
                            break;
                    case 'Q': test = queenB(i,j);
                            break;
                    default : break;
                }
                for(int k =0; k<8; k++)
                {
                    for(int l =0; l<8; l++)
                    {
                        temp = board[k][l];
                        c = change(i,j,k,l, test);
                        if(c==1)
                        {
                            if (checkB()==1)
                            {
                                board[i][j] = board[k][l];
                                board[k][l] = temp;
                                indicator=3;
                            }
                            else
                            {
                                board[i][j] = board[k][l];
                                board[k][l] = temp;
                                indicator =2;
                                return indicator;
                                break;
                            }
                        }
                        else
                        {
                            indicator=3;
                        }
                    }
                }
            }
        }
        return indicator;
    }
    else
    {
        checker = 0;
    }
}

//See if the game ended draw
int stalemateB()
{
    char temp;
    int indicator = 0;
    int c;
    int r[52]= { [ 0 ... 51 ] = -1 };
    if( checkB() == 0 )
    {
        checker = 0;
        for (int i = 0; i<8;i++)
        {
            for(int j =0; j<8; j++)
            {
                int *test = r;
                switch( board[i][j] )
                {
                    case 'P': test = pawnBlack(i,j);
                            break;
                    case 'R': test = rookB(i,j);
                            break;
                    case 'N': test = knightB(i,j);
                            break;
                    case 'B': test = bishopB(i,j);
                            break;
                    case 'K': test = kingB(i,j);
                            break;
                    case 'Q': test = queenB(i,j);
                            break;
                    default : break;
                }
                for(int k =0; k<8; k++)
                {
                    for(int l =0; l<8; l++)
                    {
                        temp = board[k][l];
                        c = change(i,j,k,l, test);
                        if(c==0)
                        {
                            indicator=3;
                        }
                        else if (c==1 && checkB()==1)
                        {
                            board[i][j] = board[k][l];
                            board[k][l] = temp;
                            indicator =3;
                        }
                        else
                        {
                            board[i][j] = board[k][l];
                            board[k][l] = temp;
                            indicator =2;
                            break;
                        }
                        if(indicator ==2) break;
                    }
                    if(indicator ==2) break;
                }
                if(indicator ==2) break;
            }
            if(indicator ==2) break;
        }
    }

    //check if there are only (two kings  / two kings and one knight / two kings and one bishop)
    char remaining[3] ={' ', ' ', ' '};
    int pieces = 0;
    for(int i = 0; i<8; i++)
    {
        for(int j =0; j<8; j++)
        {
            if (board[i][j] != ' ')
            {
                if(pieces<4) {remaining[pieces] = board[i][j];}
                pieces++;
            }
        }
    }

    char case1[3] = {' ','K','k'};
    char case2[3] = {'K','k','n'};
    char case3[3] = {'K','N','k'};
    char case4[3] = {'B','K','k'};
    char case5[3] = {'K','b','k'};


    if (pieces<4)
    {
        sort(3,remaining);
        if(compareArray(remaining,case1,3) || compareArray(remaining,case2,3) || compareArray(remaining,case3,3)||compareArray(remaining,case4,3)||compareArray(remaining,case5,3))
            {
                indicator= 3;
            }

    }


    return indicator;
}





int player1()
{
    SetColorAndBackground(15,0);
    save();
    if (checkmate()==3)
    {
        system("@cls||clear");
        printBoard();
        return 0;
    }
    if (stalemate()==3)
    {
        system("@cls||clear");
        printBoard();
        return 0;
    }
    printBoard();
    int r1, r2, c1,c2;
    char s1[2], s2[2];
    repeat1:
    printf("Enter The First Position (U To Undo |R To Redo |0 To Go To Mainmenu): ");
    scanf(" %s",s1);
    //prepare the values of position of the piece
    if (s1[0]=='A' || s1[0]=='a') c1 =0;
    else if (s1[0]=='B' || s1[0]=='b' ) c1 =1;
    else if (s1[0]=='C' || s1[0]=='c') c1 =2;
    else if (s1[0]=='D' || s1[0]=='d') c1 =3;
    else if (s1[0]=='E' || s1[0]=='e') c1 =4;
    else if (s1[0]=='F' || s1[0]=='f') c1 =5;
    else if (s1[0]=='G' || s1[0]=='g') c1 =6;
    else if (s1[0]=='H' || s1[0]=='h') c1 =7;
    else if (s1[0]=='0')
    {
        return 1;
    }
    else if (s1[0]=='U' || s1[0]=='u')
    {
        if (undoIndex != 0)
        {
            if(history[undoIndex-3] != ' ')
            {
                takesIndex2--;
                player2TakenOutPieces[takesIndex2] = ' ';
            }
            undo();
            turn++;
        }
        return 2;
    }
    else if (s1[0]=='R' || s1[0]=='r')
    {
        if (history[undoIndex] != ' ')
        {
            if(history[undoIndex+3] != ' ')
            {
                player1TakenOutPieces[takesIndex1] = history[undoIndex+3];
                takesIndex1++;;
            }
            redo();
            turn++;
        }
        return 2;
    }

    else
    {
        system("@cls||clear");//Clear The Screen
        printBoard();
        printf("\x1b[31m"); printf("Invalid Position\n"); printf("\x1b[0m");
        goto repeat1;
    }

    if (s1[1]=='8') r1 =0;
    else if (s1[1]=='7') r1 =1;
    else if (s1[1]=='6') r1 =2;
    else if (s1[1]=='5') r1 =3;
    else if (s1[1]=='4') r1 =4;
    else if (s1[1]=='3') r1 =5;
    else if (s1[1]=='2') r1 =6;
    else if (s1[1]=='1') r1 =7;
    else
    {
        system("@cls||clear");//Clear The Screen
        printBoard();
        printf("\x1b[31m"); printf("Invalid Position\n"); printf("\x1b[0m");
        goto repeat1;
    }


    //Find Available positions for the chosen piece
    int f[52];
    for(int j = 0; j<52; j++) f[j] = -1;
    int *available = f;
    switch( board[r1][c1] )
    {
        case 'p': available = pawnWhite(r1,c1);
                  break;
        case 'r': available = rook(r1,c1);
                  break;
        case 'n': available = knight(r1,c1);
                  break;
        case 'b': available = bishop(r1,c1);
                  break;
        case 'k': available = king(r1,c1);
                  break;
        case 'q': available = queen(r1,c1);
                  break;
        default: system("@cls||clear"); printBoard(); printf("\x1b[31m"); printf("Invalid Position\n"); printf("\x1b[0m"); goto repeat1 ;
    }

    //Print Available positions for the chosen piece
    system("@cls||clear");
    printAvailableBoard(available);
    printAvailable(available);
    //If the user choose piece that can't move
    if(available[0] == -1)
        {
            system("@cls||clear");
            printBoard();
            printf("\x1b[31m"); printf("This Piece Can't Move Choose Another One\n"); printf("\x1b[0m");
           goto repeat1 ;
        }
    //prepare the values of new position of the piece

    repeat2:
    printf("\nEnter The Second Position(Press 00 to change the piece): ");
    scanf("%s",s2);
    if (s2[1]=='8') r2 =0;
    else if (s2[1]=='7') r2 =1;
    else if (s2[1]=='6') r2 =2;
    else if (s2[1]=='5') r2 =3;
    else if (s2[1]=='4') r2 =4;
    else if (s2[1]=='3') r2 =5;
    else if (s2[1]=='2') r2 =6;
    else if (s2[1]=='1') r2 =7;
    else if (s2[1]=='0')
    {
        system("@cls||clear");
        printBoard();
        goto repeat1;
    }
    else
    {
        system("@cls||clear");//Clear The Screen
        printBoard();
        printf("\x1b[31m"); printf("\nInvalid Position\n"); printf("\x1b[0m");
        goto repeat2;
    }


    if (s2[0]=='A' || s2[0]=='a') c2 =0;
    else if (s2[0]=='B' || s2[0]=='b') c2 =1;
    else if (s2[0]=='C' || s2[0]=='c') c2 =2;
    else if (s2[0]=='D' || s2[0]=='d') c2 =3;
    else if (s2[0]=='E' || s2[0]=='e') c2 =4;
    else if (s2[0]=='F' || s2[0]=='f') c2 =5;
    else if (s2[0]=='G' || s2[0]=='g') c2 =6;
    else if (s2[0]=='H' || s2[0]=='h') c2 =7;
    else
    {
        system("@cls||clear");//Clear The Screen
        printBoard();
        printf("\x1b[31m"); printf("\nInvalid Position\n"); printf("\x1b[0m");
        goto repeat2;
    }

    char k1 = board[r1][c1];
    char k2 = board[r2][c2];
    int indicator = 0;
    if(k2 != ' ')
    {
        indicator = 1;
    }
    if( change(r1,c1,r2,c2, available) == 0)
    {
        printf("\x1b[31m"); printf("\nInvalid Position\n"); printf("\x1b[0m");
        goto repeat2;
    }
    if( check()==1)
    {
            checker = 1;
            board[r1][c1] = board[r2][c2];
            board[r2][c2] = temp;
            printf("\x1b[31m");printf("The King is Checked. This Move Is Invalid Choose Another one ");printf("\x1b[0m");
            goto repeat2;
    }
    else
    {
        checker = 0;
    }

    if(indicator)
    {
        player1TakenOutPieces[takesIndex1] = k2;
        takesIndex1++;
    }

    if(board[r2][c2]== 'p' && r2==0)
    {
        promotion(r2,c2);
    }

    history[undoIndex]= k1;
    history[undoIndex+1]=r1 + '0';
    history[undoIndex+2]=c1 + '0';
    history[undoIndex+3]=k2;
    history[undoIndex+4]=r2 + '0';
    history[undoIndex+5]=c2 + '0';
    undoIndex = undoIndex +6;
    turn++;
    system("@cls||clear");//Clear The Screen
    return 2;

}


int player2()
{
    SetColorAndBackground(15,0);
    save();
    if (checkmateB()==3)
    {
        system("@cls||clear");
        printBoard();
        return 0;
    }
    if (stalemateB()==3)
    {
        system("@cls||clear");
        printBoard();
        return 0;
    }
    printBoard();
    int r1, r2, c1,c2;
    char s1[2], s2[2];
    repeat1:
    printf("Enter The First Position (U To Undo |R To Redo |0 To Go To Mainmenu): ");
    scanf(" %s",s1);
    //prepare the values of position of the piece
    if (s1[0]=='A' || s1[0]=='a') c1 =0;
    else if (s1[0]=='B' || s1[0]=='b' ) c1 =1;
    else if (s1[0]=='C' || s1[0]=='c') c1 =2;
    else if (s1[0]=='D' || s1[0]=='d') c1 =3;
    else if (s1[0]=='E' || s1[0]=='e') c1 =4;
    else if (s1[0]=='F' || s1[0]=='f') c1 =5;
    else if (s1[0]=='G' || s1[0]=='g') c1 =6;
    else if (s1[0]=='H' || s1[0]=='h') c1 =7;
    else if (s1[0]=='0' || s1[0]=='0')
    {
        return 1;
    }
    else if (s1[0]=='U' || s1[0]=='u')
    {
        if(history[undoIndex-3] != ' ')
        {
            takesIndex1--;
            player1TakenOutPieces[takesIndex1] = ' ';
        }
        undo();
        turn++;
        return 2;
    }
    else if (s1[0]=='R' || s1[0]=='r')
    {
        if (history[undoIndex] != ' ')
        {
            if(history[undoIndex+3] != ' ')
            {
                player2TakenOutPieces[takesIndex2] = history[undoIndex+3];
                takesIndex2++;;
            }
            redo();
            turn++;
        }
        return 2;
    }
    else
    {
        system("@cls||clear");//Clear The Screen
        printBoard();
        printf("\x1b[31m"); printf("Invalid Position\n"); printf("\x1b[0m");
        goto repeat1;
    }


    if (s1[1]=='8') r1 =0;
    else if (s1[1]=='7') r1 =1;
    else if (s1[1]=='6') r1 =2;
    else if (s1[1]=='5') r1 =3;
    else if (s1[1]=='4') r1 =4;
    else if (s1[1]=='3') r1 =5;
    else if (s1[1]=='2') r1 =6;
    else if (s1[1]=='1') r1 =7;
    else
    {
        system("@cls||clear");//Clear The Screen
        printBoard();
        printf("\x1b[31m"); printf("Invalid Position\n"); printf("\x1b[0m");
        goto repeat1;
    }
    char k1 = board[r1][c1];
    //Find Available positions for the chosen piece
    int f[52];
    for(int j = 0; j<52; j++) f[j] = -1;
    int *available = f;
    switch( board[r1][c1] )
    {
        case 'P': available = pawnBlack(r1,c1);
                  break;
        case 'R': available = rookB(r1,c1);
                  break;
        case 'N': available = knightB(r1,c1);
                  break;
        case 'B': available = bishopB(r1,c1);
                  break;
        case 'K': available = kingB(r1,c1);
                  break;
        case 'Q': available = queenB(r1,c1);
                  break;
        default: system("@cls||clear"); printBoard(); printf("\x1b[31m"); printf("Invalid Position\n"); printf("\x1b[0m"); goto repeat1 ;
    }

    //Print Available positions for the chosen piece
    system("@cls||clear");
    printAvailableBoard(available);
    printAvailableB(available);
    //If the user choose piece that can't move
    if(available[0] == -1)
        {
            system("@cls||clear");
            printBoard();
            printf("\x1b[31m"); printf("This Piece Can't Move Choose Another One\n"); printf("\x1b[0m");
           goto repeat1 ;
        }
    //prepare the values of new position of the piece

    repeat2:
    printf("\nEnter The Second Position(Press 00 to change the piece): ");
    scanf("%s",s2);
    if (s2[1]=='8') r2 =0;
    else if (s2[1]=='7') r2 =1;
    else if (s2[1]=='6') r2 =2;
    else if (s2[1]=='5') r2 =3;
    else if (s2[1]=='4') r2 =4;
    else if (s2[1]=='3') r2 =5;
    else if (s2[1]=='2') r2 =6;
    else if (s2[1]=='1') r2 =7;
    else if (s2[1]=='0')
    {
        system("@cls||clear");
        printBoard();
        goto repeat1;
    }
    else
    {
        system("@cls||clear");//Clear The Screen
        printBoard();
        printf("\x1b[31m"); printf("\nInvalid Position\n"); printf("\x1b[0m");
        goto repeat2;
    }

    if (s2[0]=='A' || s2[0]=='a') c2 =0;
    else if (s2[0]=='B' || s2[0]=='b') c2 =1;
    else if (s2[0]=='C' || s2[0]=='c') c2 =2;
    else if (s2[0]=='D' || s2[0]=='d') c2 =3;
    else if (s2[0]=='E' || s2[0]=='e') c2 =4;
    else if (s2[0]=='F' || s2[0]=='f') c2 =5;
    else if (s2[0]=='G' || s2[0]=='g') c2 =6;
    else if (s2[0]=='H' || s2[0]=='h') c2 =7;
    else if (s1[0]=='0' || s1[0]=='0')
    {
        return 1;
    }
    else
    {
        system("@cls||clear");//Clear The Screen
        printBoard();
        printf("\x1b[31m"); printf("\nInvalid Position\n"); printf("\x1b[0m");
        goto repeat2;
    }


    char k2 = board[r2][c2];
    int indecator =0;
    if(k2 != ' ')
    {
        indecator = 1;
    }
    if( change(r1,c1,r2,c2, available) == 0)
    {
        printf("\x1b[31m"); printf("\nInvalid Position\n"); printf("\x1b[0m");
        goto repeat2;
    }

    if( checkB()==1)
    {
            checker = 1;
            board[r1][c1] = board[r2][c2];
            board[r2][c2] = temp;
            printf("\x1b[31m"); printf("The King is Checked. This Move Is Invalid Choose Another one "); printf("\x1b[0m");
            goto repeat2;
    }
    else
    {
        checker = 0;
    }

    if(indecator)
    {
        player2TakenOutPieces[takesIndex2] = k2;
        takesIndex2++;
    }
    if(board[r2][c2]== 'P' && r2==7)
    {
        promotionB(r2,c2);
    }

    history[undoIndex]= k1;
    history[undoIndex+1]=r1 + '0';
    history[undoIndex+2]=c1 + '0';
    history[undoIndex+3]=k2;
    history[undoIndex+4]=r2 + '0';
    history[undoIndex+5]=c2 + '0';
    undoIndex = undoIndex +6;

    turn++;
    system("@cls||clear");//Clear The Screen
    return 2;

}


