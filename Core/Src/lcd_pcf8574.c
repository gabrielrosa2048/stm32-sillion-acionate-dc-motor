#include "lcd_pcf8574.h"

void InitializeLCD(void){

  // Inicializando o LCD no modo de 4 bits
  HAL_Delay(50);  
  lcd_send_cmd (0x30);
  HAL_Delay(5);  
  lcd_send_cmd (0x30);
  HAL_Delay(1);  
  lcd_send_cmd (0x30);
  HAL_Delay(10);
  lcd_send_cmd (0x20);  
  HAL_Delay(10);

  // Inicializando o display
  lcd_send_cmd (0x28);   
  HAL_Delay(1);
  lcd_send_cmd (0x08); 
  HAL_Delay(1);
  lcd_send_cmd (0x01);  
  HAL_Delay(2);
  lcd_send_cmd (0x06);
  HAL_Delay(1);
  lcd_send_cmd (0x0C);

}

void SendCmdLCD(char cmd){
    
  char data_u, data_l;
  uint8_t data_t[4];
  
  // Aplicando uma mascara para separar os 8 bits da instrucao 
  data_u = (cmd & 0xf0);
  data_l = ((cmd << 4) & 0xf0);
 
  data_t[0] = data_u | 0x0C;  
  data_t[1] = data_u | 0x08; 
  data_t[2] = data_l | 0x0C;  
  data_t[3] = data_l | 0x08;  
 
  // Enviando os comandos via barramento I2C
  HAL_I2C_Master_Transmit (&hi2c1, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100);

}

void SendDataLCD(char data){

  char data_u, data_l;
  uint8_t data_t[4];
  
  // Aplicando uma mascara para separar os 8 bits da instrucao 
  data_u = (data&0xf0);
  data_l = ((data<<4)&0xf0);
  
  data_t[0] = data_u|0x0D;  
  data_t[1] = data_u|0x09;  
  data_t[2] = data_l|0x0D;  
  data_t[3] = data_l|0x09; 

  // Enviando os comandos via barramento I2C
  HAL_I2C_Master_Transmit (&hi2c1, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100);

}

void SendStringLCD(char *packet){

    while(*packet){
        SendDataLCD(*packet++);
    }
}

void PutCursorLCD(uint8_t row, uint8_t col){

    switch(row){
        case 0:
            col |= 0x80;
            break;
        case 1:
            col |= 0xC0;
            break;
    }

    SendCmdLCD(col);

}