#include "Account.h"

// C'TORS
Account::Account()
	: m_transactionList(nullptr), m_numberOfTransaction(0),
	m_persons(nullptr), m_totalPersons(0), m_accountNumber(0), m_balance(0) {}

Account::Account(Person** persons, int count, double balance)
	: m_transactionList(nullptr), m_numberOfTransaction(0),
	m_persons(nullptr), m_totalPersons(0), m_accountNumber(0), m_balance(0) {

	this->SetPersons(persons, count); 
	this->SetAccountNumber(this->GetAccountNumber());
	this->SetBalance(balance);
}

Account::Account(const Person& person, double balance)
	: m_transactionList(nullptr), m_numberOfTransaction(0),
	m_persons(nullptr), m_totalPersons(0), m_accountNumber(0), m_balance(0) {

	this->AddPerson(person, balance);
	this->SetAccountNumber(this->GetAccountNumber());
	this->SetBalance(balance);

}

Account::Account(const Account& other)
	: m_transactionList(nullptr), m_numberOfTransaction(0),
	m_persons(nullptr), m_totalPersons(0), m_accountNumber(0), m_balance(0) {

	int otherTransactionsCount = other.GetNumOfTransactions();
	Transaction** otherTransactions = other.GetTransactions();

	// copy transactions
	int numOfTransactions = 0;
	Transaction** tempTransactions = new Transaction * [otherTransactionsCount];
	for (int i = 0; i < otherTransactionsCount; i++) {
		tempTransactions[i] = new Transaction(*otherTransactions[i]);
		++numOfTransactions;
	}
	this->SetTransactions(tempTransactions, numOfTransactions);


	int otherPersonCount = other.GetTotalPersons();
	Person** otherPersons = other.GetPersons();
	// copy persons
	int numOfPersons = 0;
	Person** tempPersons = new Person * [otherPersonCount];
	for (int i = 0; i < otherPersonCount; i++) {
		tempPersons[i] = new Person(*otherPersons[i]);
		++numOfPersons;
	}
	this->SetPersons(tempPersons, numOfPersons);

	this->SetAccountNumber(other.GetAccountNumber());
	this->SetBalance(other.GetBalance());
}

Account::~Account() {

	this->clearTransactions();
	this->clearPersons();
}


// SETTERS
void Account::SetPersons(Person** persons, int count) {
	
	if (!persons || count < 0) {
		m_persons = nullptr;
		m_totalPersons = 0;
	}

	m_persons = persons;
	m_totalPersons = count;

	//m_persons = new Person*[count];
	//if (!m_persons) throw "Failed to allocate persons..";

	//for (int i = 0; i < count; i++) 
	//	this->AddPerson(*persons[i], 0);
}

void Account::SetAccountNumber(int number) {

	if (number > 0) { m_accountNumber = number; return; }

	//for (int i = 0; i < m_totalPersons; i++) {
	//	number += m_persons[i]->GetId();
	//}
	m_accountNumber = this->GetPersons()[0]->GetId() / 10;
}

void Account::SetBalance(double balance) { 	m_balance = balance; }

void Account::SetTransactions(Transaction** newTransaction, int count) { 
	if (!newTransaction || count <= 0) return;

	m_transactionList = newTransaction;
	m_numberOfTransaction = count;

	//m_transactionList = new Transaction* [count];
	//if (!m_transactionList) throw "Failed to allocate persons..";

	//for (int i = 0; i < count; i++)
	//	this->AddTransaction(*newTransaction[i]);

}

Transaction** Account::GetTransactions() const { return m_transactionList; }

int Account::GetNumOfTransactions() const { return m_numberOfTransaction; }

Person** Account::GetPersons() const { return m_persons; }

int Account::GetTotalPersons()const { return m_totalPersons; }

int Account::GetAccountNumber() const { return m_accountNumber; }

double Account::GetBalance() const { return m_balance; }

// HELPERS
void Account::Withdraw(double amount, const char* date) {
	this->AddTransaction(*(new Transaction(this, this, -amount, date)));
}

void Account::Deposit(double amount, const char* date) { 
	this->AddTransaction(*(new Transaction(this, this, amount, date)));
}

