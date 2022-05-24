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
fstream fillingFile(string filename, string code)
{
	fstream file; 
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
	return file;
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
void deleteLine(string filename, string& code, int numberline)
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

		cout << "Line index to delete: ";
		cin >> index;
		cin.ignore();
		if (index > numberline || index < 1)
		{
			cout << "This line does not exist!\n";
		}
		else
		{
			code.clear();
			while (getline(file, text))
			{
				if (index != countr)
				{
					code += text + '\n';
				}
				countr++;
			}
			file.close();
		}
		file = fillingFile(filename, code);
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
		cout << "Line index to add: ";
		cin >> index;
		cin.ignore();
		if (index > numberline || index < 1)
		{
			cout << "This line does not exist!\n";
		}
		else
		{
			cout << "Enter line: ";
			newstr = fillingStr(index);
			code.clear();
			while (getline(file, text))
			{
				if (index == countr)
				{
					code += newstr;
				}
				code += text + '\n';
				countr++;
			}
			file.close();
		}
		file = fillingFile(filename, code);
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
		cout << "Delete line - 1,\nEdit line - 2\nEnter variant: ";
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
			cout << "Enter the edited line:\n" << num << "\t|";
			getline(cin, newstr);
			code.clear();
			while (getline(file, text))
			{
				if (num == countr)
					code += newstr + "\n";
				else
					code += text + "\n";
				countr++;
			}
			file.close();
			file = fillingFile(filename, code);
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
		cout << "\nOutput code - 1,\nAdd new code - 2,\nChange code - 3,\nAdd code - 4,\nDelete line - 5,\nStart - 6,\nExit - 0\n\nEnter variant: ";
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
			if (code == "")
				cout << "No code.\n";
			else
				printCode(filename);
			break;
		}
		case 2:
		{
			newCode(filename, code);
			numberline = countStr(filename);
			break;
		}
		case 3:
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
			if (code == "")
				cout << "No code.\n";
			else
			{
				printCode(filename);
				deleteLine(filename, code, numberline);
			}
			break;
		}
		case 6:
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