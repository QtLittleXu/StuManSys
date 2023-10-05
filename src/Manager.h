#pragma once

#include "Student.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

// ��������
class Manager
{
public:
	bool read(const std::string& fileName);				// ��ȡ�ļ�������
	void write(const std::string& fileName) const;		// д�����ݵ��ļ�
	void addStudent(const Student& student);			// ���ѧ��
	void sortById();									// ��ѧ������
	void sortByScore();									// ���ܷ�����
	const Student& getStudent(int index) const;			// ��ȡѧ������
	void setStudent(int index, const Student& student);	// �޸�ѧ��
	void deleteStudent(int index);						// ɾ��ѧ��
	int size() const;									// ѧ������
	int search(const wchar_t* searchTerms) const;		// ����������ѧ��
	int search(int id) const;							// ��ѧ������ѧ��
	void clear();										// �������ѧ��

protected:
	std::vector<Student> students;						// ѧ������
};