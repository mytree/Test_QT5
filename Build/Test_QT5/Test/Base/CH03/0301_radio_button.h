
#pragma once

/*
	# QRadioButton
	1. Public Functions
		QRadioButton(const QString &text, QWidget *parent = 0)	// 생성자
		bool isChecked() const		// 해당 라디오버튼이 선택되었는지 확인해 준다. QAbstractButton 상속
		void setText(const QString &text)		// 라디오 버튼에 표시할 문자열 설정. QAbstractButton 상속
		void click()				// 라디오버튼 클릭. QAbstractButton 상속
		void setChecked(bool)		// 라디오버튼 상태 변경. QAbstractButton 상속
		void toggle()				// 라디오 버튼을 토글시킨다. QAbstractButton 상속
	2. Signals
		void clicked(bool checked = false)		// 라디오 버튼 클릭 시 발생
		void pressed()							// 라디오 버튼 누를 때 발생
		void released()							// 라디오 버튼 눌렀다가 떼었을 때 발생
		void toggled(bool checked)				// 라디오 버튼 토글 상태 바뀔 때 변경
*/

class C0301_RadioButton : public ITestObject {
public:
	class RadioButton : public QWidget {
	public:
		RadioButton() {
			resize(140, 110);
			ButtonGroup = new QButtonGroup(this);
			RadioButton1 = new QRadioButton("RadioButton1", this);
			RadioButton1->move(10, 10);
			ButtonGroup->addButton(RadioButton1);		// Qt 3 : insert(RadioButton)
			RadioButton2 = new QRadioButton("RadioButton2", this);
			RadioButton2->move(10, 30);
			ButtonGroup->addButton(RadioButton2);
			RadioButton3 = new QRadioButton("RadioButton3", this);
			RadioButton3->move(10, 50);
			ButtonGroup->addButton(RadioButton3);
			RadioButton4 = new QRadioButton("RadioButton4", this);
			RadioButton4->move(10, 70);
			ButtonGroup->addButton(RadioButton4);
		}
	private:
		QRadioButton *RadioButton1;
		QRadioButton *RadioButton2;
		QRadioButton *RadioButton3;
		QRadioButton *RadioButton4;
		QButtonGroup *ButtonGroup;
	};

	virtual int OnTest(int nArgNum, char** ppArgs) {
		QApplication app(nArgNum, ppArgs);
		RadioButton RadioButtonWindow;
		RadioButtonWindow.show();
		return app.exec();
	}
};
