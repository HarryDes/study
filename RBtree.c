#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct BRtree
{
    int color; //1 black 0 red
    int key;
    struct BRtree *parent;
    struct BRtree *left;
    struct BRtree *right;
} BRtree;
void left_rotate(BRtree *node, int flag)
{
    BRtree*parent=node->parent;
    parent->right = node->left;
    if(node->left!=NULL) node->left->parent=parent;
    node->left = parent;
    node->parent = parent->parent;
    parent->parent=node;
    if (flag == 1)
        node->parent->right = node;
    else if (flag == -1)
        node->parent->left = node;
}
void right_rotate(BRtree *node, int flag)
{
    BRtree*parent=node->parent;
    parent->left = node->right;
    if(node->right!=NULL) node->right->parent=parent;
    node->right = parent;
    node->parent = parent->parent;
    parent->parent=node;
    if (flag == 1)
        node->parent->right = node;
    else if (flag == -1)
        node->parent->left = node;
}
BRtree *BRtree_Fix(BRtree *newNode, BRtree *root)
{
    if (newNode->parent == NULL)
    {
        newNode->color = 1;
        return newNode;
    }
    else if(newNode->parent->parent==NULL)
    {
        newNode->parent->color=1;
        return newNode->parent;
    }
    else if (newNode->parent->color == 1)
    {
        return root;
    }
    else
    {
        BRtree *parent = newNode->parent;
        BRtree *grand = parent->parent;
        if (grand->left != NULL && grand->right != NULL&&grand->left->color==0&&grand->right->color==0)
        {
            //if (grand->left->color == 0 && grand->right->color == 0)
            //{
                grand->color = 0;
                grand->left->color = 1;
                grand->right->color = 1;
                return BRtree_Fix(grand, root);
            //}
        }
        else if (grand->left == parent && parent->right == newNode)
        {
            left_rotate(newNode, -1);
            BRtree*tmp=root;
            while(tmp->parent!=NULL) tmp=tmp->parent;
            return BRtree_Fix(parent, tmp);
        }
        else if (grand->right == parent && parent->left == newNode)
        {
            right_rotate(newNode, 1);
            BRtree*tmp=root;
            while(tmp->parent!=NULL) tmp=tmp->parent;
            return BRtree_Fix(parent, tmp);
        }
        else if (grand->left == parent && parent->left == newNode)
        {
            int flag = 0;
            if (grand->parent == NULL)
                flag = 0;
            else if (grand->parent->right == grand)
                flag = 1;
            else
                flag = -1;
            right_rotate(parent, flag);
            parent->color = 1;
            grand->color = 0;
        }
        else
        {
            int flag = 0;
            if (grand->parent == NULL)
                flag = 0;
            else if (grand->parent->right == grand)
                flag = 1;
            else
                flag = -1;
            left_rotate(parent, flag);
            parent->color = 1;
            grand->color = 0;
        }
        BRtree*tmp=root;
        while (tmp->parent != NULL)
        {
            tmp = tmp->parent;
        }
        return tmp;
    }
}
BRtree *insert(BRtree *root, int key)
{
    BRtree *tmp = root;
    BRtree *prve = NULL;
    while (tmp != NULL)
    {
        prve = tmp;
        if (key >= tmp->key)
            tmp = tmp->right;
        else
            tmp = tmp->left;
    }
    BRtree *newNode = (BRtree *)malloc(sizeof(BRtree));
    newNode->parent = prve;
    newNode->key = key;
    newNode->color = 0;
    newNode->left = NULL;
    newNode->right = NULL;
    if (prve != NULL)
    {
        if (key >= prve->key)
            prve->right = newNode;
        else
            prve->left = newNode;
    }
    if (root == NULL)
        root = newNode;
    return BRtree_Fix(newNode, root);
}
void print(BRtree *root)
{
    if (root == NULL)
        return;
    print(root->left);
    if(root->color==1) printf("B");
    else printf("R");
    print(root->right);
}
int main()
{
    BRtree *root = NULL;
    int n=0;
    scanf("%d",&n);
    int i=0;
    for(i=0;i<n;i++)
    {
        int num=0;
        scanf("%d",&num);
        root=insert(root,num);
    }
    print(root);
    return 0;
}