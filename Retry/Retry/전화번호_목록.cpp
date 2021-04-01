#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// phone_book 원소가 백만개일 수 있기 때문에 sort를 사용해야 한다.

bool solution(vector<string> phone_book) {
    bool answer = true;

    sort(phone_book.begin(), phone_book.end());
    
    for(int i=1; i<phone_book.size(); i++){
        if(phone_book[i-1] == phone_book[i].substr(0, phone_book[i-1].size())) return false;
    }
    
    return answer;
}
