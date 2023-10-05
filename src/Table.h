#pragma once

#include "Widget.h"
#include "Manager.h"
#include <sstream>

// �����
class Table :
    public Widget
{
public:
    Table(const Manager& manager, int x = 0, int y = 0, int width = 100, int height = 60);
    void show() const;                              // ��ʾ���
    void pageUp();                                  // ��һҳ
    void pageDown();                                // ��һҳ
    void showEditTable(const wchar_t* searchTerms); // ��ʾ�༭����ַ���������
    void showEditTable(int id);						// ��ʾ�༭���ѧ��������
    void showTable(int index);                      // ��ʾ�༭����±�������
    int getSearchIndex() const;                     // ��ȡ��������
    void setSearchIndex(int index);                 // ����ѧ������

private:
    int curIndex;                                   // ��ǰѧ������
    int searchIndex;                                // ��������
    const Manager& manager;                         // ����������
};

