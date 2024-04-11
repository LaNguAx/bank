#include "Account.h"
Account::Account() {}
Account::Account(Person** persons, int count, double balance) {}
Account::Account(const Person& person, double balance) {}
Account::Account(const Account& other) {}
Account::~Account() {}


void	Account::SetPersons(Person** persons, int count) {}
void	Account::SetAccountNumber(int number) {}
void		Account::SetBalance(double balance){}
void		Account::SetTransactions(Transaction** newTransaction, int count){}
Transaction** Account::GetTransactions() { return this->m_transactionList; }
int			Account::GetNumOfTransactions() { return 0; }
Person** Account::GetPersons() const { return this->m_persons; }
int Account::GetTotalPersons()const { return 0; }
int			Account::GetAccountNumber() const { return 0; }
double		Account::GetBalance() const { return 0; }

void Account::Withdraw(double amount, const char* date){}
void Account::Deposit(double amount, const char* date){}
void Account::AddPerson(const Person& newPerson, double	amount){}
void Account::DeletePerson(const Person& oldPerson){}
void Account::AddTransaction(const Transaction& newTransaction) {}

void Account::clearTransactions(){}
void Account::clearPersons() {}
