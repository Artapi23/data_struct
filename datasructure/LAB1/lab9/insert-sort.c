/* Program ASCENDING INSERTION SORT
1. Random raw data into 1 dimension Array
2. Sorting and display detail of each result
3. Display final result
*/
#include <stdio.h>  // use printf, getchar
#include <stdlib.h> // use rand, srand
#include <time.h>   // use time

#define MaxData 100 // Define Max Data

int Data[MaxData];
int N;

void PrepareRawData(int N)
{
    int i;
    srand((unsigned int)time(NULL)); // สุ่มค่าตั้งต้นตามเวลา
    for (i = 1; i <= N; i++)
        Data[i] = 1 + rand() % 99; // สุ่มตัวเลข 1..99
}

void DispData(int N)
{
    int i;
    for (i = 1; i <= N; i++)
        printf("%2d ", Data[i]);
    printf("\n");
}

void InsertionSort(int N)
{
    int i, j, temp;
    printf("---------------------------------------------------------------------\n");
    printf(" i  ");
    for (i = 1; i <= N; i++)
        printf(" (%2d)", i);
    printf("\n");
    printf("---------------------------------------------------------------------\n");
    printf("%2d. ", 0);
    DispData(N); // แสดงข้อมูลเริ่มต้น

    for (i = 1; i < N; i++) // ตรวจสอบจากซ้ายไปขวา
    {
        if (Data[i + 1] < Data[i]) // ถ้าตัวถัดไปน้อยกว่าตัวก่อนหน้า
        {
            temp = Data[i + 1]; // เก็บค่าตัวที่จะแทรกไว้ใน temp
            Data[i + 1] = 0;    // กำหนดเป็น 0 เพื่อแสดงตำแหน่งว่างขณะสลับ
            j = i;

            // เพิ่มเงื่อนไข j >= 1 ป้องกันไม่ให้ถอยหลังหลุดขอบ Array
            while (j >= 1 && temp < Data[j]) 
            {
                Data[j + 1] = Data[j]; // เลื่อนข้อมูลไปข้างหน้า
                Data[j] = 0;
                printf("%2d. ", i + 1);
                DispData(N);           // แสดงขั้นตอนการเลื่อนข้อมูล
                j = j - 1;             // ถอยกลับไปตรวจตัวก่อนหน้า
            }

            Data[j + 1] = temp;        // วางค่าที่ต้องการแทรกลงในช่องที่ว่าง
            printf("%2d. ", i + 1);
            DispData(N);               // แสดงข้อมูลหลังแทรกสำเร็จ
        }
    }
}

int main()
{
    printf("ASCENDING INSERTION SORT\n");
    printf("==============================\n");
    N = 12;
    PrepareRawData(N);
    
    printf("Raw Data...: ");
    DispData(N);
    
    printf("Processing Data...\n");
    InsertionSort(N);
    
    printf("---------------------------------------------------------------------\n");
    printf("Sorted Data: ");
    DispData(N); // แสดงผลลัพธ์สุดท้าย

    printf("\nPress Enter to exit...");
    getchar(); // ใช้แทน getch() เพื่อให้รันได้ทุกระบบปฏิบัติการ
    return 0;
}