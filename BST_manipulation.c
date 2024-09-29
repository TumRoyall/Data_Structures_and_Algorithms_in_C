#include<stdio.h>
#include<stdlib.h>

#define data_t int

typedef struct BSTNode
{
    data_t id;
    struct BSTNode* leftNode;
    struct BSTNode* rightNode;
}BSTNode_t;

BSTNode_t* makeNode(data_t v){ // tạo ra một nút mới có khóa v
    BSTNode_t* new;
    new = (BSTNode_t*)malloc(sizeof(BSTNode_t));
    if(new == NULL) return NULL;
    new->id = v;
    new->leftNode = NULL;
    new->rightNode = NULL;
    return new;  
}

/*  // cách này dùng void
void insert(BSTNode_t** root, int v){ // thêm nút có id là v chèn vào nút BST có gốc là root 
    BSTNode_t* p = *root;
    if(p == NULL){
        *root = makeNode(v);
    }else{
        if(v >= p->id) insert(&(p->rightNode), v);
        else insert(&(p->leftNode), v);
    }
}
*/

BSTNode_t* insert(BSTNode_t* root, int v){// thêm nút có id là v chèn vào nút BST có gốc là root 
    if(root == NULL){
        root = makeNode(v);
    } else{
        if( v > root->id) root->rightNode = insert(root->rightNode, v);
        else if(v < root->id) root->leftNode = insert(root->leftNode, v);
    }
    return root;
}

BSTNode_t* search(BSTNode_t* root, int v){ // tìm và trả về nút có khóa bằng v trong BST gốc r
    if(root == NULL) return NULL;
    if(root->id == v) return root;
    if(v >= root->id) return search(root->rightNode, v);
    return search(root->leftNode, v);
}

BSTNode_t* findMin(BSTNode_t* root){
    BSTNode_t* p = root;
    while (p->leftNode != NULL)
    {
        p = p->leftNode;
    }
    return p;
}

BSTNode_t* del(BSTNode_t* root, int v){
    if(root == NULL) return NULL;
    if(v > root->id) root->rightNode = del(root->rightNode, v); // nếu value > id thì thực hiện xóa trên nhánh phải
    else if(v < root->id) root->leftNode = del(root->leftNode, v); // nếu value < id thì thực hiện xóa trên nhánh trái
    else{ // nếu value = id thực hiện xóa: 
// trường hợp cần xóa có đầy đủ 2 con
        if(root->leftNode != NULL && root->rightNode != NULL){
            BSTNode_t* tmp = findMin(root->rightNode);
            root->id = tmp->id;
            root->rightNode = del(root->rightNode, v);
        }
//trường hợp nút cần xóa là 0 hoặc 1 con
        if(root->leftNode == NULL){
            BSTNode_t* tmp = root->rightNode;
            free(root);
            return tmp;
        }

        else if(root->rightNode == NULL){
            BSTNode_t* tmp = root->leftNode;
            free(root);
            return tmp;
        }
    }
}


int main(){
    return 0;
}