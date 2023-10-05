#pragma once

#include <string>

// ѧ����
class Student
{
public:
	unsigned short id;		// ѧ��
	wchar_t name[10];		// ����
	wchar_t Class[10];		// �༶
	unsigned short score;	// �ܷ�

	// �����������ʹѧ��������Խ�������
	bool operator==(const wchar_t* searchTerms) const
	{
		return std::wstring(name) == searchTerms;
	}

	bool operator==(int id) const
	{
		return id == this->id;
	}

	bool operator<(const Student& stu) const	// ��ѧ����������
	{
		return (this->id < stu.id);
	}

	bool operator>(const Student& stu) const	// ���ܷ���������
	{
		return this->score > stu.score;
	}
};