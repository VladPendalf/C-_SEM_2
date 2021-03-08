#include <iostream>
#include <algorithm>

using namespace std;


bool simple(int n) //�������� ����� �� ��������
{
	for (int i = 2; i <= n / 2; i++) if ((n % i) == 0) return false;
	return true;
}

/*======================��====================+
A.��� ������������ ����� MyArrayParent, �������� ����������� ������� �������
(���� InheritanceArray_empty.cpp). ��������� ����� ������������ ���������:
	1 ������������� ����� MyArrayParent (&MyArrayParent v).
	2 ���������� =.
	3 ���������� [ ] ��� ��������� � �������� �� �������.
	4 �������������, ����������� � ���������� ���������� �� ������������� �������.

B. � ������ MyArrayChild, �������������� �� ������ MyArrayParent, ����������
�������� ������� (�������� �������� �� ��, ��� ����� ������������ ���������, ���
�������������� � ������� ������):
	1 �������� �������� �� ������������� ����� � ������� RemoveAt().
	2 ������ �������� � ������� �� �������� IndexOf().
	3 ������� �������� � ��������� ����� � ������� InsertAt().
	4 �������� ������� �������� ������ �������� (��. ������� 1). ����������� ��������� ������� ������ 
	���� ����� ������ ������. �������� ������ �� ������ ��������.

C. ����������� ����� ����� MySortedArray �� MyArrayChild. �� ������������, ��� ����
����� �������� ������������� ������. �������������� ������� �� ������ B.4, ����
�����, ��� ������ ������������. �������������� �������� ���������� �������� (push)
����� �������, ����� ������ ��������� ��������������� ��� ���������� ��������

B.4 �� ������� ������� � ����� �����. ��������� � ������ �� ������ ������
������� ����� �� ����


==============================================+
*/

class MyArrayParent
{
protected:
	
	int capacity; //������� ������ �������� 
	
	int count; //���������� ��������� - ������� ������ ����������
	
	double* ptr;//������

public:

//----------------------------������������_�_�����������---------------------------------+							 
	MyArrayParent(int Dimension);	//����������� �� ��������� (�� ��� �� �����... :D )				 
																						 
	MyArrayParent(double* arr, int len); //����������� ��������� ������������ ������	 

	MyArrayParent(const MyArrayParent& V); //����������� �����������
																						 
	~MyArrayParent();																	 
//---------------------------------------------------------------------------------------+

	//��������� � �����
	int Capacity() { return capacity; } //������ ����� ������
	
	int Size() { return count; } //����� ���������

	double GetComponent(int index); //����� ����� �� �������

	void SetComponent(int index, double value); //�������� �������� ����� �� �������

	virtual void push(double value); //�������� ������� � �����

	void RemoveLastValue(); //�������� �������� � �����

	double& operator[](int index); //������� ������� �� �������

	MyArrayParent& operator=(const MyArrayParent& V); //���������� ��������� =

	void print(); //����� ����� �������

};

class MyArrayChild : public MyArrayParent
{
public:
	 
	MyArrayChild(int Dimension = 10) : MyArrayParent(Dimension) { cout << "\nMyArrayChild constructor with Dimension"; } //���������� ����������� ��������

	~MyArrayChild();
	
	void RemoveAt(int index);//�������� ��������

	virtual int IndexOf(double value);//����� ��������

	void InsertAt(double value, int index); //������� ��������

	MyArrayChild& operator=(const MyArrayChild& str);

	MyArrayChild Easyl_num();
};

class MySortedArray : public MyArrayChild
{
protected:
	int IndexOf_1(double value);// �������� �����

public:
	MySortedArray(int Dimension = 10) : MyArrayChild(Dimension) {cout << "\nMySortedArray constructor\n";}

	// using MyArrayChild::MyArrayChild -> ��� ������������� ������ � ��� ��� ��������?

	~MySortedArray();

	int IndexOf(double value);// �������� �����

	void push(double value);

	MySortedArray Easyl_num();
};



