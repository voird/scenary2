#include <iostream>
#include "fstream"
#include <filesystem>

using namespace std;

struct Student {
    char name[25]{};
    int grades[4]{};
    int answer{};
    string client_name{};
};
int answer;

int min(int grades[4]) {
    int res = 5;
    for (auto i = 0; i < 4; i++) {
        res = res > grades[i] ? grades[i] : res;
    }
    return res;
}

int get_answer(int grades[4]) {
    switch (min(grades)) {
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

void answering(const string& file, int point) {
    Student student{};
    while (true) {
        ifstream in(file, ios::binary);
        in.seekg(point);
        in.read((char*)&student, sizeof(student));
        if (point < in.tellg()) {
            answer = get_answer(student.grades);
            cout << "Name: " << student.name << "\nSalary: " << answer << "\n";
            ofstream out("../clients/" + student.client_name + ".client", ios::binary | ios::app);
            out.write((char*)&answer, sizeof(answer));
            out.close();
            point += sizeof(student);
        }
        in.close();
    }
}

int main() {
    string file = "../server.sv";
    cout << "Starting server \n";
    ifstream in(file, ios::binary);
    in.seekg(0, ios::end);
    int position = in.tellg();
    in.close();
    answering(file, position);
    return 0;
}
