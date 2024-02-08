#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
    int valor;
    int estado;

} Jazigo;

typedef struct 
{
    int andar;
    int nmr_jazigo;
    int interaction;

} query_result;


typedef struct 
{
    Jazigo* jazigos;
    int ocupados;

} Cemiterio;

int hash(int id, int andar);
int add(Cemiterio cemiterio[], int k, int j, int id);
void remover(Cemiterio cemiterio[], int val, int jazigo, int andar);
query_result query(Cemiterio cemiterio[], int val, int jazigo, int andar);

int main()
{
    int andar; 
    int jazigo;
    int id;
    int andares_cheios = 0;
    char input[12] = "GO";

    scanf("%d %d", &andar, &jazigo);

    Cemiterio* cemiterio = (Cemiterio*) malloc(andar*sizeof(Cemiterio));

    for(int j = 0; j<andar; j++)
    {
        cemiterio[j].ocupados = 0;
        cemiterio[j].jazigos = (Jazigo*) malloc(jazigo*sizeof(Jazigo));
        for(int x = 0; x<jazigo; x++)
        {
            cemiterio[j].jazigos[x].estado = 0;
            cemiterio[j].jazigos[x].valor = 0;
        }
    }

    while(strcmp(input, "END")!=0)
    {
        scanf(" %11[^\n]", input);

        if(strcmp(input, "END")!=0)
        {
            char function[4];
            strncpy(function, input, 3);
            function[3] = '\0';
            char* aux = strstr(input, " ");
            if(aux!=NULL){
                aux++;
                id = atoi(aux);
            }
            if(strcmp(function, "ADD") == 0)
            {
                int k = hash(id, andar);
                andares_cheios = 0;
                
                while(cemiterio[k].ocupados == jazigo)
                {
                    andares_cheios++;
                    if(andares_cheios == andar)
                    {
                        int val = 0;
                        int* temp = (int*) malloc(sizeof(int)*(andar*jazigo));
                        for(int a = 0; a<andar; a++)
                        {
                            for(int b = 0; b<jazigo; b++)
                            {
                                if(cemiterio[a].jazigos[b].estado == 1)
                                {
                                    temp[val] = cemiterio[a].jazigos[b].valor;
                                    val++;
                                } 
                            }
                        }
                        
                        andar = (2*andar)+1;
                        andares_cheios = 0;
                         
                        cemiterio = (Cemiterio*) malloc(andar*sizeof(Cemiterio));

                        for(int j = 0; j<andar; j++)
                        {
                            cemiterio[j].ocupados = 0;
                            cemiterio[j].jazigos = (Jazigo*) malloc(jazigo*sizeof(Jazigo));
                            for(int x = 0; x<jazigo; x++)
                            {
                                cemiterio[j].jazigos[x].estado = 0;
                                cemiterio[j].jazigos[x].valor = 0;
                            }
                        }
                         
                        for(int a = 0; a<val; a++)
                        {
                            int l = hash(temp[a], andar);
                            while(cemiterio[l].ocupados == jazigo)
                            {
                                andares_cheios++;
                                l = hash(hash(temp[a],andar)+andares_cheios, andar);
                            }
                            for(int b = 0; b<jazigo; b++)
                            {
                                if(cemiterio[l].jazigos[b].estado == 0)
                                {
                                    add(cemiterio, l, b, temp[a]);
                                    cemiterio[l].ocupados++;
                                    break;
                                }
                            }
                        }
                        k = hash (id, andar);
                    } else k = hash(hash(id, andar)+andares_cheios, andar);                    
                }

                for(int j = 0; j<jazigo; j++)
                {
                    if(cemiterio[k].jazigos[j].estado == 0)
                    {
                        int number = add(cemiterio, k, j, id);
                        cemiterio[k].ocupados++;
                        printf("%d.%d\n", k, number);
                        break;
                    }
                                    
                }
                           
            }
            else if(strcmp(function, "REM") == 0)
            {
                remover(cemiterio, id, jazigo, andar);
            }
            else if(strcmp(function, "QRY") == 0)
            {
                query(cemiterio, id, jazigo, andar);
            }
            else if(strcmp(function, "PRT") == 0)
            {
                for(int j = 0; j<andar; j++)
                {
                    printf("L%d: ", j);
                    for(int b = 0; b<jazigo; b++)
                    {
                        printf("%d(%d) ", cemiterio[j].jazigos[b].valor, cemiterio[j].jazigos[b].estado);
                    }
                    printf("\n");
                }
            }        
        }
    }
    return 0;
}

query_result query(Cemiterio cemiterio[], int val, int jazigo, int andar)
{
    int l;
    int r;
    int m = 0;
    int i = 0;
    int confirm_interaction = 0;
    
    while(i<andar)
    {
        l = 0; r = jazigo-1;
        while(l<=r)
        {
            m = (l+r)/2;
            if(cemiterio[i].jazigos[m].valor == val)
            {
                if(cemiterio[i].jazigos[m].estado == 2)
                {
                    printf("?.?\n");
                    confirm_interaction = 1;
                    break;
                }
                else
                { 
                    printf("%d.%d\n", i, m);
                    confirm_interaction = 1;
                    break;
                }
            } else if(val<cemiterio[i].jazigos[m].valor ||cemiterio[i].jazigos[m].valor == 0)
            {
                r = m-1;
            } else l = m+1;
        }
        if(confirm_interaction == 1)
        {
            break;
        }
        i++;
    }

    if(i>= andar && confirm_interaction == 0)
    {
        printf("?.?\n");
    }

    query_result temp;
    temp.andar = i;
    temp.nmr_jazigo = m;
    temp.interaction = confirm_interaction;
    
    return temp;
}

void remover(Cemiterio cemiterio[], int val, int jazigo, int andar)
{
    query_result remotion = query(cemiterio, val, jazigo, andar);
    if(remotion.interaction!=0 && remotion.andar<andar)
    {
        cemiterio[remotion.andar].jazigos[remotion.nmr_jazigo].estado = 2;
    }
}
int hash(int id, int andar)
{
    int key;
    key = id%andar;
    return key;
}

int add(Cemiterio cemiterio[], int k, int j, int id)
{
    int i = 0;

    while(i<=j)
    {
        if(id<cemiterio[k].jazigos[i].valor)
        {
            for(int f = j; f>i; f--)
            {
                cemiterio[k].jazigos[f].estado = cemiterio[k].jazigos[f-1].estado;
                cemiterio[k].jazigos[f].valor = cemiterio[k].jazigos[f-1].valor;
            }
            cemiterio[k].jazigos[i].valor = id;
            cemiterio[k].jazigos[i].estado = 1;
            break;
        }
        else if(i == j || cemiterio[k].jazigos[i].valor == 0)
        {
            cemiterio[k].jazigos[i].estado = 1;
            cemiterio[k].jazigos[i].valor = id;
            break;
        }
        i++;
    }
    return i;
}