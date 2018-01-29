#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>
#include<ctime>

using namespace std;
int ile = 0;
int ile2 = 0;

string tablica[5000];

int funkcja_haszujaca1(string slowo)
{
	unsigned int sum, i;
	sum = 0;
	for (i = 0; i < slowo.length(); i++)
	{

		sum += slowo[i];
	}
	return sum % 20000;
}
int funkcja_haszujaca2(string slowo)
{
	unsigned int sum, i;
	sum = 5381;
	for (i = 0; i < slowo.length(); i++)
	{

		sum = (sum * 33 + slowo[i]) % 20000;
	}
	return sum;
}
int funkcja_haszujaca3(string slowo)
{
	int sum, i;
	sum = 5381;
	srand(time((NULL)));
	for (i = 0; i < slowo.length(); i++)
	{

		sum = (37 * sum + 1 + slowo[i] * rand() % 20000) % 20000;
	}
	return sum;
}
int sondowanie(string slowo)
{
	int kolizja = 0;
	int indeks, sukces = 0;

	indeks = funkcja_haszujaca1(slowo);

	while (!sukces)

	{
		if (tablica[indeks] == "")

		{
			tablica[indeks] = slowo;
			sukces = 1;
		}
		else
		{
			kolizja++;
			indeks++;
			if (indeks >= 20000) indeks = 0;
		}
	}
	return kolizja;
}
int podwojne_sondowanie(string slowo) //podwojne_rozpraszanie
{
	int kolizje = 0, j = funkcja_haszujaca3(slowo) + kolizje*funkcja_haszujaca1(slowo), sukces = 0;

	while (!sukces) {
		if (tablica[j] == "") {
			tablica[j] = slowo;
			sukces = 1;
		}
		else {
			kolizje++;
			j++;
			if (j >= 20000) {
				j = 0;
			}
		}
	}
	return kolizje;
}

int znajdz(string slowo)
{
	for (int i = 0; i<20000; i++)
	{
		ile2++;
		if (tablica[funkcja_haszujaca1(slowo) + i] == slowo)
		{
			return funkcja_haszujaca1(slowo) + i;
		}
		else if (i == 20000 - 1) {
			return 0;
		}
	}
}

int main()
{
	string linia;
	ifstream plik;
	plik.open("slowa.txt");
	ifstream a;
	a.open("slowa9k.txt");
	ifstream b;
	b.open("slowa7k.txt");
	ifstream c;
	c.open("slowa5k.txt");
	ifstream d;
	d.open("slowa1.txt");


	cout << "freedom: hash1: " << funkcja_haszujaca1("freedom") << endl;
	cout << "freedom: hash2: " << funkcja_haszujaca2("freedom") << endl;
	cout << "freedom: hash3: " << funkcja_haszujaca3("freedom") << endl;

	while (getline(c, linia))
	{
		sondowanie(linia);
	}
	while (getline(d, linia))
	{
		ile += podwojne_sondowanie(linia);
		znajdz(linia);
	}
	
	
	cout << znajdz("freedom") << endl;
	cout << "Srednia wstawiania: " << ile / 1000 << endl;
	cout << "Srednia szukania: " << ile2/1000 << endl;

	plik.close();
	a.close();
	b.close();
	c.close();
	d.close();
	system("pause");
	return 0;
}
