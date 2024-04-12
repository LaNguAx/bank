#include "Bank.h"
#include <iostream>
using namespace std;

int main() //Train
{
	// PERSON TESTING:
	//Person p1;
	//Person p2("Itay Aknin", 322959412);
	//Person p3(p2);

	// ACCOUNT TESTING:
	Person** persons = new Person*[3];
	persons[0] = new Person("Lior Li", 20145876);
	persons[1] = new Person("Liam Winter", 2048741);
	persons[2] = new Person("Jordi Alabit", 573851853);

	//Account a(persons, 2, (double) 5);
	Account a(persons, 3, 1750);
	Account b(*persons[0], 500);
	b.AddPerson(*persons[1], 1000);
	b.DeletePerson(*persons[1]);
	b.DeletePerson(*persons[1]);
	b.DeletePerson(*persons[0]);
	b.DeletePerson(*persons[0]);

	b.AddPerson(*persons[0],500);
	b.AddPerson(*persons[1], 1000);
	b.AddPerson(*persons[1], 1000);
	b.AddPerson(*persons[1], 1000);
	b.DeletePerson(*persons[1]);
	b.DeletePerson(*persons[0]);
	b.DeletePerson(*persons[1]);
	b.DeletePerson(*persons[0]);
	b.DeletePerson(*persons[1]);
	b.DeletePerson(*persons[0]);


	// TRANSACTION TESTING:
	Transaction** transactions =  new Transaction*[4];
	transactions[0] = new Transaction (&a, &b, 500, "today");
	transactions[1] = new Transaction (&b, &b, 800, "yesterday");
	transactions[2] = new Transaction (&b, &a, 1200, "10/4");
	transactions[3] = new Transaction (&a, &b, -55500, "7/4");

	//b.AddTransaction(*transactions[0]);
	//b.AddTransaction(*transactions[1]);
	//b.AddTransaction(*transactions[2]);
	//b.AddTransaction(*transactions[3]);
	//b.AddTransaction(*transactions[2]);

	//a.SetTransactions(transactions, 4);
	//b.clearTransactions();

	// b balance
	std::cout << b.GetBalance()<< std::endl;
	// a balance
	std::cout << a.GetBalance() << std::endl;

	b.AddTransaction(*transactions[0]);

	// b balance
	std::cout << b.GetBalance() << std::endl;
	// a balance
	std::cout << a.GetBalance() << std::endl;


	b.Withdraw(2500, "12/4");
	// b balance
	std::cout << b.GetBalance() << std::endl;


	Account c(a);
	std::cout << c.GetBalance() << std::endl;


	//Bank bank( "The First International Bank of Israel​ Ltd", 31 );
	//Account account;
	//Person lior( "Lior Li", 20145876 );
	//Person liam( "Liam Winter", 2048741 );
	//int countNumberOfUsers = account.GetTotalPersons();
	//double currentA, currentB, currentC;

	///*****************************A**************************************/
	//if( 0 != strcmp(bank.GetBankName(), "The First International Bank of Israel​ Ltd" ) )
	//	cout << "Error in creating a bank object(-4)" << endl;

	///*****************************B**************************************/
	//account.AddPerson( Person( "Amit Choen", 30292827 ), 10000 );
	//if( account.GetTotalPersons() != 1 )
	//	cout << "Error in adding a new Person to an account(-4)" << endl;

	//account.AddPerson( lior, 5000 );
	//if( account.GetPersons()[1]->GetId() != 20145876 )
	//	cout << "Error in adding a Person to the account(-4)" << endl;

	//if( account.GetBalance() != 15000 )
	//	cout << "Error in adding a Person to the account(-4)" << endl;

	///*****************************C**************************************/
	//bank.AddAccount( account );
	//if( bank.GetTotal() != 15000 )
	//	cout << "Error in adding an account to the bank(-4)" << endl;

	//if( bank.GetNumberOfAccounts() != 1 )
	//	cout << "Error in updating the a count of account in the bank(-4)" << endl;

	//bank.AddAccount( Account( Person( "Dor Levi", 32145672 ), 10 ) );
	//if( bank.GetTotal() != 15010 )
	//	cout << "Error in adding a new account to the bank (-4)" << endl;

	//if( bank.GetNumberOfAccounts() != 2 )
	//	cout << "Error in updating the a count of account in the bank(-4)" << endl;

	///*****************************D**************************************/
	//currentA = bank.GetAccounts()[0]->GetBalance();
	//currentB = bank.GetAccounts()[1]->GetBalance();

	//bank.AddAccount( lior, 200 );
	//Account* tmp = bank.GetAccounts()[2];

	//bank.AddPerson( Person( "Karin Yon", 22415624 ), *tmp, 1005 );
	//if( bank.GetAccounts()[2]->GetTotalPersons() != 2 )
	//	cout << "Error in adding a new person to an existing account(-4)" << endl;

	//bank.GetAccounts()[0]->AddTransaction( Transaction( bank.GetAccounts()[0], bank.GetAccounts()[1], 500, "12-04-18" ) );
	//if( bank.GetAccounts()[0]->GetNumOfTransactions() != 1 )
	//	cout << "Error in number of transaction (-4)" << endl;

	//if( bank.GetAccounts()[0]->GetBalance() != currentA - 500 )
	//	cout << "Error in update the balance of the account (-4)" << endl;

	//if( bank.GetAccounts()[1]->GetBalance() != currentB + 500 )
	//	cout << "Error in update the balance of the other account (-4)" << currentA << endl;

	//currentC = bank.GetAccounts()[2]->GetBalance();
	//bank.GetAccounts()[2]->Deposit( 555, "11-04-18" );

	//if( bank.GetAccounts()[2]->GetBalance() != currentC + 555 )
	//	cout << "Error in deposit to the account (-4)" << endl;

	//Transaction t( bank.GetAccounts()[0], bank.GetAccounts()[2], 500, "12-04-18" );

	//bank.GetAccounts()[1]->AddTransaction( t );
	//if( bank.GetAccounts()[0]->GetNumOfTransactions() != 2 )
	//	cout << "Error in number of transaction (-4)" << endl;

	//if( bank.GetAccounts()[2]->GetNumOfTransactions() != 2 )
	//	cout << "Error in number of transaction (-4)" << endl;

	//if( bank.GetAccounts()[2]->GetBalance() != 2260 )
	//	cout << "Error in balance after transaction (-4)" << endl;

	///*****************************E**************************************/
	//account.DeletePerson( lior );
	//if( 3 != bank.GetNumberOfAccounts() )
	//	cout << "Error in updating number of account in the bank(-4)" << endl;

	//if( 1 != account.GetTotalPersons() )
	//	cout << "Error in updating number of persons in the account(-4)" << endl;

	//bank.DeletePerson( liam );
	//if( 3 != bank.GetNumberOfAccounts() )
	//	cout << "Error in updating number of account in the bank(-4)" << endl;

	//bank.AddAccount( Account( liam, 9955 ) );
	//if( 4 != bank.GetNumberOfAccounts() )
	//	cout << "Error in updating number of account in the bank(-4)" << endl;

	//bank.AddAccount( account );
	//if( 4 != bank.GetNumberOfAccounts() )
	//	cout << "Error in updating number of account in the bank(-4)" << endl;
	//
	//bank.DeletePerson( liam );
	//if( 3 != bank.GetNumberOfAccounts() )
	//	cout << "Error in updating number of account in the bank(-4)" << endl;

	//cout << "done" << endl;
	//
	//*/

	return 0;
}