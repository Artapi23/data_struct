#include <stdio.h>
#define MAX_SIZE 5   /* capacity of both Stack and Queue */
/* ---------------- Stack global variables ---------------- */
int stack[MAX_SIZE];
int top = -1;               /* SP : position of the top element, -1 = empty */
/* ---------------- Queue global variables ---------------- */
int queue[MAX_SIZE];
int front = 0;               /* index of the first element   */
int rear  = -1;               /* index of the last element, -1 = empty */
void printHeader(const char title[]) {
    printf("========================================\n");
    printf(" %s\n", title);
    printf("========================================\n");
}

/* Shared function 2: prints a horizontal divider line of given width */
void printDivider(int width) {
    for (int i = 0; i < width; i++) printf("-");
    printf("\n");
}

/* Shared function 3: reads an integer safely, re-prompts on bad input */
int getIntInput(const char prompt[]) {
    int value;
    printf("%s", prompt);
    while (scanf("%d", &value) != 1) {
        printf("Invalid input, please enter a number: ");
        while (getchar() != '\n') { /* discard bad input */ }
    }
    return value;
}

/* Shared function 4: resets every slot of any int array to 0        */
void clearArrayData(int arr[], int size) {
    for (int i = 0; i < size; i++) arr[i] = 0;
}

/* Shared function 5: prints the Before / After / Result block used
   by push, pop, insertQueue and deleteQueue                          */
void printOperationLog(const char operation[], const char valueLabel[], int value,
                        int hasValue, const char before[], const char after[], int success) {
    printf("Operation : %s\n", operation);
    if (hasValue) {
        printf("%-9s : %d\n", valueLabel, value);
    }
    printf("Before    : %s\n", before);
    printf("After     : %s\n", after);
    printf("Result    : %s\n", success ? "SUCCESS" : "FAILED");
    printDivider(40);
}

/* =========================================================
   STACK FUNCTIONS
   ========================================================= */

int isStackFull(void)  { return top == MAX_SIZE - 1; }
int isStackEmpty(void) { return top == -1; }

void push(int value) {
    char before[60], after[60];
    sprintf(before, "Top = %d, Data = %d", top, top + 1);

    if (isStackFull()) {
        sprintf(after, "Top = %d, Data = %d", top, top + 1);
        printOperationLog("PUSH", "Input", value, 1, before, after, 0);
        printf("Push failed: Stack Overflow\n\n");
        return;
    }

    top++;
    stack[top] = value;
    sprintf(after, "Top = %d, Data = %d", top, top + 1);
    printOperationLog("PUSH", "Input", value, 1, before, after, 1);
    printf("\n");
}

int pop(void) {
    char before[60], after[60];
    sprintf(before, "Top = %d, Data = %d", top, top + 1);

    if (isStackEmpty()) {
        sprintf(after, "Top = %d, Data = %d", top, top + 1);
        printOperationLog("POP", "Output", 0, 0, before, after, 0);
        printf("Pop failed: Stack Underflow\n\n");
        return -1;
    }

    int value = stack[top];
    top--;
    sprintf(after, "Top = %d, Data = %d", top, top + 1);
    printOperationLog("POP", "Output", value, 1, before, after, 1);
    printf("\n");
    return value;
}

void showStack(void) {
    printf("========== STACK STATUS ==========\n");
    printf("Capacity : %d\n", MAX_SIZE);
    printf("Data     : %d\n", top + 1);
    printf("Top      : %d\n", top);
    printf("Status   : %s\n", isStackEmpty() ? "EMPTY" : (isStackFull() ? "FULL" : "NORMAL"));
    printDivider(34);

    if (isStackEmpty()) {
        printf("Stack is empty.\n");
    } else {
        for (int i = top; i >= 0; i--) {
            if (i == top)
                printf("TOP -> [%d] index %d\n", stack[i], i);
            else
                printf("        [%d] index %d\n", stack[i], i);
        }
    }
    printDivider(34);
    printf("\n");
}

void clearStack(void) {
    clearArrayData(stack, MAX_SIZE);
    top = -1;
    printf("Stack cleared.\n\n");
}

/* =========================================================
   QUEUE FUNCTIONS
   ========================================================= */

int isQueueFull(void)  { return rear == MAX_SIZE - 1; }
int isQueueEmpty(void) { return rear < front; }

void insertQueue(int value) {
    char before[60], after[60];
    int count = isQueueEmpty() ? 0 : rear - front + 1;
    sprintf(before, "Front = %d, Rear = %d, Data = %d", front, rear, count);

    if (isQueueFull()) {
        sprintf(after, "Front = %d, Rear = %d, Data = %d", front, rear, count);
        printOperationLog("INSERT QUEUE", "Input", value, 1, before, after, 0);
        printf("Insert failed: Queue Overflow\n\n");
        return;
    }

    rear++;
    queue[rear] = value;
    count = rear - front + 1;
    sprintf(after, "Front = %d, Rear = %d, Data = %d", front, rear, count);
    printOperationLog("INSERT QUEUE", "Input", value, 1, before, after, 1);
    printf("\n");
}

