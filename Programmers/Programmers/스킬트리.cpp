#include <string>
#include <vector>
#include <map>
#include <tuple>

using namespace std;

//정리를 잘해야 하는 문제.

int solution(string skill, vector<string> skill_trees){
    int answer = 0;
    
    map<char,int> m;
    for(int i=0; i<skill.size(); i++)//맵에 스킬의 문자를 key, 순서를 value로 저장한다.
        m[skill[i]]=i;
    
    for(int i=0; i<skill_trees.size(); i++){
        bool success=true;
        int now=0;//n번째 스킬을 배울 차례의 뜻을 저장할 변수.
        for(int j=0; j<skill_trees[i].size(); j++){
            if(m.count(skill_trees[i][j])!=0 && now==m[skill_trees[i][j]])//스킬 순서에 해당되는 문자가 나왔을 때 현재 배워야 할 순서가 맞는지 검사.
                now++;
            else if(m.count(skill_trees[i][j])!=0 && now!=m[skill_trees[i][j]]){//현재 배워야 할 순서가 맞지 않는 경우.
                success=false;
                break;
            }
        }
        if(success) answer++;
    }
    
    return answer;
}
