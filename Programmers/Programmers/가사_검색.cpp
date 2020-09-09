#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//가사 검색 문제 재도전.
//이전에는 효율성을 다 통과하지 못했다.
//효율성을 통과하기 위해 트라이로 푸는 법이 있고 이분 탐색하는 법이 있는데
//어떻게 할지 몰라서 답을 찾아봤고 아이디어가 정말 기가 막혔다.
//문제 푸는 방법을 잘 익혀두자.

//먼저 이분탐색을 진행하기 위해 words를 정렬해야 한다.
//정렬기준은 글자수 오름차순으로 정렬하고, 글자수가 같다면 사전순으로 정렬한다.
//lower_bound는 key 값의 이상이 처음 나올때 위치를 반환하고, upper_bound는 key 값이 처음 초과하는 위치를 반환한다.
//즉 예를 aaaa, bbbb, cccc가 있을 때 bbbb를 lower_bound하면 bbbb의 iterator, upper_bound는 cccc의 iterator를 반환한다.
//이를 이용해서 bb??가 쿼리라면 bbaa를 lower_bound하고, bbzz를 upper_bound해서 이를 빼주면 몇개가 맞는지를 알 수 있다.

//하지만 쿼리가 ??bb인 경우, 이를 reverse 해줘야 한다.
//words의 모든 원소들도 reverse된 상태에서 다시 정렬해줘야 하기 때문에 rwords를 만든다.

//추가적으로 처음 알게된 함수인데 string.find_first_of('a')를 하면 string 안에 처음 나온 a의 원소의 위치를 반환해준다.

bool compare(const string &a, const string &b){
    if(a.size() < b.size()) return true;
    else if(a.size() == b.size())
        if(a < b) return true;
    
    return false;
}

vector<int> solution(vector<string> words, vector<string> queries) {
    vector<int> answer;
    
    sort(words.begin(), words.end(), compare);
    
    vector<string> rwords = words;
    
    for(int i=0; i<rwords.size(); i++){
        reverse(rwords[i].begin(), rwords[i].end());
    }
    
    sort(rwords.begin(), rwords.end(), compare);
    
    int idx;
    int start, end;
    for(int i=0; i<queries.size(); i++){
        if(queries[i][0] == '?'){
            reverse(queries[i].begin(), queries[i].end());
            idx = queries[i].find_first_of('?');
            
            for(int j=idx; j<queries[i].size(); j++) queries[i][j] = 'a';
            start = lower_bound(rwords.begin(), rwords.end(), queries[i], compare) - rwords.begin();
            
            for(int j=idx; j<queries[i].size(); j++) queries[i][j] = 'z';                   end = upper_bound(rwords.begin(), rwords.end(), queries[i], compare) - rwords.begin();
        }
        else{
            idx = queries[i].find_first_of('?');
            
            for(int j=idx; j<queries[i].size(); j++) queries[i][j] = 'a';
            start = lower_bound(words.begin(), words.end(), queries[i], compare) - words.begin();
            
            for(int j=idx; j<queries[i].size(); j++) queries[i][j] = 'z';                   end = upper_bound(words.begin(), words.end(), queries[i], compare) - words.begin();
        }
        
        answer.push_back(end - start);
    }
    
    return answer;
}

//vector<int> solution(vector<string> words, vector<string> queries) {
//    vector<int> answer;
//    map<string,int> m;
//
//    for(int i=0; i<words.size(); i++){
//        string s(words[i].size(), '?');
//        if(m.count(s)==0) m[s]=1;
//        else m[s]++;
//
//        for(int j=0; j<words[i].size()-1; j++){
//            s[j]=words[i][j];
//            if(m.count(s)==0) m[s]=1;
//            else m[s]++;
//        }
//        string s2(words[i].size(), '?');
//        for(int j=words[i].size()-1; j>=1; j--){
//            s2[j]=words[i][j];
//            if(m.count(s2)==0) m[s2]=1;
//            else m[s2]++;
//        }
//    }
//
//    for(int i=0; i<queries.size(); i++){
//        if(m.count(queries[i])==0) answer.push_back(0);
//        else answer.push_back(m[queries[i]]);
//    }
//
//    return answer;
//}
