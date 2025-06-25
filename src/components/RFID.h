#ifndef RFID_H
#define RFID_H





#define RST_PIN 6 // WiringPi pin 6 = BCM 25 = Physical pin 22

#define MAX_LEN 16



#define CommandReg         0x01
#define CommIEnReg         0x02
#define CommIrqReg         0x04
#define FIFOLevelReg       0x0A
#define FIFODataReg        0x09
#define ControlReg         0x0C
#define BitFramingReg      0x0D
#define ErrorReg           0x06
#define Status2Reg         0x08
#define ModeReg            0x11
#define TxControlReg       0x14
#define TModeReg           0x2A
#define TPrescalerReg      0x2B
#define TReloadRegH        0x2C
#define TReloadRegL        0x2D
#define VersionReg         0x37

#define PCD_IDLE           0x00
#define PCD_TRANSCEIVE     0x0C
#define PICC_REQIDL        0x26
#define PICC_ANTICOLL      0x93





void RunRFID_Test();

#endif