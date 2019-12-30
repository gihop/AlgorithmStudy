//
//  main.cpp
//  hello_null_check
//
//  Created by jiho park on 14/08/2019.
//  Copyright © 2019 jiho park. All rights reserved.
//

#include <iostream>

using namespace std;

int main() {
    int a = 3;
    if(a)
        cout << "null" << endl;
    else
        cout << "not null" << endl;
}
