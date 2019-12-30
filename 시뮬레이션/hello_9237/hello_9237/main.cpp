//
//  main.cpp
//  hello_9237
//
//  Created by jiho park on 14/08/2019.
//  Copyright © 2019 jiho park. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool desc(int a, int b){
    return a > b;
}

int main() {
    vector<int> vec;
    int num;
    int tree, days = 1, left = 0;
    
    cin >> num;
    for(int i = 0; i < num; i++){
        cin >> tree;
        vec.push_back(tree);
    }
    
    sort(vec.begin(), vec.end(), desc);
//
//    for(typename vector<int>::iterator itr = vec.begin(); itr != vec.end(); itr++){
//        cout << *itr;
//    }
//
//    cout << endl;
    
    for(typename vector<int>::iterator itr = vec.begin(); itr != vec.end(); itr++) {
        left++;
        if(days - left < *itr)
            days += (left + *itr) - days;
    }
    cout << days+1 << endl;
}

