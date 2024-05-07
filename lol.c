#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

void ft_putnbr(int n)
{
    int i = n * 2 - 3;
    if( n == 1)
        exit(0);
    printf("%d ", n);
    while(i)
    {
        printf("%d ", n);
        i--;
    }
    printf("%d\n", n);
    if(n > 1)
    {
        ft_putnbr(n - 1);
        exit(1);
    }
}
    
int main() 
{

    int n;
    scanf("%d", &n);
    // return 0;
  	ft_putnbr(n);
}