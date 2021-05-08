#include <iostream>
#include <time.h>
#include <vector>
#include <algorithm>

using namespace std;


// start from 0, find the minimum of the array and swap it with the first number.
// next from 1, find the minimum of the array and swap it with the second number and so on...
void selectionSort(int ar[], int n){
    int min_index;

    for (int i = 0; i < n-1; i++) {
        min_index = i;
        for (int j = i; j <= n-1; j++) {
            if (ar[j] < ar[min_index]){
                min_index = j;
            }
        }
        int tmp = ar[min_index];
        ar[min_index] = ar[i];
        ar[i] = tmp;
    }
}

// push bigger number further back untill next number is bigger for the whole array.
// do this n times. bigger numbers float to the end of the array.
void bubbleSort(int ar[], int n){
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (ar[j] > ar[j+1]){
                int tmp = ar[j];
                ar[j] = ar[j+1];
                ar[j+1] = tmp;
            }
        }
    }
}

// same as before but with recursion instead of for loop
void recursiveBubbleSort(int ar[], int n){

    if (n == 1){
        return;
    }

    for (int i = 0; i < n - 1; i++) {
        if (ar[i] > ar[i+1]){
            int tmp = ar[i];
            ar[i] = ar[i+1];
            ar[i+1] = tmp;
        }
    }

    recursiveBubbleSort(ar, n-1);
}

// store value being checked in key(starts from 1). check if previous value is bigger than value at key.
// if previous number is bigger change value where key was to previous number.
// go back checking if previous.previous value is greater than key, if so change previous to previous.previous, effectivly sorting the list from start to key position.
// when previous...previous is not greater than key, write key at previous...previous+1;
void insertionSort(int ar[], int n){
    int key, j;
    for (int i = 1; i < n; i++) {
        key = ar[i];
        j = i -1;

        while (j>=0 && ar[j] > key){
            ar[j+1] = ar[j];
            j = j-1;
        }
        ar[j+1] = key;
    }
}

// same as above
void recursiveInsertionSort(int ar[], int n){

    if (n <= 1){
        return;
    }

    recursiveInsertionSort(ar, n-1);

    int last = ar[n-1];
    int j = n-2;

    while ( j >=0 && ar[j]>last ){
        ar[j+1] = ar[j];
        j--;
    }
    ar[j+1] = last;
}

// splits array in half recursively until it cant be split anymore.
// puts left half of the smallest array in L and the right in R.
// compares L and R until one runs out, and appends them to main array.
// then checks if there are any elements left in L or R, if so put them in main array.
void merge(int ar[], int l, int m, int r){
    int n1 = m-l+1;
    int n2 = r -m;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = ar[l+i];
    }
    for (int i = 0; i < n2; i++) {
        R[i] = ar[m + 1 +i];
    }

    int i = 0;
    int j = 0;
    int k = l;

    while (i<n1 && j<n2){
        if (L[i] <= R[j]){
            ar[k] = L[i];
            i++;
        } else{
            ar[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1){
        ar[k] = L[i];
        i++;
        k++;
    }

    while (j <n2){
        ar[k] = R[j];
        j++;
        k++;
    }
}
void mergeSort(int ar[], int l, int r){
    if (l>=r){
        return;
    }

    int m = (l + (r-1))/2;
    mergeSort(ar,l,m);
    mergeSort(ar,m+1,r);
    merge(ar,l,m,r);
}

// kako pivot zemi go posledniot element
// i = -1, j = 0, ako vrednosta vo [j] e pomala od pivot: [i++], i smeni gi mestata na [j] i [i]
// na krajot sporedba koja ne pominuva e [j] < [j], pa mora uste edna smena so: [i++], smena na [i] i pivot [high]
// rekurzivno se povikuva quicksort za levata i desnata strana no bez pivot tockata koja sto e vo tocnoto mesto posle izminuvanje na partition()
int partition(int ar[], int low, int high){
    int pivot = ar[high];
    int i = (low -1);

    for (int j = low; j <= high ; j++) {
        if (ar[j] < pivot){
            i++;
            int tmp = ar[i];
            ar[i] = ar[j];
            ar[j] = tmp;
        }
    }
    int tmp = ar[i+1];
    ar[i+1] = ar[high];
    ar[high] = tmp;

    return (i+1);
}
void quickSort(int ar[], int low, int high){
    if (low < high){
        int pi = partition(ar, low, high);

        quickSort(ar, low, pi-1);
        quickSort(ar, pi+1, high);
    }
}


// Obicno se koristi so float za grupiranje na vrednosti kako 0.2, 0.23, 0.21 vo ista koficka, n*ar[i] ke ni dade 2.1 2.3 i slicno, so znaci ce bidat staveni vo koficka b[2]
// potoa se sortirat kofickite individualno so insertion sort
// i se dodavaat na main array
void bucketSort(float ar[], int n){
    vector<float> b[n];

    for (int i = 0; i < n; i++) {
        int bi = n*ar[i];
        b[bi].push_back(ar[i]);
    }

    for (int i = 0; i < n; i++) {
        sort(b[i].begin(),b[i].end());
        //insertionSort
    }

    int index = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < b[i].size(); j++) {
            ar[index++] = b[i][j];
        }
    }
}



int main() {
    srand(time(0));

    //Generate array
    cout << "Enter lenght of array: " << endl;
    int n;
    cin>>n;
    int array[n];
    for (int i = 0; i < n; i++) {
        array[i]=rand()%100;
    }

    //Print unsorted array
    cout<<"Elements of unsorted array:"<<endl;
    for (int i = 0; i < n; i++) {
        cout<<i+1<<": "<<array[i]<<endl;
    }

    //Sorting methods
    //
    //selectionSort(array, n);
    //bubbleSort(array, n);
    //recursiveBubbleSort(array, n);
    //insertionSort(array, n);
    //recursiveInsertionSort(array,n);
    //mergeSort(array, 0, n-1);
    //quickSort(array,0, n-1);
    //bucketSort(array, n); - doesnt work, wrong implementation in function


    //Print sorted array array
    cout<<"Elements of sorted array:"<<endl;
    for (int i = 0; i < n; i++) {
        cout<<i+1<<": "<<array[i]<<endl;
    }


    return 0;
}

