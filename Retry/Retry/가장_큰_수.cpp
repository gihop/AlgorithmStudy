#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool compare(string const &a, string const &b){
    if(a+b > b+a) return true;
    else return false;
}

string solution(vector<int> numbers) {
    vector<string> string_numbers(numbers.size(), "");
    for(int i=0; i<numbers.size(); i++)
        string_numbers[i] += to_string(numbers[i]);
    sort(string_numbers.begin(), string_numbers.end(), compare);
    if(string_numbers[0] == "0") return "0"; // 모든 원소가 0인 경우에는 배열안에 ["0","0","0"]이 되게 된다.
    string answer = "";
    for(int i=0; i<numbers.size(); i++)
        answer += string_numbers[i];
    
    return answer;
}
