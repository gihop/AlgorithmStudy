#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

//전위순회, 후위순회 문제.
//Node 구조를 만든 뒤에 sort로 y가 큰 값, x가 작은 값으로 정렬한다.
//addNode로 구조를 만든 뒤에 preorder, postorder 해준다.

struct Node{
    int order;
    int x,y;
    Node *left;
    Node *right;
};

bool compare(const Node &a, const Node &b){
    if(a.y > b.y) return true;
    if(a.y == b.y)
        if(a.x < b.x) return true;
    return false;
}

void addNode(Node *parent, Node *child){
    if(parent->x > child->x){
        if(parent->left == NULL) parent->left = child;
        else addNode(parent->left, child);
    }
    else{
        if(parent->right == NULL) parent->right = child;
        else addNode(parent->right, child);
    }
}

void preorder(vector<vector<int>> &answer, Node *node){
    if(node == NULL) return;
    answer[0].push_back(node->order);
    preorder(answer, node->left);
    preorder(answer, node->right);
}

void postorder(vector<vector<int>> &answer, Node *node){
    if(node == NULL) return;
    postorder(answer, node->left);
    postorder(answer, node->right);
    answer[1].push_back(node->order);
}

vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
    vector<vector<int>> answer;
    answer.resize(2);
    vector<Node> nodes;
    
    for(int i=0; i<nodeinfo.size(); i++){
        Node node;
        node.x = nodeinfo[i][0];
        node.y = nodeinfo[i][1];
        node.order = i+1;
        node.left = NULL;//NULL로 반드시 초기화를 해줘야 한다. 하지 않으면 addNode가 안된다.
        node.right = NULL;
        nodes.push_back(node);
    }
    
    sort(nodes.begin(), nodes.end(), compare);
    
    Node *root = &nodes[0];
    
    for(int i=1; i<nodes.size(); i++){
        addNode(root, &nodes[i]);
    }
    
    preorder(answer, root);
    postorder(answer, root);
    
    return answer;
}
