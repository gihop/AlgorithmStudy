#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

struct Node{
    int value;
    int x,y;
    Node *left;
    Node *right;
};

bool compare(const Node &a, const Node &b){
    if(a.y > b.y) return true;
    else if(a.y == b.y){
        if(a.x < b.x) return true;
        else return false;
    }
    else return false;
}

void add_node(Node *parent, Node *child){
    if(parent->x > child->x){
        if(parent->left == NULL) parent->left = child;
        else add_node(parent->left, child);
    }
    else{
        if(parent->right == NULL) parent->right = child;
        else add_node(parent->right, child);
    }
}

void pre_order(vector<vector<int>> &answer, Node *node){
    answer[0].push_back(node->value);
    if(node->left != NULL) pre_order(answer, node->left);
    if(node->right != NULL) pre_order(answer, node->right);
}

void post_order(vector<vector<int>> &answer, Node *node){
    if(node->left != NULL) post_order(answer, node->left);
    if(node->right != NULL) post_order(answer, node->right);
    answer[1].push_back(node->value);
}

vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
    vector<vector<int>> answer(2, vector<int>());
    vector<Node> Nodes;
    
    for(int i=0; i<nodeinfo.size(); i++){
        Node node;
        node.value = i+1;
        node.x = nodeinfo[i][0];
        node.y = nodeinfo[i][1];
        node.left = NULL;
        node.right = NULL;
        Nodes.push_back(node);
    }
    
    sort(Nodes.begin(), Nodes.end(), compare);

    Node *root = &Nodes[0];
    
    for(int i=1; i<Nodes.size(); i++){
        add_node(root, &Nodes[i]);
    }
    
    pre_order(answer, root);
    post_order(answer, root);
    
    return answer;
}
