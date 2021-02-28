#include <iostream>
#include <algorithm>


using namespace std;


//-------------------------��-------------------------------------------|
//����� ����� - �������� � ����� ������ , ��������� ������ ����� (1.1)  |
//����� ��������� �� ����� - �������� ������ ����� � ����� (1.2)		|
//----------------------------------------------------------------------|




class Fraction
{
protected:
	int denominator; //�����������
	int numerator; //���������
public:
	//������������
	Fraction() :numerator(1), denominator(1) {  }; //�� ���������

	Fraction(const Fraction& fraction) :numerator(fraction.numerator), denominator(fraction.denominator) {  }; //�����������

	Fraction(const int& val_1,const int& val_2) :numerator(val_1), denominator(val_2) {  };//�������

	~Fraction() {  }//����������

	//����������
	void show(); //����� �����
	
	int get_den(); //������
	
	int get_num();//������

	void set_num(const int& num); //������

	void set_den(const int& num); //������

	Fraction operator=(const Fraction& val);

	Fraction operator+(const int& num);//�������� � ����� ������

	Fraction operator-(const int& num);//�������� � ����� ������
};

Fraction Fraction::operator=(const Fraction& val)
{
	if (this == &val)
	{
		return *this;
	}

	numerator = val.numerator;
	denominator = val.denominator;
}

class Fraction_v2 : public Fraction //���������
{
public:
		Fraction_v2(const int& val_1, const int& val_2)
		{
			numerator = val_1;
			denominator = val_2;
			 
		};
		Fraction_v2()  
		{
			numerator = 1;
			denominator = 1;
		};
		Fraction_v2(const Fraction_v2& fraction) {

			numerator = fraction.numerator;
			denominator = fraction.denominator;
		}
		
		Fraction_v2(Fraction& fraction)
		{
			denominator = fraction.get_den();
			numerator = fraction.get_num();
		}

		Fraction_v2 operator=(Fraction x)
		{
			if (this == &x)
			{
				return *this;
			}

			numerator = x.get_num();
			denominator = x.get_den();

		}
		Fraction_v2 operator=(const Fraction_v2& hz)
		{
			if (this == &hz)
			{
				return *this;
			}

			numerator = hz.numerator;
			denominator = hz.denominator;
		}


		~Fraction_v2() {}

		friend Fraction_v2 operator+(int num, Fraction val);
};

Fraction_v2 operator+(int num, Fraction val)
{
	Fraction_v2 temp;
	temp.numerator = val.get_num() + num*val.get_den();
	temp.denominator = val.get_den();
	return temp;
}

void Fraction::set_den(const int& num)
{
	denominator = num;
}

void Fraction::set_num(const int& num)
{
	numerator = num;
}

void Fraction::show() //����� �����
{

	if (denominator == 1)
	{
		cout << "��������� = " << numerator << endl;
	}
	else
	{
		cout << "��������� = " << numerator << "\n����������� = " << denominator << endl;
	}
}

int Fraction::get_num()
{
	return numerator;
}

int Fraction::get_den()
{
	return denominator;
}

Fraction Fraction::operator+(const int& num) ////�������� � ����� ������
{
	this->denominator = denominator;
	numerator = numerator + num * denominator;
}


Fraction Fraction::operator-(const int& num) //��������� ������ �����
{
	Fraction temp;
	temp.denominator = denominator;
	temp.numerator = numerator - num * denominator;
	return temp;
}

int main()
{
	setlocale(LC_ALL, "Ru-ru");

	cout << "���������� Fraction and Fraction_v2" << endl;

	Fraction test = { 1,3 };
	cout << "�������� ����� ������� ������������� = " ; test.show();
	Fraction_v2 Test = test;
	cout << "Fraction_v2 - ��������� ������ Fraction ; " << endl << " ����� ��������� ������ ���� Fraction_v2 , ����� ���������� �������� Fraction � Fraction_v2 " << endl;
	Test = 5 + test;

	cout << "���� ����������� ����� � Fraction � Fraction � �����" << endl;
	Test.show();

	cout << "��������� �� Fraction " << endl;
	test = test - 5;
	Test = Test - 5;
	cout << "��� ������ �������� ������������ ����� show();" << endl;
	Test.show();
	return 0;
}