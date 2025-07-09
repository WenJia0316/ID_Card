#ifndef IDMANAGER_H
#define IDMANAGER_H

#include "Person.h"
#include <vector>
#include <string>
using std::string; 

class IDManager 
{
private:
	string deathRecordFile = "death.dat";
	
public:
	std::vector<Person> persons;
	void addPerson(const Person& person);
	void modifyPerson(const string& idNumber);
	static bool sortByAreaCodeAsc(const Person& p1, const Person& p2);
	static bool sortByAreaCodeDesc(const Person& p1, const Person& p2);
	static bool sortByNameAsc(const Person& p1, const Person& p2);
	void sortByAreaCodeAscending();
	void sortByAreaCodeDescending();
	void sortByNameAscending();
	void searchByID(const string& idNumber);
	void deletePerson(const string& idNumber);
	void outputAllPersons();
};

#endif 
