#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;

int N{ 0 }; //число детей у узла

struct Tree;

struct Child
{
	Tree* child;//указатель на сына
	Child* next;//указатель на следующий элемент
};

struct Tree
{
	Child* first; //указатель на первый элемент списка
	const char* name;//указатель на массив символов
	Tree* parent;//указатель на родителя
};

void createNode(Tree* parent, const char* n) //функция создания узла
{
	Child* _child = parent->first;
	int q{ 0 }; //счётчик детей
	while (_child != NULL)
	{
		if (!strcmp(_child->child->name, n)) //проверка на существование такого же узла
		{
			cout << "Such a node already exists!" << endl;
			return;
		}
		_child = _child->next;
		q++;
		if (q == N)//проверка на переполнение
		{
			cout << "Too many nodes!" << endl;
			return;
		}
	}

	int len = strlen(n); //строка для занесения названия
	char* newname = new char[len + 1];
	strncpy_s(newname, len + 1, n, len);
	newname[len] = 0;

	Tree* newtree = new Tree;//создание
	newtree->name = newname;
	newtree->first = NULL;
	newtree->parent = parent;
	_child = new Child;
	_child->child = newtree;
	_child->next = parent->first;
	parent->first = _child;
}

Tree* getNode(Tree* parent, const char* n)//функция получения адреса дочернего элемента
{
	Child* _child = parent->first;
	while (_child != NULL)
	{
		if (!strcmp(_child->child->name, n))
		{
			return _child->child;
		}
		_child = _child->next;
	}
	return parent;
}

void deleteTree(Tree* tree) //функция удаления поддерева
{
	if (tree != NULL)
	{
		Child* _child = tree->first;
		while (_child != NULL)
		{
			deleteTree(_child->child);
			Child* newchild = _child->next;
			delete(newchild);
			_child = newchild;
		}
		delete[] tree->name;
		delete tree;
	}
}

Tree* createTree(int n) //Создание дерева
{
	char* root = new char[2];
	if (n == 1)root[0] = 'A'; //Основное дерево
	else root[0] = 'B'; //Вспомогательное дерево
	root[1] = 0;
	Tree* newtree = new Tree;
	newtree->name = root;
	newtree->first = NULL;
	newtree->parent = NULL;
	return newtree;
}

void printPath(Tree* tree)
{
	Tree* _parent = tree->parent;
	if (_parent != NULL)
	{
		printPath(_parent);
		cout << '/';
	}
	cout << tree->name;
}

void printChildren(Tree* tree) //функция вывода дочерних узлов
{
	Child* _child = tree->first;

	if (_child == NULL)//проверка на наличие элементов
	{
		cout << "Elements are missing";
	}
	else
	{
		while (_child != NULL)
		{
			cout << _child->child->name << ' ';
			_child = _child->next;
		}
	}
	cout << endl;
}

bool equals(Tree* tree1, Tree* tree2) //Проверка на равенство
{
	if (tree1 == NULL && tree2 == NULL)
	{
		return true;
	}

	if (tree1 != NULL && tree2 == NULL)
	{
		return false;
	}

	if (tree1 == NULL && tree2 != NULL)
	{
		return false;
	}

	Child* child1 = tree1->first;
	Child* child2 = tree2->first;

	while (child1 != NULL && child2 != NULL)
	{
		if (!equals(child1->child, child2->child))
		{
			return false;
		}
		child1 = child1->next;
		child2 = child2->next;
	}

	if (child1 == NULL && child2 == NULL)
	{
		return true;
	}
	return false;
}

void find(Tree* tree1, Tree* tree2) //поиск равной структуры
{
	if (tree1 == NULL)
	{
		return;
	}

	if (equals(tree1, tree2))
	{
		printPath(tree1);
		cout << " == B" << endl;
	}
	else {
		Child* _child = tree1->first;
		while (_child != NULL)
		{
			find(_child->child, tree2);
			_child = _child->next;
		}
	}
}

int main()
{

	cout << "Enter the N: ";
	while ((!(cin >> N) || (cin.peek() != '\n')) || N <= 0)
		//Защита от ввода некорректных данных
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "Error! Enter again!" << endl;
	}

	cout << endl << "A - moving to the main tree" << endl;
	cout << "B - transition to the desired structure" << endl;
	cout << "+xxx - creating a new node xxx in the current subtree" << endl;
	cout << "/xxx - moving to the xxx subtree" << endl;
	cout << "/.. - upgrade to a higher level" << endl;
	cout << "! - output to a list of child nodes" << endl;
	cout << "\"?\" - search in A for structure B" << endl;
	cout << "\"stop\" - exit" << endl << endl;

	Tree* tree1 = createTree(1);//создаем пустое дерево A
	Tree* tree2 = createTree(2);//дерево B для сравнения
	Tree* current = tree1;
	char buf[256];//буфер для чтения из консоли
	char s; //вспомогательный буфер
	do
	{
		printPath(current);//вывод пути к текущему узлу дерева
		cout << "> ";
		cin >> buf;
		s = buf[0];
		if (s == 'A')
		{
			current = tree1;
		}
		else
		{
			if (s == 'B')
			{
				current = tree2;
			}
			else
			{
				if (s == '/')
				{
					if (buf[1] == '.' && buf[2] == '.')
					{
						if (current->parent != NULL)current = current->parent;
					}
					else
					{
						current = getNode(current, buf + 1);
					}
				}
				else
				{
					if (s == '+')
					{
						createNode(current, buf + 1);
					}
					else
					{
						if (s == '!')
						{
							printChildren(current);
						}
						else
						{
							if (s == '?')
							{
								find(tree1, tree2);
							}
							else
							{
								if ((s == 's') && (buf[1] == 't') && (buf[1] == 'o') && (buf[1] == 'p'))
								{
									break;
								}
								else
								{
									cout << "Error" << endl;
								}
							}
						}
					}
				}
			}
		}
		buf[0] = 0;
	} while (true);

	deleteTree(tree1);
	deleteTree(tree2);

	return 0;
}