#include <iostream>
#include <cstdlib>
#include <ctime>

using std::cout;
using std::cin;
using std::endl;

class MyStack
{
private:
	unsigned int size{ 0 };
	unsigned int buf{ 0 };
	MyStack* next{ NULL };
	MyStack* _top{ NULL };
	MyStack** top = &_top;

public:
	void push(unsigned int _data)
	{
		MyStack* data = new MyStack;
		data->buf = _data;
		if (top == NULL)
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

	int pop()
	{
		if (top == NULL || size == 0)
		{
			cout << "It is impossible to extract! Stack is empty!" << endl;
			exit(1);
			return -1;
		}
		else
		{
			MyStack* data = *top;
			MyStack* _data = _top;
			*top = data->next;
			data->next = NULL;
			data = data->next;
			delete data;
			size--;
			return _data->buf;
		}
	}

	void print()
	{
		if (top == NULL || size == 0)
		{
			cout << "It is impossible to print! Stack is empty!" << endl;
		}
		else
		{
			cout << endl;
			MyStack* q = _top;
			while (q != NULL)
			{
				cout << q->buf << endl;
				q = q->next;
			}
		}
	}

	void check()
	{
		if (top == NULL || size == 0)
		{
			cout << "Stack is empty!"<<endl;
		}
		else
		{
			cout << "There are " << size << " elements in the stack";
		}
	}

	int getSize()
	{
		return size;
	}

	~MyStack()
	{
		while (size > 0)
		{
			MyStack* data = *top;
			*top = data->next;
			data->next = NULL;
			data = data->next;
			delete data;
			size--;
		}
	}
};

int increase(const void* x1, const void* x2)
{
	return (*(int*)x1 - *(int*)x2);
}

int decrease(const void* x1, const void* x2)
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

	cout << "Enter the size of 3rd stack:" << endl; //Вводим размер третьего стека
	int size3;
	while (!(cin >> size3) || (cin.peek() != '\n')) //Защита от ввода некорректных данных
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "Error! Enter again!" << endl;
	}

	cout << "Enter a range of numbers in 3rd stack:" << endl; //Вводим диапазон чисел внутри стека [1;range3]
	int range3;
	while (!(cin >> range3) || (cin.peek() != '\n'))
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "Error! Enter again!" << endl;
	}

	for (int q = 0; q < size3; q++) //Заполняем третий стек
	{
		stack3.push((rand() % range3) + 1);
	}

	cout << endl;

	cout << "Enter the size of 4th stack:" << endl;
	int size4;
	while (!(cin >> size4) || (cin.peek() != '\n'))
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "Error! Enter again!" << endl;
	}

	cout << "Enter a range of numbers in 4th stack:" << endl;
	int range4;
	while (!(cin >> range4) || (cin.peek() != '\n'))
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "Error! Enter again!" << endl;
	}

	for (int q = 0; q < size4; q++)
	{
		stack4.push((rand() % range4) + 1);
	}

	cout << endl;

	cout << "3rd stack:";
	stack3.print();
	cout << endl;

	cout << "4th stack:";
	stack4.print();

	
	int* arrof3 = new int[size3]; //Создаём динамический массив для данных стека
	int* arrof4 = new int[size4];

	for (int q = 0; q < size3; q++) //Заполняем массив значениями из стека
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

	int* oddArr = new int[odd](); //Создаём динамический массив с нечётными числами
	int* evenArr = new int[even](); //Создаём динамический массив с чётными числами

	int _odd = 0; //Переменная-счётчик для заполнения массива с нечётными числами
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

	qsort(oddArr, odd, sizeof(int), increase); //Сортировка нечётного массива
	qsort(evenArr, even, sizeof(int), decrease); //Сортировка чётного массива
	
	for (int q = 0; q < even; q++) //Заполнение первого стека
	{
		stack1.push(evenArr[q]);
	}

	for (int q = 0; q < odd; q++)
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