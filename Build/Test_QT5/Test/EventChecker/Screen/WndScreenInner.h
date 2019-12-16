
#pragma once

#include <QtWidgets/QWidget>

class CWndCell;
class CWndScreenInner : public QWidget {
	Q_OBJECT

private:
	int			m_nChIdx;
	CWndCell	*m_pCell;

public:
	CWndScreenInner(QWidget *pParent = nullptr);
	virtual ~CWndScreenInner();

	bool SetChImage(int nChIdx, QPixmap *pBuf);
	int GetChIdx();

	bool SetDrawInfo(CWndCell& wndCell);

protected:
	virtual void resizeEvent(QResizeEvent *event) override;

};