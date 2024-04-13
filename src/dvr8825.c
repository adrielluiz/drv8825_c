/*
 *  dvr8825.c
 *
 *  Created on: Apr 11, 2024
 *  Author: 	Adriel Luiz Marques
 *  E-mail: 	adrielluizmarques@hotmail.com
 *  LinkedIn: 	https://www.linkedin.com/in/adriel-marques/
 *  GitHub: 	https://github.com/adrielluiz
 *
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "dvr8825.h"

typedef struct dvr8825_drv_data_s
{
	dvr8825_drv_t drv;
	dvr8825_scr_t scr;
} dvr8825_drv_data_t;

static dvr8825_drv_data_t drv_data = { 0 };

void dvr8825_set_microsteps(uint8_t microsteps)
{
	drv_data.scr.microsteps = microsteps;
}

void dvr8825_set_steps_per_revolution(uint16_t steps_per_revolution)
{
	drv_data.scr.steps_per_revolution = steps_per_revolution;
}

void dvr8825_set_rpm(uint16_t rpm)
{
	drv_data.scr.rpm = rpm;
}

uint8_t dvr8825_get_microsteps(void)
{
	return drv_data.scr.microsteps;
}

uint16_t dvr8825_get_steps_per_revolution(void)
{
	return drv_data.scr.steps_per_revolution;
}

uint16_t dvr8825_get_rpm(void)
{
	return drv_data.scr.rpm;
}

void drv8825_set_rst_pin(bool state)
{
	drv_data.drv.pin_set(DVR8825_DRV_RST_PIN, state);
}

void drv8825_set_slp_pin(bool state)
{
	drv_data.drv.pin_set(DVR8825_DRV_SLP_PIN, state);
}

void drv8825_set_en_pin(bool state)
{
	drv_data.drv.pin_set(DVR8825_DRV_EN_PIN, state);
}

void drb8825_set_microsteps_pin(uint8_t microsteps)
{
	switch (microsteps)
	{
	case 1:
		drv_data.drv.pin_set(DVR8825_DRV_M0_PIN, false);
		drv_data.drv.pin_set(DVR8825_DRV_M1_PIN, false);
		drv_data.drv.pin_set(DVR8825_DRV_M2_PIN, false);
		break;
	case 2:
		drv_data.drv.pin_set(DVR8825_DRV_M0_PIN, true);
		drv_data.drv.pin_set(DVR8825_DRV_M1_PIN, false);
		drv_data.drv.pin_set(DVR8825_DRV_M2_PIN, false);
		break;
	case 4:
		drv_data.drv.pin_set(DVR8825_DRV_M0_PIN, false);
		drv_data.drv.pin_set(DVR8825_DRV_M1_PIN, true);
		drv_data.drv.pin_set(DVR8825_DRV_M2_PIN, false);
		break;
	case 8:
		drv_data.drv.pin_set(DVR8825_DRV_M0_PIN, true);
		drv_data.drv.pin_set(DVR8825_DRV_M1_PIN, true);
		drv_data.drv.pin_set(DVR8825_DRV_M2_PIN, false);
		break;
	case 16:
		drv_data.drv.pin_set(DVR8825_DRV_M0_PIN, false);
		drv_data.drv.pin_set(DVR8825_DRV_M1_PIN, false);
		drv_data.drv.pin_set(DVR8825_DRV_M2_PIN, true);
		break;
	case 32:
		drv_data.drv.pin_set(DVR8825_DRV_M0_PIN, true);
		drv_data.drv.pin_set(DVR8825_DRV_M1_PIN, true);
		drv_data.drv.pin_set(DVR8825_DRV_M2_PIN, true);
		break;
	default:
		break;
	}
}

void dvr8825_move_steps(uint16_t steps, dvr8825_dir_t dir)
{
    if (dir == DVR8825_DIR_FORWARD)
    	drv_data.drv.pin_set(DVR8825_DRV_DIR_PIN, false);
    else
		drv_data.drv.pin_set(DVR8825_DRV_DIR_PIN, true);

    uint16_t pulse_time_us = (60.0*1000000L/steps/drv_data.scr.microsteps/drv_data.scr.rpm);

    for (uint16_t i = 0; i < steps; i++)
    {
    	drv_data.drv.pin_set(DVR8825_DRV_STEP_PIN, true);
    	drv_data.drv.delay_us(pulse_time_us);
    	drv_data.drv.pin_set(DVR8825_DRV_STEP_PIN, false);
    	drv_data.drv.delay_us(pulse_time_us);
    }
}

void dvr8825_move_revs(uint16_t revs, dvr8825_dir_t dir)
{
	dvr8825_move_steps(revs * (drv_data.scr.steps_per_revolution * drv_data.scr.microsteps), dir);
}

bool dvr8825_init(dvr8825_drv_t *drv, dvr8825_scr_t scr)
{
	if(drv == NULL)
		return false;

	drv_data.drv = *drv;
	drv_data.scr = scr;

	drb8825_set_microsteps_pin(scr.microsteps);

	return true;
}
