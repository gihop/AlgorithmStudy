//
//  main.cpp
//  hello_list
//
//  Created by jiho park on 01/08/2019.
//  Copyright © 2019 jiho park. All rights reserved.
//

#include <iostream>
#include <list>

using namespace std;

template <typename T>
void print_list(list<T>& lst) {
    cout << "[";
    for(const auto elem : lst) {
        cout << elem << " ";
    }
    cout << "]" << endl;
}

int main() {
    list<int> lst;
    
    lst.push_back(10);
    lst.push_back(20);
    lst.push_back(30);
    lst.push_back(40);
    
    cout << "처음 리스트의 상태 " << endl;
    print_list(lst);
    
    for(list<int>::iterator itr = lst.begin(); itr != lst.end(); itr++) {
        if(*itr == 20) {
            lst.insert(itr, 50);
        }
    }
    
    cout << "값이 20인 원소 앞에 50을 추가" << endl;
    print_list(lst);
    
    for(list<int>::iterator itr = lst.begin(); itr != lst.end(); itr++) {
        if(*itr == 30) {
            lst.erase(itr);
        }
    }
    
    cout << "값이 30인 원소를 제거한다" << endl;
    print_list(lst);
}