MyArrayParent::MyArrayParent(int Dimension = 10)
{
	cout << "\nMyArrayParent constructor with Dimension";
	ptr = new double[Dimension]; // �������� ������ � ������� new
	capacity = Dimension;
	count = 0;
}

MyArrayParent::MyArrayParent(double* arr, int len) //����������� ��������� ������������ ������
{
	cout << "\nMyArrayParent constructor with array" << endl;
	
	capacity = len + 5;
	ptr = new double[capacity]; //������ ������ � �������
	count = len;

	for (int i = 0; i < len; ++i)
	{
		ptr[i] = arr[i];
	}

	print();

}

MyArrayParent::MyArrayParent(const MyArrayParent& V)
{
	//�������� ����� ������� - � ��������, ��� ����������� ���������� �� ������� / �������� ���������� � �������
	cout << "\nMyArrayParent constructor copy";
	capacity = V.capacity;
	count = V.count;

	ptr = new double[V.capacity];
	for (int i = 0; i < V.count; i++)
		ptr[i] = V.ptr[i];

	print();
}

MyArrayParent::~MyArrayParent()
{
	cout << "\nMyArrayParent destructor";
	if (ptr != nullptr)
	{
		delete[] ptr; // ����������� ��������� ������ 
		ptr = nullptr;
	}
}

MyArrayChild::~MyArrayChild()
{
	cout << "\nMyArrayChild destructor\n";
	if (ptr != nullptr)
	{
		delete[] ptr;
		ptr = nullptr;
	}
}

MySortedArray::~MySortedArray()
{
	if (ptr != NULL)
	{
		delete[] ptr; // ����������� ��������� ������ 
		ptr = NULL;
	}
	cout << "\nMySortedArray destructor\n";
}

double MyArrayParent::GetComponent(int index)
{
	/*if (index >= 0 && index < count) { return ptr[index]; }
	return -1;
	*/

	try
	{
		if (index >= 0 && index < count)
		{
			return ptr[index];
		}
		else
		{
			throw "\n�� ����������� �������������� ������\n";
			throw -1;
		}
	}
	catch (const char* exeption)
	{
		cerr << "Error: " << exeption << endl;
	}
	catch (int)
	{
		return -1;
	}
}

void MyArrayParent::SetComponent(int index, double value) //�������� throw()
{
	/*if (index >= 0 && index < count)
		ptr[index] = value;
	//������������� ����������, ���� ������ ������������
	*/

	try
	{
		if (index >= 0 && index < count)
		{
			ptr[index] = value;
		}
		else
		{
			throw "\n�� ����������� �������������� ������\n";
		}
	}
	catch(const char* exeption)
	{
		cerr << "Error: " << exeption;
	}


}

void MyArrayParent::push(double value)
{
	/*if (capacity > count)
	{
		ptr[count] = value;
		count += 1;
	}
	else
		cout << ("No any space left!") << endl;

	*/
	try
	{
		if (capacity > count)
		{
			ptr[count] = value;
			count += 1;
		}
		else
		{
			throw "\n������ ������� �����������!!!\n";
		}
	}
	catch(const char* exeption)
	{
		cerr << "Error: " << exeption;
	}

}

void MyArrayParent::RemoveLastValue()
{
	if (count > 0)
		count -= 1;
	//��� ������, ���� ����? - ������
}

double& MyArrayParent::operator[](int index)
{
	//���������� ��������� []
		// cout<<arr[2]; ����������
		// arr[2] = 1; - ������
		// ���� �� ������ ������, �� ����� ������� ������, � �� ��������
	if (index < 0)
		return ptr[count + index];
	if (count > index)
		return ptr[index];
}

MyArrayParent& MyArrayParent::operator=(const MyArrayParent& V)
{
	//�������� =
	//arr1 = arr2 = arr3; ��� arr_i - ������� ������ ������
	capacity = V.capacity;
	count = V.count;

	ptr = new double[V.capacity];
	for (int i = 0; i < V.count; i++)
		ptr[i] = V.ptr[i];
	return *this; //��������� ��� �� ���� 
	// ������� �� ����������� - ����� ������� this
}

