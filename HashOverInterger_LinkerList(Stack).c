#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Kích thước của bảng băm
#define HashTableSize 100000

#define data_t long long

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
int insert(HashTable_t *ht, data_t data)
{
    if (search(ht, data) == 1)
        return 0;
    int index = hash(data);

    // Tạo nút mới
    Node_t *newNode = (Node_t *)malloc(sizeof(Node_t));
    if (newNode == NULL)
    {
        printf("Memory allocation error!");
        return NULL;
    }
    newNode->value = data;
    newNode->next = NULL;

    // Nếu vị trí index chưa có phần tử nào, thêm nút mới vào
    if (ht->HashTable[index] == NULL)
    {
        ht->HashTable[index] = newNode;
    }
    else
    {
        // Nếu vị trí đã có phần tử, thêm nút mới vào đầu danh sách liên kết
        newNode->next = ht->HashTable[index];
        ht->HashTable[index] = newNode;
    }
    return 1;
}

// Hàm tìm kiếm phần tử trong bảng băm
int search(HashTable_t *ht, data_t data)
{
    int index = hash(data);
    Node_t *cur = ht->HashTable[index];

    // Duyệt danh sách liên kết tại vị trí index để tìm kiếm phần tử
    while (cur != NULL)
    {
        if (data == cur->value)
        {
            return 1;
        }
        cur = cur->next;
    }
    return 0;
}

int main()
{
    // Tạo bảng băm
    HashTable_t ht;
    for (int i = 0; i < HashTableSize; i++)
    {
        ht.HashTable[i] = NULL;
    }

    char input[20];
    data_t number;

    while (1) {
        scanf("%s", input);

        if (strcmp(input, "*") == 0) {
            break; // Dừng vòng lặp khi người dùng nhập *
        }

        // Thực hiện chuyển đổi từ chuỗi thành số nguyên long long
        number = atoll(input);
        insert(&ht, number);
    }

    char command[10];
    data_t actionKey;

    while (1)
    {
        scanf("%s",command);
        if (strncmp(command, "find", 4) == 0)
        {
            scanf("%lld", &actionKey);
            printf("%d \n", search(&ht, actionKey));
        }
        else if (strncmp(command, "insert", 7) == 0)
        {
            scanf("%lld", &actionKey);
            printf("%d \n", insert(&ht, actionKey));
        }
        else if (strncmp(command, "***", 3) == 0)
        {
            break;
        }
    }

    return 0;
}