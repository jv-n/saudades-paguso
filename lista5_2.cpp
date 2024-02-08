#include <iostream>
#include <limits>
#include <string>
#include <sstream>
#include <cassert>
#include <cstdio>
#include <cmath>

using namespace std;

typedef struct Aresta{

    int Y;
    int W;
    struct Aresta *next;

}Aresta;

typedef struct Node{
    int id;
    float caminho;
}Node;

void DFS_visit(Aresta** head, int inicio, int fim, bool visitas[])
{
    Aresta* cur = head[inicio];
    while(cur->next!=NULL)
    {
        int x = cur->next->Y;
        if(!visitas[x])
        {
            visitas[x] = true;
            DFS_visit(head, x, fim, visitas);
        }
        cur = cur->next;
    }
}

bool DFS(Aresta** head, int quadras, int inicio, int fim)
{
    bool visitados[quadras];
    bool possivel;
    
    for(int i = 0; i<quadras; i++)
    {
        visitados[i] = false;
    }
    visitados[inicio] = true;
    
    DFS_visit(head, inicio, fim, visitados);
    if(visitados[fim])
    {
        possivel = true;
    }else possivel = false;

    return possivel;
}

int minor_tempo(Aresta** head, int quadras, int inicio, int fim)
{
    float caminhos[quadras];
    bool marcado[quadras];
    Node melhor_atual;
    int s = inicio; int f = fim;

    melhor_atual.caminho = std::numeric_limits<float>::infinity();
    melhor_atual.id = -1;

    for (int i = 0; i<quadras; i++)
    {
        caminhos[i] = std::numeric_limits<float>::infinity();
        marcado[i] = false;
    }

    caminhos[s] = 0;

    for(int k = 0; k<quadras; k++)
    {
        melhor_atual.caminho = HUGE_VAL;
        for(int i = 0; i<quadras; i++)
        {
            if(caminhos[i]<melhor_atual.caminho)
            {
                if(!marcado[i])
                {
                    melhor_atual.caminho = caminhos[i];
                    melhor_atual.id = i;
                }
            }
        }

        s = melhor_atual.id;
        marcado[s] = true;

        Aresta* cur = head[s];
        while(cur->next!=NULL)
        {
            if( caminhos[cur->next->Y] > (caminhos[s]+cur->next->W) )
            {
                caminhos[cur->next->Y] = (caminhos[s]+cur->next->W);
            }
            cur = cur->next;
        }
    }
    return caminhos[f];    
}

Aresta* add_new_street(Aresta* head, int Y, int W)
{
    Aresta* novo = new Aresta();
    novo->Y = Y; novo->W = W;
    novo->next = head->next;
    head->next = novo;
    return head;
}

Aresta* remove_street(Aresta* head, int Y)
{
    Aresta* cur = head;
    while(cur->next!= NULL && cur->next->Y!=Y)
    {
        cur = cur->next;
    }
    Aresta* p = new Aresta();
    p = cur->next;
    cur->next = p->next;
    delete p;
    
    cur = head;
    return cur;
}

int main(){

    int quadras, ruas, N_eventos, X, Y, W;

    cin >> quadras >> ruas >> N_eventos;

    Aresta** arestas = new Aresta*[quadras];
    
    for (int i = 0; i<quadras; i++)
    {
        arestas[i] = new Aresta();
        arestas[i]->next = NULL;
    }

    for (int i = 0; i<ruas; i++)
    {
        cin >> X >> Y >> W;
        arestas[X] = add_new_street(arestas[X], Y, W);
    }
   
    for (int j = 0; j<N_eventos; j++)
    {
        int control, X_check, Y_check;
        cin >> control >> X_check >> Y_check;

        if(control == 1)
        { 
            arestas[X_check] = remove_street(arestas[X_check], Y_check);
        }
        else if (control == 2)
        {
            bool possivel = DFS(arestas, quadras, X_check, Y_check);
            if(possivel)
            {
                cout << minor_tempo(arestas, quadras, X_check, Y_check) << endl;
            } else cout << "-1" << endl;
        }
    }
    
    return 0;
}