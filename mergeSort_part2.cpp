#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "Library_card.h"

using namespace std;

//Перегрузка записи в файлы
ifstream& operator>>(ifstream& is, Library_card& en);
ofstream& operator<<(ofstream& os, const Library_card& en);

//Работа с файлами
void initFiles(int size);
void clearFiles();
void printFiles();

//Сортировка
void mergeNatSort(vector<Library_card> buf, int n);
void mergerInA(vector<Library_card> buf, int n);

//Компаратор
bool comp(Library_card first, Library_card second);

int main()
{
	setlocale(LC_ALL, "ru");

	clearFiles();

	int len = 15;
	initFiles(len);

	printFiles();

	vector<Library_card> vec;

	for (int i = 1; pow(2, i) < len; i++)
	{
		//cout << "\n\n" << pow(2, i) << "\n\n";
		//mergeNatSort(vec, pow(2,i));
		//printFiles();
	}

	mergeNatSort(vec, len / 2 + 1);

	printFiles();

	return 0;
}

void initFiles(int size)
{
	ofstream outA;
	outA.open("A.txt");

	string arr_autors[] = { "В.А.Голубев", "Г.В.Александров", "В.С.Киров", "К.С.Андропов", "У.Е.Куницын" };
	string arr_books[] = { "Высшая_математика", "Физика", "Правоведение", "Программирование", "Аналитическая_геометрия_и_алгебра" };
	string arr_date_start[] = { "14.09.2021", "04.10.2021", "03.11.2021", "14.09.2021", "01.10.2021" };
	string arr_date_end[] = { "15.05.2022", "04.04.2022", "03.06.2022", "14.05.2022", "01.05.2022" };

	if (outA)
	{
		//Инициализация файла A
		for (int i = 0; i < size; i++)
		{
			/*outA << rand() % size + 1 << '\t'
							<< rand() % 10 + 1 << '\t'
							<< arr_autors[rand() % 5 + 0] << '\t'
							<< arr_books[rand() % 5 + 0] << '\t'
							<< arr_date_start[rand() % 5 + 0] << '\t'
							<< arr_date_end[rand() % 5 + 0] << '\n';*/

			Library_card lb(
				//rand() % size + 1,
				size - i,
				i + 1,
				arr_autors[rand() % 5 + 0],
				arr_books[rand() % 5 + 0],
				arr_date_start[rand() % 5 + 0],
				arr_date_end[rand() % 5 + 0]
			);

			outA << lb;
		}

		outA.close();
	}
}
void clearFiles()
{
	ofstream outA, outB, outC;
	outA.open("A.txt");
	if (outA)
	{
		outB.open("B.txt");
		if (outB)
		{
			outC.open("C.txt");
			if (outC)
			{
				outC.close();
			}
			outB.close();
		}
		outA.close();
	}
}
void printFiles()
{
	Library_card p_l;
	//Содержимое файла A
	cout << "\n\nСодержимое файла A\n";
	ifstream inA;
	inA.open("A.txt");

	if (inA)
	{
		Library_card t;
		while (!inA.eof())
		{
			inA >> t;
			t.print_inf();
		}
		inA.close();
	}

	//Содержимое файла B
	cout << "\n\nСодержимое файла B\n";
	ifstream inB;
	inB.open("B.txt");

	if (inB)
	{
		Library_card t;
		while (!inB.eof())
		{
			inB >> t;
			t.print_inf();
		}
		inB.close();
	}

	//Содержимое файла C
	cout << "\n\nСодержимое файла C\n";
	ifstream inC;
	inC.open("C.txt");

	if (inC)
	{
		Library_card t;
		while (!inC.eof())
		{
			inC >> t;
			cout << t.toString() << '\n';
		}
		inC.close();
	}
}

void mergeNatSort(vector<Library_card> buf, int n)
{
	ifstream inA("A.txt");


	if (inA)
	{
		ofstream outB("B.txt");
		if (outB)
		{
			ofstream outC("C.txt");
			if (outC)
			{
				int count = 0;
				bool b = true;
				Library_card lb;

				while (!inA.eof())
				{
					if (b)
					{
						if (count == n)
						{
							sort(buf.begin(), buf.end(), comp);
							for (vector<Library_card>::iterator it = buf.begin(); it < buf.end(); it++)
								outB << *it;

							b = false;
							count = 0;
							buf.clear();
						}
						else
						{
							inA >> lb;
							buf.push_back(lb);
							count++;
						}
					}
					else
					{
						if (count == n)
						{
							sort(buf.begin(), buf.end(), comp);
							for (vector<Library_card>::iterator it = buf.begin(); it < buf.end(); it++)
								outC << *it;

							b = true;
							count = 0;
							buf.clear();
						}
						else
						{
							inA >> lb;
							buf.push_back(lb);
							count++;
						}
					}
				}

				if (buf.size() > 0)
				{
					sort(buf.begin(), buf.end(), comp);
					for (vector<Library_card>::iterator it = buf.begin(); it < buf.end(); it++)
						outC << *it;
				}

				outC.close();
			}
			outB.close();
		}
		inA.close();
	}
	mergerInA(buf, n);
}

void mergerInA(vector<Library_card> buf, int n)
{
	ofstream outA("A.txt");
	if (outA)
	{
		ifstream inB("B.txt");
		if (inB)
		{
			ifstream inC("C.txt");
			if (inC) 
			{
				Library_card lb1;
				Library_card lb2;

				inB >> lb1;
				inC >> lb2;
				if (lb1.get_num_ticket() < lb2.get_num_ticket())
				{
					outA << lb1;
					while (!inB.eof())
					{
						inB >> lb1;
						outA << lb1;
					}
					outA << lb2;
					while (!inC.eof())
					{
						inC >> lb2;
						outA << lb2;
					}
				}
				else
				{
					outA << lb2;
					while (!inC.eof())
					{
						inC >> lb2;
						outA << lb2;
					}
					outA << lb1;
					while (!inB.eof())
					{
						inB >> lb1;
						outA << lb1;
					}
				}

				

				

				inC.close();
			}
			inB.close();
		}
		outA.close();
	}
}



ifstream& operator>>(ifstream& is, Library_card& en)
{
	is >> en.num_ticket;
	is >> en.num_inventory;
	is >> en.author;
	is >> en.title;
	is >> en.date_start;
	is >> en.date_end;
	return is;
}
ofstream& operator<<(ofstream& os, const Library_card& en)
{
	os << '\t' << en.num_ticket << '\t' <<
		en.num_inventory << '\t' <<
		en.author << '\t' <<
		en.title << '\t' <<
		en.date_start << '\t' <<
		en.date_end;
	return os;
}

bool comp(Library_card first, Library_card second) { return first.get_num_ticket() < second.get_num_ticket(); }
