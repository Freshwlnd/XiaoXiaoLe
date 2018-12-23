#pragma once
#include<iostream>
#include<vector>
#include<set>
#include<ctime>
#include<algorithm>
#include<fstream>
#include <QFile>
using namespace std;
const int maxsize = 225 + 1;
const int award = 10;
class game_map {
private:
    int score;
    int map[maxsize];
    int level;//only have three:1 2 3
    int size[3];//the map size of every level;
    set<int> s;//记录被消除的方块坐标
    vector<int> v;//排行榜
public:
    int combol;
    game_map() {
        score = 0;
        level = 0;
        combol = 0;
        size[0] = 7;
        size[1] = 10;
        size[2] = 15;
        for (int i = 0; i < maxsize; ++i) {
            map[i] = -1;
        }
        s.clear();
    }
    game_map(int level, int score) {
        if (level <= 3 && level >= 1) {
            this->level = level;
            this->score = score;
            size[0] = 7;
            size[1] = 10;
            size[2] = 15;
            for (int i = 0; i < maxsize; ++i) {
                map[i] = -1;
            }
            s.clear();
        }
        else {
            cout << "No this level" << endl;
        }
    }
    ~game_map() {

    }
    void map_creat() {
        if (level == 1 || level == 2 || level == 3) {
            for (int i = 1; i <= size[level - 1] * size[level - 1]; i++) {
                map[i] = rand() % (3 + level) + 1;//level高方块种类增加
            }
            while (all_check_destroy(0)) {
                block_fill();
                s.clear();
            }
        }
        else {
            cout << "error creat" << endl;
        }
    }
    int index(int row, int col) {
        return (row - 1)*size[level - 1] + col;
    }
    void get_row_col(int index, int &row, int &col) {
        row = index / size[level - 1] + 1;
        col = index % size[level - 1];
    }
    bool check(int row, int col) {//保证row和col首先不越界
        if (
            (row - 1 > 0 && row + 1 <= size[level - 1] && map[index(row - 1, col)] == map[index(row, col)] && map[index(row - 1, col)] == map[index(row + 1, col)])
            || (col - 1 > 0 && col + 1 <= size[level - 1] && map[index(row, col - 1)] == map[index(row, col)] && map[index(row, col)] == map[index(row, col + 1)])
            || (row - 2 > 0 && map[index(row - 2, col)] == map[index(row - 1, col)] && map[index(row - 1, col)] == map[index(row, col)])
            || (col - 2 > 0 && map[index(row, col - 2)] == map[index(row, col - 1)] && map[index(row, col - 1)] == map[index(row, col)])
            || (row + 2 <= size[level - 1] && map[index(row + 2, col)] == map[index(row + 1, col)] && map[index(row + 1, col)] == map[index(row, col)])
            || (col + 2 <= size[level - 1] && map[index(row, col + 2)] == map[index(row, col + 1)] && map[index(row, col + 1)] == map[index(row, col)])
            )
            return true;
        return false;
    }
    bool continue_game_judge() {
        for (int i = 1; i <= size[level - 1]; ++i) {
            for (int j = 1; j <= size[level - 1]; ++j) {
                if (check(i, j))//原本就能消
                    return true;

                if (i < size[level - 1]) {//向下换
                    swap(map[index(i, j)], map[index(i + 1, j)]);
                    if (check(i, j) || check(i + 1, j)) {
                        swap(map[index(i, j)], map[index(i + 1, j)]);//换回来
                        return true;
                    }
                    swap(map[index(i, j)], map[index(i + 1, j)]);//换回来
                }

                if (j < size[level - 1]) {//向右换
                    swap(map[index(i, j)], map[index(i, j + 1)]);
                    if (check(i, j) || check(i, j + 1)) {
                        swap(map[index(i, j)], map[index(i, j + 1)]);//换回来
                        return true;
                    }
                    swap(map[index(i, j)], map[index(i, j + 1)]);//换回来

                }
            }
        }
    }
    void new_check(int i, int j) {//保证i，j不越界
                                  //向下检测有三个相同色块就可以丢进set
        if (i + 2 <= size[level - 1] && map[index(i, j)] == map[index(i + 1, j)] && map[index(i, j)] == map[index(i + 2, j)]) {
            s.insert(index(i, j));
            s.insert(index(i + 1, j));
            s.insert(index(i + 2, j));
        }
        if (j + 2 <= size[level - 1] && map[index(i, j)] == map[index(i, j + 1)] && map[index(i, j)] == map[index(i, j + 2)]) {
            s.insert(index(i, j));
            s.insert(index(i, j + 1));
            s.insert(index(i, j + 2));
        }
    }
    void change_block_to_empty() {
        set<int>::iterator iter = s.begin();
        for (; iter != s.end(); ++iter) {
            map[*iter] = -1;
        }
    }
    //todo:
    bool all_check_destroy(int combo) {//it can check three, four or five continue block
        s.clear();
        for (int i = 1; i <= size[level - 1]; ++i) {
            for (int j = 1; j <= size[level - 1]; ++j) {
                new_check(i, j);
            }
        }
        if (!s.empty()) {
            change_block_to_empty();
            score += combo * award*s.size();//得分增加
            return true;
        }
        else
            return false;
    }
    void block_fill() {//fill empty block in map.
        while (1) {
            int i;
            for (i = 1; i <= size[level - 1]; ++i) {
                if (map[i] == -1) {
                    map[i] = rand() % (3 + level) + 1;
                }
            }
            for (i = size[level - 1] + 1; i <= size[level - 1] * size[level - 1]; ++i) {
                if (map[i] == -1) {
                    map[i] = map[i - size[level - 1]];
                    int k = i;
                    while (k > size[level - 1]) {
                        map[k] = map[k - size[level - 1]];
                        k = k - size[level - 1];
                    }
                    map[k] = rand() % (3 + level) + 1;
                }
            }
            if (i > size[level - 1] * size[level - 1])
                break;
        }
    }
    bool change_judge(int a1, int a2, int a3, int a4) {//确保输入在范围内1.3 row，2.4 col。
        //todo:修改为从界面获取坐标
        int index1 = index(a1, a2);
        int index2 = index(a3, a4);
        swap(map[index1], map[index2]);
        //cout << "交换坐标" << endl;
        //print_map();
        if (!all_check_destroy(1)) {//无消除
            //cout << "交换无效" << endl;
            swap(map[index1], map[index2]);
            //print_map();
            return false;
        }
        return true;
        /*
        int combo = 1;//记录连击数，得分加成。每次交换方块连击数清空
        while (combo++) {
            s.clear();
            //print_map();
            block_fill();
            if (!all_check_destroy(combo))
                return true;
        }
        */
    }
    void print_map() {
        for (int i = 1; i <= size[level - 1] * size[level - 1]; ++i) {
            cout << map[i] << " ";
            if (i%size[level - 1] == 0)
                cout << endl;
        }
        cout << "score is : " << score << endl;
    }
    int get_map(int dex) {
        return map[dex];
    }
    int get_score() {
        return score;
    }
    void get_data(int level){
        ifstream ifs;
        v.clear();
        if(level==0){
           ifs.open("../imageTest/rank_level_1.txt");
        }
        else if(level==1){
            ifs.open("../imageTest/rank_level_2.txt");
        }
        else if(level==2){
            ifs.open("../imageTest/rank_level_3.txt");
        }
        if(ifs.is_open()){
            for(int i=0;i<5;++i){
                int data;
                ifs>>data;
                v.push_back(data);
            }
            ifs.close();
        } else {
            v.assign(5,0);
        }
    }
    void fill_operator(){
        ifstream ex;
        v.clear();
        if(level==1){
           ex.open("../imageTest/rank_level_1.txt");
        }
        else if(level==2){
            ex.open("../imageTest/rank_level_2.txt");
        }
        else if(level==3){
            ex.open("../imageTest/rank_level_3.txt");
        }
        if(ex.is_open()){
            for(int i=0;i<5;++i){
                int data;
                ex>>data;
                v.push_back(data);
            }
            if(score>v[4]){
                v[4]=score;
                if(score>v[3]){
                    swap(v[4],v[3]);
                    if(score>v[2]){
                        swap(v[3],v[2]);
                        if(score>v[1]){
                            swap(v[2],v[1]);
                            if(score>v[0]){
                                swap(v[0],v[1]);
                            }
                        }
                    }
                }
            }
            ex.close();
        } else {
            v.assign(5,0);
        }
        ofstream exe;
        if(level==1){
            exe.open("../imageTest/rank_level_1.txt");
        }
        else if(level==2){
            exe.open("../imageTest/rank_level_2.txt");
        }
        else if(level==3){
            exe.open("../imageTest/rank_level_3.txt");
        }
        else{
            return ;
        }
        if(exe.is_open()){
            exe << v[0] <<endl<<v[1]<<endl<<v[2]<<endl<<v[3]<<endl<<v[4]<<endl;
            exe.close();
        }
    }
    int get_v(int i){
        return v[i];
    }
};
