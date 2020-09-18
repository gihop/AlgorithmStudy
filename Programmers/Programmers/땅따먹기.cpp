#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>

using namespace std;

//처음에 bfs+dp로 풀었는데 효율성에서 시간초과가 나왔다.
//q에 최대가 아닌 원소도 들어가기 때문이다.
//때로는 이렇게 for문으로 푸는게 더 빠를 수도 있다.

//land에
//1 6 3 7
//4 2 8 5
//이 있고

//처음 visited에
//1 6 3 7
//0 0 0 0
//순서로 있을 때
//(1,0)번 원소에 들어갈 값은 visited[0]의 원소중에 가장 큰 값과 land[1][0]인 4와 합한 수가 들어간다.
//이렇게 하면 항상 다음 원소에 갈 때 가장 큰값만 가지고 갈 수 있다.


int solution(vector<vector<int> > land)
{
    int answer = 0;
    
    vector<vector<int>> visited(land.size(), vector<int>(4, 0));
    
    visited[0][0] = land[0][0];
    visited[0][1] = land[0][1];
    visited[0][2] = land[0][2];
    visited[0][3] = land[0][3];
    
    for(int i=1; i<visited.size(); i++){
        for(int j=0; j<4; j++){
            int next = 0;
            int idx = 0;
            for(int k=0; k<4; k++){
                if(j == k) continue;
                if(visited[i-1][k] > next){
                    next = visited[i-1][k];
                    idx = k;
                }
            }
            visited[i][j] = visited[i-1][idx] + land[i][j];
        }
    }
    answer = *max_element(visited[land.size()-1].begin(), visited[land.size()-1].end());
    
    return answer;
}

//#include <iostream>
//#include <vector>
//#include <queue>
//#include <tuple>
//#include <algorithm>
//
//using namespace std;
//
//int solution(vector<vector<int> > land)
//{
//    int answer = 0;
//    queue<tuple<int,int,int>> q;
//    q.emplace(0, 0, land[0][0]);
//    q.emplace(0, 1, land[0][1]);
//    q.emplace(0, 2, land[0][2]);
//    q.emplace(0, 3, land[0][3]);
//
//    while(!q.empty()){
//        int x, y, count;
//        tie(x,y,count) = q.front();
//        q.pop();
//         if(x == land.size()-1){
//             if(answer < count) answer = count;
//             continue;
//         }
//         for(int i=0; i<4; i++){
//             if(y == i) continue;
//             if(visited[x+1][i] >= count+land[x+1][i]) continue;
//             visited[x+1][i] = count + land[x+1][i];
//             q.emplace(x+1, i, count + land[x+1][i]);
//         }
//     }
//    for(int i=0; i<visited.size(); i++){
//         for(int j=0; j<4; j++){
//             cout << visited[i][j] << " ";
//         }
//         cout << endl;
//    }
//
//
//    return answer;
//}
