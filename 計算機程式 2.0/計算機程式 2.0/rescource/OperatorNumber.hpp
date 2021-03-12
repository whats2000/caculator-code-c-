#include <iostream>
#include <math.h>
#include <string>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <cassert>
#include "Number.hpp"

class OperaterNumber : public Number
{
public:
	//評估輸入
	Number eval_input()
	{
		Number result;
		string input;

		cin >> input;

		result.set_number(input);

		return result;
	}

protected:
};