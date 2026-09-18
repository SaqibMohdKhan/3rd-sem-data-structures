#include <iostream>
using namespace std;

int main() {
    int n;

    cout << "Enter size of array: ";
    cin >> n;

    int arr[n + 1];  // +1 for the new element

    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int element;
    cout << "Enter element to insert at beginning: ";
    cin >> element;

    // Shift elements one position to the right
    for (int i = n; i > 0; i--) {
        arr[i] = arr[i - 1];
    }

    // Insert new element at index 0
    arr[0] = element;
    n++;

    cout << "Array after insertion: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }

    return 0;
}