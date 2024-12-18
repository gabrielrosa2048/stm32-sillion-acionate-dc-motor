#ifndef _H_BRIDGE_H
#define _H_BRIDGE_H

#include "stm32c0xx_hal.h"
#include "tim.h"

#define NOMINAL_VOLTAGE_DC_MOTOR 5

typedef struct {

    GPIO_TypeDef *in1_port;
    uint16_t in1_pin;
    GPIO_TypeDef *in2_port;
    uint16_t in2_pin;
    GPIO_TypeDef *enable_port;
    uint16_t enable_pin;    
    uint8_t voltage;

} dc_motor_t;


/**
 * @brief  Inicializa o motor DC configurando os pinos GPIO e o PWM.
 * @param  motor: Ponteiro para a estrutura do motor DC (dc_motor_t).
 * @param  in1_port: GPIO atribuindo ao IN1 do driver
 * @param  in1_pin: Pino atribuindo ao IN1 do driver
 * @param  in2_port: GPIO atribuindo ao IN2 do driver
 * @param  in2_pin: Pino atribuindo ao IN2 do driver
 * @param  enable_port: GPIO atribuindo ao ENABLE do driver
 * @param  enable_pin: Pino atribuindo ao ENABLE do driver
 * @retval Nenhum valor de retorno.
 */
void InitializeDcMotor(dc_motor_t *motor, GPIO_TypeDef *in1_port, uint16_t in1_pin, GPIO_TypeDef *in2_port, uint16_t in2_pin, GPIO_TypeDef *enable_port, uint16_t enable_pin);

/**
 * @brief  Inicia o motor DC configurando o PWM e habilitando o driver.
 * @param  motor: Ponteiro para a estrutura do motor DC (dc_motor_t).
 * @param  desiredVoltage: Tensão desejada para o motor (em Volts).
 * @retval Nenhum valor de retorno.
 */
void StartDcMotor(dc_motor_t *motor, uint8_t desiredVoltage);

/**
 * @brief  Para o motor DC desabilitando o driver e interrompendo o PWM.
 * @param  motor: Ponteiro para a estrutura do motor DC (dc_motor_t).
 * @retval Nenhum valor de retorno.
 */
void StopDcMotor(dc_motor_t *motor);

/**
 * @brief  Configura os registradores do timer para geração do PWM.
 * @param  desiredVoltage: Tensão desejada para o motor (em Volts).
 * @retval Nenhum valor de retorno.
 */
static void configTimerRegisters(uint8_t desiredVoltage);


#endif