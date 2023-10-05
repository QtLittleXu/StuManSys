#include "Window.h"

Window::Window(int width, int height) :
	Widget(0, 0, width, height),
	isEdit(false),
	hWnd(initgraph(width, height, EX_NOCLOSE))
{
	SetWindowText(hWnd, L"学生成绩管理系统");
	setbkcolor(WHITE);
	cleardevice();
	ShowWindow(hWnd, SW_HIDE);

	// 设置绘图样式
	LOGFONT f;
	gettextstyle(&f);
	f.lfQuality = DEFAULT_QUALITY;
	settextstyle(&f);
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	setlinecolor(BLACK);

	// 创建按钮
	mainWindow_view	 = new Button((502 - 150) / 2, 160, 150, 40, L"查看学生");
	mainWindow_edit = new Button((502 - 150) / 2, 220, 150, 40, L"编辑学生");
	mainWindow_clear = new Button((502 - 150) / 2, 280, 150, 40, L"清空数据");
	mainWindow_exit = new Button((502 - 150) / 2, 340, 150, 40, L"退出程序");

	viewStudents_pageUp = new Button(10, 380, 80, 30, L"上一页");
	viewStudents_pageDown = new Button(210, 380, 80, 30, L"下一页");
	viewStudents_back = new Button(412, 380, 80, 30, L"返回");
	viewStudents_sort = new Button(300, 380, 102, 30, L"按总分排序");

	editStudents_search = new Button(10, 380, 100, 30, L"搜索学生");
	editStudents_add = new Button(137, 380, 100, 30, L"添加学生");
	editStudents_delete = new Button(264, 380, 100, 30, L"删除学生");
	editStudents_back = new Button(392, 380, 100, 30, L"返回");

	showMainWindow();	// 显示主界面

	// 创建表格
	table = new Table(manager, 10, 10, 502 - 20, 420 - 60);

	// 读取学生数据
	if (!manager.read(DATA_FILE))
	{
		MessageBox(GetHWnd(), L" “Students.dat” 文件打开失败，无法对其进行操作！", L"错误", MB_OK | MB_ICONERROR);
		exit(-1);
	}
}

Window::~Window()
{
	// 销毁
	delete mainWindow_view;
	delete mainWindow_edit;
	delete mainWindow_clear;
	delete mainWindow_exit;

	delete viewStudents_pageUp;
	delete viewStudents_pageDown;
	delete viewStudents_sort;
	delete viewStudents_back;

	delete editStudents_search;
	delete editStudents_add;
	delete editStudents_delete;
	delete editStudents_back;

	delete table;
}

void Window::show() const
{
	ShowWindow(hWnd, SW_SHOW);
}

