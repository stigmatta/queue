#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <time.h>
using namespace std;

class Printer
{
	string* wait;
	int* pri;
	int maxQueueLength;
	int queueLength;
	time_t timestamp = time(0);
public:
	Printer(int m);
	~Printer();
	void add(string c, int p);
	string extract();
	void clear();
	bool empty();
	bool full();
	int getCount();
	void print();
};
Printer::~Printer()
{
	delete[]wait;
	delete[]pri;
}

Printer::Printer(int m)
{
	maxQueueLength = m;
	wait = new string[maxQueueLength];
	pri = new int[maxQueueLength];
	queueLength = 0;
}

void Printer::clear()
{
	queueLength = 0;
}

bool Printer::empty()
{
	return queueLength == 0;
}

bool Printer::full()
{
	return queueLength == maxQueueLength;
}

int Printer::getCount()
{
	return queueLength;
}

void Printer::add(string c, int p)
{
	if (!full()) {
		wait[queueLength] = c;
		pri[queueLength] = p;
		queueLength++;
	}
}

string Printer::extract()
{
	if (!empty()) {
		int max_pri = pri[0];
		int pos_max_pri = 0;
		for (int i = 0; i < queueLength; i++)
		{
			if (max_pri < pri[i]) {
				max_pri = pri[i];
				pos_max_pri = i;
			}
		}
		string temp1 = wait[pos_max_pri];
		for (int i = pos_max_pri; i < queueLength - 1; i++) {
			wait[i] = wait[i + 1];
			pri[i] = pri[i + 1];
		}
		queueLength--;
		return temp1;
	}
	else return "";
}
void Printer::print()
{
	Printer printHistory(queueLength);
	for (int i = 0; i < queueLength; i++)
		cout << wait[i] << " - " << pri[i] << endl;
	while (!empty()) {
		int max_pri = pri[0];
		int pos_max_pri = 0;
		for (int i = 0; i < queueLength; i++)
		{
			if (max_pri < pri[i]) {
				max_pri = pri[i];
				pos_max_pri = i;
			}
		}
		printHistory.add(wait[pos_max_pri], pri[pos_max_pri]);
		extract();
	}
	while (!printHistory.empty()) {
		int i = 0;
		cout << "User: " << printHistory.wait[i++] << " -- Printed at: " << ctime(&timestamp);
		printHistory.extract();
	}
}

void main()
{
	srand(time(0));
	Printer QUP(25);
	QUP.add("User1", 1);
	QUP.add("User2", 10);
	QUP.add("User3", 10);
	QUP.add("User4", 15);
	QUP.print();
}

