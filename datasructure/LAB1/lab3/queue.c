#include <stdio.h> //use printf()
#include <conio.h> //use getch()
#define N 5 //Set Max Queue 
int Q[N]; //Prepare Queue 0..N-1
int x, F = 0,R = 0; //Declare x and initial Front/Rear variable
char status = 'N'; //Initial Status = NORMAL
char ch; //KBD Read variable
void insertQ(int y) //INSERT Function
{ 
 if(R == N-1) //Check Queue FULL?
 { 
 printf("!!!OVER FLOW!!!...\n"); 
 status='O'; //set status = OVER FLOW
 } 
 else
 { 
 R=R+1; //Increase R
 if(F==0) 
 { 
F++; 
 } 
 Q[R]=y; //Put data into Queue
 } 
} 
int deleteQ() //DELETE Function
{ 
 int y; 
 if (F != 0) //Check QUEUE NOT EMPTY?
 { 
 y=Q[F]; //Get data from Queue
 if (F==R)
 { 
 F=0; R=0; 
 } 
 else
 { 
 F++; 
 } 
 return(y); //Return data
 } 
 else
 { 
 printf("\n!!!UNDER FLOW!!!...\n"); 
 status = 'U'; //set STATUS = "UNDER FLOW"
 } 
} 
void ShowAllQueue() //Display Function
{ 
 int i; //Counter variable
 printf("N : %d\n",N-1); 
 printf("Status : %c\n ",status); //Display STATUS
 printf("F : %d R : %d\n",F,R); //Display F&R
 for (i=1;i<N;i++) 
 { 
 printf("%d:%d / ",i, Q[i]); //Display all of data in QUEUE
 } 
 printf("\n----------------------------------------------------------\n"); 
} 
int main()
{ 
 printf("QUEUE PROGRAM...\n"); 
 printf("=======================\n"); 
 while (status == 'N') 
 { 
 printf("[1=INSERT : 2=DELETE] : "); //Show MENU
 ch = getch(); //Wait and read KBD with out ENTER Press
 switch(ch) //Check ch
 { 
 case '1' : printf("\nInsert Number : "); 
 scanf("%d", &x); //Read data from KBD
 insertQ(x); //Call INSERTNQ Function
 ShowAllQueue(); //Display all data in Queue
 break; 
 case '2' : x=deleteQ(); //Delete data
 printf("\nData from Queue = %d\n",x); //Display it
 ShowAllQueue(); //Display all data in Queue
 break; 
 } //End SWITCH CASE
 } //End WHILE Loop
 printf("\n"); //line feed
 return(0); 
}//End MAIN Fn