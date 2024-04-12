#include "Account.h"

// C'TORS
Account::Account()
	: m_transactionList(nullptr), m_numberOfTransaction(0),
	m_persons(nullptr), m_totalPersons(0), m_accountNumber(NULL), m_balance(0) {}


Account::Account(Person** persons, int count, double balance)
	: m_transactionList(nullptr), m_numberOfTransaction(0) {

	this->SetPersons(persons, count); 
	this->SetAccountNumber(m_persons[0]->GetId());
	this->SetBalance(balance);
}

Account::Account(const Person& person, double balance)
	: m_transactionList(nullptr), m_numberOfTransaction(0) {

	this->AddPerson(person, balance);
	this->SetAccountNumber(m_persons[0]->GetId());
	this->SetBalance(balance);

}
Account::Account(const Account& other) {}
Account::~Account() {}


// SETTERS
void Account::SetPersons(Person** persons, int count) {
	
	if (!persons || count <= 0) return;

	m_persons = new Person*[count];
	if (!m_persons) throw "Failed to allocate persons..";

	for (int i = 0; i < count; i++) 
		this->AddPerson(*persons[i], 0);
}

void Account::SetAccountNumber(int number) {

	if (!m_totalPersons) m_accountNumber = number;

	for (int i = 0; i < m_totalPersons; i++) {
		number += m_persons[i]->GetId();
	}
	m_accountNumber = number / 10;
}


void Account::SetBalance(double balance) { 
	
	if (balance <= 0) throw "error";

	m_balance = balance;
}

void Account::SetTransactions(Transaction** newTransaction, int count){}

Transaction** Account::GetTransactions() { return this->m_transactionList; }

int Account::GetNumOfTransactions() { return m_numberOfTransaction; }

Person** Account::GetPersons() const { return m_persons; }

int Account::GetTotalPersons()const { return m_totalPersons; }

int Account::GetAccountNumber() const { return m_accountNumber; }

double Account::GetBalance() const { return m_balance; }

// HELPERS
void Account::Withdraw(double amount, const char* date){}

void Account::Deposit(double amount, const char* date){}

void Account::AddPerson(const Person& newPerson, double	amount){

	int totalPersons = this->GetTotalPersons();

	Person** temp= new Person*[totalPersons + 1];

	// copy to temp all current persons
	for (int i = 0; i < totalPersons; i++)
		temp[i] = new Person(*m_persons[i]);

	// delete all persons from m_persons;
	for (int i = 0; i < totalPersons; i++) 
		delete m_persons[i];

	delete[] m_persons;
	m_persons = nullptr;

	m_persons = temp;

	m_persons[m_totalPersons++] = new Person(newPerson);
	
	this->SetBalance(this->GetBalance() + amount);

}
void Account::DeletePerson(const Person& oldPerson){

	int totalPersons = this->GetTotalPersons();

	// first check if person exists or empty array..
	bool found = false;
	for (int i = 0; i < totalPersons; i++)
		if (m_persons[i]->GetId() == oldPerson.GetId()) {
			found = true; 
			break;
		}

	if (!found) return;


	Person** temp = new Person*[totalPersons - 1];
	if (!temp) throw "error allocating temp";
	
	// copy all except the person
	int k = 0;
	for (int i = 0; i < totalPersons; i++) {
		
		// found person to delete so dont copy him.
		if (m_persons[i]->GetId() == oldPerson.GetId()) continue;

		temp[k] = new Person(*m_persons[k]);
		k++;
	}

	// delete old array
	for (int i = 0; i < totalPersons; i++)
		delete m_persons[i];

	delete[] m_persons;
	m_persons = nullptr;

	--m_totalPersons;

	if (m_totalPersons == 0) return;

	m_persons = temp;

}
void Account::AddTransaction(const Transaction& newTransaction) {}

void Account::clearTransactions(){}
void Account::clearPersons() {}
