#include "Table.h"

Table::Table(const Manager& manager, int x, int y, int width, int height) : Widget(x, y, width, height), manager(manager)
{
	curIndex = 0;
	searchIndex = -1;
}

void Table::show() const
{
	// 设置绘图样式
	setfillcolor(WHITE);

	// 绘制表格
	fillrectangle(x, y, x + width, y + height);
	
	// 画竖线
	for (int i = 130; i <= 370; i += 120)
	{
		line(i, 10, i, 10 + 360);
	}

	// 画横线
	for (int j = 40; j <= 340; j += 30)
	{
		line(10, j, 10 + 482, j);
	}

	RECT rect;

	// 绘制表头
	wchar_t header[4][3] = { L"学号", L"姓名", L"班级", L"总分" };	// 表头数据
	for (int i = 10, j = 0; i < 490 && j < 4; i += 120, j++)
	{
		rect = { i, 10, i + 120, 10 + 30 };
		drawtext(header[j], &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}

	// 输出学生数据
	int i = curIndex;
	wchar_t buffer[5];
	for (int j = 40; j < 370; j += 30)
	{
		if (i < manager.size())	// 在不超出索引范围的情况下才读取数据
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
	// 绘制页数提示
	std::wstringstream format;
	setbkmode(OPAQUE);
	format << L"第" << (curIndex + 11) / 11 << L"页" << L"/" << L"共" << (manager.size() + 11) / 11 << L"页";
	outtextxy(98, 380, format.str().c_str());
	setbkmode(TRANSPARENT);
}

void Table::pageUp()
{
	// 输出学生数据
	curIndex -= 11;
	if (curIndex < 0)	// 读取到第一页停止操作
	{
		curIndex += 11;
		return;
	}
	show();
}

void Table::pageDown()
{
	// 输出学生数据
	curIndex += 11;
	if (curIndex > manager.size())	// 读取到最后一页停止操作
	{
		curIndex -= 11;
		return;
	}
	show();
}

void Table::showEditTable(const wchar_t* searchTerms)
{
	// 搜索
	int index = manager.search(searchTerms);

	// 搜索成功才进行打印操作
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
	// 设置绘图样式
	setfillcolor(WHITE);

	// 绘制表格
	fillrectangle(x, y, x + width, y + 60);

	// 画竖线
	for (int i = 130; i <= 370; i += 120)
	{
		line(i, 10, i, 10 + 60);
	}

	// 画横线
	line(10, 40, 490, 40);

	RECT rect;

	// 绘制表头
	wchar_t header[4][3] = { L"学号", L"姓名", L"班级", L"总分" };	// 表头数据
	for (int i = 10, j = 0; i < 490 && j < 4; i += 120, j++)
	{
		rect = { i, 10, i + 120, 10 + 30 };
		drawtext(header[j], &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}

	// 输出学生数据
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
	// TODO: 在此处插入 return 语句
	return searchIndex;
}

void Table::setSearchIndex(int index)
{
	searchIndex = index;
}
