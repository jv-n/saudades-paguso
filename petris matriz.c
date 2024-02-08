#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int p;
    int x = 0;
    int y = 0;
    char* aux;

    scanf("%d", &p);

    int i = 0;
    char controle[6];
    int temp;
    char** petris = NULL;
    while (i<p)
    {   
        strcpy(controle, "GO");
        while(strcmp(controle, "END")!=0)
        {
            scanf(" %5[^\n]", controle);
            if(strcmp(controle, "END")!=0)
            {   
                if(atoi(controle) == x+1)
                {
                    x = atoi(controle);
                    printf("%d", x);
                    petris = (char**) realloc(petris, sizeof(char*)*x);
                    petris[x-1] = malloc(sizeof(char));
                    aux = strstr(controle, " ");
                    petris[x-1][0] = aux[0];
                    printf("%c\n", petris[x-1][0]);
                }
            }
            
        }
        printf("caso %d:", p);
        if(petris!=NULL)
        {
            for(int k = 0; k<0; k++)
            {

            }
        }
        i++;
    }    

    return 0;
}