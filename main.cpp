#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

long long totalComp = 0;
long long totalSwap = 0;

void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
    totalSwap++;
}

void resetCounters() {
    totalComp = 0;
    totalSwap = 0;
}

void selectionSort(std::vector<int>& arr);
void insertionSort(std::vector<int>& arr);
void heapSort(std::vector<int>& arr);
void mergeSort(std::vector<int>& arr, int l, int r);
void quickSort(std::vector<int>& arr, int low, int high);
void ArrayGenerate(std::vector<int>& arr, int n);

int main() {
    std::vector<int> sizes = {128, 1024};
    for (int size : sizes) {
        std::vector<int> arr(size);
        ArrayGenerate(arr, size);

        std::vector<int> arrCopy = arr;
        resetCounters();
        selectionSort(arrCopy);
        std::cout << "Selection Sort - Size: " << size << ", Comparisons: " << totalComp << ", Swaps: " << totalSwap << std::endl;

        arrCopy = arr;
        resetCounters();
        insertionSort(arrCopy);
        std::cout << "Insertion Sort - Size: " << size << ", Comparisons: " << totalComp << ", Swaps: " << totalSwap << std::endl;

        arrCopy = arr;
        resetCounters();
        heapSort(arrCopy);
        std::cout << "Heap Sort - Size: " << size << ", Comparisons: " << totalComp << ", Swaps: " << totalSwap << std::endl;

        arrCopy = arr;
        resetCounters();
        mergeSort(arrCopy, 0, size - 1);
        std::cout << "Merge Sort - Size: " << size << ", Comparisons: " << totalComp << ", Swaps: " << totalSwap << std::endl;

        arrCopy = arr;
        resetCounters();
        quickSort(arrCopy, 0, size - 1);
        std::cout << "QuickSort - Size: " << size << ", Comparisons: " << totalComp << ", Swaps: " << totalSwap << std::endl;
    }

    return 0;
}

void selectionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            totalComp++;
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        swap(arr[i], arr[min_idx]);
    }
}
void insertionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            totalComp++;
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
        if (i != j+1) totalSwap++;
    }
}
void heapify(std::vector<int>& arr, int n, int i) {
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    if (l < n && arr[l] > arr[largest]) {
        largest = l;
        totalComp++;
    }

    if (r < n && arr[r] > arr[largest]) {
        largest = r;
        totalComp++;
    }

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    for (int i=n-1; i>0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}
void merge(std::vector<int>& arr, int const left, int const mid, int const right) {
    auto const subArrayOne = mid - left + 1;
    auto const subArrayTwo = right - mid;

    std::vector<int> leftArray(subArrayOne), rightArray(subArrayTwo);

    for (auto i = 0; i < subArrayOne; i++)
        leftArray[i] = arr[left + i];
    for (auto j = 0; j < subArrayTwo; j++)
        rightArray[j] = arr[mid + 1 + j];

    auto indexOfSubArrayOne = 0, indexOfSubArrayTwo = 0;
    int indexOfMergedArray = left;

    while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
        totalComp++;
        if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {
            arr[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        } else {
            arr[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }

    while (indexOfSubArrayOne < subArrayOne) {
        arr[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }

    while (indexOfSubArrayTwo < subArrayTwo) {
        arr[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
}

void mergeSort(std::vector<int>& arr, int const begin, int const end) {
    if (begin >= end)
        return;

    auto mid = begin + (end - begin) / 2;
    mergeSort(arr, begin, mid);
    mergeSort(arr, mid + 1, end);
    merge(arr, begin, mid, end);
}
int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j < high; j++) {
        totalComp++;
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
void ArrayGenerate(std::vector<int>& arr, int n) {
    srand(static_cast<unsigned int>(time(0))); //seed for random number generation
    for (int& i : arr) {
        i = rand() % 1000; //generates random numbers between 0 and 999
    }
}
void generateAlmostSortedArray(std::vector<int>& arr, int n) {
    ArrayGenerate(arr, n); 
    std::sort(arr.begin(), arr.end()); 
    //randomness to about 10% of the elements
    for (int i = 0; i < n / 10; i++) {
        int index = rand() % n;
        arr[index] = rand() % 1000;
    }
}
void generateAlmostReversedArray(std::vector<int>& arr, int n) {
    generateAlmostSortedArray(arr, n); 
    std::reverse(arr.begin(), arr.end());
}
void generateSortedExceptLastTenPercent(std::vector<int>& arr, int n) {
    int sortUpTo = n - n / 10;
    ArrayGenerate(arr, sortUpTo); //randomize the first part
    std::sort(arr.begin(), arr.begin() + sortUpTo); //sorts only the first 90%
    // and the last 10% remains random
}
