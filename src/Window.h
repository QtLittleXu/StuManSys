#pragma once

#include "Widget.h"
#include "Button.h"
#include "Manager.h"
#include "Table.h"
#include <iostream>
#include <algorithm>

constexpr auto BACKGROUND_IMAGE = L"./background.jpg";    // ����ͼƬ��
constexpr auto DATA_FILE = "./Students.dat";              // �����ļ�

class Window :
    public Widget
{
public:
    Window(int width = 600, int height = 400);
    ~Window();

    void show() const;                          // ��ʾ����
    void messageLoop();                         // ��Ϣѭ��
    bool close();                               // �رմ���

private:
    void showMainWindow();                      // ��ʾ������
    void showViewStudents();                    // ��ʾ�鿴ѧ������
    void showEditStudents();                    // ��ʾ�༭ѧ������
    bool isNumber(const std::wstring& string);  // �ж��ܷ�Ϊ����

public:
    // ����״̬��ʶ��ÿ��״̬������һ������
    enum class WindowState
    {
        mainWindow,     // ������
        viewStudents,   // �鿴ѧ��
        editStudents    // �༭ѧ��
    };

private:
    // �����ڰ�ť
    Button* mainWindow_view;
    Button* mainWindow_edit;
    Button* mainWindow_exit;
    Button* mainWindow_clear;

    // �鿴ѧ�����ڰ�ť
    Button* viewStudents_pageUp;
    Button* viewStudents_pageDown;
    Button* viewStudents_back;
    Button* viewStudents_sort;

    // �༭ѧ�����ڰ�ť
    Button* editStudents_add;
    Button* editStudents_delete;
    Button* editStudents_back;
    Button* editStudents_search;

    WindowState state;  // ����״̬
    Table* table;       // ѧ�����ݱ��
    Manager manager;    // ������
    HWND hWnd;          // ���ھ��
    bool isEdit;        // �Ƿ�༭ѧ��
};

