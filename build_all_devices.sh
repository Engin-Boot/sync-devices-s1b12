mkdir bin

# CT
g++ DEVICES/CT/*.cpp Patient/*.cpp -o ./bin/CT_CLIENT -lpaho-mqtt3as

# ULTRASOUND
g++ DEVICES/ULTRASOUND/*.cpp Patient/*.cpp -o ./bin/ULTRASOUND_CLIENT -lpaho-mqtt3as

# X-RAY
g++ DEVICES/XRAY/*.cpp Patient/*.cpp -o ./bin/XRAY_CLIENT -lpaho-mqtt3as