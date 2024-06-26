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
- возможность изменения параметров из программы (только соответсвующие данные)
- настройка разрядности АЦП микроконтроллера

<a id="init"></a>
## Инициализация
```cpp
// можно не указывать (по умолчанию - 1024.0)
#define BIT_DEPTH _8_bit // установить разрядность АЦП
// указываем в формате _10_bit, _12_bit, или вида 1024.0, 4096.0 (стапень двойки)

// конструктор
GetVolt(r1, r2, calibration);	// с указанием сопротивлений делителя напряжения и калибровочного значания
GetVolt(calibration);     	// с указанием только калибровочного значания без делителя напряжения
```
**указывать в порядке верхнее плечо, нижнее плечо, калибровка**

<a id="use"></a>
## Использование
```cpp
float getVolt(inputVolt);                // получить напряжение
void setParameters (r1, r2, calibration);// поменять параметры из программы
void setParameters (calibration);	 // поменять параметры для сестемы без делителя напряжения
```

<a id="example"></a>
## Пример
```cpp
#include <GetVolt.h>

// можно не указывать (по умолчанию - 1024.0)
#define BIT_DEPTH _8_bit // установить разрядность АЦП
// указываем в формате _10_bit, _12_bit, или 1024.0, 4096.0 (степень двойки)

#define AnalogPin1 14
#define AnalogPin2 15

// при использовании внутреннего опорного напряжения установить примерно равным ему (1.1 вольт)
// калибровочное напряжение, подобрать опытным путём
#define calibration 1.17
#define calibrationRaw 5.02

// номиналы резисторов делителя напряжения (пример)
#define r1 5000
#define r2 10000

// указываем в порядке верхнее плечо, нижнее плечо, калибровка
GetVolt voltage (r1, r2, calibration);
// при использовании без делителя напряжения указываем только калибровку
GetVolt rawVoltage (calibrationRaw);

void setup() {
  Serial.begin(9600);
  pinMode(AnalogPin1, INPUT);
  pinMode(AnalogPin2, INPUT);
  //analogReference(INTERNAL); // установить опорное напряжение ~ 1.1
}

void loop() {
	unsigned int a, b;
	a = analogRead(AnalogPin1);
	b = analogRead(AnalogPin2);

	//напряжение с делителем
	Serial.print(voltage.getVolt(a));
  	Serial.print(',');
	// напряжение без делителя
	Serial.println(rawVoltage.getVolt(b));
	
	// можно менять параметры из программы
	// в порядке r1, r2, calibration
	//voltage.setParameters (r1, r2, 1.11); // для системы с делителем напряжения

	//rawVoltage.setParameters (5.12);      // без делителя напряжения
	
	/* ВАЖНО! Для системы с делителм напряжения при использовании функции setParameters
	 * нельзя указать только калибровочный параметр без сопротивлений резисторов и наоборот
	 * Необходимо указывать те же данный, что и для конструктора класса:
	 * НЕКОРРЕКТНО: voltage.setParameters(1.11), rawVoltage.setParameters(r1, r2, 1.11)
	 * КОРРЕКТНО:	voltage.setParameters (r1, r2, 1.11), rawVoltage.setParameters (5.12)
	 */
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
- v2.1 - исправил баг с неправильным выводом напряжения, сделал настройку разрядности АЦП микроконтроллера, 
оптимизация вычислений, Разбил библиотеку на 2 класса GetVolt и GetRawVolt, изменил название функции изменения параметров
для системы без делителя на setRawParameters. //20.11.22
- v2.2 - Мелкие улучшения
- v2.3 - Оптимизация (передача параметров функций по ссылке)// 28.01.24
- v2.4 - Облегчение работы с библиотекой, удаление избыточного класса GetRawVolt //5.04.24
