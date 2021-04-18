#include <string>
#include <vector>
#include <tuple>
#include <map>
#include <algorithm>

using namespace std;

// 뭔가 이전에 풀었을 때보다 복잡하게 푼 것 같다.

bool compare(pair<int,string> const &a, pair<int,string> const &b){
    if(a.first > b.first) return true;
    else return false;
}

vector<int> solution(vector<string> genres, vector<int> plays) {
    vector<int> answer;
    
    map<string,tuple<int,int,int,int>> best;
    map<string,int> genres_map;
    vector<pair<int,string>> sum;
    int count = 0;
    for(int i=0; i<genres.size(); i++){
        if(genres_map.count(genres[i]) > 0){
            sum[genres_map[genres[i]]].first += plays[i];
        }
        else{
            genres_map[genres[i]] = count++;
            sum.push_back(make_pair(plays[i], genres[i]));
        }
        if(best.count(genres[i]) > 0){
            int one_play, one_index, two_play, two_index;
            tie(one_play, one_index, two_play, two_index) = best[genres[i]];
            if(one_play < plays[i]){
                best[genres[i]] = make_tuple(plays[i], i, one_play, one_index);
            }
            else if(two_play < plays[i]){
                best[genres[i]] = make_tuple(one_play, one_index, plays[i], i);
            }
        }
        else{
            best[genres[i]] = make_tuple(plays[i], i, -1, -1);
        }
    }
    
    sort(sum.begin(), sum.end(), compare);
    
    for(int i=0; i<sum.size(); i++){
        int one_play, one_index, two_play, two_index;
        tie(one_play, one_index, two_play, two_index) = best[sum[i].second];
        answer.push_back(one_index);
        if(two_index != -1) answer.push_back(two_index);
    }
    
    return answer;
}
