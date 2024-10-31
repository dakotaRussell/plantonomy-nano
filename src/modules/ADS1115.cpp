#include "ADS1115.h"

ADS1115::ADS1115()
{
    //ctor
    ADS1115("/dev/i2c-0", 0xC3, 0xE3);
}

ADS1115::ADS1115(const char* deviceAddr, unsigned char configA, unsigned char configB)
{
    buf_size = 2;
    i2cReadHandle = i2c_read;
    i2cWriteHandle = i2c_write;

    /* First open i2c bus */
    int fd;
    if ((fd = i2c_open(deviceAddr)) == -1) {

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
    memset(buf, 0, sizeof(buf));
    buf[0]=configA, buf[1] = configB;
    fprintf(stdout, "Writing configuration...\n");
    printI2cData(buf, buf_size);

    ssize_t ret = i2cWriteHandle(&device, CONFIG_REG_ADDR, buf, buf_size);
    if (ret == -1 || (size_t)ret != buf_size)
    {

        fprintf(stderr, "Config write error! ADS1115 is not configured.\n");
        exit(-4);
    }

    fprintf(stdout, "Config write success. ADS1115 is configured...\n");
}

double ADS1115::calculateAnalogValue()
{
    uint16_t digVal = readDigitalValue();

    /* Calculate the analog value of the digital value read. */
    double voltage = 4.096*digVal/32768;
    fprintf(stdout, "Calculated data: %lf\n", voltage);
    return voltage;
}

void ADS1115::printI2cData(const unsigned char *data, size_t len)
{
    size_t i = 0;
    for (i = 0; i < len; i++)
    {
        if (i % 16 == 0)
            fprintf(stdout, "\n");

        fprintf(stdout, "%02x ", data[i]);
    }
    fprintf(stdout, "\n");
}

uint16_t ADS1115::readDigitalValue()
{
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

ADS1115::~ADS1115()
{
    //dtor
    fprintf(stdout, "Finishing and closing I2C bus\n");
    int fd = device.bus;
    i2c_close(fd);
}

