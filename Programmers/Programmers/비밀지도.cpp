#include <string>
#include <vector>
#include <iostream>

using namespace std;

string base = "";

string binary(int num, int n){
    string s = base;
    
    string tmp = "";
    while(num){
        if(num%2 == 0) tmp += "0";
        else tmp += "1";
        num /= 2;
    }
    
    for(int i=tmp.size()-1; i>=0; i--)
        s[n-i-1] = tmp[i];
    
    return s;
}

vector<string> solution(int n, vector<int> arr1, vector<int> arr2) {
    vector<string> answer;
    vector<vector<bool>> map(n, vector<bool>(n, false));
    
    for(int i=0; i<n; i++)
        base += "0";
    
    for(int i=0; i<n; i++){
        string a, b;
        a = binary(arr1[i], n);
        b = binary(arr2[i], n);
        for(int j=0; j<n; j++){
            if(a[j] == '1' || b[j] == '1') map[i][j] = true;
        }
    }
    
    for(int i=0; i<n; i++){
        string s = "";
        for(int j=0; j<n; j++){
            if(map[i][j]) s += "#";
            else s += " ";
        }
        answer.push_back(s);
    }
    
    return answer;
}
