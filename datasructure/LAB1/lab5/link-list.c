/* Program create SINGLY CIRCULAR LINKED LIST by...
 1. สร้างโหนด N โหนด
 2. สามารถแทรกโหนดหลังข้อมูลที่กำหนด
 3. สามารถลบโหนดหลังข้อมูลที่กำหนด
 4. แสดงที่อยู่ของโหนด
หมายเหตุ - ไม่อนุญาตให้ลบโหนดหัว
*/
#include <stdio.h>   // ใช้ printf
#include <stdlib.h>  // ใช้ malloc

#define HeadData -999 // ข้อมูลพิเศษของโหนดหัว

struct Node // ประกาศโครงสร้างของโหนด
{
    int info;
    struct Node *link;
};

struct Node *H, *H1, *p, *q; // ประกาศตัวชี้โหนด
int i,j,k,n,data;
char ch;

struct Node *Allocate() // จอง 1 โหนดจากพื้นที่เก็บข้อมูล
{
    struct Node *temp;  //สำหรับการเก็บที่อยู่แค่จำนวณ 8 byte และยังไม่ได้ชี้ไปที่ไหนหรือเป็นค่าไม่แน่นอน
    temp=(struct Node*)malloc(sizeof(struct Node)); // จองพื้นที่ที่มีขนาด หนึ่ง struct node (info + link) และจะคืนที่จองออกมาเป็น void*. ส่วน struct node*  คือการแปลงชนิด บอกคอมไพเลอร์ว่า ที่อยู่นี้เป็นของ struct node จะได้เข้าถึง ->info   ->link 
    return(temp);
}

void CreateNNode(int n) // สร้างโหนด N โหนด ใส่ข้อมูลและเชื่อมโยง
{
    int i,temp;
    p = Allocate();
    p->info = HeadData;   // กำหนดข้อมูลพิเศษ
    p->link = p;          // เชื่อมกลับตัวเอง
    H = p; H1 = p; // ให้ H และ H1 ชี้ไปที่โหนดหัว
    for (i=1;i<=n;i++) // นับ N โหนด
    {
        p=Allocate(); // จองโหนดใหม่
        // temp=1+rand()%99; // สุ่มเลข 1..99
        temp = 55;
        p->info=temp; // ใส่ข้อมูลสุ่มลงในโหนด
        H1->link=p;   // ให้โหนดสุดท้ายชี้ไปที่โหนดใหม่
        H1=p;         // ให้ H1 ชี้ไปที่โหนดใหม่
        H1->link=H;   // ตั้งค่า link ของ H1 ให้ชี้ไปที่ HEAD
    }
}

void ShowAllNode()
{
    printf("H = %p\n",(void*)H); // แสดงที่อยู่ของตัวชี้ H
    p=H->link; // ตั้งจุดเริ่มต้นของตัวชี้ p ที่โหนดแรก
    i=1; // ตั้งค่าเริ่มต้นของตัวนับ
    while (p->info != HeadData) // ถ้า INFO ไม่ใช่ HeadData
    {
        printf("%d) : %p\t",i,(void*)p); // แสดงตัวนับและตัวชี้
        printf("INFO : %d\t",p->info); // แสดงข้อมูล INFO
        printf("LINK : %p\n",(void*)p->link); // แสดงค่า LINK
        p=p->link; // ข้ามไปโหนดถัดไป
        i++; // เพิ่มตัวนับ/ชี้โหนดถัดไป
    }
}

void InsertAfter(int data1)
{
    int temp;
    if (H->link == H) // ถ้าตัวชี้ link ชี้กลับไปที่โหนดหัว
        printf("Circular Linked List have no node!!..\n");
    else
    {   int count = 1 ; // นับชั่วคราว
        H1=H->link; // ให้ H1 ชี้ที่โหนดแรก
        while (H1->info != HeadData) // ค้นหา while INFO<>HeadData
        {
            if (H1->info == data1) // ถาพบ
            {
                p=Allocate(); // จองโหนดจากพื้นที่เก็บข้อมูล
                printf("\nInsert data : ");
                scanf("%d",&temp);
                p->info=temp;      // เก็บข้อมูลชั่วคราวลงใน INFO ของโหนด
                p->link=H1->link;  // เปลี่ยนตัวชี้ด้านแรกเพื่อติดตั้งโหนด (FAR)
                H1->link=p;        // เปลี่ยนตัวชี้ด้านที่สองเพื่อติดตั้งโหนด (NEAR)
            }
            H1=H1->link; // ข้าม H1 ไปโหนดถัดไป
            count++;
        }
        printf("count = %d",count - 1);
    }
}

void DeleteAfter(int data1)
{
    if (H->link == H) // ถ้าตัวชี้ link ชี้กลับไปที่โหนดหัว
        printf("Circular Linked List have no node!!..\n");
    else
    {
        H1=H->link; // ให้ H1 ชี้ที่โหนดเริ่มต้น
        while (H1->info != HeadData) // ค้นหา while INFO<>HeadData
        {
            if (H1->info == data1) // ถาพบ
            {
                if (H1->link==H) // ถ้าไม่มีโหนดเพิ่มเติม
                    printf ("This is the HEAD Node,Can't delete it!!!\n");
                else
                {
                    p=H1->link;      // ระบุโหนดที่จะลบ
                    if(p->link==H)   // ถ้า p เป็นโหนดสุดท้าย
                        H1->link=H;  // ตั้งค่า link ของ H1 ให้ชี้ไปยังโหนดหัว
                    else
                        H1->link=p->link; // ถ้าไม่ใช่ ให้ตั้งค่า link ของ H1 ให้ชี้ไปที่ p->link
                    free(p); // คืนโหนดให้กับพื้นที่เก็บข้อมูล
                }
            }
            H1=H1->link; // ข้าม H1 ไปโหนดถัดไป
        }
    }
}

int main() // ฟังก์ชันหลัก
{
    n=5; // กำหนดจำนวนโหนด
    CreateNNode(n); // เรียกฟังก์ชันสร้าง N โหนด
    printf("PROGRAM SINGLY CIRCULAR LINKED LIST \n");
    printf("======================================== \n");
    printf("All Data in Linked List \n");
    ShowAllNode(); // เรียกฟังก์ชันแสดงข้อมูลทั้งหมด
    ch=' ';
    while (ch != 'E' && ch != 'e')
    {
        printf("MENU : [I:Insert D:Delete E:Exit]\n");
        printf("Select Menu : ");
        ch=getchar();
        while (ch=='\n') ch=getchar(); // ข้าม newline ที่เหลือ
        switch (ch)
        {
            case 'I' : case 'i' : 
                        printf("\nInsert After data : ");
                       scanf("%d",&data);
                       InsertAfter(data); // เรียกฟังก์ชันแทรกหลังข้อมูล
                       printf("\nAll Data in Linked List AFTER INSERTED\n");
                       ShowAllNode();
                       break;
            case 'D' : case 'd' : 
                        printf("\nDelete After data : ");
                       scanf("%d",&data);
                       DeleteAfter(data); // เรียกฟังก์ชันลบหลังข้อมูล
                       printf("\nAll Data in Linked List AFTER DELETED\n");
                       ShowAllNode();
                       break;
        }
    }
    return(0);
}