#pragma once

#include <string>

// 学生类
class Student
{
public:
	unsigned short id;		// 学号
	wchar_t name[10];		// 姓名
	wchar_t Class[10];		// 班级
	unsigned short score;	// 总分

	// 重载运算符，使学生对象可以进行排序
	bool operator==(const wchar_t* searchTerms) const
	{
		return std::wstring(name) == searchTerms;
	}

	bool operator==(int id) const
	{
		return id == this->id;
	}

	bool operator<(const Student& stu) const	// 按学号升序排序
	{
		return (this->id < stu.id);
	}

	bool operator>(const Student& stu) const	// 按总分升序排序
	{
		return this->score > stu.score;
	}
};