#ifndef DEMO_H
#define DEMO_H

#include <QtWidgets/QWidget>
#include "ui_demo.h"
#include <QtOpenGL/QtOpenGL>
#include <QTimer>
class demo : public QGLWidget
{
	Q_OBJECT

public:
	demo(QWidget *parent = 0);
	~demo();
	QTimer clk;
	float m_x, m_y, m_z;
	GLuint textur;
protected:
	void initializeGL();
	void initWidget();
	void paintGL();
	void resizeGL(int width, int height);
	void loadGLTextures();
	private slots:
	void updateWindow();
private:
	Ui::demoClass ui;
};

#endif // DEMO_H

