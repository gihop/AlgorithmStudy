#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <iostream>

using namespace std;

bool compare(const pair<string,int> &a, const pair<string,int> &b){
    return a.second > b.second;
}

vector<int> solution(vector<string> genres, vector<int> plays) {
    vector<int> answer;
    
    vector<pair<string,int>> v;
    map<string,int> m;
    for(int i=0; i<genres.size(); i++){
        m[genres[i]]+=plays[i];
    }
    for(map<string,int>::iterator iter=m.begin(); iter!=m.end(); iter++)
        v.push_back(make_pair(iter->first,iter->second));
    
    sort(v.begin(), v.end(), compare);
    
    for(int i=0; i<v.size(); i++){
        int first_play=0, second_play=0, first_num, second_num;
        for(int j=0; j<genres.size(); j++){
            if(genres[j]==v[i].first){
                if(first_play<plays[j]){
                    second_play = first_play;//이 부분을 추가 해야함.
                    second_num = first_num;
                    first_play = plays[j];
                    first_num = j;
                }else if(second_play<plays[j]){
                    second_play = plays[j];
                    second_num = j;
                }
            }
        }
        answer.push_back(first_num);
        if(second_play>0) answer.push_back(second_num);
    }
    
    return answer;
}
