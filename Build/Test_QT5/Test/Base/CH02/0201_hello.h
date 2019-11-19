
#pragma once

/*
	# QApplication 
	1. static public members
		int exec()		// 애플리케이션이 종료되거나 메인 위젯이 닫힐 때까지 루프 돌면서 이벤트 처리
	2. signals
		void lastWindowClosed()		// 마지막 윈도우가 닫힐 때 발생한다.
	3. public slots
		void quit()					// 애플리케이션을 종료시킨다. void exit()
		void closeAllWindows()		// 모든 윈도우를 닫는다.
*/
class C0201_Hello : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char** ppArgs) {
		QApplication a(nArgNum, ppArgs);
		QLabel *hello = new QLabel("<font color=blue>Hello<i>Qt!</i>""</font>", 0);
		hello->show();
		return a.exec();
	}
};
