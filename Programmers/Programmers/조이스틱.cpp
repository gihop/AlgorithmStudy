#include <string>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

//처음 풀어보는 그리디 문제.
//조이스틱이 위치가 이동할 때 단방향으로만 이동할 줄 알았는데
//ㄴ다ABAAAAAAAAABBAA인 경우 바로 옆 B를 들렸다가 방향을 거꾸로 가야 최소 이동을 할 수 있다.

//name의 갯수에 맞게 초기 문자열을 설정한다.
string createStartString(int stringLength){
    string start = "";
    for(int i=0; i<stringLength; i++){
        start += "A";
    }
    
    return start;
}

//'A' 와 문자의 최소 거리를 구한다.
int minDistance(char s){
    int Min = s - 'A';
    Min = min('Z' - s + 1, Min);
    
    return Min;
}

//현재 위치에서 가장 가까운 거리에 있는 다른 문자의 위치와 거리를 찾는다.
pair<int,int> findNextPosition(string name, string start, int now){
    int nextA = now, distanceA = 0;
    while(true){
        if(start[nextA] != name[nextA])
            break;
        nextA++;
        distanceA++;
        if(nextA == name.size()) nextA = 0;
    }
    
    int distanceB = 0, nextB = now;
    while(true){
        if(start[nextB] != name[nextB])
            break;
        nextB--;
        distanceB++;
        if(nextB < 0) nextB = name.size() - 1;
    }
    if(distanceA <= distanceB) return make_pair(distanceA, nextA);
    else return make_pair(distanceB, nextB);
}

int solution(string name) {
    int answer = 0;
    
    string start = createStartString(name.size());
    int now = 0;
    while(true){
        answer += minDistance(name[now]);
        start[now] = name[now];
        int count, next;
        if(start == name) break;
        tie(count, next) = findNextPosition(name, start, now);
        now = next;
        answer += count;
    }
    
    return answer;
}
