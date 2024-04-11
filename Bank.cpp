#include "Bank.h"

Bank::Bank(){}
Bank::Bank(const char* name, int code){}
Bank::~Bank(){}

void	Bank::SetBankName(const char* name){}
void			Bank::SetAccount(Account** account, int numbeOfAccounts){}
void			Bank::SetTotal(double total){}
void			Bank::SetCode(int code){}
const char* Bank::GetBankName() const { return m_name; }
Account** Bank::GetAccounts() const { return m_account; }
int				Bank::GetNumberOfAccounts() const { return 0; }
double			Bank::GetTotal() const { return 0; }
int				Bank::GetCode() const { return 0; }

