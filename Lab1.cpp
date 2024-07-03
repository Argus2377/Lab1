#include <iostream>
#include <cstdlib>
#include <ctime>

using std::cout;
using std::cin;
using std::endl;

class MyStack
{
private:
	unsigned int size{ 0 }; // Размер стека
	unsigned int buf{ 0 };  // Данные стека
	MyStack* next{ NULL };  // Указатель наследующий элемент
	MyStack* _top{ NULL };  // Указатель на вершину стека
	MyStack** top = &_top;  // Указатель на указатель позволяет изменять вершину в главной функции

public:
	void push(unsigned int _data)    // Метод добавления элемента в стек
	{
		MyStack* data = new MyStack; // Выделяем память для временого элемента
		data->buf = _data;           // Добавляем элемент
		if (top == NULL)             // Формируем указатель на новую вершину
		{
			_top = data;
		}
		else
		{
			data->next = *top;
			*top = data;
		}
		size++;
	}

	int pop()                         // Метод извлечения элемента из стека
	{
		if (top == NULL || size == 0) // Проверка на заполненность
		{
			cout << "It is impossible to extract! Stack is empty!" << endl;
			exit(1);
			return -1;
		}
		else
		{
			MyStack* data = *top;
			MyStack* _data = _top;
			*top = data->next;         // Изменяем указатель для новой вершины
			data->next = NULL;
			data = data->next;
			delete data;               // Освобождаем память
			size--;
			return _data->buf;         //Возвращаем значение вершины
		}
	}

	void print()                        // Метод вывода стека
	{
		if (top == NULL || size == 0)   // Проверка на заполненность
		{
			cout << "It is impossible to print! Stack is empty!" << endl;
		}
		else
		{
			cout << endl;
			MyStack* q = _top;           // Создаём временный указатель
			while (q != NULL)
			{
				cout << q->buf << endl; //Выводим элемент стека
				q = q->next;            // Изменяем временный указатель
			}
		}
	}

	void check()                                                      // Проверка состояния стека
	{
		if (top == NULL || size == 0)
		{
			cout << "Stack is empty!"<<endl;
		}
		else
		{
			cout << "There are " << size << " elements in the stack"; // Выводим текущий размер стека
		}
	}

	int getSize() // Метод получения размера стека
	{
		return size;
	}

	~MyStack()           // Деструктор, удаляющий стеки
	{
		while (size > 0) // Аналогично методу "pop"
		{
			MyStack* data = *top;
			*top = data->next;
			data->next = NULL;
			data = data->next;
			delete data;
			size--;
		}
		next = NULL;
		_top = NULL;
		*top = NULL;
		top = NULL;
	}
};

int increase(const void* x1, const void* x2) // Компоратор для сортировки по возрастанию
{
	return (*(int*)x1 - *(int*)x2);
}

int decrease(const void* x1, const void* x2) // Компоратор для сортировки по убыванию
{
	return (*(int*)x2 - *(int*)x1);
}

int main()
{
	MyStack stack1; //Стек для чётных чисел в порядке не убывания
	MyStack stack2; //Стек для нечётных чисел в порядке невозрастания
	MyStack stack3; //Стек с числами
	MyStack stack4; //Стек с числами

	srand(static_cast<unsigned int>(time(0))); //Инициализация генератора случайных чисел

	cout << "Enter the size of 3rd stack:" << endl;
	int size3;                                                      // Размер 3го стека
	while ((!(cin >> size3) || (cin.peek() != '\n')) || size3 <= 0) //Защита от ввода некорректных данных
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "Error! Enter again!" << endl;
	}

	cout << "Enter a range of numbers in 3rd stack:" << endl;
	int range3;                                                       // Диапазон значений 3го стека
	while ((!(cin >> range3) || (cin.peek() != '\n')) || range3 <= 0) //Защита от ввода некорректных данных
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "Error! Enter again!" << endl;
	}

	for (int q = 0; q < size3; q++)                                //Заполняем третий стек
	{
		stack3.push((rand() % range3) + 1);
	}

	cout << endl;

	cout << "Enter the size of 4th stack:" << endl;
	int size4;                                                      // Размер 4го стека
	while ((!(cin >> size4) || (cin.peek() != '\n')) || size4 <= 0)  //Защита от ввода некорректных данных
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "Error! Enter again!" << endl;
	}

	cout << "Enter a range of numbers in 4th stack:" << endl;
	int range4;                                                      // Диапазон значений 4го стека
	while ((!(cin >> range4) || (cin.peek() != '\n')) || range4 <= 0) //Защита от ввода некорректных данных
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "Error! Enter again!" << endl;
	}

	for (int q = 0; q < size4; q++)                                  //Заполняем четвёртый стек
	{
		stack4.push((rand() % range4) + 1);
	}

	cout << endl;

	cout << "3rd stack:";
	stack3.print(); // Выводим третий стек
	cout << endl;

	cout << "4th stack:";
	stack4.print(); // Выводим четвёртый стек

	
	int* arrof3 = new int[size3]; //Создаём динамические массивы для данных стеков
	int* arrof4 = new int[size4];

	for (int q = 0; q < size3; q++) //Заполняем массивы значениями из стеков
	{
		arrof3[q] = stack3.pop();
	}

	for (int q = 0; q < size4; q++)
	{
		arrof4[q] = stack4.pop();
	}

	int odd = 0; //Переменная для подсчёта нечётных чисел в двух стеках
	int even = 0; //Переменная для подсчёта чётных чисел в двух стеках

	for (int q = 0; q < size3; q++)
	{
		if ((arrof3[q] % 2) != 0)
		{
			odd++;
		}
		else
		{
			even++;
		}
	}

	for (int q = 0; q < size4; q++)
	{
		if ((arrof4[q] % 2) != 0)
		{
			odd++;
		}
		else
		{
			even++;
		}
	}

	int* oddArr = new int[odd]();   //Создаём динамический массив с нечётными числами
	int* evenArr = new int[even](); //Создаём динамический массив с чётными числами

	int _odd = 0;  //Переменная-счётчик для заполнения массива с нечётными числами
	int _even = 0; //Переменная-счётчик для заполнения массива с чётными числами

	for (int q = 0; q < (size3 + size4); q++)
	{
		if (q < size3) {
			if ((arrof3[q] % 2) != 0)
			{
				oddArr[_odd] = arrof3[q];
				_odd++;
			}
			else
			{
				evenArr[_even] = arrof3[q];
				_even++;
			}
		}
		else
		{
			if ((arrof4[q - size3] % 2) != 0)
			{
				oddArr[_odd] = arrof4[q - size3];
				_odd++;
			}
			else
			{
				evenArr[_even] = arrof4[q - size3];
				_even++;
			}
		}
	}

	delete[] arrof3; //Освобождаем память, которую занимали динамические массивы,
	delete[] arrof4; //хранящие значения из стеков

	qsort(oddArr, odd, sizeof(int), increase);   //Сортировка нечётного массива
	qsort(evenArr, even, sizeof(int), decrease); //Сортировка чётного массива
	
	for (int q = 0; q < even; q++) //Заполнение первого стека
	{
		stack1.push(evenArr[q]);
	}

	for (int q = 0; q < odd; q++) //Заполнение второго стека
	{
		stack2.push(oddArr[q]);
	}

	delete[] oddArr; //Освобождаем память, которую занимали динамические массивы,
	delete[] evenArr; //хранящие чётные и нечётные числа

	cout << endl << "1st stack:";//Вывод полученных стеков
	stack1.print();

	cout << endl << "2nd stack:";
	stack2.print();

	return 0;
}