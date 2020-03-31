#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

bool a[201];

int solution(int n, vector<vector<int>> computers) {
    int answer = 0;
    
    for(int i=0; i<n; i++){
        cout << i << endl;
        if(a[i]) continue;
        a[i]=true;
        answer++;
        queue<int> q;
        q.emplace(i);
        while(!q.empty()){
            int now = q.front();
            cout << now << endl;
            q.pop();
            for(int i=0; i<computers[now].size(); i++){
                int next = computers[now][i];
                if(!next) continue;
                if(a[i])continue;
                q.emplace(i);
                a[i]=true;
            }
        }
    }
    
    return answer;
}
