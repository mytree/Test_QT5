
#pragma once

#include <QtOpenGL/QGL>					// OpenGL

class C0804_OpenGL : public QGLWidget {
public:
	C0804_OpenGL() {
		resize(160, 120);
	}

	void paintGL() {
		glClear(GL_COLOR_BUFFER_BIT);
		qglColor(Qt::white);
		renderText(50.0, 60.0, 0.0, QString("Hello Qt"));
	}

	void resizeGL(int w, int h) {
		printf("W: %d, H: %d\n", w, h);

		glViewport(0, 0, (GLint)w, (GLint)h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, w, 0, h, -1, 1);
		glMatrixMode(GL_MODELVIEW);
	}
};

class C0804_TestOpenGL : public ITestObject {
public:
	virtual int OnTest(int nArgNum, char **ppArgs) {
		QApplication app(nArgNum, ppArgs);

		C0804_OpenGL p;
		p.show();

		return app.exec();
	}
};