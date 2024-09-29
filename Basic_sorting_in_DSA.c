#include<stdio.h>
#include<stdlib.h>
#include<limits.h>


# define MAX 1000000
int b[MAX];



void swap(int a[], int i, int j) { // hoán đổi 2 phần tử
    int temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}


void SortSelection(int a[],int N){// Sắp xếp lựa chọn
//  Tìm min và đưa nó lên trên cùng.
    for(int i = 0; i < N; i++){
        int min = INT_MAX;
        int posMin = i;
        for(int j = i; j<N; j++){
            if(a[j] <= min){
                min = a[j]; 
                posMin = j;
            } 
        }
        swap(a,i,posMin);
    }
}

void InsertionSort(int a[], int N){ // Sắp xếp chèn
// Hàm for lồng nhau
    for(int k = 1; k<N;k++){
        int j = k;
        int last = a[k];
        while(a[j-1] > last && j > 0){
            a[j] = a[j-1];
            j--;
        }
        a[j] = last;
    }
}

void BubbleSort(int a[], int N){ // Sắp xếp nổi bọt
    int swapped = 0;
    do
    {
        swapped = 0;
        for(int i = 0; i < N-1; i++){
            if(a[i] > a[i+1]) {
                swap(a,i,i+1);
                swapped = 1;
            }
        }
    } while (swapped);
}

void Merge(int a[], int L, int M, int R){ // gắn 2 dãy tăng lại với nhau
    int i = L;
    int j = M+1;
    for(int k = L; k<= R;k++){
        if(i>M){
            b[k] = a[j];
            j++;
        }
        else if(j>R){
            b[k] = a[i];
            i++;
        }
        else if(a[i] < a[j]){
            b[k] = a[i];
            i++;
        }
        else{
            b[k] = a[j];
            j++;
        }
    }

    for(int k = L; k <= R; k++) {
        a[k] = b[k];
    }
}

void MergeSort(int a[], int L, int R){ // sap xep 1 day tu L den R
    if(L < R) {
        int M = (L + R) / 2;
        MergeSort(a, L, M);
        MergeSort(a, M + 1, R);
        Merge(a, L, M, R);
    }
}




// Sắp xếp quick sort
int partition(int a[], int L, int R, int indexPivot) { // chọn 1 phần tử là indexPivot, trả về vị trí đúng của nó
// Vị trí đúng là trước nó không có phần tử nào lớn hơn nó, và sau nó không có phần tử nào bé hơn nó
    int pivot = a[indexPivot];
    swap(a, indexPivot, R);
    int storeIndex = L;
    for(int i = L; i <= R-1; i++) {
        if(a[i] < pivot) {
            swap(a, i, storeIndex);
            storeIndex++;
        }
    }
    swap(a, storeIndex, R);
    return storeIndex;
}

void QuickSort(int a[], int L, int R) { // Sắp xếp các phần tử theo thứ tự tăng dần
    if(L < R) {
        int indexPivot = (L + R) / 2; // chọn phần tử làm indexPivot
        indexPivot = partition(a, L, R, indexPivot); //đưa nó về vị trí đúng và lưu vị trí đó
        // đệ quy theo nửa trái và nửa phải so với vị trí đúng của indexPivot
        if(indexPivot > L) QuickSort(a, L, indexPivot - 1);
        if(indexPivot < R) QuickSort(a, indexPivot + 1, R);
    }
}



void heapify(int a[], int i, int n) { // vun lại cây heap-max ở vị trí i đã bị phá vỡ
// ví là mảng chạy từ 0-n nến phải lấy L và R như dưới
    int L = 2*i + 1;
    int R = 2*i + 2;
    // MaxIndex là vị trí của nút có số lớn nhất trong cây 3 nút
    int maxIndex = i;
    // i là vị trí của nút cha
    // tìm ra vị trí của maxIndex
    if (L < n && a[L] > a[maxIndex]) {
        maxIndex = L;
    }

    if (R < n && a[R] > a[maxIndex]) {
        maxIndex = R;
    }

    if (maxIndex != i) {// Nếu nút cha ko phải mà maxindex thì hoán vị nút cho cho nút vị trí maxindex
        swap(a, i, maxIndex);
        // thực hiện lại vun cây heap-max với vị trí maxindex vừa được hoán vị
        heapify(a, maxIndex, n);
    }
}


void buildHeap(int a[], int n) {// tạo 1 cây heap-max
// vun lại cây từ dưới lên trên
    for (int i = n/2 - 1; i >= 0; i--) {
        heapify(a, i, n);
    }
}

void heapSort(int a[], int n) { // sắp xếp dãy theo thứ tự không giảm
    buildHeap(a, n); // tạo cây heap-max

    for (int i = n - 1; i > 0; i--) { 
        swap(a, 0, i);// hoán vị đỉnh của cây heapmax và đưa nó vào cuối danh sách
        heapify(a, 0, i); // thực hiện đệ quy vun đống và lặp lại với các phần tử còn lại
    }
}




void printfArray(int a[], int N){ //in ra day sau khi sap xep
    for(int i = 0;i<N;i++){
        printf("%d ",a[i]);
    }
}

int main(){
    int arr[] = {64, 34, 25, 12, 22, 11, 90, 1};
    int arr_size = sizeof(arr) / sizeof(arr[0]);
    QuickSort(arr, 0, arr_size);
    printfArray(arr,arr_size);
    return 0;
}