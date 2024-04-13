/*
 *  dvr8825.h
 *
 *  Created on: Apr 11, 2024
 *  Author: 	Adriel Luiz Marques
 *  E-mail: 	adrielluizmarques@hotmail.com
 *  LinkedIn: 	https://www.linkedin.com/in/adriel-marques/
 *  GitHub: 	https://github.com/adrielluiz
 *
 */

#ifndef DVR8825_H_
#define DVR8825_H_

typedef enum dvr8825_dir_e
{
	DVR8825_DIR_FORWARD = 0,
	DVR8825_DIR_BACKWARD,
} dvr8825_dir_t;

typedef enum dvr8825_drv_pins_e
{
	/* OUT */ DVR8825_DRV_STEP_PIN = 0,
	/* OUT */ DVR8825_DRV_DIR_PIN,
	/* OUT */ DVR8825_DRV_RST_PIN,
	/* OUT */ DVR8825_DRV_SLP_PIN,
	/* OUT */ DVR8825_DRV_EN_PIN,
	/* OUT */ DVR8825_DRV_M0_PIN,
	/* OUT */ DVR8825_DRV_M1_PIN,
	/* OUT */ DVR8825_DRV_M2_PIN,
} dvr8825_drv_pins_t;

typedef struct dvr8825_drv_s
{
	void (*pin_set)(dvr8825_drv_pins_t pin, bool state);
	void (*delay_us)(uint32_t t_us);
} dvr8825_drv_t;

typedef struct dvr8825_scr_s
{
	uint16_t steps_per_revolution;
	uint8_t microsteps;
	uint16_t rpm;
} dvr8825_scr_t;

void dvr8825_set_microsteps(uint8_t microsteps);
void dvr8825_set_steps_per_revolution(uint16_t steps_per_revolution);
void dvr8825_set_rpm(uint16_t rpm);
uint8_t dvr8825_get_microsteps(void);
uint16_t dvr8825_get_steps_per_revolution(void);
uint16_t dvr8825_get_rpm(void);
void drv8825_set_rst_pin(bool state);
void drv8825_set_slp_pin(bool state);
void drv8825_set_en_pin(bool state);
void drb8825_set_microsteps_pin(uint8_t microsteps);
void dvr8825_move_steps(uint16_t steps, dvr8825_dir_t dir);
void dvr8825_move_revs(uint16_t revs, dvr8825_dir_t dir);
bool dvr8825_init(dvr8825_drv_t *drv, dvr8825_scr_t scr);

#endif /* DVR8825_H_ */
