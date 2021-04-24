#include <iostream>
#include <tchar.h>

using namespace std;

class BaseString
{
protected:
	char* p = nullptr; //óêàçàòåëü 
	int len = 0; //÷èñëî ñèìâîëîâ
	int capacity = 256; //ìàêñ ðàçìåð
public:
	BaseString(char* ptr) //Kîíñòðóêòîð
	{

		p = new char[capacity];
		
		p[len] = '\0';
		
		if (ptr != nullptr) //ïðîâåðêà íà íåíóëåâóþ ñòðîêó
		{
			while (ptr[len] != '\0' && len < (capacity - 1)) //êîïèðóåì äàííûå â íîâûé ìàññèâ
			{
				p[len] = ptr[len];
				++len;
			}

			p[len] = '\0'; //îòäåëÿåì 
			
		}
	}

	BaseString()
	{
		p = new char[capacity];
		
		p[len] = '\0';
	}

	BaseString(const char* ptr)
	{

		p = new char[capacity];
		
		p[len] = '\0';
		
		if (ptr != nullptr) 
		{
			while (ptr[len] != '\0' && len < (capacity - 1))
			{
				p[len] = ptr[len];
				++len;
			}

			p[len] = '\0';
		}
	}

	BaseString(int Capacity)
	{

		capacity = Capacity;
		
		p = new char[capacity];
		
	}

	~BaseString() //äåñòðóêòîð
	{
		
		if (p != nullptr)
		{
			delete[] p;
		}
		
		len = 0;
	}
	
	int Length() { return len; } //÷èñëî áóêâ
	
	int Capacity() { return capacity; } //ìàêñ ðàçìåð
	
	char* get() {return p;} //óêàçàòåëü íà ïåðâûé ýëåìåíò

	char& operator[](int& i) //ïåðåãðóçêà îïåðàòîðà, äëÿ âûâîäà ñèìâîëà ïî åãî èíäåêñó 
	{ 
		return p[i];
	} 
	
	BaseString& operator=(BaseString& s) //ïåðåãðóçêà îïåðàòîðà =
	{
		
		if (this != &s)
		{
			if (capacity >= s.Capacity())
			{
				len = s.Length();
				capacity = s.Capacity();
			}

			if (p != nullptr)
			{
				delete[] p;
			}

			p = new char[capacity];

			for (int i = 0; i < len; i++)
			{
				p[i] = s.p[i];
			}

			p[len] = '\0';
		}
		else
		{
			return *this;
		}
	}
	
	BaseString(BaseString& s)//êîíñòðóêòîð êîïèðîâàíèÿ 
	{
		
			len = s.Length();
			capacity = s.Capacity();

			if (p != nullptr)
			{
				delete[] p;
			}

			p = new char[capacity];

			for (int i = 0; i < len; i++)
			{
				p[i] = s.p[i];
			}

			p[len] = '\0';
	}
	
	virtual void print() //âèðòóàëüíàÿ ôóíêöèÿ âûâîäà
	{
		int i = 0;

		while (p[i] != '\0')
		{
			cout << p[i] << ',' << ' ';
			i++;
		}

		cout << ";\n";
	}
};


class String : public BaseString
{
public:

	using BaseString::BaseString; //ñ++ 11 - ýòî 1000 è 1 îòñóòñòâóþùèé êîíñòðóêòîð :)

	String& operator+(String& s)
	{
		int s_len = this->len + s.Length() - 1; //äëèíà äâóõ ñòðîê + 1 ìåñòî ïîä '\0'
		cout << "len = " << len;
		cout << "\t S_len = " << s_len << endl;

		for (int i = len, j = 0; (i < s_len && s[j] != '\0') ; ++i, ++j)
		{
			p[i] = s[j];
			cout << "\n" << p[i] << '=' << s[j] << endl;
		}

		p[s_len] = '\0';
		
		len = s_len;
		
		return *this;
	}

	int IndexOf(String& str)
	{
		bool fl = false;
		int i = 0, j = 0, index;


		while (j < str.Length() && i < len)
		{
			if (p[i] == str.p[j])
			{
				fl = true;
				if (p[i] == str.p[0])
					index = i;
				++j;
			}
			else
			{
				fl = false;
				j = 0;
				index = 0;
			}
			++i;
		}

		if (fl && j == str.Length())
		{
			cout << "Èíäåêñ ïîäñòðîêè = ";
			return index;
		}
		else
		{
			return -1;
		}

	}
};


int _tmain(int argc, _TCHAR* argv[]) //áåç #include <tchar.h> ðàáîòàòü íå áóäåò... 
{
	setlocale(LC_ALL, "Ru-ru");

	String str("acdacbdabcd"), test("abcd");
	int i;

	i = str.IndexOf(test);

	cout << i;


	return 0;
}


