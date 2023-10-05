#include "Button.h"

Button::Button(int x, int y, int width, int height, const std::wstring& text) : Widget(x, y, width, height), text(text), isChange(false)
{
}

void Button::show() const
{
	// ������ʽ
	setlinestyle(PS_SOLID, 2);
	setfillcolor(CYAN);
	settextstyle(25, 0, L"΢���ź�");

	// ���ư�ť
	fillrectangle(x, y, x + width, y + height);

	// �����ı�
	RECT rect = { x, y, x + width, y + height };
	drawtext(text.c_str(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

bool Button::state(const ExMessage& msg) 
{
	if (msg.message == WM_MOUSEMOVE && isIn(msg))	// ��ť����
	{
		// ������ʽ
		setlinestyle(PS_SOLID, 2);
		setfillcolor(LIGHTBLUE);
		settextstyle(25, 0, L"΢���ź�");

		// ���ư�ť
		fillrectangle(x, y, x + width, y + height);

		// �����ı�
		RECT rect = { x, y, x + width, y + height };
		drawtext(text.c_str(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		isChange = true;
		return false;
	}
	else if ((msg.message == WM_LBUTTONDOWN || msg.message == WM_LBUTTONUP) && isIn(msg))	// ��ť�����
	{
		// ������ʽ
		setlinestyle(PS_SOLID, 2);
		setfillcolor(LIGHTBLUE);
		settextstyle(25, 0, L"΢���ź�");

		// ���ư�ť
		fillrectangle(x, y, x + width, y + height);

		// �����ı�
		RECT rect = { x, y, x + width, y + height };
		drawtext(text.c_str(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		isChange = true;
		return true;
	}
	else	// �ڰ�ť״̬�ı��ʱ�򣬻ָ���ťԭ����״̬����ֹ����
	{
		if (isChange)
		{
			show();
			isChange = false;
		}
		return false;
	}
}

const std::wstring& Button::getText() const
{
	// TODO: �ڴ˴����� return ���
	return text;
}

void Button::setText(const std::wstring& text)
{
	this->text = text;
}

bool Button::isIn(const ExMessage& msg) const
{
	if (msg.x >= this->x && msg.x <= this->x + width && msg.y >= this->y && msg.y <= this->y + height)
	{
		return true;
	}
	return false;
}
