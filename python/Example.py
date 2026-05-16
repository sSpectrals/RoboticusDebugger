import time
import serial # pip install pyserial
from RoboticusDebugger import RoboticusDebugger, Sensor, Vector

#    port = None for simple print
#    port = serial.Serial("COM3", 115200)        # Windows
#    port = serial.Serial("/dev/ttyUSB0", 115200) # Linux / macOS
port = None

debugger = RoboticusDebugger(output=port)

sensors = [
    # Circle Layer
    Sensor("IR_1",  23.5, ">=", 30.0, "Circle Layer",  10.00,  0.00),
    Sensor("IR_2",  18.2, "<=", 20.0, "Circle Layer",   9.66,  2.59),
    Sensor("IR_3",  31.7, ">",  28.0, "Circle Layer",   8.66,  5.00),
    Sensor("IR_4",  22.1, "<",  25.0, "Circle Layer",   7.07,  7.07),
    Sensor("IR_5",  23.5, "==", 30.0, "Circle Layer",   5.00,  8.66),
    Sensor("IR_6",  23.5, ">=", 30.0, "Circle Layer",   2.59,  9.66),
    Sensor("IR_7",  18.2, "<=", 20.0, "Circle Layer",   0.00, 10.00),
    Sensor("IR_8",  31.7, ">",  28.0, "Circle Layer",  -2.59,  9.66),
    Sensor("IR_9",  22.1, "<",  25.0, "Circle Layer",  -5.00,  8.66),
    Sensor("IR_10", 23.5, ">=", 30.0, "Circle Layer",  -7.07,  7.07),
    Sensor("IR_11", 23.5, ">=", 30.0, "Circle Layer",  -8.66,  5.00),
    Sensor("IR_12", 18.2, "<=", 20.0, "Circle Layer",  -9.66,  2.59),
    Sensor("IR_13", 31.7, ">",  28.0, "Circle Layer", -10.00,  0.00),
    Sensor("IR_14", 22.1, "<",  25.0, "Circle Layer",  -9.66, -2.59),
    Sensor("IR_15", 23.5, ">=", 30.0, "Circle Layer",  -8.66, -5.00),
    Sensor("IR_16", 23.5, ">=", 30.0, "Circle Layer",  -7.07, -7.07),
    Sensor("IR_17", 18.2, "<=", 20.0, "Circle Layer",  -5.00, -8.66),
    Sensor("IR_18", 31.7, ">",  28.0, "Circle Layer",  -2.59, -9.66),
    Sensor("IR_19", 22.1, "<",  25.0, "Circle Layer",   0.00,-10.00),
    Sensor("IR_20", 23.5, ">=", 30.0, "Circle Layer",   2.59, -9.66),
    Sensor("IR_21", 23.5, ">=", 30.0, "Circle Layer",   5.00, -8.66),
    Sensor("IR_22", 18.2, "<=", 20.0, "Circle Layer",   7.07, -7.07),
    Sensor("IR_23", 31.7, ">",  28.0, "Circle Layer",   8.66, -5.00),
    Sensor("IR_24", 22.1, "<",  25.0, "Circle Layer",   9.66, -2.59),
    # Right Arm
    Sensor("IR_25", 23.5, ">=", 30.0, "Right Arm",  13.0, 0.0),
    Sensor("IR_26", 18.2, "<=", 20.0, "Right Arm",  15.5, 0.0),
    Sensor("IR_27", 31.7, ">",  28.0, "Right Arm",  18.0, 0.0),
    Sensor("IR_28", 22.1, "<",  25.0, "Right Arm",  20.5, 0.0),
    # Left Arm
    Sensor("IR_29", 23.5, ">=", 30.0, "Left Arm", -13.0, 0.0),
    Sensor("IR_30", 18.2, "<=", 20.0, "Left Arm", -15.5, 0.0),
    Sensor("IR_31", 31.7, ">",  28.0, "Left Arm", -18.0, 0.0),
    Sensor("IR_32", 22.1, "<",  25.0, "Left Arm", -20.5, 0.0),
    # Top Arm
    Sensor("IR_33", 23.5, ">=", 30.0, "Top Arm", 0.0,  13.0),
    Sensor("IR_34", 18.2, "<=", 20.0, "Top Arm", 0.0,  15.5),
    Sensor("IR_35", 31.7, ">",  28.0, "Top Arm", 0.0,  18.0),
    Sensor("IR_36", 22.1, "<",  25.0, "Top Arm", 0.0,  20.5),
    # Bottom Arm
    Sensor("IR_37", 23.5, ">=", 30.0, "Bottom Arm", 0.0, -13.0),
    Sensor("IR_38", 18.2, "<=", 20.0, "Bottom Arm", 0.0, -15.5),
    Sensor("IR_39", 31.7, ">",  28.0, "Bottom Arm", 0.0, -18.0),
    Sensor("IR_40", 22.1, "<",  25.0, "Bottom Arm", 0.0, -20.5),
]

vectors = [
    Vector("Line avoidance",  45.0, "#FF5733", "Circle Layer",    -15, -15),
    Vector("Line tracker",    90.0, "#33FF57", "Right arm",        -18, -15),
    Vector("Ball",           135.0, "#3357FF", "whatever is left", -10, -15),
]


frame = 0

while True:


    # Emulate changes in sensor inputs
    frame += 1
    for s in sensors:
        if frame % 2 == 0:
            s.input = s.threshold + 1.0  # trigger
        else:
            s.input = s.threshold - 1.0  # not trigger

    # Rotate vectors
    vectors[0].rotation += 1.0
    vectors[1].rotation += 3.0
    vectors[2].rotation += 9.0

    # Add all sensors and vectors to the debugger
    for s in sensors:
        debugger.add(s)

    for v in vectors:
        debugger.add(v)

    debugger.write()  # Send the frame and clear for next frame
    time.sleep(0.1) 