#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxNode 40

typedef struct Node
{
    char info;
    struct Node *lson;
    struct Node *rson;
} Node;

Node *T = NULL;
Node *address[MaxNode];
char info[MaxNode];
int N = 0;

Node *Allocate(char value)
{
    Node *temp = (Node *)malloc(sizeof(Node));

    if (temp == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    temp->info = value;
    temp->lson = NULL;
    temp->rson = NULL;

    return temp;
}

void CreateTreeNP(const char *input)
{
    int i;
    int father;
    Node *p;
    Node *fatherPT;

    T = NULL;

    for (i = 1; i <= N; i++)
    {
        p = Allocate(input[i - 1]);

        info[i] = input[i - 1];
        address[i] = p;

        if (T == NULL)
        {
            T = p;
        }
        else
        {
            father = i / 2;
            fatherPT = address[father];

            if (fatherPT->lson == NULL)
                fatherPT->lson = p;
            else
                fatherPT->rson = p;
        }
    }
}

void ShowTree(void)
{
    int level;
    int start;
    int end;
    int j;
    int height = 0;
    int nodeCount = N;

    /* คำนวณจำนวนระดับของต้นไม้ */
    while (nodeCount > 0)
    {
        height++;
        nodeCount /= 2;
    }

    printf("\nTree Structure:\n\n");

    for (level = 1; level <= height; level++)
    {
        start = 1 << (level - 1);
        end = (1 << level) - 1;

        /* ระยะห่างด้านหน้าก่อนแสดง Node */
        for (j = 0; j < (1 << (height - level)) - 1; j++)
            printf(" ");

        for (j = start; j <= end && j <= N; j++)
        {
            if (info[j] != '\0')
                printf("%c", info[j]);
            else
                printf(" ");

            for (int space = 0;
                 space < (1 << (height - level + 1)) - 1;
                 space++)
            {
                printf(" ");
            }
        }

        printf("\n\n");
    }
}

void PreOrder(Node *node)
{
    if (node != NULL)
    {
        printf(" %c", node->info);
        PreOrder(node->lson);
        PreOrder(node->rson);
    }
}

void InOrder(Node *node)
{
    if (node != NULL)
    {
        InOrder(node->lson);
        printf(" %c", node->info);
        InOrder(node->rson);
    }
}

void PostOrder(Node *node)
{
    if (node != NULL)
    {
        PostOrder(node->lson);
        PostOrder(node->rson);
        printf(" %c", node->info);
    }
}

void FreeTree(Node *node)
{
    if (node != NULL)
    {
        FreeTree(node->lson);
        FreeTree(node->rson);
        free(node);
    }
}

int main(void)
{
    char input[MaxNode];
    char ch;
    int c;
    int i;

    printf("Enter infix expression: ");

    if (scanf("%39s", input) != 1)
    {
        printf("Invalid input.\n");
        return 1;
    }

    while ((c = getchar()) != '\n' && c != EOF)
    {
    }

    N = (int)strlen(input);

    if (N >= MaxNode)
        N = MaxNode - 1;

    for (i = 0; i < MaxNode; i++)
    {
        info[i] = '\0';
        address[i] = NULL;
    }

    CreateTreeNP(input);

    ch = ' ';

    while (ch != 'E' && ch != 'e')
    {
        printf("\nPROGRAM TREE (Node Pointer)\n");
        printf("===========================\n");
        printf("N : %d\n", N);

        printf("Sequence of data: ");
        for (i = 1; i <= N; i++)
            printf("%c ", info[i]);

        ShowTree();

        printf("\nMENU => P:PreOrder I:InOrder O:PostOrder E:Exit\n");
        printf("Select: ");

        ch = (char)getchar();

        while ((c = getchar()) != '\n' && c != EOF)
        {
        }

        switch (ch)
        {
            case 'P':
            case 'p':
                printf("PRE ORDER TRAVERSAL :");
                PreOrder(T);
                printf("\n");
                break;

            case 'I':
            case 'i':
                printf("IN ORDER TRAVERSAL :");
                InOrder(T);
                printf("\n");
                break;

            case 'O':
            case 'o':
                printf("POST ORDER TRAVERSAL :");
                PostOrder(T);
                printf("\n");
                break;

            case 'E':
            case 'e':
                break;

            default:
                printf("Invalid menu choice.\n");
        }
    }

    FreeTree(T);
    return 0;
}