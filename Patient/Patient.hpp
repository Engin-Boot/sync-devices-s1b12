#pragma once
#include <string>
using namespace std;

class Patient
{
    int age;
    string name;
    char gender;
    string procedure;
    string consumables_used;
    public:
        Patient():age(0), name("none"), gender('X'), procedure("none"), consumables_used("none") {}
        Patient(int age, const string& name, char gender, const string& procedure, const string& consumables_used)
            :age(age), name(name), gender(gender), procedure(procedure), consumables_used(consumables_used){} 

        string toString();
 
        void setName(const string& name);
 
        void setAge(int age);

        void setGender(char gender);

        void setProcedure(const string& procedure);

        void setConsumables_used(const string& consumables_used);

        string getName();

        int getAge();

        char getGender();

        string getProcedure();

        string getConsumables_used();

};