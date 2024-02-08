#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    unsigned int val;
    struct node *next;
} node;

typedef struct lista{
    node *pilha;
    struct lista *next;
} lista;

node* stacktop(node** new, node** cur)
{
    (*new)->next = (*cur);
    (*cur) = (*new);
    return (*cur);
}

node* stackpop(node** cur)
{
    (*cur) = (*cur)->next;
    return (*cur);
}

node* stackcopy(node** cur_source, node** cur_dest)
{
    (*cur_dest) = (*cur_source); 
    return (*cur_dest);
}

node* create_stack()
{
    node* head = (node*) malloc(sizeof(node));
    head->next = NULL;

    return head;
}

lista* list_new_insert(node** new, lista** cur_lista)
{
    
    lista* newer = (lista*) malloc(sizeof(lista));
    newer->pilha = create_stack();
    stacktop(new, &newer->pilha); 
    newer->next = (*cur_lista)->next;
    
    (*cur_lista)->next = newer;
    (*cur_lista) = (*cur_lista)->next;    
      
    return (*cur_lista);
}

int main()
{
    char controle[42] = "GO";
    int partidas;

    scanf("%d\n", &partidas);
    
    int i = 0;
    unsigned int j = 0;

    while(i<partidas)
    {
        lista* head;
        head = (lista*) malloc(sizeof(lista));   //lista de pilhas
        head->next = NULL;
        lista* cur_lista = head;
        strcpy(controle, "GO");
        j = 0; //numero de pilhas na partida
        while(strcmp(controle, "END")!= 0)
        {
            scanf(" %41[^\n]", controle);
            node* new = (node*) malloc(sizeof(node));
            
            if(strcmp(controle, "END")!= 0)
            {
                unsigned int x = atoi(controle);
                char* aux = strstr(controle, " ");
                new->val = atoi(aux);
                aux = NULL;

                if(x==j+1)
                {
                    j++;
                    cur_lista = list_new_insert(&new, &cur_lista); 
                }
                else if(x==0)
                {
                    j++;
                    cur_lista = head;
                    cur_lista = list_new_insert(&new, &cur_lista);
                }
                else if (x<=j && x>0)
                {
                    cur_lista = head;
                    unsigned int k = 0;
                    while(k<x)
                    {
                        cur_lista = cur_lista->next;
                        k++;
                    }
                    
                    if(cur_lista->pilha->val== new->val)
                    {
                        stackpop(&cur_lista->pilha);
                        if(cur_lista->pilha->next == NULL)
                        {
                            j--;
                            lista* p = cur_lista->next;
                            cur_lista = head;
                            unsigned int k = 0;
                            
                            while(k<x-1)
                            {
                                cur_lista = cur_lista->next;
                                k++;
                            }
                            cur_lista->next = p;
                            while(cur_lista->next!=NULL)
                            {
                                cur_lista = cur_lista->next;
                            }
                            
                        }
                    } else stacktop(&new, &cur_lista->pilha);
 
                    while(cur_lista->next!=NULL)
                    {
                        cur_lista = cur_lista->next;
                    }
                }

                while(cur_lista->next!=NULL)
                {
                    cur_lista = cur_lista->next; // vai apontar pro final da lista
                }                
            }
            if(strcmp(controle, "END") == 0)
            {
                printf("caso %d:", i);
                if(cur_lista!=NULL)
                {
                    cur_lista = head->next;
                    while(cur_lista!=NULL)
                    {
                        printf(" %d", cur_lista->pilha->val);
                        cur_lista = cur_lista->next;
                    }
                    printf("\n");
                } else printf("\n");
            }
        }

        i++;
    }
    
    return 0;
}