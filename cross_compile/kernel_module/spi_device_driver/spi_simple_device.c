#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/spi/spi.h>
#include <linux/delay.h>

static struct spi_device *spi_dev;

static void send_data(struct spi_device *spi)
{
    u8 data[] = {0x00, 0x01, 0x02};

    spi_write(spi, data, sizeof(data));
}

static int spi_driver_probe(struct spi_device *spi)
{
    printk(KERN_INFO "SPI driver probed\n");
    spi_dev = spi;

    send_data(spi_dev);
    printk("vanhao__ da gui tin hieu spi \n");
    

    return 0;
}

static int spi_driver_remove(struct spi_device *spi)
{
    printk(KERN_INFO "SPI driver removed\n");
    spi_dev = NULL;
    return 0;
}

static const struct spi_device_id simple_spi_ids[] = {
    { "simple_spi_driver", 0 }, // Đặc điểm phù hợp của thiết bị
    { }
};
MODULE_DEVICE_TABLE(spi, simple_spi_ids);

static struct spi_driver simple_spi_driver = {
    .driver = {
        .name = "simple_spi_driver",
        .owner = THIS_MODULE,
    },
    .probe = spi_driver_probe,
    .remove = spi_driver_remove,
    .id_table = simple_spi_ids, // Sử dụng bảng ID
};
static int __init simple_spi_init(void)
{
    int ret;

    ret = spi_register_driver(&simple_spi_driver);
    if (ret < 0) {
        printk(KERN_ERR "Failed to register SPI driver\n");
        return ret;
    }

    printk(KERN_INFO "[vanhao]Simple SPI driver loaded\n");
    return 0;
}

static void __exit simple_spi_exit(void)
{
    spi_unregister_driver(&simple_spi_driver);
    printk(KERN_INFO "Simple SPI driver unloaded\n");
}

module_init(simple_spi_init);
module_exit(simple_spi_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Simple SPI Driver");