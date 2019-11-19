
#pragma once

/*
	QCheckBox
	1. Public Functions
		QCheckBox(const QString &text, QWidget *parent = 0)
		void setCheckState(Qt::CheckState state)	// 체크 박스의 상태를 설정. checkState()
		void setTristate(bool y = true)		// bool 값에 따라 체크 박스를 세가지 상태로 설정, bool isTristate()
		bool isChecked() const		// 체크 박스가 선택되었는지 확인
		void setText(const QString &text)		// 체크 박스에 표시할 문자열 설정
	2. Public Slots
		void click()				// 체크 박스를 클릭한다.
		void setChecked(bool)		// 체크 박스의 상태를 바꾼다.
		void toggle()				// 체크 박스를 토글시킨다.
	3. Signals
		void stateChanged(int state)		// 체크 박스의 상태가 바뀔 때 발생
		void clicked(bool checked = false)	// 마우스로 체크 박스 클릭 했을 때 발생
		void pressed()						// 마우스로 체크 박스 누를 때 발생
		void released()						// 마우스로 체크 박스 눌렀다가 떼었을 때 발생
		void toggled(bool checked)			// 체크 박스의 토글 상태 변경 시 발생
*/

class C0302_CheckBox : public ITestObject {
public:
	class CheckBox : public QWidget {
	private:
		QCheckBox		*CheckBox1;
		QCheckBox		*CheckBox2;
		QCheckBox		*CheckBox3;
		QCheckBox		*CheckBox4;
		QButtonGroup	*ButtonGroup;

	public:
		CheckBox() {
			resize(130, 110);
			ButtonGroup = new QButtonGroup(this);
			CheckBox1 = new QCheckBox("CheckBox1", this);
			CheckBox1->move(10, 10);
			ButtonGroup->addButton(CheckBox1);
			CheckBox2 = new QCheckBox("CheckBox2", this);
			CheckBox2->move(10, 30);
			ButtonGroup->addButton(CheckBox2);
			CheckBox3 = new QCheckBox("CheckBox3", this);
			CheckBox3->move(10, 50);
			ButtonGroup->addButton(CheckBox3);
			CheckBox4 = new QCheckBox("CheckBox4", this);
			CheckBox4->move(10, 70);
			ButtonGroup->addButton(CheckBox4);
		}
	};
	virtual int OnTest(int nArgNum, char** ppArgs) {
		QApplication app(nArgNum, ppArgs);

		CheckBox CheckBoxWindow;
		CheckBoxWindow.show();
		
		return app.exec();
	}
};