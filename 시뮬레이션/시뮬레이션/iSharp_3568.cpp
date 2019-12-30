//
//  iSharp_3568.cpp
//  시뮬레이션
//
//  Created by jiho park on 2019/11/17.
//  Copyright © 2019 jiho park. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(){
    char declaration[121];
    string dec;
    char type[121];
    int index = 0;
    vector<string> name;
    vector<string> extraType;
    string tmp1 = "", tmp2 = "";

    cin.getline(declaration,121);
//    getline(cin, dec);

//    cout << declaration;


    for(int i = 0; i < 121; i++){
        if(declaration[i] == ' '){
            declaration[i] = '\n';
            index = i + 1;
            break;
        }
        type[i] = declaration[i];
    }

//    printf("%s\n", type);

    for(int i = index; i < 121; i++){
        if((declaration[i] >= 'a' && declaration[i] <= 'z') || (declaration[i] >= 'A' && declaration[i] <='Z')){
            tmp1 += declaration[i];
        }else if(declaration[i] == ' '){
            name.push_back(tmp1);
            extraType.push_back(tmp2);
            tmp1 = "";
            tmp2 = "";
            continue;
        }else if(declaration[i] == ';'){
            tmp2 += declaration[i];
            name.push_back(tmp1);
            extraType.push_back(tmp2);
            break;
        }else if(declaration[i] == '['){
            tmp2 += ']';
        }else if(declaration[i] == ']'){
            tmp2 += '[';
        }
        else{
            tmp2 += declaration[i];
        }
    }
//    cout << extraType[0] << endl;

    for(int i = 0; i < name.size(); i++){
        cout << type;
        tmp1 = extraType[i];
//        size = tmp1.length();
        if(tmp1.length() > 1){
            for(int j = (int)tmp1.length() - 2; j >= 0; j--){
                cout << tmp1[j];
            }
        }
        cout << " " << name[i] << ";" << endl;
    }

    return 0;
}
//
//#include <iostream>
//#include <vector>
//
//using namespace std;
//
//int main(){
//    string s;
//    getline(cin, s);
//    vector <string> vec;
//    string now = "";
//
//    for(char x : s){
//        if(x == ' ' || x == ',' || x == ';'){
//            if(now.length() > 0){
//                vec.push_back(now);
//            }
//            now = "";
//        } else {
//            now += x;
//        }
//    }
//
//    string base = vec[0];
//    for(int i = 1; i < vec.size(); i++){
//        string t = base;
//        string s = vec[i];
//        while(s.length() > 0 && !(s.back() >= 'a' && s.back() <= 'z')){
//            if(s.back() == ']')
//                t += '[';
//            else if(s.back() == '[')
//                t += ']';
//            else
//                t += s.back();
//            s.pop_back();
//        }
//
//        cout << t << ' ' << s << ';' << endl;
//    }
//
//    return 0;
//}
