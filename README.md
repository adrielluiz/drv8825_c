# DRV8825 Stepper Motor Driver Library

This is a comprehensive C library designed to interface with the [DRV8825](https://www.ti.com/lit/ds/slvsa73f/slvsa73f.pdf?ts=1712991513606&ref_url=https%253A%252F%252Fwww.google.com%252F) stepper motor driver. It is also compatible with generic two-pin (step and direction) stepper motor drivers.

## Library Usage

To use this library, you need to provide implementations for the `pin_set` and `delay_us` functions in your application. Here's an example of how to use the library:

```c
#include <stdint.h>
#include <stdbool.h>
#include "dvr8825.h"

// Define your pin_set function to control pins
static void app_pin_set(dvr8825_drv_pins_t pin, bool state)
{
    // Add your code here to control the specified pin
}

// Define your delay_us function for microsecond delays
static void app_delay_us(uint32_t t_us)
{
    // Add your code here for microsecond delays
}

// Define your pin mapping based on your hardware configuration
static uint32_t app_pin_mapping[] =
{
    HW_MOTOR_STEP,
    HW_MOTOR_DIR,
    HW_MOTOR_RST,
    HW_MOTOR_SLP,
    HW_MOTOR_EN,
    HW_MOTOR_M0,
    HW_MOTOR_M1,
    HW_MOTOR_M2,
};

// Initialize the DRV8825 driver with your pin_set and delay_us functions
static dvr8825_drv_t drv =
{
    .pin_set = app_pin_set,
    .delay_us = app_delay_us,
};

// Configure the stepper motor settings
dvr8825_scr_t scr =
{
    .steps_per_revolution = 200,
    .microsteps = 1,
    .rpm = 200,
};

// Initialize the application
void app_init(void)
{
    dvr8825_init(&drv, scr);
}

// Main application loop
void app_loop(void)
{
    // Move the stepper motor forward
    dvr8825_move_steps(200, DVR8825_DIR_FORWARD);

    // Delay for 1000 milliseconds
    app_delay_us(1000);

    // Move the stepper motor backward
    dvr8825_move_steps(200, DVR8825_DIR_BACKWARD);
}
```
