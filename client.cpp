#include <iostream>
#include "fstream"
#include <string>

using namespace std;

struct Student {
    char name[25]{};
    int grades[4]{};
    int answer{};
    string client_name{};
};

void listen(const string& file, int position) {
    int cursor = position;
    int answer;
    while (true) {
        ifstream in(file, ios::binary);
        if (in) {
            in.seekg(cursor);
            in.read((char*)&answer, sizeof(answer));
            if (cursor < in.tellg()) {
                cout << "Answer: " << answer << "\n";
                cursor += sizeof(answer);
                break;
            }
            in.close();
        }
    }
}

int main() {
    setlocale(LC_ALL, "rus");
    string client_name;
    cout << "Введите имя клиента:\n";
    getline(cin, client_name);
    while (true) {
        Student student{};
        cout << "Введите имя:\n";
        cin >> student.name;
        cout << "Введите оценки:\n";
        for (int i = 0; i < 4; i++)
            cin >> student.grades[i];
        student.client_name = client_name;
        ofstream out("../server.sv", ios::binary | ios::app);
        out.write((char*)&student, sizeof(student));
        out.close();

        ifstream in("../clients/" + client_name + ".client", ios::binary);
        int pos;
        if (in) {
            in.seekg(0, ios::end);
            pos = in.tellg();
            in.close();
        }
        else {
            pos = 0;
        }
        listen("../clients/" + client_name + ".client", pos);
    }
    return 0;
}
