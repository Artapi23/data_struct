#include <stdio.h>      // ใช้งาน printf(), getchar()
#include <stdlib.h>     // ใช้งาน rand(), srand()
#include <time.h>       // ใช้งาน time()

#define MaxNode 100     // จำนวนช่องสูงสุดของอาเรย์
#define MAX_LEVEL 5    // จำนวนระดับของต้นไม้
#define NODE_COUNT 31   // จำนวนโหนดทั้งหมด

int N = NODE_COUNT;     // จำนวนโหนดที่ใช้งาน
int data[MaxNode] = {0}; // อาเรย์เก็บข้อมูลของแต่ละโหนด

// สร้างข้อมูลแบบ Node Sequence
void CreateTreeNS(int n)
{
    // สร้างค่าตัวเลขสุ่มตั้งแต่ 1 ถึง 99
    for (int i = 1; i <= n; i++)
        data[i] = 1 + rand() % 99;
}

// แสดงข้อมูลในรูปแบบอาเรย์
void ShowArray(void)
{
    printf("\nNode Sequence:\n");

    // แสดงข้อมูลตั้งแต่โหนดที่ 1 ถึง N
    for (int i = 1; i <= N; i++)
        printf("[%d]%02d ", i, data[i]);

    printf("\n============================================================\n");
}

// แสดงต้นไม้ตามระดับ
void ShowTree(void)
{
    printf("\nTree Structure:\n\n");

    // วนแสดงต้นไม้ทีละระดับ
    for (int level = 1; level <= MAX_LEVEL; level++)
    {
        // คำนวณตำแหน่งเริ่มต้นและสิ้นสุดของแต่ละระดับ
        int start = 1 << (level - 1);
        int end = (1 << level) - 1;

        // คำนวณระยะห่างก่อนเริ่มแสดงข้อมูล
        int indent = (1 << (MAX_LEVEL - level)) * 3;

        // คำนวณระยะห่างระหว่างโหนด
        int gap = (1 << (MAX_LEVEL - level + 1)) * 3;

        // เว้นระยะด้านซ้าย
        for (int space = 0; space < indent; space++)
            printf(" ");

        // แสดงข้อมูลของแต่ละโหนดในระดับนั้น
        for (int i = start; i <= end; i++)
        {
            printf("%02d", data[i]);

            // เว้นระยะระหว่างโหนด
            if (i < end)
            {
                for (int space = 0; space < gap; space++)
                    printf(" ");
            }
        }

        printf("\n\n");
    }

    printf("============================================================\n");
}

// ท่องต้นไม้แบบ PreOrder: Root -> Left -> Right
void PreOrder(int i)
{
    // หยุดเมื่อเกินจำนวนโหนด หรือไม่มีข้อมูล
    if (i > N || data[i] == 0)
        return;

    // แสดงข้อมูล Root ก่อน
    printf(" %d", data[i]);

    // ไปยังลูกซ้าย
    PreOrder(2 * i);

    // ไปยังลูกขวา
    PreOrder(2 * i + 1);
}

// ท่องต้นไม้แบบ InOrder: Left -> Root -> Right
void InOrder(int i)
{
    // หยุดเมื่อเกินจำนวนโหนด หรือไม่มีข้อมูล
    if (i > N || data[i] == 0)
        return;

    // ไปยังลูกซ้าย
    InOrder(2 * i);

    // แสดงข้อมูล Root
    printf(" %d", data[i]);

    // ไปยังลูกขวา
    InOrder(2 * i + 1);
}

// ท่องต้นไม้แบบ PostOrder: Left -> Right -> Root
void PostOrder(int i)
{
    // หยุดเมื่อเกินจำนวนโหนด หรือไม่มีข้อมูล
    if (i > N || data[i] == 0)
        return;

    // ไปยังลูกซ้าย
    PostOrder(2 * i);

    // ไปยังลูกขวา
    PostOrder(2 * i + 1);

    // แสดงข้อมูล Root เป็นลำดับสุดท้าย
    printf(" %d", data[i]);
}

// ฟังก์ชันหลักของโปรแกรม
int main(void)
{
    char ch; // เก็บตัวเลือกเมนูจากผู้ใช้
    int c;   // ใช้ล้างข้อมูลที่เหลือใน Input Buffer

    // กำหนดค่าเริ่มต้นสำหรับการสุ่มตัวเลข
    srand((unsigned int)time(NULL));

    // สร้างต้นไม้
    CreateTreeNS(N);

    // แสดงเมนูจนกว่าผู้ใช้จะเลือก E
    do
    {
        printf("\nTREE (NODE SEQUENCE)\n");
        printf("==================================\n");

        // แสดงข้อมูลแบบอาเรย์
        ShowArray();

        // แสดงข้อมูลแบบต้นไม้
        ShowTree();

        // แสดงเมนู
        printf("\nMENU\n");
        printf("P : PreOrder\n");
        printf("I : InOrder\n");
        printf("O : PostOrder\n");
        printf("E : Exit\n");
        printf("Select: ");

        // รับตัวเลือกจากผู้ใช้
        ch = (char)getchar();

        // ล้างข้อมูลที่เหลือหลังจากกด Enter
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }

        // ตรวจสอบตัวเลือกเมนู
        switch (ch)
        {
            case 'P':
            case 'p':
                printf("\nPRE ORDER TRAVERSAL :");
                PreOrder(1); // เริ่มต้นที่ Root index 1
                printf("\n");
                break;

            case 'I':
            case 'i':
                printf("\nIN ORDER TRAVERSAL :");
                InOrder(1); // เริ่มต้นที่ Root index 1
                printf("\n");
                break;

            case 'O':
            case 'o':
                printf("\nPOST ORDER TRAVERSAL :");
                PostOrder(1); // เริ่มต้นที่ Root index 1
                printf("\n");
                break;

            case 'E':
            case 'e':
                printf("\nExit program.\n");
                break;

            default:
                printf("\nInvalid choice.\n");
        }

    } while (ch != 'E' && ch != 'e');

    // จบการทำงานของโปรแกรม
    return 0;
}