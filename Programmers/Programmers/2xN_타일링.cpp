#include <string>
#include <vector>

using namespace std;

int MAX = 1000000007;

int solution(int n) {
    int answer = 0;
    
    if(n <= 3)
        return n;
    
    int a=2, b=3;
    for(int i=4; i<=n; i++){
        answer = (a+b)%MAX;
        a = b;
        b = answer;
    }
    
    return answer;
}
