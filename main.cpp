#include "Person.h"
#include "IDManager.h"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <string>
using std::string;
#include <algorithm>
#include <time.h>

int main() {
	IDManager idManager;
	
	int choice;
	do {
		cout << "���˵�" << endl;
		cout << "1. ����Ա" << endl;
		cout << "2. �����û�" << endl;
		cout << "3. �˳�" << endl;
		cout << "��ѡ��";
		cin >> choice;
		
		switch (choice) {
			case 1: {
				int adminChoice;
				do {
					cout << "����Աϵͳ" << endl;
					cout << "1. ��Ӹ�����Ϣ" << endl;
					cout << "2. �޸ĸ�����Ϣ(�����֤��)" << endl;
					cout << "3. ����(�ֱ������������Ž�����������)" << endl;
					cout << "4. ��ѯ������Ϣ(�����֤��)" << endl;
					cout << "5. ɾ��������Ϣ" << endl;
					cout << "6. ������и�����Ϣ" << endl;
					cout << "7. �˳���ϵͳ" << endl;
					cout << "��ѡ��";
					cin >> adminChoice;
					switch (adminChoice) {
						case 1: {
							string id, name, gender, address, ethnicity, dob, issue;
							cout << "���������֤�ţ�";
							cin >> id;
							
							if (id.length() != 18 || !all_of(id.begin(), id.end(), ::isdigit)) {
								cout << "���֤�ű���Ϊ18λ���֣�����������" << endl;
								break;
							}
							
							bool idExists = false;
							for (const auto& person : idManager.persons) {
								if (person.getIDNumber() == id) {
									idExists = true;
									break;
								}
							}
							if (idExists) {
								cout << "���֤���Ѵ��ڣ�����������" << endl;
								break;
							}
							
							cout << "������������";
							cin.ignore();
							getline(std::cin, name);
							cout << "�������Ա�";
							cin >> gender;
							cout << "�������ַ��";
							cin.ignore();
							getline(std::cin, address);
							cout << "���������壺";
							cin >> ethnicity;
							cout << "�������������(YYYY-MM-DD)��";
							cin >> dob;
							
							time_t now = time(0);
							tm* currentTime = localtime(&now);
							char buffer[80];
							strftime(buffer, 80, "%Y-%m-%d", currentTime);
							issue = buffer;
							
							Person newPerson(id, name, gender, address, ethnicity, dob, issue);
							idManager.addPerson(newPerson);
							cout << "������Ϣ��ӳɹ�" << endl;
							break;
						}
						case 2: {
							string idToModify;
							cout << "������Ҫ�޸ĵĸ��˵����֤�ţ�";
							cin >> idToModify;
							idManager.modifyPerson(idToModify);
							break;
						}
						case 3: {
							int sortChoice;
							cout << "����ѡ�" << endl;
							cout << "1. ��������" << endl;
							cout << "2. ���Ž���" << endl;
							cout << "3. ��������" << endl;
							cout << "��ѡ������ʽ��";
							cin >> sortChoice;
							
							switch (sortChoice) {
							case 1:
								idManager.sortByAreaCodeAscending();
								break;
							case 2:
								idManager.sortByAreaCodeDescending();
								break;
							case 3:
								idManager.sortByNameAscending();
								break;
								default:
									cout << "��ѡ��1-3" << endl;
									break;
							}
							break;
						}
						case 4: {
							string idToSearch;
							cout << "������Ҫ��ѯ�ĸ��˵����֤�ţ�";
							cin >> idToSearch;
							idManager.searchByID(idToSearch);
							break;
						}
						case 5: {
							string idToDelete;
							cout << "������Ҫɾ���ĸ��˵����֤�ţ�";
							cin >> idToDelete;
							idManager.deletePerson(idToDelete);
							break;
						}
						case 6: {
							idManager.outputAllPersons();
							break;
						}
					case 7:
						break;
						default:
							cout << "��ѡ��1-7" << endl;
							break;
					}
				} while (adminChoice != 7);
				break;
			}
			case 2: {
				int userChoice;
				do {
					cout << "�����û�ϵͳ" << endl;
					cout << "1. ��ѯ������Ϣ(�����֤��)" << endl;
					cout << "2. �˳���ϵͳ" << endl;
					cout << "��ѡ��";
					cin >> userChoice;
					
					switch (userChoice) {
						case 1: {
							string idToSearch;
							cout << "������Ҫ��ѯ�ĸ��˵����֤�ţ�";
							cin >> idToSearch;
							idManager.searchByID(idToSearch);
							break;
						}
					case 2:
						break;
						default:
							cout << "��ѡ��1-2" << endl;
							break;
					}
				} while (userChoice != 2);
				break;
			}
		case 3:
			break;
			default:
				cout << "��ѡ��1-3" << endl;
				break;
		}
	} while (choice != 3);
	
	return 0;
}
