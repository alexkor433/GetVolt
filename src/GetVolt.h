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
	v1.0 - Релиз;
	v1.1 - Получение "сырых" 5 вольт (без делителя напряжения);
	v1.2 - Теперь калибровочное значение можно менять из программы;
	v2.0 - Полностью переработана структура программы, добавлена функция изменения параметров калибровки из кода
		облегчена работа с библиотекой, оптимизация. //18.11.22
	v2.1 - Исправлен баг с неправильным выводом напряжения, добавлена возможность настройки разрядности АЦП микроконтроллера, 
		оптимизация вычислений; Разбиение библиотеки на 2 класса GetVolt и GetRawVolt, изменение названий функций калибровки параметров
		для системы без делителя на setRawParameters. //20.11.22
	v2.2 - Мелкие улучшения
	v2.3 - Оптимизация (передача параметров функций по ссылке)// 28.01.24
	v2.4 - Облегчение работы с библиотекой, удаление избыточного класса GetRawVolt //5.04.24
*/

#pragma once

#define _BIT_DEPTH 1024.0

#ifndef BIT_DEPTH
#define BIT_DEPTH _BIT_DEPTH //можно указать свою разрядность АЦП
#endif

class GetVolt {
	public:
		// конструктор для измерения напряжения с делителем напряжения и калибровочным параметром
		GetVolt(const float& r1, const float& r2, const float& calibration) { 
			setParameters(r1, r2, calibration);
		}

		GetVolt(const float& calibration) {
			setParameters(calibration);
		}

		// функции установки параметров (можно вызывать из программы)
		// сопротивления резисторов и праметр калибровки (с делителем напряжения)
		void setParameters (const float& r1, const float& r2, const float& calibration) {
			_ratio = (calibration * (r1 + r2)) / (r2 * BIT_DEPTH);
		}

		void setParameters (const float& calibration) {
			_ratio = calibration / BIT_DEPTH;
		}

		// возвращает напряжение
		float getVolt(const unsigned int& inputVolt) {
			float temp;
			temp = float(inputVolt) * _ratio;
			if (temp < 0.1) return 0.0;
			return temp;
		}

	private:
		float _ratio;
};

#define _4_BIT 32.0
#define _6_BIT 64.0
#define _8_BIT 256.0
#define _10_BIT 1024.0
#define _12_BIT 4096.0
#define _14_BIT 16384.0
