#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <linux/spi/spidev.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <wiringPi.h>


#include "RFID.h"




static const char *spi_device = "/dev/spidev0.0";
static uint8_t spi_mode = 0;
static uint8_t spi_bits = 8;
static uint32_t spi_speed = 1000000;
static int spi_fd = -1;



void spi_write(uint8_t reg, uint8_t val)
{
    uint8_t buf[2];
    buf[0] = ((reg << 1) & 0x7E);
    buf[1] = val;
    write(spi_fd, buf, 2);
}

uint8_t spi_read(uint8_t reg)
{
    uint8_t tx[2], rx[2];
    tx[0] = ((reg << 1) & 0x7E) | 0x80;
    tx[1] = 0;
    struct spi_ioc_transfer tr =
    {
        .tx_buf = (unsigned long)tx,
        .rx_buf = (unsigned long)rx,
        .len = 2,
        .speed_hz = spi_speed,
        .bits_per_word = spi_bits,
    };
    ioctl(spi_fd, SPI_IOC_MESSAGE(1), &tr);
    return rx[1];
}

void mfrc522_reset()
{
    spi_write(CommandReg, 0x0F);
}

void mfrc522_init()
{
    mfrc522_reset();
    spi_write(TModeReg, 0x8D);
    spi_write(TPrescalerReg, 0x3E);
    spi_write(TReloadRegL, 30);
    spi_write(TReloadRegH, 0);
    spi_write(TxControlReg, 0x83);
    spi_write(ModeReg, 0x3D);
}

void mfrc522_antenna_on()
{
    uint8_t temp = spi_read(TxControlReg);
    if(!(temp & 0x03))
    {
        spi_write(TxControlReg, temp | 0x03);
    }
}

int mfrc522_request(uint8_t req_mode, uint8_t *tag_type)
{
    spi_write(BitFramingReg, 0x07);
    spi_write(CommandReg, PCD_IDLE);
    spi_write(FIFOLevelReg, 0x80);
    spi_write(FIFODataReg, req_mode);
    spi_write(CommandReg, PCD_TRANSCEIVE);
    spi_write(BitFramingReg, 0x87);

    usleep(1000);

    uint8_t irq = spi_read(CommIrqReg);
    if(!(irq & 0x30)) return 0;

    uint8_t error = spi_read(ErrorReg);
    if(error & 0x1B) return 0;

    int n = spi_read(FIFOLevelReg);
    if(n == 2)
    {
        tag_type[0] = spi_read(FIFODataReg);
        tag_type[1] = spi_read(FIFODataReg);
        return 1;
    }
    return 0;
}

int mfrc522_anticoll(uint8_t *ser_num)
{
    spi_write(BitFramingReg, 0x00);
    spi_write(CommandReg, PCD_IDLE);
    spi_write(FIFOLevelReg, 0x80);
    spi_write(FIFODataReg, PICC_ANTICOLL);
    spi_write(FIFODataReg, 0x20);
    spi_write(CommandReg, PCD_TRANSCEIVE);
    spi_write(BitFramingReg, 0x80);

    usleep(1000);

    uint8_t irq = spi_read(CommIrqReg);
    if (!(irq & 0x30)) return 0;

    uint8_t error = spi_read(ErrorReg);
    if(error & 0x1B) return 0;

    int n = spi_read(FIFOLevelReg);
    if(n == 5)
    {
        for(int i = 0; i < 5; i++)
        {
            ser_num[i] = spi_read(FIFODataReg);
        }
        return 1;
    }
    return 0;
}

void RunRFID_Test()
{
    //Todo
}