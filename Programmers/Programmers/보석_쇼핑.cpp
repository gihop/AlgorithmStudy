#include <string>
#include <vector>
#include <set>
#include <map>

using namespace std;

//투포인터 문제.

vector<int> solution(vector<string> gems) {
    vector<int> answer;
    int answerStart, answerEnd, answerDistance;
    
    set<string> set;
    for(int i=0; i<gems.size(); i++)
        set.insert(gems[i]);
    
    //맵은 구간내에 갖고 있는 보석의 종류와 갯수를 의미한다.
    map<string, int> map;
    
    //처음 위치의 보석을 갖고 시작한다.
    map[gems[0]] = 1;
    int gemSize = set.size();
    int start = 0, end = 0;
    bool first = true;
    while(true){
        //first를 이용해서 모든 종류의 보석을 모두 가질 때 까지 end를 증가시킨다.
        if(first && map.size() < gemSize){
            end++;
            if(map.count(gems[end]) == 0) map[gems[end]] = 1;
            else map[gems[end]] += 1;
        }
        else if(first && map.size() == gemSize) {
            first = false;
            answerStart = start;
            answerEnd = end;
            answerDistance = end - start;
        }
        
        //모든 종류의 보석을 가진 뒤에는 계속해서 모든 종류의 보석을 갖고 있는 상태를 유지한다.
        //start 위치의 보석을 2개 이상 갖고 있다면 start를 증가시킨다.
        //그렇지 않다면 end를 증가시킨다.
        //start 위치의 보석이 한 개이고, end가 끝에 위치한다면 탐색을 종료한다.
        if(!first){
            if(map[gems[start]] > 1){
                map[gems[start]] -= 1;
                start++;
                if(end - start < answerDistance){
                    answerStart = start;
                    answerEnd = end;
                    answerDistance = end - start;
                }
            }
            else if(end == gems.size()-1) break;
            else{
                end++;
                map[gems[end]] += 1;
            }
        }
    }
    answer.push_back(answerStart+1);
    answer.push_back(answerEnd+1);
    
    return answer;
}
