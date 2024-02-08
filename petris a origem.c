#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int val;
    struct node *next;
} node;

node* stacktop(int* j, node** new, node** cur)
{
    (*j)++;
    (*new)->next = (*cur);
    (*cur) = (*new);
    return (*cur);
}

node* stackpop(int* j, node** cur)
{
    (*j)--;
    (*cur) = (*cur)->next;
    return (*cur);
}

int main()
{
    
    char controle[5] = "GO";
    int partidas;

    node* head;
    head = (node*) malloc(sizeof(node));
    head->next = NULL;

    scanf("%d\n", &partidas);
    
    int i = 0;
    int j = 0;
    while(i<partidas)
    {
        node* cur = head;
        j = 0;
        strcpy(controle, "GO");
        while(strcmp(controle, "END")!= 0)
        {
            scanf(" %4[^\n]", controle);
            node* new = (node*) malloc(sizeof(node));
            
            if(strcmp(controle, "END")!= 0)
            {
                new->val = atoi(controle);
                if(cur->next != NULL && new->val == cur->val)
                {
                    stackpop(&j, &cur);

                }else
                {
                    stacktop(&j, &new, &cur);
                }
                
            }
            else if(strcmp(controle, "END")== 0)
            {
                if(cur->next!=NULL)
                {
                    printf("caso %d: %d %d\n", i, j, cur->val);
                }
                else printf("caso %d: %d -1\n", i, j);
            }
        }
        i++;
    }

    return 0;
}