#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define MaxData 100
#define MaxRow 10
#define MaxCol 20

int Data[MaxData];
int Data1[MaxData], Data2[MaxData];
int Radix[MaxRow][MaxCol];
int N;

void PrepareRawData(int n) {
    int i;
    srand((unsigned int)time(NULL));
    for (i = 1; i <= n; i++)
        Data[i] = 1 + rand() % 99;
}

void PrepareRawDataRadix(int n2) {
    int i;
    srand((unsigned int)time(NULL));
    for (i = 0; i < n2; i++)
        Data[i] = (rand() % 899) + 100;
}

void PrepareRawDataHeap(int n) {
    int i;
    srand((unsigned int)time(NULL));
    for (i = 1; i <= n; i++)
        Data1[i] = 1 + rand() % 99;
}

void DispData(int n) {
    int i;
    for(i = 1; i <= n; i++)
        printf("%2d ", Data[i]);
    printf("\n");
}

void DispDataRadix(int n2) {
    int i;
    for (i = 0; i < n2; i++)
        printf("%3d ", Data[i]);
    printf("\n");
}

void swap(int a, int b) {
    int temp = Data[a];
    Data[a] = Data[b];
    Data[b] = temp;
}

void BubbleSort(int n) {
    int i, j;
    printf("----------------------------------------------------------------\n");
    printf(" i ");
    for(i = 1; i <= n; i++)
        printf(" (%2d)", i);
    printf("\n");
    printf("----------------------------------------------------------------\n");
    for(i = 1; i <= n - 1; i++) {
        if(Data[i] > Data[i + 1]) {
            printf("%2d. ", i + 1);
            DispData(n);
            j = i + 1;
            while(Data[j] < Data[j - 1]) {
                swap(j - 1, j);
                j--;
                printf("%2d. ", i + 1);
                DispData(n);
            }
        }
    }
}

void swapHeap(int a, int b) {
    int temp = Data2[a];
    Data2[a] = Data2[b];
    Data2[b] = temp;
}

void DispDataHeap(int DataArr[], int out, int n_val) {
    int i;
    for (i = 1; i <= n_val; i++) {
        if (i < out)
            printf("%2d ", DataArr[i]);
        else
            printf("[%2d] ", DataArr[i]);
    }
    printf("\n");
}

int Maximum(int a, int b) {
    if(a > b) return a;
    else return b;
}

void AdjustTree(int LastNode, int n_val) {
    int i, Max, lson, rson, son;
    bool result = false;
    i = 1;
    while(!result) {
        lson = 2 * i;
        rson = 2 * i + 1;
        son = 0;
        if(lson == LastNode) {
            son = 1;
            if(Data2[i] < Data2[lson]) {
                swapHeap(i, lson);
                DispDataHeap(Data2, LastNode + 1, n_val);
            }
            result = true;
        }
        if(rson <= LastNode) {
            son = 2;
            Max = Maximum(Data2[lson], Data2[rson]);
            if(Data2[i] < Max) {
                if(Max == Data2[lson]) {
                    swapHeap(i, lson);
                    DispDataHeap(Data2, LastNode + 1, n_val);
                    if(rson == LastNode) result = true;
                    else i = lson;
                } else {
                    swapHeap(i, rson);
                    DispDataHeap(Data2, LastNode + 1, n_val);
                    if(rson == LastNode) result = true;
                    else i = rson;
                }
            } else {
                result = true;
            }
        }
        if(son == 0) result = true;
    }
    printf("---------------------------------------------------Adjust Tree Finished at N=%d \n", LastNode);
}

