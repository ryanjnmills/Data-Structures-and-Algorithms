#include <iostream>
#include <array>
#include <algorithm>
#include <random>
#include <chrono>
#include <numeric>
#include <functional>

using std::array, std::cout;

const int SIZE = 1000;
const int MINIMUM = 1;
const int MAXIMUM = 100;
const int REPEAT = 100;
array<int, SIZE> sortedArr; 

void generateRandomArray(std::array<int, SIZE>& arr) {
    std::mt19937 prng(std::random_device{}());
    std::uniform_int_distribution<int> dist(MINIMUM, MAXIMUM);
    for (auto& i : arr) {
        i = dist(prng);
    }
}

void printArray(const array<int, SIZE>& arr, std::string name = "") {
    cout << name << "[ ";
    for (const auto& el : arr)
        cout << el << " ";
    cout << "]\n";
}

void bubbleSort(array<int, SIZE>& arr) {
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
}

void selectionSort(array<int, SIZE>& arr) {
    for (int i = 0; i < SIZE-1; i++) {
        int minIdx = i;
        for (int j = i+1; j < SIZE; j++) {
            if (arr[j] < arr[minIdx])
                minIdx = j;
        }
        if (minIdx != i)
            std::swap(arr[minIdx], arr[i]);
    }
}

void insertionSort(array<int, SIZE>& arr) {
    for (int i = 1; i < SIZE; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

int partition(array<int, SIZE>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i+1], arr[high]);
    return i+1;
}

void quicksort(array<int, SIZE>& arr, int low = 0, int high = SIZE-1) {
    if (low < high) {
        int pivotIdx = partition(arr, low, high);
        quicksort(arr, low, pivotIdx-1);
        quicksort(arr, pivotIdx+1, high);
    }
}

void merge(array<int, SIZE>& arr, int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    array<int, SIZE> leftArr;
    array<int, SIZE> rightArr;
    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int i = 0; i < n2; i++)
        rightArr[i] = arr[middle + 1 + i];
    
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

void mergeSort(array<int, SIZE>& arr, int left = 0, int right = SIZE-1) {
    if (left >= right)
        return;
    
    int middle = left + (right - left) / 2;
    mergeSort(arr, left, middle);
    mergeSort(arr, middle+1, right);
    merge(arr, left, middle, right);
}

void countingSort(array<int, SIZE>& arr) {
    array<int, SIZE> outputArr;
    int maximum = *std::max_element(arr.begin(), arr.end());
    /* Note that MAXIMUM is the maximum possible value not the actual maximum value of the array. 
    To improve space efficiency without using a dynamically sized array (std::vector), must use a C-style array. */
    // array<int, MAXIMUM> countArr = {};
    int countArr[maximum + 1] = {0};
    
    for (int i = 0; i < SIZE; i++)
        countArr[arr[i]]++;

    for (int i = 1; i <= maximum; i++)
        countArr[i] += countArr[i - 1];

    for (int i = SIZE-1; i >= 0; i--) {
        outputArr[countArr[arr[i]] - 1] = arr[i];
        countArr[arr[i]]--;
    }

    for (int i = 0; i < SIZE; i++)
        arr[i] = outputArr[i];
}

void countingSortForRadix(array<int, SIZE>& arr, int exp) {
    array<int, SIZE> outputArr;
    array<int, 10> countArr = {0};
    
    for (int i = 0; i < SIZE; i++)
        countArr[(arr[i] / exp) % 10]++;
    
    for (int i = 1; i < 10; i++)
        countArr[i] += countArr[i - 1];

    for (int i = SIZE-1; i >= 0; i--) {
        outputArr[countArr[(arr[i] / exp) % 10] - 1] = arr[i];
        countArr[(arr[i] / exp) % 10]--;
    }

    for (int i = 0; i < SIZE; i++)
        arr[i] = outputArr[i];
}

void radixSort(array<int, SIZE>& arr, int exp = 1) {
    int maximum = *std::max_element(arr.begin(), arr.end());
    
    for (int exp = 1; maximum/exp > 0; exp *= 10) {
        countingSortForRadix(arr, exp);
    }
}

void heapify(array<int, SIZE>& arr, int N, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < N && arr[largest] < arr[left])
        largest = left;
    if (right < N && arr[largest] < arr[right])
        largest = right;

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, N, largest);
    }
}

void heapSort(array<int, SIZE>& arr) {
    for (int i = SIZE/2-1; i >= 0; i--)
        heapify(arr, SIZE, i);
    
    for (int i = SIZE-1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

bool isSorted(array<int, SIZE>& arr) {
    return true;
}

double calculateStats(array<double, REPEAT>& arr) {
    double sum = std::accumulate(arr.begin(), arr.end(), 0.0);
    double average = sum / arr.size();
    double minimum = *std::min_element(arr.begin(), arr.end());
    double maximum = *std::min_element(arr.begin(), arr.end());
    return average, minimum, maximum;
}

void calculateTimings(array<int, SIZE> arr, std::function<void(array<int, SIZE>&)> func, std::string name) {
    array<double, REPEAT> times;
    array<int, SIZE> tempArr;
    for (int i = 0; i < REPEAT; i++) {
        tempArr = arr;
        auto start = std::chrono::high_resolution_clock::now();
        func(tempArr);
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        times[i] = elapsed.count();
    }
    double avgTime, minTime, maxTime = calculateStats(times);
    cout << name << " avg: " << avgTime << "  min: " << minTime << "  max: " << maxTime << "\n";
}

int main() {
    array<int, SIZE> arr;
    generateRandomArray(arr);
    sortedArr = std::sort(arr.begin(), arr.end());
    
    array<int, SIZE> bbl = arr;
    array<int, SIZE> slc = arr;
    array<int, SIZE> ins = arr;
    array<int, SIZE> qik = arr;
    array<int, SIZE> mrg = arr;
    array<int, SIZE> cnt = arr;
    array<int, SIZE> rdx = arr;
    array<int, SIZE> hep = arr;

    if (SIZE < 31) {
        bubbleSort(bbl);
        selectionSort(slc);
        insertionSort(ins);
        quicksort(qik);
        mergeSort(mrg);
        countingSort(cnt);
        radixSort(rdx);
        heapSort(hep);

        cout << "UNSORTED ARRAY\n";
        printArray(arr);
        printArray(bbl, "BBL: ");
        printArray(slc, "SLC: ");
        printArray(ins, "INS: ");
        printArray(qik, "QIK: ");
        printArray(mrg, "MRG: ");
        printArray(cnt, "CNT: ");
        printArray(rdx, "RDX: ");
        printArray(hep, "HEP: ");
    } else {
        cout << "SIZE: " << SIZE << "\nREPEATS: " << REPEAT << "\n";
        calculateTimings(bbl, &bubbleSort, "[BBL]");
        calculateTimings(slc, &selectionSort, "[SLC]");
        calculateTimings(ins, &insertionSort, "[INS]");
        //calculateTimings(qik, &quicksort, "[QIK]");
        //calculateTimings(mrg, &mergeSort, "[MRG]");
        calculateTimings(cnt, &countingSort, "[CNT]");
        //calculateTimings(rdx, &radixSort, "[RDX]");
        calculateTimings(hep, &heapSort, "[HEP]");
    }
    
    return 0;
}