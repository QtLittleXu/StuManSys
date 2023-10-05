#include "Manager.h"

bool Manager::read(const std::string& fileName)
{
    // �Զ����ƶ�ȡģʽ���ļ�
    std::ifstream file(fileName, std::ios::in | std::ios::binary);
    if (!file)
    {
        return false;
    }

    // ��ȡ����
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
    // �Զ�����д��ģʽ���ļ�
    std::ofstream file(fileName, std::ios::out | std::ios::binary);

    // д������
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
    // TODO: �ڴ˴����� return ���
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
    // TODO: �ڴ˴����� return ���
    return (int)students.size();
}

int Manager::search(const wchar_t* searchTerms) const
{
    // TODO: �ڴ˴����� return ���
    std::vector<Student>::const_iterator iter;
    iter = std::find(students.begin(), students.end(), searchTerms);
    if (iter != students.end())
    {
        // �����ɹ�����������
        return (int)(iter - students.begin());
    }
    else
    {
        // ����ʧ�ܣ����� -1 ��ʾ����
        return -1;
    }
}

int Manager::search(int id) const
{
    std::vector<Student>::const_iterator iter;
    iter = std::find(students.begin(), students.end(), id);
    if (iter != students.end())
    {
        // �����ɹ�����������
        return (int)(iter - students.begin());
    }
    else
    {
        // ����ʧ�ܣ����� -1 ��ʾ����
        return -1;
    }
}

void Manager::clear()
{
    students.clear();
}
