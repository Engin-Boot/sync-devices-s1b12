#include <iostream>
#include <string>
#include <stack>
#include <unordered_map>
#include "pub_sub_utils.hpp"
#include "../Patient/Patient.hpp"
#include "XRAY.hpp"

using namespace std;

// Global variables shared across multiple translation units
pubsub_opts opts;
int finished;
int subscribed;
int toStop;
int disconnected;
stack<Patient> patient_stack;

// Global variables visible to current translation unit only


int main(int argc, char** argv)
{
    // Initial configurations and setup
	MQTTAsync_disconnectOptions disc_opts = MQTTAsync_disconnectOptions_initializer;
	MQTTAsync_createOptions create_opts = MQTTAsync_createOptions_initializer;
    MQTTAsync_responseOptions pub_opts = MQTTAsync_responseOptions_initializer;
	MQTTAsync client;

    // Initialize global variables
    init_globals();

    // MQTT Broker url
    char* url = (char*)BROKER_URL;

    // Create Client Object
    create_client_object(client, create_opts, url);

    // Set Callbacks
    set_callbacks(client);
    
    // Connect client to broker
	myconnect(client);

    // Set Publish Callbacks
    pub_opts.onSuccess = onPublish;
	pub_opts.onFailure = onPublishFailure;

    //Repeat until finished:
    // Publish any messages the client needs to
    // Handle any incoming messages 
    while (!toStop)
	{
        sleep(5);
        display_main_menu();
        repeat_until_finished(client, pub_opts);
        sleep(5);
	}

    // Disconnect
	wait_for_disconnection(client, disc_opts);

    // Destroy client
	MQTTAsync_destroy(&client);

	return EXIT_SUCCESS;
}