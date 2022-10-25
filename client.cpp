#include <iostream>
#include "fstream"


using namespace std;

struct Students{
    char name[25];
    int grades[4];
    int salary;
    string client_name;
};

bool compare(char a[25], char a2[25]){
    for(int i = 0; i < 25; i++){
        if (a[i] != a2[i])
            return false;
    }
    return true;
}

void answering(const string &file, int pos){
    int c = pos; // позиция в файле
    int answer; //ответ
    while(true){
        ifstream in(file,ios::binary); //ввод в файл
        if(in){
            in.seekg(c); //ставит в заданную позицию
            in.read((char *) &answer, sizeof(answer)); //запись в файл ответа
            if(c < in.tellg()){ // если начальная позиция меньше позиции в файле
                cout<<"Answer: "<<answer<<endl; // выводим ответ
                c += sizeof(answer); // добавляем к нашей позиции новые данные
                break;
            }
            in.close();
        }
    }
}

int main(){
    string client_name;
    cout<<"Name of client: \n";
    getline(cin, client_name);
    while(true){
        Students student;
        cout<<"Name of student: \n";
        cin>>student.name;
        cout<<"Marks of student: \n";
        for(int i = 0; i<4; i++)
            cin>>student.grades[i];
        student.client_name = client_name;
        ofstream out("../second scenery/server.sv", ios::binary | ios::app);
        out.write((char*)&student, sizeof(student));
        out.close();
        ifstream in("../second scenery/"+client_name + ".c", ios::binary);
        int position;
        if (in){
            in.seekg(0,ios::end);
            position = in.tellg();
            in.close();
        }
        else
            position = 0;
        answering("../second scenery/" +client_name + ".c", position);
    }
    return 0;
}
