//
//  텀_프로젝트_9466.cpp
//  DFS
//
//  Created by jiho park on 2020/02/29.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cstring>

#define endl "\n"
using namespace std;

//시간초과의 극치.
//정말 최적화를 잘해줘야함.
//dfs 순회해서 팀을 만들 수 있는 조건이 되었을 때 경로내에 있는 모든 정점들을 이미 팀에 속한 정점으로 표시를 해두어서 이미 팀에 속한 정점을 다시 dfs 순회가 일어나지 않도록 해줘야한다.
//dfs 순회를 하다가 팀 생성 조건에 맞지 않았을 때 시작점인 정점을 표시를 해둬서 다음 dfs에서 이 정점으로 오면 바로 팀 생성을 실패할 수 있게 해줘야 한다.
//위에 까지 했을 때
//테스트케이스가 1 1 2 3 4 5 6인 경우 1은 1 자기 자신을 원하니 팀 생성 성공하고, 그 다음 2는 1을 팀원으로 원하기 때문에 if(check[num])에서 실패한다. 위에 경우에 따라 2를 실패인 수로 finished[start]=-1 저장을 해놓고, 3이 2를 팀원으로 원할 때 바로 실패로 넘어가게 되면 finished[num]!=0에서 걸려서 return team을 하게 되는데 이 부분에서 다시 finished[start]=-1로 3을 저장해줘야 한다. 그렇지 않으면 4에서 3을 원할 때, 5에서 4를 원할 때, 계속 dfs 순회를 돌게 된다. 이 부분 때문에 시간초과가 발생했다.

int tc;
int n;
int selected[100001];
bool check[100001];
int finished[100001];
int ans;
vector<int> v;

bool dfs(int n, int start){
    int num = selected[n];
    bool team=false;
    if(finished[num]!=0) {//실패 표시된 정점에 다다른 경우.
        finished[start]=-1;//이 곳 시작점 역시 표시를 해둬야한다.
        return team;
    }
    if(check[num]){//dfs 순회하다가 팀 생성 조건에 맞지 않는 경우.
        finished[start]=-1;//시작점을 표시해둔다.
        return team;
    }
    
    if(num == start){//팀 생성에 성공한 경우.
        team=true;
        v.push_back(start);//시작점 포함.
        for(int i=0; i<v.size(); i++){//팀 생성 성공된 숫자로 표시한다.
            finished[v[i]]=1;
        }
        return team;
    }
    check[num]=true;
    v.push_back(num);
    team = dfs(num, start);
    check[num]=false;//백트래킹 부분. dfs 순회를 시작할 때 시작점은 false이기 때문에 시작점이 아닌 정점인데 이미 방문한 곳이라면 팀을 생성할 수 없다.
    return team;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> tc;
    
    while(tc--){
        memset(finished, 0, sizeof(finished));
        cin >> n;
        for(int i=1; i<=n; i++)
            cin >> selected[i];
        for(int i=1; i<=n; i++){
            v.clear();//벡터는 계속 비워줘야 한다.
            if(finished[i]==1) continue;//이미 팀으로 생성된 정점인 경우.
            if(!dfs(i,i)) ans++;//팀 생성하지 못한 경우 ans+1.
        }
        cout << ans << endl;
        ans = 0;
    }
    
    return 0;
}

