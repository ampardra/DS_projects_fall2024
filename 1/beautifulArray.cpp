#include <iostream>
#include <vector>

using namespace std;

void beautiful_arr_generator(vector<int>&, int, int);
void print_array(vector<int>);

int main() {
    int n;
    cin >> n;
    vector<int> initial_arr(n);
    for (size_t i = 0; i < n; i++)
        initial_arr[i] = i + 1;
    beautiful_arr_generator(initial_arr, 0, n - 1);
    print_array(initial_arr);
    return 0;    
}

void beautiful_arr_generator(vector<int>& arr, int start, int end) {
    if (end - start <= 1)
        return;
    int mid = start + (end - start) / 2;
    vector<int> left(mid - start + 1),right(end - mid); 
    for (size_t i = start; i < end + 1; i++)
    {
        if ((i - start) % 2 == 0)
            left[(i - start) / 2] = arr[i];
        else right[((i - start) - 1) / 2] = arr[i];
        
    }
    for (size_t i = start; i < end + 1; i++)
    {
        if (i - start <= mid - start)
            arr[i] = left[i - start];
        else arr[i] = right[i - start - (mid - start + 1)];
    }
    beautiful_arr_generator(arr, start, mid);
    beautiful_arr_generator(arr, mid + 1, end);
}

void print_array(vector<int> arr) {
    for (size_t i = 0; i < arr.size(); i++)
        cout << arr[i] << " ";
    cout << endl;
}