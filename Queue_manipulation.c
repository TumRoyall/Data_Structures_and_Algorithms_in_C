#include<stdio.h>
#include<stdlib.h>

#define data_t int

typedef struct Node // Định nghĩa node
{
    data_t data;
    struct Node* next;
}Node_t;

typedef struct Queue // Định nghĩa queue
{
    Node_t* head;
    Node_t* tail;
}Queue_t;

void initialize(Queue_t* queue){ // khởi tạ một queue
    queue->tail = NULL;
    queue->head = NULL;
}

int isEmpty(Queue_t* queue){ // Kiểm tra coi queue có rỗng hay không.
    return (queue->head == NULL);
}



void enqueue(Queue_t* queue,data_t value){ // Thêm một phần tử vào hàng đợi
    Node_t* newNode = (Node_t*)malloc(sizeof(Node_t));
    if(newNode == NULL){
        printf("Memory allocation error\n");
        return;
    }
    newNode->data = value;
    newNode->next = NULL;
    if(isEmpty(queue)){
        queue->head = newNode;
        queue->tail = newNode;
    }else{
        queue->tail->next = newNode;
        queue->tail = newNode;
    }
}

data_t dequeue(Queue_t* queue) { // xóa phần tử đầu hàng đợi, và trả về giá trị của phần tử đó
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return -1;
    }

    int value = queue->head->data;
    Node_t* temp = queue->head;
    queue->head = queue->head->next;

    if (queue->head == NULL) {
        queue->tail = NULL;
    }

    free(temp);
    return value;
}

void printQueue(Queue_t* queue) { // in hàng đợi
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
    } else {
        Node_t* current = queue->head;
        printf("Head -> ");
        while (current != NULL) {
            printf("%d -> ", current->data);
            current = current->next;
        }
        printf("Tail\n");
    }
}


int main(){
    Queue_t queue;
    initialize(&queue);
    int n;
    scanf("%d",&n);
    for(int i = 0;i<n;i++){
        int temp;
        scanf("%d",&temp);
        enqueue(&queue,temp);
    }
    int k;
    scanf("%d",&k);
    k = k % n;
    while(k>0){
        int temp;
        temp = dequeue(&queue);
        enqueue(&queue,temp);
        k--;
    }
    printQueue(&queue);
    return 0;
}