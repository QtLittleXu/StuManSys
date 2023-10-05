#pragma once

#include <easyx.h>

// �����������
class Widget
{
public:
    Widget(int x = 0, int y = 0, int width = 100, int height = 60);
    void setRect(int x, int y, int width, int height);  // ���ÿؼ�����
    virtual void show() const = 0;                                                  // ��ʾ����
    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;
    void setX(int x);
    void setY(int y);
    void setWidth(int width);
    void setHeight(int height);

protected:
    int x;        // X ����
    int y;        // Y ����
    int width;    // ���
    int height;   // �߶�
};