void Window::messageLoop()
{
	// 开启消息循环
	ExMessage msg;
	while (true)
	{
		// 获取并判断消息
		msg = getmessage();

		// 判断显示界面
		if (state == WindowState::mainWindow)		// 主窗口显示
		{
			if (mainWindow_view->state(msg))		// 查看学生
			{
				showViewStudents();
			}
			else if (mainWindow_edit->state(msg))	// 编辑学生
			{
				showEditStudents();
			}
			else if (mainWindow_clear->state(msg))	// 清空数据
			{
				if (MessageBox(GetHWnd(), L"确定要清空所有学生数据？", L"清空数据", MB_YESNO | MB_ICONQUESTION) == IDYES)
				{
					// 确定清空
					manager.clear();
					isEdit = true;
				}
			}
			else if (mainWindow_exit->state(msg))	// 退出程序
			{
				if (close())
				{
					return;
				}
			}
		}
		else if (state == WindowState::viewStudents)	// 查看学生窗口显示
		{
			if (viewStudents_pageUp->state(msg) && msg.message != WM_LBUTTONUP)			// 上一页
			{
				table->pageUp();
			}
			else if (viewStudents_pageDown->state(msg) && msg.message != WM_LBUTTONUP)	// 下一页
			{
				table->pageDown();
			}
			else if (viewStudents_back->state(msg))	// 返回
			{
				// 显示主窗口
				showMainWindow();
			}
			else if (viewStudents_sort->state(msg) && msg.message != WM_LBUTTONUP)	// 排序
			{
				if (viewStudents_sort->getText() == L"按总分排序")
				{
					manager.sortByScore();
					table->show();
					viewStudents_sort->setText(L"按学号排序");
					viewStudents_sort->state(msg);
				}
				else
				{
					manager.sortById();
					table->show();
					viewStudents_sort->setText(L"按总分排序");
					viewStudents_sort->state(msg);
				}
			}
		}
		else	// 编辑学生窗口显示
		{
			if (editStudents_back->state(msg))	// 返回
			{
				// 显示主窗口
				showMainWindow();
			}
			else if (editStudents_search->state(msg) && msg.message != WM_LBUTTONUP)	// 搜索学生
			{
				wchar_t str[10];
				if (InputBox(str, 5, L"请输入学号或姓名进行搜索：", L"搜索学生", NULL, 0, 0, false))
				{
					int number = _wtoi(str);

					if (number == 0)	//为字符串
					{
						table->showEditTable(str);

						if (table->getSearchIndex() == -1)	// 搜索失败
						{
							MessageBox(GetHWnd(), L"未找到学生！", L"提示", MB_OK | MB_ICONINFORMATION);
						}
					}
					else				// 为数字
					{
						table->showEditTable(number);
						
						if (table->getSearchIndex() == -1)
						{
							MessageBox(GetHWnd(), L"未找到学生！", L"提示", MB_OK | MB_ICONINFORMATION);
						}
					}
				}
			}
			else if (editStudents_add->state(msg) && msg.message != WM_LBUTTONUP)		// 添加学生
			{
				wchar_t stuString[20];	// 学生字符串

				// 点击确定按钮才进行添加
				if (InputBox(stuString, 20, L"请按照 “学号 姓名 班级 总分” 的格式输入数据：", L"添加学生", NULL, 0, 0, false))
				{
					// 格式化输入字符串
					std::wstringstream format(stuString);
					Student stu = {};
					format >> stu.id >> stu.name >> stu.Class >> stu.score;

					// 判断格式
					if (stu.id <= 0)
					{
						MessageBox(GetHWnd(), L"学号不能小于或等于零！", L"提示", MB_OK | MB_ICONINFORMATION);
						continue;
					}
					else if (std::wstring(stu.name) == L"" || std::wstring(stu.Class) == L"")
					{
						MessageBox(GetHWnd(), L"姓名和班级不能为空！", L"提示", MB_OK | MB_ICONINFORMATION);
						continue;
					}
					else if (stu.score < 0)
					{
						MessageBox(GetHWnd(), L"分数不能小于零！", L"提示", MB_OK | MB_ICONINFORMATION);
						continue;
					}

					// 添加和刷新数据
					manager.addStudent(stu);
					table->showEditTable(stu.name);
					manager.sortById();

					isEdit = true;
				}
			}
			else if (editStudents_delete->state(msg) && msg.message != WM_LBUTTONUP)	// 删除学生
			{
				short i = table->getSearchIndex();

				// 判断是否搜索了学生
				if (i != -1)
				{
					std::wstringstream format;
					if (MessageBox(GetHWnd(), L"确定要删除这个学生吗？", L"确定删除", MB_YESNO | MB_ICONQUESTION) == IDYES)
					{
						manager.deleteStudent(i);
						showEditStudents();
						isEdit = true;
						table->setSearchIndex(-1);
					}
				}
				else
				{
					MessageBox(GetHWnd(), L"请先搜索学生！", L"提示", MB_OK | MB_ICONINFORMATION);
				}
			}
		}
	}
}

bool Window::close()
{
	if (isEdit)
	{
		// 进行保存
		int id = MessageBox(GetHWnd(), L"是否保存所有的操作？", L"退出程序", MB_YESNOCANCEL | MB_ICONQUESTION);
		if (id == IDYES)
		{
			// 写入学生数据
			manager.sortById();
			manager.write(DATA_FILE);
			closegraph();
			return true;
		}
		else if (id == IDNO)
		{
			return true;
		}
	}
	else
	{
		return true;
	}
	return false;
}

void Window::showMainWindow()
{
	state = WindowState::mainWindow;
	cleardevice();

	// 加载背景图片
	loadimage(NULL, BACKGROUND_IMAGE, 502, 420);

	// 绘制提示文字
	RECT rect = { 0, 0, width, 200 };
	settextstyle(50, 0, L"微软雅黑");
	drawtext(L"学生成绩管理系统", &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	// 显示按钮
	mainWindow_view->show();
	mainWindow_edit->show();
	mainWindow_exit->show();
	mainWindow_clear->show();
}

void Window::showViewStudents()
{
	state = WindowState::viewStudents;
	cleardevice();

	// 加载背景图片
	loadimage(NULL, BACKGROUND_IMAGE, 502, 420);

	// 显示控件
	table->show();
	viewStudents_pageUp->show();
	viewStudents_pageDown->show();
	viewStudents_back->show();
	viewStudents_sort->show();
}

void Window::showEditStudents()
{
	state = WindowState::editStudents;
	cleardevice();

	// 加载背景图片
	loadimage(NULL, BACKGROUND_IMAGE, 502, 420);

	// 显示控件
	editStudents_search->show();
	editStudents_add->show();
	editStudents_delete->show();
	editStudents_back->show();
}

bool Window::isNumber(const std::wstring& string)
{
	if (_wtoi(string.c_str()) == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}
