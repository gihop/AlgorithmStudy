#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int idx;

bool compare(string &a, string &b){
    if(a[idx] < b[idx]) return true;
    else if(a[idx] == b[idx]){
        if(a < b) return true;
        else return false;
    }
    else return false;
}

vector<string> solution(vector<string> strings, int n) {
    idx = n;
    sort(strings.begin(), strings.end(), compare);
    
    return strings;
}
