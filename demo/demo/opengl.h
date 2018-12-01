#ifndef OPENGL_H
#define OPENGL_H

#include <QGLWidget>
#include <QtOpenGL/QtOpenGL>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

#define MIN_LENGTH 35
#define IMAGE_WIDTH 640
#define IMAGE_HEIGHT 480
class OpenGL : public QGLWidget
{
	Q_OBJECT

public:
	OpenGL(QWidget *parent = 0);
	~OpenGL();
	//cam
	Mat frame;
	VideoCapture cam, video;
	vector<Point3f> Xworld;
	vector<Point2f> Ximage;
	GLfloat projection_matrix[16];//
	//GLdouble rotMatrix[16];
	vector<GLdouble> rotMatrix;//ĳһ����ǵı任����
	GLdouble rotMat[16];//Ϊ�˶�Ӧopengl������ʽ���������
	//GLdouble *rotMatrix = new GLdouble(16);
	vector<vector<GLdouble> >  RotationMatrix;//�����еı任���󱣴�ͬһ��Ⱦ
	Mat cameraMatrix = Mat(3, 3, CV_64FC1, 1);
	Mat distCoeffs = Mat(1, 4, CV_64FC1, 1);
	//opengl
	QTimer clk;
	//GLfloat m_x, m_y, m_z;
	//GLfloat xx;
	float WINDOW_SIZE;
	//float Z_JUST; 
	//int WINDOW_SIZE;
	GLuint texturImage;
	GLuint texturFrame;
	void imageProcess(Mat);
	//�����Ӧ
	Mat warpMat;
	Point2f dstRect[4];
	Point2f srcRect[4];
	char number;
	Mat dobotPos = Mat(3, 1, CV_64FC1, Scalar(0, 0, 0));
	Mat dobotTargetPos;
	Point2f dobotFinalTargetPos;//��һ����λ��
protected:
	void initializeGL();
	void initWidget();
	void paintGL();
	void resizeGL(int width, int height);
	void loadGLTextures();
	void  mousePressEvent(QMouseEvent *);
	private slots:

	void updateWindow();
	void updateParams(int);
};

#endif // OPENGL_H
