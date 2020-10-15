#pragma once
#include <string>
using namespace std;
 
class Patient
{
    int id;
    int age;
    string name;
    string gender;
    string procedure;
    string consumables_used;
    public:
        Patient():id(0), age(0), name("none"), gender("X"), procedure("none"), consumables_used("none") {}
        Patient(int id, int age, const string& name, const string& gender, const string& procedure = "none", const string& consumables_used = "none")
            :id(id), age(age), name(name), gender(gender), procedure(procedure), consumables_used(consumables_used){} 
 
        string toString();

        void setID(int id);
 
        void setName(const string& name);
 
        void setAge(int age);
 
        void setGender(const string& gender);
 
        void setProcedure(const string& procedure);
 
        void setConsumables_used(const string& consumables_used);
 
        string getName();
 
        int getAge();

        int getID();
 
        string getGender();
 
        string getProcedure();
 
        string getConsumables_used();
 
};