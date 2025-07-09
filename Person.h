#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>
using std::string; 

class Person
{
private:
	string idNumber;
	string name;
	string gender;
	string address;
	string ethnicity;
	string dateOfBirth;
	string issueDate;
	string expirationDate;
	
public:
	Person(string id, string n, string gen, string addr, string eth, string dob, string issue);
	int calculateAge() const;
	string getIDNumber() const;
	string getName() const;
	string getGender() const;
	string getAddress() const;
	string getEthnicity() const;
	string getDateOfBirth() const;
	string getIssueDate() const;
	string getExpirationDate() const;
	string calculateExpirationDate(int years) const;
	void display() const;
	void setIssueDate(const string& newIssueDate);
	void setExpirationDate(const string& newExpirationDate);
};

#endif  
