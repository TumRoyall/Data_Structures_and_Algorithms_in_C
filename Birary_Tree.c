#include <stdio.h>
#include <stdlib.h>

typedef struct Birary_Tree
{
    int id;
    struct Birary_Tree *leftChild;
    struct Birary_Tree *rightChill;
} BNode_t;

BNode_t *makeNode(int id)
{
    BNode_t *new = (BNode_t *)malloc(sizeof(BNode_t));
    if (new == NULL)
    {
        printf("Memory allocation error!");
        return NULL;
    }
    new->id = id;
    new->leftChild = NULL;
    new->rightChill = NULL;
    return new;
}

BNode_t *find(int id, BNode_t *r)
{
    if (r == NULL)
        return NULL;
    if (r->id == id)
        return r;
    BNode_t *tmp = find(id, r->leftChild);
    if (tmp != NULL)
        return tmp;
    tmp = find(id, r->rightChill);
    if (tmp != NULL)
        return tmp;
    return NULL;
}

void addChildP(int id, BNode_t *p)
{ // them con sau nut p
    if (p == NULL)
        return;
    if (p->leftChild == NULL)
    {
        BNode_t *new = makeNode(id);
        p->leftChild = new;
        return;
    }
    if (p->rightChill == NULL)
    {
        BNode_t *new = makeNode(id);
        p->rightChill = new;
        return;
    }
    return;
}

void addChild(int id, int p, BNode_t *r)
{ // thêm nút có định danh id sau nút có định danh p ở cây nhị phân p
    BNode_t *tmp = find(p, r);
    addChildP(id, tmp);
}

void inOder(BNode_t *r)
{
    if (r == NULL)
        return;
    inOder(r->leftChild);
    printf("%d ", r->id);
    inOder(r->rightChill);
}

void preOder(BNode_t *r)
{
    if (r == NULL)
        return;
    printf("%d ", r->id);
    preOder(r->leftChild);
    preOder(r->rightChill);
}

void postOder(BNode_t *r)
{
    if (r == NULL)
        return;
    postOder(r->leftChild);
    postOder(r->rightChill);
    printf("%d ", r->id);
}

int count(BNode_t *r)
{
    if (r == NULL)
        return 0;
    return count(r->leftChild) + count(r->rightChill) + 1;
}

int main()
{
    BNode_t *r = makeNode(10);
    addChildP(1, r);
    addChildP(2, r);
    addChild(3, 2, r);
    addChild(4, 2, r);
    addChild(5, 4, r);
    addChild(6, 4, r);
    addChild(7, 1, r);
    preOder(r);
    printf("\n");
    postOder(r);
    printf("\n");
    inOder(r);
    return 0;
}