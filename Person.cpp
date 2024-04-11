#include "Person.h"

Person::Person():m_name(nullptr),m_id(NULL){}
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
	m_id = NULL;

}



void Person::SetName(const char* newName){
	
	int newNameLen = strlen(newName) + 1;

	m_name = new char[newNameLen];
	strcpy_s(m_name, newNameLen, newName);

}

void Person::SetId(int newId) { m_id = newId; }

char* Person::GetName() const { return m_name; }
int	Person::GetId() const { return m_id; }
