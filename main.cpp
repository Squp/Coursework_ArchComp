#include "stdafx.h"

using namespace std;

void todo(int num1, int num2) {
	int result;
	int t1, t2;											// Вычисление погрешности
	int time[10];
	float t = 0;
	float miss = t = t1 = t2 = 0;
	int tmp1, tmp2;
	for (int i = 0; i < N; i++) {
		__asm{
			rdtsc
			mov[t1], eax
			rdtsc
			mov[t2], eax
		}
		miss = miss + (t2 - t1);
	}
	miss /= N;

	for (int i = 0; i < N; i++) {						// Сложение
		__asm {
			rdtsc
			mov[t1], eax
			mov ecx, [num1]
			mov edx, [num2]
			add ecx, edx
			mov [result], ecx
			rdtsc
			mov[t2], eax
			
		}
		t += (t2 - t1);
	}
	t /= N;
	t -= miss;

	cout << "Результат сложения двух чисенл типа int: " << num1 << " + " << num2 << " = " << result << endl;
	cout << "Среднее время операции с использованием регистров: " << (abs(t)) << endl;

	for (int i = 0; i < N; i++) {
		__asm {
			rdtsc
			mov[t1], eax
			mov ecx, [num1]
			add ecx, [num2]
			mov[result], ecx
			rdtsc
			mov[t2], eax

		}
		t += (t2 - t1);
	}
	t /= N;
	t -= miss;
	cout << "Среднее время операции без использованием регистров: " << (abs(t)) << endl;
	//cout << "Промах " << abs(miss) << endl;

	(long int)tmp1; tmp1 = num1;
	(short int)tmp2; tmp2 = num2;
	for (int i = 0; i < N; i++) {						// Сложение long int add short int
		__asm {
			rdtsc
			mov[t1], eax
			mov ecx, [tmp1]
			mov edx, [tmp2]
			add ecx, edx
			mov[result], ecx
			rdtsc
			mov[t2], eax

		}
		t += (t2 - t1);
	}
	t /= N;
	t -= miss;
	cout << "Результат сложения двух чисенл типа long int и short int: " << tmp1 << " + " << tmp2 << " = " << result << endl;
	cout << "Среднее время операции с использованием регистров: " << (abs(t)) << endl;

	for (int i = 0; i < N; i++) {
		__asm {
			rdtsc
			mov[t1], eax
			mov ecx, [tmp1]
			add ecx, [tmp2]
			mov[result], ecx
			rdtsc
			mov[t2], eax

		}
		t += (t2 - t1);
	}
	t /= N;
	t -= miss;
	cout << "Среднее время операции без использованием регистров: " << (abs(t)) << endl;

	t = 0;										//Операция вычитания с испольхованем регистров:
	for (int i = 0; i < N; i++) {
		__asm {
			rdtsc
			mov[t1], eax
			mov ecx, [num1]
			mov edx, [num2]
			sub ecx, edx
			mov[result], ecx
			rdtsc
			mov[t2], eax

		}
		//time[i] = (t2 - t1);
		t += (t2 - t1);
	}
	t /= N;
	t -= miss;
	cout << "Результат вычитания: " << num1 << " - " << num2 << " = " << result << endl;
	cout << "Среднее время операции с использованием регистров: " << ceil(abs(t)) << endl;
	t = 0;
	for (int i = 0; i < N; i++) {
		__asm {
			rdtsc
			mov[t1], eax
			mov ecx, [num1]
			sub ecx, [num2]
			mov[result], ecx
			rdtsc
			mov[t2], eax

		}
		//time[i] = (t2 - t1);
		t += (t2 - t1);
	}
	t /= N;
	t -= miss;
	cout << "Среднее время операции без использования регистров: " << ceil(abs(t)) << endl;
	cout << "Промах " << abs(miss) << endl;
	t = 0;
	for (int i = 0; i < N; i++) {						// Вычитание long int add short int
		__asm {
			rdtsc
			mov[t1], eax
			mov ecx, [tmp1]
			mov edx, [tmp2]
			sub ecx, edx
			mov[result], ecx
			rdtsc
			mov[t2], eax

		}
		t += (t2 - t1);
	}
	t /= N;
	t -= miss;
	cout << "Результат вычитания двух чисенл типа long int и short int: " << tmp1 << " - " << tmp2 << " = " << result << endl;
	cout << "Среднее время операции с использованием регистров: " << (abs(t)) << endl;
	t = 0;
	for (int i = 0; i < N; i++) {
		__asm {
			rdtsc
			mov[t1], eax
			mov ecx, [tmp1]
			sub ecx, [tmp2]
			mov[result], ecx
			rdtsc
			mov[t2], eax

		}
		t += (t2 - t1);
	}
	t /= N;
	t -= miss;
	cout << "Среднее время операции без использованием регистров: " << (abs(t)) << endl;

	// Деление int'ов
	t = 0;
	(long int)num1;
	(short int)num2;
	for (int i = 0; i < N; i++) {
		__asm {
			rdtsc
			mov[t1], eax
			mov eax, [num1]
			mov ecx, [num2]
			fdiv ecx
			mov[result], eax
			rdtsc
			mov[t2], eax

		}
		t += (t2 - t1);
	}
	t /= N;
	t -= miss;
	cout << "Результат деления двух чисел типа int: " << num1 << " / " << num2 << " = " << result << endl;
	cout << "Среднее время операции с использованием регистров: " << (abs(t)) << endl;

	// Деление long на short
	// ...
	// ...
}

void case1() {
	int num1;
	int num2;
	cout << "Введите два целочисленных числа" << endl;
	cin >> num1 >> num2;
	todo(num1, num2);
}

int case2() {
	return 0;
	float num1;
	float num2;
	cout << "Введите два числа с плавующей точкой" << endl;
	cin >> num1 >> num2;
	todo(num1, num2);

}

void menu() {
	int c;
	while (1) {
		cout << "Выберите действие:" << endl;
		cout << "1. Оценка производительности системы при выполнении целочисленных операций." << endl;
		cout << "2. Оценка производительности системы при выполнении операций с плавающей точкой." << endl;
		cin >> c;
		switch (c) {
		case 1:
			case1();
			break;
		case 2:
			case2();
			break;
		default:
			cout << "Ошибка" << endl;
		}
	}
	
}

int main()
{
	setlocale(0, "");
	menu();
    return 0;
}

