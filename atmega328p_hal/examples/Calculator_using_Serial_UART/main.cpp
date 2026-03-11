#include "hal/hal_gpio.h"
#include "hal/hal_delay.h"
#include "hal/hal_timer.h"
#include "hal/hal_interrupt.h"
#include "hal/hal_uart.h"
void calc_reset(void);
void calculator_input_data_handle(char single_data);
void get_input_expression(void);
int64_t calculate_expression(void);
void Serial_println_int64(int64_t result);
#define MAX_Buffer 50
int8_t buffer =0;
char full_expression[50];
bool expression_ready_for_calc = false;

int numbers_operator_index = 0;

int64_t numbers_seperation[25];
char operators_seperation[25];

void calculator_input_data_handle(char single_data){
  if(buffer<MAX_Buffer ){
    if((single_data >= '0' && single_data <= '9' )|| single_data == '-' || single_data == '+' || single_data == '/' || single_data == '*'){
      full_expression[buffer] = single_data;
      buffer++;
      hal_uart_tx_byte(single_data);
    }
    else if(single_data == '\n' || single_data == '='){
      expression_ready_for_calc = true;
      full_expression[buffer]='\0';
      hal_Serial_println((char *)"");
      //hal_Serial_println(full_expression);
    }else if(single_data == '\b'){
      if(buffer>0){
        buffer--;
        full_expression[buffer] = '\0';
        hal_uart_tx_byte(single_data);
        hal_uart_tx_byte(' ');
        hal_uart_tx_byte(single_data);
      }else{
        calc_reset();
      }
    }
  }else if(buffer>=MAX_Buffer){
    hal_Serial_println((char *)"Buffer overflow.");
    calc_reset();
  }
}

void calc_reset(){
  buffer = 0;
  expression_ready_for_calc = false;
}

void get_input_expression(){
    char receive_single_data;
    if(hal_uart_rx_available()){
      receive_single_data = hal_uart_rx_byte();
      calculator_input_data_handle(receive_single_data);
    }
} 

void tokenization_expression(){
  int64_t current_number=0;  
  numbers_operator_index = 0;
  for(int index=0;full_expression[index]!= '\0';index++){
    if(full_expression[index] >= '0' && full_expression[index] <= '9'){
      current_number = (current_number*10) + (full_expression[index] - '0');
    }else if(full_expression[index] == '+' || full_expression[index] == '-' || full_expression[index] == '/' || full_expression[index] == '*'){
      numbers_seperation[numbers_operator_index] = current_number;
      current_number = 0;
      operators_seperation[numbers_operator_index] = full_expression[index];
      numbers_operator_index++;
    }
  }
  numbers_seperation[numbers_operator_index] = current_number;
  
}

int64_t calculate_expression(){
  tokenization_expression();
  int64_t result_calculation=numbers_seperation[0];
  int operand_index_temp=0;
  for(int index_numbers=1; index_numbers<(numbers_operator_index+1);index_numbers++){
    if(operators_seperation[operand_index_temp]== '+'){
      result_calculation = result_calculation+numbers_seperation[index_numbers];
    }else if(operators_seperation[operand_index_temp] == '-'){
      result_calculation = result_calculation - numbers_seperation[index_numbers];
    }else if(operators_seperation[operand_index_temp] == '*'){
      result_calculation = result_calculation * numbers_seperation[index_numbers];
    }else if(operators_seperation[operand_index_temp] == '/'){
      result_calculation = result_calculation / numbers_seperation[index_numbers];
    }
    operand_index_temp++;
  }
  return result_calculation;
}

void Serial_println_int64(int64_t results){
  //hal_uart_tx_byte('\n');
  char result_string[64];
  int i = 0;
  if(results > 0){
    
    for(int64_t num=results; num != 0 ; num/=10){
      char temp = (num%10) + '0';
      result_string[i++] = temp;
    }
  }if(results < 0){
    hal_uart_tx_byte('-');
    results = -results;
    for(int64_t num=results; num != 0 ; num/=10){
      char temp = (num%10) + '0';
      result_string[i++] = temp;
    }
  }
  for(int j=i-1;j >= 0;j--){
    hal_uart_tx_byte(result_string[j]);
  }
  
}

int main(void){
  hal_systick_init();
  hal_enable_interrupt();
  hal_gpio_init(13,'O'); 
  hal_uart_init(9600);
  uint32_t LED_timer = 0;
  uint8_t LED_state = 0;
  hal_Serial_println((char *)"Calculator is ready");
  hal_Serial_print((char *)"calc>>>");
  while(1){
    if(hal_timeout_expired(LED_timer, 500)){
      LED_timer = hal_millis();
      LED_state ^= 1;
      hal_gpio_write(13,LED_state);
    }
    get_input_expression();
    
    if(expression_ready_for_calc){
      int64_t result = calculate_expression();
      Serial_println_int64(result);
      calc_reset();
      hal_uart_tx_byte('\n');
      hal_Serial_print((char *)"calc>>>");
    }
    
  }
}