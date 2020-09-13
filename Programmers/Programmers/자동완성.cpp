#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

using namespace std;

//밑에 map으로 풀었던 문제는 생각하기도 쉽지만 역시 시간초과가 발생한다.
//단어들을 정렬해서 두 개씩 비교해서 풀었다.

//하루종일 시험보고 푸는 알고리즘 문제.
//시험이 아니니깐 잘풀린다~

int solution(vector<string> words) {
    int answer = 0;
    
    sort(words.begin(), words.end());
    
    //이전 단어와 같았던 부분을 저장한다.
    string word = "";
    for(int i=0; i<words.size()-1; i++){
        if(word == ""){//이전 단어와 같았던 부분이 없는 경우.
            for(int j=0; j<words[i].size(); j++){
                //같은 부분을 저장한다.
                if(words[i][j] == words[i+1][j]) word += words[i][j];
                else{
                    //같은 부분이 끝났경우 예를 들어
                    //abacde, abadcde의 같은 부분은 "aba", abac를 검색하려면 같은 부분의 +1 만큼 더해야 하기 때문에 answer++
                    answer++;
                    break;
                }
            }
            answer+=word.size();//같은 부분만큼 더해준다.
        }
        else{//이전 단어와 같은 부분이 있었던 경우.
            //다음 단어 역시 같은 부분을 공유하는 경우.
            if(words[i+1].size() >= word.size() && words[i+1].substr(0,word.size()) == word){
                //같은 단어 다음 부분부터 검사해서 같은 부분을 확장한다.
                for(int j=word.size(); j<words[i].size(); j++){
                    if(words[i][j] == words[i+1][j]) word += words[i][j];
                    else{
                        //역시 abadcde abadzzz, 같은 부분 abad의 +1 (abadc)까지 검색해야하기 때문에 answer++
                        answer++;
                        break;
                    }
                }
                answer += word.size();
            }
            else{//다음 단어가 같은 부분을 공유하지 않는 경우.
                //abc, abcd, abzzz인 경우, abcd는 같은 부분 abc+1 까지 더해준다.
                answer+=word.size()+1;
                word = "";//같은 부분을 초기화 해주고 다시 같은 부분을 찾는다.
                for(int j=0; j<words[i].size(); j++){
                    if(words[i][j] == words[i+1][j]) word += words[i][j];
                    else break;
                }
            }
        }
    }
    //마지막 단어 역시 이전 단어와 같은 부분 +1로 더해준다.
    answer += word.size()+1;
    
    return answer;
}

//int solution(vector<string> words) {
//    int answer = 0;
//
//    map<string,int> wordMap;
//
//    for(int i=0; i<words.size(); i++){
//        string word = "";
//        for(int j=0; j<words[i].size(); j++){
//            word += words[i][j];
//            if(wordMap.count(word) == 0) wordMap[word] = 1;
//            else wordMap[word] += 1;
//        }
//    }
//
//    for(int i=0; i<words.size(); i++){
//        string word = "";
//        for(int j=0; j<words[i].size(); j++){
//            answer++;
//            word += words[i][j];
//            if(wordMap[word] == 1) break;
//        }
//    }
//
//    return answer;
//}
