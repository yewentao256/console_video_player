#include "pch.h"
#include "Player.h"
using namespace std;
using namespace cv;
using namespace std::chrono;

//构造函数，初始化赋值
Player::Player()
{
	FramesNum = 0;
	FrameWidth = 400;
	FrameHeight = 225;
	speed = 1.0;
	FrameRate = 30.0;
	Myfontsize = 2;
}


//得到句柄
void Player::SetStdWindow(HANDLE hd, HWND hwnd)
{
	MyHandle = hd;
	MyHwnd = hwnd;
}


//将数据输出到文件，如果没有，就创建一个
void Player::Output_to_file()
{
	ofstream file_txt;
	file_txt.open("set.txt", std::ios::out);
	file_txt << Myfontsize << endl;
	file_txt << speed << endl;
	file_txt << FrameHeight << endl;
	file_txt << FrameWidth << endl;
	file_txt << FrameRate << endl;
	file_txt << file << endl;
	file_txt.close();
}

//从文件中获取储存的数据
void Player::Gain_date_from_file()
{
	const int Number_of_int_data = 5;
	//利用数组存储数据
	int data[Number_of_int_data];
	ifstream file_txt;
	try {
		file_txt.open("set.txt");
	}
	catch (exception) {
		cout << "找不到set.txt文件，请重新运行本程序并进行初始化" << endl;
		return;
	}
	//读取所有数据
	for (int i = 0; i < Number_of_int_data; i++) {
		file_txt >> data[i];
	}
	string file_info;
	file_txt >> file_info;

	//将值赋给player的量
	Myfontsize = data[0];
	speed = data[1];
	FrameHeight = data[2];
	FrameWidth = data[3];
	FrameRate = data[4];
	file = file_info;
	//这里不清屏，可以在读取每一帧的时候有个信息显示
	cout << endl;
	file_txt.close();

}

//得到字体大小
int Player::Get_Myfontsize()
{
	return Myfontsize;
}

//整体的设置
void Player::Set()
{
	double key = 1;
	cout << "是否需要进行初始化？输入1进行初始化并进行设置，否则将使用上一次的设置（按99进入开发者模式）" << endl;
	cout << endl;
	cout << "注意，如果是第一次使用该程序，必须初始化！" << endl;
	cin >> key;
	system("cls");
	if (key == 1) 
	{
		Input_file();
		
	}
	else if (key == 99) {
		cout << "注意，您进入了开发者模式……" << endl;
		system("pause");
		system("cls");
		Input_file();
		Set_speed();
		SetPixelSize();
		Set_frame_width();
		Set_frame_height();
		Set_framerate();
		Output_to_file();
	}
	else
	{
		Gain_date_from_file();
	}

}

//输入文件信息
void Player::Input_file()
{
	cout << "第一步，输入文件路径及文件名：" << endl;
	cout << endl;
	cout << "提示：最简单的方式是将视频放在同一路径下然后直接输入文件名（使用相对路径），如：视频.mp4" << endl;
	cout << endl;
	cout << "否则，需要您输入完整的路径（绝对路径）" << endl;
	cout << "例如：C:/Users/zhyan/Desktop/ConsoleVideoPlayer/ConsoleVideoPlayer/视频.mp4" << endl;
	cout << "现在请输入文件路径及文件名：";
	cin >> file;
	//通过文件名输入视频（绝对路径或相对路径）
	VideoCapture vc;

	while (!vc.open(file)) {
		cout << "视频路径格式有误或视频不存在" << endl;
		cout << "请重新输入：";
		cin >> file;
	}
	system("cls");
}



//得到文件信息
string Player::Get_file_info()
{
	return file;
}

//设置播放速度
void Player::Set_speed()
{
	string str;
	double d;
	while (1) {
		cout << "请输入视频的播放速度：（请输入0.5-2.0的一个数字）" << endl;
		cin >> str;

		try {
			d = stod(str);
			if (d > 2 || d < 0.5) {
				cout << "输入错误，请重新输入：";
				continue;
			}
			break;
		}
		catch (exception) {
			cout << "输入错误，请重新输入：";
			continue;
		}
	}
	speed = d;
}

//设置播放速度（带参数）
void Player::Set_speed(double sp)
{
	speed = sp;
}

//返回播放速度
double Player::Get_speed()
{
	return speed;
}

