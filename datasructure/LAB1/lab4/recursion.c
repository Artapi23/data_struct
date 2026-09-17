/*
Code 4.3
Program Recursion can..
1. Calculate M^N Function
2. Show each step of recursive result
3. Show final result
===========================================================================
*/
#include <stdio.h> //use printf()
 
int Mbase, Nexp, ans;
 
/*
   Recursive definition of M^N (Power function)
   -----------------------------------------------
   Base Criteria : If N = 0 then M^N = 1
   Recursive case: If N > 0 then M^N = M * M^(N-1)
 
   Each recursive call reduces N by 1, moving the value closer
   to the Base Criteria (N = 0), which is required for the
   recursion to terminate.
*/
int Power(int M, int N)
{
    int x, y;
 
    if (N == 0)
    {
        printf("...............Roll Back Point\n");
        return (1); //Base Criteria : M^0 = 1
    }
    else
    {
        x = N - 1;
        printf("%2d^%2d = %2d * %2d^%2d\n", M, N, M, M, x); //Display before Recursive (Roll-down)
        y = Power(M, x);                                     //Recursive call itself
        printf("%2d^%2d = %2d * %3d = %5d\n", M, N, M, y, M * y); //Display after Recursive (Roll-back)
        return (M * y);
    }
} //End Fn
 
int main()
{
    printf("RECURSIVE (M^N) PROGRAM\n");
    printf("===========================\n");
 
    while (1)
    {
        printf("Enter Base M (-999 is END) : ");
        scanf("%d", &Mbase);
        if (Mbase == -999)
            break;
 
        printf("Enter Exponent N           : ");
        scanf("%d", &Nexp);
 
        if (Nexp >= 0)
        {
            printf("M^N = M * M^(N-1)\n");
            printf("------------------\n");
            ans = Power(Mbase, Nexp); //Recursive it self
            printf("\nAnswer %d^%d = %d\n", Mbase, Nexp, ans);
            printf("----------------Finished\n");
        }
    } //End while
    return (0);
} //End Main
 
