#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

using namespace std;

//굉장히 까다로운 구현 문제.
//테스트 케이스에서 2개가 틀렸다. 총점 92점.
//개선 사항이 떠오르면 수정할 것.

vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {
    vector<vector<int>> answer;
    
    //기둥과 보의 x,y 좌표와 1,0으로 삭제 유무를 저장한다.
    map<pair<int,int>,int> pillar, beam;
    int pillarSize = 0, beamSize = 0;
    
    for(int i=0; i<build_frame.size(); i++){
        int x, y, type, construct;
        x = build_frame[i][0];
        y = build_frame[i][1];
        type = build_frame[i][2];
        construct = build_frame[i][3];
        if(construct){//설치하는 경우.
            if(type == 0){//기둥 설치.
                if(y == 0) {//바닥에서 설치하는 경우 바로 설치할 수 있다.
                    pillar[make_pair(x,y)] = 1;
                    pillarSize++;
                }
                else{
                    //아래에 기둥이 있는 경우.
                    if(pillar.count(make_pair(x, y-1)) > 0 && pillar[make_pair(x, y-1)] == 1) {
                        pillar[make_pair(x,y)] = 1;
                        pillarSize++;
                        continue;
                    }
                    //보의 오른쪽 위에 설치하는 경우.
                    if(x > 0 && beam.count(make_pair(x-1, y)) > 0 && beam[make_pair(x-1, y)] == 1) {
                        pillar[make_pair(x,y)] = 1;
                        pillarSize++;
                        continue;
                    }
                    //보의 왼쪽 위에 설치하는 경우.
                    if(beam.count(make_pair(x, y)) > 0 && beam[make_pair(x,y)] == 1){
                        pillar[make_pair(x,y)] = 1;
                        pillarSize++;
                        continue;
                    }
                }
            }
            else{//보를 설치하는 경우.
                //보의 왼쪽에 기둥이 있는 경우.
                if(pillar.count(make_pair(x, y-1)) > 0 && pillar[make_pair(x, y-1)] == 1){
                    beam[make_pair(x,y)] = 1;
                    beamSize++;
                    continue;
                }
                //보의 오른쪽에 기둥이 있는 경우.
                if(pillar.count(make_pair(x+1, y-1)) > 0 && pillar[make_pair(x+1, y-1)] == 1){
                    beam[make_pair(x,y)] = 1;
                    beamSize++;
                    continue;
                }
                //양쪽에 보가 있는 경우.
                if(x > 0 && x < n && beam.count(make_pair(x-1, y)) > 0 && beam[make_pair(x-1, y)] == 1 && beam.count(make_pair(x+1, y)) > 0 && beam[make_pair(x+1, y)] == 1){
                    beam[make_pair(x,y)] = 1;
                    beamSize++;
                    continue;
                }
            }
        }
        else{//삭제하는 경우 삭제할 구조물을 임시로 삭제하고 남아있는 구조물이 모두 적합한지 검사한다.
            bool possible = false;
            //값을 0으로 바꿔서 임시로 삭제한다.
            if(type == 0) pillar[make_pair(x,y)] = 0;
            else beam[make_pair(x,y)] = 0;
            //임시로 삭제했을 때 남아있는 기둥이 모두 적합한지 검사.
            for(map<pair<int,int>,int>::iterator iter = pillar.begin(); iter != pillar.end(); iter++){
                //삭제된 기둥인 넘어간다.
                if(iter->second == 0) continue;
                int nx = (iter->first).first, ny = (iter->first).second;
                possible = false;
                if(ny == 0) {
                    possible = true;
                    continue;
                }
                else{
                    if(pillar.count(make_pair(nx, ny-1)) > 0 && pillar[make_pair(nx, ny-1)] == 1) {
                        possible = true;
                        continue;
                    }
                    if(nx > 0 && beam.count(make_pair(nx-1, ny)) > 0 && beam[make_pair(nx-1, ny)] == 1) {
                        possible = true;
                        continue;
                    }
                    if(beam.count(make_pair(nx, ny)) > 0 && beam[make_pair(nx,ny)] == 1){
                        possible = true;
                        continue;
                    }
                }
                //한 개라도 부적합하면 실패.
                if(!possible) break;
            }
            //부적합한 기둥이 있는 경우 임시 삭제한 기둥을 다시 설치한다.
            if(!possible){
                if(type == 0) pillar[make_pair(x,y)] = 1;
                else beam[make_pair(x,y)] = 1;
                continue;
            }
            //남아있는 모든 보가 적합한지 검사한다.
            for(map<pair<int,int>,int>::iterator iter = beam.begin(); iter != beam.end(); iter++){
                if(iter->second == 0) continue;
                int nx = (iter->first).first, ny = (iter->first).second;
                possible = false;
                if(pillar.count(make_pair(nx, ny-1)) > 0 && pillar[make_pair(nx, ny-1)] == 1){
                    possible = true;
                    continue;
                }
                if(pillar.count(make_pair(nx+1, ny-1)) > 0 && pillar[make_pair(nx+1, ny-1)] == 1){
                    possible = true;
                    continue;
                }
                if(nx > 0 && nx < n && beam.count(make_pair(nx-1, ny)) > 0 && beam[make_pair(nx-1, ny)] == 1 && beam.count(make_pair(nx+1, ny)) > 0 && beam[make_pair(nx+1, ny)] == 1){
                    possible = true;
                    continue;
                }
                //한 개라도 부적합하면 실패.
                if(!possible) break;
            }
            //부적합한 보가 있는 경우 임시 삭제한 보를 다시 설치한다.
            if(!possible){
                if(type == 0) pillar[make_pair(x,y)] = 1;
                else beam[make_pair(x,y)] = 1;
            }
            //남아있는 기둥과 보가 모두 적합한 경우.
            else{
                if(type == 0) pillarSize--;
                else beamSize--;
            }
        }
    }
    
    answer.resize(pillarSize + beamSize);
    int count = 0;
    
    for(map<pair<int,int>,int>::iterator iter = pillar.begin(); iter != pillar.end(); iter++){
        if(iter->second == 0) continue;//삭제된 기둥.
        answer[count].push_back((iter->first).first);
        answer[count].push_back((iter->first).second);
        answer[count].push_back(0);
        count++;
    }
    
    for(map<pair<int,int>,int>::iterator iter = beam.begin(); iter != beam.end(); iter++){
        if(iter->second == 0) continue;//삭제된 보.
        answer[count].push_back((iter->first).first);
        answer[count].push_back((iter->first).second);
        answer[count].push_back(1);
        count++;
    }
    sort(answer.begin(), answer.end());
    
    return answer;
}
