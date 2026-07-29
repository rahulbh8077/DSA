#include <iostream>
#include <vector>
using namespace std;
// logic for merging the two sorted left and right array into a temp array
void merge(vector<int> &arr, int low, int mid, int high) {
    vector<int> temp;

    int i = low;
    int j = mid + 1;

    while (i <= mid && j <= high) {
        if (arr[i] <= arr[j]) {
            temp.push_back(arr[i]);
            i++;
        } else {
            temp.push_back(arr[j]);
            j++;
        }
    }

    while (i <= mid) {
        temp.push_back(arr[i]);
        i++;
    }

    while (j <= high) {
        temp.push_back(arr[j]);
        j++;
    }

    // Copy temp back to arr
    for (int idx = 0; idx < temp.size(); idx++) {
        arr[idx + low] = temp[idx];
    }
}
// divide the array rules follows from here.
void mergesort(vector<int> &arr, int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;

        mergesort(arr, low, mid);
        mergesort(arr, mid + 1, high);

        merge(arr, low, mid, high);
    }
}

int main() {
    vector<int> arr = {12, 31, 35, 8, 32, 17};

    mergesort(arr, 0, arr.size() - 1);

    for (int val : arr) {
        cout << val << " ";
    }

    cout << endl;
    return 0;
}
