#include <stdio.h>
#include <stdlib.h>

//定义Node
typedef struct BiTNode
{
    char data;
    struct BiTNode *lchild, *rchild, *parent;
}BiTNode;

//建立二叉树（先序）
BiTNode *create_tree(BiTNode *p)
{
    char c = getchar();
    if (c == '#')
    {
        p = NULL;
    }
    else
    {
        p = (BiTNode *)malloc(sizeof(BiTNode));
        p->data = c;
        p->lchild = create_tree(p->lchild);
        p->rchild = create_tree(p->rchild);
    }
    return p;
}

//设置parent指针
BiTNode *addparent(BiTNode *p, BiTNode *q)
{
    if (p != NULL)
    {
        p->parent = q;
        q = p;
        p->lchild = addparent(p->lchild, q);
        p->rchild = addparent(p->rchild, q);
    }
    return p;
}

//输出到根节点的路径
void path(BiTNode *p)
{
    while (p != NULL)
    {
        printf("%c ", p->data);
        p = p->parent;
    }
    printf("\n");
}

//输出所有节点到根节点的路径
void all_path(BiTNode *p)
{
    if (p != NULL)
    {
        path(p);
        all_path(p->lchild);
        all_path(p->rchild);
    }
}

int main()
{
    BiTNode *BiTree = NULL;
    printf("\n------Create Binary Tree------\n\n");
    BiTree = create_tree(BiTree);
    if (BiTree == NULL)
    {
        printf("Empty Binary Tree!\n");
    }
    addparent(BiTree, NULL);
    all_path(BiTree);
    system("pause");
    return 0;
}
