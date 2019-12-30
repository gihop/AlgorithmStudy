#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
}Node;

Node *NewNode() {
    Node *New;
    New = (Node*)malloc(sizeof(Node));
    New->data = 0;
    New->left = NULL;
    New->right = NULL;
    return New;
}

void addtree(Node *root) {
    int x, y, z;
    scanf("%d %d %d",&x,&y,&z);
    (root)->data = x;
    
    if (y != 0)
    {
        Node *leftNode = NewNode();
        leftNode->data = y;
        (root)->left = leftNode;
        addtree((root)->left);
    }
    if (z != 0) {
        Node *rightNode = NewNode();
        rightNode->data = z;
        (root)->right = rightNode;
        addtree((root)->right);
    }
}
void print_Node(Node *root, char *x, int len) {
    int i;
    
    for(i = 0; i <= len; i++) {
        printf("%d ", root->data);
        if(x[i] == NULL)
            return;
        else if(x[i] == 'L')
            root = root->left;
        else
            root = root->right;
    }
}

void tree_free(Node *root) {
    if (root->left)
        tree_free(root->left); if (root->right)
            tree_free(root->right); free(root);
}

int main() {
    int i, n;
    scanf("%d", &n);
    Node *root = NewNode();
    
    addtree(root);
    
    scanf("%d", &n);
    
    char x[101];
    for (i = 0; i < n; i++) {
        scanf("%s", x);
        print_Node(root, x, (int)(strlen(x)));
        printf("\n");
    }
    
    tree_free(root);
    
    return 0;
}
