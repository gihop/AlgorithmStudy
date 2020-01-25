//
//  스타트링크_5014.cpp
//  BFS
//
//  Created by jiho park on 2020/01/25.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <queue>

using namespace std;

bool check[1000001];//입력이 백만이 들어올 수 있기 때문에 1000001.
int dist[1000001];
int f, g, s, u[2];

bool ok(int next){
    if(next<=0 || next>f) return false;//건물을 벗어난 경우.
    if(check[next]) return false;//이미 방문한 층인 경우.
    return true;
}

int main(){
    cin >> f >> s >> g >> u[0] >> u[1];
    u[1]*=-1;//내려가는 버튼.
    check[s]=true;//시작 층 방문 기록.
    dist[s]=0;//버튼을 누른 횟수 0으로 시작.
    if(s == g){//가야할 층에 이미 있는 경우. 이 부분을 추가 안해서 처음에 오답이였음.
        cout << dist[s];
        return 0;
    }
    
    queue<int> q;
    q.emplace(s);
    
    while(!q.empty()){
        int now=q.front();
        q.pop();
        for(int i=0; i<2; i++){
            int next=now;
            next+=u[i];
            if(!ok(next)) continue;
            q.emplace(next);
            check[next]=true;
            dist[next]=dist[now]+1;
            if(next == g){
                cout << dist[next];
                return 0;
            }
        }
    }
    cout << "use the stairs";
    
    return 0;
}
