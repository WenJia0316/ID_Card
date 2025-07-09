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
		cout << "主菜单" << endl;
		cout << "1. 管理员" << endl;
		cout << "2. 个人用户" << endl;
		cout << "3. 退出" << endl;
		cout << "请选择：";
		cin >> choice;
		
		switch (choice) {
			case 1: {
				int adminChoice;
				do {
					cout << "管理员系统" << endl;
					cout << "1. 添加个人信息" << endl;
					cout << "2. 修改个人信息(按身份证号)" << endl;
					cout << "3. 排序(分别按区号升序、区号降序、姓名升序)" << endl;
					cout << "4. 查询个人信息(按身份证号)" << endl;
					cout << "5. 删除个人信息" << endl;
					cout << "6. 输出所有个人信息" << endl;
					cout << "7. 退出子系统" << endl;
					cout << "请选择：";
					cin >> adminChoice;
					switch (adminChoice) {
						case 1: {
							string id, name, gender, address, ethnicity, dob, issue;
							cout << "请输入身份证号：";
							cin >> id;
							
							if (id.length() != 18 || !all_of(id.begin(), id.end(), ::isdigit)) {
								cout << "身份证号必须为18位数字，请重新输入" << endl;
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
								cout << "身份证号已存在，请重新输入" << endl;
								break;
							}
							
							cout << "请输入姓名：";
							cin.ignore();
							getline(std::cin, name);
							cout << "请输入性别：";
							cin >> gender;
							cout << "请输入地址：";
							cin.ignore();
							getline(std::cin, address);
							cout << "请输入民族：";
							cin >> ethnicity;
							cout << "请输入出生日期(YYYY-MM-DD)：";
							cin >> dob;
							
							time_t now = time(0);
							tm* currentTime = localtime(&now);
							char buffer[80];
							strftime(buffer, 80, "%Y-%m-%d", currentTime);
							issue = buffer;
							
							Person newPerson(id, name, gender, address, ethnicity, dob, issue);
							idManager.addPerson(newPerson);
							cout << "个人信息添加成功" << endl;
							break;
						}
						case 2: {
							string idToModify;
							cout << "请输入要修改的个人的身份证号：";
							cin >> idToModify;
							idManager.modifyPerson(idToModify);
							break;
						}
						case 3: {
							int sortChoice;
							cout << "排序选项：" << endl;
							cout << "1. 区号升序" << endl;
							cout << "2. 区号降序" << endl;
							cout << "3. 姓名升序" << endl;
							cout << "请选择排序方式：";
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
									cout << "请选择1-3" << endl;
									break;
							}
							break;
						}
						case 4: {
							string idToSearch;
							cout << "请输入要查询的个人的身份证号：";
							cin >> idToSearch;
							idManager.searchByID(idToSearch);
							break;
						}
						case 5: {
							string idToDelete;
							cout << "请输入要删除的个人的身份证号：";
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
							cout << "请选择1-7" << endl;
							break;
					}
				} while (adminChoice != 7);
				break;
			}
			case 2: {
				int userChoice;
				do {
					cout << "个人用户系统" << endl;
					cout << "1. 查询个人信息(按身份证号)" << endl;
					cout << "2. 退出子系统" << endl;
					cout << "请选择：";
					cin >> userChoice;
					
					switch (userChoice) {
						case 1: {
							string idToSearch;
							cout << "请输入要查询的个人的身份证号：";
							cin >> idToSearch;
							idManager.searchByID(idToSearch);
							break;
						}
					case 2:
						break;
						default:
							cout << "请选择1-2" << endl;
							break;
					}
				} while (userChoice != 2);
				break;
			}
		case 3:
			break;
			default:
				cout << "请选择1-3" << endl;
				break;
		}
	} while (choice != 3);
	
	return 0;
}
