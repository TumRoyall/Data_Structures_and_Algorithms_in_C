#include<stdio.h>
#include<stdlib.h>

typedef struct NodeTree // định nghĩa cây bình thường
{
    int id;
    struct NodeTree* leftMostChild;
    struct NodeTree* rightSibling;
}Node_t;




Node_t* makeNode(int id){ // Tạo một nút có key là id
    Node_t* p = (Node_t*)malloc(sizeof(Node_t));
    if(p == NULL){
        printf("Memory allocation error!");
        return NULL ;
    }
    p->id = id;
    p->leftMostChild = NULL;
    p->rightSibling = NULL;
    return p;
}




Node_t* find(int id, Node_t* r) { // tìm nút có key là id và trả về nút đó
    if (r == NULL) return NULL;
    if (r->id == id) return r;
    for (Node_t* p = r->leftMostChild; p != NULL; p = p->rightSibling) {
        Node_t* q = find(id,p);
        if (q != NULL) return q;
    }
    return NULL;
}



void addChildP(int id, Node_t* p){// Thêm 1 nút con có định danh 'id' vào cuối danh sách con của 1 nút P
    if( p == NULL) return;
    if(p->leftMostChild == NULL){
        Node_t* newNode = makeNode(id);
        p->leftMostChild = newNode;
        return;
    }
    Node_t* q = p->leftMostChild;
    while (q->rightSibling != NULL)
    {
        q = q->rightSibling;
    }
    Node_t* new = makeNode(id);
    q->rightSibling = new;
}



void insert(int id, int p, Node_t* r){// Thêm 1 nút có định danh 'id' chưa tồng tại vào cuối danh sách con của 1 nút có định danh 'd' đã tòn tại của cây r.
    if(find(id,r) != NULL) return; //Nếu tồn tại id rồi thì không thêm nữa
    Node_t * cur = find(p,r);
    addChildP(id,cur);
}




void preOder(Node_t* r){// Duyệt theo thứ tự trước (printf)
    if(r == NULL) return;
    printf("%d ",r->id);
    Node_t* p = r->leftMostChild;

    while (p!= NULL)
    {
        preOder(p);
        p = p->rightSibling;
    }
}


void inOrder(Node_t* r){ // Duyệt theo thứ tự giữa
if(r == NULL) return;
Node_t* p = r->leftMostChild;
inOrder(p);
printf("%d ",r->id);
if(p != NULL) 
p = p->rightSibling;
while(p != NULL){
inOrder(p);
p = p->rightSibling;
}
}



void postOrder(Node_t* r){ // Duyết theo thứ tự sau
    if(r == NULL) return;
    Node_t* p = r->leftMostChild;
    while (p != NULL)
    {
        postOrder(p);
        p = p->rightSibling;
    }
    printf("%d ",r->id);
}




void printTree(Node_t* r){ // in cây
    if(r == NULL) return;
    printf("%d: ",r->id);
    
    Node_t* p = r->leftMostChild;
    while (p!= NULL)
    {
        printf("%d ",p->id);
        p = p->rightSibling;
    }
    printf("\n");
    
    p = r->leftMostChild;
    while (p != NULL)
    {
        printTree(p);
        p = p->rightSibling;
    }
}




int countNode(Node_t* r){ // Đếm số nút
    if(r == NULL) return 0;
    Node_t* p = r->leftMostChild;
    int count = 1;
    while( p != NULL){
        count += countNode(p);
        p = p->rightSibling;
    }
    return count;
}





int countLeaves(Node_t* r){ // Đếm số lá
    int count = 0;
    if(r == NULL) return 0;
    Node_t* p = r->leftMostChild;
    if(p == NULL) return 1;
    while (p != NULL)
    {
        count += countLeaves(p);
        p = p->rightSibling;
    }
    return count;
}





int height(Node_t* r){  // Trả về độ cao của cây
    if(r == NULL) return 0;
    int MaxHeight = 0;
    Node_t* p = r->leftMostChild;
    while (p!=NULL)
    {
        int h = height(p);
        if(h>MaxHeight) MaxHeight = h;
        p = p->rightSibling;
    }
    return MaxHeight+1;
}




/*  Cách 1: 
int depthP(int id, Node_t* p, int dp){ // Trả về độ sâu của cây
    // p co do sau dr
    if(p == NULL) return 0;
    if(p->id == id) return dp;
    for(Node_t* q = p->leftMostChild; q != NULL; q = q->rightSibling){
        if(q->id == id) return dp + 1;
        int d = depthP(id,q,dp+1);
        if(d>0) return d;
    }
    return 0;
}

int depth(int id, Node_t* r){
    return depthP(id,r,1);
}
*/
int depth(int id, Node_t* r){ // Trả về độ sâu của cây
    int dp = 1;
    if(r == NULL) return 0;
    if(r->id == id) return 1;
    Node_t* p = r->leftMostChild;
    while (p != NULL)
    {
        if(p->id == id) return dp + 1;
        int h = depth(id,p);
        if(h>1) return dp + h;
        p = p->rightSibling;
    }
    return 0;
}



Node_t* parent(Node_t* p, Node_t* r){ // Trả về cha của 1 nút
    if(r == NULL) return NULL;
    Node_t* q = r->leftMostChild;
    while (q != NULL)
    {
        if(q == p) return r;
        Node_t* pp = parent(p,q);
        if(pp != NULL) return pp;
        q = q->rightSibling;
    }
    return NULL;
}


int main(){
    Node_t* root = makeNode(10);
    Node_t* p;
    addChildP(11,root);
    addChildP(12,root);
    addChildP(13,root);
    insert(3,11,root);
    insert(4,11,root);
    insert(2,4,root);
    insert(0,3,root);
    insert(43,2,root);
    insert(41,2,root);
    insert(5,41,root);

    preOder(root);
    printf("\n");
    inOrder(root);
    printf("\n");
    postOrder(root);
    printf("\n");
    printTree(root);
    printf("\n %d",depth(2,root));
    return 0;
}