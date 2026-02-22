#include "hal/hal_gpio.h"
#include "hal/hal_delay.h"
#include "hal/hal_timer.h"
#include "hal/hal_interrupt.h"
#include "hal/hal_uart.h"

#define MAX_Expression_LEN 50

char expression[MAX_Expression_LEN + 1]; 
char buffer = 0;
char index = 0;
bool expression_ready = false; 
int64_t numbers[25];
char operators[25];
char numbers_index =0;
char operators_index = 0;
int64_t result = 0;
bool equation_processed = false;

void calculator_init(){
  hal_uart_init(9600);
  char sentence[] = "Calculator is Ready";
  hal_Serial_println((char *)sentence);
  buffer =0;
  index =0;
}

void calculator_input_handle(char data){

  if ((data >= '0' && data <= '9')|| data == '+' || data == '-' || data == '/' || data == '*'){
    if (index <= 50){
      expression[index] = data;
      index++;
      hal_uart_tx_byte(data);
    }
  }
  if (data == '\n' || data == '='){
    expression[index] = '\0';
    expression_ready = true;
  }

  if (data == '\b'){
    if(index > 0){
      index--;
      expression[index]=' ';
      hal_uart_tx_byte(data);
      hal_uart_tx_byte(' ');
    }
  }
}

void tokenize_expression(){
  numbers_index = 0;
  operators_index = 0;
  char current_number =0;
  for (int i=0; expression[i] != '\0';i++){
    if(expression[i] <= '9' && expression[i] >= '0'){
      current_number = current_number*10 + (expression[i] - '0');
    }
    if(expression[i] == '+' || expression[i] == '-' || expression[i] == '/' || expression[i] == '*'){
      numbers[numbers_index] = current_number;
      operators[operators_index] = expression[i];
      current_number = 0;
      operators_index++;
      numbers_index++;
    }
  }
  numbers[numbers_index+1]=current_number;
}

void resolve_add_sub(char first_no_index, char second_no_index, char operator_symbols){
    equation_processed = true;
    if(operator_symbols == '+'){
      result += numbers[first_no_index] + numbers[second_no_index];
    }if(operator_symbols == '-'){
      result += numbers[first_no_index] - numbers[second_no_index];
    }
}

void resolve_mul_div(char first_no_intex,char second_no_index, char operator_symbols){
    if(!equation_processed){
      result=1;
    }
    equation_processed = true;
    if(operator_symbols == '*'){
      result *= numbers[first_no_intex] * numbers[second_no_index];
    }
    if(operator_symbols == '/'){
      result *= numbers[first_no_intex] / numbers[second_no_index];

    }
}

int64_t calculator_evaluate(){
  tokenize_expression();
  char No_index = 0;
  
  4if((operators_index + 1) == (numbers_index )){
    for(char i=0; i< operators_index; i++){
      if(operators[i] == '+' || operators[i] == '-'){
        resolve_add_sub(No_index, No_index+1, operators[i]);
        No_index+=2;
      }if(operators[i] == '*' || operators[i] == '/'){
        resolve_mul_div(No_index,No_index+1,operators[i]);
        No_index +=2;
      }
    }
  }else{
    hal_Serial_println("Syntax error");

  }
  return result;
}

void calculator_process_input(){
  char receive_data;
  if(hal_uart_rx_available()){    
      receive_data = hal_uart_rx_byte();
      calculator_input_handle(receive_data);
  }
}


void calculator_print_result(int64_t result){
    char int_string[65];
    char i;
    for( i=0; result != 0;i++){
      char temp = result%10;
      int_string[i] = temp + 32;
    }
    int_string[i] = '\0';

    hal_Serial_println((char *)int_string);
}

void calculator_reset(){
  index = 0;
  expression[0] = '\0';
  expression_ready = false;
}

int main(void){
  hal_systick_init();
  hal_enable_interrupt();
  hal_gpio_init(13,'O'); 
  calculator_init();
  uint32_t LED_timer = 0;
  uint8_t LED_state = 0;
  int64_t final_result = 0;
  while(1){

    calculator_process_input();
    if(expression_ready){
      final_result = calculator_evaluate();
      calculator_print_result(final_result);
      calculator_reset();
    }

  }
}