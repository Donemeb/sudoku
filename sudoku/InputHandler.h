#pragma once

#include "stdafx.h"

using namespace std;

class InputHandler {
public:
	int check(int argc, char **argv);

private:
	int isNum(const string &str);
	int isPath(const string &str);
};
