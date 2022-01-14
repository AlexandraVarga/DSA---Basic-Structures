#include <stdio.h>
#include <stdlib.h>
///declarare
typedef struct node_type
{
    int id;
    struct node_type *left, *right;

} NodeT;
///construire arbore
NodeT *createBinTreeFromFile (FILE *f)
{
    NodeT *p;
    int c;
    ///citire id nod
    fscanf(f,"%d",&c);
    if(c==0)
        return NULL; ///arbore vid, nu face nimic
    else
    {
        ///construim nodul la care pointeaza p
        p=(NodeT *)malloc(sizeof(NodeT));
        if(p==NULL)
            exit("Nu mai avem memmorie in createBinTree");
        ///populam nodul
        p->id=c;
        p->left=createBinTreeFromFile(f);
        p->right=createBinTreeFromFile(f);
    }
}
void preorder (NodeT *p,int *count_node)
{
    ///p- nodul curent
    if(p!=NULL)
    {
        (*count_node)++; ///numar nodurile din arbore
        printf("%d ",p->id);
        preorder(p->left,count_node);
        preorder(p->right,count_node);
    }
}
void inorder (NodeT *p)
{
    ///p- nodul curent
    if(p!=NULL)
    {
        inorder(p->left);
        printf("%d ",p->id);
        inorder(p->right);
    }
}
void postorder (NodeT *p)
{
    ///p- nodul curent
    if(p!=NULL)
    {
        postorder(p->left);
        postorder(p->right);
        printf("%d ",p->id);
    }
}
int leaf_node(NodeT *node)
{
    if(node==NULL)
        return 0;
    else if(node->left==NULL&&node->right==NULL)
        return 1;
    else
        return leaf_node(node->left)+leaf_node(node->right);
}
///noduri interne == noduri totale arbore - frunze
int noduri_interne(NodeT *node,int *count_node)
{
    return (*count_node)-(leaf_node(node));
}
int inaltime (NodeT *node)
{
    if(node==NULL)
        return 0;
    else
    {
        if(inaltime(node->left)>inaltime(node->right))return 1+inaltime(node->left);
        else return 1+inaltime(node->right);
    }
}
NodeT *search (NodeT *root, int key)
{
    if(root!=NULL)
    {
        if(root->id==key)
        {
            return root;
            exit(0);
        }
        search(root->left,key);
        search(root->right,key);
    }

}
NodeT *creBalBinTree (int nbOfNodes)
{
    NodeT *p;
    int nLeft,nRight;
    if(nbOfNodes<=0)
        return NULL;
    else
    {
        nLeft=nbOfNodes/2;
        nRight=nbOfNodes-nLeft-1;
        p=(NodeT*)malloc(sizeof(NodeT));
        printf("\nNode indentifier=",nLeft,nRight);
        scanf("%d",&(p->id));
        p->left=creBalBinTree(nLeft);
        p->right=creBalBinTree(nRight);
    }
    return p;
}
int main()
{
    ///ex. 1
    NodeT *root=NULL;
    FILE *f=fopen("ArboreBinar.txt","r");
    if(!f)
    {
        puts("Nu s-a putut deschide fisierul ArboreBinar.txt\n");
        exit(1);
    }
    int count_node=0;
    ///in fisier am : 1 7 2 0 5 0 0 0 9 3 0 0 4 0 6 0 0
    root=createBinTreeFromFile(f);///constructie arbore
    ///ex. 2
    preorder(root,&count_node);///preordine
    printf("\n");
    inorder(root);///inordine
    printf("\n");
    postorder(root);///postordine
    printf("\n");
    /// ex. 3
    printf("%d\n",leaf_node(root));///numar frunze arbore

    /// ex. 4
    ///ESTE OK?
    printf("%d\n",noduri_interne(root,&count_node)); ///numar noduri interne

    /// ex. 5
    printf("%d\n", inaltime(root));///inaltime arbore

    /// ex. 6
    ///ESTE OK?
    NodeT *nod_cautat=NULL;
    nod_cautat=search(root,3);
    printf("%d ",inaltime(nod_cautat));

    /// ex. 7
    root=NULL;
    int nbOfNodes=0;
    printf("\n Numarul de noduri din arbore este:");
    scanf("%d",&nbOfNodes);
    root=creBalBinTree(nbOfNodes); ///creare arbore binar total echilibrat
    printf("\n");
    inorder(root); ///parcurgere inordine / afisare arbore binar total echilibrat

    fclose(f);
    return 0;
}
