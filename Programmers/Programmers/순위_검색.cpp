#include <string>
#include <vector>
#include <iostream>
#include <tuple>
#include <algorithm>

using namespace std;

// 사람들을 어떻게 효율적으로 나눠서 저장할지에 대한 방법을 생각해내기 정말 어려운 문제였다.
// 방법을 생각하기가 어려웠다.
// vector<string> group[4][3][3][3]에 각 사람의 점수를 모두 더하고
// vector의 0번째 인덱스에는 query 문의 '-'을 대응하기 위해 '-'가 나올 수 있는 모든 경우의 수에 모두 더해준다.

/*
 +++추가적인 방법으로 group의 원소들을 모두 오름차순으로 정렬 한 뒤에
 모든 원소들을 iteration 하지 않고 lower_bound 함수를 사용해서 약간 더 빠르게 찾을 수 있는 방법이 있다.
 호율성 case에서 평균적으로 230ms이 정도였는데 이 함수를 사용해서 평균 170ms으로 줄일 수 있었다.
 큰 폭으로 속도를 줄인 것은 아니지만 lower_bound 함수 혹은 upper_bound 함수를 잘 사용하면 좋을 것 같아서 추가한다.
 */

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
    
    
    for(int i=0; i<4; i++){
        for(int j=0; j<3; j++){
            for(int k=0; k<3; k++){
                for(int l=0; l<3; l++){
                    sort(group[i][j][k][l].begin(), group[i][j][k][l].end());
                }
            }
        }
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
        people_count += group[language][position][career][food].size() - (lower_bound(group[language][position][career][food].begin(), group[language][position][career][food].end(), score) - group[language][position][career][food].begin());
        answer.push_back(people_count);
    }
    
    return answer;
}

int main(){
    vector<string> infos = {"java backend junior pizza 150","python frontend senior chicken 210","python frontend senior chicken 150","cpp backend senior pizza 260","java backend junior chicken 80","python backend senior chicken 50"};
    vector<string> query  = {"java and backend and junior and pizza 100","python and frontend and senior and chicken 200","cpp and - and senior and pizza 250","- and backend and senior and - 150","- and - and - and chicken 100","- and - and - and - 150"};
    
    vector<int> answer;
    answer = solution(infos, query);
    
    for(int i=0; i<answer.size(); i++){
        cout << answer[i] <<" ";
    }
    
    return 0;
}
