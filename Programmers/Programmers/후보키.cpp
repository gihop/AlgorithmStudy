#include <string>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

//처음에 go함수를 작성하지 않고 for문으로 combination을 만들었는데
//모든 경우의 수가 들어가지 않았고, 이를 못 알아채서 문제 푸는데 계속 해맸다.

//처음에 dfs로 후보키 여부를 판단했는데 이렇게 하면 틀린다.
//후보키인지 검사할 col이 4개라면 오름차순 순서로 검사를 해야되기 때문이다.
//0,1,2,3,4,01,02,03,04,12....이런식으로 해야한다.
//dfs로 하면 0,01,012,0123,01234,0124...이런식이라서 틀린다.

//go 함수로 0,1,2,3,4...의 조합 벡터를 만들고 sort해서 정렬한다.

//"01"이 후보키가 된다면 "01"이 포함된 뒷순서의 원소들을 모두 삭제해야 한다.
//이 때 "04"가 "01234"에 포함되는지 검사하려면
//str1.find("0") == string::npos
//str1.find("4") == string::npos를 써서 검사할 수 있다. 0,4 따로 해야한다.
//"04"로 하면 "014"는 검사되지 않기 때문.
//find는 찾으면 해당 위치를 반환하는데 string::npos는 상수로 검사되지 않았을 때의 숫자다.

//다른 방법으로 include(str1.begin(), str1.end(), str2.begin(), str2.end());
//를 사용할 수 있다. 이렇게 하면 부분 집합을 한번에 검사해준다.

vector<string> combination;

bool compare(const string &a, const string &b){
    if(a.size() < b.size()) return true;
    else if(a.size() == b.size()){
        if(a < b) return true;
    }
    return false;
}

bool isCandidate(vector<vector<string>> relation, string combination){
    set<string> s;
    
    for(int i=0; i<relation.size(); i++){
        string st = "";
        for(int j=0; j<combination.size(); j++){
            st += relation[i][combination[j] - '0'] + " ";
        }
        if(s.count(st) == 0) s.insert(st);
        else return false;
    }
    return true;
}

void go(string now, int idx, int count, int size){
    if(count > 0){
        combination.push_back(now);
    }
    for(int i=idx+1; i<size; i++){
        now += to_string(i);
        go(now, i, count+1, size);
        now.pop_back();
    }
}

int solution(vector<vector<string>> relation) {
    int answer = 0;
    
    go("", -1, 0, relation[0].size());
    
    sort(combination.begin(), combination.end(), compare);
    
    for(int i=0; i<combination.size(); i++){
        if(isCandidate(relation, combination[i])){
            answer++;
            for(int j=i+1; j<combination.size(); j++){
                if(includes(combination[j].begin(), combination[j].end(), combination[i].begin(), combination[i].end())){
                    combination.erase(combination.begin()+j);
                    j--;
                }
            }
            
        }
    }
    
    return answer;
}
