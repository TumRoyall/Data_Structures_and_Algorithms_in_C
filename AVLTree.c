#include <stdio.h>
#include <stdlib.h>

#define data_t int

// Định nghĩa cấu trúc của một nút trong cây AVL
typedef struct Node
{
    data_t data;
    struct Node *left;
    struct Node *right;
    int height;
} Node_t;

// Hàm để tạo một nút mới trong cây AVL
Node_t *makeNode(data_t v)
{
    Node_t *new = (Node_t *)malloc(sizeof(Node_t));
    if (new == NULL)
    {
        printf("error!!!");
        return NULL;
    }
    new->data = v;
    new->left = NULL;
    new->right = NULL;
    new->height = 1;
    return new;
}

// Hàm để lấy độ cao của một nút
int height(Node_t *node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// Hàm để tính cân bằng của một nút
// Cân bằng của một nút là độ lệch chiều cao của nút con bên trái và nút con bên phải của một nút
int getBalance(Node_t *node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}



int main()
{

    return 0;
}
