#include <string>
#include <vector>

using namespace std;

int solution(string arrangement) {
    int answer = 0;
    int now=0;
    for(int i=0; i<arrangement.size(); i++){
        if(arrangement[i]=='('){
            if(i<arrangement.size()-1 && arrangement[i+1]==')'){
                answer+=now;
                i++;
            }else{
                now++;
            }
        }else{
            now--;
            answer++;
        }
    }
    return answer;
}
