#include "Widget.h"

Widget::Widget(int x, int y, int width, int height) : x(x), y(y), width(width), height(height)
{
}

int Widget::getX() const
{
	// TODO: �ڴ˴����� return ���
	return x;
}

int Widget::getY() const
{
	// TODO: �ڴ˴����� return ���
	return y;
}

int Widget::getWidth() const
{
	// TODO: �ڴ˴����� return ���
	return width;
}

int Widget::getHeight() const
{
	// TODO: �ڴ˴����� return ���
	return height;
}

void Widget::setX(int x)
{
	this->x = x;
	show();
}

void Widget::setY(int y)
{
	this->y = y;
	show();
}

void Widget::setWidth(int width)
{
	this->width = width;
	show();
}

void Widget::setHeight(int height)
{
	this->height = height;
	show();
}

void Widget::setRect(int x, int y, int width, int height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	show();
}
