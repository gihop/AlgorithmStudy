#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

/*
 구간 합과 비슷한 구간 곱 문제이다.
 합이 아니라 곱인 경우 update가 달라져야 한다.
 원소가 0이면 이 원소와 곱해지는 값은 모두 0이된다.
 그래서 구간합 처럼 update 시에 탐색을 하면서 값을 update하는 것이 아니라,
 먼저 값을 찾아서 바꾼 후에 backtraking하면서 값을 바꿔준다.
 */

int INF = 1000000007;
vector<int> arr;
vector<int> tree;

int init(int start, int end, int node){
    if(start == end) return tree[node] = arr[start];
    int mid = (start + end) / 2;
    return tree[node] = (int)((long long)init(start, mid, node*2) * (long long)init(mid+1, end, node*2+1) % INF);
}

int update(int node, int start, int end, int index, int next){
    if(!(start <= index && index <= end)) return tree[node];
    if(start == end){
        arr[start] = next;
        return tree[node] = next;
    }
    else{
        int mid = (start+end)/2;
        return tree[node] = (int)((long long)update(node*2, start, mid, index, next) * (long long)update(node*2+1, mid+1, end, index, next) % INF);
    }
}

int mul(int node, int start, int end, int left, int right){
    if(start > right || end < left) return 1;
    if(start >= left && end <= right) return tree[node];
    int mid = (start+end)/2;
    return (int)((long long)mul(node*2, start, mid, left, right) * (long long)mul(node*2+1, mid+1, end, left, right) % INF);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int N, M, K;
    cin >> N >> M >> K;
    
    arr.resize(N);
    
    int h = ceil(log2(N));
    int tree_size = (1 << (h+1));
    tree.resize(tree_size);
    
    for(int i=0; i<N; i++){
        cin >> arr[i];
    }
    
    init(0, N-1, 1);
    
    for(int i=0; i<M+K; i++){
        int a, b, c;
        cin >> a >> b >> c;
        if(a == 1){
            update(1, 0, N-1, b-1, c);
        }
        else{
            cout << mul(1, 0, N-1, b-1, c-1) << "\n";
        }
    }
    
    
    return 0;
}
