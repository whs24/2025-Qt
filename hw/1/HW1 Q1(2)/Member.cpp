#include "Member.h"
#include <iostream>
#include <string>

Member::Member(): m_name("?"), m_age(0) // Ĭ��ѧ����Ϣ
{
}

Member::Member(std::string name, int age): m_name(name), m_age(age)
{
}

Member::~Member()
{
}

const std::string Member::getName() const
{
	return m_name;
}

const int Member::getAge() const
{
	return m_age;
}

std::ostream& operator<<(std::ostream& os, const Member& m)
{
	os << "Name: " << m.getName() << ", Age: " << m.getAge();  // ͨ���ӿڷ���˽�г�Ա
	return os;
}