#include <GetVolt.h>

// можно не указывать (по умолчанию - 1024.0)
#define bit_depth _8_bit // установить разрядность АЦП
// указываем в формате _10_bit, _12_bit, или 1024.0, 4096.0 (стапень двойки)

#define AnalogPin1 14
#define AnalogPin2 15

// при использовании внутреннего опорного напряжения установить примерно равным ему (1.1 вольт)
#define calibration 1.17 // калибровочное напряжение, подобрать опытным путём
//#define calibration2 1.12

// номиналы резисторов делителя напряжения (пример)
#define r1 5000
#define r2 10000

// указываем в порядке верхнее плечо, нижнее плечо, калибровка
GetVolt voltage (r1, r2, calibration);
//GetRawVolt rawvoltage (calibration); 	// без делителя

void setup() {
  Serial.begin(9600);
  pinMode(AnalogPin1, INPUT);
  pinMode(AnalogPin2, INPUT);
  //analogReference(INTERNAL); // установить опорное напряжение ~ 1.1
}

void loop() {
	unsigned int a, b;
	a = analogRead(AnalogPin1);
	//b = analogRead(AnalogPin2);

	//напряжение с делителем
	Serial.print(voltage.getVolt(a));
	
	// напряжение без делителя
	//Serial.println(rawvoltage.getRawVolt(b));
	
	// можно менять параметры из программы
	// в порядке r1, r2, calibration
	//voltage.setParameters (r1, r2, 1.11);// для системы с делителем напряжения

	//rawvoltage.setRawParameters (1.12); // без делителя напряжения

  delay(50);
}