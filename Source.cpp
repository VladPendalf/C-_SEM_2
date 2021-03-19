#include <iostream>

using namespace std;

/*
			�������� ������������
					A1
					|
					|
					|
				 __	B1__
				/		\
			   /		 \
			  /			  \
			 C1            C2
			  
���������� ����������� ��������� ����� ������������. � ����� �0� �1 ��������� ��� ������� B1, B2.
	1 ������ ����� �������� ���������� ����������. 
��������: A1�������� ���������� a1, B1 � b1, C2 � c2 � �.�. ������ ����� ����������������, ������������� ���� ���������� ����� ��������.
������������ ����������� ������� ������ �������� ������������ ������� ������� � ���������� ���� ���������.
	2 � ������� ������� ����������� ������� print(), ������� ������� �� ������� ��� ������, �� �������� ��� �������. � ����������� �������
�������������� �, ����� ��� �������� ���������� ���������.

��������:
A1 a;
a.print(); => �A1�
B1 b;
b.print(); => �B1�

	3 �������� ������� show(), ������� ������� ��� ��������� ��� ����� ������ ����������. ��������, � ������ B1 �������� ���������
���������� ������ B1 � ��������� ���������� �� ������������� ������ A1. 

�������������� � � ����������� �������.
A1 a;
a.show(); => ������ ���������� � A1
B1 b;
b.show(); => ���������� �� B1 � A1

*/



class A1
{
protected:
	int a1 = 0;
public:
	A1(int val = 0) : a1(val) {};
	virtual void print() { cout << "\n \t -> �1\n"; }
	virtual void show() { cout << "\nA1 = " << a1 << '\t'<< endl; }
};

class B1 : virtual public A1
{
protected:
	int b1 = 0;
public:
	B1(int val, int val_2) : b1(val), A1(val_2) {};
	void print() { cout << "\n\t ->B1\n"; }
	void show() { cout << "\nA1 = " << a1 << "\tB1 = " << b1 << endl;  }
};

class C1 : public B1
{
protected:
	int c1 = 0;
public:
	C1(int val, int val_2, int val_3) :c1(val), B1(val_2, val_3), A1(val_3) {}; //��������� 2 ������������ ,�.�. ����� ������ ���� �� �������
	void print() { cout << "\n\t ->C1\n"; }
	void show() { cout << "\nA1 = " << a1 << "\tB1 = " << b1 << "\tC1 = " << c1<< endl; }
};

class C2 : public B1
{
protected:
	int c2 = 0;
public:
	C2(int val, int val_2, int val_3) :c2(val), B1(val_2, val_3), A1(val_3) {};
	void print() { cout << "\n\t ->C2\n"; }
	void show() { cout << "\nA1 = " << a1 << "\tB1 = " << b1 << "\tC2 = " << c2 << endl; }
};

int main()
{
	setlocale(LC_ALL, "Ru-ru");

	B1 b1(5,4);
	b1.print();
	b1.show();

	A1* a1 = &b1;
	a1->print();
	a1->show();

	C1 c1(3, 4, 5);
	c1.print();
	c1.show();

	B1* b2 = &c1;
	b2->print();
	b2->show();


	return 0;
}