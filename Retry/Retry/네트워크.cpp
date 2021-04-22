#include <string>
#include <vector>
#include <queue>
using namespace std;

int solution(int n, vector<vector<int>> computers) {
    int answer = 0;
    
    vector<int> visited(n, false);
    
    for(int i=0; i<n; i++){
        if(visited[i]) continue;
        queue<int> q;
        q.emplace(i);
        visited[i] = true;
        answer+=1;
        while(!q.empty()){
            int now = q.front();
            q.pop();
            for(int j=0; j<computers[now].size(); j++){
                if(computers[now][j] == 0 || visited[j]) continue;
                visited[j] = true;
                q.emplace(j);
            }
        }
    }
    
    return answer;
}
