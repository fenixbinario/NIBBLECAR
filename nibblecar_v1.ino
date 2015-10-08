/*
NIBBLECAR Bluetooth
Dibujo de las conexiones en www.moviolab.es

ARDUINO   L293D(Puente H)        
  5          10
  6          15
  9          7
  10         2
  5V         1, 9, 16
  GND        4, 5, 12, 13
  
  El motor 1 y 3 se conecta a los pines 3 y 6 del Puente H
  El motor 2 y  4 se conecta a los pines 11 y 14 del Puente H
  
  La fuente de alimentacion de los Motores se conecta a tierra y
  el positivo al pin 8 del puennte H. 
 
Conexion del Modulo Bluetooth HC-06 y el Arduino
ARDUINO    Bluetooth HC-06 
 0 (RX)       TX
 1 (TX)       RX
 5V           VCC
 GND          GND
!!ADVERTENCIA!! Las conexiones de TX y RX al modulo Bluetooth deben estar desconectadas
en el momento que se realiza la carga del codigo (Sketch) al Arduino. 
*/

#include <SoftwareSerial.h>

SoftwareSerial BT(4, 2); 
// creates a "virtual" serial port/UART
// connect BT module TX to D9
// connect BT module RX to D3
// connect BT Vcc to 5V, GND to GND
int izqA = 5;
int izqB = 6; 
int derA = 9; 
int derB = 10; 
int vel = 255;

void setup()  
{
  // set digital pin to control as an output
  pinMode(13, OUTPUT);
  pinMode(derA, OUTPUT);
  pinMode(derB, OUTPUT);
  pinMode(izqA, OUTPUT);
  pinMode(izqB, OUTPUT);

  // set the data rate for the SoftwareSerial port
  BT.begin(9600);

  // Send test message to other device
  BT.println("Hello from Arduino");
}

char a; // stores incoming character from other device

void loop() 
{
  if (BT.available())
  // if text arrived in from BT serial...
  {
    a=(BT.read());
    if (a=='1')
    {
      digitalWrite(13, HIGH);
      BT.println("LED on");
    }
    if (a=='2')
    {
      digitalWrite(13, LOW);
      BT.println("LED off");
    }
    if (a=='a')
    {
      analogWrite(derB, 0);     
      analogWrite(izqB, 0); 
      analogWrite(derA, vel);  
      analogWrite(izqA, vel);
      BT.println("Adelante");
    }
    if (a=='b')
    {
      analogWrite(derB, 0);     
      analogWrite(izqB, 0); 
      analogWrite(derA, 0);  
      analogWrite(izqA, vel);
      BT.println("Izquierda");
    }
    if (a=='c')
    {
      analogWrite(derB, 0);     
      analogWrite(izqB, 0); 
      analogWrite(derA, 0);    
      analogWrite(izqA, 0);
      BT.println("Boton Parar");
    }
    if (a=='d')
    {
       analogWrite(derB, 0);     
       analogWrite(izqB, 0);
       analogWrite(izqA, 0);
       analogWrite(derA, vel);
      BT.println("Derecha");
    }
    if (a=='e')
    {
       analogWrite(derA, 0);    
       analogWrite(izqA, 0);
       analogWrite(derB, vel);  
       analogWrite(izqB, vel);
      BT.println("Atrás");
    }    
    if (a=='?')
    {
      BT.println("Send '1' to turn LED on");
      BT.println("Send '2' to turn LED on");
    }   
    // you can add more "if" statements with other characters to add more commands
  }
}
