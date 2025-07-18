#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/spi/spidev.h>
#include <sys/ioctl.h>
#include <string.h>

#define SPI_DEVICE "/dev/spidev1.0"
#define SPI_MODE SPI_MODE_0
#define SPI_BITS 8
#define SPI_SPEED 1000000

int spi_fd;

uint8_t spi_transfer(uint8_t reg) {
    uint8_t tx[] = { reg, 0x00 };
    uint8_t rx[2] = { 0 };

    struct spi_ioc_transfer tr = {
        .tx_buf = (unsigned long)tx,
        .rx_buf = (unsigned long)rx,
        .len = 2,
        .speed_hz = SPI_SPEED,
        .bits_per_word = SPI_BITS,
    };

    ioctl(spi_fd, SPI_IOC_MESSAGE(1), &tr);
    return rx[1];
}

void read_calibration(uint16_t *dig_T1, int16_t *dig_T2, int16_t *dig_T3) {
    *dig_T1 = spi_transfer(0x88 | 0x80) | (spi_transfer(0x89 | 0x80) << 8);
    *dig_T2 = spi_transfer(0x8A | 0x80) | (spi_transfer(0x8B | 0x80) << 8);
    *dig_T3 = spi_transfer(0x8C | 0x80) | (spi_transfer(0x8D | 0x80) << 8);
}

int main() {
    spi_fd = open(SPI_DEVICE, O_RDWR);
    if (spi_fd < 0) {
        perror("Failed to open SPI device");
        return 1;
    }

    ioctl(spi_fd, SPI_IOC_WR_MODE, &SPI_MODE);
    ioctl(spi_fd, SPI_IOC_WR_BITS_PER_WORD, &SPI_BITS);
    ioctl(spi_fd, SPI_IOC_WR_MAX_SPEED_HZ, &SPI_SPEED);

    uint8_t chip_id = spi_transfer(0xD0 | 0x80);
    printf("BMP280 Chip ID: 0x%X\n", chip_id);

    uint16_t dig_T1;
    int16_t dig_T2, dig_T3;
    read_calibration(&dig_T1, &dig_T2, &dig_T3);

    printf("Calibration T1: %u, T2: %d, T3: %d\n", dig_T1, dig_T2, dig_T3);

    close(spi_fd);
    return 0;
}
