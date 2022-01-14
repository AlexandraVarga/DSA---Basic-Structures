#include <stdio.h>
#include <stdlib.h>
typedef int KeyType;//tip cheie

typedef struct node
{
    KeyType key;
    struct node *left;
    struct node *right;
}NodeT;

///inserare nod in arbore binar de cautare
NodeT* insertNode(NodeT* root, int key)
{
    if(root)
    {
        if(key>root->key)
            root->right=insertNode(root->right,key);
        else if (key<root->key)
            root->left=insertNode(root->left,key);
        return root;
    }
    else
    {
        NodeT* p=(NodeT*)malloc(sizeof(NodeT));
        p->key=key;
        p->left=NULL;
        p->right=NULL;
        return p;
    }

}
NodeT *searchNodeRec (NodeT *root, int key)
{
    ///arbore vid / cheie cautata este in radacina
    if(root==NULL||root->key==key)
        return root;
    ///key>root->key caut in subarbore drept
    if(root->key<key)
        return searchNodeRec(root->right,key);
    ///key<root->key caut in subarbore stang
    return searchNodeRec(root->left,key);
}
void inorder (NodeT *root)
{
    if(root)
    {
        inorder(root->left);
        printf("%d ",root->key);
        inorder(root->right);
    }
}
void preorder(NodeT *root)
{
    if(root)
    {
        printf("%d ",root->key);
        preorder(root->left);
        preorder(root->right);
    }
}
void postorder(NodeT *root)
{
    if(root)
    {
        postorder(root->left);
        postorder(root->right);
        printf("%d ",root->key);
    }
}
NodeT *findMin(NodeT *node)
{
    NodeT *mn=node;
    if(node->left)
        mn=findMin(node->left);
    return mn;
}
NodeT *findMax(NodeT *node)
{
    NodeT *mx=node;
    if(node->right)
        mx=findMax(node->right);
    return mx;
}
NodeT *succesor (NodeT *node)
{
    NodeT *s=NULL;
    if(node->right)
        s=findMin(node->right);
    else
    {

    }
    return s;

}
NodeT *predecesor (NodeT *node)
{
    NodeT *p=NULL;
    if(node->left)
        p=findMax(node->left);
    else
    {

    }
    return p;
}
NodeT *deleteNode (NodeT *root, int key)
{
    NodeT *p;
    ///arbore vid
    if(root==NULL)
        return root;
    ///key<root->key caut in subarbore stang
    if(key<root->key)
        root->left=deleteNode(root->left,key);
    ///key>root->key, caut in subaorbore drept
    else if (key>root->key)
        root->right=deleteNode(root->right,key);
    else
    {
        ///nodul are un singur fiu
        if(root->left==NULL)
        {
            p=root->right;
            free(root);
            return p;
        }
        else if (root->right==NULL)
        {
            p=root->left;
            free(root);
            return p;
        }
        ///nodul are 2 fii
        ///determin nod minim subarbore drept in p
        p=findMin(root->right);
        root->key=p->key;
        root->right=deleteNode(root->right,p->key);

    }
    return root;
}
int main()
{

    NodeT *root=NULL;
    FILE *f=fopen("ArboreBinCautare.txt","r");
    if(!f)
    {
        puts("Nu s-a putut deschide fisierul ArboreBinCautare");
        exit(-1);
    }
    int key;
    ///in fisier am : 15 6 18 20 17 7 13 3 2 4 9
    ///ex 1
    while(fscanf(f,"%d",&key)==1)
            root=insertNode(root,key);

    ///ex 2
    NodeT *p=NULL;
    for (int i=0;i<3;i++)
        p=searchNodeRec(root,i);
    inorder(p);

    ///ex 3
    printf("\n");
    inorder(root);
    printf("\n");
    preorder(root);
    printf("\n");
    postorder(root);
    printf("\n");
    ///4
    NodeT *mn=NULL;
    mn=findMin(root);
    printf("%d ",mn->key);
    printf("\n");
    ///5
    NodeT *mx=NULL;
    mx=findMax(root);
    printf("%d ",mx->key);
    printf("\n");
    ///6 NU INTELEG CAZUL IN CARE SUBARBORELE DREPT E VID
    NodeT *sc=NULL;
    sc=succesor(root);
    printf("%d ",sc->key);
    printf("\n");
    ///7 NU INTELEG CAZUL IN CARE SUBARBORELE STANG E VID
    NodeT *pr=NULL;
    pr=predecesor(root);
    printf("%d",pr->key);
    printf("\n");
    ///8
    NodeT *d=deleteNode(root,20);
    inorder(d);

    fclose(f);
    return 0;
}
