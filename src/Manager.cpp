#include "Manager.h"

bool Manager::read(const std::string& fileName)
{
    // 以二进制读取模式打开文件
    std::ifstream file(fileName, std::ios::in | std::ios::binary);
    if (!file)
    {
        return false;
    }

    // 读取数据
    Student data = {};
    while (file.read((char*)&data, sizeof(Student)))
    {
        students.push_back(data);
    }

    file.close();
    return true;
}

void Manager::write(const std::string& fileName) const
{
    // 以二进制写入模式打开文件
    std::ofstream file(fileName, std::ios::out | std::ios::binary);

    // 写入数据
    for (int i = 0; i < students.size(); i++)
    {
        file.write((const char*)&students[i], sizeof(Student));
    }

    file.close();
}

void Manager::addStudent(const Student& student)
{
    students.push_back(student);
}

void Manager::sortById()
{
    std::sort(students.begin(), students.end());
}

void Manager::sortByScore()
{
    std::sort(students.begin(), students.end(), std::greater<Student>());
}

const Student& Manager::getStudent(int index) const
{
    // TODO: 在此处插入 return 语句
    return students[index];
}

void Manager::setStudent(int index, const Student& student)
{
    students[index] = student;
}

void Manager::deleteStudent(int index)
{
    students.erase(students.begin() + index);
}

int Manager::size() const
{
    // TODO: 在此处插入 return 语句
    return (int)students.size();
}

int Manager::search(const wchar_t* searchTerms) const
{
    // TODO: 在此处插入 return 语句
    std::vector<Student>::const_iterator iter;
    iter = std::find(students.begin(), students.end(), searchTerms);
    if (iter != students.end())
    {
        // 搜索成功，返回索引
        return (int)(iter - students.begin());
    }
    else
    {
        // 搜索失败，返回 -1 表示错误
        return -1;
    }
}

int Manager::search(int id) const
{
    std::vector<Student>::const_iterator iter;
    iter = std::find(students.begin(), students.end(), id);
    if (iter != students.end())
    {
        // 搜索成功，返回索引
        return (int)(iter - students.begin());
    }
    else
    {
        // 搜索失败，返回 -1 表示错误
        return -1;
    }
}

void Manager::clear()
{
    students.clear();
}
