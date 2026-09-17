/* Program create Graph structure by "Sparse Matrix  
representation method".  
Can show the result of graph are .. 
 1. Set of vertex 
 2. Set of Edge 
Note.- can use both Undirected graph and Directed graph 
*/ 
#include <stdio.h> //use printf 
#include <conio.h> //use getch 
#include <stdlib.h>//use molloc 
#define MaxNode 4 // Define Max Node of Graph 
char NodeName[4] = {'A','B','C','D'};  
int graph[MaxNode][MaxNode] = {  
  {0,1,0,0},  
  {1,0,1,1},  
  {1,0,0,1},  
  {0,0,0,0},  
 }; //Declare array and keep data of graph 
struct Node //Declare structure of every node 
 {  
  char V1,V2;  
  struct Node *Row,*Column;  
 };  
struct Node *Start[MaxNode], *p, *Head; //Declare pointer uses 
struct Node *Allocate() //Allocate 1 node from storage pool 
{  
  struct Node *temp;  
  temp=(struct Node*)malloc(sizeof(struct Node)); //Allocate node by size declare 
  return(temp);  
}  
void CreateHeadRC() //Create Head Node 
 {  
  int i,j;  
  struct Node *row, *col;  
  p=Allocate(); //Create HEAD Node 
  Head=p; //Let Head point at this Node and FREEEZE it 
  row=Head;  
  for (i=0;i<MaxNode;i++) //Create HEAD ROW  
  {  
    p=Allocate();  
    row->Row=p; //Let ROW OF TEMP point to new node 
    row=p; //Change temp point to new node 
    row->V1=NodeName[i]; //Set Node Name 
    row->Row=NULL;  
    row->Column=NULL;  
  }  
  col=Head;  
  for (j=0;j<MaxNode;j++) //Create HEAD COLUMN 
  {  
    p=Allocate();  
    col->Column=p; //Let COLUMN OF TEMP point to new node 
    col=p; //Change temp point to new node 
    col->V2=NodeName[j]; //Set Node Name 
    col->Row=NULL;  
    col->Column=NULL;  
  }  
 }  
void TransferToSparseMT() //Transfer array to Sparse Matrix of graph 
 {  
  int i,j;  
  struct Node *row1, *row2, *col1, *col2;  
  row1=Head->Row;  
  i=0; //Start of Row in Array 
  while (row1 != NULL) //row loop 
  { 
    col1=Head->Column;  
    j=0; //Start of Column in Array 
    col2=row1; //Let COL2 Count Column2 at ROW Pointed 
    while (col1 != NULL) //column loop 
    {  
      if (graph[i][j]==1) //if PATH? 
      {  
        p=Allocate(); //get new Node 
        p->V1=row1->V1; // Set arrow tail of Edge 
        p->V2=col1->V2; //Set head tail of Edge 
        p->Row=NULL; //Set pointer as NULL default 
        p->Column=NULL; //Set pointer as NULL default 
        col2->Column=p; //Let Column2 at ROW point to New Node 
        col2=p; //Change COL2 position 
        row2=col1; //Mark ROW2 point at first ROW of COLUMN 
        while (row2->Row != NULL) //Find the last Node  
          row2=row2->Row; //Skip to next Node 
        row2->Row=p; //Let Row of Column point to this node 
      }  
      col1=col1->Column;  
      j++; // Skip to next Column Edge of Array 
    }  
    row1=row1->Row;  
    i++; // Skip to next Row Edge of Array 
  }  
 }  
void DispSetOfVertex() //Display set of Vertex 
 {  
  struct Node *row;  
  printf("\nSet of Vertex = {");  
  row=Head->Row; //Start Row at here 
  while (row != NULL) //Loop at Row direction 
  {  
    printf("%c",row->V1); //Display each node name 
    if(row->Row != NULL) 
      printf(",");  
    row=row->Row; //Skip to next Row 
  }  
  printf("}\n"); 
}  
void DispSetOfEdge() //Display set of Edge 
 {  
  struct Node *row, *col;  
  printf("\nSet of Edge = {");  
  row=Head->Row; //Start point of Row 
  while (row != NULL) //row loop 
  {  
    col=row->Column; //Start point of Column 
    while (col != NULL) //Column loop 
    {  
      printf("(%c,%c),",col->V1,col->V2); //Show each Edge 
      col=col->Column; //Skip to next Edge/Column 
    }  
    row=row->Row; //Skip to next Row 
  }  
  printf("}\n");  
 }  
int main() 
{  
  printf("GRAPH SPARSE MATRIX REPRESENTATION METHOD\n");  
  printf("=============================================\n");  
  CreateHeadRC();  
  TransferToSparseMT();  
  DispSetOfVertex();  
  DispSetOfEdge();  
  getch();  
  return(0);  
} //End Main