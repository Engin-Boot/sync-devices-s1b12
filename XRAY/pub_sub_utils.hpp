#pragma once

#include "../Patient/Patient.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include "MQTTAsync.h"
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <stack>
#include <unistd.h>

#define TOPIC "MedicalDevice"
#define CLIENT_ID "XRAY"
#define BROKER_URL "tcp://localhost:1883"

using namespace std;

struct pubsub_opts
{
	/* Message options */
	char* message;
	/* MQTT options */
	int MQTTVersion;
	char* topic;
	char* clientid;
	int qos;
	int retained;
	int keepalive;
};

extern pubsub_opts opts;
extern int finished;
extern int subscribed;
extern int toStop;
extern int disconnected;

vector<string> split(const char* str, char delimiter);

void mysleep(int ms);

int messageArrived(void *context, char *topicName, int topicLen, MQTTAsync_message *message);

void onDisconnect(void* context, MQTTAsync_successData* response);

void onPublishFailure(void* context, MQTTAsync_failureData* response);

void onPublish(void* context, MQTTAsync_successData* response);

void onSubscribe(void* context, MQTTAsync_successData* response);

void onSubscribeFailure(void* context, MQTTAsync_failureData* response);

void onConnectFailure(void* context, MQTTAsync_failureData* response);

void onConnect(void* context, MQTTAsync_successData* response);

void myconnect(MQTTAsync client);

int mypublish(MQTTAsync client, int datalen, std::string& data, MQTTAsync_responseOptions& pub_opts);

void create_client_object(MQTTAsync& client, MQTTAsync_createOptions& create_opts, char* url);

void set_callbacks(MQTTAsync& client);

void disconnect_client(MQTTAsync& client, MQTTAsync_disconnectOptions& disc_opts);

void publish(MQTTAsync& client, MQTTAsync_responseOptions& pub_opts, string& data);

bool is_patient_stack_empty();

Patient deserialize(MQTTAsync_message* message);

void add_patient_if_stack_empty(MQTTAsync_message *message);

bool patient_exists(Patient& p);

void update_or_add_patient(Patient& p);

void add_patient_if_stack_not_empty(MQTTAsync_message *message);

