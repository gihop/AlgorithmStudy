#include <iostream>
#include <string>
#include <stack>

using namespace std;

//밑에 주석으로 쓴 것이 처음 풀었던 방식인데 시간초과가 발생했다.
//union find를 써야하나 생각했지만 stack을 이용하면 간단히 풀 수 있었다.

int solution(string s){
    stack<char> st;
    
    for(int i=0; i<s.size(); i++){
        if(st.empty() || st.top() != s[i]) st.push(s[i]);
        else if(st.top() == s[i]) st.pop();
    }
    if(st.empty()) return 1;
    else return 0;
}

//int solution(string s){
//    int i = 0;
//    while(i < s.size()-1){
//        if(s.size() == 0) return 1;
//        if(s[i] == s[i+1]){
//            s.erase(s.begin()+i);
//            s.erase(s.begin()+i);
//            if(i!=0) i--;
//        }
//        else i++;
//    }
//
//    return 0;
//}