void Account::AddPerson(const Person& newPerson, double	amount){

	int totalPersons = this->GetTotalPersons();

	if (totalPersons == 0) this->SetAccountNumber(newPerson.GetId());

	// check if person already exists
	bool found = false;
	for (int i = 0; i < totalPersons; i++) 
		if (m_persons[i]->GetId() == newPerson.GetId()) {
			found = true;
			break;
		}
	// if person already exists.
	if (found) return;

	Person** temp = new Person*[totalPersons + 1];

	// copy to temp all current persons
	for (int i = 0; i < totalPersons; i++)
		temp[i] = new Person(*m_persons[i]);

	this->clearPersons();

	temp[totalPersons] = new Person(newPerson);
	this->SetPersons(temp, totalPersons + 1);
	
	this->SetBalance(this->GetBalance() + amount);

}

void Account::DeletePerson(const Person& oldPerson){

	int totalPersons = this->GetTotalPersons();
	
	// first check if person exists or the array is empty..
	bool found = false;
	for (int i = 0; i < totalPersons; i++)
		if (m_persons[i]->GetId() == oldPerson.GetId()) {
			found = true; 
			break;
		}

	if (!found) return;

	// if last person is to be deleted
	if (totalPersons - 1 <= 0) {
		this->clearPersons();
		return;
	}

	Person** temp = new Person*[totalPersons - 1];
	if (!temp) throw "error allocating temp";
	
	// copy all except the person
	int k = 0;
	for (int i = 0; i < totalPersons; i++) {
		
		// found person to delete so dont copy him.
		if (m_persons[i]->GetId() == oldPerson.GetId()) continue;

		temp[k] = new Person(*m_persons[i]);
		k++;
	}

	/*// delete old array
	for (int i = 0; i < totalPersons; i++)
		delete m_persons[i];

	// avoid dangling pointer
	delete[] m_persons;
	m_persons = nullptr;*/
	this->clearPersons();

	this->SetPersons(temp, totalPersons - 1);
	//--m_totalPersons;
	//if (this->GetTotalPersons() == 0) return;

	//m_persons = temp;

}

void Account::AddTransaction(const Transaction& newTransaction) {

	Account* src = newTransaction.GetSource();
	Account* dest = newTransaction.GetDes();

	int transactionsCountSource = src->GetNumOfTransactions();

	Transaction** tempSrc = new Transaction * [transactionsCountSource + 1];
	// copy all transactions to tempSrc buffer
	for (int i = 0; i < transactionsCountSource; i++) {
		tempSrc[i] = new Transaction(*(src->GetTransactions()[i]));
	}
	// delete old transaction array src
	src->clearTransactions();

	// add transaction to each account
	tempSrc[transactionsCountSource] = new Transaction(newTransaction);

	src->SetTransactions(tempSrc, transactionsCountSource + 1);

	// if its deposit or withdraw so they're the same.
	if (src == dest) {
		src->SetBalance(src->GetBalance() + newTransaction.GetAmount());
		return;
	}
	else 
		src->SetBalance(src->GetBalance() - newTransaction.GetAmount());

	// if the transaction happened on the same account then return
	//if (src == dest) return;


	int transactionsCountDest = dest->GetNumOfTransactions();

	Transaction** tempDest = new Transaction * [transactionsCountDest + 1];

	// copy all transactions to tempDest buffer
	for (int i = 0; i < transactionsCountDest; i++) {
		tempDest[i] = new Transaction(*(dest->GetTransactions()[i]));
	}
	// delete old transaction array src
	dest->clearTransactions();

	tempDest[transactionsCountDest] = new Transaction(newTransaction);

	dest->SetTransactions(tempDest, transactionsCountDest + 1);

	dest->SetBalance(dest->GetBalance() + newTransaction.GetAmount());

}

void Account::clearTransactions() { 

	int transactionsCount = this->GetNumOfTransactions();
	if (transactionsCount == 0) return;

	for (int i = 0; i < transactionsCount; i++) {

		//delete[] m_transactionList[i]->GetDate();
		m_transactionList[i]->SetDate(nullptr);

		delete m_transactionList[i];
		--m_numberOfTransaction;
	}
	// this will break the code if the array of transactions was created in stack
	// for example: Transaction* transactions[4]; so note this'll only work on dynamically allocated transactions/
	delete[] m_transactionList;
	m_transactionList = nullptr;

}

void Account::clearPersons() {

	int totalPersons = this->GetTotalPersons();

	// delete old array
	for (int i = 0; i < totalPersons; i++)
		delete m_persons[i];	


	// avoid dangling pointer
	delete[] m_persons;
	m_persons = nullptr;

	this->SetPersons(m_persons, 0);

}
