
#pragma once

#include <Qt>
#include <QtCore/QTimer>
#include <QtCore/QThread>
#include <QtCore/QMutex>
#include <QtCore/QWaitCondition>
#include <QtGui/QGuiApplication>
#include <QtGui/QStandardItemModel>
#include <QtGui/QScreen>
#include <QtGui/QPainter>
#include <QtGui/qevent.h>
#include <QtNetwork/QNetworkAccessManager>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QTextBrowser>		// Hyper-text
#include <QtWidgets/QLineEdit>			// 한 줄로 된 문자열 입력 받을 때 사용
#include <QtWidgets/QComboBox>	
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSlider>
#include <QtWidgets/QDial>
#include <QtWidgets/QBoxLayout>			// QHBoxLayout, QVBoxLayout
#include <QtWidgets/QGridLayout>		// QGridLayout
#include <QtWidgets/QStackedLayout>		// QStackedLayout
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QDialog>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMdiSubWindow>
#include <QtWidgets/QMdiArea>			// MDI 지원
#include <QtWidgets/QDesktopWidget>
#include <QtWidgets/QMessageBox>


#if defined(WIN32) | defined(WIN64)
#	if defined(DEBUG) | defined(_DEBUG)
#		pragma comment(lib, "qtmaind.lib")
#		pragma comment(lib, "Qt5Cored.lib")			// QCoreApplication, QString
#		pragma comment(lib, "Qt5Guid.lib")			// QGuiApplication
#		pragma comment(lib, "QT5Widgetsd.lib")		// QLabel
#		pragma comment(lib, "Qt5Multimediad.lib")	// QSound
#		pragma comment(lib, "Qt5OpenGLd.lib")		// QGL
#		pragma comment(lib, "opengl32.lib")			// OpenGL
#		pragma comment(lib, "Qt5Svgd.lib")			// QSvgWidget, QSvgRenderer
#	else
#		pragma comment(lib, "qtmain.lib")
#		pragma comment(lib, "Qt5Core.lib")			// QCoreApplication
#		pragma comment(lib, "Qt5Gui.lib")			// QGuiApplication
#		pragma comment(lib, "QT5Widgets.lib")		// QLabel
#		pragma comment(lib, "Qt5Multimedia.lib")	// QSound
#		pragma comment(lib, "opengl32.lib")			// OpenGL
#		pragma comment(lib, "Qt5Svg.lib")			// QSvgWidget, QSvgRenderer
#	endif
#endif

namespace QUtil {
	//!	@brief	BMP Binary Image(BGR24) 를 QImage 로 변환
	bool ConvertBGR24ToQImage(QImage &convImg, unsigned char* pSrcData, int nSrcW, int nSrcH);

	//!	@brief	BMP Binary Image(ARGB32) 를 QImage 로 변환
	bool ConvertARGB32ToQImage(QImage &convImg, unsigned char* pSrcData, int nSrcW, int nSrcH);

}

