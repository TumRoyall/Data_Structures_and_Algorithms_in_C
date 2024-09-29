#include <stdio.h>
#include <stdlib.h>
void insert(int *a, int *n, int x, int k)
{ // Chén phẩn tử có giá trị x vào vị trí k
    for (int i = *n - 1; i >= k; i--)
    {
        a[i + 1] = a[i];
    }
    a[k] = x;
    *n = *n + 1;
}

void deleteElement(int *a, int *n, int k)
{ // Xóa phần tử thứ k
    for (int i = k; i < *n - 1; i++)
    {
        a[i] = a[i + 1];
    }
    *n = *n - 1;
}

void print_arr(int a[], int n)
{ // in các phần tử của mảng
    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
}
int main()
{
    int n;
    scanf("%d", &n);
    // input bình thường
    // int a[100];
    // Cấp phát động
    int *a; // gọi con trỏ a chỉ vị trí đầu mảng;
    a = (int *)malloc(sizeof(int) * n);
    if (a == NULL)
        printf("Error!");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
    int b;
    scanf("%d", &b);
    deleteElement(a, &n, b);
    print_arr(a, n);
    return 0;
}