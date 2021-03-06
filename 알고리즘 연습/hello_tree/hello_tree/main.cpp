//
//  main.cpp
//  hello_tree
//
//  Created by jiho park on 14/08/2019.
//  Copyright © 2019 jiho park. All rights reserved.
//

#include <iostream>
#include <string>

using namespace std;

class Tree {
    string data;
    Tree *left, *right;
    
public:
    Tree() {
        data = "";
        left = NULL;
        right = NULL;
    }
    void setData(char data) {
        this->data = data;
    }
    void setLeft(Tree *left) {
        this->left = left;
    }
    void setRight(Tree *right) {
        this->right = right;
    }
    void static preorder(Tree *root) {
        if(root){
            cout << root->data;
            preorder(root->left);
            preorder(root->right);
        }
    }
    void static inorder(Tree *root) {
        if(root){
            inorder(root->left);
            cout<< root->data;
            inorder(root->right);
        }
    }
    void static postorder(Tree *root){
        if(root){
            postorder(root->left);
            postorder(root->right);
            cout << root->data;
        }
    }
};

int main() {
    int n;
    cin >> n;
    Tree *tree = new Tree[n];
    
    for(int i = 0; i < n; i++) {
        char data, left, right;
        cin >> data >> left >> right;
        if(data != '.'){
            tree[(int)(data - 'A')].setData(data);
        }
        if(left != '.'){
            tree[(int)(data - 'A')].setLeft(&tree[(int)(left - 'A')]);
        }
        else {
            tree[(int)(data - 'A')].setLeft(NULL);
        }
        if(right != '.'){
            tree[(int)(data - 'A')].setRight(&tree[(int)(right - 'A')]);
        }
        else{
            tree[(int)(data - 'A')].setRight(NULL);
        }
    }
    Tree *root = &tree[0];
    Tree::preorder(root);
    cout << endl;
    Tree::inorder(&tree[0]);
    cout << endl;
    Tree::postorder(&tree[0]);
    cout << endl;
}
