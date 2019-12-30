//
//  main.cpp
//  hello_deque
//
//  Created by jiho park on 03/08/2019.
//  Copyright © 2019 jiho park. All rights reserved.
//

#include <iostream>
#include <deque>

using namespace std;

template <typename T>
void print_deque(deque<T>& dq) {
    cout << "[ ";
    for(const auto& elem : dq) {
        cout << elem << " ";
    }
    cout << "]" << endl;
}

int main(void) {
    deque<int> dq;
    dq.push_back(10);
    dq.push_back(20);
    dq.push_front(30);
    dq.push_front(40);
    
    cout << "초기 dq 상태" << endl;
    print_deque(dq);
    
    cout<< "맨 앞의 원소 제거" << endl;
    dq.pop_front();
    print_deque(dq);
}
