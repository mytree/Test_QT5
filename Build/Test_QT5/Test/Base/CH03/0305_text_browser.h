
#pragma once

/*
	QTextBrowser
	1. Public Functions
		QTextBrowser(QWidget *parent = 0)
		virtual QVariant loadResource(int type, const QUrl &name)	// 문서가 불려지면 호출된다.
		void setSearchPaths(const QStringList &paths)		// 텍스트 브라우저가 지원하는 콘텐츠를 찾을 경로를 설정
		QUrl source() const		// 불러온 문서의 위치를 반환한다.
	2. Public Slots
		virtual void backward()		// 방금 전에 봤던 문서로 이동한다.
		virtual void forward()		// 다음 문서로 이동한다. backward() 메소드를 실행한 경우 이전 문서 이동
		virtual void home()			// 홈(가장 처음에 봤던 문서)으로 이동한다.
		virtual void reload()		// 현재 문서를 다시 불러온다.
		virtual void setSource(const QUrl &name)	// 텍스트 브라우저에 불러올 문서의 위치를 설정
	3. Signals
		void anchorClicked(const QUrl &link)	// 사용자가 하이퍼텍스트의 링크를 클릭할 때 발생
		void backwardAvailable(bool available)	// 이전 문서로 이동하는 것이 가능하면 발생한다.
		void forwardAvailable(bool available)	// 다음 문서로 이동하는 것이 가능하면 발생한다.
		void highlighted(const QString &link)	// 아직 보지 않은 하이퍼텍스트의 링크를 클릭할 때 발생한다.
	4. Protected Functions
		virtual void keyPressEvent(QKeyEvent *ev)	// 키보드를 누르는 것과 관련된 이벤트

*/

class C0305_TextBrowser : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char** ppArgs) {
		QApplication app(nArgNum, ppArgs);

		QUrl url("index.html");

		QTextBrowser *tb = new QTextBrowser();
		tb->setSource(url);
		tb->show();

		return app.exec();
	}
};