void MyArrayParent::print()
{
	cout << "\nMyArrParent, size = " << count << "\n values: { ";

	for (int i = 0; i < (count-1); ++i)
	{
		cout << ptr[i] <<" , ";
	}
	cout << ptr[count-1] << " }\n";
}

void MyArrayChild::RemoveAt(int index)
{
	if (abs(index) < count)
	{
		if (index > 0)
		{
			for (int i = index; i < count; i++)
			{
				ptr[i] = ptr[i + 1];
			}
			count -= 1;
		}
		if (index < 0)
		{
			for (int i = count + index; i < count; i++)
			{
				ptr[i] = ptr[i + 1];
			}
		}
	}
}

int MyArrayChild::IndexOf(double value)
{
	for (int i = 0; i < count; i++)
		if (ptr[i] == value)
			return i;
		return -1;
}

void MyArrayChild::InsertAt(double value, int index)
{
	if (index > 0)
	{
		for (int i = count - 1; i >= index; i--)
		{
			ptr[i + 1] = ptr[i];
		}
		ptr[index] = value;
		count++;
	}
}

MyArrayChild MyArrayChild::Easyl_num()
{
	MyArrayChild arr_es_num; //������ ������

	arr_es_num.count = count;
	arr_es_num.capacity = capacity;

	for (int i = 0; i < count; ++i) //��������� �� ��������
	{
		if (simple(ptr[i]) == true)
		{
			arr_es_num.ptr[i] = ptr[i];
		}
		else
		{
			arr_es_num.count--;
		}
	}
	arr_es_num.count--;
	return arr_es_num;
}

MyArrayChild& MyArrayChild::operator=(const MyArrayChild& str)
{
	count = str.count;
	capacity = str.capacity;

	for (int i = 0; i < count; ++i)
	{
		ptr[i] = str.ptr[i];
	}

	return *this;
}

void MySortedArray::push(double value)
{
	if (count == 0)
	{
		ptr[count] = value;
		count += 1;
	}
	else
	{
		int index = IndexOf_1(value);
		InsertAt(value, index);
	}
}

int MySortedArray::IndexOf_1(double value)
{
	int l = 0;
	int r = count;
	int mid = 0;

	while (l <= r)
	{
		mid = (l + r) / 2;
		if (ptr[mid] == value)
			return mid;
		if (value < ptr[mid])
			r = mid - 1;
		if (value > ptr[mid])
			l = mid + 1;
	}
	return mid;
}

int MySortedArray::IndexOf(double value)
{
	int l = 0;
	int r = count;
	int mid;

	while (l <= r)
	{
		mid = (l + r) / 2;
		if (ptr[mid] == value)
			return mid;
		if (value < ptr[mid])
			r = mid - 1;
		if (value > ptr[mid])
			l = mid + 1;
	}
	return -1;
}

MySortedArray MySortedArray::Easyl_num()
{
	MySortedArray arr_es_num; //������ ������

	arr_es_num.count = count;
	arr_es_num.capacity = capacity;

	for (int i = 0; i < count; ++i) //��������� �� ��������
	{
		if (simple(ptr[i]) == true)
		{
			arr_es_num.ptr[i] = ptr[i];
		}
		else
		{
			arr_es_num.count--;
		}
	}
	arr_es_num.count--;
	return arr_es_num;
}

int main()
{
	setlocale(LC_ALL,"Ru-ru");

	MyArrayParent arr;

	for (int i = 0; i < 6; ++i)
	{
		arr.push(i);
	}
	arr.print();
	
	MyArrayChild test, es_num;
	for (int i = 0; i < 6; ++i)
	{
		test.push(i);
	}
	test.print();

	int index;
	test.InsertAt(5, 5);
	index = test.IndexOf(5);
	cout << "\nIndex = " << index << endl;

	test.print();

	es_num = test.Easyl_num();

	es_num.print();
	test.print();
	return 0;
}