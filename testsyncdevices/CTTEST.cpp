#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>
#include<stack>
#include "CT.h"
#include "../Patient/Patient.hpp"

using namespace std;
TEST_CASE("testing get information function"){
    Patient p = CT::get_patient_information();
    //cout<<p;
    int i = 0;
    if(p.age == 15 && p.gender=="M" && p.name=="chandan" && p.procedure =="ABC" && p.consumables_used == "XYZ"){
        i=1;
    }
    REQUIRE(i==1);
}
TEST_CASE("testing get information function for false"){
    Patient p = CT::get_patient_information();
    //cout<<p;
    int i = 0;
    if(p.age == 17 && p.gender=="M" && p.name=="chandan" && p.procedure =="ABC" && p.consumables_used == "XYZ"){
        i=1;
    }
    REQUIRE(i==0);
}
TEST_CASE("Test for UnFlatten function"){
    string s = "0|chandan|15|M|ABC|XYZ";
    Patient p = CT::UnFlatten(s);
    int i = 0;
    if(p.id == 0 && p.gender=="M" && p.name=="chandan" && p.procedure =="ABC" && p.consumables_used == "XYZ"){
        i=1;
    }
    REQUIRE(i == 1);
}
TEST_CASE("Test for UnFlatten function for false"){
    string s = "0|chandan|15|M|ABC|XYZ";
    Patient p = CT::UnFlatten(s);
    int i = 0;
    if(p.id == 0 && p.age == 17 && p.gender=="M" && p.name=="chandan" && p.procedure =="ABC" && p.consumables_used == "XYZ"){
        i=1;
    }
    REQUIRE(i == 0);
}
TEST_CASE("Set ID and Get patient ID"){
    Patient p;
    p.setID(15);
    int id = p.getID();
    REQUIRE(id == 15);
}
TEST_CASE("Set Name and Get name"){
    Patient p;
    p.setName("chandan");
    string name = p.getName();
    REQUIRE(name == "chandan");
}
TEST_CASE("setage and getage"){
    Patient p;
    p.setAge(17);
    int age = p.getAge();
    REQUIRE(age == 17);
}
TEST_CASE("setProcedure and getprocedure"){
    Patient p;
    p.setProcedure("ABC");
    string procedure = p.getProcedure();
    REQUIRE(procedure == "ABC");
}
TEST_CASE("SetConsumables used and GetConsumables used"){
    Patient p;
    p.setConsumables_used("XYZ");
    string consumables = p.getConsumables_used();
    REQUIRE(consumables == "XYZ");
}
TEST_CASE("SetGender and GetGender"){
    Patient p;
    p.setGender("M");
    string gender = p.getGender();
    REQUIRE(gender == "M");
}
TEST_CASE("Converting all the data taken from user into a big string"){
    Patient p;
    p.setID(15);
    p.setName("chandan");
    p.setAge(17);
    p.setGender("M");
    p.setProcedure("ABC");
    p.setConsumables_used("XYZ");
    string s = p.toString();
    REQUIRE(s == "15|chandan|17|M|ABC|XYZ");
}
TEST_CASE("Add patient information to stack"){
    CT::add_patient();
    REQUIRE(patient_stack.size() == 1);
}
TEST_CASE("Pop patient details from stack and return function"){
    Patient p;
    CT::add_patient();
    p = CT::pop_and_return_patient();
    //cout<<p.id<<endl;
    int i=0;
    if(p.id == 1 && p.age == 15 && p.gender == "M" && p.procedure == "ABC" && p.consumables_used == "XYZ"){
        i =1;
    }
    REQUIRE(i == 1);
}
TEST_CASE("Edit Patient Name"){
    Patient p;
    CT::add_patient();
    CT::edit_name();
    p = CT::pop_and_return_patient();
    //cout<<patient_stack.size()<<endl;
    cout<<p.name<<endl;
    REQUIRE(p.name == "Rachoti");
}
TEST_CASE("Edit Patient Age"){
    Patient p;
    CT::add_patient();
    CT::edit_age();
    p = CT::pop_and_return_patient();
    cout<<p.age<<endl;
    REQUIRE(p.age == 22);
}
TEST_CASE("Edit Patient gander"){
    Patient p;
    CT::add_patient();
    CT::edit_gender();
    p = CT::pop_and_return_patient();
    cout<<p.gender<<endl;
    REQUIRE(p.gender == "F");
}
TEST_CASE("Edit Patient Procedure"){
    Patient p;
    CT::add_patient();
    CT::edit_procedure();
    p = CT::pop_and_return_patient();
    cout<<p.procedure<<endl;
    REQUIRE(p.procedure == "ABCDEF");
}
TEST_CASE("Edit Patient Consumables Used"){
    Patient p;
    CT::add_patient();
    CT::edit_consumables_used();
    p = CT::pop_and_return_patient();
    cout<<p.consumables_used<<endl;
    REQUIRE(p.consumables_used == "VWXYZ");
}
