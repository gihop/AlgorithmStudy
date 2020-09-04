#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

//https://programmers.co.kr/learn/courses/30/lessons/60062
//next_permutation을 사용하면 좀 더 쉽게 풀 수 있는 문제다.
//dist를 정렬시켜서 1,2,3,4로 만들어 놓고
//next_permutation을 사용하면 다음 순열을 반환한다.
//1,2,4,3 그 다음엔 1,3,2,4 ... 4,3,2,1까지 가고 다음 순열이 1,2,3,4인데
//다음 순열이 전 순열보다 작다면 false를 반환한다.
//아래 코드는 1,2,3,4에서 시작해서 다시 1,2,3,4가 되고 false를 반환하고 do while 문이 끝나기 때문에
//그 다음 for문이 계속 돌면서 1,2,3,4에서 시작한다.
//즉 dist의 모든 조합을 검사할 수 있다.

//다음으로 이 문제를 풀기 위해 필요한 개념은 원형 레스토랑을 일자로 생각을 하는 것이다.
//취약점의 위치가 1,5,6,10 일 때, dist의 원소를 겹치지 않게 해야 최소로 친구를 사용할 수 있다.
//각 원소 사이의 길이만 유지하면 되므로 weak의 원소를 5,6,10,13 으로 바꾼다.
//이런 방식으로 간격을 유지하면서 순서를 계속 바꾼다.
//바뀐 순서마다 dist를 next_permutation으로 만들 수 있는 친구들의 모든 조합에 대해 계산한다.

int solution(int n, vector<int> weak, vector<int> dist) {
    int answer = 987654321;
    
    sort(dist.begin(), dist.end());
    
    for(int i=0; i<weak.size(); i++){
        int tmp = weak[0]+n;
        for(int j=0; j<weak.size()-1; j++){
            weak[j] = weak[j+1];
        }
        weak[weak.size()-1] = tmp;
        
        do{
            int weakIdx = 0, distIdx = 0;
            
            //핵심인 부분.
            for(distIdx=0; distIdx<dist.size(); distIdx++){
                int next = weak[weakIdx] + dist[distIdx];//현재 가야할 취약점에서 현재 순서인 친구가 파견됐을 때 커버 가능한 위치.
                while(next >= weak[weakIdx]){//현재 가야할 취약점이 커버된다면
                    weakIdx++;//취약점을 다음 위치로 옮긴다.
                    if(weakIdx == weak.size()) break;//모든 취약점이 커버가 된경우.
                }
                if(weakIdx == weak.size()) break;//모든 취약점이 커버가 됐기 때문에 다음 친구를 파견할 필요가 없다.
            }
            if(weakIdx == weak.size()){
                //distIdx가 파견한 친구들의 숫자를 나타내기 때문.
                if(answer > distIdx+1) answer = distIdx+1;
            }
        }while(next_permutation(dist.begin(), dist.end()));
    }
    
    if(answer == 987654321) return -1;
    return answer;
}
