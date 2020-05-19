#include "graph.h"
#include <time.h>
#include <vector>
#include <numeric>
#include <string>
#include <chrono>
#include <algorithm>

using namespace Graph;
using namespace std;
using namespace std::chrono;

struct
{
    int cost;
    vector<int> path;
} typedef Path;

int **matrix;
int n = 24;
vector<int>
    times;

int avarageTime()
{
    return accumulate(times.begin(), times.end(), 0) / 10;
}

Path tsdp(int actual, int visited, vector<vector<Path>> &cities)
{
    Path travellingPath;
    travellingPath.cost = INT_MAX;

    if (visited == ((1 << n) - 1))
    {
        travellingPath.cost = matrix[actual][0];
        travellingPath.path.push_back(actual + 1);
    }
    else

        if (cities[actual][visited].cost != INT_MAX)
    {
        travellingPath = cities[actual][visited];
        travellingPath.path.push_back(actual + 1);
    }
    else
    {
        for (int i = 0; i < n; ++i)
        {
            if (i == actual || (visited & (1 << i)))
                continue;

            Path temp = tsdp(i, visited | (1 << i), cities);
            temp.cost += matrix[actual][i];

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
    while (n < 25)
    {
        matrix = new int *[n];
        initMatrix(matrix, n);
        fillMatrix(matrix, n, x, y);

        Path mPath;
        mPath.cost = INT_MAX;
        vector<vector<Path>> cities(n);

        for (auto &path : cities)
        {
            path = vector<Path>((1 << n) - 1, mPath);
        }

        Path finalStats;

        for (int i = 0; i < 10; i++)
        {
            auto start = high_resolution_clock::now();
            finalStats = tsdp(0, 1, cities);
            auto end = high_resolution_clock::now();

            auto duration = duration_cast<microseconds>(end - start);
            times.push_back(duration.count());
        }

        cout << finalStats.cost << endl;
        for (int i = finalStats.path.size() - 1; i >= 0; i--)
            cout << finalStats.path.at(i) << " ";

        cout << endl;

        cout
            << "Tempo medio para n = " << n << ": " << avarageTime() << " microseconds" << endl
            << endl;
        times.clear();
        n++;
    }

    return 0;
}