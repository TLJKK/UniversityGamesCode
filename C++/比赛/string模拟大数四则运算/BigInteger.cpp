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

	if (isNotActive(left) != isNotActive(right))active = false;//���Ų�ͬ��Ϊ��

	if ('-' == left[0])left = left.substr(1);//��leftΪ��
	if ('-' == right[0])right = right.substr(1);//��rightΪ��

	if (left.size() < right.size())std::swap(left, right);//������ַ������ȸ��������ڶ�Ϊ�������Խ���������Ӱ��

	for (int i = right.size() - 1; i >= 0; i--)//�ұߵ�ÿһλ��������ߵ�ÿһλ��
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

		for (int j = 0; j < right.size() - 1 - i; j++)tmp += '0';//ȷ���Ǹ�λʮλ���߰�λ�ĳ˻�
		ret = add(ret, this->clearZero(tmp));//��ʽ�˷��еļӷ�����
	}

	return active ? ret : '-' + ret;
}

std::string BigInteger::sub(std::string left, std::string right)
{
	std::string ret = "";

	if (isNotActive(left) && isNotActive(right))//��Ϊ����
	{
		int active = true;//����߼�ȥ�ұߵ�����ߵĸ��������ұ߸������෴����������Ҵ���Ϊ������֮Ϊ��
		if (left.size() > right.size())active = false;
		else if (left.size() == right.size() && left > right)active = false;
		return active ? sub(right.substr(1), left.substr(1)) : '-' + sub(left.substr(1), right.substr(1));
	}
	else
	{

		if (isNotActive(left) && !isNotActive(right))return '-' + add(left.substr(1), right);//������
		else if (!isNotActive(left) && isNotActive(right))return add(left, right.substr(1));//�����Ҹ�
		else if (!isNotActive(left) && !isNotActive(right))//��Ϊ������ֱ������
		{
			int active = 1;
			if (left.size() < right.size())std::swap(left, right), active = false;
			if (left.size() == right.size() && left < right)std::swap(left, right), active = false;//����߱��ұߴ�

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
	if (!isNotActive(left) && !isNotActive(right))//ȫ�����㷵�ؽ��
	{
		int up = 0;
		if (left.size() < right.size())std::swap(left, right);//����ߵĳ��ȴ����ұߵ�
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
		if (!isNotActive(left) && isNotActive(right))return sub(left, right.substr(1));//�����Ҹ�ת����
		else if (isNotActive(left) && !isNotActive(right))return sub(right, left.substr(1));//������ת����
		else return '-' + add(left.substr(1), right.substr(1));//��Ϊ������ת�����෴���ļӷ�����������ŷ���
	}
}