void CreateHeapTree(int n_val) {
    int i, j, k, father;
    bool result;
    Data2[1] = Data1[1];
    DispDataHeap(Data2, n_val + 1, n_val);
    for(i = 2; i <= n_val; i++) {
        Data2[i] = Data1[i];
        DispDataHeap(Data2, n_val + 1, n_val);
        result = true;
        j = i;
        while(result) {
            father = j / 2;
            if((Data2[j] > Data2[father]) && (j > 1)) {
                swapHeap(j, father);
                DispDataHeap(Data2, n_val + 1, n_val);
                j = father;
                result = true;
            } else {
                result = false;
            }
        }
    }
    printf("---------------------------------------------------Create Heap Tree Finished \n");
    for(k = 1; k <= n_val; k++)
        printf("(%d) ", k);
    printf("\n");
    for(i = n_val; i > 1; i--) {
        swapHeap(1, i);
        DispDataHeap(Data2, i, n_val);
        AdjustTree(i - 1, n_val);
    }
}

void RunHeapSort() {
    int n_heap = 8;
    printf("ASCENDING HEAP SORT\n");
    printf("===================================================\n");
    PrepareRawDataHeap(n_heap);
    printf("Raw Data : ");
    DispDataHeap(Data1, n_heap + 1, n_heap);
    printf("---------------------------------------------------Raw Data Finished \n");
    printf("Create Heap Tree...\n");
    CreateHeapTree(n_heap);
    printf("Sorted Data is : ");
    DispDataHeap(Data2, 1, n_heap);
    printf("---------------------------------------------------Sort Finished \n");
}

void InsertionSort(int n) {
    int i, j, temp;
    printf("------------------------------------------------------------\n");
    printf(" i ");
    for (i = 1; i <= n; i++)
        printf(" (%2d)", i);
    printf("\n------------------------------------------------------------\n");
    printf("%2d. ", 0);
    DispData(n);

    for (i = 2; i <= n; i++) {
        temp = Data[i];
        j = i - 1;
        while (j >= 1 && Data[j] > temp) {
            Data[j + 1] = Data[j];
            j--;
        }
        Data[j + 1] = temp;
        printf("%2d. ", i);
        DispData(n);
    }
}

void QuickSort(int f, int r) {
    int f1 = f, r1 = r;
    bool direction = true;
    while(f != r) {
        if(Data[f] > Data[r]) {
            printf("%2d %2d : ", f, r);
            DispData(N);
            swap(f, r);
            printf("%2d %2d : ", f, r);
            DispData(N);
            direction = !direction;
        }
        if (direction) r--;
        else f++;
    }
    printf("k1=[%2d]--------------------------------------------------------\n", Data[f]);
    if((f > f1) && (f - 1 != f1)) QuickSort(f1, f - 1);
    if((r < r1) && (r + 1 != r1)) QuickSort(r + 1, r1);
}

void ClearStackPT(void) {
    int i;
    for (i = 0; i <= MaxRow; i++)
        Radix[i][0] = 0;
}

void Push(int Rad, int Dat) {
    int SP = Radix[Rad][0] + 1;
    Radix[Rad][0] = SP;
    Radix[Rad][SP] = Dat;
}

void ReadStack(void) {
    int i, j, k = 0, SP;
    for (i = 0; i < MaxRow; i++) {
        SP = Radix[i][0];
        for (j = 1; j <= SP; j++) {
            Data[k] = Radix[i][j];
            k++;
        }
    }
}

void RadixSortLogic(int n2) {
    int Digit, i, RadixNo, divisor, d;
    for (Digit = 0; Digit < 3; Digit++) {
        printf("[Digit : %d] ==>\n", Digit);
        ClearStackPT();
        for (i = 0; i < n2; i++) {
            divisor = 1;
            for (d = 0; d < Digit; d++) divisor *= 10;
            RadixNo = (Data[i] / divisor) % 10;
            Push(RadixNo, Data[i]);
        }
        ReadStack();
        DispDataRadix(n2);
    }
}

