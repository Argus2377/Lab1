#include <iostream>
#include <cmath>
#include "Vector.h"

using std::cout;
using std::cin;
using std::endl;

int main()
{
	cout << "Enter b:" << endl;
	cout << "b = ";

	int b; //Число b, с которым сравниваются остальные числа
	while (!(cin >> b) || (cin.peek() != '\n')) //Защита
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "Error! Enter again!" << endl;
	}
	cout << endl << endl;


	MyVector <int> elements;  //Вектор с элементами
	MyVector <int> i;         //Вектор с координатой I
	MyVector <int> j;         //Вектор с координатой J
	MyVector <int> less;      //Вектор для чисел меньше b
	MyVector <int> more;      //Вектор для чисел больше b
	int buf{ 0 };             //Буфер значений
	int I{ 0 };               //Буфер для координаты I
	int J{ 0 };               //Буфер для координаты J
	int M{ 0 };               //Столбцы
	int N{ 0 };               //Строки

	cout << "Enter the size of the matrix:" << endl; //Ввод размеров матрицы
	cout << "M:";
	while ((!(cin >> M) || (cin.peek() != '\n')) || (M == 0))
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "Error! Enter again!" << endl;
		cout << "M:";
	}
	cout << "N:";
	while ((!(cin >> N) || (cin.peek() != '\n')) || (N == 0))
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "Error! Enter again!" << endl;
		cout << "N:";
	}

	cout << "Enter the elements:" << endl; //Ввод элементов; производится до ввода символа
	cout << "The element:";
	while (cin >> buf)
	{
		elements.push(buf);               //занесение значения в соответствующий стек
		cout << "Enter the coordinates:" << endl;
		cout << "I:";
		while ((!(cin >> I) || (cin.peek() != '\n')) || (I > M) || (I == 0))
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "Error! Enter again!" << endl << "Incorrect data may have been entered or";
			cout << endl << "the element coordinates may be out of the matrix range" << endl;
			cout << "I:";
		}
		i.push(I);

		cout << "J:";
		while ((!(cin >> J) || (cin.peek() != '\n')) || (J > N) || (J == 0))
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "Error! Enter again!" << endl << "Incorrect data may have been entered or";
			cout << endl << "the element coordinates may be out of the matrix range" << endl;
			cout << "J:";
		}
		j.push(J);

		cout << endl << "The element:";
	}

	int p = elements.getSize();        //Переменная для создания динамических массивов


	int* A = new int[p];	 //Массив значений
	int* index = new int[p]; //Массив индексов
	int* LI = new int[p];    //Массив LI
	int* LJ = new int[p];    //Массив LJ

	for (int q = 0; q < p; q++) //Заполнение массивов
	{
		index[q] = q + 1;
	}

	for (int q = 0; q < p; q++)
	{
		A[q] = elements[q];
	}

	for (int q = 0; q < p; q++)
	{
		LI[q] = i[q];
	}

	for (int q = 0; q < p; q++)
	{
		LJ[q] = j[q];
	}

	cout << "A:";
	for (int q = 0; q < p; q++) //Вывод массивов
	{
		cout << A[q] << " ";
	}
	cout << endl << "N:";
	for (int q = 0; q < p; q++)
	{
		cout << index[q] << " ";
	}
	cout << endl << "LJ:";
	for (int q = 0; q < p; q++)
	{
		cout << LJ[q] << " ";
	}
	cout << endl << "LI:";
	for (int q = 0; q < p; q++)
	{
		cout << LI[q] << " ";
	}

	for (int q = 0; q < p; q++) //Заполнение соответствующих стеков элементами больше и меньше b
	{
		if ((A[q] != 0) && (A[q] < b))
		{
			less.push(A[q]);
		}
		if ((A[q] != 0) && (A[q] >= b))
		{
			more.push(A[q]);
		}
	}

	int pless = less.getSize(); //Количество элементов меньше b
	int pmore = more.getSize(); //Количество элементов больше b

	int* arrLess = new int[pless](); //Массив чисел меньших b
	int* arrMore = new int[pmore](); //Массив чисел больших b

	for (int q = 0; q < pless; q++)  //Заполнение массивов
	{
		arrLess[q] = less[q];
	}

	for (int q = 0; q < pmore; q++)
	{
		arrMore[q] = more[q];
	}


	int rows{ 0 };             //Количество строк
	int count = pless + pmore; //Счётчик

	while (count > 0)          //Вычисление количества строк
	{
		rows++;
		count -= M;
	}


	if (rows == 1)
	{
		for (int q = 0; q < (pless + pmore); q++) //Перемещение элементов в начало
		{
			if (q < pmore)
			{
				A[q] = arrMore[q];
				LI[q] = q + 1;
				LJ[q] = 1;
			}
			else
			{
				A[q] = arrLess[q - pmore];
				LI[q] = q + 1;
				LJ[q] = 1;
			}
		}
	}

	else
	{
		int counter = pless + pmore;

		for (int qj = 0; qj < rows; qj++)
		{
			for (int qi = 0; qi < M; qi++)
			{
				if (counter != 0)
				{
					if (qi < pmore)
					{
						A[qi] = arrMore[qi];
						LI[qi] = qi + 1;
						LJ[qi] = qj + 1;
					}
					else
					{
						A[qi] = arrLess[qi - pmore];
						LI[qi] = qi + 1;
						LJ[qi] = qj + 1;
					}
					counter--;
				}
				else
				{
					break;
				}
			}
		}
	}


	cout << endl << endl << "A*:";
	for (int q = 0; q < p; q++) //Вывод полученных данных
	{
		cout << A[q] << " ";
	}
	cout << endl << "N*:";
	for (int q = 0; q < p; q++)
	{
		cout << index[q] << " ";
	}
	cout << endl << "LJ*:";
	for (int q = 0; q < p; q++)
	{
		cout << LJ[q] << " ";
	}
	cout << endl << "LI*:";
	for (int q = 0; q < p; q++)
	{
		cout << LI[q] << " ";
	}

	delete[] arrLess; //Освобождение памяти
	delete[] arrMore;
	delete[] A;
	delete[] index;
	delete[] LI;
	delete[] LJ;


	return 0;
}