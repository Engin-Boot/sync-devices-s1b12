#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "Patient.hpp"

string Patient::toString()
{
    return name + "|" + to_string(this->age)+ "|"+to_string(this->gender)+ "|" +procedure+ "|" +consumables_used;
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

void Patient::setGender(char gender)
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

char Patient :: getGender()
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
 