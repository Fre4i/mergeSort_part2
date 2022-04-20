#ifndef __LIBRARY_CARD__
#define __LIBRARY_CARD__
#include <iostream>
#include <string>

using namespace std;

class Library_card
{
	int num_ticket;
	int num_inventory;
	string author;
	string title;
	string date_start;
	string date_end;
public:

	friend ifstream& operator>>(ifstream& is, Library_card& en);
	friend ofstream& operator<<(ofstream& os, const Library_card& en);

	Library_card() {};
	Library_card(
		int num_ticket1,
		int num_inventory1,
		string author1,
		string title1,
		string date_start1,
		string date_end1
	) :
		num_ticket(num_ticket1),
		num_inventory(num_inventory1),
		author(author1),
		title(title1),
		date_start(date_start1),
		date_end(date_end1)
	{};
	int get_num_ticket() { return num_ticket; };
	void print_inf()
	{
		cout << num_ticket << '\t' << num_inventory << '\t' << author << '\t' << title << '\t' << date_start << '\t' << date_end << endl;
	};
	string toString()
	{
		return to_string(num_ticket) + '\t' +
			to_string(num_inventory) + '\t' +
			author + '\t' +
			title + '\t' +
			date_start + '\t' +
			date_end;
	};
};

#endif