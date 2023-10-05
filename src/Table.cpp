#include "Table.h"

Table::Table(const Manager& manager, int x, int y, int width, int height) : Widget(x, y, width, height), manager(manager)
{
	curIndex = 0;
	searchIndex = -1;
}

void Table::show() const
{
	// ���û�ͼ��ʽ
	setfillcolor(WHITE);

	// ���Ʊ��
	fillrectangle(x, y, x + width, y + height);
	
	// ������
	for (int i = 130; i <= 370; i += 120)
	{
		line(i, 10, i, 10 + 360);
	}

	// ������
	for (int j = 40; j <= 340; j += 30)
	{
		line(10, j, 10 + 482, j);
	}

	RECT rect;

	// ���Ʊ�ͷ
	wchar_t header[4][3] = { L"ѧ��", L"����", L"�༶", L"�ܷ�" };	// ��ͷ����
	for (int i = 10, j = 0; i < 490 && j < 4; i += 120, j++)
	{
		rect = { i, 10, i + 120, 10 + 30 };
		drawtext(header[j], &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}

	// ���ѧ������
	int i = curIndex;
	wchar_t buffer[5];
	for (int j = 40; j < 370; j += 30)
	{
		if (i < manager.size())	// �ڲ�����������Χ������²Ŷ�ȡ����
		{
			rect = { 10, j, 10 + 120, j + 30 };
			_itow_s(manager.getStudent(i).id, buffer, 10);
			drawtext(buffer, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			rect = { 130, j, 130 + 120, j + 30 };
			drawtext(manager.getStudent(i).name, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			rect = { 250, j, 250 + 120, j + 30 };
			drawtext(manager.getStudent(i).Class, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			rect = { 370, j, 370 + 120, j + 30 };
			_itow_s(manager.getStudent(i).score, buffer, 10);
			drawtext(buffer, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			i++;
		}
		else
		{
			break;
		}
	}
	// ����ҳ����ʾ
	std::wstringstream format;
	setbkmode(OPAQUE);
	format << L"��" << (curIndex + 11) / 11 << L"ҳ" << L"/" << L"��" << (manager.size() + 11) / 11 << L"ҳ";
	outtextxy(98, 380, format.str().c_str());
	setbkmode(TRANSPARENT);
}

void Table::pageUp()
{
	// ���ѧ������
	curIndex -= 11;
	if (curIndex < 0)	// ��ȡ����һҳֹͣ����
	{
		curIndex += 11;
		return;
	}
	show();
}

void Table::pageDown()
{
	// ���ѧ������
	curIndex += 11;
	if (curIndex > manager.size())	// ��ȡ�����һҳֹͣ����
	{
		curIndex -= 11;
		return;
	}
	show();
}

void Table::showEditTable(const wchar_t* searchTerms)
{
	// ����
	int index = manager.search(searchTerms);

	// �����ɹ��Ž��д�ӡ����
	if (index != -1)
	{
		showTable(index);

		searchIndex = index;
	}
	else
	{
		searchIndex = -1;
	}
}

void Table::showEditTable(int id)
{
	int index = manager.search(id);
	
	if (index != -1)
	{
		showTable(index);

		searchIndex = index;
	}
	else
	{
		searchIndex = index;
	}
}

void Table::showTable(int index)
{
	// ���û�ͼ��ʽ
	setfillcolor(WHITE);

	// ���Ʊ��
	fillrectangle(x, y, x + width, y + 60);

	// ������
	for (int i = 130; i <= 370; i += 120)
	{
		line(i, 10, i, 10 + 60);
	}

	// ������
	line(10, 40, 490, 40);

	RECT rect;

	// ���Ʊ�ͷ
	wchar_t header[4][3] = { L"ѧ��", L"����", L"�༶", L"�ܷ�" };	// ��ͷ����
	for (int i = 10, j = 0; i < 490 && j < 4; i += 120, j++)
	{
		rect = { i, 10, i + 120, 10 + 30 };
		drawtext(header[j], &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}

	// ���ѧ������
	wchar_t buffer[10];
	rect = { 10, 40, 10 + 120, 70 };
	_itow_s(manager.getStudent(index).id, buffer, 10);
	drawtext(buffer, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	rect = { 130, 40, 130 + 120, 70 };
	drawtext(manager.getStudent(index).name, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	rect = { 250, 40, 250 + 120, 70 };
	drawtext(manager.getStudent(index).Class, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	rect = { 370, 40, 370 + 120, 70 };
	_itow_s(manager.getStudent(index).score, buffer, 10);
	drawtext(buffer, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

int Table::getSearchIndex() const
{
	// TODO: �ڴ˴����� return ���
	return searchIndex;
}

void Table::setSearchIndex(int index)
{
	searchIndex = index;
}
