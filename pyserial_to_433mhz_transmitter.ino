#include <VirtualWire.h>

int in_bytes;
String bytes_str;
int str_int;
const int data_lenth = 10;
int arr_index = 0;

const int transmit_pin = 12;
unsigned long lastcount = 0;
unsigned long now = 0;


struct rx_byte
{
  bool rx_bit = false;
};


typedef struct rx_byte Rx_byte;
Rx_byte chack_byte;


struct package
{
  byte int_byte[data_lenth];
};


typedef struct package Package;
Package data;


void setup() {

  Serial.begin(250000);
  while(!Serial){}
  vw_set_tx_pin(transmit_pin);
  vw_set_ptt_inverted(true);
  vw_setup(6000); 
}

void loop() {
  while(Serial.available() > 0){
    char mode = Serial.read();
    if(mode == 'g'){show_data();}
    else if(mode == 'e'){empty_arr();}
    else if(mode == 'w'){read_data();}
    else if(mode == 't'){
      chack_byte.rx_bit = true;
      vw_send((uint8_t *)&chack_byte, sizeof(chack_byte));
      vw_wait_tx();
      vw_send((uint8_t *)&data, sizeof(data));
      vw_wait_tx();
      chack_byte.rx_bit = false;Serial.print('d');}}
      vw_send((uint8_t *)&chack_byte, sizeof(chack_byte));
      vw_wait_tx();
}

void show_data(){
    for(int i=0; i<data_lenth; i++){
      Serial.println(data.int_byte[i]);}
      arr_index = 0; 
}

void empty_arr(){
  for(int i = 0; i < data_lenth; i++){data.int_byte[i] = 0;}
  arr_index = 0;
}

void read_data(){
  while(arr_index < data_lenth){
   in_bytes = Serial.read();
   if(sizeof(in_bytes) > 0){
     if(isDigit(in_bytes)){
      bytes_str += char(in_bytes);}
     if(in_bytes == '\n'){
      str_int = bytes_str.toInt();
      if(str_int <= 255){
        data.int_byte[arr_index] = byte(str_int);
        arr_index++;}
      bytes_str = "";}}}
}
