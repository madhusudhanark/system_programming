#include <linux/module.h>
#include <linux/spi/spi.h>
#include <linux/fs.h>



static void bmp280_probe(struct spi_device *bmp)
{
    
    

    

     


}

static void bmp280_remove()
{



}



struct spi_driver bmp280_driver  = 
{

    .driver = {
        .name = "bm280_driver",
        .owner = THIS_MODULE,
    },
   .probe = bmp280_probe,
   .remove = bmp280_remove,
};






module_spi_driver(bmp280_driver)
MODULE_LICENCE("GPL")
MODULE_OWNER("MADHU")
MODULE_COMMENT("THIS IS KERNEL SPI DRIVER")