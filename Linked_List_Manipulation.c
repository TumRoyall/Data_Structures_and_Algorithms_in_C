#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define data_t int

typedef struct Node // Định nghĩa node
{
    data_t data;
    struct Node *next;
}Node_t;

int isEmpty(Node_t** head){// Kiểm tra node tồn tại không
    return (*head == NULL);
}

int findNode(Node_t* head,data_t value){ // kiểm tra node có value có tồn tại chưa, nếu chưa thì trả về -1 ngược lại trả về VỊ TRÍ của nó
    Node_t* p = head;
    int n = 0;
    if(p == NULL) return -1;
    while(p != NULL){
        if(p->data == value) return n;
        p = p->next;
        n++;
    }
    return -1;
}

Node_t* makeNode(data_t value){ // Tạo một node có giá trị là value
    Node_t* newNode = (Node_t*)malloc(sizeof(Node_t));
    if(newNode == NULL){
        printf("Memory allocation error!");
        return NULL;
    }
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}


void insertLast(Node_t** head, data_t value){ // thêm vào cuối ll 1 phần tử có giá trị là value
    Node_t* p = *head;
    if(findNode(p,value) != -1) return;
    Node_t* newNode = makeNode(value);
    if(isEmpty(head)){
        *head = newNode;
    }else{
        while(p->next != NULL){
            p = p->next;
        }
        p->next = newNode;
    }
}

void addFirst(Node_t** head, data_t value){ // Thêm vào đầu ll 1 phần tử có giá trị là value
    Node_t* p = *head;
    if(findNode(p,value) != -1) return;
    Node_t* newNode = makeNode(value);
    if(isEmpty(head))
    {
        *head = newNode;
    }
    else
    {
        newNode->next = p;
        *head = newNode;
    }
}

void addAfter(Node_t** head,data_t value,data_t u){ // Chèn phần tử có data là value vào sau phần tử có data là u 
    Node_t* p = *head;
    if(findNode(p,value) != -1) return;
    Node_t* new = makeNode(value);
    while(p!= NULL){
        if(p->data == u){
            new->next = p->next;
            p->next = new;
            return;
        }
        p = p->next;
    }
}

void addBefore(Node_t** head,data_t value,data_t u){// Chèn phần tử có data là value vào trước phần tử có data là u 
    Node_t* current = *head;
    if(findNode(current,value) != -1) return;
    Node_t* prev = NULL;
    Node_t* new = makeNode(value);
    while (current != NULL){
        if(current->data == u){
            if(prev == NULL){
                new->next = current;
                *head = new;
            }else{
                prev->next = new;
                new->next = current;
            }
            return;
        }
        prev = current;
        current = current->next;
    }
}

void removeAllNode(Node_t** head,data_t value){// Xóa tất cả phần tử có giá trị là value
    Node_t* curr = *head;
    Node_t* prev = NULL;
    while(curr!= NULL){
        if(curr->data == value){
            if(prev == NULL){
                *head = (*head)->next;
                curr = *head;
            }else{
                Node_t* tmp = curr;
                prev->next = curr->next;
                curr = curr->next;
                free(tmp);
            }
        }else{
            prev = curr;
            curr = curr->next;
        }
    }
}

void removePos(Node_t** head,int pos){ // Xóa phần tử vị trí pos
    int count = 0;
    Node_t* curr = *head;
    Node_t* prev = NULL;
    while(curr!= NULL){
        if(count == pos){
            if(prev == NULL){
                *head = (*head)->next;
                return;
            }else{
                Node_t* tmp = curr;
                prev->next = curr->next;
                free(tmp);
                return;
            }
        }else{
            prev = curr;
            curr = curr->next;
            count++;
        }
    }
}
void reverse(Node_t** head) { // Đảo các phần tử
    Node_t* prev = NULL;
    Node_t* curr = *head;
    Node_t* next = NULL;

    while (curr != NULL) {
        next = curr->next; // Lưu trữ nút tiếp theo trước khi thay đổi liên kết

        curr->next = prev; // Đảo liên kết

        prev = curr; // Di chuyển con trỏ prev và curr
        curr = next; // Di chuyển con trỏ curr và next
    }

    *head = prev; // Cập nhật con trỏ đầu để trỏ đến nút mới đảo ngược
}

data_t printPos(Node_t** head,int pos){ // Trả về phần tử vị trí pos
    int count = 0;
    Node_t* p = *head;
    while(p != NULL){
        if(count == pos){
            return p->data;
        }
        p = p->next;
        count++;
    }
}

void LinkedListConvert(Node_t** head, int u, int convertData){ // Đổi phần tử có data là u thành convertData
    Node_t* p = *head;
    while (p!= NULL)
    {
        if(p->data == u){
            p->data = convertData;
        }
        p = p->next;
    }
}

void printNode(Node_t** head){ // in các phần tử của ll
    Node_t* p = *head;
    while(p != NULL){
        printf("%d ",p->data);
        p = p->next;
    }
}

int main(){
    Node_t* head = NULL;
    int n;
    int k,v,u;
    scanf("%d",&n);
    for(int i = 0; i < n; i++){
        int k;
        scanf("%d",&k);
        insertLast(&head, k);
    }
    char input[20];
    while(1){
        scanf("%s",&input);
        if(strncmp(input, "#", 1) == 0) break; 
        if(strncmp(input,"addlast",7) == 0){
            scanf("%d",&k);
            insertLast(&head,k);
        } else if(strncmp(input,"addafter",7) == 0){
            scanf("%d %d",&u,&v);
            addAfter(&head,u,v);
        } else if(strncmp(input,"addbefore",9) == 0){
            scanf("%d %d",&u,&v);
            addBefore(&head,u,v);
        } else if(strncmp(input,"addfirst",8) == 0){
            scanf("%d",&k);
            addFirst(&head,k);
        } else if(strncmp(input,"remove",6) == 0){
            scanf("%d",&k);
            removePos(&head,findNode(head,k));  
        } else if(strncmp(input,"reverse",7) == 0){
            reverse(&head);
        }
    }
    printNode(&head);
    return 0;
}