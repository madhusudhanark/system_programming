
#include <linux/module.h>
#include <linux/spi/spi.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/slab.h>

#define BMP280_REG_TEMP_MSB 0xFA
#define BMP280_REG_TEMP_LSB 0xFB
#define BMP280_REG_TEMP_XLSB 0xFC
#define BMP280_REG_CALIB_START 0x88
#define BMP280_CALIB_LEN 6

#define BMP280_IOCTL_GET_TEMP _IOR('b', 1, int)

struct bmp280_data {
    struct spi_device *spi;
    struct cdev cdev;
    dev_t devt;
    struct class *class;
    int t1, t2, t3;
    int temp;
};

static struct bmp280_data *bmp_data;

static int bmp280_spi_read(struct spi_device *spi, u8 reg, u8 *buf, int len) {
    u8 tx = reg | 0x80;
    struct spi_transfer t[] = {
        {
            .tx_buf = &tx,
            .len = 1,
        },
        {
            .rx_buf = buf,
            .len = len,
        }
    };
    struct spi_message m;
    spi_message_init(&m);
    spi_message_add_tail(&t[0], &m);
    spi_message_add_tail(&t[1], &m);
    return spi_sync(spi, &m);
}

static void bmp280_read_calib(struct bmp280_data *data) {
    u8 buf[BMP280_CALIB_LEN];
    bmp280_spi_read(data->spi, BMP280_REG_CALIB_START, buf, BMP280_CALIB_LEN);
    data->t1 = buf[1] << 8 | buf[0];
    data->t2 = (short)(buf[3] << 8 | buf[2]);
    data->t3 = (short)(buf[5] << 8 | buf[4]);
}

static void bmp280_read_temp(struct bmp280_data *data) {
    u8 buf[3];
    bmp280_spi_read(data->spi, BMP280_REG_TEMP_MSB, buf, 3);
    int adc_T = ((int)buf[0] << 12) | ((int)buf[1] << 4) | (buf[2] >> 4);

    int var1 = ((((adc_T >> 3) - (data->t1 << 1))) * (data->t2)) >> 11;
    int var2 = (((((adc_T >> 4) - (data->t1)) * ((adc_T >> 4) - (data->t1))) >> 12) * (data->t3)) >> 14;
    int t_fine = var1 + var2;
    data->temp = (t_fine * 5 + 128) >> 8;
}

static long bmp280_ioctl(struct file *file, unsigned int cmd, unsigned long arg) {
    if (cmd == BMP280_IOCTL_GET_TEMP) {
        bmp280_read_temp(bmp_data);
        return copy_to_user((int __user *)arg, &bmp_data->temp, sizeof(int)) ? -EFAULT : 0;
    }
    return -ENOTTY;
}

static int bmp280_open(struct inode *inode, struct file *file) {
    file->private_data = bmp_data;
    return 0;
}

static const struct file_operations bmp280_fops = {
    .owner = THIS_MODULE,
    .open = bmp280_open,
    .unlocked_ioctl = bmp280_ioctl,
};

static int bmp280_probe(struct spi_device *spi) {
    int ret;
    bmp_data = devm_kzalloc(&spi->dev, sizeof(*bmp_data), GFP_KERNEL);
    if (!bmp_data)
        return -ENOMEM;

    bmp_data->spi = spi;
    bmp280_read_calib(bmp_data);

    ret = alloc_chrdev_region(&bmp_data->devt, 0, 1, "bmp280");
    if (ret < 0)
        return ret;

    cdev_init(&bmp_data->cdev, &bmp280_fops);
    ret = cdev_add(&bmp_data->cdev, bmp_data->devt, 1);
    if (ret)
        goto unregister;

    bmp_data->class = class_create(THIS_MODULE, "bmp280");
    if (IS_ERR(bmp_data->class)) {
        ret = PTR_ERR(bmp_data->class);
        goto del_cdev;
    }

    device_create(bmp_data->class, NULL, bmp_data->devt, NULL, "bmp280");
    spi_set_drvdata(spi, bmp_data);
    return 0;

del_cdev:
    cdev_del(&bmp_data->cdev);
unregister:
    unregister_chrdev_region(bmp_data->devt, 1);
    return ret;
}

static int bmp280_remove(struct spi_device *spi) {
    device_destroy(bmp_data->class, bmp_data->devt);
    class_destroy(bmp_data->class);
    cdev_del(&bmp_data->cdev);
    unregister_chrdev_region(bmp_data->devt, 1);
    return 0;
}

static struct spi_driver bmp280_driver = {
    .driver = {
        .name = "bmp280",
        .owner = THIS_MODULE,
    },
    .probe = bmp280_probe,
    .remove = bmp280_remove,
};

module_spi_driver(bmp280_driver);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Copilot");
MODULE_DESCRIPTION("BMP280 SPI Driver with ioctl temperature access");
