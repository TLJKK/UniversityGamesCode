#pragma once
#include<string>

class BigInteger
{
public:

	BigInteger() { ; }
	~BigInteger() { ; }

	bool isNotActive(std::string now);//判断字符串是否为负

	std::string clearZero(std::string now);//清除当前string的前导零

	std::string mul(std::string left, std::string right);//乘法左参与右参

	std::string sub(std::string left, std::string right);//减法左参与右参

	std::string add(std::string left, std::string right);//加法左参与右参

};