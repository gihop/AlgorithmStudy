#include <string>
#include <vector>

using namespace std;

//처음 풀어보는 플로이드 와샬 알고리즘 문제.

int solution(int n, vector<vector<int>> results) {
    int answer = 0;
    
    vector<vector<bool>> graph(n+1, vector<bool>(n+1, false));
    
    for(int i=0; i<results.size(); i++)
        graph[results[i][0]][results[i][1]] = true;
    
    //플로이드 와샬 알고리즘은 각 정점을 경유해서 이동했을 때의 비용과 현재 비용을 비교하여
    //계속 갱신하는 것이기 때문에 i에 해당하는 정점들이 경유 정점이어야 한다.
    //따라서 if문처럼 j -> i -> k로 갈 수 있는지 확인한다.
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            for(int k=1; k<=n; k++){
                if(graph[j][i] && graph[i][k]) graph[i][k] = true;
            }
        }
    }
    
    for(int i=1; i<=n; i++){
        int count = 0;
        for(int j=1; j<=n; j++){
            if(graph[i][j] || graph[j][i]) count++;
        }
        if(count == n-1) answer++;
    }
    
    return answer;
}
