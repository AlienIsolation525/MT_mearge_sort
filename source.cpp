#include <iostream>
#include <vector>
#include <future>
#include <algorithm>
#include <chrono>

using namespace std;

void print(vector<int> result)
{
    cout << "Merged array:\n ";
    for (const auto& x : result) {
        cout << x << ' ';
    }
    cout << endl;
}
void merge(vector<int>& a, int left, int right) {
    if (right - left <= 1) return;

    int mid = (left + right) / 2;
    // Recursive part
    merge(a, left, mid);
    merge(a, mid, right);

    vector<int> temp(right - left);
    int i = left, j = mid, k = 0;

    this_thread::sleep_for(chrono::seconds(2));

    while (i < mid && j < right) {
        if (a[i] < a[j]) temp[k++] = a[i++];
        else temp[k++] = a[j++];
    }

    while (i < mid) temp[k++] = a[i++];
    while (j < right) temp[k++] = a[j++];

    for (int t = 0; t < temp.size(); ++t) {
        a[left + t] = temp[t];
    }
}

int main() {
    vector<int> a = { 1, 3, 5, 7, 9 };
    vector<int> b = { 2, 4, 6, 8 };

    // future multi-thread
    auto future_a = async(launch::async, [&a]() { merge(a, 0, a.size()); });
    auto future_b = async(launch::async, [&b]() { merge(b, 0, b.size()); });

    time_t start, end;
    time(&start);
    // Wait thread end
    future_a.wait();
    time(&end);
    double seconds = difftime(end, start);
    printf("Elapsed time: %f seconds\n", seconds);

    future_b.wait();


    vector<int> result(a.size() + b.size());
    merge(a.begin(), a.end(), b.begin(), b.end(), result.begin());

    print(result);
    return 0;
}