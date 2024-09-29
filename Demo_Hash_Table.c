#include <stdio.h>
#include <stdlib.h>

// Kích thước của bảng băm
#define HashTableSize 10

#define data_t int

//  Cấu trúc trong danh sách liên kết
typedef struct Node
{
    data_t value;
    struct Node *next;
} Node_t;

// Cáu trúc bảng băm
typedef struct HashTable
{
    Node_t *HashTable[HashTableSize];
} HashTable_t;

// Hash function basic
int hash(data_t data)
{
    return data % HashTableSize;
}

// Thêm phần tử vào bảng băm
void insert(HashTable_t *ht, data_t data) {
    int index = hash(data);

    // Tạo nút mới
    Node_t *newNode = (Node_t *)malloc(sizeof(Node_t));
    if (newNode == NULL) {
        printf("Memory allocation error!");
        return;
    }
    newNode->value = data;
    newNode->next = NULL;

    // Nếu vị trí index chưa có phần tử nào, thêm nút mới vào
    if (ht->HashTable[index] == NULL) {
        ht->HashTable[index] = newNode;
    } else {
        // Nếu vị trí đã có phần tử, thêm nút mới vào đầu danh sách liên kết
        newNode->next = ht->HashTable[index];
        ht->HashTable[index] = newNode;
    }
}

// Hàm tìm kiếm phần tử trong bảng băm
Node_t *search(HashTable_t *ht, data_t data) {
    int index = hash(data);
    Node_t *cur = ht->HashTable[index];

    // Duyệt danh sách liên kết tại vị trí index để tìm kiếm phần tử
    while (cur != NULL) {
        if (data == cur->value) {
            printf("%d", 1);
            return cur; // Phần tử được tìm thấy
        }
        cur = cur->next;
    }
    printf("%d", 0);
    return NULL; // Không tìm thấy phần tử
}

void delete(HashTable_t *ht, data_t data)
{
    // Tính chỉ số băm từ dữ liệu
    int index = hash(data);

    // Lấy con trỏ đến danh sách liên kết tại vị trí index
    Node_t *cur = ht->HashTable[index];
    Node_t *prev = NULL; // Con trỏ đến nút trước nút hiện tại

    // Duyệt danh sách liên kết để tìm phần tử cần xóa
    while (cur != NULL)
    {
        if (data == cur->value)
        {
            // Xóa nút khỏi danh sách liên kết
            if (prev == NULL)
                ht->HashTable[index] = cur->next;
            else
                prev->next = cur->next;

            // Giải phóng bộ nhớ của nút cần xóa
            free(cur);

            return; // Kết thúc hàm sau khi xóa thành công
        }

        // Di chuyển con trỏ tới nút tiếp theo trong danh sách liên kết
        prev = cur;
        cur = cur->next;
    }

    // Nếu không tìm thấy phần tử cần xóa
    printf("Element not found for deletion\n");
}

int main()
{
    // Tạo bảng băm
    HashTable_t ht;
    for (int i = 0; i < HashTableSize; i++)
    {
        ht.HashTable[i] = NULL;
    }

    insert(&ht, 15);
    insert(&ht, 17);
    insert(&ht, 20);
    insert(&ht, 30);
    search(&ht, 1);
    search(&ht, 15);
    search(&ht, 20);

    printf("\n");
    delete(&ht, 20);

    search(&ht, 20);

    return 0;
}