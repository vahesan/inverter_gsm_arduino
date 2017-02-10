#include <SoftwareSerial.h>
#include "SIM900.h"
#include "sms.h"
#include <EEPROM.h>
//SoftwareSerial mySerial(9, 10);
SMSGSM sms;

#define inputlivepin	  7
#define inputfailpin	  11
#define outputlivepin		12
#define outputfailpin		13

int numdata;
boolean started=false;
char smsbuffer[160];
char n[20];
char nmbr[20];

String status;

unsigned long timer;
unsigned long previous = 0;
const long interval = 1000;

int addr;
void setup()
{
	//mySerial.begin(9600);
	Serial.begin(9600);
	pinMode(inputlivepin, INPUT);
	pinMode(inputfailpin, INPUT);
	pinMode(outputlivepin, INPUT);
	pinMode(outputfailpin, INPUT);
	
	if (gsm.begin(9600)){
		Serial.println("\nstatus=READY");
		started=true;
		for (int i = 0; i <12; i++)
		{
			nmbr[i] = EEPROM.read(i);
		}
	}
	
}

void loop()
{
	if (digitalRead(inputlivepin)==1 && digitalRead(inputfailpin)==0 && digitalRead(outputlivepin)==1 && digitalRead(outputfailpin)==0)
	{
		status = "Normal Mode";
	}
	if (digitalRead(inputlivepin)==0 && digitalRead(inputfailpin)==1 && digitalRead(outputlivepin)==1 && digitalRead(outputfailpin)==0)
	{
		timer = millis();
		Serial.println(timer);
		Serial.println(previous);
		if ((timer > interval) && (digitalRead(inputlivepin) == 0) && (digitalRead(inputfailpin) == 1))
		{
			timer -= interval;
			status = "Mains Fail, Battery Mode";
		}
	}
	if (digitalRead(inputlivepin)==0 && digitalRead(inputfailpin)==1 && digitalRead(outputlivepin)==0 && digitalRead(outputfailpin)==1)
	{
		status = "Mains Fail & Output Fail";
	}
	if (digitalRead(inputlivepin) == 1 && digitalRead(inputfailpin) == 0 && digitalRead(outputlivepin) == 0 && digitalRead(outputfailpin) == 1)
	{
		status = "Mains Live, Inverter Off/Inverter Fault";
	}
	
	delay(100);
}

void smscheck() {
		/*if(gsm.readSMS(smsbuffer, 160, n, 20))
		{
			
			//Serial.println(smsbuffer);
			if(smsbuffer[0] == 'A' && smsbuffer[1] == 'B')
			{
				for (int i = 0; i < 12; i++)
				{
					nmbr[i] = n[i];
					Serial.println(n);
				}
			}
			delay(10);
			eeprom();
		}*/
}

void powerfailure()
{
	/*if (onflag == 1 && (digitalRead(linepowerpin)==0))
	{
		timer = millis();
		Serial.println(timer);
		Serial.println(previous);
		if ((timer - previous > interval) && (linelossflag == 0))
		{
			previous = timer;
			sendmsg("LINE POWER OFF");
			Serial.println("POWER OFF");
			linelossflag = 1;
			digitalWrite(led, HIGH);
			//Serial.println(poweroutflag);
		}
	}
	if (linelossflag == 1 && (digitalRead(linepowerpin)==1))
	{
		sendmsg("POWER IS BACK");
		linelossflag = 0;
		digitalWrite(led, LOW);
		Serial.println("Power is Back");
	}*/
}

void sendmsg(char MSG[])
{
	//String at = "AT+CMGS=";
	//String cmd = at + nmbr + "\r";
	int sendingmsg = 0;
	Serial.println("msg");
	while(sendingmsg == 0){
	/*Serial.println(MSG);
	Serial.println("AT+CMGF=1");    //To send SMS in Text Mode
	delay(800);
	Serial.println(cmd); // change to the phone number you using
	delay(800);
	Serial.println(MSG);//the content of the message
	delay(200);
	Serial.println((char)26);//the stopping character*/
	if (sms.SendSMS(nmbr,MSG));
	sendingmsg = 1;
	Serial.println("msgsent");
	}
	

}

void eeprom()
{
	for (int i = 0; i < 12; i++)
	{
		EEPROM.write(i, nmbr[i]);
		Serial.println(EEPROM.read(i));
	}
}

void serialcheck()
{

}