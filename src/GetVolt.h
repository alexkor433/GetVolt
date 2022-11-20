/*
	Библиотека для получения температуры процессора микроконтроллеров AVR
	GitHub: https://github.com/alexkor433/GetVolt

	Возможности:
	- получение напряжения
	- возможность работы с делителем напряжения и без
	- настройка сопротивления резисторов и параметра калибровки
	- возможность изменения параметров из программы (только соответсвующими функциями)
	- настройка разрядности АЦП микроконтроллера

	MIT License

	Версии:
	v1.0 - релиз;
	v1.1 - получение "сырых" 5 вольт (без делителя напряжения);
	v1.2 - теперь калибровочное значение можно менять из программы;
	v2.0 - полностью переработана структура программы, добавил функцию для изменения параметров из кода
		облегчена работа с библиотекой, оптимизация. //18.11.22
	v2.1 - исправил баг с неправильным выводом напряжения, сделал настройку разрядности АЦП микроконтроллера, 
		оптимизация вычислений, Разбил библиотеку на 2 класса GetVolt и GetRawVolt, изменил название функции изменения параметров
		для системы без делителя на setRawParameters. //20.11.22
*/

#pragma once

#define _bit_depth 1024.0

#ifndef bit_depth
#define bit_depth _bit_depth //можно указать свою разрядность АЦП
#endif

class GetVolt {
	public:
		// конструктор для измерения напряжения с делителем напряжения и калибровочным параметром
		GetVolt(float r1, float r2, float calibration) { 
			setParameters(r1, r2, calibration);
		}

		// функции установки параметров (можно вызывать из программы)
		// сопротивления резисторов и праметр калибровки (с делителем напряжения)
		void setParameters (float r1, float r2, float calibration) {
			_ratio = (calibration * (r1 + r2)) / (r2 * bit_depth);
		}

		// возвращает напряжение
		float getVolt(unsigned int inputVolt) {
			float temp;
			temp = float(inputVolt) * _ratio;
			if (temp < 0.1) return 0.0;
			return temp;
		}



	private:
		float _ratio;
};

class GetRawVolt {
	public:
		// конструктор для получения напряжения без делителя напряжения
		GetRawVolt(float calibration) {
			setRawParameters(calibration);
		}
	
		// только параметр калибровки (без делителя напряжения)
		void setRawParameters (float calibration) {
			_calibration = calibration / bit_depth;
		}
		
		// возвращает напряжение без делителей
		float getRawVolt (unsigned int inputRawVolt) {
			float temp;
			temp = float(inputRawVolt) * _calibration;
			if (temp < 0.1) return 0.0;
			return temp;
		}
	private:
		float _calibration;
};

#define _4_bit 32.0
#define _6_bit 64.0
#define _8_bit 256.0
#define _10_bit 1024.0
#define _12_bit 4096.0
#define _14_bit 16384.0