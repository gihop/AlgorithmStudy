#include <string>
#include <vector>
#include <iostream>
#include <tuple>

using namespace std;

// 사람들을 어떻게 효율적으로 나눠서 저장할지에 대한 방법을 생각해내기 정말 어려운 문제였다.
// 방법을 생각하기가 어려웠다.
// vector<string> group[4][3][3][3]에 각 사람의 점수를 모두 더하고
// vector의 0번째 인덱스에는 query 문의 '-'을 대응하기 위해 '-'가 나올 수 있는 모든 경우의 수에 모두 더해준다.

tuple<int,int,int,int> find_group(vector<string> substring){
    int language, position, career, food;
    if(substring[0] == "-")
        language = 0;
    else if(substring[0] == "cpp")
        language = 1;
    else if(substring[0] == "java")
        language = 2;
    else
        language = 3;

    if(substring[1] == "-")
        position = 0;
    else if(substring[1] == "backend")
        position = 1;
    else
        position = 2;

    if(substring[2] == "-")
        career = 0;
    else if(substring[2] == "junior")
        career = 1;
    else
        career = 2;

    if(substring[3] == "-")
        food = 0;
    else if(substring[3] == "chicken")
        food = 1;
    else
        food = 2;
    
    return make_tuple(language, position, career, food);
}

vector<int> solution(vector<string> info, vector<string> query) {
    vector<int> answer;
    vector<int> group[4][3][3][3];
    
    for(int i=0; i<info.size(); i++){
        int current = info[i].find(' ');
        int count = 0;
        int language = 0, position = 0, career = 0, food = 0, score = 0;
        vector<string> split;
        while(current != string::npos){
            string substring = info[i].substr(0, current);
            split.push_back(substring);
            info[i] = info[i].substr(current+1, info[i].size());
            current = info[i].find(' ');
            if(current == string::npos)
                score = stoi(info[i]);
            count++;
        }
        tie(language, position, career, food) = find_group(split);
        group[language][position][career][food].push_back(score);
        group[0][position][career][food].push_back(score);
        group[language][0][career][food].push_back(score);
        group[language][position][0][food].push_back(score);
        group[language][position][career][0].push_back(score);
        group[0][0][career][food].push_back(score);
        group[0][position][0][food].push_back(score);
        group[0][position][career][0].push_back(score);
        group[language][0][0][food].push_back(score);
        group[language][0][career][0].push_back(score);
        group[language][position][0][0].push_back(score);
        group[0][0][0][food].push_back(score);
        group[0][0][career][0].push_back(score);
        group[0][position][0][0].push_back(score);
        group[language][0][0][0].push_back(score);
        group[0][0][0][0].push_back(score);
    }
    
    for(int i=0; i<query.size(); i++){
        int current = query[i].find(' ');
        int count = 0;
        int language = 0, position = 0, career = 0, food = 0, score = 0;
        vector<string> split;
        while(current != string::npos){
            string substring = query[i].substr(0, current);
            if(substring != "and")
                split.push_back(substring);
            query[i] = query[i].substr(current+1, query[i].size());
            current = query[i].find(' ');
            if(current == string::npos)
                score = stoi(query[i]);
            count++;
        }
        tie(language, position, career, food) = find_group(split);
        int people_count = 0;
        for(int j=0; j<group[language][position][career][food].size(); j++){
            if(group[language][position][career][food][j] >= score)
                people_count++;
        }
        answer.push_back(people_count);
    }
    
    return answer;
}
