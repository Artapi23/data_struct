/* Program create DOUBLY LINKED LIST by...
1. Create Node N Nodes
2. Can Insert node before/after data as defined
3. Can Delete node before/itself/after data as defined
4. Show address of Node

   Adapted from Turbo C to Linux/gcc:
   - removed conio.h (getch -> use custom getMenuChar() with scanf)
   - added "typedef struct Node Node;" so that "Node *Allocate()" compiles
     under standard C (Turbo C allowed the struct tag to be used as a type
     name directly; gcc does not)
   - changed address format specifier from %x to %p (correct way to print
     a pointer; %x truncates 64-bit addresses on modern systems)
*/
#include <stdio.h>   //use printf
#include <stdlib.h>  //use malloc

struct Node                //Declare structure of node
{
    int info;
    struct Node *llink;
    struct Node *rlink;
};
typedef struct Node Node;  //ADAPTED: allow "Node" to be used as a type name

struct Node *H, *H1, *p, *q;   // Declare pointer node
int i,j,k,n,data;
char ch;

Node *Allocate()  //Allocate 1 node from storage pool
{
    struct Node *temp;
    temp=(Node*)malloc(sizeof(Node));  //Allocate node by size declare
    return(temp);
}

void CreateNNode(int n)  //Create N Node put data and link it
{
    int i,temp;
    H=NULL;H1=NULL;
    for (i=1;i<=n;i++)   //Count N Node
    {
        p=Allocate();               //Allocate Node
        // temp=1+rand() % 99;         //random difference number 1..99
        temp = 55;
        p->info=temp;               //Put random data in to node
        if (i==1)
            H=p;                    //Set H point to first node
        else
        {
            H1->rlink=p;            //Link first node to second node
            p->llink=H1;
        }
        H1=p;                       //Let H1 point to last node
        H1->rlink=NULL;             //Set rlink of H1 to NULL
    }
}

void ShowAllNode()
{
    printf("H = %p\n",(void*)H);          //Display address of pointer H
    p=H;                                  //Set start point of p pointer
    i=1;                                  //set start value of counter
    while (p != NULL)                     //While if NOT NULL
    {
        printf("%d) : %p\t",i,(void*)p);          //Show COUNTER and POINTER
        printf("LLINK : %p\t",(void*)p->llink);   //Show LLINK
        printf("INFO : %d\t",p->info);            //Show INFO
        printf("RLINK : %p\n",(void*)p->rlink);   //Show RLINK
        p=p->rlink;                        //Skip to next node
        i++;                               //Skip Counter
    } //End While
} //End Fn.

void InsertAfter(int data1)
{
    int temp;                     //Temporary variable
    if (H==NULL)
        printf("Linked List have no node!!..\n");
    else
    {
        H1=H;                     //Let H1 point at start node
        while (H1 != NULL)        // Search for the data while H1<>NULL
        {
            if (H1->info == data1)   //if Found
            {
                p=Allocate();                    //Allocate one node from storage pool
                printf("\nInsert data : " );      //Input data for insert
                scanf("%d",&temp);                //Read from KBD
                p->info=temp;                     // Entry temporary data into INFO of node
                if (H1->rlink == NULL)
                {
                    p->rlink=NULL;
                }
                else
                {
                    p->rlink=H1->rlink;           //Change pointer 1st for insert node (FAR to NEAR)
                    H1->rlink->llink=p;            //LLINK(RLINK(H1))=p
                }
                p->llink=H1;      //LLINK(P)=H1
                H1->rlink=p;      //RLINK(H1)=p
            } //End if
            H1=H1->rlink;         //Skip H1 to next node
        } //End while
    } //End IF
} //End Fn.

void InsertBefore(int data1)
{
    int temp;                     //Temporary variable
    if (H==NULL)
        printf("Linked List have no node!!..\n");
    else
    {
        H1=H;                     //Let H1 point at start node
        while (H1 != NULL)        // Search for the data while H1<>NULL
        {
            if (H1->info == data1)   //if Found
            {
                p=Allocate();                    //Allocate one node from storage pool
                printf("\nInsert data : " );      //Input data for insert
                scanf("%d",&temp);                //Read from KBD
                p->info=temp;                     // Entry temporary data into INFO of node
                if (H1->llink == NULL)
                {
                    p->llink=NULL;
                    H=p;
                }
                else
                {
                    H1->llink->rlink=p;           //RLINK(LLINK(H1))=p
                    p->llink=H1->llink;            //LLINK(p)=LLINK(H1)
                }
                H1->llink=p;      //LLINK(H1)=p
                p->rlink=H1;      //RLINK(P)=H1
            } //End if
            H1=H1->rlink;         //Skip H1 to next node
        } //End while
    } //End IF
} //End Fn.

