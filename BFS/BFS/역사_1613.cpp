//
//  역사_1613.cpp
//  BFS
//
//  Created by jiho park on 2020/02/10.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <cstring>
#include <map>

#define endl "\n"
using namespace std;

//s입력되고 들어오는 서로 다른 사건의 두 번호가 들어올때마다 이들이 연결여부를 검사했었는데
//이렇게 하니 시간초과가 발생했다.
//입력되는 s 값이 4만이나 되기 때문이다.
//그래서 s값이 입력되기 전에 미리 사건끼리의 관계를 모두 작성해서 시간초과를 해결할 수 있었다.

int conn[401][401];
int n, k, s;
map<int,int> gom, backm;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n >> k;
    
    vector<vector<int>> go(n+1), back(n+1);
    
    for(int i=0; i<k; i++){
        int a, b;
        cin >> a >> b;
        go[a].push_back(b);//어떤 사건 보다 뒤인 사건을 앞으로 가면서 찾기 위한 벡터.
        back[b].push_back(a);//어떤 사건 보다 앞인 사건을 뒤로 가면서 찾기 위한 벡터.
    }
    
    for(int i=1; i<=n; i++){//미리 사건간의 관계도를 모두 만들어 놓는다.
        queue<int> q;
        q.emplace(i);
        while(!q.empty()){
            int x = q.front();
            q.pop();
            for(int j=0; j<go[x].size(); j++){
                int nx=go[x][j];
                if(conn[i][nx]!=0) continue;
                conn[i][nx]=-1;
                q.emplace(nx);
            }
        }
        q.emplace(i);
        while(!q.empty()){
            int x = q.front();
            q.pop();
            for(int j=0; j<back[x].size(); j++){
                int nx=back[x][j];
                if(conn[i][nx]!=0) continue;
                conn[i][nx]=1;
                q.emplace(nx);
            }
        }
    }
    
    cin >> s;
    for(int i=0; i<s; i++){//a,b가 들어오면 연결 상태를 바로 출력할 수 있음.
        int a,b;
        cin >> a >> b;
        cout << conn[a][b] << endl;
    }
    
    return 0;
}
