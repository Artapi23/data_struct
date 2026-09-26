#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>_

#define MaxData 100
#define MaxRow 10
#define MaxCol 20

int Data[MaxData];
int Data1[MaxData], Data2[MaxData];
int Radix[MaxRow][MaxCol];
int N;

// สุ่มข้อมูลแบบ random สำหรับ Bubble Sort, Insertion Sort, Quick Sort, Selection Sort
void PrepareRawData(int n) {
    int i;
    srand((unsigned int)time(NULL));
    for (i = 1; i <= n; i++)
        Data[i] = 1 + rand() % 99;
}

// สุ่มข้อมูลแบบ random สำหรับ Radix Sort โดยให้มีค่าอยู่ในช่วง 100-999
void PrepareRawDataRadix(int n2) {
    int i;
    srand((unsigned int)time(NULL));
    for (i = 0; i < n2; i++)
        Data[i] = (rand() % 899) + 100;
}

// สุ่มข้อมูลอันใหม่สำหรับ Heap Sort ลงใน Data1[]
void PrepareRawDataHeap(int n) {
    int i;
    srand((unsigned int)time(NULL));
    for (i = 1; i <= n; i++)
        Data1[i] = 1 + rand() % 99;
}

// แสดงข้อมูลใน Data[] แบบทั่วไปสำหรับฟังก์ชัน sort อื่น ๆ
void DispData(int n) {
    int i;
    for(i = 1; i <= n; i++)
        printf("%2d ", Data[i]);
    printf("\n");
}

// แสดงข้อมูลใน Data[] แบบ Radix Sort เพื่อดูผลลัพธ์ทีละรอบ
void DispDataRadix(int n2) {
    int i;
    for (i = 0; i < n2; i++)
        printf("%3d ", Data[i]);
    printf("\n");
}

// สลับข้อมูล 2 ตำแหน่งใน Data[]
void swap(int a, int b) {
    int temp = Data[a];
    Data[a] = Data[b];
    Data[b] = temp;
}

// Bubble Sort: เปรียบเทียบคู่เพื่อนบ้านแล้วสลับถ้าตัวหน้า > ตัวหลัง
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

// สลับข้อมูล 2 ตัวใน Data2[] สำหรับ Heap Sort
void swapHeap(int a, int b) {
    int temp = Data2[a];
    Data2[a] = Data2[b];
    Data2[b] = temp;
}

// แสดงข้อมูลใน heap แบบมีการ highlight ตำแหน่งที่กำลังทำงาน DispDataHeap(Data2, 1, n_heap);
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

// คืนค่าใหญ่ที่สุดระหว่าง 2 ตัวเลข
int Maximum(int a, int b) {
    if(a > b) return a;
    else return b;
}

// ปรับโครงสร้าง heap หลังจากการสลับค่าเพื่อฟื้นฟูคุณสมบัติของ heap
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

// สร้าง heap tree จากข้อมูลใน Data1[] แล้วจัดเรียงข้อมูลลงใน Data2[]
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

// เรียก Heap Sort แบบครบวงจร: สุ่มข้อมูล -> แสดงข้อมูลดิบ -> สร้าง heap -> เรียง -> แสดงผลสุดท้าย
void RunHeapSort() {
    int n_heap = 4; // จำนวนข้อมูลสำหรับตัวอย่าง Heap Sort
    printf("ASCENDING HEAP SORT\n");
    printf("===================================================\n");
    PrepareRawDataHeap(n_heap); // สุ่มข้อมูลบันทึกลง Data1[]
    printf("Raw Data : ");
    DispDataHeap(Data1, n_heap + 1, n_heap); // แสดงข้อมูลก่อนเรียง
    printf("---------------------------------------------------Raw Data Finished \n");
    printf("Create Heap Tree...\n");
    CreateHeapTree(n_heap); // สร้าง heap tree และเรียงข้อมูล
    printf("Sorted Data is : ");
    DispDataHeap(Data2, 1, n_heap); // แสดงข้อมูลหลังเรียง
    printf("---------------------------------------------------Sort Finished \n");
}

// Insertion Sort: ดึงค่าตัวถัดไปมาแทรกไว้ในส่วนที่เรียงแล้ว
void InsertionSort(int N)
{
    int i, j, temp; // i = ตำแหน่งที่กำลังพิจารณา, j = ตำแหน่งที่เลื่อนข้อมูล, temp = ค่าชั่วคราว
    printf("---------------------------------------------------------------------\n");
    printf(" i  ");
    for (i = 1; i <= N; i++)
        printf(" (%2d)", i);
    printf("\n");
    printf("---------------------------------------------------------------------\n");
    printf("%2d. ", 0);
    DispData(N); // แสดงข้อมูลเริ่มต้น

    for (i = 1; i < N; i++) // วนรอบสำหรับแต่ละข้อมูลที่ต้องแทรก
    {
        if (Data[i + 1] < Data[i]) // ถ้าค่าตัวถัดไปน้อยกว่าตัวก่อนหน้า ให้แทรก
        {
            temp = Data[i + 1]; // เก็บค่าไว้ก่อนเริ่มย้ายข้อมูล
            Data[i + 1] = 0;    // ใส่ 0 เพื่อเป็นตำแหน่งว่างสำหรับแทรก
            j = i; // เริ่มจากตำแหน่งก่อนหน้าที่กำลังพิจารณา

            while (j >= 1 && temp < Data[j]) // เลื่อนค่าที่ใหญ่กว่า temp ไปทางขวา
            {
                Data[j + 1] = Data[j]; // เลื่อนข้อมูลที่ใหญ่กว่า temp ไปทางขวา
                Data[j] = 0; // ทำให้ตำแหน่งเดิมกลายเป็นช่องว่าง
                printf("%2d. ", i + 1);
                DispData(N); // แสดงกระบวนการเลื่อนข้อมูล
                j = j - 1; // ลด j เพื่อดูข้อมูลก่อนหน้าอีกชั้น
            }

            Data[j + 1] = temp; // ใส่ temp ลงในตำแหน่งสุดท้ายที่ว่าง
            printf("%2d. ", i + 1);
            DispData(N); // แสดงข้อมูลหลังจากแทรกเรียบร้อยแล้ว
        }
    }
}

