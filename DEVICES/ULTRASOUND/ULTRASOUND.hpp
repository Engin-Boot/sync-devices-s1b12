#pragma once

#include <unordered_map>
#include <stack>
#include "../../Patient/Patient.hpp"
#include "pub_sub_utils.hpp"
using namespace std;

typedef void (*ScriptFunction)(void); // function pointer type
typedef unordered_map<int, ScriptFunction> script_map;

extern stack<Patient> patient_stack;

Patient get_patient_information();
Patient pop_and_return_patient();
Patient UnFlatten(const string& str);
void display_main_menu();
void display_edit_menu();
void add_patient();
void view_current_patient_data();
void edit_name();
void edit_age();
void edit_gender();
void edit_procedure();
void edit_consumables_used();
void display_data(Patient& p);
void view_patient_count();
void exit_client();
void edit_all();
void call_script_corresponding_to_choice(script_map& m, const int choice);
void edit_current_patient_data();
void serialize_and_publish(MQTTAsync& client, MQTTAsync_responseOptions& pub_opts);
void repeat_until_finished(MQTTAsync& client, MQTTAsync_responseOptions& pub_opts);
void wait_for_disconnection(MQTTAsync& client, MQTTAsync_disconnectOptions& disc_opts);
void init_globals();
