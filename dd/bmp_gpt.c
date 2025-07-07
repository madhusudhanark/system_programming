// bmp280.c
//this driver does not expose device through dev , only temp is logged in dmesg//
#include <linux/module.h>
#include <linux/spi/spi.h>
#include <linux/delay.h>
#include <linux/slab.h>
#include <linux/of.h>

#define BMP280_CHIP_ID_REG     0xD0
#define BMP280_RESET_REG       0xE0
#define BMP280_CTRL_MEAS_REG   0xF4
#define BMP280_TEMP_MSB_REG    0xFA
#define BMP280_CALIB_DATA_START 0x88
#define BMP280_CALIB_DATA_LENGTH 24

struct bmp280_calib_param {
    u16 dig_T1;
    s16 dig_T2;
    s16 dig_T3;
};

struct bmp280_data {
    struct spi_device *spi;
    struct bmp280_calib_param calib;
    s32 t_fine;
};

static int bmp280_read_reg(struct spi_device *spi, u8 reg, u8 *val, int len)
{
    u8 tx_buf[1] = { reg | 0x80 };
    struct spi_transfer t[] = {
        {
            .tx_buf = tx_buf,
            .len = 1,
        },
        {
            .rx_buf = val,
            .len = len,
        },
    };

    return spi_sync_transfer(spi, t, 2);
}

static int bmp280_write_reg(struct spi_device *spi, u8 reg, u8 val)
{
    u8 buf[2] = { reg & 0x7F, val };
    struct spi_transfer t = {
        .tx_buf = buf,
        .len = 2,
    };

    return spi_sync_transfer(spi, &t, 1);
}

static int bmp280_read_calib_data(struct bmp280_data *data)
{
    u8 buf[BMP280_CALIB_DATA_LENGTH];
    int ret = bmp280_read_reg(data->spi, BMP280_CALIB_DATA_START, buf, BMP280_CALIB_DATA_LENGTH);
    if (ret < 0) return ret;

    data->calib.dig_T1 = buf[1] << 8 | buf[0];
    data->calib.dig_T2 = buf[3] << 8 | buf[2];
    data->calib.dig_T3 = buf[5] << 8 | buf[4];
    return 0;
}

static s32 bmp280_compensate_temp(struct bmp280_data *data, s32 adc_T)
{
    s32 var1, var2, T;
    var1 = ((((adc_T >> 3) - ((s32)data->calib.dig_T1 << 1))) *
           ((s32)data->calib.dig_T2)) >> 11;

    var2 = (((((adc_T >> 4) - ((s32)data->calib.dig_T1)) *
             ((adc_T >> 4) - ((s32)data->calib.dig_T1))) >> 12) *
           ((s32)data->calib.dig_T3)) >> 14;

    data->t_fine = var1 + var2;
    T = (data->t_fine * 5 + 128) >> 8;
    return T;
}

static int bmp280_probe(struct spi_device *spi)
{
    int ret;
    u8 chip_id;
    struct bmp280_data *data = devm_kzalloc(&spi->dev, sizeof(*data), GFP_KERNEL);
    if (!data)
        return -ENOMEM;

    data->spi = spi;
    spi_set_drvdata(spi, data);

    ret = bmp280_read_reg(spi, BMP280_CHIP_ID_REG, &chip_id, 1);
    if (ret < 0 || chip_id != 0x58) {
        dev_err(&spi->dev, "BMP280 not found or wrong chip ID: 0x%x\n", chip_id);
        return -ENODEV;
    }

    bmp280_write_reg(spi, BMP280_RESET_REG, 0xB6);
    msleep(100);

    ret = bmp280_read_calib_data(data);
    if (ret < 0)
        return ret;

    bmp280_write_reg(spi, BMP280_CTRL_MEAS_REG, 0x27); // normal mode, temp x1

    msleep(100);

    u8 raw_temp[3];
    bmp280_read_reg(spi, BMP280_TEMP_MSB_REG, raw_temp, 3);
    s32 adc_T = (raw_temp[0] << 12) | (raw_temp[1] << 4) | (raw_temp[2] >> 4);

    s32 temp = bmp280_compensate_temp(data, adc_T);
    dev_info(&spi->dev, "Calibrated temperature: %d.%02d °C\n", temp / 100, temp % 100);

    return 0;
}

static int bmp280_remove(struct spi_device *spi)
{
    dev_info(&spi->dev, "BMP280 removed\n");
    return 0;
}

static const struct of_device_id bmp280_of_match[] = {
    { .compatible = "bosch,bmp280" },
    { }
};
MODULE_DEVICE_TABLE(of, bmp280_of_match);

static struct spi_driver bmp280_driver = {
    .driver = {
        .name = "bmp280",
        .of_match_table = bmp280_of_match,
    },
    .probe = bmp280_probe,
    .remove = bmp280_remove,
};
module_spi_driver(bmp280_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ChatGPT");
MODULE_DESCRIPTION("BMP280 SPI Temperature Sensor Driver");
