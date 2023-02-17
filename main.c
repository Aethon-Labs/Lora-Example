#include <lmic.h>
#include <hal/hal.h>

// Device address (MSB)
static const u4_t DEVADDR = 0x12345678;

// Network session key (MSB)
static const PROGMEM u1_t NWKSKEY[16] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10 };

// Application session key (MSB)
static const PROGMEM u1_t APPSKEY[16] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10 };

// LoRaWAN channel frequency (in Hz)
#define CHANNEL_FREQUENCY 868100000

// LoRaWAN channel data rate
#define CHANNEL_DATARATE DR_SF7

// LoRaWAN transmit power (in dBm)
#define TX_POWER 14

// LoRaWAN message payload
static const char MESSAGE[] = "Hello, World!";

void os_getArtEui (u1_t* buf) {
    // Not used by RN2483
}

void os_getDevEui (u1_t* buf) {
    // Not used by RN2483
}

void os_getDevKey (u1_t* buf) {
    // Not used by RN2483
}

void onEvent (ev_t ev) {
    switch (ev) {
        case EV_TXCOMPLETE:
            Serial.println("Transmission complete");
            break;
        case EV_RXCOMPLETE:
            Serial.println("Reception complete");
            break;
        default:
            break;
    }
}

void setup() {
    Serial.begin(9600);
    Serial.println("LoRaWAN node starting up");

    // Initialize LoRaWAN stack
    os_init();

    // Set LoRaWAN channel parameters
    LMIC_setupChannel(0, CHANNEL_FREQUENCY, CHANNEL_DATARATE);

    // Set LoRaWAN transmit power
    LMIC_setDrTxpow(CHANNEL_DATARATE, TX_POWER);

    // Set LoRaWAN device address, network session key, and application session key
    LMIC_setSession(0x1, DEVADDR, NWKSKEY, APPSKEY);

    // Set LoRaWAN data rate adaptation mode
    LMIC_setAdrMode(1);

    // Set LoRaWAN link check mode
    LMIC_setLinkCheckMode(1);

    // Enable LoRaWAN automatic data rate adaptation
    LMIC_setAutoDataRate(1, 0);

    // Disable LoRaWAN channel hopping
    LMIC_disableChannelHop(0);

    // Set up LoRaWAN event handler
    LMIC_setEventCallback(onEvent);
}
/*
 * loop() function that is repeatedly executed in the program. It first checks if a LoRaWAN transmission is already in progress using the OP_TXRXPEND flag. If a transmission is in progress, the function skips the current loop iteration and returns.

If LoRaWAN is ready to transmit, the function prepares a message containing the string "Hello, World!" and sends it using the LMIC_setTxData2 function. The message is then scheduled to be sent again in 1 minute, and the program waits for the specified delay period before sending the next message.
**/

void loop() {
    // Check if LoRaWAN is ready to transmit
    if (LMIC.opmode & OP_TXRXPEND) {
        Serial.println("Transmission in progress, skipping loop iteration");
        return;

        // Prepare LoRaWAN message
        LMIC.frame[0] = strlen(MESSAGE);
        memcpy(LMIC.frame + 1, MESSAGE, strlen(MESSAGE));
        LMIC_setTxData2(1, LMIC.frame, strlen(MESSAGE) + 1, 0);

        Serial.println("LoRaWAN transmission scheduled");
        delay(60000); // Wait 1 minute before sending next message
    }
}

