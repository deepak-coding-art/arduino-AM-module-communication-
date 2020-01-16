#include <VirtualWire.h>

int in_bytes;
String bytes_str;
int str_int;
const int data_lenth = 10;
int arr_index = 0;

const int receive_pin = 12;
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
  vw_set_rx_pin(receive_pin);
  vw_setup(6000);   
  vw_rx_start(); ; 
}

void loop() {
  uint8_t buf[sizeof(data)];
  uint8_t buflen = sizeof(data);
  
  uint8_t buf_b[sizeof(chack_byte)];
  uint8_t buflen_b = sizeof(chack_byte);
  
  while(Serial.available() > 0){
    char mode = Serial.read();
    if(mode == 'g'){show_data();}
    else if(mode == 'e'){empty_arr();}}
if (vw_have_message())  
  {
    vw_get_message(buf_b, &buflen_b);
    memcpy(&chack_byte,&buf_b,buflen_b);
    vw_wait_rx();
    if(chack_byte.rx_bit){
        vw_get_message(buf, &buflen);
        memcpy(&data,&buf,buflen);
        vw_wait_rx();
        Serial.print('r');}
  }
}

void show_data(){
    Serial.print('m');
    for(int i=0; i<data_lenth; i++){
      Serial.println(data.int_byte[i]);}
      arr_index = 0;
}

void empty_arr(){
  for(int i = 0; i < data_lenth; i++){data.int_byte[i] = 0;}
  arr_index = 0;
}
