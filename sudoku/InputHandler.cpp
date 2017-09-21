#include "stdafx.h"
#include "InputHandler.h"
#include "FinalMaker.h"
#include "SudokuSolver.h"

void InputHandler::check(int argc, char ** argv)
{
	if (argc == 3) {
		string parameter1 = argv[1];
		string parameter2 = argv[2];
		if (parameter1 == "-c") {
			int n = isNum(parameter2);
			if (n <= 0 || n > 1000000)
				cout << "������0<n<=1000000��" << endl;
			else {
				string str;
				FianlMaker fm;
				str = fm.make(n);
				ofstream out("sudoku.txt", ios::out | ios::trunc);	// д��ǰ������ļ�
				if (out.is_open()) {
					out << str;
					out.close();
				}
				cout << "������" + parameter2 + "����������" << endl;
			}
			
		}
		else if (parameter1 == "-s") {
			ifstream in(parameter2);
			if (!in.is_open()) {
				cout << parameter2 + "�޷��򿪣�" << endl;
				return ;
			}
			
			char ch[81];
			char c;
			int count = 0;
			string answer = "";
			while (in.get(c)) {	//in >> c ����Կհ׻س���
				if (isdigit(c)) {
					ch[count++] = c;
				}
				if (count == 81) {
					count = 0;
					SudokuSolver ss;
					answer += ss.solve(ch);
				}
			}
			if (count != 0) {
				string str = "���ڷǷ���ʽ��";
				answer += str;
				cout << str << endl;
			}
			else
				cout << "�ѽ��" + parameter2 + "�������" << endl;
			in.close();
			ofstream out("sudoku.txt", ios::out|ios::trunc);
			if (out.is_open()) {
				out << answer;
				out.close();
			}
		}
		else {
			cout << "��������" << endl;
		}
	}
	else {
		cout << "��������" << endl;
	}
	return ;
}

int InputHandler::isNum(const string & str)
{
	size_t size = str.size();
	if (size > 7)
		return 0;
	for (size_t i = 0; i < size; i++){
		int ascii = int(str[i]);
		if (ascii >= 48 && ascii <= 57)
			continue;
		else
			return 0;
	}
	return stoi(str);
}

int InputHandler::isPath(const string & str)
{
	fstream file;
	file.open(str, ios::in);
	if (file)
		return 1;
	else {
		return 0;
	}
}