#include <string>
#include <vector>
#include <algorithm>
#include <tuple>
#include <iostream>

using namespace std;

//문제를 풀긴 했지만 문제 해석을 잘못 해서 해맸었다.
//약간의 오해의 소지가 있다.
//문제의 "음악이 00:00를 넘겨서까지 재생되는 일은 없다."를 나는
//끝나는 시간이 00:00까지 가능하다고 이해했는데 그래서 주석된 부분을 넣어준 것이었고,
//또한 음악의 재생되는 시간이 1이상이라고 생각했다.

//compare에서 if(aTime > bTime) return true;의 부등호를 반대로 하면 어느 부분이 틀리고
//또 반대로 하면 다른 부분이 틀렸었다.

//결론적으로 그 것의 이유는 문제의 테스트케이스에 음악이 재생되는 시간이 0인 부분이 있었다.
//즉 00:00,00:00이여서 runningTime의 계산에 오류가 있었던 것이었고,
//시작한 시간에서 다음날 00:00로 넘어가는 테스트 케이스는 없었다.
//즉 23:56,00:00은 불가능했다. 00:00, 00:00은 같은날이여서 가능했다.

bool compare(const tuple<int,int,string> &a, const tuple<int,int,string> &b){
    int aTime, aIndex, bTime, bIndex;
    string aName, bName;
    tie(aTime, aIndex, aName) = a;
    tie(bTime, bIndex, bName) = b;
    if(aTime > bTime) return true;
    else if(aTime == bTime)
        if(aIndex < bIndex) return true;
    return false;
}

int calculateRunningTime(int startHour, int startMin, int endHour, int endMin){
    int runningTime = 0;
    // if(endHour == 0 && endMin == 0) endHour = 24; 바로 이 부분.
    if(endMin >= startMin) runningTime += endMin - startMin;
    else{
        runningTime += 60 + endMin - startMin;
        endHour--;
    }
    runningTime += (endHour-startHour) * 60;
    
    return runningTime;
}

string solution(string m, vector<string> musicinfos) {
    string answer = "";
    vector<tuple<int,int,string>> answers;
    
    vector<string> M;
    for(int i=0; i<m.size(); i++){
        if(i != m.size()-1 && m[i+1] == '#'){
            M.push_back(m.substr(i,2));
            i++;
        }
        else M.push_back(m.substr(i,1));
    }
    
    for(int i=0; i<musicinfos.size(); i++){
        int startHour = stoi(musicinfos[i].substr(0,2)), startMin = stoi(musicinfos[i].substr(3,2)), endHour = stoi(musicinfos[i].substr(6,2)), endMin = stoi(musicinfos[i].substr(9,2));
        
        int runningTime = calculateRunningTime(startHour, startMin, endHour, endMin);
        
        string tmp = musicinfos[i].substr(12, musicinfos[i].size()-12);
        size_t comma = tmp.find(",");
        string name = tmp.substr(0, comma);
        string melody = tmp.substr(comma+1, tmp.size()-comma);
        
        vector<string> melodies;
        for(int j=0; j<melody.size(); j++){
            if(j != melody.size()-1 && melody[j+1] == '#'){
                melodies.push_back(melody.substr(j,2));
                j++;
            }
            else melodies.push_back(melody.substr(j,1));
        }
        
        vector<string> heard;
        for(int j=0, k=0; j<runningTime; j++, k++){
            if(k == melodies.size()) k = 0;
            heard.push_back(melodies[k]);
        }

        if(heard.size() >= M.size()){
            bool success = false;
            for(int j=0; j<=heard.size()-M.size(); j++){
                success = true;
                for(int k=0; k<M.size(); k++){
                    if(heard[j+k] != M[k]){
                        success = false;
                        break;
                    }
                }
                if(success) break;
            }
            if(success)
                answers.push_back(make_tuple(runningTime, i, name));
        }
    }
    if(answers.size() == 0) answer = "(None)";
    else {
        sort(answers.begin(), answers.end(), compare);
        int tmpTime, tmpIndex;
        tie(tmpTime, tmpIndex, answer) = answers[0];
    }
    
    return answer;
}
