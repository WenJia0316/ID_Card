#include "Person.h"
#include <ctime>
#include <cstring> 
#include <iomanip>
#include <sstream>

Person::Person(std::string id, std::string n, std::string gen, std::string addr, std::string eth, std::string dob, std::string issue)
: idNumber(id), name(n), gender(gen), address(addr), ethnicity(eth), dateOfBirth(dob), issueDate(issue) 
{
	int age = calculateAge();
	if (age < 18) 
	{
		expirationDate = calculateExpirationDate(5);
	} 
	else 
	{
		expirationDate = calculateExpirationDate(10);
	}
}

int Person::calculateAge() const {
	time_t now = time(0);
	tm* currentTime = localtime(&now);
	int currentYear = currentTime->tm_year + 1900;
	int birthYear = stoi(dateOfBirth.substr(0, 4));
	int age = currentYear - birthYear;
	return age;
}

std::string Person::getIDNumber() const { return idNumber; }
std::string Person::getName() const { return name; }
std::string Person::getGender() const { return gender; }
std::string Person::getAddress() const { return address; }
std::string Person::getEthnicity() const { return ethnicity; }
std::string Person::getDateOfBirth() const { return dateOfBirth; }
std::string Person::getIssueDate() const { return issueDate; }
std::string Person::getExpirationDate() const { return expirationDate; }

std::string Person::calculateExpirationDate(int years) const {
	tm tmIssue = {};
	sscanf(issueDate.c_str(), "%d-%d-%d", &tmIssue.tm_year, &tmIssue.tm_mon, &tmIssue.tm_mday);
	tmIssue.tm_year -= 1900;
	tmIssue.tm_mon--;
	tmIssue.tm_year += years;
	char buffer[11];
	strftime(buffer, sizeof(buffer), "%Y-%m-%d", &tmIssue);
	return std::string(buffer);
}

void Person::display() const {
	std::cout << "���֤�ţ�" << idNumber << std::endl;
	std::cout << "������" << name << std::endl;
	std::cout << "�Ա�" << gender << std::endl;
	std::cout << "��ַ��" << address << std::endl;
	std::cout << "���壺" << ethnicity << std::endl;
	std::cout << "�������ڣ�" << dateOfBirth << std::endl;
	std::cout << "�������ڣ�" << issueDate << std::endl;
	std::cout << "��ֹ���ڣ�" << expirationDate << std::endl;
}

void Person::setIssueDate(const std::string& newIssueDate) {
	issueDate = newIssueDate;
}

void Person::setExpirationDate(const std::string& newExpirationDate) {
	expirationDate = newExpirationDate;
}
