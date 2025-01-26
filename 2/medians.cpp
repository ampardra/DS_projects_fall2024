#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

void print_array(vector<int> arr) {
    for (size_t i = 0; i < arr.size(); i++)
        cout << arr[i] << " ";
    cout << endl;    
}

int main() {
    int n;
    cin >> n;
    int mode_input;
    long sum = 0;
    vector<int> main_arr, sum_arr;
    int a, b;
    int median = 0;
    priority_queue<int> g, s;
    for (size_t i = 0; i < n; i++)
    {
        cin >> mode_input;
        if (mode_input == 1)
        {
            cin >> a >> b;
            main_arr.push_back(a);
            sum_arr.push_back(b);
            sum += b;
            s.push(a);
            int temp = s.top();
            s.pop();
            g.push(-1 * temp);
            if (g.size() > s.size()) {
                temp = g.top();
                g.pop();
                s.push(-1 * temp);
            }
            int temp_median = s.top();
            if (main_arr.size() != 1)
                sum += ((main_arr.size() - 1) % 2) * (median - temp_median) + abs(temp_median - a);
            median = temp_median;
        } else if (mode_input == 2)
            cout << median << " " << sum << endl;
    }
    return 0;
}