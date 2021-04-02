#include "BigInteger.h"


bool BigInteger::isNotActive(std::string now) { return now.size() ? '-' == now[0] : false; }

std::string BigInteger::clearZero(std::string now)
{
	int idx = 0;
	while (idx < now.size() && '0' == now[idx])idx++;
	return idx == now.size() ? "0" : now.substr(idx);
}

std::string BigInteger::mul(std::string left, std::string right)
{
	std::string ret = "0";
	int active = 1;

	if (isNotActive(left) != isNotActive(right))active = false;//符号不同，为负

	if ('-' == left[0])left = left.substr(1);//令left为正
	if ('-' == right[0])right = right.substr(1);//令right为正

	if (left.size() < right.size())std::swap(left, right);//令左边字符串长度更长，由于都为正，所以交换后结果无影响

	for (int i = right.size() - 1; i >= 0; i--)//右边的每一位数乘以左边的每一位数
	{
		std::string tmp = "";
		int up = 0, mulNum = right[i] - '0';

		for (int j = left.size() - 1; j >= 0; j--)
		{
			up += mulNum * (left[j] - '0');
			tmp = (char)(up % 10 + '0') + tmp;
			up /= 10;
		}

		while (up)
		{
			tmp = (char)(up % 10 + '0') + tmp;
			up /= 10;
		}

		for (int j = 0; j < right.size() - 1 - i; j++)tmp += '0';//确定是个位十位或者百位的乘积
		ret = add(ret, this->clearZero(tmp));//竖式乘法中的加法运算
	}

	return active ? ret : '-' + ret;
}

std::string BigInteger::sub(std::string left, std::string right)
{
	std::string ret = "";

	if (isNotActive(left) && isNotActive(right))//都为负数
	{
		int active = true;//对左边减去右边等于左边的负数加上右边负数的相反数，若左比右大则为负，反之为正
		if (left.size() > right.size())active = false;
		else if (left.size() == right.size() && left > right)active = false;
		return active ? sub(right.substr(1), left.substr(1)) : '-' + sub(left.substr(1), right.substr(1));
	}
	else
	{

		if (isNotActive(left) && !isNotActive(right))return '-' + add(left.substr(1), right);//左负右正
		else if (!isNotActive(left) && isNotActive(right))return add(left, right.substr(1));//左正右负
		else if (!isNotActive(left) && !isNotActive(right))//都为正可以直接运算
		{
			int active = 1;
			if (left.size() < right.size())std::swap(left, right), active = false;
			if (left.size() == right.size() && left < right)std::swap(left, right), active = false;//令左边比右边大

			int lenNow = left.size() - right.size();
			while (lenNow--)right = '0' + right;

			int up = 0;

			for (int i = right.size() - 1; i >= 0; i--)
				if (left[i] < right[i] + up) ret = (char)(left[i] + 10 - up - right[i] + '0') + ret, up = 1;
				else ret = (char)(left[i] - right[i] - up + '0') + ret, up = 0;

			ret = this->clearZero(ret);
			return active ? ret : '-' + ret;
		}
	}

}

std::string BigInteger::add(std::string left, std::string right)
{
	std::string ret;
	if (!isNotActive(left) && !isNotActive(right))//全正计算返回结果
	{
		int up = 0;
		if (left.size() < right.size())std::swap(left, right);//令左边的长度大于右边的
		int lenNow = left.size() - right.size();
		while (lenNow--)right = '0' + right;

		for (int i = right.size() - 1; i >= 0; i--)
		{
			up += right[i] + left[i] - '0' - '0';
			ret = (char)(up % 10 + '0') + ret;
			up /= 10;
		}

		while (up)
		{
			ret = (char)(up % 10 + '0') + ret;
			up /= 10;
		}

		return ret;

	}
	else
	{
		if (!isNotActive(left) && isNotActive(right))return sub(left, right.substr(1));//左正右负转减法
		else if (isNotActive(left) && !isNotActive(right))return sub(right, left.substr(1));//左负右正转减法
		else return '-' + add(left.substr(1), right.substr(1));//都为负，则转它们相反数的加法，结果带符号返回
	}
}