void DeleteBefore(int data1) //ลบโหนดที่อยู่ก่อนหน้าที่โหนดค้นเจอ
{
    int temp;                     //ตัวแปรชั่วคราว (ฟังก์ชันนี้ไม่ได้ใช้จริง)
    if (H==NULL)                  //ตรวจก่อนว่ามีโหนดในลิสต์หรือยัง
        printf("Linked List have NO NODE!!..\n");   //ลิสต์ว่าง ทำอะไรไม่ได้
    else
    {
        H1=H;                     //ให้ H1 เริ่มชี้ที่โหนดแรก เพื่อใช้เดินหา
        while (H1 != NULL)        //วนหาจนกว่าจะสุดลิสต์
        {
            if (H1->info == data1)   //เจอโหนดที่มีข้อมูลตรงกับที่ผู้ใช้ระบุ
            {
                if (H1->llink==NULL)  //H1 เป็นโหนดแรก แปลว่าไม่มีโหนดข้างหน้าให้ลบ
                    printf ("No more node from here,Can't delete it!!!\n");
                else
                {
                    p=H1->llink;              //ให้ p ชี้โหนดก่อนหน้า = โหนดที่จะถูกลบ
                    if(p->llink==NULL)        //p เป็นโหนดแรกของลิสต์ (ไม่มีโหนดก่อนหน้า p)
                    {
                        H1->llink=NULL;       //ตัด llink ของ H1 ทิ้ง H1 จะกลายเป็นโหนดแรก
                        H=H1;                 //ย้ายหัวลิสต์ H มาชี้ที่ H1
                    }
                    else                      //p อยู่กลางลิสต์ ต้องเชื่อมโหนดซ้าย-ขวาข้าม p
                    {
                        H1->llink=p->llink;       //ให้ H1 ชี้ย้อนกลับข้าม p ไปหาโหนดก่อน p
                        p->llink->rlink=H1;       //ให้โหนดก่อน p ชี้ไปข้างหน้าข้าม p มาที่ H1
                    }
                    free(p);                  //คืนหน่วยความจำของโหนด p ให้ระบบ
                } //End if2
            } //End if1
            H1=H1->rlink;         //เลื่อน H1 ไปโหนดถัดไป (วนต่อเผื่อมีข้อมูลซ้ำ)
        } //End while
    } //End IF
} //End Fn.

void DeleteSelf(int data1) //ลบตัวโหนดที่ค้นเจอเอง
{
    int temp;                     //ตัวแปรชั่วคราว (ฟังก์ชันนี้ไม่ได้ใช้จริง)
    if (H==NULL)                  //ตรวจก่อนว่ามีโหนดในลิสต์หรือยัง
        printf("Linked List have NO NODE!!..\n");
    else
    {
        H1=H;                     //ให้ H1 เริ่มชี้ที่โหนดแรก
        while (H1 != NULL)        //วนหาจนกว่าจะสุดลิสต์
        {
            if (H1->info == data1)   //เจอโหนดที่ต้องการลบ
            {
                p=H1;                          //ให้ p ชี้โหนดที่จะลบ (คือตัว H1 เอง)

                if(p->llink==NULL && p->rlink==NULL)  //กรณีที่ 1 : เหลือโหนดเดียวในลิสต์
                    H=NULL;                    //ลบแล้วลิสต์ว่าง ตั้งหัวลิสต์เป็น NULL
                else
                {
                    if(p->llink==NULL)          //กรณีที่ 2 : p เป็นโหนดแรก
                    {
                        H=p->rlink;              //เลื่อนหัวลิสต์ไปโหนดถัดไป
                        H->llink=NULL;           //โหนดใหม่ที่เป็นหัว ต้องไม่มี llink
                    }
                    else
                    {
                        if(p->rlink==NULL)       //กรณีที่ 3 : p เป็นโหนดสุดท้าย
                            p->llink->rlink=NULL;  //ให้โหนดก่อนหน้ากลายเป็นตัวสุดท้าย
                        else                     //กรณีที่ 4 : p อยู่กลางลิสต์
                        {
                            p->llink->rlink=p->rlink;  //โหนดซ้ายชี้ข้าม p ไปหาโหนดขวา
                            p->rlink->llink=p->llink;  //โหนดขวาชี้ย้อนข้าม p ไปหาโหนดซ้าย
                        }
                    }
                }
                free(p);              //คืนหน่วยความจำของโหนด p ให้ระบบ
            } //End if1
            H1=H1->rlink;         //เลื่อน H1 ไปโหนดถัดไป
        } //End while
    } //End IF
} //End Fn.

