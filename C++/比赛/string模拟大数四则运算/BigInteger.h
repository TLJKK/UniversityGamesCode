#pragma once
#include<string>

class BigInteger
{
public:

	BigInteger() { ; }
	~BigInteger() { ; }

	bool isNotActive(std::string now);//�ж��ַ����Ƿ�Ϊ��

	std::string clearZero(std::string now);//�����ǰstring��ǰ����

	std::string mul(std::string left, std::string right);//�˷�������Ҳ�

	std::string sub(std::string left, std::string right);//����������Ҳ�

	std::string add(std::string left, std::string right);//�ӷ�������Ҳ�

};