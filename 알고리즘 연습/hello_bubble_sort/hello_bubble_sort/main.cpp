//
//  main.cpp
//  hello_bubble_sort
//
//  Created by jiho park on 06/08/2019.
//  Copyright © 2019 jiho park. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

template <typename T>
void sort_list(vector<T>& data) {
    for(size_t i = 1; i < data.size(); i++) {
        for(size_t j = 0; j < data.size() - i; j++) {
            if(data[j] > data[j + 1]) {
                T temp = move(data[j]);
                data[j] = move(data[j + 1]);
                data[j + 1] = move(temp);
            }
        }
    }
}

int main() {
    vector<int> vec = {1, 5, 7, 6, 8, 9, 4, 3, 2, 10};
    sort_list(vec);
    
    for(int num : vec) {
        cout << num << " ";
    }
}