//设置每一帧的宽度
void Player::Set_frame_width()
{
	//提供推荐设置的屏幕大小
	switch (Myfontsize) {
	case 1:
		cout << "推荐宽度800，高度450" << endl;
		break;
	case 2:
		cout << "推荐宽度480，高度270" << endl;
		break;
	case 3:
		cout << "推荐宽度320，高度180" << endl;
		break;
	case 4:
		cout << "推荐宽度240,高度135" << endl;
		break;
	case 5:
		cout << "推荐宽度160，高度90" << endl;
		break;
	case 6:
		cout << "推荐宽度160，高度90" << endl;
		break;
	case 7:
		cout << "推荐宽度160，高度90" << endl;
		break;
	case 8:
		cout << "推荐宽度160，高度90" << endl;
		break;
	case 9:
		cout << "推荐宽度120，高度72" << endl;
		break;
	}
	cout << "注意：如果播放卡顿或闪屏，则请调小宽度和高度" << endl;
	int w;
	string str;
	//用户进行输入与容错处理
	while (1) {
		cout << "请输入您需要的视频宽度：";
		cin >> str;
		try {
			w = stoi(str);
			if (w > 2000 || w < 20) {
				cout << "输入不合理，请重新输入" << endl;
				continue;

			}
			break;
		}
		catch (exception) {
			cout << "输入不合理，请重新输入" << endl;
			continue;
		}
	}
	FrameWidth = w;
}

//设置每一帧的高度
void Player::Set_frame_height()
{
	string str;
	int h;
	
	//用户输入与容错处理
	while (1) {
		cout << "请输入您需要的视频高度：";
		cin >> str;
		try {
			h = stoi(str);
			if (h > 2000 || h < 20) {
				cout << "输入不合理，请重新输入" << endl;
				continue;

			}
			break;
		}
		catch (exception) {
			cout << "输入不合理，请重新输入" << endl;
			continue;
		}
	}
	FrameHeight = h;
	system("cls");
}

//设置每一帧的宽度（带参数）
void Player::Set_frame_width(int w)
{
	FrameWidth = w;
}

//设置每一帧的高度（带参数）
void Player::Set_frame_height(int h)
{
	FrameHeight = h;
}

//返回帧的宽度
int Player::Get_frame_width()
{
	return FrameWidth;
}

//返回帧的高度
int Player::Get_frame_height()
{
	return FrameHeight;
}

//设置帧率（用户交互）
void Player::Set_framerate()
{
	cout << "请输入帧率（一秒播放多少帧）" << endl;
	cout << "注意，实际帧率与机器配置有关，建议帧率大于20且小于40" << endl;
	int f;
	string str;

	//用户输入与容错处理
	while (1) {
		cout << "请输入您需要的视频帧率：";
		cin >> str;
		try {
			f = stoi(str);
			if (f>65||f<0) {
				cout << "输入不合理，请重新输入" << endl;
				continue;

			}
			break;
		}
		catch (exception) {
			cout << "输入不合理，请重新输入" << endl;
			continue;
		}
	}
	FrameRate = f;
	system("cls");
}

//设置帧率
void Player::Set_framerate(int f)
{
	FrameRate = f;
}

//得到帧率
int Player::Get_framerate()
{
	return FrameRate;
}

//显示设置的视频参数
void Player::show_info()
{
	cout << "文件信息：" << file << endl;
	cout << "像素大小:" << Myfontsize << endl;
	cout << "播放速度:" << speed << endl;
	cout << "视频高度：" << FrameHeight << endl;
	cout << "视频宽度：" << FrameWidth << endl;
	cout << "帧率：" << FrameRate << endl;
}

//设置控制台信息（全屏）
void Player::SetWindowConfig()
{
	//得到屏幕长度
	int screen_width = GetSystemMetrics(SM_CXSCREEN);

	//得到屏幕宽度
	int screen_length = GetSystemMetrics(SM_CYSCREEN);

	//获取hwnd的窗口信息，GWL_STYLE获取窗口风格信息
	//注意：它是由一串二进制代码010101010101011等等共32位构成的，每一位代表一个功能
	LONG  l_Winstyle = GetWindowLong(MyHwnd, GWL_STYLE);

	//进行设置
	SetWindowLong(MyHwnd, GWL_STYLE, (l_Winstyle | WS_POPUP | WS_MAXIMIZE));

	//进行设置
	SetWindowPos(MyHwnd, HWND_TOP, 0, 0, screen_width, screen_length, 0);
}

