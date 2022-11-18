# GetVolt
### Библиотека для получения напряжения с аналоговых пинов

## Содержание
- [Возможности](#capabilities)
- [Инициализация](#init)
- [Использование](#use)
- [Пример](#example)
- [Версии](#versions)

<a id="capabilities"></a>
## Возможности
- получение напряжения
- возможность работы с делителем напряжения и без
- настройка сопротивления резисторов и параметра калибровки
- возможность изменения параметров из программы

<a id="init"></a>
## Инициализация
```cpp
GetVolt(r1, r2, calibration)//с указанием сопротивлений делителя напряжения и калибровочного значания
GetVolt(calibration)        // с указанием только калибровочного значания без делителя напряжения
```
**указывать в порядке верхнее плечо, нижнее плечо, калибровка**

<a id="use"></a>
## Использование
```cpp
float getVolt(inputVolt)                // получить напряжение
float getRawVolt (inputVolt)            // получить напряжение без делителя
void setParameters (r1, r2, calibration)// поменять параметры из программы
void setParameters (calibration)
```

<a id="example"></a>
## Пример
```cpp
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

	//voltage.setParameters (1000, 2000, 1.11); // можно менять параметры из программы

	//rawvoltage.setParameters (1.12); // без делителя напряжения

  delay(50);
}
```

<a id="versions"></a>
## Версии
- v1.0 - релиз;
- v1.1 - получение "сырых" 5 вольт (без делителя напряжения);
- v1.2 - теперь калибровочное значение можно менять из программы;
- v2.0 - полностью переработана структура программы, добавил функцию для изменения параметров из кода
	облегчена работа с библиотекой, оптимизация. //18.11.22
