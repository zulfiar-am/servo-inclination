/*
 * Example showing how to send position commands to AX-12A
 */

#include "Arduino.h"
#include "AX12A.h"

#define DirectionPin 	(10u)
#define BaudRate  		(57600ul)
#define ID				(1u)
// Inisiasi sudut yang diinginkan
int sudut= 180; //masukkan nilai sudut awal yang diinginkan
int var_max= 0; //masukkan nilai sudut putaran clockwise
int var_min= 0; // masukkan nilai sudut putaran counter clockwise
//perhitungan
float deg2reg = 11.37777777777778; // 1 derajat = 11,37777777778 register
float initial_pos = sudut*deg2reg;
float max = initial_pos + var_max*deg2reg;
float min = initial_pos - var_min*deg2reg;

float pos = initial_pos;
float delta = 8;

void setup()
{
	ax12a.begin(BaudRate, DirectionPin, &Serial);
}

void loop()
{
  pos = pos + delta;

	if (pos > max)
	{
		pos = max;
		delta *= -1;
	}

	if (pos < min)
	{
		pos = min;
		delta *= -1;
	}

	ax12a.move(ID, pos);
	delay(100);
}
