#include <iostream>
#include <cassert>
#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

int decaimento(int j, int diversao, int aborrecimento)
{
    int decay_result = diversao - ((j-1) * (j-1) * aborrecimento);

    if(decay_result<=0) 
    {
        decay_result = 0;
    }

    return decay_result;
}

void napisaq(int credito_visita, int brinquedos, int** diversao, int** aborrecimento, int** creditos, int** dp)
{
    int i = 0;
    int maxf = 0;
    for(i = 0; i<brinquedos; i++)
    {
        for(int j = credito_visita; j>=(*creditos)[i]; j--)
        {
            maxf = 0;   
            int rep = j/(*creditos)[i];
            int funtimes = (*diversao)[i];
            for(int k = 1; k<=rep; k++)
            {
                maxf = ((*dp)[j - ((*creditos)[i]*k)] + funtimes);
                if(maxf>(*dp)[j]) (*dp)[j] = maxf;
                funtimes += decaimento(k+1, (*diversao)[i], (*aborrecimento)[i]);
            }
        }
    }    
}

int main()
{
    int brinquedos, visitas;
    cin >> brinquedos;

    int* diversao; int* aborrecimento; int* creditos;

    diversao = new int[brinquedos];
    aborrecimento = new int[brinquedos];
    creditos = new int[brinquedos];
    
    for(int i = 0; i<brinquedos; i++)
    {
        cin >> diversao[i] >> aborrecimento[i] >> creditos[i];
    }

    cin >> visitas;
    int creditos_visita;
    int last_result = 0;
    int* dp = NULL;
    for(int j = 0; j<visitas; j++)
    {
        cin >> creditos_visita;
        int aloc = creditos_visita + 1;
        if(creditos_visita>last_result)
        {
            dp = new int[aloc];
            napisaq(creditos_visita, brinquedos, &diversao, &aborrecimento, &creditos, &dp);
            last_result = creditos_visita;
        }

        cout << j << ": "<< dp[creditos_visita] << endl;
    }

    delete diversao; delete aborrecimento; delete creditos; delete dp;

    return 0;
}