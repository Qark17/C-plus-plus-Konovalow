//#include "D:\VSCODE\CODE C++\Codes 2.1\C++ Code 1\Matrix\Solver\Array.h"
//#include "D:\VSCODE\CODE C++\Codes 2.1\C++ Code 1\Matrix\Solver\Generator.h"
#include"../Solver/Array.h"
#include"../Solver/Generator.h"
#include <iostream>
using namespace std;

int getValueInt(string message);
size_t getValue(string message);
enum Cin
{
	randomArray = 1, cinArray = 2,
};
enum Action
{
	replacement = 1, pop = 2, newArray = 3,
};

int main()
{
	setlocale(LC_ALL, "Russian");
	Array normArray;
	size_t size = getValue("Введите размер массива: ");
	cout << "Как создать массив? Рандомом - введите " << Cin::randomArray << ". Вручную - " << cinArray;
	int choiceCin = getValueInt("");
	switch ((enum Cin)choiceCin)
	{
	case Cin::randomArray:
	{
		int min, max;
		cout << "Введите минимальный элемент: ";
		cin >> min;
		cout << "Введите максимальный элемент: ";
		cin >> max;
		normArray = Array(size);
		Generator gen(min, max);
		normArray.fill(gen);
		normArray.coutArray();
		break;
	}
	case Cin::cinArray:
	{
		normArray = Array(size);
		Generator gen(cin);
		normArray.fill(gen);
		normArray.coutArray();
		break;
	}
	default:
	{
		cout << "Нет такого выбора.";
		normArray = Array();
		break;
	}
	}
	cout << "Какое действие выполнить над массивом? Добавить замена - введите " << Action::replacement <<
		", удалить элементы - " << Action::pop << ", построить новую матрицу - " << Action::newArray;
	int choiceDo = getValueInt("");
	switch ((enum Action)choiceDo)
	{
	case Action::replacement:
	{
		if (!normArray.replacement())
			cout << "Заменять нечего.";
		normArray.coutArray();
		break;
	}
	case Action::pop:
	{
		if (!normArray.pop())
		{
			cout << "Удалять нечего.";
		}
		normArray.coutArray();
		break;
	}
	case Action::newArray:
	{
		if (normArray.checkEmpty())
		{
			cout << "Пустой массив.";
		}
		else
		{
			normArray.coutArray();
		}
		break;
	}
	default:
	{
		cout << "Нет такого выбора.";
		normArray.clear();
		return 1;
	}
	}
	return 0;
}

int getValueInt(string message)
{
	cout << message << endl;
	int value = 0;
	cin >> value;
	if (cin.fail())
	{
		cout << "Ошибка ввода!" << endl;
		exit(1);
	}
	return value;
}
size_t getValue(string message)
{
	cout << message << endl;
	int value = 0;
	cin >> value;
	if (cin.fail() || value < 0)
	{
		cout << "Длина минимум нулевая!" << endl;
		exit(1);
	}
	return value;
}