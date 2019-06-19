/******************************************************************************
 * @copyright Copyright (c) Link Line Ukraine Ltd. All rights reserved.
 * @author Ruslan B
 *****************************************************************************/
#include <stdio.h>
//#include <stdint.h>
#include <string.h>
//#include "stm32f0xx_usart.h"
//#include "usart.h"
//#include "heaters.h"
//#include "powermetr.h"
#include "communication.h"


//uint8_t in_buf[16], out_buf[16];
//request_t request;
//response_t  response;

uint16_t LiczCRC2(uint8_t *FromAddr, uint8_t Many)
{
  uint8_t i, NrBajtu;
  uint16_t C, CRC16 = 0;

  for(NrBajtu = 1; NrBajtu <= Many; NrBajtu++, FromAddr++)
  {
    C = ((CRC16 >> 8) ^ *FromAddr) << 8;
    for(i = 0; i < 8; i++)
    {
      if(C&0x8000) C=(C << 1) ^ 0x1021;
        else C = C << 1;
    }
    CRC16 = C ^ (CRC16 << 8);
  }
  return CRC16;
}

/* @brief �onvert request structure to array ..... for master
 */
void request_to_array(request_t *from, uint8_t to[sizeof(request_t)])
{
  from->crc16 = LiczCRC2((uint8_t *)from, sizeof(request_t) - 2);

  /* copying data from structure to array */
  memcpy(to, from, sizeof(request_t));
}

/* @brief �onvert array to request structure ...... for slave
 */
void array_to_request(request_t *to, uint8_t from[sizeof(request_t)])
{
  /* copying data from structure to array */
  memcpy(to, from, sizeof(response_t));
}




/* @brief  �onvert response array to structure ..... for master
 */
void array_to_response(response_t *to, uint8_t from[sizeof(response_t)])
{
  /* copying data from structure to array */
  memcpy(to, from, sizeof(response_t));
}

/* @brief  �onvert response structure to array ...... for slave
 */
void response_to_array(response_t *from, uint8_t to[sizeof(response_t)])
{

  from->crc16 = LiczCRC2((uint8_t *)from, sizeof(request_t) - 2);

  /* copying data from structure to array */
  memcpy(to, from, sizeof(request_t));
}

//void init_comm_hardware()
//{
//  USART1_UART_Inite();
//}
//
//void communication_demon (void)
//{
//  static uint16_t time_p;
//  static uint8_t wk;
//  if (wk==0)
//  {
//    if (get_n_rx() >= sizeof(request_t))
//    {
//      get_arrey (in_buf);
//      array_to_request ( &request, in_buf );
//      if ( request.address == (my_address + (master_adress<<4)) )
//      {
//        if (request.crc16 == LiczCRC2((uint8_t *)&request, sizeof(request_t) - 2) )
//        {
//         if ( ok == comm_comander(&request, &response))
//         {
//           response_to_array (&response, out_buf);
//           wk=1;
//           time_p=time_request;
//         }
//
//        }
//      }
//    }
//  }
//  else if (wk==1)
//  {
//    if (time_p > 0)
//    {
//      time_p--;
//    }
//    else
//    {
//      wk=2;
//    }
//  }
//  else if (wk==2)
//  {
//    send_array (out_buf, sizeof(response_t));
//    wk=3;
//    time_p=time_response;
//  }
//  else if (wk==3)
//  {
//    if (time_p > 0)
//    {
//      time_p--;
//    }
//    else
//    {
//      wk=0;
//    }
//  }
//
//}

//status comm_comander (request_t* question, response_t* answer)
//{
//
//
//  if (question->command == set_power)
//  {
//    set_pwm1(question->value);
//    set_pwm2(question->value);
//
//    answer->address = (my_address<<4) + master_adress;
//    answer->comand = question->command;
//    answer->value = question->value;
//    answer->status_w = OK;
//
//    return ok;
//  }
//
//  if (question->command == get_temperature)
//  {
//
//    answer->address = (my_address<<4) + master_adress;
//    answer->comand = question->command;
//    answer->value = t2_value();
//    answer->status_w = OK;
//    return ok;
//  }
//  return error10;
//}


/*****************************************************************************/



































