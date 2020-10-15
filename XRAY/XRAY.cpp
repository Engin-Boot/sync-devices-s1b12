#include "XRAY.hpp"

Patient get_patient_information()
{
    int age;
    string gender;
    string name;
    string procedure;
    string consumables_used;
    
    cout << "Enter patient name: ";
    std::cin >> name;
    cout << "Enter patient age: ";
    std::cin >> age;
    cout << "Enter patient gender: ";
    cin >> gender;
    cout << "Procedure: ";
    cin >> procedure;
    cout << "Consumables Used: ";
    cin >> consumables_used;

    Patient p(0, age, name, gender, procedure, consumables_used);
    return p;
}

Patient UnFlatten(const string& str)
{
    vector<string> contents;
    stringstream ss(str);
    string token;
    while (getline(ss, token, '|')) {
        contents.push_back(token);
    }
    Patient temp;
    temp.setID(stoi(contents[1]));
    temp.setName(contents[2]);
    temp.setAge(stoi(contents[3]));
    temp.setGender(contents[4]);
    temp.setProcedure(contents[5]);
    temp.setConsumables_used(contents[6]);
    return temp;
}

void display_main_menu()
{
    cout << "\n                         XRAY_DEVICES_V1               \n" << endl;
    cout << "1. Add a new patient" << endl;
    cout << "2. Edit current patient data" << endl;
    cout << "3. View current patient data" << endl;
    cout << "4. View Patient Count" << endl;
    cout << endl;
    fflush(stdout);
}

void display_edit_menu()
{
    cout << "\n1. Edit name" << endl;
    cout << "2. Edit age" << endl;
    cout << "3. Edit gender" << endl;
    cout << "4. Edit procedure" << endl;
    cout << "5. Edit consumables used" << endl;
    cout << "6. Edit all fields" << endl;
    cout << endl;
    fflush(stdout);
}

void add_patient()
{
    Patient p;
    p = get_patient_information();
    int patient_id = patient_stack.size();
    p.setID(patient_id);
    patient_stack.emplace(p);
}

void display_data(Patient& p)
{
    cout << "\nPatient details: " << endl;
    cout << "\n\tName: " << p.getName() << endl;
    cout << "\tAge: " << p.getAge() << endl;
    cout << "\tGender: " << p.getGender() << endl;
    cout << "\tProcedure: " << p.getProcedure() << endl;
    cout << "\tConsumables Used: " << p.getConsumables_used() << endl;
    fflush(stdout);
}

void view_current_patient_data()
{
    if(patient_stack.empty())
    {
        cout << "No records found" << endl;
    }
    else
    {
        Patient p;
        p = patient_stack.top();
        display_data(p);
    }
}

Patient pop_and_return_patient()
{
    Patient p;
    p = patient_stack.top();
    patient_stack.pop();
    return p;
}

void edit_name()
{
    Patient p = pop_and_return_patient();
    string name;
    cout << "Enter corrected name: ";
    cin >> name;
    p.setName(name);
    patient_stack.emplace(p);
}

void edit_age()
{
    Patient p = pop_and_return_patient();
    int age;
    cout << "Enter corrected age: ";
    cin >> age;
    p.setAge(age);
    patient_stack.emplace(p);
}

void edit_gender()
{
    Patient p = pop_and_return_patient();
    string gender;
    cout << "Enter correctd gender: ";
    cin >> gender;
    p.setGender(gender);
    patient_stack.emplace(p);
}

void edit_procedure()
{
    Patient p = pop_and_return_patient();
    string procedure;
    cout << "Enter correctd procedure: ";
    cin >> procedure;
    p.setProcedure(procedure);
    patient_stack.emplace(p);
}

void edit_consumables_used()
{
    Patient p = pop_and_return_patient();
    string consumables_used;
    cout << "Enter correctd consumables used: ";
    cin >> consumables_used;
    p.setProcedure(consumables_used);
    patient_stack.emplace(p);
}

void edit_all()
{
    Patient p = pop_and_return_patient();
    int patient_id = p.getID();
    p = get_patient_information();
    p.setID(patient_id);
    patient_stack.emplace(p);
}

void call_script_corresponding_to_choice(script_map& m, const int choice)
{
    auto iter = m.find(choice);
    (*iter->second)();
}

void edit_current_patient_data()
{
    Patient p;
    int choice;
    script_map edit_functions_map;
    edit_functions_map.emplace(1, &edit_name);
    edit_functions_map.emplace(2, &edit_age);
    edit_functions_map.emplace(3, &edit_gender);
    edit_functions_map.emplace(4, &edit_procedure);
    edit_functions_map.emplace(5, &edit_consumables_used);
    edit_functions_map.emplace(6, &edit_all);
    view_current_patient_data();
    display_edit_menu();
    cin >> choice;
    call_script_corresponding_to_choice(edit_functions_map, choice);
}

void serialize_and_publish(MQTTAsync& client, MQTTAsync_responseOptions& pub_opts)
{
    string serialized_data;
    serialized_data = patient_stack.top().toString();
    serialized_data = opts.clientid + string("|") + serialized_data; // prefix client_id
    publish(client, pub_opts, serialized_data);
}

void view_patient_count()
{
    cout << patient_stack.size() << endl;
}

void repeat_until_finished(MQTTAsync& client, MQTTAsync_responseOptions& pub_opts)
{
    int choice;
    script_map functions_map;
    functions_map.emplace(1, &add_patient);
    functions_map.emplace(2, &edit_current_patient_data);
    functions_map.emplace(3, &view_current_patient_data);
    functions_map.emplace(4, &view_patient_count);
    cin >> choice;

    call_script_corresponding_to_choice(functions_map, choice);

    if(choice < 3)
    {
        // Publish only after patient add or edit
        serialize_and_publish(client, pub_opts);
    }

    fflush(stdout);
}

void wait_for_disconnection(MQTTAsync& client, MQTTAsync_disconnectOptions& disc_opts)
{
    disconnect_client(client, disc_opts);
    while (!disconnected)
		mysleep(100);
}

void init_globals()
{
    opts =
    {
	    NULL, MQTTVERSION_DEFAULT, (char*)TOPIC, (char*)CLIENT_ID, 0, 0, 20, /* MQTT options */
    };

    finished = 0;
    subscribed = 0;
    toStop = 0;
    disconnected = 0;
}
