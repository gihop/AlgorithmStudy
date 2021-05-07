#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

/*
 처음 풀어본 세그먼트 트리 문제.
 주의사항을 잘 알아두자.
 arr, tree는 전역변수로 선언해야한다.(그렇지 않으면 메모리 초과뜬다.)
 update에서 start==end일 경우 arr의 값도 바꿔줘야 한다.
 diff를 구할 때 다시 사용하기 때문이다.
 그리고 update할 때 c값은 long long으로 들어올 수 있음을 주의해야한다.
 */

vector<long long> arr;
vector<long long> tree;

long long init(int node, int start, int end){
    if(start == end)
        return tree[node] = arr[start];
    int mid = (start+end)/2;
    return tree[node] = init(node*2, start, mid) + init(node*2+1, mid+1, end);
}

void update(int node, int start, int end, int index, long long diff){
    if(!(start <= index && index <= end)) return;
    tree[node] += diff;
    if(start == end) arr[index] += diff;
    else{
        int mid = (start+end) / 2;
        update(node*2, start, mid, index, diff);
        update(node*2+1, mid+1, end, index, diff);
    }
}

long long sum(int node, int start, int end, int left, int right){
    if(left > end || start > right) return 0;
    if(left <= start && end <= right) return tree[node];
    int mid = (start+end)/2;
    return sum(node*2, start, mid, left, right) + sum(node*2+1, mid+1, end, left, right);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int N, M, K;
    cin >> N >> M >> K;
    
    arr.resize(N);
    
    for(int i=0; i<N; i++){
        cin >> arr[i];
    }
    
    int h = ceil(log2(N));
    
    int tree_size = (1 << (h+1));
    
    tree.resize(tree_size);
    init(1, 0, N-1);
    
    for(int i=0; i<M+K; i++){
        int a, b;
        long long c;
        cin >> a >> b >> c;
        if(a == 1){
            long long diff = c - arr[b-1];
            update(1, 0, N-1, b-1, diff);
        }
        else{
            cout << sum(1, 0, N-1, b-1, (int)c-1) << "\n";
        }
    }
    
    return 0;
}
