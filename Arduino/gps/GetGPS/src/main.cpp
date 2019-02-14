#include <Arduino.h>
#include <stdio.h>
#include <string.h>

#define DEBUG true

// Ligar o GPS
const char * CMD_GPS_ON = "AT+GPS=1";
// Desligar o GPS
const char * CMD_GPS_OFF = "AT+GPS=0";
// Obter o status de funcionamento do GPS
const char * CMD_GPS_STATUS = "AT+GPS?";
// Ler dados do GPS (N eh o numero de segundos para obter uma mensagem NEMA da porta AT)
const char * CMD_GPS_READ = "AT+GPSRD=%d"; 
// Comando para configurar a localizacao (1 - endereco da estacao base / 2 - endereco do GPS)
const char * CMD_LOCATION = "AT+LOCATION=%d";
/*OBS: apos o GPS ser ligado, o GPS_TXD ira enviar as informacoes de posicionaemtno a uma taxa de 9600.
Isso nao afeta o baud rate do modulo, ou seja, a taxa de funcionamento do A9G continua sendo 115200.
As mudancas de localizacao irao disponibilizar mensagens GNGGA e GNRMC, e nao GPGGA e GPRMC. 
O modulo usa um sistema de posicionamento hibrido que inclui GPS, BDS e GNNS.*/
// Comando para ligar o AGPS
const char * CMD_AGPS_ON = "AT+AGPS=1";
// Comando para desligar o AGPS
const char * CMD_AGPS_OFF = "AT+AGPS=0";
// Comando para verificar o status do AGPS
const char * CMD_AGPS_STATUS = "AT+AGPS?";


int pon = 9;
int poff = 6;
int lowp = 5;

String sendData(String command, const int timeout, boolean debug);

void setup()
{
    SerialUSB.begin(115200);

    while (!SerialUSB)
    {
        ; // wait for serial port to connect
    }
    SerialUSB.println("#############################");
    SerialUSB.println("######  LAB - GET GPS  ######");
    SerialUSB.println("#############################");

    pinMode(pon, OUTPUT);
    pinMode(poff, OUTPUT);
    pinMode(lowp, OUTPUT);
    digitalWrite(poff, LOW);
    digitalWrite(lowp, HIGH);
    digitalWrite(pon, HIGH);

    
    SerialUSB.println("==> Inicializando serial de comunicacao...");
    Serial1.begin(115200);
    digitalWrite(pon, LOW);
    delay(300);
    digitalWrite(pon, HIGH);
    delay(500);
    SerialUSB.println("==> Serial de comunicacao inicializada! Enviando AT+GPS = 1...");
    sendData("AT+GPS=1 ", 1000, DEBUG);
}

void loop()
{
    sendData("AT+GPSRD=1", 1000, DEBUG);
    delay(1000);
}

String sendData(String command, const int timeout, boolean debug)
{
    String response = "";
    SerialUSB.print("\n==>Enviando comando:");
    SerialUSB.println( command.c_str() );

    Serial1.println(command);
    unsigned long time = millis();
    while ((time + timeout) > millis())
    {
        while (Serial1.available())
        {
            char c = Serial1.read();
            response += c;
        }
    }
    if (debug)
    {
        SerialUSB.print(response);
    }
    return response;
}