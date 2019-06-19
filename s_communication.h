/******************************************************************************
 * @copyright Copyright (c) Link Line Ukraine Ltd. All rights reserved.
 * @author Ruslan B
 *****************************************************************************/

#pragma once /****************************************************************/

#ifdef __cplusplus
 extern "C" {
#endif


#define uint16_t unsigned short
#define uint8_t unsigned char


//#define _master_
#define _slave_

#define my_address    0x03
#define master_adress 0x00
#define time_request  0x03
#define time_response 0x03


/* @enum status
 */
typedef enum __attribute__((packed)) {
  OK,
  CRC_error,
  frame_error,
  time_out,

  hight_voltage,
  hight_current,
  low_voltage,
  low_current,
  soft_start,

} status_w;

/* @enum command
 */
typedef enum __attribute__((packed)) {
  none,
  set_power,
  set_max_power,
  set_max_voltage,
  set_min_voltage,
  set_max_carrent,
  set_base_resistence_1,
  set_base_resistence_2,
  set_temperature_glass_1,
  set_temperature_glass_2,
  get_voltage,
  get_current1,
  get_current2,
  get_power,
  get_dU,
  get_temperature_glass_1,
  get_temperature_glass_2,
  get_temperature,
  get_temperature_CPU,
  get_PWM1,
  get_PWM2,
  get_base_resistence_1,
  get_base_resistence_2,

  get_humidity,
  get_temperature_out_1,
  get_temperature_out_2,
  get_temperature_out_3,

} command;

/* @struct request_t
 */
typedef struct __attribute__((packed)) {
  uint8_t address;
  uint8_t command;
  uint16_t value;
  uint16_t crc16;
} request_t; //to slave

/* @struct response_t
 */

typedef struct __attribute__((packed)) {
  uint8_t address;
  uint8_t command;
  uint16_t value;
  uint8_t status_w;
  uint16_t crc16;
} response_t; //from slave


/* @brief �onvert request structure to array
 * @param  from - structure which will be unpacked to array
 * @param  to   - array for send
 * master send request
 * @return none
 */
void request_to_array(request_t *from, uint8_t to[sizeof(request_t)]);

/* @brief  �onvert response array to structure
 * @param  to   - structure to which array will be unpacked
 * @param  from - array from
 * slave receive request
 * @return none
 */
void array_to_request(request_t *to, uint8_t from[sizeof(request_t)]);

/* @brief  �onvert response array to structure
 * @param  to   - structure to which array will be unpacked
 * @param  from - array from
 * slave send
 * @return none response
 */
void array_to_response(response_t *to, uint8_t from[sizeof(response_t)]);

/* @brief �onvert request structure to array
 * @param  from - structure which will be unpacked to array
 * @param  to   - array for send
 * master receive response
 * @return none
 */
void response_to_array(response_t *from, uint8_t to[sizeof(response_t)]);

/* init usert
 *
 */
//void init_comm_hardware();
//void communication_demon (void);

//status comm_comander (request_t* question, response_t* answer);




uint16_t LiczCRC2(uint8_t *FromAddr, uint8_t Many);



#ifdef __cplusplus
}
#endif

/*****************************************************************************/
