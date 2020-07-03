#include <vector>
#include <tuple>
#include <queue>
#include <cstring>

using namespace std;

//무난한 bfs 문제.

vector<int> solution(int m, int n, vector<vector<int>> picture) {
    int number_of_area = 0;
    int max_size_of_one_area = 0;
    
    int dx[]={0, 1, 0, -1};
    int dy[]={1, 0, -1, 0};
    
    bool visited[m][n];
    memset(visited, 0, sizeof(visited));
    
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            if(picture[i][j]==0) continue;
            if(visited[i][j]) continue;
            number_of_area++;
            visited[i][j]=true;
            int area=1;
            queue<tuple<int,int,int>> q;
            q.emplace(i,j,picture[i][j]);
            while(!q.empty()){
                int x,y,color;
                tie(x,y,color) = q.front();
                q.pop();
                for(int k=0; k<4; k++){
                    int nx=x+dx[k];
                    int ny=y+dy[k];
                    if(nx<0 || nx>=m || ny<0 || ny>=n) continue;
                    if(visited[nx][ny]) continue;
                    if(picture[nx][ny]==color){
                        q.emplace(nx,ny,color);
                        visited[nx][ny]=true;
                        area++;
                    }
                }
            }
            if(max_size_of_one_area<area) max_size_of_one_area=area;
        }
    }
    
    vector<int> answer(2);
    answer[0] = number_of_area;
    answer[1] = max_size_of_one_area;
    return answer;
}
