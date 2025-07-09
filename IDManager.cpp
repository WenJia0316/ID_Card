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
			cout << "当前个人信息：" << endl;
			person.display();
			string newName;
			string newGender;
			string newAddress;
			string newEthnicity;
			string newDob;
			string newIssue;
			char choice;
			cout << "是否修改姓名？(y/n): ";
			cin >> choice;
			if (tolower(choice) == 'y') {
				cout << "请输入新姓名：";
				cin.ignore();
				getline(std::cin, newName);
				person.getName() = newName; 
			}
			cout << "是否修改性别？(y/n): ";
			cin >> choice;
			if (tolower(choice) == 'y') {
				cout << "请输入新性别：";
				cin >> newGender;
				person.getGender() = newGender; 
			}
			cout << "是否修改地址？(y/n): ";
			cin >> choice;
			if (tolower(choice) == 'y') {
				cout << "请输入新地址：";
				cin.ignore();
				getline(std::cin, newAddress);
				person.getAddress() = newAddress; 
			}
			cout << "是否修改民族？(y/n): ";
			cin >> choice;
			if (tolower(choice) == 'y') {
				cout << "请输入新民族：";
				cin >> newEthnicity;
				person.getEthnicity() = newEthnicity; 
			}
			cout << "是否修改出生日期？(y/n): ";
			cin >> choice;
			if (tolower(choice) == 'y') {
				cout << "请输入新出生日期(YYYY-MM-DD)：";
				cin >> newDob;
				person.getDateOfBirth() = newDob; 
			}
			cout << "是否修改办理日期？(y/n): ";
			cin >> choice;
			if (tolower(choice) == 'y') {
				cout << "请输入新办理日期(YYYY-MM-DD)：";
			    cin >> newIssue;
				person.setIssueDate(newIssue);
				int age = person.calculateAge();
				if (age < 18) {
					person.setExpirationDate(person.calculateExpirationDate(5));
				} else {
					person.setExpirationDate(person.calculateExpirationDate(10));
				}
			}
			cout << "个人信息修改成功！" << endl;
			break;
		}
	}
	if (!found) {
		cout << "查无身份证号为 " << idNumber << " 的记录" << endl;
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
	cout << "按地区代码升序" << endl;	outputAllPersons();
}

void IDManager::sortByAreaCodeDescending() {
	std::sort(persons.begin(), persons.end(), sortByAreaCodeDesc);
	cout << "按地区代码降序" << endl;	outputAllPersons();
}

void IDManager::sortByNameAscending() {
	std::sort(persons.begin(), persons.end(), sortByNameAsc);
	cout << "按姓名升序" << endl;	outputAllPersons();
}

void IDManager::searchByID(const string& idNumber) {
	bool found = false;
	for (const auto& person : persons) {
		if (person.getIDNumber() == idNumber) {
			cout << "个人信息：" << endl;
			person.display();
			found = true;
			break;
		}
	}
	if (!found) {
		cout << "查无身份证号为 " << idNumber << " 的记录" << endl;
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
				outFile << "身份证号：" << person.getIDNumber() << endl;
				outFile << "姓名：" << person.getName() << endl;
				outFile << "性别：" << person.getGender() << endl;
				outFile << "地址：" << person.getAddress() << endl;
				outFile << "民族：" << person.getEthnicity() << endl;
				outFile << "出生日期：" << person.getDateOfBirth() << endl;
				outFile << "办理日期：" << person.getIssueDate() << endl;
				outFile << "截止日期：" << person.getExpirationDate() << endl;
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
			
			cout << "记录将被删除，并添加到 " << deathRecordFile << endl;
			person.display();
			
			break;
		}
	}
	if (!found) {
		cout << "查无身份证号为 " << idNumber << " 的记录" << endl;
	}
}

void IDManager::outputAllPersons() {
	if (persons.empty()) {
		cout << "无任何个人信息" << endl;
	} else {
		cout << "所有个人信息：" << endl;
		for (const auto& person : persons) {
			person.display();
			cout << endl;
		}
	}
}
