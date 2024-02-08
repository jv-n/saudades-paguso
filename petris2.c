#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    int val;
    struct node *next;
} node;

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

int main()
{
    
    char controle[5] = "GO";
    int partidas;

    node** head;
    head = (node**) malloc(sizeof(node*));
    (*head) = (node*) malloc(sizeof(node));
    (*head)->next = NULL;

    scanf("%d\n", &partidas);
    
    int i = 0;
    int j = 0;
    int x;
    while(i<partidas)
    {
        node** cur = head;
        strcpy(controle, "GO");
        j = 0;
        while(strcmp(controle, "END")!= 0)
        {
            scanf(" %4[^\n]", controle);
            node* new = (node*) malloc(sizeof(node));
            
            if(strcmp(controle, "END")!= 0)
            {
                x = atoi(controle);
                char* aux = strstr(controle, " ");
                new->val = atoi(aux);
                
                if(x == j+1)
                {
                    j++;
                    stacktop(&new, &cur[j-1]);
                }
                else if(x == 0)
                {
                    j++;
                    for(int k = j-1; k>0; k--)
                    {
                        cur[k] = cur[k-1];
                    }
                    stackcopy(&new, &cur[0]);
                }
                else if(x>0 && x<=j)
                {
                    if(cur[x-1]->val != new->val)
                    {
                        stacktop(&new, &cur[x-1]);
                    } else if(cur[x-1]->next != NULL && cur[x-1]->val == new->val)
                    {
                        stackpop(&cur[x-1]);
                        //if(cur[x-1]->next == NULL)
                        if(cur[x-1]->val<0 || cur[x-1]->val > 1000000)
                        {
                            cur[x-1] = NULL;
                            for(int k = x-1; k<j; k++)
                            {
                                cur[k] = cur[k+1];
                            }
                            j--;
                        }
                    }
                }
            }
            else if(strcmp(controle, "END")== 0)
            {
                printf("caso %d:", i);
                if(cur!=NULL)
                {
                    for(int k = 0; k<j; k++)
                    {
                        printf(" %d", cur[k]->val);
                    }
                    printf("\n");
                } else printf("\n");
            }
        }
        i++;
    }

    return 0;
}