#pragma once

#include "Widget.h"
#include <string>

// ��ť��
class Button :
    public Widget
{
public:
    Button(int x = 0, int y = 0, int width = 100, int height = 60, const std::wstring& text = L"��ť");
    void show() const;                      // ��ʾ��ť
    bool state(const ExMessage& msg);       // ��ť״̬��true ��ʾ��ť����
    const std::wstring& getText() const;    // ��ȡ��ť�ı�
    void setText(const std::wstring& text); // ���ð�ť�ı�

protected:
    bool isIn(const ExMessage& msg) const;  // �ж�����Ƿ��ڰ�ť����
    std::wstring text;                      // ��ť�ı�
    bool isChange;                          // ��ť״̬�Ƿ�ı�
};

