#ifndef _LCD_PCF8574_H_
#define _LCD_PCF8574_H_

#include "stm32c0xx_hal.h"
#include "i2c.h"

#define SLAVE_ADDRESS_LCD 0x4E

/**
 * @brief  Inicializa o LCD em modo de 4 bits usando o barramento I2C.
 * @param  Nenhum parâmetro.
 */
void InitializeLCD(void);

/**
 * @brief  Envia um comando para o LCD via I2C.
 * @param  cmd: Comando de 8 bits a ser enviado ao LCD.
 * @retval Nenhum valor de retorno.
 */
void SendCmdLCD(char cmd);

/**
 * @brief  Envia um caractere para o LCD via I2C.
 * @param  data: Dado de 8 bits a ser enviado ao LCD.
 * @retval Nenhum valor de retorno.
 */
void SendDataLCD(char data);

/**
 * @brief  Envia uma string de caracteres para o LCD.
 * @param  packet: Ponteiro para a string a ser enviada.
 * @retval Nenhum valor de retorno.
 */
void SendStringLCD(char *packet);

/**
 * @brief  Posiciona o cursor do LCD em uma linha e coluna específica.
 * @param  row: Linha do display (0 para a primeira linha, 1 para a segunda).
 * @param  col: Coluna do display (0 a 15 para displays de 16 colunas).
 * @retval Nenhum valor de retorno.
 */
void PutCursorLCD(uint8_t row, uint8_t col);

#endif