
#pragma once

/*
	# QObject::connect(sender, SIGNAL(signal), receiver, SLOT(slot));
	- sender : 시그널을 발생시킬 객체의 포인터 지정
	- signal : sender 가 발생시키는 시그널을 지정한다. 반드시 sender 를 지정해야 한다.
	- receiver : sender 에 의해 발생된 시그널을 받을 객체의 포인터를 지정한다.
	- slot :	receiver에 정의되어 있는 슬롯을 지정한다. signal 이 반드시 있어야 한다.
	- 시그널이 전달하는 매개 변수의 타입과 수가 슬롯과 일치해야 한다.
	- 연결 해제 시 disconnect 함수 이용

	# QObject
	1. public functions
	- QObject(QObject *parent = 0)	// 생성자
	- virtual ~QObject()			// 소멸자
	- bool inherits(const char *className) const	// QObject 클래스를 상속하는 객체를 재상속하는 클래스 인스턴스라면 참
	- bool setProperty(const char *name, const QVariant &value)	// 객체의 name 속성 값을 설정, 속성정보는 metaObject()제공
	- const QObjectList &children() const		// 객체의 QObjectList 클래스를 반환한다. 자식 없으면 0
	- QObject *parent() const					// 부모 객체의 포인터를 반환한다.
	2. Related Non-members
	- T findChild(const QString &name = QString()) const	// 이름이 name 인 자식 객체를 찾아 T로 캐스팅해서 반환
*/

class C0204_Quit : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char** ppArgs) {
		QApplication app(nArgNum, ppArgs);
		QPushButton *quit = new QPushButton("Quit", 0);
		quit->resize(75, 35);
		quit->show();
		QObject::connect(quit, SIGNAL(clicked()), &app, SLOT(quit()));
		return app.exec();
	}
};
