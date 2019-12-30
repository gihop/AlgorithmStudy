//
//  main.cpp
//  hellocpp
//
//  Created by jiho park on 24/07/2019.
//  Copyright © 2019 jiho park. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

template <typename T>
void print_vector(vector<T> vec) {
    cout << "[ ";
    for(typename vector<T>::iterator itr = vec.begin(); itr != vec.end(); itr++) {
        cout << *itr << " ";
    }
    cout << "]";
}

int main() {
    vector<int> vec;
    
    vec.push_back(10);  //맨 뒤에 10 추가
    vec.push_back(20);
    vec.push_back(30);
    vec.push_back(40);

//    for(int i = 0; i < vec.size(); i++) {
//        cout << "vec 의 " << i + 1 << " 번째 원소는 :: " << vec[i] << endl;
//    }
//
//    for(vector<int>::iterator itr = vec.begin(); itr != vec.end(); itr++){
//        cout << *itr << endl;
//    }
//
//    vector<int>::iterator itr = vec.begin() + 2;
//
//    cout << "3번째 원소는? : " << *itr << endl;

    cout << "처음 벡터 상태" << endl;
    
    print_vector(vec);
    
//    vector<int>::iterator itr = vec.begin();
//    vector<int>::iterator end_itr = vec.end();
//
//    for(; itr != end_itr; itr++) {
//        if(*itr == 20) {
//            vec.erase(itr);
//            itr = vec.begin();
//        }
//    }
//
//    cout << "값이 20인 원소를 지운다!" << endl;
//    print_vector(vec);
    
    cout << "역으로 벡터 출력하기!" << endl;
    vector<int>::reverse_iterator r_itr = vec.rbegin();
    for(; r_itr != vec.rend(); r_itr++) {
        cout << *r_itr << endl;
    }
}
