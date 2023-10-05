#pragma once

#include "Widget.h"
#include <string>

// 按钮类
class Button :
    public Widget
{
public:
    Button(int x = 0, int y = 0, int width = 100, int height = 60, const std::wstring& text = L"按钮");
    void show() const;                      // 显示按钮
    bool state(const ExMessage& msg);       // 按钮状态，true 表示按钮按下
    const std::wstring& getText() const;    // 获取按钮文本
    void setText(const std::wstring& text); // 设置按钮文本

protected:
    bool isIn(const ExMessage& msg) const;  // 判断鼠标是否在按钮里面
    std::wstring text;                      // 按钮文本
    bool isChange;                          // 按钮状态是否改变
};

