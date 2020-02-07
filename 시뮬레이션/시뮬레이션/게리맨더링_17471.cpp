//
//  게리맨더링_17471.cpp
//  시뮬레이션
//
//  Created by jiho park on 2020/02/06.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <cstdlib>

#define endl "\n"
using namespace std;

//이 문제에서 관건은 1이상의 조합을 만드는 것과 conn[10][10] 배열을 만드는 것이다.
//1번 지역과 2번 지역이 연결이 되어있다면 conn[1][2]=true; conn[2][1]=true; 가 핵심이다.

int n;
int person[10];
bool conn[10][10];
bool selected[10];
bool check_conn[10];
int ans=999999999;

bool check_connection(vector<int> v){//선거구 내의 지역들이 모두 연결되어 있는지 검사한다.
    memset(check_conn, false, sizeof(check_conn));
    queue<int> q;
    q.emplace(v[0]);//첫 번째 지역을 큐에 넣는다.
    int cnt=1;
    bool t=selected[v[0]];//첫 번째 지역이 true인지 false 인지 저장한다. 같은 선거구인지 확인하기 위함이다.
    check_conn[v[0]]=true;//이미 방문한 지역을 다시 안가기 위함.
    while(!q.empty()){
        int num = q.front();
        q.pop();
        for(int i=0; i<n; i++){
            if(!conn[num][i]) continue;//두 지역이 연결되어있지 않은 경우.
            if(check_conn[i]) continue;//이미 방문한 지역인 경우.
            if(t != selected[i]) continue;//같은 선거구가 아닌 경우.
            cnt++;
            check_conn[i]=true;
            q.emplace(i);
        }
    }
    if(cnt == v.size())//벡터에 넣어있는(같은 선거구) 같은 지역의 숫자와 cnt 숫자가 같으면 모두 연결되어 있음을 뜻한다. 지역구내에 첫 번째 지역부터 같은 선거구 내의 다른 지역을 모두 방문할 수 있기 때문.
        return true;
    else
        return false;
}

void go(int idx, int cnt){//조합(순서 상관없는)이므로 idx를 이용한다. 이전 인덱스를 필요로 하지 않는다.
    if(cnt>0){//한개라도 지역을 뽑으면 실행된다. 이 부분에는 return이 없다.
        vector<int> a,b;
        for(int i=0; i<n; i++){
            if(selected[i])//select에 표시된 true 지역은 a 벡터, false는 b 벡터.
                a.push_back(i);
            else
                b.push_back(i);
        }
        bool check=true;
        if(a.empty() || b.empty()) check=false;//각 선거구가 하나의 지역구를 가지고 있어야 한다.
        if(check){//각 선거구가 최소 한개의 지역을 가지고 있을 경우.
            if(check_connection(a) && check_connection(b)){//각 선거구내의 지역들이 모두 연결되어 있는 경우.
                int apop=0, bpop=0;
                for(int i=0; i<a.size(); i++)
                    apop+=person[a[i]];
                for(int i=0; i<b.size(); i++)
                    bpop+=person[b[i]];
                int sub = abs(apop-bpop);
                if(ans > sub)
                    ans = sub;
            }
        }
    }
    for(int i=idx; i<n; i++){
        if(selected[i]) continue;
        selected[i]=true;
        go(i, cnt+1);//idx가 아니라 i를 보내야 한다. 자주 실수하는 부분.
        selected[i]=false;
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n;
    
    for(int i=0; i<n; i++)
        cin >> person[i];
    
    for(int i=0; i<n; i++){
        int cnt;
        cin >> cnt;
        for(int j=0; j<cnt; j++){
            int tmp;
            cin >> tmp;
            conn[i][tmp-1]=true;//지역이 연결되어있는 곳을 배열에 저장한다.
            conn[tmp-1][i]=true;
        }
    }
    
    go(0,0);
    
    if(ans == 999999999)
        cout << -1;
    else
        cout << ans;
    
    return 0;
}
