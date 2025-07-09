#include "IDManager.h"
#include <algorithm>
#include <iostream>
using std::cout;
using std::cin;
using std::endl; 
#include <string>
using std::string; 
#include <fstream>
#include <ctime>

void IDManager::addPerson(const Person& person) {
	persons.push_back(person);
}

void IDManager::modifyPerson(const string& idNumber) {
	bool found = false;
	for (auto& person : persons) {
		if (person.getIDNumber() == idNumber) {
			found = true;
			cout << "��ǰ������Ϣ��" << endl;
			person.display();
			string newName;
			string newGender;
			string newAddress;
			string newEthnicity;
			string newDob;
			string newIssue;
			char choice;
			cout << "�Ƿ��޸�������(y/n): ";
			cin >> choice;
			if (tolower(choice) == 'y') {
				cout << "��������������";
				cin.ignore();
				getline(std::cin, newName);
				person.getName() = newName; 
			}
			cout << "�Ƿ��޸��Ա�(y/n): ";
			cin >> choice;
			if (tolower(choice) == 'y') {
				cout << "���������Ա�";
				cin >> newGender;
				person.getGender() = newGender; 
			}
			cout << "�Ƿ��޸ĵ�ַ��(y/n): ";
			cin >> choice;
			if (tolower(choice) == 'y') {
				cout << "�������µ�ַ��";
				cin.ignore();
				getline(std::cin, newAddress);
				person.getAddress() = newAddress; 
			}
			cout << "�Ƿ��޸����壿(y/n): ";
			cin >> choice;
			if (tolower(choice) == 'y') {
				cout << "�����������壺";
				cin >> newEthnicity;
				person.getEthnicity() = newEthnicity; 
			}
			cout << "�Ƿ��޸ĳ������ڣ�(y/n): ";
			cin >> choice;
			if (tolower(choice) == 'y') {
				cout << "�������³�������(YYYY-MM-DD)��";
				cin >> newDob;
				person.getDateOfBirth() = newDob; 
			}
			cout << "�Ƿ��޸İ������ڣ�(y/n): ";
			cin >> choice;
			if (tolower(choice) == 'y') {
				cout << "�������°�������(YYYY-MM-DD)��";
			    cin >> newIssue;
				person.setIssueDate(newIssue);
				int age = person.calculateAge();
				if (age < 18) {
					person.setExpirationDate(person.calculateExpirationDate(5));
				} else {
					person.setExpirationDate(person.calculateExpirationDate(10));
				}
			}
			cout << "������Ϣ�޸ĳɹ���" << endl;
			break;
		}
	}
	if (!found) {
		cout << "�������֤��Ϊ " << idNumber << " �ļ�¼" << endl;
	}
}

bool IDManager::sortByAreaCodeAsc(const Person& p1, const Person& p2) {
	return p1.getIDNumber().substr(0, 6) < p2.getIDNumber().substr(0, 6);
}

bool IDManager::sortByAreaCodeDesc(const Person& p1, const Person& p2) {
	return p1.getIDNumber().substr(0, 6) > p2.getIDNumber().substr(0, 6);
}

bool IDManager::sortByNameAsc(const Person& p1, const Person& p2) {
	return p1.getName() < p2.getName();
}

void IDManager::sortByAreaCodeAscending() {
	std::sort(persons.begin(), persons.end(), sortByAreaCodeAsc);
	cout << "��������������" << endl;	outputAllPersons();
}

void IDManager::sortByAreaCodeDescending() {
	std::sort(persons.begin(), persons.end(), sortByAreaCodeDesc);
	cout << "���������뽵��" << endl;	outputAllPersons();
}

void IDManager::sortByNameAscending() {
	std::sort(persons.begin(), persons.end(), sortByNameAsc);
	cout << "����������" << endl;	outputAllPersons();
}

void IDManager::searchByID(const string& idNumber) {
	bool found = false;
	for (const auto& person : persons) {
		if (person.getIDNumber() == idNumber) {
			cout << "������Ϣ��" << endl;
			person.display();
			found = true;
			break;
		}
	}
	if (!found) {
		cout << "�������֤��Ϊ " << idNumber << " �ļ�¼" << endl;
	}
}

void IDManager::deletePerson(const string& idNumber) {
	bool found = false;
	char buffer[80]; 
	
	for (auto& person : persons) {
		if (person.getIDNumber() == idNumber) {
			found = true;
			
			std::ofstream outFile(deathRecordFile, std::ios::app);
			if (outFile.is_open()) {
				outFile << "���֤�ţ�" << person.getIDNumber() << endl;
				outFile << "������" << person.getName() << endl;
				outFile << "�Ա�" << person.getGender() << endl;
				outFile << "��ַ��" << person.getAddress() << endl;
				outFile << "���壺" << person.getEthnicity() << endl;
				outFile << "�������ڣ�" << person.getDateOfBirth() << endl;
				outFile << "�������ڣ�" << person.getIssueDate() << endl;
				outFile << "��ֹ���ڣ�" << person.getExpirationDate() << endl;
				outFile << "Deletion Date: ";
				time_t now = time(0);
				tm* currentTime = localtime(&now);
				strftime(buffer, 80, "%Y-%m-%d", currentTime); 
				outFile << buffer << endl;
				outFile << "------------------------------------" << endl;
				outFile.close();
			} 
			
			person.setIssueDate(buffer);
			person.setExpirationDate(buffer);
			
			cout << "��¼����ɾ��������ӵ� " << deathRecordFile << endl;
			person.display();
			
			break;
		}
	}
	if (!found) {
		cout << "�������֤��Ϊ " << idNumber << " �ļ�¼" << endl;
	}
}

void IDManager::outputAllPersons() {
	if (persons.empty()) {
		cout << "���κθ�����Ϣ" << endl;
	} else {
		cout << "���и�����Ϣ��" << endl;
		for (const auto& person : persons) {
			person.display();
			cout << endl;
		}
	}
}
