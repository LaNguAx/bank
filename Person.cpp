#include "Person.h"

/*
	Itay Andre Aknin
*/


Person::Person():m_name(nullptr),m_id(0){}

Person::Person(const char* name, int id){
	this->SetName(name);
	this->SetId(id);
}
Person::Person(const Person& other){

	this->SetName(other.GetName());
	this->SetId(other.GetId());
}
Person::~Person(){
	
	delete[] m_name;
	m_name = nullptr;
	m_id = 0;
	
}

void Person::SetName(const char* newName){
	
	int newNameLen = strlen(newName) + 1;

	m_name = new char[newNameLen];
	//strcpy_s(m_name, newNameLen, newName);
	strcpy(m_name, newName);
}

void Person::SetId(int newId) { m_id = newId; }

char* Person::GetName() const { return m_name; }
int	Person::GetId() const { return m_id; }
