//the device driver ulike previous exposes through char driver file to userspace


#include <linux/module.h>
#include <linux/spi/spi.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "bmp280"
#define CLASS_NAME "bmp280_class"

static struct spi_device *bmp280_spi_device;
static dev_t dev_num;
static struct class *bmp280_class;
static struct cdev bmp280_cdev;

static s32 bmp280_spi_read_reg(u8 reg)
{
    u8 tx_buf[2] = { reg | 0x80, 0x00 };  // Set MSB for read
    u8 rx_buf[2] = { 0 };
    struct spi_transfer t[] = {
        {
            .tx_buf = tx_buf,
            .rx_buf = rx_buf,
            .len = 2,
        },
    };
    spi_sync_transfer(bmp280_spi_device, t, 1);
    return rx_buf[1];
}

static s32 bmp280_read_temperature(void)
{
    s32 msb = bmp280_spi_read_reg(0xFA);
    s32 lsb = bmp280_spi_read_reg(0xFB);
    s32 xlsb = bmp280_spi_read_reg(0xFC);
    s32 adc_T = ((msb << 16) | (lsb << 8) | xlsb) >> 4;
    return adc_T;  // Not yet calibrated
}

// Optional: Add your calibration algorithm for real °C

static ssize_t bmp280_read(struct file *file, char __user *buf, size_t len, loff_t *offset)
{
    s32 raw_temp = bmp280_read_temperature();
    char temp_str[32];
    int size = snprintf(temp_str, sizeof(temp_str), "Raw Temp: %d\n", raw_temp);
    return copy_to_user(buf, temp_str, size) ? -EFAULT : size;
}

static ssize_t bmp280_write(struct file *file, const char __user *buf, size_t len, loff_t *offset)
{
    char cmd[16];

    if (len > sizeof(cmd) - 1)
        return -EINVAL;

    if (copy_from_user(cmd, buf, len))
        return -EFAULT;

    cmd[len] = '\0';

    if (strncmp(cmd, "reset", 5) == 0) {
        u8 soft_reset = 0xB6;
        struct spi_transfer t = {
            .tx_buf = (u8[]){ 0xE0 & 0x7F, soft_reset },  // write: MSB cleared
            .len = 2,
        };
        spi_sync_transfer(bmp280_spi_device, &t, 1);
        pr_info("bmp280: sensor reset\n");
    }

    return len;
}

static struct file_operations bmp280_fops = {
    .owner = THIS_MODULE,
    .read = bmp280_read,
    .write = bmp280_write,
};

static int bmp280_probe(struct spi_device *spi)
{
    bmp280_spi_device = spi;

    // Register char device
    if (alloc_chrdev_region(&dev_num, 0, 1, DEVICE_NAME) < 0)
        return -1;

    cdev_init(&bmp280_cdev, &bmp280_fops);
    if (cdev_add(&bmp280_cdev, dev_num, 1) < 0)
        goto unregister_chr;

    bmp280_class = class_create(THIS_MODULE, CLASS_NAME);
    if (IS_ERR(bmp280_class))
        goto del_cdev;

    device_create(bmp280_class, NULL, dev_num, NULL, DEVICE_NAME);
    pr_info("bmp280: char device created at /dev/%s\n", DEVICE_NAME);

    return 0;

del_cdev:
    cdev_del(&bmp280_cdev);
unregister_chr:
    unregister_chrdev_region(dev_num, 1);
    return -1;
}

static int bmp280_remove(struct spi_device *spi)
{
    device_destroy(bmp280_class, dev_num);
    class_destroy(bmp280_class);
    cdev_del(&bmp280_cdev);
    unregister_chrdev_region(dev_num, 1);
    pr_info("bmp280: removed\n");
    return 0;
}

static const struct of_device_id bmp280_dt_ids[] = {
    { .compatible = "bosch,bmp280" },
    { }
};
MODULE_DEVICE_TABLE(of, bmp280_dt_ids);

static struct spi_driver bmp280_driver = {
    .driver = {
        .name = "bmp280",
        .of_match_table = bmp280_dt_ids,
    },
    .probe = bmp280_probe,
    .remove = bmp280_remove,
};

module_spi_driver(bmp280_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("OpenAI User");
MODULE_DESCRIPTION("BMP280 SPI driver with /dev interface");
