#include "graph.h"
#include <time.h>
#include <vector>
#include <numeric>
#include <string>
#include <algorithm>

using namespace Graph;
using namespace std;

/**
 * @author Atilio Ferreira, João Pedro Santos, Marcelo Bruno Viegas
 * @date 17 mar 2020
 * 
 * 
 * Basicamente o algoritmo funciona como o de força bruta, 
 * porém nesse caso ele utiliza a recursividade e trabalha com os
 * bits de cada vertice para identificar o caminho que foi visitado
 */

struct
{
    int cost;
    vector<int> path;
} typedef Path;

int **matrix;
int n = 1;

Path tsdp(int actual, int visited, vector<vector<Path>> &cities)
{
    Path travellingPath;
    travellingPath.cost = INT_MAX;

    //Nesse primeiro if, verificamos se visited é igual 2^(n) - 1 o que significa que todos os vertices foram visitados
    //Por exemplo, 4 cidades visitadas seria 1111
    if (visited == ((1 << n) - 1))
    {
        travellingPath.cost = matrix[actual][0];
        travellingPath.path.push_back(actual + 1);
    }
    else
        //Esse eh o if que carcteriza a programacao dinamimca, porque a medida
        //que calculo as distancia eu guardo no vector cities
        //logo se aquela posicao tiver um valor diferente de infinito
        //quer dizer que ela ja tem uma distancia calculada
        //e o custo para fazer esse acesso e retornar o valor eh O(1)
        if (cities[actual][visited].cost != INT_MAX)
    {
        travellingPath = cities[actual][visited];
        travellingPath.path.push_back(actual + 1);
    }
    else
    {
        for (int i = 0; i < n; ++i)
        {
            //Esse if indica que se estou olhando em vertice a, visitando o proprio a
            //ou se a cidade ja foi visitada posso pular a execucao da parte de baixo
            if (i == actual || (visited & (1 << i)))
                continue;

            //Aqui, realizo a chamada recursiva, a operacao bit a bit | indica que estou somando
            //o vertice de atual ao proximo vertice, indicando que ambos foram visitados
            //por exemplo 1 = 0001 (atual) | 2 = 0010 (prox) == 3 = 0011
            //e 3 (0011) indica que eu visitei os vertices 1 e 2 e estou no 3
            Path temp = tsdp(i, visited | (1 << i), cities);
            temp.cost += matrix[actual][i];

            //Se o tempo que eu tiver obtido, for menor que o que ja tenho, ai faco a atualizacao
            //sempre marcando o vertice que visitei
            if (temp.cost < travellingPath.cost)
            {
                cities[actual][visited] = temp;
                travellingPath = temp;
                travellingPath.path.push_back(actual + 1);
            }
        }
    }

    return travellingPath;
}

int main()
{
    //Os valores de n vao ate 21
    //a partir de 22 na maquina que testamos ja estoura a memoria
    while (n < 22)
    {
        matrix = new int *[n];
        initMatrix(matrix, n);
        fillMatrix(matrix, n, x, y);

        Path mPath;
        mPath.cost = INT_MAX;
        vector<vector<Path>> cities(n);

        //Aqui eu crio uma matriz n x 2^(n) - 1, que pra indexar as cidades visitadas
        for (auto &path : cities)
        {
            path = vector<Path>((1 << n) - 1, mPath);
        }

        Path finalStats = tsdp(0, 1, cities);

        cout << finalStats.cost << endl;
        for (int i = finalStats.path.size() - 1; i >= 0; i--)
            cout << finalStats.path.at(i) << " ";

        cout << endl;
        n++;
    }

    return 0;
}