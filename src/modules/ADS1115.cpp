#include "ADS1115.h"

ADS1115::ADS1115()
{
    //ctor
    ADS1115("/dev/i2c-0", 0xC3, 0xE3);
}

ADS1115::ADS1115(const char* deviceAddr, unsigned char configA, unsigned char configB)
{
    buf_size = 2;
    this->deviceAddr = deviceAddr;
    const unsigned char config[2]{configA, configB};
    open(config, 2);
}

void ADS1115::open(const unsigned char* configOptions, size_t len)
{
    connection.open(configOptions, len);

    fprintf(stdout, "ADS1115 is configured...\n");

}

double ADS1115::read()
{
    uint16_t digVal = readDigitalValue();

    /* Calculate the analog value of the digital value read. */
    double voltage = 4.096*digVal/32768;
    fprintf(stdout, "Calculated data: %lf\n", voltage);
    return voltage;
}

ssize_t ADS1115::write(const unsigned char *buf, size_t len)
{
    // unused
    return 0;
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
    return connection.read();
}

ADS1115::~ADS1115()
{

}

