#include <string>
#include <vector>

using namespace std;

int solution(int n) {
    int answer = 0;
    int oneCount=0, number=n;
    while(number){
        int divide=number%2;
        if(divide==1) oneCount++;
        number/=2;
    }
    int nextCount=0;
    while(true){
        n++;
        nextCount=0;
        number=n;
        while(number){
            int divide=number%2;
            if(divide==1) nextCount++;
            number/=2;
        }
        if(nextCount==oneCount) {
            answer=n;
            break;
        }
    }
    return answer;
}
