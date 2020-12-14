#include "pch.h"
#include "Player.h"

using namespace std;
using namespace cv;

int main()
{

	//取消cin与stdin的同步，提升程序效率
	ios::sync_with_stdio(false);

	//声明Player对象 py
	Player py;

	//得到句柄
	py.SetStdWindow(GetStdHandle(STD_OUTPUT_HANDLE), GetForegroundWindow());

	//进行总的设置
	py.Set();

	//从视频中读取每一帧并且做字符串处理
	//多线程，创建新的进程
	thread t1{ &Player::GetFrameFromVideo,&py };
	t1.detach();

	//缓冲一会儿
	cout << "视频正在缓冲……" << endl;
	py.show_info();
	Sleep(3000);
	//进行视频的播放
	py.PlayVideo();


	return 0;
}