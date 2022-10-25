#include <iostream>
#include "fstream"
#include <filesystem>
#include <string>

using namespace std;

struct Students {
    char name[25];
    int grades[4];
    int salary;
    string client_name;
};
int answer;

int min_grade(int grades[4]) {
    int res = 5;
    for (auto i = 0; i < 4; i++) {
        res = res > grades[i] ? grades[i] : res;
    }
    return res;
}

int get_answer(int grades[4]) {
    switch (min_grade(grades)) {
        case 2:
            return -1;
        case 3:
            return 0;
        case 4:
            return 1800;
        default:
            return 2500;
    }
}

void answering(const string &file, int c){
    Students student;
    while(true){
        ifstream in(file,ios::binary);
        in.seekg(c);
        in.read((char*)&student, sizeof(student));
        if(c<in.tellg()){
            answer = get_answer(student.grades);
            cout<<"Name: "<<student.name<<"\n Answer: "<<answer<<endl;
            ofstream out("../second scenery/" +student.client_name+".c", ios::binary | ios::app);
           out.write((char*)&answer, sizeof(answer));
           out.close();
           c += sizeof(student);
        }
        in.close();
    }
}

int main(){
    cout<<"server is working \n";
    string file = "../second scenery/server.sv";
    ifstream in(file, ios::binary);
    in.seekg(0,ios::end);
    int position  = in.tellg();
    in.close();
    answering(file, position);
    return 0;
}
