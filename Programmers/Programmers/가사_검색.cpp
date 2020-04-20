#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

vector<int> solution(vector<string> words, vector<string> queries) {
    vector<int> answer;
    map<string,int> m;
    
    for(int i=0; i<words.size(); i++){
        string s(words[i].size(), '?');
        if(m.count(s)==0) m[s]=1;
        else m[s]++;
        
        for(int j=0; j<words[i].size()-1; j++){
            s[j]=words[i][j];
            if(m.count(s)==0) m[s]=1;
            else m[s]++;
        }
        string s2(words[i].size(), '?');
        for(int j=words[i].size()-1; j>=1; j--){
            s2[j]=words[i][j];
            if(m.count(s2)==0) m[s2]=1;
            else m[s2]++;
        }
    }
    
    for(int i=0; i<queries.size(); i++){
        if(m.count(queries[i])==0) answer.push_back(0);
        else answer.push_back(m[queries[i]]);
    }
    
    return answer;
}
