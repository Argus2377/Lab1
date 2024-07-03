#include <iostream>

using std::cout;
using std::cin;
using std::endl;



int main()
{
	int size{ 0 }; //Размер сортируемого массива

	cout << "Enter the size:" << endl;
	cout << "Size:";
	while ((!(cin >> size) || (cin.peek() != '\n')) || (size <= 0)) //Защищённый ввод размера
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "Error! Enter again!" << endl;
		cout << "Size:";
	}

	cout << endl << "Enter the elements:" << endl;

	int* element = new int[size](); //Массив для эоементов

	for (int q = 0; q < size; q++)  //Ввод сортируемых элементов
	{
		cout << "Element #" << q+1 <<": ";
		while (!(cin >> element[q]) || (cin.peek() != '\n'))
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "Error! Enter again!" << endl;
			cout << "Element #" << q+1 << ": ";
		}
	}

	for (int q = 0; q < size - 1; q++)                        //Алгоритм сортировки пузырьком
	{
		for (int i = 0; i < size - 1; i++)
		{
			if (element[i + 1] < element[i])
			{
				element[i + 1] = element[i + 1] + element[i]; //Алгоритм обмена значениями
				element[i] = element[i + 1] - element[i];
				element[i + 1] = element[i + 1] - element[i];
			}
		}
	}

	cout << endl << endl << "Sorted:" << endl;

	for (int q = 0; q < size; q++) //Вывод отсортированного массива
	{
		cout << "Element #" << q+1 << ": " << element[q]<<endl;
	}

	delete[] element;              //Освобождение памяти

	return 0;
}