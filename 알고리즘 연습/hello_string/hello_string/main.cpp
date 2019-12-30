//
//  main.cpp
//  hello_string
//
//  Created by jiho park on 08/08/2019.
//  Copyright © 2019 jiho park. All rights reserved.
//

#include <iostream>
#include <string>

using namespace std;

int main() {
    string s = "abc";
    string t = "def";
    string s2 = s;
    
    cout << s << " 의 길이 : " << s.length() << endl;
    cout << s << " 뒤에 " << t << "를 붙이면 : " << s + t << endl;
    
    if (s == s2) {
        cout << s << " 와 " << s2 << " 는 같다 " << endl;
    }
    if (s != t) {
        cout << s << " 와 " << t << " 는 다르다 " << endl;
    }
    
    return 0;
}
