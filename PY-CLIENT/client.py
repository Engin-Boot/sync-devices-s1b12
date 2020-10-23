import paho.mqtt.client as mqtt
import sys
import time
 
# class Pat:
#     def __init__(self, name):
#         self.name = name
Name = ""
Age = ""
Gender = ""
Procedure = ""
Consumables_used = ""
id_list = []
def on_subscribe(client, userdata, mid, granted_qos):
    client.subscribed = True
    print(f"Subscribed: {mid} {granted_qos}")
 
def on_publish(client,userdata,result):  
    client.published = True
    print(f"Published...")
 
def on_disconnect(client, userdata, rc):
    print("Disconnected")
 
def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connected... Returned code = ", rc)
    else:
        print("Bad connection Returned code = ", rc)
 
def on_message(client, userdata, msg):
    topic = msg.topic
    decoded_msg = str(msg.payload.decode("utf-8", "strict"))
    print(f"{topic} : {decoded_msg}")
    UnFlatten(decoded_msg)
    
 
def set_callbacks(client):
    client.on_connect = on_connect
    client.on_subscribe = on_subscribe
    client.on_publish = on_publish
    client.on_message = on_message
    client.on_disconnect = on_disconnect
 
def connect_client(host, port):
    try:
        client.connect(host=host, port=port, keepalive=60)
    except:
        print("Unable to connect")
        exit(1)
 
def wait_for_connection(client):
    while not client.is_connected():
        time.sleep(1)
 
def wait_for_subscription(client):
    while not client.subscribed:
        time.sleep(1)
 
def display_menu():
    print("1. Add a new patient")
    #print("2. Edit current patient data")
    print("2. View current patient data")
    print("3. View Patient Count")
    print("4. Exit")
 
def get_user_choice():
    choice = input()
    return choice

def add_patient():
    #msg = input("Enter a message to publish: ")
    print("add patient called\n")
    global Name
    Name = input("\n\tEnter patient name:  ")
    global Age 
    Age = input("\tEnter patient age: ")
    global Gender 
    Gender = input("\tEnter patient gender: ")
    global Procedure 
    Procedure = input("\tProcedure: ")
    global Consumables_used 
    Consumables_used = input("\tConsumables Used: ")
    s1 = "Client_1"+"|"+str(len(id_list))+"|"+Name+"|"+Age+"|"+Gender+"|"+Procedure+"|"+Consumables_used
    client.publish("MedicalDevice", s1)
    while not client.published:
        time.sleep(1)

