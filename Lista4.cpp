#include <iostream>
#include <string>
#include <cassert>
#include <cmath>

using namespace std;

class Aresta
{
    public:
    int x;
    int y;
  
};

class Celula
{
    public:
    int val;
    Celula* par;
    int height;
};

Celula* find(Celula* cel)
{
    Celula* temp = cel;
    while(temp->par!=temp)
    {
        temp = temp->par;
    }
    return temp;
}

Celula* united(Celula* x, Celula* y)
{
    Celula* raiz_a = find(x);
    Celula* raiz_b = find(y);

    if(raiz_a->height>=raiz_b->height)
    {
        raiz_b->par = raiz_a;
        if(raiz_a->height == raiz_b->height)
        {
            raiz_a->height++;
        }
        return raiz_a;
    } else{
        raiz_a->par = raiz_b;
        return raiz_b;
    }
}

Celula* makeset(int val)
{
    Celula* N = new Celula();
    N->val = val;
    N->par = N;
    N->height = 1;
    return N;
}

int main(){

    int casos, maze_size, maze_walls, Q;

    cin >> casos;

    for(int w = 0; w<casos; w++)
    {
        cin >> maze_size >> maze_walls >> Q;
        
        Celula** celulas = new Celula*[maze_size*maze_size];

        for(int j = 0; j<(maze_size*maze_size); j++)
        {
            celulas[j] = makeset(j);
        }

        Aresta* arestas = new Aresta[(2*((maze_size*maze_size) - maze_size))];

        int j = 0; int i = 0;
        
        for(int x = 0; x<(maze_size*maze_size); x++)
        {
            if(i<(2*((maze_size*maze_size) - maze_size)))
            {
                bool added_right = false;
                if((x+1)%maze_size != 0)
                {
                    arestas[i].x = x;
                    arestas[i].y = x+1;
                    added_right = true;
                    i++;
                }
                if(j == (maze_size-1))
                {
                    j = 0;
                    int z = x-(maze_size-1);
                        
                    while(j<maze_size)
                    {
                        arestas[i].x = z;
                        arestas[i].y = z+maze_size;
                        z++;
                        i++;
                        j++;
                    }
                    j = 0;
                }
                if(added_right)
                {
                    j++;
                }
            }     

        }
<<<<<<< HEAD
=======
        
        /*for(int l = 0; l<(2*((maze_size*maze_size) - maze_size)); l++)
        {
            printf("aresta.%d = %d,%d\n", l, arestas[l].x, arestas[l].y);
        }*/
>>>>>>> 38d1e83db0ad9ec86d30795a9307e1fc901a8bfa

        for(int j =0; j<maze_walls; j++)
        {
            int remotion;
            cin >> remotion; 

            celulas[arestas[remotion].y]->par = united(celulas[arestas[remotion].x], celulas[arestas[remotion].y]); // fazer com union !!!!
        }


        for(int k = 0; k<Q; k++)
        {
            int start;
            int destino;

            cin >> start >> destino;
            Celula* x = find(celulas[start]);
            Celula* y = find(celulas[destino]);
            
            if(x == y)
            {
                cout << w << "." << k << " 1" << endl;
            } else cout << w << "." << k << " 0" << endl;
            
        }
        cout << endl;        
    }

    return 0;
}