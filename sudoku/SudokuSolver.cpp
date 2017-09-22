#include "stdafx.h"
#include "SudokuSolver.h"

string SudokuSolver::solve(char ch[]) {
	transform(table,ch);
	link();
	int select = 0;
	for (size_t i = 0; i < 9; i++) {
		for (size_t j = 0; j < 9; j++) {
			int k = table[i][j];
			if (k) {	// ����������Ŀ�Ѹ����ֵ��б�ѡ
				int row = i * 81 + j * 9 + k - 1;
				select++;
				remove(Col[Head[row]]);		// �Ƴ�������Ԫ�ؼ������Ԫ��
				for (int u = Right[Head[row]]; u != Head[row]; u = Right[u])	// �Ƴ���������Ԫ�ؼ������Ԫ��
					remove(Col[u]);
			}
		}
	}
	if (dfs(select + 1)) {
		out = "";
		for (size_t i = 0; i < 9; i++) {
			for (size_t j = 0; j < 8; j++)
				out += (to_string(table[i][j]) + " ");
			out += (to_string(table[i][8]) + "\n");
		}
	}
	else
		out = "�������޽�\n";
	out += "\n";
	return out;
}

void SudokuSolver::transform(int table[][9],char ch[]) {
	int index = 0;
	for (size_t i = 0; i < 9; i++)
		for (size_t j = 0; j < 9; j++)
			table[i][j] = ch[index++] - '0';
	return;
}

void SudokuSolver::link() {
	/* �����б�Ԫ�� */
	for (size_t i = 0; i < maxcol; i++) {
		Left[i] = i - 1;
		Right[i] = i + 1;
		Up[i] = Down[i] = i;
		Row[i] = 0;
		Col[i] = i;
		Size[i] = 0;
	}
	/* ����HeadԪ�� */
	Left[0] = maxcol - 1;
	Right[maxcol - 1] = 0;
	no = maxcol;
	/* ���ӡ�1��Ԫ�� */
	for (size_t i = 0; i < 9; i++) {
		for (size_t j = 0; j < 9; j++) {	// ����9x9����
			int k = table[i][j];
			if (k) {
				for (size_t t = 1; t <= 4; t++) {	// ÿ����0���ֻ���01�����в���4����1��Ԫ��
					Left[no + t] = no + t - 1;
					Right[no + t] = no + t + 1;
					Row[no + t] = i * 81 + j * 9 + k - 1;
				}
				Left[no + 1] = no + 4;
				Right[no + 4] = no + 1;
				Head[Row[no + 1]] = no + 1;
				/* ��4��Ԫ�ز��������� */
				insertNode(i * 9 + j + 1, no + 1);
				insertNode(81 + i * 9 + k, no + 2);
				insertNode(81 * 2 + j * 9 + k, no + 3);
				insertNode(81 * 3 + (i / 3 * 3 + j / 3) * 9 + k, no + 4);
				no += 4;
			}
			else {	// ��λ��Ϊ0��������
				for (size_t k = 1; k <= 9; k++) {	// ����9���
					for (size_t t = 1; t <= 4; t++) {	// ���ɲ��������ǵ�Ԫ��
						Left[no + t] = no + t - 1;
						Right[no + t] = no + t + 1;
						Row[no + t] = i * 81 + j * 9 + k - 1;
					}
					Left[no + 1] = no + 4;
					Right[no + 4] = no + 1;
					Head[Row[no + 1]] = no + 1;
					insertNode(i * 9 + j + 1, no + 1);
					insertNode(81 + i * 9 + k, no + 2);
					insertNode(81 * 2 + j * 9 + k, no + 3);
					insertNode(81 * 3 + (i / 3 * 3 + j / 3) * 9 + k, no + 4);
					no += 4;
				}
			}
		}
	}
}

void SudokuSolver::insertNode(int c, int no){	// ��no��Ԫ����ӵ�c����
	/* ��Ԫ��c��Down[c]֮�����no */
	Up[Down[c]] = no;
	Down[no] = Down[c];
	Up[no] = c;
	Down[c] = no;
	Size[c]++;
	Col[no] = c;
}

void SudokuSolver::remove(int c){	// ���б�Ԫ���Ƴ����Ԫ��
	Left[Right[c]] = Left[c];
	Right[Left[c]] = Right[c];
	for (size_t i = Down[c]; i != c; i = Down[i]) {	// ����ɾ
		for (size_t j = Right[i]; j != i; j = Right[j]) {	// ����ɾ
			Up[Down[j]] = Up[j];
			Down[Up[j]] = Down[j];
			Size[Col[j]]--;
		}
	}
}

void SudokuSolver::restore(int c){	
	/* �ָ�c�б�Ԫ�� */
	Left[Right[c]] = Right[Left[c]] = c;
	/* �ָ�c�С�1��Ԫ������ͬ��Ԫ�� */
	for (size_t i = Up[c]; i != c; i = Up[i]){		// �ָ�˳�����Ƴ�˳���෴
		for (size_t j = Left[i]; j != i; j = Left[j]){	 
			Up[Down[j]] = Down[Up[j]] = j;
			Size[Col[j]]++;
		}
	}
}

bool SudokuSolver::dfs(int select){
	if (select > 81)	// ��ѡ��
		return true;
	int c, minnum = INT_MAX;
	/* �����б�Ԫ�أ�ѡһ��Ԫ�����ٵ��У������ʵͣ� */
	for (size_t i = Right[0]; i != 0; i = Right[i]) {	
		if (Size[i] == 0)
			return false;
		if (Size[i] < minnum){
			minnum = Size[i];
			c = i;
		}
	}
	remove(c);
	/* �������и���1��Ԫ�� */
	for (int i = Down[c]; i != c; i = Down[i]){
		int row = Row[i];
		table[row / 81][row % 81 / 9] = row % 9 + 1;	// ���ݸ�Ԫ�ص�����������
		for (size_t j = Right[i]; j != i; j = Right[j])	// �Ƴ����Ԫ��ͬ��Ԫ�ص���
			remove(Col[j]);
		if (dfs(select + 1))	// ��ѡ����+1���ݹ����
			return true;
		for (size_t j = Left[i]; j != i; j = Left[j])	// �ݹ鷵��false��˵�������޷����㣬�ʻָ����Ԫ��ͬ��Ԫ�ص��У�ѭ�����뱾����һԪ��
			restore(Col[j]);
	}
	restore(c);
	return false;
}






