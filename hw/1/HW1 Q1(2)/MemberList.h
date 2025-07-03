#pragma once
#include "Member.h"
#include <string>

class MemberList
{
public:
	MemberList();
	MemberList(Member* members, int size);

	std::string operator[](const std::string& name) const;

	~MemberList();

private:
	Member* m_members;
	int m_size;
};

