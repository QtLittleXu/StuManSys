#pragma once

#include "Widget.h"
#include "Manager.h"
#include <sstream>

// 表格类
class Table :
    public Widget
{
public:
    Table(const Manager& manager, int x = 0, int y = 0, int width = 100, int height = 60);
    void show() const;                              // 显示表格
    void pageUp();                                  // 上一页
    void pageDown();                                // 下一页
    void showEditTable(const wchar_t* searchTerms); // 显示编辑表格（字符串搜索）
    void showEditTable(int id);						// 显示编辑表格（学号搜索）
    void showTable(int index);                      // 显示编辑表格（下标索引）
    int getSearchIndex() const;                     // 获取搜索索引
    void setSearchIndex(int index);                 // 设置学生索引

private:
    int curIndex;                                   // 当前学生索引
    int searchIndex;                                // 搜索索引
    const Manager& manager;                         // 管理器引用
};