//从视频中获取每一帧，并且处理，最后存储都字符串数组中
void Player::GetFrameFromVideo()
{
	//通过文件名输入视频（绝对路径或相对路径）
	VideoCapture vc;
	try {
		vc.open(file);
	}
	catch (Exception) {
		cout << "视频路径格式有误或视频不存在" << endl;
		return;
	}

	//声明将要预处理的帧
	Mat frameRaw;

	//获得视频总帧数
	//CAP_PROP_FRAME_COUNT是opencv宏定义的抓取帧数总量
	FramesNum = vc.get(CAP_PROP_FRAME_COUNT);
	Frames.resize(FramesNum + 2);

	//将光标设为不可见,1表示光标厚度，false表示不可见
	_CONSOLE_CURSOR_INFO cf = { 1,false };


	//使用vector数组来储存每一帧
	//+3是为了冗余
	vector<string> allframe(FramesNum + 3);

	//记录开始时间
	double start = GetTickCount64();

	//计数用
	int framediff = 0, j, k;

	//定义存储一帧的字符串
	string output = "";

	//定义一个二值化字符串
	string sign[2] = { " ","#" };

	//CAP_PROP_POS_AVI_RATIO是视频相对位置,0~1的一个值
	//这样写一样是为了冗余 
	//这整个for循环用于读取视频每一帧，并存放到数组里。
	for (int i = 0; i < FramesNum && vc.get(CAP_PROP_POS_AVI_RATIO) < (1 - 10E-6); i++) {
		Mat frameGray, frameOut,frameRaw;
		//将光标设为不可见
		SetConsoleCursorInfo(MyHandle, &cf);

		//获得下一帧，如果还未获得过，则获取第一帧
		vc >> frameRaw;

		//防止视频空帧。2019年6月1日19:20，追踪短点调试debug发现
		//dim是维数，宽和高各代表一个维度
		if (frameRaw.dims == 0)
			break;
		//将当前RGB帧转换为灰度图像
		cvtColor(frameRaw, frameGray, 7);

		//缩小尺寸
		resize(frameGray, frameOut, Size(FrameWidth, FrameHeight));

		//第一个for循环是行遍历，第二个for循环是列遍历
		for (j = 0; j < FrameHeight; j++) {
			for (k = 0; k < FrameWidth; k++) {

				//二值化显示像素，灰度大于127即显示
				if (frameOut.at<bool>(j, k) > 127) {
					output += "#";
					//putchar(' ');
				}
				else {
					output += " ";
					//putchar(' ');
				}
			}
			output += "\n";
		}
		Frames[i] = output;
		output = "";

	}
}

//使用锁帧算法进行放映，原理：每秒划分为n段，如果播放完一帧还有时间，则暂停播放直至下一段
void Player::PlayVideo()
{
	//清屏
	system("cls");

	//应用字体设置
	SetPixelSize(Get_Myfontsize());

	//全屏
	SetWindowConfig();

	//定义当前帧数
	int framediff = 0, totalFrameNum = FramesNum, start = 0, startDisplay = 0,
		delay = 0;
	double span = 1000 / ((FrameRate + 1) * speed);

	//光标控制，设定光标大小为1，不可见
	_CONSOLE_CURSOR_INFO cf = { 1,false };

	//startDisplay = GetTickCount64();
	auto startTime = high_resolution_clock::now();
	for (int i = 0; i < totalFrameNum; i++) {
		//确保每一帧的显示光标都不可见
		//startDisplay = GetTickCount64();
		SetConsoleCursorInfo(MyHandle, &cf);

		//把光标位置定义在（0,0）位置，可以实现重置效果
		SetConsoleCursorPosition(MyHandle, { 0,0 });


		//输出画面
		cout << Frames[i] << endl;
		auto endTime = high_resolution_clock::now();
		auto ftime = duration_cast<duration<double, ratio<1, 1000>>>(endTime - startTime).count();
		if (ftime < span) this_thread::sleep_for(milliseconds((int)(span - ftime)));


		//展示目前的帧数并计算帧率
		if (GetTickCount64() - start >= 1000) {
			string temp = "frame：" + to_string(i) + "  fps：" + to_string(i - framediff) + "display frame time:" + to_string(ftime);
			SetConsoleTitleA(temp.c_str());
			framediff = i + 1;
			start = GetTickCount64();
			//system("cls");

		}
		startTime = high_resolution_clock::now();
	}
	system("cls");
	SetPixelSize(30);
	cout << "视频已播放完毕，感谢您的使用！" << endl;
}

//设置字体大小（即像素点）
void Player::SetPixelSize()
{
	cout << "注意：像素点较低的话要求一定电脑配置" << endl;
	cout << "请输入像素点大小（限定范围1-9）" << endl;
	int size;
	string str;
	while (1) {
		cin >> str;
		try {
			size = stoi(str);
			if (size > 9 || size < 1) {
				cout << "输入不合理，请重新输入（限定范围1-9）" << endl;
				continue;
			}
			break;
		}
		catch (exception) {
			cout << "输入不合理，请重新输入:" << endl;
			continue;
		}
	}
	Myfontsize = size;
	system("cls");
}

//设置字体（像素点）大小（带参数）
void Player::SetPixelSize(int size)
{
	Myfontsize = size;
	//调整字体
	WCHAR myFont[] = TEXT("Arial");
	//使用设置字体API所需的结构体
	_CONSOLE_FONT_INFOEX fontinfo = { sizeof(CONSOLE_FONT_INFOEX) ,
	1,
	{Myfontsize,Myfontsize},
	TMPF_FIXED_PITCH,
	400,
	*myFont };
	SetCurrentConsoleFontEx(MyHandle, false, &fontinfo);
}