// Quick Sort: ใช้ pivot หลักและแบ่งข้อมูลเป็นสองฝั่งแบบ recursive
void QuickSort(int f, int r) {
    int f1 = f, r1 = r; // เก็บช่วงเริ่มต้นและช่วงสุดท้ายไว้สำหรับ recursive
    bool direction = true; // true = เลื่อนไปทางซ้าย, false = เลื่อนไปทางขวา
    while(f != r) {
        if(Data[f] > Data[r]) { // ถ้าค่าด้านซ้ายมากกว่าด้านขวา ให้สลับ
            printf("%2d %2d : ", f, r);
            DispData(N); // แสดงก่อนสลับ
            swap(f, r); // สลับค่าเมื่อพบคู่ที่ผิดลำดับ
            printf("%2d %2d : ", f, r);
            DispData(N); // แสดงหลังสลับ
            direction = !direction; // เปลี่ยนทิศทางการเคลื่อนค่า
        }
        if (direction) r--; // ถ้า direction เป็น true ให้ลด r
        else f++; // ถ้า direction เป็น false ให้เพิ่ม f
    }
    printf("k1=[%2d]--------------------------------------------------------\n", Data[f]); // แสดง pivot ที่เจอ
    if((f > f1) && (f - 1 != f1)) QuickSort(f1, f - 1); // เรียงซ้ายก่อน
    if((r < r1) && (r + 1 != r1)) QuickSort(r + 1, r1); // เรียงขวาหลัง
}

// เคลียร์ค่าในแต่ละถังของ Radix ก่อนเริ่มรอบใหม่
void ClearStackPT(void) {
    int i;
    for (i = 0; i <= MaxRow; i++)
        Radix[i][0] = 0;
}

// ใส่ข้อมูลลงในถังที่ตรงกับหลักที่กำลังพิจารณา
// เช่น หลักหน่วย = 5 จะไปอยู่ที่ Radix[5]
void Push(int Rad, int Dat) {
    int SP = Radix[Rad][0] + 1;
    Radix[Rad][0] = SP;
    Radix[Rad][SP] = Dat;
}

// ดึงข้อมูลกลับจากถัง Radix[0] ถึง Radix[9] แล้วบรรจุกลับไปที่ Data[]
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

// Radix Sort ทำงานทีละหลักจากหลักหน่วย -> หลักสิบ -> หลักร้อย
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
    int n_radix = 4;
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

// โปรแกรมหลัก: แสดงเมนูและเรียกฟังก์ชัน sort ที่เลือก
int main() {
    int choice; // ตัวแปรเก็บตัวเลือกเมนู
    while(1) { // วนลูปจนกว่าจะเลือก 0 เพื่อออก
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
        if (scanf("%d", &choice) != 1) break; // ถ้าอ่านค่าไม่ได้ ให้หยุดโปรแกรม

        if(choice == 0) break; // ออกจากโปรแกรม

        switch(choice) { // จัดการตามตัวเลือกที่ผู้ใช้กรอก
            case 1:
                N = 4; // กำหนดจำนวนข้อมูลสำหรับ Bubble Sort
                printf("\nASCENDING BUBBLE SORT\n");
                printf("================================================================\n");
                PrepareRawData(N); // สุ่มข้อมูลใน Data[]
                printf("Raw Data : "); DispData(N); // แสดงข้อมูลเริ่มต้น
                printf("----------------------------------------------------------------\n");
                printf("Processing Data...\n");
                BubbleSort(N); // เรียก Bubble Sort
                printf("----------------------------------------------------------------\n");
                printf("Sorted Data : "); DispData(N); // แสดงผลลัพธ์สุดท้าย
                break;
            case 2:
                printf("\n");
                RunHeapSort(); // เรียกฟังก์ชัน Heap Sort ครบวงจร
                break;
            case 3:
                N = 4; // กำหนดจำนวนข้อมูล
                printf("\nASCENDING INSERTION SORT\n");
                printf("==============================\n");
                PrepareRawData(N); // สุ่มข้อมูล
                printf("Raw Data... "); DispData(N); // แสดงข้อมูลเดิม
                printf("Processing Data...\n");
                InsertionSort(N); // เรียก Insertion Sort
                printf("------------------------------------------------------------\n");
                printf("Sorted Data : "); DispData(N); // แสดงข้อมูลหลังเรียง
                break;
            case 4:
                N = 4; // กำหนดจำนวนข้อมูล
                printf("\nASCENDING QUICK SORT\n");
                printf("==============================\n");
                PrepareRawData(N); // สุ่มข้อมูล
                printf("Raw Data : "); DispData(N); // แสดงข้อมูลเดิม
                printf("Processing Data...\n");
                printf(" F R ");
                for(int i = 1; i <= N; i++) printf(" (%2d)", i);
                printf("\n");
                QuickSort(1, N); // เรียก Quick Sort
                printf("----------------------------------------------------------------\n");
                printf("Sorted Data : "); DispData(N); // แสดงข้อมูลหลังเรียง
                break;
            case 5:
                printf("\n");
                RunRadixSort(); // เรียก Radix Sort แบบเต็ม
                break;
            case 6:
                N = 4;
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