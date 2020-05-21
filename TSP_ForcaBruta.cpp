#include "graph.h"
#include <vector>
#include <cstring>
#include <chrono>
#include <numeric>

using namespace std::chrono;
using namespace Graph;
using namespace std;

int **matrix;           // Matriz de distâncias
int n = 2;              // Número de cidades
int *path = new int[n]; // Caminho de cidades com menor distância total
int minDist = INT_MAX;  // Distancia mínima

void bruteForce(int *vector, int inf, int sup)
{
    int sum = 0;

    // se gerada uma nova permutação
    if (inf == sup)
    {
        //soma a distancia percorrendo as cidades
        for (int i = 0; i <= sup - 1; i++)
        {
            sum = sum + matrix[(vector[i])][(vector[i + 1])];
        }

        // soma da distancia da ultima cidade da permutacao para voltar ate a primeira cidade
        sum = sum + matrix[(vector[n - 1])][0];

        if (sum < minDist)
        {
            minDist = sum;

            for (int i = 0; i <= sup; i++)
            {
                path[i] = vector[i];
            }
        }
    }
    else //enquanto não foi gerado uma nova permutacao
    {
        for (int i = inf; i <= sup; i++)
        {
            swap(vector, inf, i);
            bruteForce(vector, inf + 1, sup);
            swap(vector, inf, i); // backtracking
        }
    }
}

int main()
{

    while (n < 13)
    {
        matrix = new int *[n];
        int *vector = new int[n];

        initMatrix(matrix, n);
        fillMatrix(matrix, n, x, y);
        fillVector(vector, n);

        for (int i = 0; i < 10; i++)
        {
            bruteForce(vector, 1, n - 1);

        }

        cout << minDist << endl;

        for (int i = 0; i < n; i++)
        {
            cout << path[i] + 1 << " ";
        }

        cout << endl << endl;

        n++;
        minDist = INT_MAX;
        path = new int[n];
    }

    return 0;
}