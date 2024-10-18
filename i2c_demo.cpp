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
#include "i2c/i2c.h"

#define I2C_ADDRESS 0x48
#define CONFIG_REGISTER 0x01
#define CONVERSION_REGISTER 0x00

// Flag to determine when user wants to end program
bool done = false;

// Function called by Interrupt
void signalHandler (int s)
{
    done = true;
}

void print_i2c_data(const unsigned char *data, size_t len)
{
    size_t i = 0;

    for (i = 0; i < len; i++) {

        if (i % 16 == 0) {

            fprintf(stdout, "\n");
        }

        fprintf(stdout, "%02x ", data[i]);
    }

    fprintf(stdout, "\n");
}

int openI2CBus(const char *bus_name)
{
    int bus = i2c_open(bus_name);
    if (bus == -1)
    {
        fprintf(stdout, "Failed to open the I2C bus\n");
        exit(1);
    }

    return bus;
}

I2CDevice configureI2CDevice(int bus) {
    I2CDevice device;
    memset(&device, 0, sizeof(device));
    device.bus = bus;
    device.addr = I2C_ADDRESS;
    device.iaddr_bytes = 1;
    device.page_bytes = 16;
    return device;
}

void writeConfig(I2CDevice *device)
{
    uint8_t data[2] = {0xC3, 0xE3};
    if (i2c_write(device, CONFIG_REGISTER, data, 2) != 2)
    {
        fprintf(stdout, "Failed to write config to the I2C bus\n");
        exit(1);
    }
}

uint16_t readConversion(I2CDevice *device)
{
    uint16_t data = 0;
    if (i2c_read(device, CONVERSION_REGISTER, &data, 2) != 2)
    {
        fprintf(stdout, "Failed to write config to the I2C bus\n");
        exit(1);
    }
    else
    {
        return data;
    }
}

int main()
{
    const char *bus_name = "/dev/i2c-0";
    int bus = openI2CBus(bus_name);
    I2CDevice device = configureI2CDevice(bus);

    writeConfig(&device);
    sleep(1);

    int i = 0;
    while(i++ <= 20)
    {
        int16_t result = readConversion(&device);
        fprintf(stdout, "Got result: {%u}\n", result);
        sleep(1);
    }

    fprintf(stdout, "Finishing and closing I2C bus\n");
    i2c_close(bus);
    return 0;
}
