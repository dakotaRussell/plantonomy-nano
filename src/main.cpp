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
#include "ADS1115.h"

int main()
{
    ADS1115 adc = ADS1115("/dev/i2c-1", 0xC2, 0xE3);

    fprintf(stdout, "\nPrepare ADC read....\n");
    int i = 0;
    while(i++ <= 200)
    {
        usleep(100000);
        // Read from ADC.
        double val = adc.calculateAnalogValue();
        // Do something with val.
        sleep(1);
    }

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
