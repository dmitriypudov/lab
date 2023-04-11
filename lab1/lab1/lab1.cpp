#include <iostream>
#include <iomanip>
#include <cstddef>
#include <bitset>

using namespace std;

class Assembler
{
public:


	// Сложение
	void add(int32_t valueOne, int32_t valueTwo) {
		int32_t result;
		__asm
		{
			mov eax, valueOne
			add eax, valueTwo

			mov result, eax
		}
		std::cout << "\n" << setw(25) << "ADD: " << result;
	}


	// Вычитание
	void sub(int32_t valueOne, int32_t valueTwo)
	{
		int32_t result;
		__asm
		{
			mov eax, valueOne
			sub eax, valueTwo

			mov result, eax
		}

		std::cout << "\n" << setw(25) << "SUB: " << result;
	}

	// Умножение
	void mul(int32_t valueOne, int32_t valueTwo)
	{
		int32_t result;
		__asm
		{
			mov eax, valueOne
			mov ebx, valueTwo

			mul ebx

			mov result, eax
		}
		std::cout << "\n" << setw(25) << "MUL: " << result;
	}


	// Деление
	void div(int32_t valueOne, int32_t valueTwo)
	{
		int32_t result;
		__asm
		{
			mov eax, valueOne
			mov ebx, valueTwo
			mov edx, 0

			div ebx

			mov result, eax
		}
		std::cout << "\n" << setw(25) << "DIV: " << result;
	}

	// Сравнение
	void cmp_ja(int32_t valueOne, int32_t valueTwo)
	{
		int32_t result;
		__asm
		{
			mov eax, valueOne
			cmp eax, valueTwo
			ja L0
			mov eax, valueTwo
			mov result, eax

			L0 : mov result, eax
		}
		std::cout << "\n" << setw(25) << "a > b ? a : b = " << result << "\t c++ : " << (valueOne > valueTwo ? valueOne : valueTwo);
	}


	// Приравнивание
	void cmp_je(int32_t valueOne, int32_t valueTwo)
	{
		int32_t result;
		__asm
		{
			mov eax, valueOne
			cmp eax, valueTwo
			je L1
			mov eax, 0
			mov result, eax

			L1 : mov result, eax
		}
		std::cout << "\n" << setw(25) << "a == b ? a : 0 = " << result << "\t c++ : " << (valueOne == valueTwo ? valueOne : 0);
	}

	// Отрицание
	void not_asm(uint16_t byte_1) {
		uint16_t result;
		__asm
		{
			mov ax, byte_1
			not ax

			mov result, ax
		}

		std::cout << "\n" << setw(25) << "NOT: " << std::bitset<8>{result} << "\t BYTE_1: " << std::bitset<8>{byte_1};
	}

	// Умножение (Конъюнкция)
	void and_asm(uint16_t byte_1, uint16_t byte_2) {
		uint16_t result;
		__asm
		{
			mov ax, byte_1
			mov bx, byte_2

			and ax, bx

			mov result, ax
		}

		std::cout << "\n" << setw(25) << "AND: " << std::bitset<8>{result} << "\t BYTE_2: " << std::bitset<8>{byte_2};
	}

	// Сложение (Дизъюнкция)
	void or_asm(uint16_t byte_1, uint16_t byte_2) {
		uint16_t result;
		__asm
		{
			mov ax, byte_1
			mov bx, byte_2

			or ax, bx

			mov result, ax
		}

		std::cout << "\n" << setw(25) << "OR: " << std::bitset<8>{result};
	}

	// "Исключающее ИЛИ" (XOR)
	void xor_asm(uint16_t byte_1, uint16_t byte_2) {
		uint16_t result;
		__asm
		{
			mov ax, byte_1
			mov bx, byte_2

			xor ax, bx

			mov result, ax
		}

		std::cout << "\n" << setw(25) << "XOR: " << std::bitset<8>{result} << '\n';
	}

	//  Возвращает сумму значений массива
	void sum_array() {
		int32_t result = 0;

		const int n = 10;
		int sum = 0;
		int mass[n]{};

		for (size_t i = 0; i < n; i++)
			mass[i] = rand() % 100 + 1;

		for (size_t i = 0; i < n; i++)
			cout << "[" << i << "] " << mass[i] << " ";


		// __asm вызывает встроенный ассемблер
		__asm
		{
			mov eax, sum
			mov ecx, n
			lea ebx, mass

			L :
				add eax, [ebx]
				add ebx, type mass
				dec ecx
				cmp ecx, 0
				jne L

				mov result, eax
		}

		cout << "\nASM_SUM: " << result;
	}

	// Сдвиг по массиву
	void shift(bool isRightShift, uint16_t byteValue) {
		uint16_t result;

		switch (isRightShift)
		{
		case true:
			__asm
			{
				mov ax, byteValue
				shr ax, 1

				mov result, ax
			}

			std::cout << "\n" << setw(25) << "SHIFT RIGHT: " << result << '\t' << std::bitset<16>{result} << '\n';
			break;
		case false:
			__asm
			{
				mov ax, byteValue
				shl ax, 1

				mov result, ax
			}

			std::cout << "\n" << setw(25) << "SHIFT LEFT: " << result << '\t' << std::bitset<16>{result};
			break;
		default:
			break;
		}
	}

};

int main()
{

	int32_t a, b;
	int32_t result;

	std::cout << "Enter: ";
	cin >> a >> b;

	cout << setiosflags(ios::right);
	cout << '\n' << "a = " << a << " b = " << b;

	Assembler asmr;
	asmr.add(a, b);
	asmr.sub(a, b);
	asmr.mul(a, b);
	asmr.div(a, b);
	asmr.cmp_ja(a, b);
	asmr.cmp_je(a, b);


	uint16_t byteOne, byteTwo;

	std::cout << "\nEnter bytes: ";
	std::cin >> byteOne >> byteTwo;

	asmr.not_asm(byteOne);
	asmr.and_asm(byteOne, byteTwo);
	asmr.or_asm(byteOne, byteTwo);
	asmr.xor_asm(byteOne, byteTwo);
	asmr.sum_array();
	asmr.shift(true, byteOne);
	asmr.shift(false, byteTwo);

	return 0;
}