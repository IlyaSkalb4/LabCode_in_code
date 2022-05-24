#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

using namespace std;

void printCode(string filename)
{
	int countr = 1;
	string str;
	fstream file;
	file.open(filename, ios::in);
	if (!file.is_open())
	{
		cout << "Error! File not opened!" << endl;
	}
	else
	{
		while (getline(file, str))
		{
			cout << countr << "\t|" << str << "\n";
			countr++;
		}
	}
	cout << endl;
}
int countStr(string filename)
{
	int countr = 1;
	string str;
	fstream file;
	file.open(filename, ios::in);
	if (!file.is_open())
	{
		cout << "Error! File not opened!" << endl;
	}
	else
	{
		while (getline(file, str))
		{
			countr++;
		}
	}
	return countr;
}
string fillingStr(int countr)
{
	string text, end = "~", buf;
	cout << "To finish typing type: Enter + \"~\" + Enter!\n\n";
	do
	{
		cout << countr << "\t|";
		getline(cin, buf);
		if (buf == end)
		{
			return text;
		}
		text += buf;
		text += "\n";
		countr++;
	} while (true);
}
void newCode(string filename, string& code)
{
	string text, buf = "~";
	fstream file;
	int countr = 1;
	file.open(filename, ios::out);
	if (file.is_open())
	{
		code = fillingStr(countr);
		file << code;
		file.close();
	}
	else
	{
		cout << "Error! File not opened!" << endl;
	}
}
void addLine(string filename, string& code, int numberline)
{
	int index = 0, pos = 0, countr = 1;
	string newstr, text, begin, end, buf;
	fstream file;
	file.open(filename, ios::in);
	if (!file.is_open())
	{
		cout << "Error! File not opened!" << endl;
	}
	else
	{
		cout << "Enter line number to edit: ";
		cin >> index;
		cin.ignore();
		if (index > numberline || index < 1)
		{
			cout << "This line does not exist!\n";
		}
		else
		{
			newstr = fillingStr(index);
			while (getline(file, text))
			{
				if (index == countr)
				{
					pos = code.find(text);
					for (int i = 0; i < code.size(); i++)
					{
						if (i < pos + text.size())
						{
							begin += code[i];
						}
						else if (i > pos + text.size())
						{
							end += code[i];
						}
					}
					buf = begin + newstr + end;
					code = buf;
				}
				countr++;
			}
			file.close();
		}
		file.open(filename, ios::out);
		if (!file.is_open())
		{
			cout << "Error! File not opened!" << endl;
		}
		else
		{
			file << code;
			file.close();
		}
	}
}
void changeCode(string filename, string& code, int numberline)
{
	int num = 0, pos = 0, countr = 1;
	string newstr, text, begin, end, buf;
	fstream file;
	file.open(filename, ios::in);
	if (!file.is_open())
	{
		cout << "Error! File not opened!" << endl;
	}
	else
	{
		cout << "Delete line - 1,\nEdit line - any number\nEnter variant: ";
		cin >> pos;
		cout << "Enter line number to edit: ";
		cin >> num;
		cin.ignore();
		if (num > numberline || num < 1)
		{
			cout << "This line does not exist!\n";
		}
		else
		{
			if (pos == 1)
			{
				newstr = "";
			}
			else
			{
				cout << "Enter the edited line:\n" << num << "\t|";
				getline(cin, newstr);
			}
			while(getline(file, text))
			{
				if (num == countr)
				{
					pos = code.find(text);
					for (int i = 0; i < code.size(); i++)
					{
						if (i < pos)
						{
							begin += code[i];
						}
						else if (i >= pos + text.size())
						{
							end += code[i];
						}
					}
					buf = begin + newstr + end;
					code = buf;
				}
				countr++;
			}
			file.close();
		}
		file.open(filename, ios::out);
		if (!file.is_open())
		{
			cout << "Error! File not opened!" << endl;
		}
		else
		{
			file << code;
			file.close();
		}
	}
}
void startCode(string filename)
{
	string filename_exe = "prog.exe", command;
	command = "g++ -o " + filename_exe + " " + filename;
	system(command.c_str());
	command = "start " + filename_exe;
	system(command.c_str());
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int num = 0, numberline = 0;
	string filename = "inside_main.cpp", code = "";
	cout << "\t\t\t\t\tMini C++ code editor.\n";
		do
		{
			cout << "\nAdd new code - 1,\nChange code - 2,\nOutput code - 3,\nAdd code - 4,\nStart - 5,\nExit - 0\n\nEnter variant: ";
			cin >> num;
			system("cls");
			cin.ignore();
			switch (num)
			{
			case 0:
			{
				exit(1);
				break;
			}
			case 1:
			{
				newCode(filename, code);
				numberline = countStr(filename);
				break;
			}
			case 2:
			{
				if (code == "")
					cout << "No code.\n";
				else
				{
					printCode(filename);
					changeCode(filename, code, numberline);
				}
				break;
			}
			case 3:
			{
				if (code == "")
					cout << "No code.\n";
				else
					printCode(filename);
				break;
				startCode(filename); 
				break;
			}
			case 4:
			{
				if (code == "")
					cout << "No code.\n";
				else
				{
					printCode(filename);
					addLine(filename, code, numberline);
				}
				break;
				startCode(filename);
				break;
			}
			case 5:
			{
				startCode(filename);
				break;
			}
			default:
				cout << "Invalid!\n";
				break;
			}
		} while (true);
		return 0;
}