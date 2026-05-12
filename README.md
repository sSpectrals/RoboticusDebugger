# Roboticus Debugger

[![Arduino Library](https://img.shields.io/badge/Arduino-Library-blue)](https://www.arduino.cc/reference/en/libraries/roboticus-debugger/)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/your-username/library/roboticus-debugger.svg)](https://registry.platformio.org/libraries/your-username/roboticus-debugger)
[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)

An Arduino library for sending sensor and vector data to the **Roboticus Data Visualiser** desktop application — visualize your robot's sensors and state vectors in real-time.

## ‼️ This library is meant to be used with the Roboticus Debugger application
The repository can be found here: https://github.com/sSpectrals/Roboticus-Data-Visualiser

## ✨ Features

- 📡 Send **sensor** data (name, value, operator, threshold, position)
- 🧭 Send **vector** data (name, rotation angle, color, layer, position)
- 🎯 Real‑time visualization of data with the Roboticus Data Visualiser app

## 📦 Installation

### Arduino IDE (Library Manager)
1. Open **Sketch** → **Include Library** → **Manage Libraries**
2. Search for `"Roboticus Debugger"`
3. Click **Install**

### PlatformIO (Library Registry)
```ini
lib_deps =
    sspectrals/Roboticus Debugger @ ^1.0.0
