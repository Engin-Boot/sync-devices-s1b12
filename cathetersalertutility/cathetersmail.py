import paho.mqtt.client as mqtt
import sys
import time
import smtplib
# class Pat:
#     def __init__(self, name):
#         self.name = name
Name = ""
Age = ""
Gender = ""
Procedure = ""
Consumables_used = ""
id_list = []
cathethercount = 5

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
    global cathethercount
    topic = msg.topic
    decoded_msg = str(msg.payload.decode("utf-8", "strict"))
    print(f"{topic} : {decoded_msg}")
    UnFlatten(decoded_msg)
    if(cathethercount<4):
        s = smtplib.SMTP('smtp.gmail.com', 587) 
        s.starttls() 
        s.login("rachotibiradar007@gmail.com", "rachu1998") 
  
        # message to be sent 
        message = "Cathether count is low"
  
        # sending the mail 
        s.sendmail("rachotibiradar007@gmail.com", "rachubiradar007@gmail.com", message) 
  
        # terminating the session 
        s.quit() 
    
 
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

# def edit_patient_details():
#     print("1. Edit name")
#     print("2. Edit age")
#     print("3. Edit gender")
#     print("4. Edit procedure")
#     print("5. Edit consumables used")

def view_patient_details():
    print("\nPatient details: ")
    print("\n\tName: "+Name)
    print("\tAge: " +Age)
    print("\tGender: "+Gender)
    print("\tProcedure: "+Procedure)
    print("\tConsumables Used: "+Consumables_used)

def exit_function():
    print("Exiting application...")
    exit(0)

def view_patient_count():
    print("Patient Count is : "+str(len(id_list)))

def contains(id_list1,value):
    for i in range(len(id_list1)):
        if id_list1[i] == value:
            return 1
    return 0

def UnFlatten(str1):
    list1 = str1.split("|")
    global Name,Age,Gender,Procedure,Consumables_used
    global cathethercount
    Name = list1[2]
    Age = list1[3]
    Gender = list1[4]
    Procedure = list1[5]
    Consumables_used = list1[6]
    if(contains(id_list,int(list1[1])) == 0):
        id_list.append(int(list1[1]))
    if(Procedure == "cardiac"):
        cathethercount-=1

def main_application(client):
    while True:
        client.published = False
        display_menu()
        choice = get_user_choice()
        dict1 = {"1":add_patient,"2":view_patient_details,"3":view_patient_count,"4":exit_function}
        dict1[choice]()
            
        # elif choice == "2":
        #     print("Exiting application...")
        #     exit(0)
 
if __name__ == '__main__':
    # Create Client
    client = mqtt.Client("Client_1")
 
    # Set Callbacks
    set_callbacks(client)
 
    client.subscribed = False
    client.published = False
 
    host = "localhost"
    port = 1883
 
    connect_client(host, port)
 
    client.loop_start()
 
    wait_for_connection(client)
 
    client.subscribe("MedicalDevice")
 
    wait_for_subscription(client)
 
    main_application(client)
 
    client.loop_stop()
 
    client.disconnect()
