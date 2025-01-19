#include "I2CComm.h"

I2CComm::I2CComm()
{
    //ctor
    i2cReadHandle = i2c_read;
    i2cWriteHandle = i2c_write;
}

I2CComm::~I2CComm()
{
    //dtor
    fprintf(stdout, "Finishing and closing I2C bus\n");
    int fd = device.bus;
    i2c_close(fd);
}

void I2CComm::open(const unsigned char *configOptions, size_t len)
{
    /* First open i2c bus */
    int fd;
    if ((fd = i2c_open(addr)) == -1) {

        perror("Open i2c bus error");
        exit(-1);
    }

    /* Init i2c device */
    memset(&device, 0, sizeof(device));
    i2c_init_device(&device);

    /* Fill i2c device struct */
    device.bus = fd;
    device.addr = DEFAULT_I2C_ADDR;

    /* Print i2c device description */
    char i2c_dev_desc[128];
    fprintf(stdout, "%s\n", i2c_get_device_desc(&device, i2c_dev_desc, sizeof(i2c_dev_desc)));

    /* Configure i2c device-specific information. */
    memset(this->buf, 0, sizeof(this->buf));

    if (len != 2)
    {
        fprintf(stderr, "Insufficient number of configuration parameters.\n");
        exit(-4);
    }

    buf[0]=configOptions[0], buf[1] = configOptions[1];
    fprintf(stdout, "Writing configuration...\n");
    //this->printI2cData(buf, buf_size);

    ssize_t ret = i2cWriteHandle(&device, CONFIG_REG_ADDR, buf, buf_size);
    if (ret == -1 || (size_t)ret != buf_size)
    {

        fprintf(stderr, "Config write error! ADS1115 is not configured.\n");
        exit(-4);
    }

    fprintf(stdout, "Config write success. ADS1115 is configured...\n");
}

double I2CComm::read()
{
    unsigned char buf[256];
    size_t buf_size = 2;
    memset(buf, 0, buf_size);
    ssize_t ret = i2cReadHandle(&device, CONVERSION_REG_ADDR, buf, buf_size);
    if (ret == -1 || (size_t)ret != buf_size)
    {

        fprintf(stderr, "Read i2c error!\n");
        exit(-5);
    }

    fprintf(stdout, "\n Raw ADC Read success....\n");

    /* Print read result */
    uint16_t digitalVal = buf[0] << 8 | buf[1];
    fprintf(stdout, "Raw read data: %u\n", digitalVal);
    return digitalVal;

}

ssize_t I2CComm::write(const unsigned char *buf, size_t len){}
