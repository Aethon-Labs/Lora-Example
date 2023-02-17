#ifndef _lmic_h_
#define _lmic_h_

#ifdef __cplusplus
extern "C"{
#endif

// LMIC version
#define LMIC_VERSION_MAJOR 1
#define LMIC_VERSION_MINOR 7
#define LMIC_VERSION_BUILD 0
#define LMIC_VERSION_BUILD_LONG 0x00010700

// Radio type enumeration
enum {  // radio type
    RADIO_Unknown,
    RADIO_SX1276,
    RADIO_SX1272,
    RADIO_SX1278
};

// Bandwidth enumeration
enum {  // bandwidth and data rate indexes
    BW125 = 0,
    BW250,
    BW500
};

// Data rate enumeration
enum {  // bandwidth and data rate indexes
    DR_SF7 = 0,
    DR_SF8,
    DR_SF9,
    DR_SF10,
    DR_SF11,
    DR_SF12
};

// TX power enumeration
enum {  // tx power indexes
    TX_POWER_14 = 0,
    TX_POWER_11,
    TX_POWER_8,
    TX_POWER_5,
    TX_POWER_2,
    TX_POWER_MINUS_1,
    TX_POWER_MINUS_4,
    TX_POWER_MINUS_7,
    TX_POWER_MIN
};

// LMIC maximum frame length
#define LMIC_FRAME_MAXLEN 64

// LMIC maximum number of channels
#define MAX_CHANNELS 72

// LMIC event types
enum {
    EV_SCAN_TIMEOUT = 1,
    EV_BEACON_FOUND,
    EV_BEACON_MISSED,
    EV_BEACON_TRACKED,
    EV_JOINING,
    EV_JOINED,
    EV_RFU1,
    EV_JOIN_FAILED,
    EV_REJOIN_FAILED,
    EV_TXCOMPLETE,
    EV_LOST_TSYNC,
    EV_RESET,
    EV_RXCOMPLETE,
    EV_LINK_DEAD,
    EV_LINK_ALIVE,
    EV_SCAN_FOUND,
    EV_TXSTART,
    EV_TXCANCELED,
    EV_RXSTART,
    EV_JOIN_TXCOMPLETE
};

// LMIC event callback function type
typedef void (*lmic_event_callback_t)(u1_t ev);

// LoRaWAN MAC state
typedef struct {
    u4_t netid;         // network identifier (32 bits)
    u4_t devaddr;       // device address (32 bits)
    u1_t nwkKey[16];    // network session key (128 bits)
    u1_t artKey[16];    // application router session key (128 bits)
    u1_t appKey[16];    // application session key (128 bits)
    u4_t seqnoDn;       // downlink sequence number
    u4_t seqnoUp;       // uplink sequence number
    u4_t dnConf;        // confirmed downlink bitmap (32 bits)
    u2_t adrTxPow;      // TX power limit
    s1_t rssi;          // last gateway RSSI (dBm)
    s1_t snr;           // last gateway SNR (dB)
    s1_t rssi_cal;      // RSSI calibration offset
    u1_t margin;        // link margin (dB)
    u1_t devNonce[2];   // device nonce (16 bits)
    u1_t artEui[8];     // application router EUI (64 bits)
    u1_t devEui[8];     // device EUI (64 bits)
    u1_t joinNonce[3];  // join nonce (24 bits)
} lmic_t;

// Function declarations
void os_init();
void os_runloop();
void os_setCallback(u
void os_radio(RADIO r);
void os_getDevEui(u1_t *buf);
void os_getArtEui(u1_t *buf);
void os_getDevKey(u1_t *buf);
void os_setSeqnoUp(u4_t seq);
void os_setSeqnoDn(u4_t seq);
void os_setTxPower(s1_t power);
void os_radioTx(fcnt_t cnt, u1_t dataLen);
void os_radioRx();
void os_initRadio(RADIO r);
void os_clearMem(void *p, size_t n);

// LMIC state
extern lmic_t LMIC;

// LMIC function declarations
void LMIC_reset();
void LMIC_setupChannel(u1_t ch, u4_t freq, u2_t drmap, s1_t band);
void LMIC_disableChannel(u1_t channel);
void LMIC_setDrTxpow(u1_t dr, s1_t txpow);
void LMIC_setLinkCheckMode(u1_t mode);
void LMIC_setClockError(u1_t error);
void LMIC_shutdown();
void LMIC_startJoining();
void LMIC_tryRejoin();
void LMIC_cancelJoin();
void LMIC_setSession(u4_t netid, u4_t devaddr, const u1_t *nwkKey, const u1_t *artKey);
void LMIC_startJoining();
void LMIC_setAdrMode(u1_t enabled);
void LMIC_setDrTxpow(u1_t dr, s1_t txpow);
void LMIC_sendAlive();
void LMIC_sendAliveCheck();
void LMIC_setLinkCheckMode(u1_t mode);
u1_t LMIC_scheduleTx(u1_t port, u2_t flags, u1_t dataLen, u1_t *data);
void LMIC_setRx2Parameter(u4_t freq, u1_t dr);
void LMIC_setTxData2(u1_t port, xref2u1_t data, u1_t dlen, u1_t confirmed);
void LMIC_setLinkCheckLimit(u8_t n);
void LMIC_init();
void LMIC_shutdown();
u4_t LMIC_rnd4u4();
u1_t LMIC_fifobyte(u2_t i);
void LMIC_clrTxData();
void LMIC_rxenable(u1_t delay, u1_t irqmask, u1_t i);
void LMIC_setSession(u4_t netid, u4_t devaddr, const u1_t *nwkKey, const u1_t *artKey);
void LMIC_setLinkCheckMode(u1_t mode);
void LMIC_setClockError(u1_t error);
void LMIC_getDevEui(u1_t *buf);
void LMIC_getArtEui(u1_t *buf);
void LMIC_getSessionKeys(u1_t *buf);
u1_t LMIC_startJoining();
u1_t LMIC_tryRejoin();
void LMIC_cancelJoin();
u1_t LMIC_setTxData(u1_t port, xref2u1_t data, u1_t dlen, u1_t confirmed);
u1_t LMIC_setTxData2(u1_t port, xref2u1_t data, u1_t dlen, u1_t confirmed);
u1_t LMIC_setTxData2(u1_t port, xref2u1_t data, u1_t dlen, u1_t confirmed);
u1_t LMIC_sendAlive(u1_t *p);
u1_t LMIC_dequeueTxPacket(u1_t port, xref2u1_t data, u1_t *alen);
u2_t LMICe_at_tx(const char *s, xref2u1_t txdata, u1_t txlen, xref2u1_t rxdata, u2_t rxsize);
u2_t LMICe_at(const char *s, xref2u1_t buf, u2_t buflen);
u1_t LMICe_sendSolicited(u1_t port, xref2u1_t data, u1_t dlen);
void LMIC_setDrJoin(u1_t dr);
u2_t LMICbandplan_txDoneTime(oslmic_time_t timestamp, u1_t dr, u1_t payloadLen);
u1_t LMICbandplan_isValidBeacon1(const u1_t *d, u2_t s);
void LMICbandplan_setBcnRxParams(void);
void LMICbandplan_setPingableChannel(u1_t chpage, u1_t ch);
void LMICbandplan_setTxParams(u1_t pwr, u1_t opt);
u4_t LMICbandplan_convFreq(xref2u1_t ptr);
u1_t LMICbandplan_convDr(u1_t dr);
u1_t LMICbandplan_nextDr(u1_t dr);
u1_t LMICbandplan_maxFrameLen(u1_t dr);
void LMICbandplan_init(void);

// Radio function declarations
void radio_init();
void radio_irq_handler();
void radio_starttx();
void radio_timer_init(void);
void radio_reset(void);
void radio_txrxTimeout(void);

// Function declarations for AES crypto
void os_aes(AES_ENC_DEC mode, xref2u1_t buf, u2_t len);

// LoraMac function declarations
void lorawan_init(void);
void lorawan_reset(void);
u1_t lorawan_join(void);
u1_t lorawan_send(u1_t port, xref2u1_t data, u1_t len, u1_t confirmed);
void lorawan_sleep(void);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _lmic_h_

