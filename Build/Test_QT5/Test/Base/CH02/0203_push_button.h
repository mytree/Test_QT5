
#pragma once

/*
	# QPushButton
	1. public functions
		void setFlat(bool)					// 버튼 모양이 평평한지 결정한다.
			void isFlat()
		void setIcon(const QIcon &icon)		// 버튼 위에 표시 할 아이콘을 설정한다.
		void setText(const QString &text)	// 버튼 위에 표시할 문자를 설정한다.
			QString text()
	2. Signals
		void pressed()						// 마우스 버튼을 누르고 있을 때 발생. QAbstractButton 클래스로부터 상속받는다.
		void released()						// 마우스의 버튼을 눌렀다 뗄 때 발생. QAbstractButton 클래스로부터 상속받는다.
		void clicked()						// 마우스로 버튼을 클릭할 때 발생.	  QAbstractButton 클래스로부터 상속받는다.
		void toggle(bool checked)			// 토글 메시지 처리.				  QAbstractButton 클래스로부터 상속받는다.
*/

class C0203_PushButton : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char** ppArgs) {
		QApplication app(nArgNum, ppArgs);
		QPushButton *quit = new QPushButton("Quit", 0);
		quit->resize(75, 35);
		quit->show();
		return app.exec();
	}
};
