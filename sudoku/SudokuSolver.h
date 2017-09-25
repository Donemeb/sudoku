#pragma once

#include "stdafx.h"

using namespace std;

const int maxrow = 9 * 9 * 9;
const int maxcol = 1 + 9 * 9 * 4;
const int num = maxcol + maxrow * 4;	// ��Ԫ�ظ���,  ��һ��ΪHeadԪ��,����9*9*4��Ϊ�б�Ԫ��,���9*9*9*4��Ϊ��1��Ԫ��

class SudokuSolver {
public:
	char* solve(char ch[]);

private:
	int Left[num], Right[num], Up[num], Down[num];	// ÿ��Ԫ�ص�4������������൱�������еļ�ͷ��
	int Col[num];		// ��¼ÿ��Ԫ�ص��б�Ԫ��
	int Row[num];		// ��¼ÿ��Ԫ�����ڵ�01��������
	int Size[maxcol];	// ��¼ÿ�еġ�1��Ԫ�ظ���
	int Head[maxrow];	// ��¼ÿ�е�һ����1��Ԫ��
	int table[9][9];	// ����
	int no;				// Ԫ�ر��
	void transform(int table[][9], char ch[]);
	void link();
	void insertNode(int col, int no);
	void remove(int col);
	void restore(int col);
	bool dfs(int k);
};
