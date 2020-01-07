#include "funkcje.h"

int main()
{
	vector<string> historia;
	string wyrazenie;
	float wynik = 0;
	int x = 0;
	while (true)
	{
		cout << "Wszystkie znaki nalezy wpisywac bez spacji!" << endl;
		cout << "pierwiastek -> sqrt(liczba)" << endl;
		cout << "potega -> pow(podstawa,wykladnik)" << endl;
		cout << "Aby wyswietlic historie wpisz -> history" << endl;
		cout << "Aby wyzerowac wpisz -> clear" << endl;
		if (x == 0)
		{
			cout << "wynik: " << wynik << endl;
			cout << "Podaj wyrazenie: ";
		}
		else
			cout << "wynik: " << wynik;
		cin >> wyrazenie;
		historia.push_back(wyrazenie);

		if (wyrazenie == "history")
		{
			system("cls");
			for (int i = 0; i < historia.size(); i += 2)
			{
				if (historia.at(i) != "history" && historia.at(i + 1) != "history")
					cout << historia.at(i) << "=" << historia.at(i + 1) << endl;
				if (i == historia.size() - 1)
					cout << endl;
			}
		}
		else if (wyrazenie == "clear")
		{
			wynik = 0;
			historia.clear();
			system("cls");
		}
		else
		{
			wylicz(wyrazenie, wynik, historia);
			x = 1;
			system("cls");
		}
	}
	return 0;
}