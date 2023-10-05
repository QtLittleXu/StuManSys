#pragma once

#include "Widget.h"
#include "Button.h"
#include "Manager.h"
#include "Table.h"
#include <iostream>
#include <algorithm>

constexpr auto BACKGROUND_IMAGE = L"./background.jpg";    // 背景图片名
constexpr auto DATA_FILE = "./Students.dat";              // 数据文件

class Window :
    public Widget
{
public:
    Window(int width = 600, int height = 400);
    ~Window();

    void show() const;                          // 显示窗口
    void messageLoop();                         // 消息循环
    bool close();                               // 关闭窗口

private:
    void showMainWindow();                      // 显示主窗口
    void showViewStudents();                    // 显示查看学生窗口
    void showEditStudents();                    // 显示编辑学生窗口
    bool isNumber(const std::wstring& string);  // 判断受否为数字

public:
    // 窗口状态标识，每个状态代表了一个界面
    enum class WindowState
    {
        mainWindow,     // 主窗口
        viewStudents,   // 查看学生
        editStudents    // 编辑学生
    };

private:
    // 主窗口按钮
    Button* mainWindow_view;
    Button* mainWindow_edit;
    Button* mainWindow_exit;
    Button* mainWindow_clear;

    // 查看学生窗口按钮
    Button* viewStudents_pageUp;
    Button* viewStudents_pageDown;
    Button* viewStudents_back;
    Button* viewStudents_sort;

    // 编辑学生窗口按钮
    Button* editStudents_add;
    Button* editStudents_delete;
    Button* editStudents_back;
    Button* editStudents_search;

    WindowState state;  // 窗口状态
    Table* table;       // 学生数据表格
    Manager manager;    // 管理器
    HWND hWnd;          // 窗口句柄
    bool isEdit;        // 是否编辑学生
};

