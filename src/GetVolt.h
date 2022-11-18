/*
	Библиотека для получения температуры процессора микроконтроллеров AVR
	GitHub: https://github.com/alexkor433/GetVolt

	Возможности:
	- получение напряжения
	- возможность работы с делителем напряжения и без
	- настройка сопротивления резисторов и параметра калибровки
	- возможность изменения параметров из программы

	MIT License

	Версии:
	v1.0 - релиз;
	v1.1 - получение "сырых" 5 вольт (без делителя напряжения);
	v1.2 - теперь калибровочное значение можно менять из программы;
	v2.0 - полностью переработана структура программы, добавил функцию для изменения параметров из кода
	облегчена работа с библиотекой, оптимизация. //18.11.22
*/

#pragma once

class GetVolt {
	public:
		// конструктор для измерения напряжения с делителем напряжения и калибровочным параметром
		GetVolt(float r1, float r2, float calibration) { 
			setParameters(r1, r2, calibration);
		}
		
		// конструктор для получения напряжения без делителя напряжения
		GetVolt(float calibration) {
			setParameters(calibration);
		}

		// функции установки параметров (можно вызывать из программы)
		void setParameters (float r1, float r2, float calibration) { // сопротивления резисторов и праметр калибровки
			_R = r2 / (r1 + r2);
			_calibration = calibration;
		}

		void setParameters (float calibration) { // только параметр калибровки
			_calibration = calibration;
		}
		
		// возвращает напряжение
		float getVolt(unsigned int inputVolt) {
			float temp;
			temp = inputVolt * _calibration / _R * 1024.0;
			if (temp  < 0.1) return 0.0;
			return temp;
		}
		
		// возвращает напряжение без делителей
		float getRawVolt (unsigned int inputRawVolt) {
			float temp;
			temp = inputRawVolt * _calibration / 1024.0;
			if (temp < 0.1) return 0.0;
			return temp;
		}

	private:
		float _calibration;
		float _R;
};