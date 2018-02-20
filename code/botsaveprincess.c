#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct game_board {
    char board[100][100];
    int traversed[100][100];
    int r, c;
} board;

int bot_r, bot_c, pri_r, pri_c;

struct node {
    char data;
    int r, c;
    struct node *left;
    struct node *right;
    struct node *top;
    struct node *bottom;
    struct node *parent;
} *start = NULL;


static char shortest_path[100] = "";
static int cnt = 100;

/* This function is to print the details of the game */
void print_game_details() {

    printf("\n****************************************************************************************\n");
    printf("****************************************************************************************\n");
    printf("****************************************************************************************\n");
    printf("**                                                                                    **\n");
    printf("**                             BOT SAVE THE PRINCESS                                  **\n");
    printf("**                                                                                    **\n");
    printf("****************************************************************************************\n");
    printf("****************************************************************************************\n");
    printf("****************************************************************************************\n");
    printf("**                                                                                    **\n");
    printf("**  INSTRUCTIONS ---------->>>>>>>>                                                   **\n");
    printf("**   1. GIVE THE DIAMENSION OF THE BOARD AS THE COMMENT LINE ARGUMENT                 **\n");
    printf("**          (SUPPOSE YOU WANT TO ENTER A 3x3 BOARD THEN './a.out 3 3').               **\n");
    printf("**   2. THEN YOU WILL BE ASKED TO ENTER THE MATRIX IN WHICH ON OF ITS INDEX CAN HOLD  **\n");
    printf("** THE PRINCESS AND OTHER CAN HOLD THE BOT THAT SAVES THE PRINCESS.                   **\n");
    printf("**   3. EACH OTHER INDICES IMPLIES PATHS, IF THE PATH IS CLEAR THE INPUT '-'.AND IF   **\n");
    printf("** YOU WANT TO ENTER A BLOCK ON THE PATH THEN INPUT '/' AT THE INDEX.                 **\n");
    printf("**   4. ENTER 'P' FOR PRINCESS AND 'B' FOR THE BOT.                                   **\n");
    printf("**                                                                                    **\n");
    printf("****************************************************************************************\n");
    printf("****************************************************************************************\n");
    printf("****************************************************************************************\n");

}

/* This function inputs the data into the game board */
board input_data(board Board) {

    char ch;
    int i, j;

    for (i = 0; i < Board.r; i++) {
        for (j = 0; j < Board.c; j++) {
            scanf("%c", &ch);
            Board.board[i][j] = ch;
            Board.traversed[i][j] = 0;
            if (ch == 'B') {
                bot_r = i;
                bot_c = j;
            }
            if (ch == 'P') {
                pri_r = i;
                pri_c = j;
            }
            scanf("%c", &ch);
        }
    }
    return Board;
}

struct node *new() {
    return (struct node *) malloc(sizeof(struct node));
}


void path(struct node *n);
/* This function is to traverse through all the columns and rows of the board */
void traverse(board Board, struct node *n) {

    if (n->c - 1 >= 0) {
        if (Board.traversed[n->r][n->c - 1] == 0 && Board.board[n->r][n->c - 1] != '/') {
            Board.traversed[n->r][n->c - 1] = 1;
            n->left = new();
            (n->left)->data = 'L';
            (n->left)->left = NULL;
            (n->left)->top = NULL;
            (n->left)->right = NULL;
            (n->left)->bottom = NULL;
            (n->left)->r = n->r;
            (n->left)->c = n->c - 1;
            if (n->r == pri_r && n->c - 1 == pri_c) {
                (n->left)->parent = n;
                path(n->left);
            } else {
                (n->left)->parent = n;
                traverse(Board, n->left);
            }
        }

    }
    if (n->c + 1 < Board.r) {
        if (Board.traversed[n->r][n->c + 1] == 0 && Board.board[n->r][n->c + 1] != '/') {
            Board.traversed[n->r][n->c + 1] = 1;
            n->right = new();
            (n->right)->data = 'R';
            (n->right)->left = NULL;
            (n->right)->top = NULL;
            (n->right)->right = NULL;
            (n->right)->bottom = NULL;
            (n->right)->r = n->r;
            (n->right)->c = n->c + 1;
            if (n->r == pri_r && n->c + 1 == pri_c) {
                (n->right)->parent = n;
                path(n->right);
            } else {
                (n->right)->parent = n;
                traverse(Board, n->right);
            }
        }

    }
    if (n->r - 1 >= 0) {
        if (Board.traversed[n->r - 1][n->c] == 0 && Board.board[n->r - 1][n->c] != '/') {
            Board.traversed[n->r - 1][n->c] = 1;
            n->top = new();
            (n->top)->data = 'T';
            (n->top)->left = NULL;
            (n->top)->top = NULL;
            (n->top)->right = NULL;
            (n->top)->bottom = NULL;
            (n->top)->r = n->r - 1;
            (n->top)->c = n->c;
            if (n->r - 1 == pri_r && n->c == pri_c) {
                (n->top)->parent = n;
                path(n->top);
            } else {
                (n->top)->parent = n;
                traverse(Board, n->top);
            }
        }
    }
    if (n->r + 1 < Board.c) {
        if (Board.traversed[n->r + 1][n->c] == 0 && Board.board[n->r + 1][n->c] != '/') {
            Board.traversed[n->r + 1][n->c] = 1;
            n->bottom = new();
            (n->bottom)->data = 'B';
            (n->bottom)->left = NULL;
            (n->bottom)->top = NULL;
            (n->bottom)->right = NULL;
            (n->bottom)->bottom = NULL;
            (n->bottom)->r = n->r + 1;
            (n->bottom)->c = n->c;
            if (n->r + 1 == pri_r && n->c == pri_c) {
                (n->bottom)->parent = n;
                path(n->bottom);
            } else {
                (n->bottom)->parent = n;
                traverse(Board, n->bottom);
            }
        }
    }
}

/* This function is to construct the tree structure for the board*/
struct node *construct_tree(board Board) {

    board b = Board;
    start = new();
    start->data = '0';
    start->r = bot_r;
    start->c = bot_c;
    start->parent = NULL;
    start->left = NULL;
    start->right = NULL;
    start->top = NULL;
    start->bottom = NULL;
    b.traversed[bot_r][bot_c] = 1;
    traverse(b, start);

    return start;
}

/* This function finds the shortest path for the bot to reach the princess */
void path(struct node *n) {
    struct node *newn = n;
    int i = 0;
    char temp[100];
    while (newn != NULL) {
        temp[i++] = newn->data;
        newn = newn->parent;

    }
    temp[i - 1] = '\0';
    if (i < cnt) {
        strcpy(shortest_path, temp);
        cnt = i;
    }
}

/* This function decodes the shortest path and will print it*/
void print_shortest_path(char *string) {
    int i;
    printf("Path --> ");
    for (i = (int) (strlen(string) - 1); i >= 0; i--) {
        switch (string[i]) {
            case 'T':
                printf("TOP ");
                break;
            case 'B':
                printf("BOTTOM ");
                break;
            case 'L':
                printf("LEFT ");
                break;
            case 'R':
                printf("RIGHT ");
                break;
            default:break;
        }
    }
    printf("\n");
}

/* The main function will take dimension of the box as commandline argument*/
int main(int argc, char **argv) {

    board Board;
    Board.r = atoi(argv[1]);
    Board.c = atoi(argv[2]);
    system("clear");

    print_game_details();
    Board = input_data(Board);
    start = construct_tree(Board);
    print_shortest_path(shortest_path);

    return 0;
}
