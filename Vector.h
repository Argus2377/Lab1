#ifndef _Vector_H_
#define _Vector_H_

#include <iostream>
using std::cout;

template <class T>
class  MyVector
{
private:
    int size{ 0 };     //Количество элементов в векторе
    int capacity{ 0 }; //Размер вектора
    T* buffer{ NULL }; //Динамический массив элементов

public:
    T& operator[](int index) //Перегруз оператораа []
    {
        return buffer[index];
    }

    void memory(int _capacity) //Выделение памяти для вектора
    {
        T* NewBuffer = new T[_capacity];
        int numderOfElements = _capacity < size ? _capacity : size;

        for (int i = 0; i < numderOfElements; i++)
        {
            NewBuffer[i] = buffer[i];
        }

        capacity = _capacity;

        delete[] buffer;
        buffer = NewBuffer;
    }

    void push(const T& element) //Добавление элемента в вектор
    {
        if (size >= capacity)
        {
            memory(capacity + 5);
        }
        buffer[size++] = element;
    }

    int getSize() //Размер вектора
    {
        return size;
    }

    ~MyVector()
    {
        delete[] buffer;
    }
};

#endif