/**
 *  Stooge Sort in C++
 *  @author Luke Tinnermeier
 *  @version 0.1
 *  @date 05-03-2026
 */
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// === Utility Functions === // 
/**
 *  Fills an array of size `n` with pseudo-random numbers between 1 and a given range 
 *  @param size the size of the array
 *  @param range the largest number that should be generated
 *  @param arr the array to be filled 
 */
void fillArray(int size, int range, vector<int> &arr) {
  srand(time(0));
  for (int i = 0; i < size; i++) {
    arr[i] = (rand() % range) + 1;
  }
}

/**
 *  Prints out a given array to the terminal
 *  @param size the size of the array
 *  @param arr the array to be printed
 */
void printArray(int size, vector<int> &arr) {
  cout << "=== Printing Array ===" << endl;
  
  for (int i = 0; i < size; i++) {
    cout << "Element " << (i + 1) << ": " << arr[i] << endl;
  }

  cout << "=== End of Array ===" << endl;
}

/**
 *  Parses the parameters the user can enter at runtime
 *  @param sizeOfArray the size of the array
 *  @param randomRange the largest possible random number
 *  @param displayArray whether or not to print out the array before and after sorting
 *  @param argc a copy of the number of inputed parameters
 *  @param argv a copy of the parameters
 */
void parseRuntimeParameters(int &sizeOfArray, int &randomRange, bool &displayArray, int argc, char *argv[]) {
  if (argc > 1) {
    switch (argc) {
      case 2:  
        sizeOfArray = atoi(argv[1]);
        cout << "Set the array's size to " << sizeOfArray << endl;
        break;
      case 3: 
        sizeOfArray = atoi(argv[1]);
        cout << "Set the array's size to " << sizeOfArray << endl;
        randomRange = atoi(argv[2]);
        cout << "set the maximum random value to " << randomRange << endl;
        break;
      case 4:
        sizeOfArray = atoi(argv[1]);
        cout << "Set the array's size to " << sizeOfArray << endl;
        randomRange = atoi(argv[2]);
        cout << "Set the maximum random value to " << randomRange << endl;
        if (*argv[3] == 'f') {
          displayArray = false;
          cout << "No longer displaying the array's contents" << endl;
        }
        break;
      default:
        cout << "Please enter parameters in the following format: [int] [int] [t/f]" << endl;
        cout << "Which means [size of the array] [largest random number] [print out array]" << endl;
        break;
      }
  }
}

// === Stooge Sort === //
/**
 *  Recursively sorts an array by splitting it into thirds
 *  First sorts the inital 2/3rd of the array
 *  Next sorts the last 2/3rd
 *  Lastly re-sorts the initial 2/3rd
 *  @param arr the array to be sorted
 *  @param start the start of the chunk to be sorted
 *  @param end the end of the array to be sorted
 */
void stoogeSort(vector<int> &arr, int start, int end) {
  // Stopping condition
  if (start >= end) { return; }

  // If the last element is smalelr than the first, swap them
  if (arr[start] > arr[end]) { swap(arr[start], arr[end]); }

  // Only continue if there are two or more elements in the array
  if (end - start + 1 > 2) {
    // Find the size of a "third"
    //  Stooge Sort requires the third to always be floored; this is handled automatically by C++'s `int` data type
    int chunk = (end - start + 1) / 3;

    // Recursively sort the first third
    stoogeSort(arr, start, end - chunk);
    // Recursively sort the last third
    stoogeSort(arr, start + chunk, end);
    // Recursively sort the first third again
    stoogeSort(arr, start, end - chunk);
  }
}

// === Driver Code === //
int main (int argc, char *argv[]) {

  // Sets variables to default valyes and checks to see if they're modified at runtime
  int sizeOfArray = 5;
  int randomRange = 100;
  bool displayArray = true;
  parseRuntimeParameters(sizeOfArray, randomRange, displayArray, argc, argv);

  // Cool title
  const string title = R"(
  ______     ______   ______     ______     ______     ______        ______     ______     ______     ______  
 /\  ___\   /\__  _\ /\  __ \   /\  __ \   /\  ___\   /\  ___\      /\  ___\   /\  __ \   /\  == \   /\__  _\ 
 \ \___  \  \/_/\ \/ \ \ \/\ \  \ \ \/\ \  \ \ \__ \  \ \  __\      \ \___  \  \ \ \/\ \  \ \  __<   \/_/\ \/ 
  \/\_____\    \ \_\  \ \_____\  \ \_____\  \ \_____\  \ \_____\     \/\_____\  \ \_____\  \ \_\ \_\    \ \_\ 
   \/_____/     \/_/   \/_____/   \/_____/   \/_____/   \/_____/      \/_____/   \/_____/   \/_/ /_/     \/_/ 
                                                                                                             
  )";

  cout << title << endl;

  // Filling array and displaying its contents
  vector<int> elementsToBeSorted(sizeOfArray, 0);
  fillArray(sizeOfArray, randomRange, elementsToBeSorted);
  if (displayArray) {
    cout << "== Unsorted Array ==" << endl;
    printArray(sizeOfArray, elementsToBeSorted);
  }

  // Timing the time it takes to sort the array
  auto start = chrono::high_resolution_clock::now();
  stoogeSort(elementsToBeSorted, 0, sizeOfArray - 1);
  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::microseconds>(end - start);

  // Displaying the sorted array and its speed
  if (displayArray) { 
    cout << "== Sorted Array ==" << endl;
    printArray(sizeOfArray, elementsToBeSorted); 
  }

  cout << "Sorted " << sizeOfArray << " elements in " << duration.count() << " microseconds." << endl;
  return 0;
}