int deleteQueue(void) {
    char before[60], after[60];
    int count = isQueueEmpty() ? 0 : rear - front + 1;
    sprintf(before, "Front = %d, Rear = %d, Data = %d", front, rear, count);

    if (isQueueEmpty()) {
        sprintf(after, "Front = %d, Rear = %d, Data = %d", front, rear, 0);
        printOperationLog("DELETE QUEUE", "Output", 0, 0, before, after, 0);
        printf("Delete failed: Queue Underflow\n\n");
        return -1;
    }

    int value = queue[front];
    front++;
    count = isQueueEmpty() ? 0 : rear - front + 1;
    sprintf(after, "Front = %d, Rear = %d, Data = %d", front, rear, count);
    printOperationLog("DELETE QUEUE", "Output", value, 1, before, after, 1);
    printf("\n");
    return value;
}

void showQueue(void) {
    printf("=========== QUEUE STATUS ===========\n");
    printf("Capacity : %d\n", MAX_SIZE);
    printf("Data     : %d\n", isQueueEmpty() ? 0 : rear - front + 1);
    printf("Front    : %d\n", front);
    printf("Rear     : %d\n", rear);
    printf("Status   : %s\n", isQueueEmpty() ? "EMPTY" : (isQueueFull() ? "FULL" : "NORMAL"));
    printDivider(36);

    if (isQueueEmpty()) {
        printf("Queue is empty.\n");
        printDivider(36);
        printf("\n");
        return;
    }

    printf("Index : ");
    for (int i = 0; i < MAX_SIZE; i++) printf("%-5d", i);
    printf("\n");

    printf("Data  : ");
    for (int i = 0; i < MAX_SIZE; i++) {
        if (i >= front && i <= rear)
            printf("[%-3d]", queue[i]);
        else
            printf("[   ]");
    }
    printf("\n");

    printf("        ");
    for (int i = 0; i < MAX_SIZE; i++) {
        if (i == front && i == rear)      printf("FR   ");
        else if (i == front)              printf("F    ");
        else if (i == rear)               printf("R    ");
        else                               printf("     ");
    }
    printf("\n");
    printDivider(36);

    printf("Order : ");
    for (int i = front; i <= rear; i++) {
        printf("%d", queue[i]);
        if (i != rear) printf(" -> ");
    }
    printf("\n");
    printf("\n");
}

void clearQueue(void) {
    clearArrayData(queue, MAX_SIZE);
    front = 0;
    rear = -1;
    printf("Queue cleared.\n\n");
}

/* =========================================================
   MENU FUNCTIONS
   ========================================================= */

void stackMenu(void) {
    int choice, value;
    do {
        printf("========== STACK MENU ==========\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Show Stack\n");
        printf("4. Clear Stack\n");
        printf("0. Back to Main Menu\n");
        printDivider(32);
        choice = getIntInput("Select menu: ");
        printf("\n");

        switch (choice) {
            case 1:
                value = getIntInput("Enter value to push: ");
                push(value);
                break;
            case 2:
                pop();
                break;
            case 3:
                showStack();
                break;
            case 4:
                clearStack();
                break;
            case 0:
                printf("Returning to main menu...\n\n");
                break;
            default:
                printf("Invalid choice, please try again.\n\n");
        }
    } while (choice != 0);
}

void queueMenu(void) {
    int choice, value;
    do {
        printf("========== QUEUE MENU ==========\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Show Queue\n");
        printf("4. Clear Queue\n");
        printf("0. Back to Main Menu\n");
        printDivider(32);
        choice = getIntInput("Select menu: ");
        printf("\n");

        switch (choice) {
            case 1:
                value = getIntInput("Enter value to insert: ");
                insertQueue(value);
                break;
            case 2:
                deleteQueue();
                break;
            case 3:
                showQueue();
                break;
            case 4:
                clearQueue();
                break;
            case 0:
                printf("Returning to main menu...\n\n");
                break;
            default:
                printf("Invalid choice, please try again.\n\n");
        }
    } while (choice != 0);
}

int main(void) {
    int choice;
    do {
        printHeader("STACK AND QUEUE PROGRAM");
        printf("1. Stack\n");
        printf("2. Queue\n");
        printf("0. Exit\n");
        printDivider(40);
        choice = getIntInput("Select menu: ");
        printf("\n");

        switch (choice) {
            case 1: stackMenu(); break;
            case 2: queueMenu(); break;
            case 0: printf("Exiting program. Goodbye!\n"); break;
            default: printf("Invalid choice, please try again.\n\n");
        }
    } while (choice != 0);

    return 0;
}
