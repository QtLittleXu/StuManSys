#include "Window.h"

Window::Window(int width, int height) :
	Widget(0, 0, width, height),
	isEdit(false),
	hWnd(initgraph(width, height, EX_NOCLOSE))
{
	SetWindowText(hWnd, L"ѧ���ɼ�����ϵͳ");
	setbkcolor(WHITE);
	cleardevice();
	ShowWindow(hWnd, SW_HIDE);

	// ���û�ͼ��ʽ
	LOGFONT f;
	gettextstyle(&f);
	f.lfQuality = DEFAULT_QUALITY;
	settextstyle(&f);
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	setlinecolor(BLACK);

	// ������ť
	mainWindow_view	 = new Button((502 - 150) / 2, 160, 150, 40, L"�鿴ѧ��");
	mainWindow_edit = new Button((502 - 150) / 2, 220, 150, 40, L"�༭ѧ��");
	mainWindow_clear = new Button((502 - 150) / 2, 280, 150, 40, L"�������");
	mainWindow_exit = new Button((502 - 150) / 2, 340, 150, 40, L"�˳�����");

	viewStudents_pageUp = new Button(10, 380, 80, 30, L"��һҳ");
	viewStudents_pageDown = new Button(210, 380, 80, 30, L"��һҳ");
	viewStudents_back = new Button(412, 380, 80, 30, L"����");
	viewStudents_sort = new Button(300, 380, 102, 30, L"���ܷ�����");

	editStudents_search = new Button(10, 380, 100, 30, L"����ѧ��");
	editStudents_add = new Button(137, 380, 100, 30, L"���ѧ��");
	editStudents_delete = new Button(264, 380, 100, 30, L"ɾ��ѧ��");
	editStudents_back = new Button(392, 380, 100, 30, L"����");

	showMainWindow();	// ��ʾ������

	// �������
	table = new Table(manager, 10, 10, 502 - 20, 420 - 60);

	// ��ȡѧ������
	if (!manager.read(DATA_FILE))
	{
		MessageBox(GetHWnd(), L" ��Students.dat�� �ļ���ʧ�ܣ��޷�������в�����", L"����", MB_OK | MB_ICONERROR);
		exit(-1);
	}
}

