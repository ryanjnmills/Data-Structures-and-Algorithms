#include <iostream>
#include <array>
#include <random>
#include <map>

using std::array, std::cout;

const int SIZE = 15;
const int MINIMUM = 1;
const int MAXIMUM = 100;
const int REPEAT = 100;

array<int, SIZE> bubbleSort(array<int, SIZE>& arr) {
    for (int i = 0; i < SIZE-1; i++) {
        bool swapped = false;
        for (int j = 0; j < SIZE-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                std::swap(arr[j], arr[j+1]);
                swapped = true;
            }
        }
        if (swapped == false)
            break;
    }
    return arr;
}

array<int, SIZE> selectionSort(array<int, SIZE>& arr) {
    for (int i = 0; i < SIZE-1; i++) {
        int minIdx = i;
        for (int j = i+1; j < SIZE; j++) {
            if (arr[j] < arr[minIdx])
                minIdx = j;
        }
        if (minIdx != i)
            std::swap(arr[minIdx], arr[i]);
    }
    return arr;
}

array<int, SIZE> insertionSort(array<int, SIZE>& arr) {
    for (int i = 1; i < SIZE-1; i++) {
        
    }
}

void printArray(array<int, SIZE>& arr, std::string name="") {
    cout << name << "[ ";
    for (const auto& el : arr)
        cout << el << " ";
    cout << "]\n";
}

void outputArrays(array<int, SIZE>& arr) {
    cout << "UNSORTED ARRAY\n";
    printArray(arr);

    array<int, SIZE> bbl = bubbleSort(arr);
    printArray(bbl, "BBL: ");
    array<int, SIZE> slc = selectionSort(arr);
    printArray(slc, "SLC: ");
    array<int, SIZE> ins = insertionSort(arr);
    printArray(ins, "INS: ");
}

void outputTimings() {

}

int main() {
    array<int, SIZE> arr;
    std::mt19937 prng(std::random_device{}());
    std::uniform_int_distribution<int> dist(MINIMUM, MAXIMUM);

    for (auto& i : arr) {
        i = dist(prng);
    }

    outputArrays(arr);

    return 0;
}