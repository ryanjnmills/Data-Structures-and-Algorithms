#include <iostream>
#include <array>
#include <random>
#include <map>

const int SIZE = 15;
const int MINIMUM = 1;
const int MAXIMUM = 100;
const int REPEAT = 100;

void bubbleSort(std::array<int, SIZE>& arr) {
    
}

void output_arrays(std::array<int, SIZE>& arr) {
    std::cout << 
}

void output_timings() {

}

int main() {
    std::array<int, SIZE> arr;
    std::mt19937 prng(std::random_device{}());
    std::uniform_int_distribution<int> dist(MINIMUM, MAXIMUM);

    for (auto& i : arr) {
        i = dist(prng);
    }

    output_arrays(arr);

    return 0;
}