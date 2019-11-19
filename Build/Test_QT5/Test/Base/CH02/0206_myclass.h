
#pragma once

/*
	# QWidget
	1. public functions
		- QWidget(QWidget *parent=0, WFlags f=0)	// 생성자. parent 가 0 이면 최상위 위젯.
		- ~QWidget()					// 소멸자. 자식 위젯이 먼저 소멸된다. 메인 위젯이라면 애플리케이션이 종료된다.
		- WId winId() const				// 윈도우 시스템 ID 를 반환한다. QWidget *find(WId id)
		- bool isVisible() const		// 위젯이 화면에서 보이는 상태이면 참(True) 값을 반환한다.
		- bool isHidden() const			// 위젯이 화면에서 숨겨진 상태이면 참(True) 값을 반환한다.
		- isMinimized() const			// 위젯이 최소 윈도우 형태(아이콘화)이면 참(True) 값을 반환한다.
		- isMaximized() const			// 위젯이 최대 윈도우 형태이면 참(True) 값을 반환한다.
		- bool isTopLevel() const		// 위젯이 최상이 위젯이면 참(True) 값을 반환한다.
		- bool isDialog() const			// 위젯이 대화상자이면 참(True) 값을 반환한다.
		- bool isModal() const			// 위젯이 모달(Modal) 위젯이면 True 반환
		- bool isPopup() const			// 팝업 위젯이면 True 반환
		- bool isDesktop() const		// 데스크톱 위젯이면 True 반환
		- void stackUnder(QWidget *w)	// 스태킹 순서를 부모 위젯에서 형재 위젯의 아래에 위치시킨다.
		- QWidget *parentWidget(bool sameWindow=FALSE) const	// 부모 위젯의 포인터 반환
		- QWidget *childAt(int x, int y, bool includeThis = FALSE) const // 지정한 위치에 있는 자식 위젯의 포인터 반환
	2. public slots
		- void close()		// QCloseEvent 를 내보내고 위젯을 닫는다.
		- void hide()		// 위젯을 화면에서 숨긴다.	hideEvent()
		- void show()		// 위젯을 화면에 보여준다.
		- void raise()		// 위젯의 스태킹 순서를 위(Top)로 올린다.
		- void lower()		// 위젯의 스태킹 순서를 밑(Bottom)으로 내린다.
	3. static public member
		QWidget *find(WId id)		// 윈도우 시스템 ID 와 관련된 위젯의 포인터를 반환한다.
*/

class C0206_MyClass : public ITestObject {
public:
	class MyClass : public QWidget {
	public:
		MyClass() {
			QPushButton *quit = new QPushButton("Quit", this);
			quit->resize(75, 35);

			// QApplication 은 인스턴스 변수를 갖고 있지 않기 때문에 
			//	qApp 라는 전역 변수를 제공한다.
			QObject::connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));
		}
	};

	virtual int OnTest(int nArgNum, char** ppArgs) {
		QApplication app(nArgNum, ppArgs);
		MyClass *quit = new MyClass();
		quit->show();		
		return app.exec();
	}
};
