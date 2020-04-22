#include <string>
#include <vector>
#include <map>
#include <sstream>

using namespace std;

vector<string> solution(vector<string> record) {
    vector<string> answer;
    
    map<string, string> m;
    vector<vector<string>> v(record.size(), vector<string>(0));
    string w;
    
    for(int i=0; i<record.size(); i++){
        for(stringstream sts(record[i]); (sts>>w);){
            v[i].push_back(w);
        }
    }
    for(int i=0; i<v.size(); i++){
        if(v[i][0]=="Enter" || v[i][0]=="Change"){
            m[v[i][1]]=v[i][2];
        }
    }
    for(int i=0; i<v.size(); i++){
        string result = m[v[i][1]];
        if(v[i][0]=="Enter"){
            result += "님이 들어왔습니다.";
            answer.push_back(result);
        }
        else if(v[i][0]=="Leave"){
            result += "님이 나갔습니다.";
            answer.push_back(result);
        }
    }
    
    return answer;
}
