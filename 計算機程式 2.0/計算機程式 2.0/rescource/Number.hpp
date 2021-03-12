#include <iostream>
#include <math.h>
#include <string>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <cassert>
#define PI 3.141592653
//#define Pi 245850922 / 78256779
#define DegToRad PI / 180
using namespace std;

typedef vector<int> bigint; //運算用緩存

class Number
{
	friend class NumberOperator;

private:
	vector<char> integer; //整數
	vector<char> decimal; //小數
	bool positive = true; //正負

public:
	void set_number(string input)
	{
		bool isinteger = true;
		positive = true;

		//this->integer.assign(input.begin(),input.end());
		for (auto& character : input)
		{
			if (character == '-')
				this->positive = false;
			else if (isdigit(character))
				if (isinteger)
					this->integer.push_back(character);
				else
					this->decimal.push_back(character);
			else if (character == '.')
				isinteger = false;
			else
				break;
		}
		reverse(this->integer.begin(), this->integer.end());

		reverse(this->decimal.begin(), this->decimal.end());
	}

	//輸出陣列
	void print_number()
	{
		if (!this->positive)
			cout << "-";
		else
			cout << " ";

		if (this->integer.empty())
			cout << "0 . "; // 預設輸出
		else
		{
			cout << this->integer.back();
			for (auto it = this->integer.rbegin() + 1; it != this->integer.rend(); ++it)
			{
				cout << *it;
			}
			cout << " . ";
		}

		if (this->decimal.empty())
			cout << "0\n"; // 預設輸出
		else
		{
			cout << this->decimal.back();
			for (auto it = this->decimal.rbegin() + 1; it != this->decimal.rend(); ++it)
			{
				cout << *it;
			}
			cout << endl;
		}
	}

	//加減乘除

	//加法
	Number operator+(Number& obj)
	{
		Number result;
		bool flag = false; //進位檢視
		int res;
		result.positive = this->positive; //(正 加 正)或(負 加 負)
		bool isdecimalend = true;		  //處理最終位進位去除多餘0，節省記憶體

		if (this->decimal.size() < obj.decimal.size())
			this->decimal.swap(obj.decimal);
		//缺項補0
		while (this->decimal.size() != obj.decimal.size())
		{
			obj.decimal.insert(obj.decimal.begin(), '0');
		}
		for (auto i = 0; i < this->decimal.size(); i++)
		{
			//cout << this->decimal[i] << " + " << obj.decimal[i] << " = " << endl;
			res = (this->decimal[i] - '0') + (obj.decimal[i] - '0') + flag;
			//cout << res << endl;
			if (res >= 10)
			{
				res %= 10;
				flag = true;
			}
			else
			{
				flag = false;
			}
			if (res != 0) //檢測是否為0
				isdecimalend = false;
			if (isdecimalend != true)
				result.decimal.push_back(res + '0');
		}

		//整數部份
		if (this->integer.size() < obj.integer.size())
			this->integer.swap(obj.integer);
		//缺項補0
		while (this->integer.size() != obj.integer.size())
		{
			obj.integer.insert(obj.integer.begin(), '0');
		}
		for (auto i = 0; i < this->integer.size(); i++)
		{
			//cout << this->integer[i] << " + " << obj.integer[i] << " = " << endl;
			res = (this->integer[i] - '0') + (obj.integer[i] - '0') + flag;
			//cout << res << endl;
			if (res >= 10)
			{
				res %= 10;
				flag = true;
			}
			else
			{
				flag = false;
			}
			result.integer.push_back(res + '0');
			//如果多一位數補上
			if (i == this->integer.size() - 1 && flag == true)
				result.integer.push_back('1');
		}
		return result;
	}
};