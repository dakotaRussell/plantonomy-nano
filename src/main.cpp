// Handles input and output
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
// For delay function
#include <chrono>
// Handles threads of program execution
#include <thread>
// Signal handling
#include <signal.h>
#include <JetsonGPIO.h>
#include "i2c.h"
//#include "Plantonomy.h"//

#define DEFAULT_I2C_ADDR 0x48
#define CONVERSION_REG_ADDR 0x00
#define CONFIG_REG_ADDR 0x01

void print_i2c_data(const unsigned char *data, size_t len)
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

int main()
{
    I2C_READ_HANDLE i2c_read_handle = i2c_read;
    I2C_WRITE_HANDLE i2c_write_handle = i2c_write;

    /* First open i2c bus */
    int fd;
    if ((fd = i2c_open("/dev/i2c-1")) == -1) {

        perror("Open i2c bus error");
        return -1;
    }

    /* Init i2c device */
    I2CDevice device;
    memset(&device, 0, sizeof(device));
    i2c_init_device(&device);

    /* Fill i2c device struct */
    device.bus = fd;
    device.addr = DEFAULT_I2C_ADDR;

    /* Print i2c device description */
    char i2c_dev_desc[128];
    fprintf(stdout, "%s\n", i2c_get_device_desc(&device, i2c_dev_desc, sizeof(i2c_dev_desc)));

  /* Configure i2c device-specific information. */
    unsigned char buf[256];
    memset(buf, 0, sizeof(buf));
    buf[0]=0xC2, buf[1] = 0xE3; //0xC3, buf[1]=0xE3;
    size_t buf_size = 2;
    fprintf(stdout, "Writing configuration...\n");
    print_i2c_data(buf, buf_size);

    ssize_t ret = i2c_write_handle(&device, CONFIG_REG_ADDR, buf, buf_size);
    if (ret == -1 || (size_t)ret != buf_size)
    {

        fprintf(stderr, "Config write error! ADS1115 is not configured.\n");
        exit(-4);
    }

    fprintf(stdout, "\nConfig write success, prepare ADC read....\n");

    int i = 0;
    while(i++ <= 200)
    {
        usleep(100000);
        memset(buf, 0, buf_size);
        ret = i2c_read_handle(&device, CONVERSION_REG_ADDR, buf, buf_size);
        if (ret == -1 || (size_t)ret != buf_size)
        {

            fprintf(stderr, "Read i2c error!\n");
            exit(-5);
        }

        fprintf(stdout, "\n Raw ADC Read success....\n");

        /* Print read result */
        uint16_t digitalVal = buf[0] << 8 | buf[1];
        fprintf(stdout, "Raw read data: %u\n", digitalVal);

        /* Calculate the analog value of the digital value read. */
        double voltage = 4.096*digitalVal/32768;
        fprintf(stdout, "Calculated data: %lf\n", voltage);
        sleep(1);
    }
    fprintf(stdout, "Finishing and closing I2C bus\n");
    i2c_close(fd);

    // When CTRL+C pressed, signalHandler will be called
    // to interrupt the programs execution
    /*signal(SIGINT, signalHandler);
    // Pin Definitions
    GPIO::setmode(GPIO::BOARD);
    // LED pin gets set to high initially
    GPIO::setup(led_pin, GPIO::OUT, GPIO::HIGH);
    std::cout << "Press CTRL+C to stop the LED" << std::endl;
    int curr_value = GPIO::HIGH;

    // Blink LED every 0.5 seconds
    int i = 0;
    while(i++ < 5)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        curr_value = GPIO::HIGH;
        GPIO::output(led_pin, curr_value);
        std::cout << "LED is ON" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        curr_value = GPIO::LOW;
        GPIO::output(led_pin, curr_value);
        std::cout << "LED is OFF" << std::endl;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    GPIO::output(led_pin, GPIO::LOW);
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    GPIO::cleanup();*/

    return 0;
}
