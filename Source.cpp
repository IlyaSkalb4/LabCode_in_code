#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int countstr(string filename)
{
	int countr = 0;
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
void newCode(string filename, string& code)
{
	string text, buf = "~";
	fstream file;
	int countr = 1;
	file.open(filename, ios::out);
	if (file.is_open())
	{
		cout << "To finish typing type: Enter + \"~\" + Enter!\n\n";
		do
		{
			cout << countr << "\t|";
			getline(cin, text);
			if (text == buf)
			{
				break;
			}
			code += text;
			code += "\n";
			countr++;
		} while (true);
		file << code;
		file.close();
	}
	else
	{
		cout << "Error! File not opened!" << endl;
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
			while(getline(file, text))
			{
				if (num == countr)
				{
					pos = code.find(text);
					for (int i = 0; i < code.length(); i++)
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
	int num = 0, numberline = 0;
	string filename = "inside_main.cpp", code;
	cout << "\t\t\t\t\tMini C++ code editor.\n";
		do
		{
			cout << "\nAdd new code - 1,\nChange code - 2,\nStart - 3,\nExit - 0\nEnter variant: ";
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
				numberline = countstr(filename);
				break;
			}
			case 2:
			{
				changeCode(filename, code, numberline);
				break;
			}
			case 3:
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