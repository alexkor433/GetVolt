#include <GetVolt.h>

#define AnalogPin1 14
#define AnalogPin2 15

// при использовании внутреннего опорного напряжения установить примерно равным ему (1.1 вольт)
#define calibration 1.17 // калибровочное напряжение, подобрать опытным путём

// номиналы резисторов делителя напряжения (пример)
#define r1 5000
#define r2 10000

// указываем в порядке верхнее плечо, нижнее плечо, калибровка
GetVolt voltage (r1, r2, calibration);
//GetVolt rawvoltage (calibration); 	// без делителя

void setup() {
  Serial.begin(9600);
  pinMode(AnalogPin1, INPUT);
  pinMode(AnalogPin2, INPUT);
  //analogReference(INTERNAL); // установить калибровочное значение ~ 1.1
}

void loop() {
	float a, b;
	a = analogRead(AnalogPin1);
	b = analogRead(AnalogPin2);

	//напряжение с делителем
	Serial.print(voltage.getVolt(a));
	
	// напряжение без делителя
	//Serial.println(rawvoltage.getRawVolt(b));

	//voltage.setParameters (1000, 2000, 1.11);// можно менять параметры из программы

	//rawvoltage.setParameters (1.12); // без делителя напряжения

  delay(50);
}