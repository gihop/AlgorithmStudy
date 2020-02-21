//
//  닭싸움_팀_정하기.cpp
//  BFS
//
//  Created by jiho park on 2020/02/21.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <queue>
#include <vector>
#include <tuple>

#define endl "\n"
using namespace std;

//입력받을 때 친구와 원수를 잘 정리해야한다.

bool check[1001];
vector<int> Friend[1001];
vector<int> Enemy[1001];
int n, m;
int ans=0;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> n >> m;
    for(int i=0; i<m; i++){
        char rel;
        int a,b;
        cin >> rel >> a >> b;
        if(rel == 'F'){//친구 관계는 바로 벡터에 저장해준다.
            Friend[a].push_back(b);
            Friend[b].push_back(a);
        }else{//원수인 경우.
            if(Enemy[a].size()>0){//a와 원수 관계인 학생이 이미 있는 경우.
                for(int j=0; j<Enemy[a].size(); j++){//a와 원수 관계인 학생들은 b와는 친구.
                    Friend[Enemy[a][j]].push_back(b);
                    Friend[b].push_back(Enemy[a][j]);
                }
            }
            if(Enemy[b].size()>0){//b와 원수 관계인 학생이 이미 있는 경우.
                for(int j=0; j<Enemy[b].size(); j++){//b와 원수 관계인 학생들은 a와는 친구.
                    Friend[Enemy[b][j]].push_back(a);
                    Friend[a].push_back(Enemy[b][j]);
                }
            }
            Enemy[a].push_back(b);//원수 관계 저장.
            Enemy[b].push_back(a);
        }
    }
    for(int i=1; i<=n; i++){
        if(check[i]) continue;//이미 어느 팀에 속한 경우.
        ans++;//팀 수 +1.
        check[i]=true;//이미 팀에 속했음을 저장.
        for(int j=0; j<Friend[i].size(); j++){//친구 관계에 있는 학생들을 큐에 넣어서 bfs.
            check[Friend[i][j]]=true;
            queue<int> q;
            q.emplace(Friend[i][j]);
            while(!q.empty()){
                int st = q.front();
                q.pop();
                for(int k=0; k<Friend[st].size(); k++){
                    int nst = Friend[st][k];
                    if(check[nst]) continue;//이미 팀에 넣은 학생인 경우.
                    q.emplace(nst);
                    check[nst]=true;
                }
            }
        }
    }
    cout << ans;
    
    return 0;
}
