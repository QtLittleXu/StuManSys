#pragma once

#include <easyx.h>

// 部件抽象基类
class Widget
{
public:
    Widget(int x = 0, int y = 0, int width = 100, int height = 60);
    void setRect(int x, int y, int width, int height);  // 设置控件矩形
    virtual void show() const = 0;                                                  // 显示函数
    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;
    void setX(int x);
    void setY(int y);
    void setWidth(int width);
    void setHeight(int height);

protected:
    int x;        // X 坐标
    int y;        // Y 坐标
    int width;    // 宽度
    int height;   // 高度
};