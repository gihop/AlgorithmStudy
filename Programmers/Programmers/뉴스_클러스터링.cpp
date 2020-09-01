#include <string>
#include <map>
#include <algorithm>

using namespace std;

int solution(string str1, string str2) {
    int answer = 0;
    
    map<string, int> mapA, mapB;
    
    for(int i=0; i<str1.size()-1; i++){
        //문자열을 2문자 단위로 자른다.
        string s = str1.substr(i, 2);
        
        //2문자가 모두 영어로 이루어져 있는지 검사하고, 대문자는 모두 소문자로 변환한다.
        if(((s[0] >= 'A' && s[0] <= 'Z') || (s[0] >= 'a' && s[0] <= 'z')) &&
           ((s[1] >= 'A' && s[1] <= 'Z') || (s[1] >= 'a' && s[1] <= 'z'))){
            if(s[0] >= 'A' && s[0] <='Z') s[0] = s[0] - 'A' + 'a';
            if(s[1] >= 'A' && s[1] <='Z') s[1] = s[1] - 'A' + 'a';
            
            //map에 없다면 값을 1로 설정하고, 있다면 1을 더한다.
            if(mapA.count(s) > 0) mapA[s] += 1;
            else mapA[s] = 1;
        }
    }
    
    for(int i=0; i<str2.size()-1; i++){
        string s = str2.substr(i, 2);
        if(((s[0] >= 'A' && s[0] <= 'Z') || (s[0] >= 'a' && s[0] <= 'z')) &&
           ((s[1] >= 'A' && s[1] <= 'Z') || (s[1] >= 'a' && s[1] <= 'z'))){
            if(s[0] >= 'A' && s[0] <='Z') s[0] = s[0] - 'A' + 'a';
            if(s[1] >= 'A' && s[1] <='Z') s[1] = s[1] - 'A' + 'a';
            if(mapB.count(s) > 0) mapB[s] += 1;
            else mapB[s] = 1;
        }
    }
    int intersection=0, Union=0;
    
    //mapA와 mapB를 비교해서 mapA와 mapB 둘 다 값이 있다면 작은 값은 교집합에, 큰 값은 합집합에 추가한다.
    //mapB에 같은 값이 없다면 합집합에 값을 추가한다.
    //mapB에 있는 값은 모두 0으로 설정한다.
    for(map<string,int>::iterator iter = mapA.begin(); iter != mapA.end(); iter++){
        if(mapB.count(iter->first) > 0){
            intersection += min(mapA[iter->first], mapB[iter->first]);
            Union += max(mapA[iter->first], mapB[iter->first]);
            mapB[iter->first] = 0;
        }
        else{
            Union += mapA[iter->first];
        }
    }
    
    //mapA와의 교집합은 이미 모두 추가했으니 0인값, 즉 교집합인 값을 제외한 값들을 모두 합집합에 추가한다.
    for(map<string,int>::iterator iter = mapB.begin(); iter != mapB.end(); iter++){
        if(mapB[iter->first] == 0) continue;
        else Union += mapB[iter->first];
    }
    
    //합집합이 0이면 그대로 반환한다.
    if(intersection == 0 && Union == 0) return 65536;
    
    answer = 65536 * intersection / Union;
    
    return answer;
}
