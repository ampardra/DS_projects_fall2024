#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
template <typename T>
class priority_queue {
private:
    vector<T> heap;
    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;

            if (heap[index] > heap[parent]) {
                swap(heap[index], heap[parent]);
                index = parent;
            } else {
                break;
            }
        }
    }

    void heapifyDown(int index) {
        int size = heap.size();

        while (true) {
            int leftChild = 2 * index + 1;
            int rightChild = 2 * index + 2;
            int largest = index;

            if (leftChild < size && heap[leftChild] > heap[largest]) {
                largest = leftChild;
            }

            if (rightChild < size && heap[rightChild] > heap[largest]) {
                largest = rightChild;
            }

            if (largest == index) {
                break;
            }

            swap(heap[index], heap[largest]);
            index = largest;
        }
    }

public:
    void push(const T& value) {
        heap.push_back(value);
        heapifyUp(heap.size() - 1); 
    }

    void pop() {
        if (heap.empty()) {
            throw runtime_error("Priority queue is empty");
        }

        heap[0] = heap.back();
        heap.pop_back();        
        if (!heap.empty()) {
            heapifyDown(0);     
        }
    }

    const T& top() const {
        if (heap.empty()) {
            throw std::runtime_error("Priority queue is empty");
        }
        return heap[0];
    }

    bool empty() const {
        return heap.empty();
    }

    size_t size() const {
        return heap.size();
    }
};

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