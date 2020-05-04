/*
  HM1X Bluetooth SoftwareSerial Configure Device
  Updated Support for HM1X devices 
  By: Niel Cansino
  Date: May 4, 2020
  License: This code is public domain but you buy me a beer 
  if you use this and we meet someday (Beerware license).

  Demonstrates how to configure the HM-19's BLE name,
  and how to reset the module. 
  Demonstrates the library's support for:
  - bleAddress(), 
  - bleAddress()
  - lastBleAddress()
  - clearBleConnected()
  - getBleMode(), setBleMode()
  - getBlePin(), setBlePin()
  Also prints out BLE addresses (not configurable).

  Works well with a DSD-Tech HM-19 board -- 
  connecting via software serial (D3, D4)

  Hardware Connections:
  DSD-Tech HM-19 ------------------- Arduino Uno
       GND ----------------------------- GND
       3.3V ---------------------------- 5V
       TX ------------------------------ 3
       RX ------------------------------ 4
*/

// Use Library Manager or download here: https://github.com/sparkfun/SparkFun_HM1X_Bluetooth_Arduino_Library
#include <SparkFun_HM1X_Bluetooth_Arduino_Library.h>
#include <SoftwareSerial.h>

// Do not forget to initialize the class with the HM-1X model type
// in this sketch it is HM19
HM1X_BT bt(HM1X_BT::HM19);

SoftwareSerial btSerial(3, 4);

// BLE and EDR device names
String edrName = "MyEDR";
String bleName = "MyBLE";
String existingName;

void setup() {
  Serial.begin(9600); // Serial debug port @ 9600 bps

  // bt.begin --
  // in this case takes a SoftwareSerial connection and
  // a desired serial baud rate.
  // Returns true on success
  if (bt.begin(btSerial, 9600) == false) {
    Serial.println(F("Failed to connect to the HM-13."));
    while (1) ;
  }
  boolean setName = false;
  Serial.println("Ready to Bluetooth!");

  boolean resetRequired = false; // Reset is required on name change

  // 1: Device Name  
  // getEdrName returns a string containing EDR device name
  // This should fail for HM-19
  existingName = bt.getEdrName(); // fetch existing name first
  if (existingName != edrName) {
    Serial.print("Setting new EDR name (currently ");
    Serial.print(existingName);
    Serial.println(")");
    // Set EDR device name
    if (bt.setEdrName(edrName) == HM1X_SUCCESS) {
      Serial.println("Set EDR name");
      setName = true;
      resetRequired = true;
    }else{
      Serial.println("Setting EDR name failed");
    }
  }
  
  // getBleName returns a string containing BLE device name
  // This should work for HM-19
  existingName = bt.getBleName(); // fetch existing name first
  if (existingName != bleName) {
    Serial.print("Setting new BLE name (currently ");
    Serial.print(existingName);
    Serial.println(")");
    // Set BLE device name
    if (bt.setBleName(bleName) == HM1X_SUCCESS) {
      Serial.println("Set BLE name to " + bleName);
      resetRequired = true;
    }else{
      Serial.println("Setting BLE name failed");
    }
  } else {
    Serial.println("BLE name is: " + bleName);
  }

  // 2: Device Address  
  Serial.println("EDR address: " + bt.edrAddress());  // should not return anything
  Serial.println("BLE address: " + bt.bleAddress());  // should return the BLE address

  char* lastAddress = (char *) calloc(22, sizeof(char));
  if (bt.lastBleAddress(lastAddress) == HM1X_SUCCESS){
    Serial.println("last BLE address: " + String(lastAddress));
  }
  free(lastAddress);

  // clear last connected
  if (bt.clearBleConnected() == HM1X_SUCCESS){
    Serial.println("last BLE Address cleared!");  
  }

  // 3: Mode
  // get BLE mode
  HM1X_BT::HM1X_ble_mode_t mode;
  if (bt.getBleMode(&mode) == HM1X_SUCCESS){
    Serial.print("BLE mode before: ");
    Serial.println(mode);  
  }

  // set BLE mode
  mode = (HM1X_BT::HM1X_ble_mode_t)1;
  if (bt.setBleMode(mode) == HM1X_SUCCESS){
    Serial.print("changing... ");
    Serial.println(mode);  
  }

  // get BLE mode again
  if (bt.getBleMode(&mode) == HM1X_SUCCESS){
    Serial.print("BLE mode after: ");
    Serial.println(mode);  
  }

  // 4: Pin
  // get BLE pin
  char* pin = (char *) calloc(6, sizeof(char));
  if (bt.getBlePin(pin) == HM1X_SUCCESS){
    Serial.print("Current BLE Pin: ");
    Serial.println(pin);  
  }

  // set BLE pin to an arbitrary PIN
  strcpy(pin, "784923");
  if (bt.setBlePin(pin) == HM1X_SUCCESS){
    Serial.print("changing... ");
    Serial.println(mode);  
  }

  // get BLE pin again
  if (bt.getBlePin(pin) == HM1X_SUCCESS){
    Serial.print("New BLE Pin: ");
    Serial.println(pin);  
  }
  
  if (resetRequired) {
    Serial.println("Resetting BT module. Wait a few seconds.");
    bt.reset();
  }
}

void loop() {
  if (bt.available()) {
    Serial.write((char) bt.read());
  }
  if (Serial.available()) {
    bt.write((char) Serial.read());
  } 
}
