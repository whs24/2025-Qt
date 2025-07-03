#include "MemberList.h"
#include <iostream>

MemberList::MemberList(): m_members(nullptr), m_size(0) //默认初始化
{
}

MemberList::MemberList(Member* members, int size) : m_members(members), m_size(size)
{
}

std::string MemberList::operator[](const std::string& name) const {
	for (int i = 0; i < m_size; i++) {
		if (m_members[i].getName() == name) {
			return "The age of " + m_members[i].getName()
				+ " is " + std::to_string(m_members[i].getAge()); //输出年龄信息
		}
	}
	return "Student " + name + " is not found"; //异常处理
}

MemberList::~MemberList() 
{
}