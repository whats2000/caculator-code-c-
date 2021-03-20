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
			//cout << "大小 " << this->integer.size() << " 非空陣列" << endl;
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
		unsigned int res;
		result.positive = this->positive; //(正 加 正)或(負 加 負)
		bool isempty = true;			  //處理最終位進位去除多餘0，節省記憶體

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
			if (res != 0 && isempty) //檢測是否為0
				isempty = false;
			if (isempty != true)
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

	//減法
	Number operator-(Number& obj)
	{
		Number result;
		bool flag = false; //借位檢視
		int res;
		bool isempty = true; //處理最終位進位去除多餘0，節省記憶體

		//將等效加法轉移
		if (this->positive == true && obj.positive == false)
		{
			result = *this + obj;
			result.positive = true; //覆蓋正負
			return result;
		}
		else if (this->positive == false && obj.positive == true)
		{
			result = *this + obj;
			result.positive = false; //覆蓋正負
			return result;
		}

		// 等效 正 + 負 / 負 + 正 (判定大小決定positive)

		//小數補全
		while (this->decimal.size() != obj.decimal.size())
		{
			if (this->decimal.size() > obj.decimal.size())
				obj.decimal.insert(obj.decimal.begin(), '0');
			else
				this->decimal.insert(this->decimal.begin(), '0');
		}
		//數字比大小
		if (this->integer.size() > obj.integer.size())
		{
			cout << "整數位數檢測區分" << endl;
			goto bypass;
		}
		else if (this->integer.size() < obj.integer.size()) //第一層檢測 比整數位數
		{
			cout << "整數位數檢測區分" << endl; //數字長固定放前方
			this->integer.swap(obj.integer);
			this->decimal.swap(obj.decimal);
			swap(this->positive, obj.positive);

			goto bypass;
		}
		else //第二層如果位數一樣比整數部分
		{
			for (auto i = 0; i < this->integer.size(); i++)
			{
				if (this->integer[i] != obj.integer[i])
				{
					cout << "整數數字檢測區分" << endl;
					if ((this->integer[i] - '0') < (obj.integer[i])) //把較大數字擺前面
					{
						this->integer.swap(obj.integer);
						this->decimal.swap(obj.decimal);
						swap(this->positive, obj.positive);
					}
					goto bypass;
				}
			}
			//整數一樣檢測小數
			for (auto i = 0; i < this->decimal.size(); i++)
			{
				if (this->decimal[i] != obj.decimal[i])
				{
					cout << "小數數字檢測區分" << endl;
					if ((this->decimal[i] - '0') < (obj.decimal[i])) //把較大數字擺前面
					{
						this->decimal.swap(obj.decimal);
						swap(this->positive, obj.positive);
					}
					goto bypass;
				}
			}
		bypass: //檢測完成
			result.positive = this->positive;

			//小數處理
			for (auto i = 0; i < this->decimal.size(); i++)
			{
				res = (this->decimal[i] - '0') - (obj.decimal[i] - '0') - flag;
				if (res < 0)
				{
					res += 10;
					flag = true;
				}
				else
				{
					flag = false;
				}
				//cout << "res = " << res << " flag = " << flag << endl;
				if (res != 0 && isempty)
					isempty = false;
				if (!isempty)
				{
					result.decimal.push_back(res + '0');
				}
			}
			//整數處理
			for (auto i = 0; i < this->integer.size(); i++)
			{
				if (obj.integer[i] != 0)
					res = (this->integer[i] - '0') - (obj.integer[i] - '0') - flag;
				else
					res = (this->integer[i] - '0') - flag;
				if (res < 0)
				{
					res += 10;
					flag = true;
				}
				else
				{
					flag = false;
				}
				//cout << "res = " << res << " flag = " << flag << endl;

				result.integer.push_back(res + '0');
			}
			//清除整數多餘0
			for (vector<char>::reverse_iterator it = result.integer.rbegin(); it != result.integer.rend(); it++)
			{
				cout << "debug";
				if (*it == '0')
					result.integer.pop_back();
				else
					break;
			}

			//除錯用

			cout << "debug" << endl;
			Number a = *this;
			cout << "a = ";
			a.print_number();
			cout << "b = ";
			obj.print_number();

			//=====
			return result;
		}
	}
};