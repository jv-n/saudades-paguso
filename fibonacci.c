#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){

    int* fibonacci = NULL;
    
    long int n;
    scanf("%ld", &n);
    fibonacci = (int*) realloc(fibonacci, sizeof(long int)*n);
    if(fibonacci == NULL)
    {
        printf("Falha de Alocacao");
        exit(1);
    }

    fibonacci[0] = 0;
    
    if(n>1)
    {
        fibonacci[1] = 1;
    
        for(int i = 1; i<n; i++)
        {
            fibonacci[i+1] = fibonacci[i] + fibonacci[i-1];
        }
    }

    printf("%d", fibonacci[n-1]);
    free(fibonacci);
    return 0;
}