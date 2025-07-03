#pragma once
#include <string>

class Member
{
public:
	Member();
	Member(std::string name, int age);

	~Member();

	const std::string getName() const;
	const int getAge() const;

private:
	const std::string m_name;
	const int m_age;
};

std::ostream& operator<<(std::ostream& os, const Member& m);


