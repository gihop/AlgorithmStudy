#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

vector<int> tree;
vector<int> arr;

int INF = 1000000001;

int init(int node, int start, int end){
    if(start == end) return tree[node] = arr[start];
    int mid = (start+end) / 2;
    return tree[node] = min(init(node*2, start, mid), init(node*2+1, mid+1, end));
}

int find(int node, int start, int end, int left, int right){
    if(left > end || right < start) return INF;
    if(left <= start && end <= right) return tree[node];
    int mid = (start+end)/2;
    return min(find(node*2, start, mid, left, right), find(node*2+1, mid+1, end, left, right));
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int N, M;
    cin >> N >> M;
    
    arr.resize(N);
    
    int h = ceil(log2(N));
    int tree_size = (1 << (h+1));
    
    tree.resize(tree_size);
    
    for(int i=0; i<N; i++){
        cin >> arr[i];
    }
    
    init(1, 0, N-1);
    
    for(int i=0; i<M; i++){
        int a, b;
        cin >> a >> b;
        cout << find(1, 0, N-1, a-1, b-1) << "\n";
    }
    
    return 0;
}
