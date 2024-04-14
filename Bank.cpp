#include "Bank.h"

Bank::Bank()
	: m_name(nullptr), m_account(nullptr), m_bankCode(0), m_numbeOfAccounts(0), m_totalBalance(0){}

Bank::Bank(const char* name, int code)
	:m_numbeOfAccounts(0), m_totalBalance(0) {

	this->SetBankName(name);
	this->SetCode(code);

}

Bank::~Bank() {

	delete[] m_name;
	for (int i = 0; i < this->GetNumberOfAccounts(); i++)
		delete this->GetAccounts()[i];

	delete this->GetAccounts();

}

void Bank::SetBankName(const char* name){

	delete[] m_name;
	m_name = nullptr;

	int nameLen = strlen(name) + 1;
	char* newName = new char[nameLen];
	//strcpy_s(newName, nameLen, name);
	strcpy(newName, name);

	m_name = newName;
}

void Bank::SetAccount(Account** account, int numbeOfAccounts) { 
	if (numbeOfAccounts > 0) {
		m_account = account;
		m_numbeOfAccounts = numbeOfAccounts;
	}
	else {
		m_account = nullptr;
		m_numbeOfAccounts = 0;
	}
}

void Bank::SetTotal(double total) { m_totalBalance = total; }

void Bank::SetCode(int code) { m_bankCode = code; }

const char* Bank::GetBankName() const { return m_name; }

Account** Bank::GetAccounts() const { return m_account; }

int Bank::GetNumberOfAccounts() const { return m_numbeOfAccounts; }

double Bank::GetTotal() const { return m_totalBalance; }

int Bank::GetCode() const { return m_bankCode; }

void Bank::AddAccount(const Account& account) {

	int numOfAccounts = this->GetNumberOfAccounts();
	Account** accounts = this->GetAccounts();
	
	// check if account exists.
	for (int i = 0; i < numOfAccounts; i++)
		// same account
		if (accounts[i]->GetAccountNumber() == account.GetPersons()[0]->GetId())
			return;

	Account** temp = new Account * [numOfAccounts + 1];
	for (int i = 0; i < numOfAccounts; i++)
		temp[i] = new Account(*accounts[i]);

	// delete old accounts array
	for (int i = 0; i < numOfAccounts; i++)
		delete accounts[i];

	delete[] m_account;
	m_account = nullptr;

	temp[numOfAccounts] = new Account(account);
	this->SetAccount(temp, numOfAccounts + 1);

	/*int sum = 0;
	for (int i = 0; i < numOfAccounts + 1; i++)
		sum += temp[i]->GetBalance();
		*/

	this->SetTotal(this->GetTotal() + temp[numOfAccounts]->GetBalance());
}

void Bank::AddAccount(const Person& per, double amount) {
	
	Account newAccount(per, amount);
	this->AddAccount(newAccount);

}

void Bank::AddPerson(const Person& newPerson, const Account& account, double amount) {

	int numOfAccounts = this->GetNumberOfAccounts();
	Account** accounts = this->GetAccounts();

	Account* foundAccount = nullptr;
	// find account
	for (int i = 0; i < numOfAccounts; i++) 
		// if account was found.
		if (accounts[i]->GetAccountNumber() == account.GetAccountNumber()) {
			foundAccount = accounts[i];
			break;
		}
	
	// if no account was found, create account for person.
	if(!foundAccount) {
		
		Account newAccount(newPerson, amount);
		this->AddAccount(newAccount);
		return;
	}

	// search if person exists in account, if exists then stop execution.
	int foundAccountNumPersons = foundAccount->GetTotalPersons();
	Person** foundAcountPersons = foundAccount->GetPersons();

	for (int i = 0; i < foundAccountNumPersons; i++)
		// if person was found in the account already.
		if (foundAcountPersons[i]->GetId() == newPerson.GetId())
			return;



	// if account was found && person not found in account, add person to account
	foundAccount->AddPerson(newPerson, amount);

	this->SetTotal(this->GetTotal() + amount);

}

void Bank::DeleteAccount(const Account& account) {

	int numOfAccounts = this->GetNumberOfAccounts();
	Account** accounts = this->GetAccounts();

	Account* foundAccount = nullptr;
	// find account
	for (int i = 0; i < numOfAccounts; i++)
		// if account was found.
		if (accounts[i]->GetAccountNumber() == account.GetAccountNumber()) {
			foundAccount = accounts[i];
			break;
		}

	// if account was not found
	if (!foundAccount) return;
	
	//copy everything to temp except account to be deleted
	Account** temp = new Account * [numOfAccounts - 1];
	int k = 0;
	for (int i = 0; i < numOfAccounts; i++) {
		if (accounts[i]->GetAccountNumber() == account.GetAccountNumber()) continue;

		temp[k] = new Account(*accounts[i]);
		k++;
	}

	// delete old accounts array
	for (int i = 0; i < numOfAccounts; i++)
		delete accounts[i];

	delete[] accounts;
	accounts = nullptr;

	this->SetAccount(temp, numOfAccounts - 1);

	// update bank total sum
	int sum = 0; 
	for (int i = 0; i < numOfAccounts - 1; i++)
		sum += temp[i]->GetBalance();

	this->SetTotal(sum);

}

void Bank::DeletePerson(const Person& p) {

	for (int i = 0; i < this->GetNumberOfAccounts(); i++) {
		int numOfAccounts = this->GetNumberOfAccounts();
		Account** accounts = this->GetAccounts();

		accounts[i]->DeletePerson(p);
		if (accounts[i]->GetTotalPersons() == 0) this->DeleteAccount(*accounts[i--]);
	}
}
