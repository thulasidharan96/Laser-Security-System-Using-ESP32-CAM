# Laser Security System using ESP32-CAM and Blynk

## Overview
This repository contains the code and resources for a Laser Security System built using ESP32-CAM and Blynk. The system uses a laser and a light sensor to detect intrusions. When an intrusion is detected, the ESP32-CAM takes a photo of the intruder and sends an alert along with the photo to your phone via the Blynk app.

## Features
- Real-time intrusion detection
- Intruder photo capture with ESP32-CAM
- Alerts and photos sent to your phone using Blynk
- Easy to set up and use

## Hardware Requirements
- ESP32-CAM module
- Laser module
- Light-dependent resistor (LDR)
- Buzzer (optional)

## Software Requirements
- Arduino IDE
- Blynk app on your smartphone

## Setup
1. Connect the hardware as per the circuit diagram.
2. Open the Arduino IDE and install the ESP32 board and Blynk library.
3. Load the provided Arduino sketch onto your ESP32-CAM.
4. Open the Blynk app and set up a new project. Use the provided auth token in your Arduino sketch.
5. Run the Blynk project and power up your ESP32-CAM.

## Usage
Once the system is set up, it will start monitoring the light level on the LDR. If the laser beam is interrupted, the light level will drop, the system will take a photo with the ESP32-CAM, and send an alert along with the photo to your phone via Blynk.

## Contributing
Contributions are welcome! Please read the contributing guidelines before making any changes.

## License
This project is licensed under the MIT License. See the LICENSE file for details.
