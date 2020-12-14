#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <cmath>
#include <windows.h>
#include <stdlib.h>
#include <string>
#include <fstream>
using namespace std;
//使用opencv的命名空间
using namespace cv;
class Player {
public:

	//构造函数
	Player();

	//获取控制台和前台窗口句柄
	void SetStdWindow(HANDLE hd, HWND hwnd);

	//进行控制台窗口的一些设置，比如全屏
	void SetWindowConfig();

	//从文件中获取每一帧，解析为字符串存在数组中
	void GetFrameFromVideo();

	//放映视频
	void PlayVideo();

	//设置字体大小（用户交互）
	void SetPixelSize();

	//设置字体大小
	void SetPixelSize(int size);

	//输出数据到文本
	void Output_to_file();

	//从文本中获取数据
	void Gain_date_from_file();

	//得到当前字体大小
	int Get_Myfontsize();

	//用户设定模式
	void Set();

	//输入文件路径及文件名
	void Input_file();

	//得到文件路径及文件名
	string Get_file_info();

	//设置视频播放速度(用户交互)
	void Set_speed();

	//设置视频播放速度（带参数）
	void Set_speed(double sp);

	//得到视频速度
	double Get_speed();

	//设置视频宽度（用户交互）
	void Set_frame_width();

	//设置视频高度（用户交互）
	void Set_frame_height();

	//设置视频宽度（带参数）
	void Set_frame_width(int w);

	//设置视频高度（带参数）
	void Set_frame_height(int h);

	//得到视频宽度
	int Get_frame_width();

	//得到视频高度
	int Get_frame_height();

	//设置帧率（用户交互）
	void Set_framerate();

	//设置帧率（带参数）
	void Set_framerate(int f);

	//得到当前帧率
	int Get_framerate();

	//展示参数
	void show_info();

private:

	//存放所有帧解析好的的字符串数组
	vector<string> Frames;

	//帧总数
	int FramesNum;

	//帧宽度
	int FrameWidth;

	//帧高度
	int FrameHeight;

	//放映速度
	double speed;

	//帧率
	double FrameRate;

	//前台窗口句柄
	HWND MyHwnd;

	//控制台句柄
	HANDLE MyHandle;

	//像素点大小
	int Myfontsize;

	//视频路径及名字
	string file;
};

#endif 