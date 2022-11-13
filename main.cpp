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
  
  for(int c = 0; c < 5; c++) {
    for(int d = 0; d < 3; d++) {
      merge = new int[ArraySize[c]]; // Dynamically allocates the memory
      generateArray(merge, ArraySize[c]);
      start = clock(); // time in milliseconds
      MergeSort(merge, 0, ArraySize[c] - 1);
      finish = clock();
      merge_duration[c] += (double)((finish - start) / double(CLOCKS_PER_SEC)); // time in seconds
      merge_duration[c] /= 3.0;
    }
    
    for(int d = 0; d < 3; d++) {
      quick_sorted = new int[ArraySize[c]];  // Dynamically allocates the memory
      generateArray(quick_sorted, ArraySize[c]);
      start = clock(); // time in milliseconds
      QuickSort(quick_sorted, 0, ArraySize[c] - 1);
      finish = clock();
      quick_duration[c] += (double)((finish - start) / double(CLOCKS_PER_SEC));
      quick_duration[c] /= 3.0;
    }
    
    
    for(int d = 0; d < 3; d++) {
      ins_sorted = new int[ArraySize[c]];  // Dynamically allocates the memory
      generateArray(ins_sorted, ArraySize[c]);
      start = clock(); //time in milliseconds
      InsertionSort(ins_sorted, ArraySize[c]);
      finish = clock();
      insertion_duration[c] += (double)((finish - start) / double(CLOCKS_PER_SEC)); // the constant CLOCKS_PER_SEC below is equal to 1000
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
  for(int x = 0; x < listSize; x++) { // Loops until the end of the array
    list[x] = (rand() % listSize) + 1; // Generating random numbers between 1 and listSize storing it in x index position
  }
}

void showArray(int list[], int listSize) {
  for(int x = 0; x < listSize; x++) { // Loops until the end of the array
    cout << list[x] << " "; // Showing the x index position value
    cout << endl; 
  }
}

void InsertionSort(int a[], int listSize) {
  for(int c = 1; c < listSize; c++) {   // Loops number of elements in the array
    int stored = a[c];  // Stores the "c" position element to swap
    int d = c - 1;  // Stores previous index position of "c" 
    while(d >= 0 && a[c] > stored) {   // Loops until c index position element of the array is greater than stored value and to 0 index position
      a[d + 1] = a[d];   // Assigns the d index position element at next index position of d
      d = d - 1;
    }
    a[d + 1] = stored;     // Assigns the c index position element which is stored at next index position of d
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

void QuickSort(int list[], int low, int high) {
  if(low < high) {
    int pi = partition(list, low, high);
    QuickSort(list, low, pi - 1);
    QuickSort(list, pi + 1, high);
  }
}


void merge(int list[], int l, int m, int r) {
  int i, j, k;
  int n1 = m - l + 1; // Stores the length
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

  i = 0;  // For left sub array
  j = 0; // For right sub array
  k = l; // For merged sub array

 
  while(i < n1 && j < n2) {
    if(left[i] <= right[j]) {   // Checks if left sub array i index position data is less than or equals to right sub array j index position data
      list[k] = left[i];       // Assigns the left sub array i index position data at k index position of the list
      i++; // Increase index of left sub array by one
    }

    else {
      list[k] = right[j];       // Assigns the right sub array j index position data at k index position of list
      j++;       // Increase the index of right sub array by one
    }
    k++;     // Increase the merged array index by one
  }
  
  // Loops until it gets to n1 for rest of the elements of left sub array
  while (i < n1) {
    list[k] = left[i];  // Assigns the left sub array i index position data at k index position of list
    i++;     // Increase the index of left sub array by one
    k++;    // Increase the merged array index by one
  }

  // Loops until it gets to n2 for rest of the elements of right sub array
  while (j < n2) {
    list[k] = right[j]; // Assigns the right sub array j index position data at k index position of list
    j++; // Increase the index of right sub array by one
    k++; // Increase the merged array index by one
  }
}

void MergeSort(int list[], int l, int r) {
  if (l < r) { // Checks if left is less than right
    int m = l + (r - l) / 2; // Calculates the middle
    MergeSort(list, l, m); // Sort first and second halves
    MergeSort(list, m + 1, r);
    merge(list, l, m, r); // Calls the function to merge
  }
}
