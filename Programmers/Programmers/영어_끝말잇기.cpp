#include <string>
#include <vector>
#include <iostream>
#include <set>

using namespace std;

vector<int> solution(int n, vector<string> words) {
    vector<int> answer;
    vector<int> persons(n, 0);
    set<string> s;
    int person = 1;
    char nextWord = words[0][0];
    
    for(int i=0; i<words.size(); i++){
        persons[person-1]++;
        if(words[i][0] == nextWord && s.count(words[i]) == 0){
            s.insert(words[i]);
            person++;
            nextWord = words[i][words[i].size()-1];
            if(person > n) person = 1;
        }
        else{
            answer.push_back(person);
            answer.push_back(persons[person-1]);
            break;
        }
    }
    if(answer.size() == 0){
        answer.push_back(0);
        answer.push_back(0);
    }
    
    return answer;
}