Window::~Window()
{
	// ����
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
	// ������Ϣѭ��
	ExMessage msg;
	while (true)
	{
		// ��ȡ���ж���Ϣ
		msg = getmessage();

		// �ж���ʾ����
		if (state == WindowState::mainWindow)		// ��������ʾ
		{
			if (mainWindow_view->state(msg))		// �鿴ѧ��
			{
				showViewStudents();
			}
			else if (mainWindow_edit->state(msg))	// �༭ѧ��
			{
				showEditStudents();
			}
			else if (mainWindow_clear->state(msg))	// �������
			{
				if (MessageBox(GetHWnd(), L"ȷ��Ҫ�������ѧ�����ݣ�", L"�������", MB_YESNO | MB_ICONQUESTION) == IDYES)
				{
					// ȷ�����
					manager.clear();
					isEdit = true;
				}
			}
			else if (mainWindow_exit->state(msg))	// �˳�����
			{
				if (close())
				{
					return;
				}
			}
		}
		else if (state == WindowState::viewStudents)	// �鿴ѧ��������ʾ
		{
			if (viewStudents_pageUp->state(msg) && msg.message != WM_LBUTTONUP)			// ��һҳ
			{
				table->pageUp();
			}
			else if (viewStudents_pageDown->state(msg) && msg.message != WM_LBUTTONUP)	// ��һҳ
			{
				table->pageDown();
			}
			else if (viewStudents_back->state(msg))	// ����
			{
				// ��ʾ������
				showMainWindow();
			}
			else if (viewStudents_sort->state(msg) && msg.message != WM_LBUTTONUP)	// ����
			{
				if (viewStudents_sort->getText() == L"���ܷ�����")
				{
					manager.sortByScore();
					table->show();
					viewStudents_sort->setText(L"��ѧ������");
					viewStudents_sort->state(msg);
				}
				else
				{
					manager.sortById();
					table->show();
					viewStudents_sort->setText(L"���ܷ�����");
					viewStudents_sort->state(msg);
				}
			}
		}
		else	// �༭ѧ��������ʾ
		{
			if (editStudents_back->state(msg))	// ����
			{
				// ��ʾ������
				showMainWindow();
			}
			else if (editStudents_search->state(msg) && msg.message != WM_LBUTTONUP)	// ����ѧ��
			{
				wchar_t str[10];
				if (InputBox(str, 5, L"������ѧ�Ż���������������", L"����ѧ��", NULL, 0, 0, false))
				{
					int number = _wtoi(str);

					if (number == 0)	//Ϊ�ַ���
					{
						table->showEditTable(str);

						if (table->getSearchIndex() == -1)	// ����ʧ��
						{
							MessageBox(GetHWnd(), L"δ�ҵ�ѧ����", L"��ʾ", MB_OK | MB_ICONINFORMATION);
						}
					}
					else				// Ϊ����
					{
						table->showEditTable(number);
						
						if (table->getSearchIndex() == -1)
						{
							MessageBox(GetHWnd(), L"δ�ҵ�ѧ����", L"��ʾ", MB_OK | MB_ICONINFORMATION);
						}
					}
				}
			}
			else if (editStudents_add->state(msg) && msg.message != WM_LBUTTONUP)		// ���ѧ��
			{
				wchar_t stuString[20];	// ѧ���ַ���

				// ���ȷ����ť�Ž������
				if (InputBox(stuString, 20, L"�밴�� ��ѧ�� ���� �༶ �ܷ֡� �ĸ�ʽ�������ݣ�", L"���ѧ��", NULL, 0, 0, false))
				{
					// ��ʽ�������ַ���
					std::wstringstream format(stuString);
					Student stu = {};
					format >> stu.id >> stu.name >> stu.Class >> stu.score;

					// �жϸ�ʽ
					if (stu.id <= 0)
					{
						MessageBox(GetHWnd(), L"ѧ�Ų���С�ڻ�����㣡", L"��ʾ", MB_OK | MB_ICONINFORMATION);
						continue;
					}
					else if (std::wstring(stu.name) == L"" || std::wstring(stu.Class) == L"")
					{
						MessageBox(GetHWnd(), L"�����Ͱ༶����Ϊ�գ�", L"��ʾ", MB_OK | MB_ICONINFORMATION);
						continue;
					}
					else if (stu.score < 0)
					{
						MessageBox(GetHWnd(), L"��������С���㣡", L"��ʾ", MB_OK | MB_ICONINFORMATION);
						continue;
					}

					// ��Ӻ�ˢ������
					manager.addStudent(stu);
					table->showEditTable(stu.name);
					manager.sortById();

					isEdit = true;
				}
			}
			else if (editStudents_delete->state(msg) && msg.message != WM_LBUTTONUP)	// ɾ��ѧ��
			{
				short i = table->getSearchIndex();

				// �ж��Ƿ�������ѧ��
				if (i != -1)
				{
					std::wstringstream format;
					if (MessageBox(GetHWnd(), L"ȷ��Ҫɾ�����ѧ����", L"ȷ��ɾ��", MB_YESNO | MB_ICONQUESTION) == IDYES)
					{
						manager.deleteStudent(i);
						showEditStudents();
						isEdit = true;
						table->setSearchIndex(-1);
					}
				}
				else
				{
					MessageBox(GetHWnd(), L"��������ѧ����", L"��ʾ", MB_OK | MB_ICONINFORMATION);
				}
			}
		}
	}
}

bool Window::close()
{
	if (isEdit)
	{
		// ���б���
		int id = MessageBox(GetHWnd(), L"�Ƿ񱣴����еĲ�����", L"�˳�����", MB_YESNOCANCEL | MB_ICONQUESTION);
		if (id == IDYES)
		{
			// д��ѧ������
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

	// ���ر���ͼƬ
	loadimage(NULL, BACKGROUND_IMAGE, 502, 420);

	// ������ʾ����
	RECT rect = { 0, 0, width, 200 };
	settextstyle(50, 0, L"΢���ź�");
	drawtext(L"ѧ���ɼ�����ϵͳ", &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	// ��ʾ��ť
	mainWindow_view->show();
	mainWindow_edit->show();
	mainWindow_exit->show();
	mainWindow_clear->show();
}

void Window::showViewStudents()
{
	state = WindowState::viewStudents;
	cleardevice();

	// ���ر���ͼƬ
	loadimage(NULL, BACKGROUND_IMAGE, 502, 420);

	// ��ʾ�ؼ�
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

	// ���ر���ͼƬ
	loadimage(NULL, BACKGROUND_IMAGE, 502, 420);

	// ��ʾ�ؼ�
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
