#include "Transaction.h"

/*
	Itay Andre Aknin
*/


Transaction::Transaction(Account* s, Account* d, double amount, const char* date)
	: m_source(nullptr), m_destination(nullptr), m_amount(0.0), m_date(nullptr) {
		
	this->SetSource(s);
	this->SetDes(d);
	this->SetAmount(amount);
	this->SetDate(date);

}
Transaction::Transaction(const Transaction& other) 
	: m_source(nullptr), m_destination(nullptr), m_amount(0.0), m_date(nullptr) {

	if (this == &other) throw "same transaction";

	this->SetSource(other.GetSource());
	this->SetDes(other.GetDes());
	this->SetAmount(other.GetAmount());
	this->SetDate(other.GetDate());

}

void Transaction::SetSource(Account* src) { m_source = src; }

void Transaction::SetDes(Account* dst) { m_destination = dst; }

void Transaction::SetAmount(double amount) { m_amount = amount; }

void Transaction::SetDate(const char* date){

	delete[] m_date;
	m_date = nullptr;
	if (date == nullptr) return;

	int dateLen = strlen(date) + 1;
	char* newDate = new char[dateLen];
	//strcpy_s(newDate, dateLen, date);
	strcpy(newDate, date);

	m_date = newDate;

}

Account* Transaction::GetSource() const { return m_source; }

Account* Transaction::GetDes() const { return m_destination; }

double	Transaction::GetAmount() const { return m_amount; }

char* Transaction::GetDate() const { return m_date; }
