/* =====================================================================
   โปรแกรม: สร้างต้นไม้ไบนารี (Binary Expression Tree) จากนิพจน์ Postfix
   แล้วแสดงผลโครงสร้างต้นไม้ พร้อมทั้งท่องต้นไม้ทั้ง 3 แบบ
   (Pre-Order, In-Order, Post-Order)

   วิธีสร้างต้นไม้จาก Postfix:
   - อ่านทีละตัวอักษรจากซ้ายไปขวา
   - ถ้าเป็น "โอเปอแรนด์" (ตัวแปร/ตัวเลข) -> สร้างโหนดใบ แล้ว Push ลง Stack
   - ถ้าเป็น "โอเปอเรเตอร์" (+ - * / ^)   -> Pop โหนด 2 ตัวออกจาก Stack
        โหนดที่ Pop ออกมาตัวแรก = ลูกขวา (RSon)
        โหนดที่ Pop ออกมาตัวสอง = ลูกซ้าย (LSon)
        แล้วสร้างโหนดใหม่เก็บโอเปอเรเตอร์นั้น ให้ชี้ลูกซ้าย/ขวาตามที่ Pop ได้
        จากนั้น Push โหนดใหม่นี้กลับลง Stack
   - เมื่ออ่านครบทุกตัวอักษร โหนดที่เหลืออยู่ตัวเดียวใน Stack คือ Root ของต้นไม้
   ===================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

/* ----------- โครงสร้างโหนดของต้นไม้ไบนารี (แทนแบบพอยน์เตอร์) ----------- */
typedef struct Node {
    char info;              /* เก็บตัวอักษร (โอเปอแรนด์ หรือ โอเปอเรเตอร์) */
    struct Node *lson;      /* พอยน์เตอร์ชี้ลูกซ้าย */
    struct Node *rson;      /* พอยน์เตอร์ชี้ลูกขวา */
} Node;

/* ----------- Stack สำหรับเก็บพอยน์เตอร์ของโหนด ขณะสร้างต้นไม้ ----------- */
Node *stack[MAX];
int top = -1;

void push(Node *p) {
    if (top >= MAX - 1) {
        printf("Stack Overflow!\n");
        exit(1);
    }
    stack[++top] = p;
}

Node *pop() {
    if (top < 0) {
        printf("Stack Underflow! (Invalid postfix expression)\n");
        exit(1);
    }
    return stack[top--];
}

/* ตรวจสอบว่าตัวอักษรที่รับเข้ามาเป็นโอเปอเรเตอร์หรือไม่ */
int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

/* สร้างโหนดใหม่ 1 โหนด (Allocate) */
Node *makeNode(char c) {
    Node *p = (Node *) malloc(sizeof(Node));
    p->info = c;
    p->lson = NULL;
    p->rson = NULL;
    return p;
}

/* ----------- สร้างต้นไม้ไบนารีจากนิพจน์ Postfix ----------- */
Node *buildTreeFromPostfix(char *postfix) {
    int i;
    int len = strlen(postfix);

    for (i = 0; i < len; i++) {
        char ch = postfix[i];

        if (ch == ' ') continue;   /* ข้ามช่องว่าง เผื่อผู้ใช้พิมพ์เว้นวรรค */

        if (isOperator(ch)) {
            Node *rightNode = pop();   /* ตัวที่ pop ออกมาก่อน = ลูกขวา */
            Node *leftNode  = pop();   /* ตัวที่ pop ออกมาถัดมา = ลูกซ้าย */

            Node *newNode = makeNode(ch);
            newNode->lson = leftNode;
            newNode->rson = rightNode;

            push(newNode);
        } else if (isalnum(ch)) {
            /* โอเปอแรนด์ -> สร้างโหนดใบ */
            push(makeNode(ch));
        } else {
            printf("Invalid character found: '%c'\n", ch);
            exit(1);
        }
    }

    return pop();   /* โหนดสุดท้ายที่เหลือใน Stack คือ Root */
}

/* ===================== การท่องต้นไม้ทั้ง 3 แบบ ===================== */

/* Pre-Order  : R - TL - TR */
void PreOrder(Node *pt) {
    if (pt != NULL) {
        printf("%c ", pt->info);
        PreOrder(pt->lson);
        PreOrder(pt->rson);
    }
}

/* In-Order   : TL - R - TR */
void InOrder(Node *pt) {
    if (pt != NULL) {
        InOrder(pt->lson);
        printf("%c ", pt->info);
        InOrder(pt->rson);
    }
}

/* Post-Order : TL - TR - R */
void PostOrder(Node *pt) {
    if (pt != NULL) {
        PostOrder(pt->lson);
        PostOrder(pt->rson);
        printf("%c ", pt->info);
    }
}

/* หาความสูงของต้นไม้ เพื่อนำไปใช้แสดงผลแบบตามระดับ (Level) */
int TreeHeight(Node *pt) {
    if (pt == NULL) return 0;
    int lh = TreeHeight(pt->lson);
    int rh = TreeHeight(pt->rson);
    return (lh > rh ? lh : rh) + 1;
}

void PrintTreeLevel(Node *pt, int currentLevel, int targetLevel, int gap) {
    if (currentLevel == targetLevel) {
        printf("%c", pt == NULL ? ' ' : pt->info);
        printf("%*s", gap, "");
        return;
    }

    PrintTreeLevel(pt == NULL ? NULL : pt->lson,
                   currentLevel + 1, targetLevel, gap);
    PrintTreeLevel(pt == NULL ? NULL : pt->rson,
                   currentLevel + 1, targetLevel, gap);
}

/* ===================== แสดงโครงสร้างต้นไม้ ===================== */
void ShowTree(Node *pt, int space) {
    int height;
    int slotWidth;
    int level;

    (void) space;
    if (pt == NULL) return;

    height = TreeHeight(pt);
    for (level = 1; level <= height; level++) {
        int i;
        slotWidth = 4;
        for (i = level; i < height; i++) {
            slotWidth *= 2;
        }

        int leadingSpaces = slotWidth / 2 - 1;
        int gap = slotWidth - 1;

        printf("%*s", leadingSpaces, "");
        PrintTreeLevel(pt, 1, level, gap);
        printf("\n");
    }
}

/* ===================== โปรแกรมหลัก ===================== */
int main() {
    char postfix[MAX];
    Node *root;

    printf("=====================================================\n");
    printf(" Binary Expression Tree from Postfix Expression\n");
    printf("=====================================================\n");
    printf("Enter a postfix expression: ");
    scanf("%s", postfix);

    root = buildTreeFromPostfix(postfix);

    printf("\n----------- Tree Structure (Centered) -----------\n");
    printf("(Parent nodes are above their children)\n");
    ShowTree(root, 0);

    printf("\n----------- Tree Traversal Results -----------\n");

    printf("Pre-Order  (R-TL-TR)  : ");
    PreOrder(root);
    printf("\n");

    printf("In-Order   (TL-R-TR)  : ");
    InOrder(root);
    printf("\n");

    printf("Post-Order (TL-TR-R)  : ");
    PostOrder(root);
    printf("\n");

    printf("\nTree height : %d\n", TreeHeight(root));

    return 0;
}