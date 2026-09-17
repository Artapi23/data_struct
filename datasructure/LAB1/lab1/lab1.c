#include <stdio.h>
#include <stdlib.h>

#define l 1
#define u 5
#define l1 1
#define u1 3
#define l2 1
#define u2 4
#define l3 1
#define u3 5

typedef int ElementType;

// คงเหลือเฉพาะ Base Address ที่จำเป็นต้องใช้ข้ามฟังก์ชัน
ElementType *BA1, *BA2, *BA3, *BA4;

void Create1DArray(){
    int element = (u - l + 1);
    BA1 = (ElementType*)malloc(element * sizeof(ElementType));
}

void A1(int i, int x){
    ElementType *p = BA1 + (i - l); // ใช้ Local Pointer ป้องกันข้อมูลตีกัน
    *p = x;
}

int ReadA1(int i) {
    ElementType *p = BA1 + (i - l);
    printf("Address of A1(%d) = %p\n", i, (void*)p);
    printf("Value at A1(%d) = %d\n", i, *p);
    printf("Size of element in A1 = %zu bytes\n", sizeof(ElementType));
    printf("Total Memory allocated for A1 = %zu bytes\n", (u - l + 1) * sizeof(ElementType));
    return (*p);
}

void Create2DArray() {
    int element = (u1 - l1 + 1) * (u2 - l2 + 1);
    BA2 = (ElementType*)malloc(element * sizeof(ElementType));
}

void A2(int i, int j, int x) {
    ElementType *p = BA2 + ((i - l1) * (u2 - l2 + 1) + (j - l2));
    *p = x;
}

int ReadA2(int i, int j) {
    ElementType *p = BA2 + (i - l1) * (u2 - l2 + 1) + (j - l2);
    printf("Address of A2(%d,%d) = %p\n", i, j, (void*)p);
    printf("Value at A2(%d,%d) = %d\n", i, j, *p);
    printf("Size of element in A2 = %zu bytes\n", sizeof(ElementType));
    printf("Total Memory allocated for A2 = %zu bytes\n", (u1 - l1 + 1) * (u2 - l2 + 1) * sizeof(ElementType));
    return (*p);
}

void Create3DArray() {
    int element = (u1 - l1 + 1) * (u2 - l2 + 1) * (u3 - l3 + 1);
    BA3 = (ElementType*)malloc(element * sizeof(ElementType));
}

void A3(int i, int j, int k, int x) {
    ElementType *p = BA3 + ((i - l1) * (u2 - l2 + 1) * (u3 - l3 + 1) + (j - l2) * (u3 - l3 + 1) + (k - l3));
    *p = x;
}

int ReadA3(int i, int j, int k){
    ElementType *p = BA3 + ((i - l1) * (u2 - l2 + 1) * (u3 - l3 + 1) + (j - l2) * (u3 - l3 + 1) + (k - l3));
    printf("Address of A3(%d,%d,%d) = %p\n", i, j, k, (void*)p);
    printf("Value at A3(%d,%d,%d) = %d\n", i, j, k, *p);
    return (*p);
}

void Create3DArray2() {
    int element = (u1 - l1 + 1) * (u2 - l2 + 1) * (u3 - l3 + 1);
    BA4 = (ElementType*)malloc(element * sizeof(ElementType));
}

// ปรับสูตรการสลับแกนให้ถูกต้องตามหลักเลขคณิตศาสตร์ในการทำ Mapping
void A4(int i, int j, int k, int x) {
    ElementType *p = BA4 + ((j - l2) * (u3 - l3 + 1) * (u1 - l1 + 1) + (k - l3) * (u1 - l1 + 1) + (i - l1));
    *p = x;
}

int ReadA4(int i, int j, int k){
    ElementType *p = BA4 + ((j - l2) * (u3 - l3 + 1) * (u1 - l1 + 1) + (k - l3) * (u1 - l1 + 1) + (i - l1));
    printf("Address of A4(%d,%d,%d) = %p\n", i, j, k, (void*)p);
    printf("Value at A4(%d,%d,%d) = %d\n", i, j, k, *p);
    return (*p);
}

int main() {
    // ประกาศตัวแปรดัชนีเป็น Local 
    int test_i, test_j, test_k;
    int val1, val2, val3, val4;

    printf("\n=== 1D-3D ARRAY ADDRESS DEMO ===\n");
    Create1DArray();
    Create2DArray();
    Create3DArray();
    Create3DArray2();

    // 1D Array Testing
    printf("\nUsing 1D Array...\n");
    test_i = 2;
    A1(test_i, 9);
    val1 = ReadA1(test_i); // เรียกเก็บค่าไว้ก่อนพิมพ์ป้องกันการสลับบรรทต
    printf("Result: A1(%d) = %d\n", test_i, val1);

    // 2D Array Testing
    printf("\nUsing 2D Array...\n");
    test_i = 2; test_j = 3;
    A2(test_i, test_j, 99);
    val2 = ReadA2(test_i, test_j);
    printf("Result: A2(%d,%d) = %d\n", test_i, test_j, val2);

    // 3D Array Testing (Standard)
    printf("\nUsing 3D Array (Row-Major)...\n");
    test_i = 3; test_j = 4; test_k = 5;
    A3(test_i, test_j, test_k, 999);
    val3 = ReadA3(test_i, test_j, test_k);
    printf("Result: A3(%d,%d,%d) = %d\n", test_i, test_j, test_k, val3);

    // 3D Array Testing (Alternative)
    printf("\nUsing 3D Array (Alternative)...\n");
    test_i = 3; test_j = 4; test_k = 5;
    A4(test_i, test_j, test_k, 123);
    val4 = ReadA4(test_i, test_j, test_k);
    printf("Result: A4(%d,%d,%d) = %d\n", test_i, test_j, test_k, val4);

    free(BA1);
    free(BA2);
    free(BA3);
    free(BA4);
    return 0;
}