void RunRadixSort() {
    int n_radix = 16;
    printf("ASCENDING RADIX SORT\n");
    printf("=====================================================================\n");
    PrepareRawDataRadix(n_radix);
    printf("Raw Data...\n");
    DispDataRadix(n_radix);
    printf("---------------------------------------------------------------------\n");
    printf("Processing Data...\n");
    RadixSortLogic(n_radix);
    printf("---------------------------------------------------------------------\n");
    printf("Sorted Data : \n");
    DispDataRadix(n_radix);
}

void DispDataSelection(int n, int out) {
    int i;
    for(i = 1; i <= n; i++) {
        if(out >= i) printf("[%2d] ", Data[i]);
        else printf("%2d ", Data[i]);
    }
    printf("\n");
}

int Minimum(int j, int n_val) {
    int i, temp, Location;
    Location = j;
    temp = Data[j];
    for(i = j + 1; i <= n_val; i++) {
        if(temp > Data[i]) {
            temp = Data[i];
            Location = i;
        }
    }
    return Location;
}

void SelectionSortLogic(int n) {
    int i, Location;
    printf("---------------------------------------------------------------------\n");
    printf(" i LOC ");
    for(i = 1; i <= n; i++)
        printf("(%2d) ", i);
    printf("\n ");
    DispDataSelection(n, 0);
    printf("---------------------------------------------------------------------\n");
    for(i = 1; i <= n; i++) {
        Location = Minimum(i, n);
        swap(i, Location);
        printf("(%2d) (%2d) ", i, Location);
        DispDataSelection(n, i);
    }
}

int main() {
    int choice;
    while(1) {
        printf("\n========================================\n");
        printf("      DATA STRUCTURES & ALGORITHMS      \n");
        printf("========================================\n");
        printf("1. Bubble Sort\n");
        printf("2. Heap Sort\n");
        printf("3. Insertion Sort\n");
        printf("4. Quick Sort\n");
        printf("5. Radix Sort\n");
        printf("6. Selection Sort\n");
        printf("0. Exit\n");
        printf("Select an option (0-6): ");
        if (scanf("%d", &choice) != 1) break;

        if(choice == 0) break;

        switch(choice) {
            case 1:
                N = 12;
                printf("\nASCENDING BUBBLE SORT\n");
                printf("================================================================\n");
                PrepareRawData(N);
                printf("Raw Data : "); DispData(N);
                printf("----------------------------------------------------------------\n");
                printf("Processing Data...\n");
                BubbleSort(N);
                printf("----------------------------------------------------------------\n");
                printf("Sorted Data : "); DispData(N);
                break;
            case 2:
                printf("\n");
                RunHeapSort();
                break;
            case 3:
                N = 12;
                printf("\nASCENDING INSERTION SORT\n");
                printf("==============================\n");
                PrepareRawData(N);
                printf("Raw Data... "); DispData(N);
                printf("Processing Data...\n");
                InsertionSort(N);
                printf("------------------------------------------------------------\n");
                printf("Sorted Data : "); DispData(N);
                break;
            case 4:
                N = 12;
                printf("\nASCENDING QUICK SORT\n");
                printf("==============================\n");
                PrepareRawData(N);
                printf("Raw Data : "); DispData(N);
                printf("Processing Data...\n");
                printf(" F R ");
                for(int i = 1; i <= N; i++) printf(" (%2d)", i);
                printf("\n");
                QuickSort(1, N);
                printf("----------------------------------------------------------------\n");
                printf("Sorted Data : "); DispData(N);
                break;
            case 5:
                printf("\n");
                RunRadixSort();
                break;
            case 6:
                N = 12;
                printf("\nASCENDING SELECTION SORT\n");
                printf("=====================================================================\n");
                PrepareRawData(N);
                printf("Raw Data..."); DispDataSelection(N, 0);
                printf("Processing Data...\n");
                SelectionSortLogic(N);
                printf("---------------------------------------------------------------------\n");
                printf("Sorted Data : "); DispDataSelection(N, N);
                break;
            default:
                printf("\nInvalid option. Please try again.\n");
        }
    }
    return 0;
}