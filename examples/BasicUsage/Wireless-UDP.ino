#include <WiFi.h>
#include <WiFiUdp.h>
#include <RoboticusDebugger.h>

const char* WIFI_SSID = "YourWifiSSID";
const char* WIFI_PASS = "YourWifiPass";

WiFiUDP udp;
RoboticusDebugger debugger(udp);

IPAddress targetIp(255, 255, 255, 255);
const uint16_t targetPort = 8080;


// Create arrays of sensors  ||  name | input | operatorStr | threshold | x | y
Sensor sensors[] = {
    // Circle
    {"Phototransistor_1", 23.5, ">=", 30.0, "Circle Layer", 10.00, 0.00},
    {"Phototransistor_2", 18.2, "<=", 20.0, "Circle Layer", 9.66, 2.59},
    {"Phototransistor_3", 31.7, ">", 28.0, "Circle Layer", 8.66, 5.00},
    {"Phototransistor_4", 22.1, "<", 25.0, "Circle Layer", 7.07, 7.07},
    {"Phototransistor_5", 23.5, "==", 30.0, "Circle Layer", 5.00, 8.66},
    {"Phototransistor_6", 23.5, ">=", 30.0, "Circle Layer", 2.59, 9.66},
    {"Phototransistor_7", 18.2, "<=", 20.0, "Circle Layer", 0.00, 10.00},
    {"Phototransistor_8", 31.7, ">", 28.0, "Circle Layer", -2.59, 9.66},
    {"Phototransistor_9", 22.1, "<", 25.0, "Circle Layer", -5.00, 8.66},
    {"Phototransistor_10", 23.5, ">=", 30.0, "Circle Layer", -7.07, 7.07},
    {"Phototransistor_11", 23.5, ">=", 30.0, "Circle Layer", -8.66, 5.00},
    {"Phototransistor_12", 18.2, "<=", 20.0, "Circle Layer", -9.66, 2.59},
    {"Phototransistor_13", 31.7, ">", 28.0, "Circle Layer", -10.00, 0.00},
    {"Phototransistor_14", 22.1, "<", 25.0, "Circle Layer", -9.66, -2.59},
    {"Phototransistor_15", 23.5, ">=", 30.0, "Circle Layer", -8.66, -5.00},
    {"Phototransistor_16", 23.5, ">=", 30.0, "Circle Layer", -7.07, -7.07},
    {"Phototransistor_17", 18.2, "<=", 20.0, "Circle Layer", -5.00, -8.66},
    {"Phototransistor_18", 31.7, ">", 28.0, "Circle Layer", -2.59, -9.66},
    {"Phototransistor_19", 22.1, "<", 25.0, "Circle Layer", 0.00, -10.00},
    {"Phototransistor_20", 23.5, ">=", 30.0, "Circle Layer", 2.59, -9.66},
    {"Phototransistor_21", 23.5, ">=", 30.0, "Circle Layer", 5.00, -8.66},
    {"Phototransistor_22", 18.2, "<=", 20.0, "Circle Layer", 7.07, -7.07},
    {"Phototransistor_23", 31.7, ">", 28.0, "Circle Layer", 8.66, -5.00},
    {"Phototransistor_24", 22.1, "<", 25.0, "Circle Layer", 9.66, -2.59},

    // Right arm
    {"Phototransistor_25", 23.5, ">=", 30.0, "Right Arm", 13.0, 0.0},
    {"Phototransistor_26", 18.2, "<=", 20.0, "Right Arm", 15.5, 0.0},
    {"Phototransistor_27", 31.7, ">", 28.0, "Right Arm", 18.0, 0.0},
    {"Phototransistor_28", 22.1, "<", 25.0, "Right Arm", 20.5, 0.0},

    // Left arm
    {"Phototransistor_29", 23.5, ">=", 30.0, "Left Arm", -13.0, 0.0},
    {"Phototransistor_30", 18.2, "<=", 20.0, "Left Arm", -15.5, 0.0},
    {"Phototransistor_31", 31.7, ">", 28.0, "Left Arm", -18.0, 0.0},
    {"Phototransistor_32", 22.1, "<", 25.0, "Left Arm", -20.5, 0.0},

    // Top arm
    {"Phototransistor_33", 23.5, ">=", 30.0, "Top Arm", 0.0, 13.0},
    {"Phototransistor_34", 18.2, "<=", 20.0, "Top Arm", 0.0, 15.5},
    {"Phototransistor_35", 31.7, ">", 28.0, "Top Arm", 0.0, 18.0},
    {"Phototransistor_36", 22.1, "<", 25.0, "Top Arm", 0.0, 20.5},

    // Bottom arm
    {"Phototransistor_37", 23.5, ">=", 30.0, "Bottom Arm", 0.0, -13.0},
    {"Phototransistor_38", 18.2, "<=", 20.0, "Bottom Arm", 0.0, -15.5},
    {"Phototransistor_39", 31.7, ">", 28.0, "Bottom Arm", 0.0, -18.0},
    {"Phototransistor_40", 22.1, "<", 25.0, "Bottom Arm", 0.0, -20.5}};

// Create arrays of vectors
Vector vectors[] = {
    {"Line avoidance", 45.0, "#FF5733", "Layer1", -15, -15},
    {"Line tracker", 90.0, "#33FF57", "Layer1", -18, -15},
    {"Ball", 135.0, "#3357FF", "Layer1", -10, -15}};

const int numSensors = sizeof(sensors) / sizeof(sensors[0]);
const int numVectors = sizeof(vectors) / sizeof(vectors[0]);

void setup() {
    Serial.begin(9600);
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    Serial.println("connecting...");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(300);
    };
    udp.begin(1234);
}

int frame = 0;
void loop() {
    // emulating changes in sensor inputs and vector rotations for demonstration
    // purposes
    frame++;
    for (int i = 0; i < numSensors; i++) {
        if (frame % 2 == 0) {
        sensors[i].input = sensors[i].threshold + 1.0; // trigger
        } else {
        sensors[i].input = sensors[i].threshold - 1.0; // not trigger
        }
    }
    vectors[0].rotation += 1.0;
    vectors[1].rotation += 3.0;
    vectors[2].rotation += 9.0;

    for (int i = 0; i < numSensors; i++) debugger.add(sensors[i]);
    for (int i = 0; i < numVectors; i++) debugger.add(vectors[i]);

    udp.beginPacket(targetIp, targetPort);
    debugger.write();
    udp.endPacket();

    delay(100);
}