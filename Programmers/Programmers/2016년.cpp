#include <string>
#include <vector>
#include <iostream>

using namespace std;

string solution(int a, int b) {
    string answer = "";
    
    vector<int> months = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30};
    int days = 5;
    
    for(int i=0; i<a-1; i++)
        days += months[i];
    
    days += b;
    
    int day = days % 7;
    
    if(day == 1) answer = "SUN";
    else if(day == 2) answer = "MON";
    else if(day == 3) answer = "TUE";
    else if(day == 4) answer = "WED";
    else if(day == 5) answer = "THU";
    else if(day == 6) answer = "FRI";
    else answer = "SAT";
    
    return answer;
}
