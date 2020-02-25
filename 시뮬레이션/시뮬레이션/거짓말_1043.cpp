//
//  거짓말_1043.cpp
//  시뮬레이션
//
//  Created by jiho park on 2020/02/24.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <vector>
#include <queue>

#define endl "\n"
using namespace std;

//문제를 잘못 이해했었다. 그래프 탐색이 필요하다. bfs로 해결했다.
//파티의 순서에 상관없이 거짓말을 할 수 있는 최대 파티의 수를 구해야 한다.
//진실을 알고 있는 사람 기준으로 해야한다.
//진실을 알고 있는 사람을 큐에 넣고 그들과 같은 파티에 해당하는 사람들을 큐에 넣으면서 truth배열에 1을 표시했다.
//최종에서 truth 배열에서 1을 갖고 있는 사람이 파티에 있으면 진실을 말해야 하고 없으면 거짓을 말할 수 있다.

int n,m;
int truth[51];
int ans;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> n >> m;
    
    int truth_people;
    cin >> truth_people;
    queue<int> q;
    for(int i=0; i<truth_people; i++){
        int num;
        cin >> num;
        truth[num]=1;//진실을 말해줘야 하는 사람이라는 뜻.
        q.emplace(num);//진실을 말해야하는 사람은 큐에 넣는다.
    }
    
    vector<int> v[51];//1번부터 M 번 파티까지 누가 오는지 저장하는 벡터.
    vector<int> a[51];//1번부터 N 번 사람이 몇번 파티에 가는지 저장하는 벡터.
    for(int i=1; i<=m; i++){
        int num;
        cin >> num;
        for(int j=0; j<num; j++){
            int invited;
            cin >> invited;
            v[i].push_back(invited);
            a[invited].push_back(i);
        }
    }
    
    while(!q.empty()){
        int x = q.front();//진실을 말해야줘야 하는 사람.
        q.pop();
        for(int i=0; i<a[x].size(); i++){//x가 속한 파티를 검사.
            int party=a[x][i];
            for(int j=0; j<v[party].size(); j++){//x가 속한 파티에 누가 있는지 검사.
                int nx = v[party][j];
                if(truth[nx]==1) continue;//이미 진실을 말해줘야하는 사람인 경우.
                truth[nx]=1;
                q.emplace(nx);
            }
        }
    }
    
    for(int i=1; i<=m; i++){
        bool check=true;
        for(int j=0; j<v[i].size(); j++){
            if(truth[v[i][j]] == 1){//진실을 말해줘야하는 사람인 경우.
                check=false;
                break;
            }
        }
        if(check)//파티에 진실을 말해줘야하는 사람이 없는 경우.
            ans++;
    }
    cout << ans;
    
    return 0;
}

