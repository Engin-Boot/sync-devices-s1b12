#include "CT.h"
#include<vector>
#include<sstream>
#include<iostream>
stack<Patient> patient_stack;

Patient CT::get_patient_information()
{
    int age = 15;
    string gender = "M";
    string name = "chandan";
    string procedure = "ABC";
    string consumables_used = "XYZ";
    
    // cout << "Enter patient name: ";
    // std::cin >> name;
    // cout << "Enter patient age: ";
    // std::cin >> age;
    // cout << "Enter patient gender: ";
    // cin >> gender;
    // cout << "Procedure: ";
    // cin >> procedure;
    // cout << "Consumables Used: ";
    // cin >> consumables_used;

    Patient p(0, age, name, gender, procedure, consumables_used);
    return p;
}
Patient CT::UnFlatten(string str)
{
    vector<string> contents;
    stringstream ss(str);
    string token;
    while (getline(ss, token, '|')) {
        contents.push_back(token);
    }
    Patient temp;
    temp.setID(stoi(contents[0]));
    temp.setName(contents[1]);
    temp.setAge(stoi(contents[2]));
    temp.setGender(contents[3]);
    temp.setProcedure(contents[4]);
    temp.setConsumables_used(contents[5]);
    return temp;
}
void CT::add_patient()
{
    Patient p;
    p = get_patient_information();
    int patient_id = patient_stack.size();
    p.setID(patient_id);
    patient_stack.emplace(p);
    //cout<<patient_stack.size();
    // ::patient_stack.emplace(p);
    // cout<<::patient_stack.size();
}
Patient CT::pop_and_return_patient()
{
    Patient p;
    p = patient_stack.top();
    patient_stack.pop();
    return p;
}
void CT::edit_name()
{
    Patient p = pop_and_return_patient();
    string name = "Rachoti";
    // cout << "Enter corrected name: ";
    // cin >> name;
    p.setName(name);
    patient_stack.emplace(p);
}
void CT::edit_age()
{
    Patient p = pop_and_return_patient();
    int age = 22;
    // cout << "Enter corrected age: ";
    // cin >> age;
    p.setAge(age);
    patient_stack.emplace(p);
}
void CT::edit_gender()
{
    Patient p = pop_and_return_patient();
    string gender = "F";
    // cout << "Enter correctd gender: ";
    // cin >> gender;
    p.setGender(gender);
    patient_stack.emplace(p);
}

void CT::edit_procedure()
{
    Patient p = pop_and_return_patient();
    string procedure = "ABCDEF";
    // cout << "Enter correctd procedure: ";
    // cin >> procedure;
    p.setProcedure(procedure);
    patient_stack.emplace(p);
}

void CT::edit_consumables_used()
{
    Patient p = pop_and_return_patient();
    string consumables_used = "VWXYZ";
    // cout << "Enter correctd consumables used: ";
    // cin >> consumables_used;
    p.setConsumables_used(consumables_used);
    patient_stack.emplace(p);
}

void Patient::setID(int id)
{
    this->id = id;
}

int Patient::getID()
{
    return this->id;
}

string Patient::toString()
{
    return to_string(id) + "|" + name + "|" + to_string(this->age)+ "|" + this->gender + "|" + procedure + "|" + consumables_used;
}

void Patient::setName(const string& name)
{
    this->name = name;
}
 
string Patient :: getName()
{
    return this->name;
}
 
void Patient::setAge(int age)
{
    this->age = age;
}
 
void Patient::setGender(const string& gender)
{
    this->gender = gender;
}
 
void Patient:: setProcedure(const string& procedure)
{
    this->procedure = procedure;
}
 
void Patient:: setConsumables_used(const string& consumables_used)
{
    this->consumables_used = consumables_used;
}

int Patient :: getAge()
{
    return this->age;
}
 
string Patient :: getGender()
{
    return this->gender;
}
 
string Patient :: getProcedure()
{
    return this->procedure;
}
 
string Patient :: getConsumables_used()
{
    return this->consumables_used;
}
