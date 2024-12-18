#include "h_bridge.h"

void InitializeDcMotor(dc_motor_t *motor, GPIO_TypeDef *in1_port, uint16_t in1_pin, GPIO_TypeDef *in2_port, uint16_t in2_pin, GPIO_TypeDef *enable_port, uint16_t enable_pin){

    // Atribuindo os pinos ao objeto para encapsulamento
    motor->in1_port = in1_port;
    motor->in1_pin = in1_pin;
    motor->in2_port = in2_port;
    motor->in2_pin = in2_pin;
    motor->enable_port = enable_port;
    motor->enable_pin = enable_pin;

    // Inicializando o estado dos pinos
    HAL_GPIO_WritePin(motor->in1_port, motor->in1_pin, 0);
    HAL_GPIO_WritePin(motor->in2_port, motor->in2_pin, 0);
    HAL_GPIO_WritePin(motor->enable_port, motor->enable_pin, 1);

    // Configurando os registadores do timer para que seja possivel setar a tensao desejada do motor via PWM (0 - 5V)
    configTimerRegisters(5);

}

void StartDcMotor(dc_motor_t *motor, uint8_t desiredVoltage){

    configTimerRegisters(desiredVoltage);                           // Configurando o duty cycle do pwm para a tensao desejada
    HAL_GPIO_WritePin(motor->enable_port, motor->enable_pin, 0);    // Habilitando o enable do driver L298N
    HAL_TIM_Base_Start_IT(&htim1);                                  // Iniciando a interrupcao para a geracao do sinal de PWM

}

void StopDcMotor(dc_motor_t *motor){

    HAL_GPIO_WritePin(motor->enable_port, motor->enable_pin, 1);    // Desabilitando o driver L298N
    HAL_TIM_Base_Stop_IT(&htim1);                                   // Desabilitando a interrupcao do sinal de PWM
    HAL_GPIO_WritePin(motor->in1_port, motor->in1_pin, 0);          // Redudancia para desabilitar a entrada do motor

}

static void configTimerRegisters(uint8_t desiredVoltage){

    uint16_t period_cycles = 0;
    uint16_t prescaler = 0;
    uint16_t overflow = 0;
    uint16_t duty = 0;
    
    period_cycles = HAL_RCC_GetPCLK1Freq() / (1E3*2);
    prescaler = (uint16_t)(period_cycles / 0xFFFF + 1);
    overflow = (uint16_t)(((period_cycles + (prescaler / 2)) / prescaler));
    duty = (uint16_t)(overflow * (NOMINAL_VOLTAGE_DC_MOTOR/desiredVoltage));

    TIM1->PSC = prescaler;
    TIM1->ARR = overflow;
    TIM1->CCR1 = duty;

}