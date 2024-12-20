#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "gpio.h"
#include "h_bridge.h"
#include "lcd_pcf8574.h"

void SystemClock_Config(void);

dc_motor_t motor;

int main(void)
{

  uint32_t millisMotor = HAL_GetTick(); // Variavel para armazenar os ticks do microcontrolador
  uint8_t buttonIsPressed = 0;          // Variavel para armazenar o estado do push button
  uint8_t desiredVoltage = 5;           // Variavel que define a tensao de acionamento do motor

  // Inicializada da biblioteca de abstracao de hardware
  HAL_Init();

  // Funcao gerada pelo STM32CubeMX para configurar o clock do microcontrolador
  SystemClock_Config();

  // Funcoes geradas pelo STM32CubeMX para configuracao dos pinos e dos perifericos
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_TIM1_Init();

  // Inicializando o driver do motor
  InitializeDcMotor(&motor, IN1_GPIO_Port, IN1_Pin, IN2_GPIO_Port, IN2_Pin, ENABLEA_GPIO_Port, ENABLEA_Pin);

  // Inicializando o display LCD 16x2
  InitializeLCD();  
  PutCursorLCD(0, 0);
  SendStringLCD("Motor Desligado");

  while (1){

    // Verificando o estado do botao
    buttonIsPressed = HAL_GPIO_ReadPin(BUTTON_GPIO_Port, BUTTON_Pin);

    // Logica para acionamento e indicacao do estado do motor
    if(buttonIsPressed){

      millisMotor = HAL_GetTick();
      StartDcMotor(&motor, desiredVoltage);

      PutCursorLCD(0, 0);
      SendStringLCD("Motor Ligado");
    
    }

    if((HAL_GetTick() - millisMotor) > 10000){
      StopDcMotor(&motor);

      PutCursorLCD(0, 0);
      SendStringLCD("Motor Desligado");
    
    }

  }
}

// Funcao gerada pelo STM32CubeMX para configuracao do clock do microcontrolador
void SystemClock_Config(void){

  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

// Funcao utilizada para gerar o sinal de PWM no pino de entrada do driver de motor de passo
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){

  if(htim->Instance == TIM1)
    HAL_GPIO_TogglePin(motor.in1_port, motor.in1_pin);

}

// Funcao gerada pelo STM32CubeMX para tratamento de erros
void Error_Handler(void)
{

  __disable_irq();
  while (1)
  {
  }

}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
