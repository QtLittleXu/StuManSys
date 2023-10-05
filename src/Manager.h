#pragma once

#include "Student.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

// 管理器类
class Manager
{
public:
	bool read(const std::string& fileName);				// 读取文件到数据
	void write(const std::string& fileName) const;		// 写入数据到文件
	void addStudent(const Student& student);			// 添加学生
	void sortById();									// 按学号排序
	void sortByScore();									// 按总分排序
	const Student& getStudent(int index) const;			// 获取学生数据
	void setStudent(int index, const Student& student);	// 修改学生
	void deleteStudent(int index);						// 删除学生
	int size() const;									// 学生数量
	int search(const wchar_t* searchTerms) const;		// 按姓名搜索学生
	int search(int id) const;							// 按学号搜索学生
	void clear();										// 清空所有学生

protected:
	std::vector<Student> students;						// 学生数据
};