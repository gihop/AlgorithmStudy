//
//  DSLR_9019.cpp
//  BFS
//
//  Created by jiho park on 2020/02/22.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <queue>
#include <tuple>
#include <string>
#include <cstring>

#define endl "\n"
using namespace std;

//생각을 잘해야 풀 수 있다.
//처음에 bfs 순회할 때 큐에 string을 넣어서 쌓이는 string을 계속 복사했었는데 이 부분이 시간초과를 발생시켰다.
//string이 자주 복사되면 시간초과가 발생하니 이 부분은 피해야 한다.
//그래서 parent와 op배열을 만들어서 숫자가 어느 숫자에서 왔고 어떤 명령어로 왔는지 저장을 했다.
//최종값이 나오면 parent 배열을 추적해서 명령어를 조합하는 방식으로 풀었다.

int n;
int parent[10000];
char op[10000];

tuple<int,int,int,int> divide(int x){//숫자를 d1,d2,d3,d4로 나눠준다.
    int a[4]={0,},cnt=0;
    while(x>0){
        a[3-cnt++]=x%10;
        x/=10;
    }
    return make_tuple(a[0],a[1],a[2],a[3]);
}

int spin(int a, int b, int c, int d){//각각의 자릿수를 하나의 숫자로 만들어준다.
    int x=0, cnt=4, y[4]={a,b,c,d}, idx=0;
    bool found=false;
    while(cnt--){//1000과 0100이 들어왔을 때를 대비해야 한다.
        if(y[idx]==0){
            idx++;
            if(found && cnt!=0) x*=10;
            continue;
        }
        x+=y[idx++];
        found=true;
        if(cnt!=0) x*=10;
    }
    return x;
}

void bfs(int a, int b){
    string s="";
    queue<pair<int,char>> q;
    q.emplace(a,'.');
    while(!q.empty()){
        char ch;
        int x;
        tie(x,ch) = q.front();
        q.pop();
        if(x==b){
            while(x!=a){//최종값에서 최초값까지 추적한다.
                s.push_back(op[x]);//string 배열에 넣는다.
                x = parent[x];//어느 숫자에서 왔는지 찾는다.
            }
            for(int i=s.size()-1; i>=0; i--)//string 배열의 끝부분부터 출력한다.
                cout << s[i];
            cout << endl;
            return;
        }
        int d1,d2,d3,d4;
        tie(d1,d2,d3,d4) = divide(x);
        for(int i=0; i<4; i++){
            if(i==0){
                int nx=x*2;
                if(nx>=10000) nx%=10000;
                if(parent[nx]>=0) continue;
                parent[nx]=x;
                op[nx]='D';
                q.emplace(nx,'D');
            }else if(i==1){
                int nx=x-1;
                if(nx<0) nx = 10000+nx;
                if(parent[nx]>=0) continue;
                parent[nx]=x;
                op[nx]='S';
                q.emplace(nx,'S');
            }else if(i==2 && ch!='R'){
                int nx = spin(d2,d3,d4,d1);
                if(parent[nx]>=0) continue;
                parent[nx]=x;
                op[nx]='L';
                q.emplace(nx,'L');
            }else if(i==3 && ch!='L'){
                int nx = spin(d4,d1,d2,d3);
                if(parent[nx]>=0) continue;
                parent[nx]=x;
                op[nx]='R';
                q.emplace(nx,'R');
            }
        }
    }
}

int main(){
    cin >> n;
    
    for(int i=0; i<n; i++){
        memset(parent, -1, sizeof(parent));
        memset(op, 0, sizeof(op));
        int a,b;
        cin >> a >> b;
        bfs(a,b);
    }
    
    return 0;
}
