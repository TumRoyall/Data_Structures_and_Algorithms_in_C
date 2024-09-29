#include<stdio.h>
#include<stdlib.h>

#define data_t int

typedef struct Node // Định nghĩa node
{
    data_t data;
    struct Node* next;
}Node_t;

typedef struct Stack // Định nghĩa stack
{
    Node_t* top;
}Stack_t;

void initialize(Stack_t* stack){// Khởi tạo 1 stack rỗng
    stack->top = NULL;
}

int isEmpty(Stack_t* stack) {// Kiểm tra xem stack có rỗng không
    return (stack->top == NULL);
}

void pushStack(Stack_t* stack,data_t data){// Thêm phần tử có data vào stack
    Node_t* newNode = (Node_t*)malloc(sizeof(Node_t));
    if(newNode==NULL){
        printf("Khong the cap phat! error");
        return;
    }
    newNode->data = data;
    newNode->next = stack->top;
    stack->top = newNode;  
}


data_t popStack(Stack_t* stack){// Lấy phần tử top của stack ra, trả về phần tử top, nếu stack null trả về -1
    data_t popElement;
    if(isEmpty(stack)){
        printf("Stack empty");
        return -1;
    }
    Node_t* cur = stack->top;
    popElement = cur->data;
    stack->top = stack->top->next;
    free(cur);
    return popElement;
}


void printStack(Stack_t* Stack){// In ra các phần tử của stack
    Node_t* p = Stack->top;
    while(p != NULL){
        printf("%d ",p->data);\
        p = p->next;
    }
}

int main(){
    Stack_t stack;
    initialize(&stack);
    return 0;
}