#include "stdafx.h"
#include "FinalMaker.h"
#include "FileHandler.h"





string FianlMaker::make(int n){
	num = n;
	count = 0;
	seednum = 0;
	while (count < num) {
		makeSeed();
	}
	return out;
}

bool FianlMaker::toString(int table[][9]){
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			out += char(table[i][j] + '0');
			if (j != 8) {
				out += " ";
			}
		}
		out += "\n";
	}
	out += "\n";
	count++;
	return count < num ? true : false;
}

void FianlMaker::rowExchange(int table[][9], int r1, int r2){
	for (size_t i = 0; i < 9; i++){
		int temp;
		temp = table[i][r1];
		table[i][r1] = table[i][r2];
		table[i][r2] = temp;
	}
}

void FianlMaker::colExchange(int table[][9], int c1, int c2){
	for (size_t i = 0; i < 9; i++) {
		int temp;
		temp = table[c1][i];
		table[c1][i] = table[c2][i];
		table[c2][i] = temp;
	}
}

void FianlMaker::combina(int c1, int c2, int c3, int r1, int r2, int r3){
	int t[9][9];
	memcpy(t, table, sizeof(table));
	if (c1 == 1)
		colExchange(t, 1, 2);

	if(c2==1)
		colExchange(t, 4, 5);
	else if (c2 == 2)
		colExchange(t, 3, 4);
	else if (c2 == 3) {
		colExchange(t, 3, 4);
		colExchange(t, 4, 5);
	}
	else if (c2 == 4) {
		colExchange(t, 3, 5);
		colExchange(t, 4, 5);
	}
	else if (c2 == 5) 
		colExchange(t, 3, 5);

	if (c3 == 1)
		colExchange(t, 7, 8);
	else if (c3 == 2)
		colExchange(t, 6, 7);
	else if (c3 == 3) {
		colExchange(t, 6, 7);
		colExchange(t, 7, 8);
	}
	else if (c3 == 4) {
		colExchange(t, 6, 8);
		colExchange(t, 7, 8);
	}
	else if (c3 == 5)
		colExchange(t, 6, 8);

	if (r1 == 1)
		rowExchange(t, 1, 2);

	if (r2 == 1)
		rowExchange(t, 4, 5);
	else if (r2 == 2)
		rowExchange(t, 3, 4);
	else if (r2 == 3) {
		rowExchange(t, 3, 4);
		rowExchange(t, 4, 5);
	}
	else if (r2 == 4) {
		rowExchange(t, 3, 5);
		rowExchange(t, 4, 5);
	}
	else if (r2 == 5)
		rowExchange(t, 3, 5);

	if (r3 == 1)
		rowExchange(t, 7, 8);
	else if (r3 == 2)
		rowExchange(t, 6, 7);
	else if (r3 == 3) {
		rowExchange(t, 6, 7);
		rowExchange(t, 7, 8);
	}
	else if (r3 == 4) {
		rowExchange(t, 6, 8);
		rowExchange(t, 7, 8);
	}
	else if (r3 == 5)
		rowExchange(t, 6, 8);

	toString(t);
}

void FianlMaker::makeTable(int a[]) {
	table[0][4] = table[1][1] = table[2][7] = table[3][3] = table[4][0] = table[5][6] = table[6][5] = table[7][2] = table[8][8] = a[0];
	table[0][5] = table[1][2] = table[2][8] = table[3][4] = table[4][1] = table[5][7] = table[6][3] = table[7][0] = table[8][6] = a[1];
	table[0][3] = table[1][0] = table[2][6] = table[3][5] = table[4][2] = table[5][8] = table[6][4] = table[7][1] = table[8][7] = a[2];
	table[0][7] = table[1][4] = table[2][1] = table[3][6] = table[4][3] = table[5][0] = table[6][8] = table[7][5] = table[8][2] = a[3];
	table[0][8] = table[1][5] = table[2][2] = table[3][7] = table[4][4] = table[5][1] = table[6][6] = table[7][3] = table[8][0] = a[4];
	table[0][6] = table[1][3] = table[2][0] = table[3][8] = table[4][5] = table[5][2] = table[6][7] = table[7][4] = table[8][1] = a[5];
	table[0][1] = table[1][7] = table[2][4] = table[3][0] = table[4][6] = table[5][3] = table[6][2] = table[7][8] = table[8][5] = a[6];
	table[0][2] = table[1][8] = table[2][5] = table[3][1] = table[4][7] = table[5][4] = table[6][0] = table[7][6] = table[8][3] = a[7];
	table[0][0] = table[1][6] = table[2][3] = table[3][2] = table[4][8] = table[5][5] = table[6][1] = table[7][7] = table[8][4] = a[8];
	changeTable(table);
}

void FianlMaker::makeSeed(){
	int a[9] = { 1,2,3,4,5,6,7,8,9 };
	int tmp, x;
	int flag = 0;
	while (true){
		for (size_t i = 0; i < 8; i++) {	// ���x,��a[x]��a[i]����
			x = rand() % 8;
			tmp = a[x];
			a[x] = a[i];
			a[i] = tmp;
		}
		for (int i = 0; i < seednum; i++) {
			if ((a[6] == seeds[i][0] && a[7] == seeds[i][1]) || (a[6] == seeds[i][1] && a[7] == seeds[i][0]) ||
				(a[2] == seeds[i][2] && a[5] == seeds[i][3]) || (a[2] == seeds[i][3] && a[5] == seeds[i][2])) {
				flag = 1;
				break;
			}
		}
		if (flag==0)
			break;
	}
	seeds[seednum][0] = a[6];
	seeds[seednum][1] = a[7];
	seeds[seednum][2] = a[2];
	seeds[seednum][3] = a[5];
	seednum++;
	makeTable(a);
}

void FianlMaker::changeTable(int table[][9]){
	for (size_t c1 = 0; c1 < 2 && count<num; c1++)
		for (size_t c2 = 0; c2 < 6 && count<num; c2++)
			for (size_t c3 = 0; c3 < 6 && count<num; c3++)
				for (size_t r1 = 0; r1 < 2 && count<num; r1++)
					for (size_t r2 = 0; r2 < 6 && count<num; r2++)
						for (size_t r3 = 0; r3 < 6 && count<num; r3++)
							combina(c1, c2, c3, r1, r2, r3);
			
	
}
