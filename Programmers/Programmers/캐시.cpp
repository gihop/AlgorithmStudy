#include <string>
#include <vector>
#include <map>
#include <deque>

using namespace std;

//cacheSize가 0일 수도 있다.
//문제를 꼼꼼히 보자.

string lowerCase(string city){
    string lowerCity = "";
    for(int i=0; i<city.size(); i++){
        if(city[i] >= 'A' && city[i] <= 'Z') lowerCity += city[i] - 'A' + 'a';
        else lowerCity += city[i];
    }
    
    return lowerCity;
}

int solution(int cacheSize, vector<string> cities) {
    int answer = 0;
    
    map<string, int> m;
    deque<string> cacheCity;
    
    if(cacheSize == 0) return cities.size()*5;
    
    for(int i=0; i<cities.size(); i++){
        string nowCity = lowerCase(cities[i]);
        if(m.count(nowCity) == 1 && m[nowCity] == 1){
            if(cacheCity[cacheCity.size()-1] != nowCity){
                string hitCity = "";
                for(deque<string>::iterator iter = cacheCity.begin(); iter != cacheCity.end(); iter++){
                    if(*iter == nowCity){
                        hitCity = *iter;
                        cacheCity.erase(iter);
                        break;
                    }
                }
                cacheCity.push_back(hitCity);
            }
            answer += 1;
        }
        else{
            if(cacheCity.size() < cacheSize){
                cacheCity.push_back(nowCity);
                m[nowCity] = 1;
            }
            else{
                string lruCity = cacheCity.front();
                cacheCity.pop_front();
                m[lruCity] = 0;
                m[nowCity] = 1;
                cacheCity.push_back(nowCity);
            }
            answer += 5;
        }
    }
    
    return answer;
}
