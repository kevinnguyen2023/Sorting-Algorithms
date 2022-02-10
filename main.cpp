#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;
using namespace std::chrono;

void QuickSort(int list[], int, int);
void InsertionSort(int list[], int);
int partition(int list[], int, int);
void merge(int list[], int, int, int);
void MergeSort(int list[], int, int);

void generateArray(int list[], int);
void showArray(int list[], int);

int main(void) {
  //srand time
  srand((unsigned)time(0));
  clock_t start, finish; 
  double merge_duration[3] = {0};
  double quick_duration[3] = {0.0};
  double insertion_duration[3] = {0.0};

  //Declaration for pointers
  int *ins_sorted;
  int *quick_sorted;
  int *merge;

  //Creating an array with different sizes
  int ArraySize[] = {20000, 60000, 80000, 160000, 320000};
  // Merge sort couldn't handle 160000 and 320000 on replit for array sizes. 640000 elements will not execute the code because this array size is too large for replit. 

  //Looping 5 times for different sizes
  for(int c = 0; c < 5; c++) {
    // Loop 3 times
    for(int d = 0; d < 3; d++) {
      // Dynamically allocates the memory
      merge = new int[ArraySize[c]];
      generateArray(merge, ArraySize[c]);
      start = clock(); // time in milliseconds
      MergeSort(merge, 0, ArraySize[c] - 1);
      finish = clock(); //milliseconds
      merge_duration[c] += (double)((finish - start) / double(CLOCKS_PER_SEC)); // time in seconds
      merge_duration[c] /= 3.0;
    }
    //Loop 3 times
    for(int d = 0; d < 3; d++) {
      // Dynamically allocates the memory
      quick_sorted = new int[ArraySize[c]];
      generateArray(quick_sorted, ArraySize[c]);
      start = clock(); // time in milliseconds
      QuickSort(quick_sorted, 0, ArraySize[c] - 1);
      finish = clock(); // milliseconds
      quick_duration[c] += (double)((finish - start) / double(CLOCKS_PER_SEC));
      quick_duration[c] /= 3.0;
    }
    //Loop 3 times
    for(int d = 0; d < 3; d++) {
      // Dynamically allocates the memory
      ins_sorted = new int[ArraySize[c]];
      generateArray(ins_sorted, ArraySize[c]);
      start = clock(); //time in milliseconds
      InsertionSort(ins_sorted, ArraySize[c]);
      finish = clock(); //time in milliseconds
      //the constant CLOCKS_PER_SEC below is equal to 1000
      insertion_duration[c] += (double)((finish - start) / double(CLOCKS_PER_SEC));
      insertion_duration[c] /= 3.0; 
    }
  }
  cout << "Each sorting algorithm across with 3 consecutive tests on average: ";
  cout << "\nData Size \tMerge Sort \tQuick Sort \tInsertion Sort\n";

  // Looping 5 times for each sorting
  for(int c = 0; c < 5; c++) {
    cout << fixed << setprecision(5) << ArraySize[c] << "\t\t" << merge_duration[c] << "\t\t" << quick_duration[c] << "\t\t" << insertion_duration[c] << endl; 
  }
  return 0;
}

// Creating a function that assigns random numbers to the array
void generateArray(int list[], int listSize) {
  // Loops until the end of the array
  for(int x = 0; x < listSize; x++) {
    // Generating random numbers between 1 and listSize storing it in x index position
    list[x] = (rand() % listSize) + 1;
  }

}

void showArray(int list[], int listSize) {
  // Loops until the end of the array
  for(int x = 0; x < listSize; x++) {
    // Showing the x index position value
    cout << list[x] << " ";
    cout << endl; 
  }
}

// Creating a function to use InsertionSort
void InsertionSort(int a[], int listSize) {
  // Loops number of elements in the array
  for(int c = 1; c < listSize; c++) {
    // Stores the "c" position element to swap
    int stored = a[c];
    // Stores previous index position of "c" 
    int d = c - 1;
    // Loops until c index position element of the array is greater than stored value and to 0 index position
    while(d >= 0 && a[c] > stored) {
      // Assigns the d index position element at next index position of d
      a[d + 1] = a[d];
      d = d - 1;
    }
    // Assigns the c index position element which is stored at next index position of d
    a[d + 1] = stored;

  }
}

// partition the segment of the array a[], going from index p to index q
int partition(int a[], int p, int q) {
  int pivot = a[q];
  int i = (p - 1), j;

  for (j = p; j <= q - 1; j++) {
    if (a[j] <= pivot) {
      i++;
      int stored = a[i];
      a[i] = a[j];
      a[j] = stored;
    }
  }

  int stored = a[i + 1];
  a[i + 1] = a[q];
  a[q] = stored;

  return (i + 1);
}

// Creating a function to use QuickSort
void QuickSort(int list[], int low, int high) {
  if(low < high) {
    int pi = partition(list, low, high);
    QuickSort(list, low, pi - 1);
    QuickSort(list, pi + 1, high);
  }
}

// Creating a function to use merge operation
void merge(int list[], int l, int m, int r) {
  int i, j, k;
  // Stores the length
  int n1 = m - l + 1;
  int n2 = r - m;

  // Creates left and right pointer type array
  int *left = new int[n1];
  int *right = new int[n2];

  // Loops until the n1 of the list and stores which assigns it to left array
  for (i = 0; i < n1; i++) {
    left[i] = list[l + i];
  }

  // Loops until n2 of the list and stores which assigns it to right array
  for (j = 0; j < n2; j++) {
    right[j] = list[m + 1 + j];
  }

  // For left sub array
  i = 0;
  // For right sub array
  j = 0;
  // For merged sub array
  k = l;

  // Loops until i is less than n1 and j is less than n2
  while(i < n1 && j < n2) {
    // Checks if left sub array i index position data is less than or equals to right sub array j index position data
    if(left[i] <= right[j]) {
      // Assigns the left sub array i index position data at k index position of the list
      list[k] = left[i];
      // Increase index of left sub array by one
      i++;
    }

    else {
      // Assigns the right sub array j index position data at k index position of list
      list[k] = right[j];
      // Increase the index of right sub array by one
      j++;
    }
    // Increase the merged array index by one
    k++;
  }
  // Loops until it gets to n1 for rest of the elements of left sub array
  while (i < n1) {
    // Assigns the left sub array i index position data at k index position of list
    list[k] = left[i];
    // Increase the index of left sub array by one
    i++;
    // Increase the merged array index by one
    k++;
  }

  // Loops until it gets to n2 for rest of the elements of right sub array
  while (j < n2) {
    // Assigns the right sub array j index position data at k index position of list
    list[k] = right[j];
    // Increase the index of right sub array by one
    j++;
    // Increase the merged array index by one
    k++;
  }
}

// Creating a function to use MergeSort
void MergeSort(int list[], int l, int r) {
  // Checks if left is less than right
  if (l < r) {
    // Calculates the middle
    int m = l + (r - l) / 2;
    // Sort first and second halves
    MergeSort(list, l, m);
    MergeSort(list, m + 1, r);
    // Calls the function to merge
    merge(list, l, m, r);
  }
}