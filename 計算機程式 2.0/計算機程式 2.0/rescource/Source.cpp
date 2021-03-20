#include <iostream>
#include <math.h>
#include <string>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <cassert>
#include "OperatorNumber.hpp"
#define PI 3.141592653
//#define Pi 245850922 / 78256779
#define DegToRad PI / 180
using namespace std;

typedef vector<int> bigint; //運算用緩存

int main(int argc, char* argv[])
{
	//Number ans;
	//	OperaterNumber userInput;
	//	ans = userInput.eval_input();
	//	ans.print_number();

	//測試加減 (兩者符號必須一致)
	Number a, b, c;
	string a0, b0;
	char numcase;
	long double a1 = 0, b1 = 0 , c1 = 0;
	cout << "輸入a = ";
	cin >> a0;
	cout << "輸入b = ";
	cin >> b0;
	cout << "輸入運算 = ";
	cin >> numcase;
	a.set_number(a0);
	b.set_number(b0);
	try {
		a1 = strtold(a0.c_str(), 0);
		b1 = strtold(b0.c_str(), 0);
		if (!double(a1))
			throw 1;
		if (!double(b1))
			throw 2;
	}
	catch (int x) {
		cout << "意料外錯誤 錯誤編號" << x;
	}
	switch (numcase)
	{
	case '+':
		c = a + b;
		c1 = a1 + b1;
		break;
	case '-':
		c = a - b;
		c1 = a1 - b1;
		break;
	default:
		break;
	}
	cout << "   ";
	a.print_number();
	cout << " "<< numcase <<")";
	b.print_number();
	for (int i = 0; i < 60; i++)
		cout << "—";
	cout << endl;
	cout << " = ";
	c.print_number();
	
	cout << "內建double卻變成了" << setprecision(1000) << c1;
}