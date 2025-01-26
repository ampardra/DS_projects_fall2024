#include <iostream>
#include <vector>
#include <array>
using namespace std;
int main() {
    long Q;
    cin >> Q;
    for (size_t counter = 0; counter < Q; counter++)
    {
        long n;
        cin >> n;
        vector<long> totalHits(n, 0);
        vector<array<long, 3>> towersInformation;
        array<long, 3> inputInformation;
        for (size_t i = 0; i < n; i++)
        {
            cin >> inputInformation[0] >> inputInformation[1] >> inputInformation[2];
            towersInformation.push_back(inputInformation);
        }
        vector<array<long, 3>> stack(0);
        long currentHeight = 0;
        long currentTotalDamage = 0;
        
        for (size_t i = 0; i < n; i++)
        {
            currentHeight = towersInformation[i][0];
            totalHits[i] += currentTotalDamage;
            long lastIndex;
            while (true) {
                lastIndex = stack.size() - 1;
                if (lastIndex >= 0)
                    if (currentHeight > stack[lastIndex][0])
                    {
                        currentTotalDamage -= stack[lastIndex][2];
                        stack.pop_back();
                    } else break;
                else break;
            }
            stack.push_back(towersInformation[i]);
            currentTotalDamage += towersInformation[i][2];
        }
        stack.clear();
        currentHeight = 0;
        currentTotalDamage = 0;
        for (long i = n - 1; i >= 0; i--)
        {
            currentHeight = towersInformation[i][0];
            totalHits[i] += currentTotalDamage;
            long lastIndex;
            while (true) {
                lastIndex = stack.size() - 1;
                if (lastIndex >= 0)
                    if (currentHeight > stack[lastIndex][0])
                    {
                        currentTotalDamage -= stack[lastIndex][2];
                        stack.pop_back();
                    } else break;
                else break;
            }
            stack.push_back(towersInformation[i]);
            currentTotalDamage += towersInformation[i][2];
        }
        for (size_t i = 0; i < n; i++)
            cout << (totalHits[i] + towersInformation[i][1] - 1) / totalHits[i] << " ";
        cout << endl;
    }
    return 0;
}