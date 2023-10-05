/*
*	程序：使用 EasyX 实现的学生成绩管理系统
*	作者：Qt小徐
*	编译环境：Visual Studio 2022 + EasyX_20220901
*	最后修改：2023 年 1 月 31 日
*/


#include "Window.h"

int main()
{
	Window window(502, 420);
	window.show();
	window.messageLoop();
	return 0;
}