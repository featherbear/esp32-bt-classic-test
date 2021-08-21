#ifdef CORE_DEBUG_LEVEL
#undef CORE_DEBUG_LEVEL
#endif

#define CORE_DEBUG_LEVEL 5
#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE

#include <BluetoothSerial.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

#define BT_DISCOVER_TIME 10000

// static bool btScanAsync = true;
// static bool btScanSync = true;

char* str = NULL;

bool ready = false;
bool didConnect = false;
// void btAdvertisedDeviceFound(BTAdvertisedDevice* pDevice) {
//     Serial.printf("Found a device asynchronously: %s\n", pDevice->toString().c_str());
//     const char* s = pDevice->getAddress().toString().c_str();
//     str = strdup(s);
//     if (s[0] == '1' && s[1] == 'e') {
//         SerialBT.discoverAsyncStop();
//         ready = true;
//         // Serial.print("YE\n");
//         // SerialBT.connect(s);
//     }
// }
uint8_t address[6] = {0x1E, 0xD3, 0x1C, 0x80, 0x11, 0x80};

#include <Arduino.h>

void setup() {
    esp_log_level_set("*", ESP_LOG_VERBOSE);
    Serial.begin(9600);

    // SerialBT.enableSSP();

    SerialBT.begin("ESP32test", true);  //Bluetooth device name
    Serial.println("The device started, now you can pair it with bluetooth!");

    Serial.println("PIN");
    // SerialBT.setPin("1234");

    // // typedef std::function<void(boolean success)> AuthCompleteCb;
    // SerialBT.onAuthComplete([](bool success) {
    //     Serial.printf("Auth complete: %d\n", success);
    // });

    // // typedef std::function<void(uint32_t num_val)> ConfirmRequestCb;
    // SerialBT.onConfirmRequest([](uint32_t num_val) {
    //     Serial.printf("Confirm req");
    // });

    // // typedef std::function<void(const uint8_t *buffer, size_t size)> BluetoothSerialDataCb;
    // SerialBT.onData([](const uint8_t* buff, size_t a) {
    //     Serial.println("Data");
    // });

    // SerialBT.confirmReply()
    Serial.printf("Connect return %d\n", SerialBT.connect(address));
    while (!SerialBT.connected(10000)) {
        Serial.print(".");
    }
    Serial.print("connected!");

    // if (btScanAsync) {
    //     // Serial.print("Starting discoverAsync...");
    //     // if (SerialBT.discoverAsync(btAdvertisedDeviceFound)) {
    //     //     Serial.println("Findings will be reported in \"btAdvertisedDeviceFound\"");
    //     //     // SerialBT.discoverAsyncStop();
    //     //     // Serial.println("stopped");
    //     // } else {
    //     //     Serial.println("Error on discoverAsync f.e. not workin after a \"connect\"");
    //     // }
    // }
}
int i = 0;
void loop() {
    if (ready && !didConnect) {
        Serial.println("go!");

        didConnect = true;
        while (true) {
            Serial.printf("%u %d\n", i++, SerialBT.connected(1000));
        }
    }
}

/*
https://github.com/espressif/arduino-esp32/pull/3219

 - framework-arduinoespressif32 3.10006.210326 (1.0.6)
 - tool-esptoolpy 1.30100.210531 (3.1.0)
 - toolchain-xtensa32 2.50200.97 (5.2.0)

https://github.com/espressif/arduino-esp32/blob/master/libraries/BluetoothSerial/examples/SerialToSerialBTM/SerialToSerialBTM.ino

https://github.com/espressif/arduino-esp32/issues/3916#issuecomment-625486992

https://techtutorialsx.com/2017/07/08/esp32-bluetooth-using-the-btstack-library/
https://github.com/espressif/arduino-esp32/pull/4811
https://github.com/espressif/arduino-esp32#41c372c143a9585d67110782e735d80813f1889f


AT+CMODE=0 //set to connect only with specific address
AT+BIND= //address to be conected to

https://techtutorialsx.com/2017/07/08/esp32-bluetooth-using-the-btstack-library/


https://techtutorialsx.com/2017/07/09/esp32-bluetooth-finding-the-device-with-python-and-btstack/

https://www.youtube.com/watch?v=ACkTy9BXAww


    Setup HC-05
    Check for available nearby devices AT+IRQ
    Check the response to check is the desired device is enlisted in the nearby devices
    If device is enlisted, use AT+BIND=<Bluetooth address> to connect to the other device
    Check the response of the AT+STATE? command until you receive “CONNECTED” (you can go for a while loop here)
    Once the connection is successfully established here, you can send a confirmation now as per your requirement.


https://api.registry.platformio.org/v3/packages/platformio/tool/toolchain-xtensa32

*/