void DeleteAfter(int data1) //ลบโหนดที่อยู่่ถัดจากโหนดที่พบเจอ
{
    int temp;                     //ตัวแปรชั่วคราว (ฟังก์ชันนี้ไม่ได้ใช้จริง)
    if (H==NULL)                  //ตรวจก่อนว่ามีโหนดในลิสต์หรือยัง
        printf("Linked List have NO NODE!!..\n");
    else
    {
        H1=H;                     //ให้ H1 เริ่มชี้ที่โหนดแรก
        while (H1 != NULL)        //วนหาจนกว่าจะสุดลิสต์
        {
            if (H1->info == data1)   //เจอโหนดที่มีข้อมูลตรงกับที่ผู้ใช้ระบุ
            {
                if (H1->rlink==NULL)  //H1 เป็นโหนดสุดท้าย ไม่มีโหนดถัดไปให้ลบ
                    printf ("No more node from here,Can't delete it!!!\n");
                else
                {
                    p=H1->rlink;             //ให้ p ชี้โหนดถัดไป = โหนดที่จะถูกลบ
                    if(p->rlink==NULL)       //p เป็นโหนดสุดท้ายของลิสต์
                        H1->rlink=NULL;      //ตัด rlink ของ H1 ทิ้ง H1 กลายเป็นโหนดสุดท้าย
                    else                     //p อยู่กลางลิสต์ ต้องเชื่อมข้าม p
                    {
                        H1->rlink=p->rlink;      //ให้ H1 ชี้ไปข้างหน้าข้าม p ไปหาโหนดหลัง p
                        p->rlink->llink=H1;      //ให้โหนดหลัง p ชี้ย้อนกลับข้าม p มาที่ H1
                    }
                    free(p);                 //คืนหน่วยความจำของโหนด p ให้ระบบ
                } //End if2
            } //End if1
            H1=H1->rlink;         //เลื่อน H1 ไปโหนดถัดไป
        } //End while
    } //End IF
} //End Fn.

char getMenuChar()   //ADAPTED replacement for Turbo C's getch()
{
    char c;
    scanf(" %c",&c);   // %c with leading space skips whitespace/newline
    return c;
}

int main()   //MAIN Fn.
{
    n=3;                    //Set amount of node
    CreateNNode(n);          //Call Fn. Create N nodes
    printf("PROGRAM DOUBLY LINKED LIST \n");
    printf("================================== \n");
    printf("All Data in Linked List \n");
    ShowAllNode();           //Call Fn. Show all node
    ch=' ';
    while (ch != 'E')
    {
        printf("MENU>> [B:InsertBefore A:InsertAfter\n");
        printf("        O:DeleteBefore X:Delete itself\n");
        printf("        D:DeleteAfter E:Exit]\n");
        printf("Select Menu : ");
        ch=getMenuChar();
        switch (ch)
        {
            case 'B' : printf("\nInsert Before data : " ); //Input data for insert before
                       scanf("%d",&data);
                       InsertBefore(data);      //Call Fn. Insert before data
                       printf("\nAll Data in Linked List Before INSERTED\n");
                       ShowAllNode();           //Call Fn. Show all node
                       break;
            case 'A' : printf("\nInsert After data : " );  //Input data for insert after
                       scanf("%d",&data);
                       InsertAfter(data);       //Call Fn. Insert after data
                       printf("\nAll Data in Linked List AFTER INSERTED\n");
                       ShowAllNode();           //Call Fn. Show all node
                       break;
            case 'O' : printf("\nDelete Before data : " );  //Input data for Delete before
                       scanf("%d",&data);
                       DeleteBefore(data);      //Call Fn. Delete before data
                       printf("\nAll Data in Linked List AFTER DELETED\n");
                       ShowAllNode();           //Call Fn. Show all node
                       break;
            case 'X' : printf("\nDelete ItSelf data : " );  //Input data for Delete self
                       scanf("%d",&data);
                       DeleteSelf(data);        //Call Fn. Delete self data
                       printf("\nAll Data in Linked List ITSELF DELETED\n");
                       ShowAllNode();           //Call Fn. Show all node
                       break;
            case 'D' : printf("\nDelete After data : " );   //Input data for Delete after
                       scanf("%d",&data);
                       DeleteAfter(data);       //Call Fn. Delete after data
                       printf("\nAll Data in Linked List AFTER DELETED\n");
                       ShowAllNode();           //Call Fn. Show all node
                       break;
        } // End Switch...case
    } //End While
    return 0;
} //End MAIN