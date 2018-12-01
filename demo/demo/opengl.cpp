#include "opengl.h"

OpenGL::OpenGL(QWidget *parent)
	: QGLWidget(parent), number(0)
{
	cam.open(0);
	//cam.set(CV_CAP_PROP_FRAME_WIDTH, IMAGE_WIDTH);
	//cam.set(CV_CAP_PROP_FRAME_HEIGHT, IMAGE_HEIGHT);
	//video.open("F:\\MOVIE\\NBA\\2016��06��20�� NBA�ܾ��� ��ʿVS��ʿ ILP 720P 30fps.mp4");
	initWidget();
	initializeGL();
	//resizeGL(640,480);
	clk.start(30);
	QObject::connect(&clk, SIGNAL(timeout()), this, SLOT(updateWindow()));
	//
	cameraMatrix.at<double>(0, 0) = 958.75165;
	cameraMatrix.at<double>(0, 1) = 0;
	cameraMatrix.at<double>(0, 2) = 288.77948;
	cameraMatrix.at<double>(1, 0) = 0;
	cameraMatrix.at<double>(1, 1) = 961.14463;
	cameraMatrix.at<double>(1, 2) = 235.69318;
	cameraMatrix.at<double>(2, 0) = 0;
	cameraMatrix.at<double>(2, 1) = 0;
	cameraMatrix.at<double>(2, 2) = 1;
	//
	distCoeffs.at<double>(0, 0) = -0.1569114923;
	distCoeffs.at<double>(0, 1) = 0.0902004093;
	distCoeffs.at<double>(0, 2) = 0.0047139050;
	distCoeffs.at<double>(0, 3) = -0.0022716345;
	Xworld.push_back(Point3f(-0.5, -0.5, 0));
	Xworld.push_back(Point3f(-0.5, 0.5, 0));
	Xworld.push_back(Point3f(0.5, 0.5, 0));
	Xworld.push_back(Point3f(0.5, -0.5, 0));
	WINDOW_SIZE = 0.5;
	//
	dstRect[0] = Point2f(83.3, 164.7);
	dstRect[1] = Point2f(191.9, 226.4);
	dstRect[2] = Point2f(185.5, 0);
	dstRect[3] = Point2f(291.4, 61.7);

}
OpenGL::~OpenGL()
{

}

void OpenGL::initializeGL()
{
	loadGLTextures();		//����ͼƬ�ļ�
	glEnable(GL_TEXTURE_2D);//��������
	glShadeModel(GL_SMOOTH);
	glClearColor(0, 0, 0.0, 0.0);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void OpenGL::initWidget()
{
	setGeometry(0, 0, IMAGE_WIDTH, IMAGE_HEIGHT);//���ô���λ�ü���С
	setWindowTitle(tr("opengl demo"));
}

void OpenGL::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();//��������ϵ����Ļ���� ��+��- ��-��+ ��-��+
	glTranslatef(3.2f, -0.6f, -100);//����ʾ������Z������ƶ��㹻���룬��ֹ�ڵ���Ⱦ����
	glScalef(8.35f, 8.35f, 1.0f);//ƽ�� �Ŵ� ʵ�ִ������-
	//������
	glBindTexture(GL_TEXTURE_2D, texturFrame);
	glBegin(GL_QUADS);//����ͼ�νӿڣ���glEnd()��Ӧ

	glTexCoord2f(0.0, 0.0); glVertex3f(-4, -3, 0);//
	glTexCoord2f(1.0, 0.0); glVertex3f(4, -3, 0);
	glTexCoord2f(1.0, 1.0); glVertex3f(4, 3, 0);
	glTexCoord2f(0.0, 1.0); glVertex3f(-4, 3, 0);

	glEnd();
	//���任����ͳһ������Ⱦ
	if (RotationMatrix.size())
	{
		for (int i = 0; i < RotationMatrix.size(); i++)
		{
			glLoadIdentity();//��������ϵ����Ļ���� ��+��- ��-��+ ��-��+
			for (int j = 0; j < 16; j++)
				rotMat[j] = RotationMatrix[i][j];
			glLoadMatrixd(rotMat);//���ر任����
			glTranslatef(0, 0, -WINDOW_SIZE);//�����������ƶ�WINDOW_SIZE����λ
			//glRotatef(m_x, 1.0, 0.0, 0.0);//��ת
			//glRotatef(m_y, 0.0, 1.0, 0.0);
			//glRotatef(m_z, 0.0, 0.0, 1.0);
			glBindTexture(GL_TEXTURE_2D, texturImage);
			//glLoadMatrixd();
			glBegin(GL_QUADS);//����ͼ�νӿڣ���glEnd()��Ӧ
			//glBegin(GL_LINE_STRIP);//����ͼ�νӿڣ���glEnd()��Ӧ
			/*�����������ӿں�����
			glTexCoord2f( x, y );
			glVertex3f( x, y, z );

			glTexCoord2f������ڱ�ʾԭͼƬ�����꣬������������⣬	������ ��x,y ���ƽ�����棬 ��0��0����ʾͼƬ�����½ǣ�
			��0��1�� ��ʾ���Ͻǣ� ��1��1����ʾ���Ͻǣ� ��1��0����ʾ���½ǡ�

			����Ӧ��glVertex3f���ӦΪ (-1, -1) , (-1, 1) , (1, 1), (1, -1)

			������ô��������ֶ�Ӧ��ϵ�أ���

			1.��Ҫ��ͼ���������һһ��Ӧ�������������˳ʱ��д����Ӧ������Ҫ˳ʱ�룬�����ʱ��д����Ӧ�����궼Ҫ��ʱ�룬һһ��Ӧ��
			2.���ǵ���ͼ��һ��ͼƬ��������һ����һ��ƽ�档��������ӣ�0��0����ʼ���������ʹ�á���������Ҫ��ͼ������ͼ�Σ�
			��Ȼÿ������ƽ��ͼ�Σ�����������ϵ�У�ʼ��������ͼ�ε�����Ϊ����ԭ�㣬���ԣ�����һ����ά���꣬��ά�������ά�Ķ�Ӧ����ֻ������ͬ��ƽ�涥��
			E��ת˳������Ӧ�ˡ�*/
			glNormal3f(0.0, 0.0, 1.0);
			glTexCoord2f(0.0, 0.0); glVertex3f(-WINDOW_SIZE, WINDOW_SIZE, WINDOW_SIZE);//
			glTexCoord2f(1.0, 0.0); glVertex3f(WINDOW_SIZE, -WINDOW_SIZE, WINDOW_SIZE);
			glTexCoord2f(1.0, 1.0); glVertex3f(WINDOW_SIZE, WINDOW_SIZE, WINDOW_SIZE);
			glTexCoord2f(0.0, 1.0); glVertex3f(-WINDOW_SIZE, WINDOW_SIZE, WINDOW_SIZE);

			glNormal3f(0.0, 0.0, -1.0);
			glTexCoord2f(1.0, 0.0); glVertex3f(-WINDOW_SIZE, -WINDOW_SIZE, -WINDOW_SIZE);
			glTexCoord2f(1.0, 1.0); glVertex3f(-WINDOW_SIZE, WINDOW_SIZE, -WINDOW_SIZE);
			glTexCoord2f(0.0, 1.0); glVertex3f(WINDOW_SIZE, WINDOW_SIZE, -WINDOW_SIZE);
			glTexCoord2f(0.0, 0.0); glVertex3f(WINDOW_SIZE, -WINDOW_SIZE, -WINDOW_SIZE);

			glNormal3f(0.0, 1.0, 0.0);
			glTexCoord2f(0.0, 1.0); glVertex3f(-WINDOW_SIZE, WINDOW_SIZE, -WINDOW_SIZE);
			glTexCoord2f(0.0, 0.0); glVertex3f(-WINDOW_SIZE, WINDOW_SIZE, WINDOW_SIZE);
			glTexCoord2f(1.0, 0.0); glVertex3f(WINDOW_SIZE, WINDOW_SIZE, WINDOW_SIZE);
			glTexCoord2f(1.0, 1.0); glVertex3f(WINDOW_SIZE, WINDOW_SIZE, -WINDOW_SIZE);

			glNormal3f(0.0, -1.0, 0.0);
			glTexCoord2f(1.0, 1.0); glVertex3f(-WINDOW_SIZE, -WINDOW_SIZE, -WINDOW_SIZE);
			glTexCoord2f(0.0, 1.0); glVertex3f(WINDOW_SIZE, -WINDOW_SIZE, -WINDOW_SIZE);
			glTexCoord2f(0.0, 0.0); glVertex3f(WINDOW_SIZE, -WINDOW_SIZE, WINDOW_SIZE);
			glTexCoord2f(1.0, 0.0); glVertex3f(-WINDOW_SIZE, -WINDOW_SIZE, WINDOW_SIZE);

			glNormal3f(1.0, 0.0, 0.0);
			glTexCoord2f(1.0, 0.0); glVertex3f(WINDOW_SIZE, -WINDOW_SIZE, -WINDOW_SIZE);
			glTexCoord2f(1.0, 1.0); glVertex3f(WINDOW_SIZE, WINDOW_SIZE, -WINDOW_SIZE);
			glTexCoord2f(0.0, 1.0); glVertex3f(WINDOW_SIZE, WINDOW_SIZE, WINDOW_SIZE);
			glTexCoord2f(0.0, 0.0); glVertex3f(WINDOW_SIZE, -WINDOW_SIZE, WINDOW_SIZE);

			glNormal3f(-1.0, 0.0, 0.0);
			glTexCoord2f(0.0, 0.0); glVertex3f(-WINDOW_SIZE, -WINDOW_SIZE, -WINDOW_SIZE);
			glTexCoord2f(1.0, 0.0); glVertex3f(-WINDOW_SIZE, -WINDOW_SIZE, WINDOW_SIZE);
			glTexCoord2f(1.0, 1.0); glVertex3f(-WINDOW_SIZE, WINDOW_SIZE, WINDOW_SIZE);
			glTexCoord2f(0.0, 1.0); glVertex3f(-WINDOW_SIZE, WINDOW_SIZE, -WINDOW_SIZE);

			glEnd();
		}
		RotationMatrix.clear();
	}
	//������Դ�ͷ�
	glDeleteTextures(1, &texturFrame);
	//glDeleteTextures(1, &texturImage);

	//glLoadIdentity();//��������ϵ����Ļ���� ��+��- ��-��+ ��-��+
}

void OpenGL::resizeGL(int width, int height)
{
	if (0 == height) {
		height = 1;
	}

	glViewport(0, 0, (GLint)width, (GLint)height);//���õ�ǰ��������ʾλ��
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);//ѡ�����ģʽ
	double f_x = cameraMatrix.at<double>(0, 0);
	double f_y = cameraMatrix.at<double>(1, 1);

	double c_x = cameraMatrix.at<double>(0, 2);
	double c_y = cameraMatrix.at<double>(1, 2);

	projection_matrix[0] = 2 * f_x / IMAGE_WIDTH;
	projection_matrix[1] = 0.0f;
	projection_matrix[2] = 0.0f;
	projection_matrix[3] = 0.0f;

	projection_matrix[4] = 0.0f;
	projection_matrix[5] = 2 * f_y / IMAGE_HEIGHT;
	projection_matrix[6] = 0.0f;
	projection_matrix[7] = 0.0f;

	projection_matrix[8] = 1.0f - 2 * c_x / IMAGE_WIDTH;
	projection_matrix[9] = 2 * c_y / IMAGE_HEIGHT - 1.0f;
	projection_matrix[10] = -(0.01f + 100.0f) / (100.0f - 0.01f);
	projection_matrix[11] = -1.0f;

	projection_matrix[12] = 0.0f;
	projection_matrix[13] = 0.0f;
	projection_matrix[14] = -2.0f * 100 * 0.01 / (100.0f - 0.01f);
	projection_matrix[15] = 0.0f;
	//��������ڲ�����ģ��
	glMultMatrixf(projection_matrix);

	//glLoadMatrixf(projection_matrix);
	//glEnableClientState(GL_VERTEX_ARRAY);  //���ÿͻ��˵�ĳ���
	//glEnableClientState(GL_NORMAL_ARRAY);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void OpenGL::updateWindow()
{
	//��ȡ����ͷͼ�񲢽��и�ʽת��
	cam >> frame; // imshow("frame",frame);
	cvtColor(frame, frame, CV_BGR2RGB);
	for (char i = 0; i < 4; i++)
	{
		circle(frame, srcRect[i], 8, Scalar(255, 0, 0), -1, 8, 0);
	}
	circle(frame, Point(dobotPos.at<double>(0, 0), dobotPos.at<double>(1, 0)), 5, Scalar(0, 255, 255), -1, 8);
	imageProcess(frame);
	QImage buf, tex;
	//��Mat����ת����QImage
	buf = QImage((const unsigned char*)frame.data, frame.cols, frame.rows, frame.cols * frame.channels(), QImage::Format_RGB888);
	tex = QGLWidget::convertToGLFormat(buf);
	glGenTextures(1, &texturFrame);//��ӦͼƬ��������
	glBindTexture(GL_TEXTURE_2D, texturFrame);//���������
	//������
	glTexImage2D(GL_TEXTURE_2D, 0, 3, tex.width(), tex.height(), 0,
		GL_RGBA, GL_UNSIGNED_BYTE, tex.bits());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	updateGL();

}
void OpenGL::imageProcess(Mat image)
{
	Mat grayImage, tempImage;
	cvtColor(image, grayImage, CV_BGR2GRAY);
	adaptiveThreshold(grayImage, tempImage, 255, ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY_INV, 7, 7);
	//imshow("��ֵ��",tempImage);
	vector<vector<Point>> all_contours;
	vector<vector<Point>> contours;
	//Rect RectArea;
	findContours(tempImage, all_contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
	for (int i = 0; i < all_contours.size(); ++i)
	{
		if (all_contours[i].size() > 100)
		{
			contours.push_back(all_contours[i]);
			//drawContours(frame,all_contours,i,Scalar(0,0,255),1,8);
		}
	}
	vector<Point> approxCurve;//���ؽ��Ϊ����Σ��õ㼯��ʾ//������״

	for (size_t i = 0; i < contours.size(); i++)
	{
		/*����һ������αƽ���Ϊ�˼������������ء������ȽϺã���ɸѡ���Ǳ��������Ϊ������ܱ��ĸ�����Ķ���α�ʾ���������εĶ�����ڻ������ĸ����;��Բ��Ǳ���Ŀ��Ҫ�ı�ǡ�ͨ���㼯���ƶ���Σ�����������Ϊepsilon������Ƴ̶ȣ���ԭʼ���������ƶ����֮��ľ��룬���ĸ�������ʾ������Ǳպϵġ�*/
		double eps = contours[i].size()*0.05;
		//����ͼ���2ά�㼯�������������ƾ��ȣ��Ƿ�պϡ��������εĶ�����ɵĵ㼯//ʹ����α�Եƽ�����õ����ƵĶ���� 
		approxPolyDP(contours[i], approxCurve, eps, true);

		//���Ǹ���Ȥ�Ķ����ֻ���ĸ�����
		if (approxCurve.size() != 4)
			continue;

		//��������Ƿ���͹����
		if (!isContourConvex(approxCurve))
			continue;

		//ȷ��������֮��ľ������㹻��ġ�//ȷ�����ڵ������ľ��롰�㹻�󡱣�����һ���߶����Ƕ��߶ξ�����
		//float minDist = numeric_limits<float>::max();//����float���Ա�ʾ�����ֵ��numeric_limits����ģ���࣬�����ʾmax��float��;3.4e038
		float minDist = 1e10;//���ֵ�ͺܴ���

		//��ǰ�ı��θ�����֮�����̾���
		for (int j = 0; j < 4; j++)
		{
			Point side = approxCurve[j] - approxCurve[(j + 1) % 4];//����Ӧ����2ά�����
			float squaredSideLength = side.dot(side);//��2ά�����ĵ��������XxY
			minDist = min(minDist, squaredSideLength);//�ҳ���С�ľ���
		}
		//�������ǲ����ر�С��С�Ļ����˳�����ѭ������ʼ��һ��ѭ��
		if (minDist < MIN_LENGTH*MIN_LENGTH)
			continue;
		//���еĲ���ͨ���ˣ������ʶ��ѡ�����ı��δ�С���ʣ��򽫸��ı���maker����possibleMarkers������ //�������Ƶı��   
		drawContours(frame, contours, i, Scalar(255, 0, 255), 1, 8);
		for (int j = 0; j < 4; j++){
			Ximage.push_back(approxCurve[j]);
		}
		// Sort the points in anti - clockwise
		Point2f v1 = Ximage[1] - Ximage[0];
		Point2f v2 = Ximage[2] - Ximage[0];
		if (v1.cross(v2) > 0)	//����ͼ�������Y�����£����Դ�����Ŵ�����ʱ��
		{
			swap(Ximage[1], Ximage[3]);
		}
		//possible_markers.push_back(marker);
		Mat rvec, tvec;
		solvePnP(Xworld, Ximage, cameraMatrix, distCoeffs, rvec, tvec);
		Mat rmat;
		Rodrigues(rvec, rmat);

		//��X����ת180�ȣ���OpenCV����ϵ�任ΪOpenGL����ϵ
		static double d[] =
		{
			1, 0, 0,
			0, -1, 0,
			0, 0, -1
		};
		Mat_<double> rx(3, 3, d);

		rmat = rx*rmat;
		tvec = rx*tvec;

		rotMatrix.push_back(rmat.at<double>(0, 0));
		rotMatrix.push_back(rmat.at<double>(1, 0));
		rotMatrix.push_back(rmat.at<double>(2, 0));
		rotMatrix.push_back(0.0f);

		rotMatrix.push_back(rmat.at<double>(0, 1));
		rotMatrix.push_back(rmat.at<double>(1, 1));
		rotMatrix.push_back(rmat.at<double>(2, 1));
		rotMatrix.push_back(0.0f);

		rotMatrix.push_back(rmat.at<double>(0, 2));
		rotMatrix.push_back(rmat.at<double>(1, 2));
		rotMatrix.push_back(rmat.at<double>(2, 2));
		rotMatrix.push_back(0.0f);

		rotMatrix.push_back(tvec.at<double>(0, 0));
		rotMatrix.push_back(tvec.at<double>(1, 0));
		rotMatrix.push_back(tvec.at<double>(2, 0));
		rotMatrix.push_back(1.0f);

		RotationMatrix.push_back(rotMatrix);
		//RotMat.pop_back(rotMatrix);
		Ximage.clear();
		rotMatrix.clear();
	}
}
void OpenGL::updateParams(int timerValue)
{
	clk.start(timerValue);
}
void OpenGL::loadGLTextures()
{
	QImage tex;
	QImage buf;

	if (!buf.load("E:\\qt\\QtOpenGL\\qtOpenGL\\QtOpenGL\\Resources\\butterfly.jpg"))
	{
		qWarning("load image failed!");
		QImage dummy(128, 128, QImage::Format_RGB32);
		dummy.fill(Qt::green);
		buf = dummy;

	}

	tex = QGLWidget::convertToGLFormat(buf);
	glGenTextures(1, &texturImage);//��ӦͼƬ��������
	glBindTexture(GL_TEXTURE_2D, texturImage);//���������
	//������
	glTexImage2D(GL_TEXTURE_2D, 0, 3, tex.width(), tex.height(), 0,
		GL_RGBA, GL_UNSIGNED_BYTE, tex.bits());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	/*
	//������Ƶ����
	video >> frame; cvtColor(frame, frame, CV_BGR2RGB);
	buf = QImage((const unsigned char*)frame.data, frame.cols, frame.rows, frame.cols * frame.channels(), QImage::Format_RGB888);
	tex = QGLWidget::convertToGLFormat(buf);
	glGenTextures(1, &texturImage);//��ӦͼƬ��������
	glBindTexture(GL_TEXTURE_2D, texturImage);//���������
	//������
	glTexImage2D(GL_TEXTURE_2D, 0, 3, tex.width(), tex.height(), 0,
	GL_RGBA, GL_UNSIGNED_BYTE, tex.bits());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);*/
}
void OpenGL::mousePressEvent(QMouseEvent *mouseEvent)
{
	switch (mouseEvent->button())
	{
	case Qt::LeftButton:
	{
		if (number < 4)
		{
			srcRect[number].x = float(mouseEvent->windowPos().x());//��¼��ʼ��
			srcRect[number].y = float(mouseEvent->windowPos().y());//��¼��ʼ��
			number++;

			if (number == 4)
				warpMat = getPerspectiveTransform(srcRect, dstRect);
		}
		else
		{
			dobotPos.at<double>(0, 0) = mouseEvent->windowPos().x();
			dobotPos.at<double>(1, 0) = mouseEvent->windowPos().y();
			dobotPos.at<double>(2, 0) = 1;
			dobotTargetPos = warpMat*dobotPos;//����ӳ�����
			double s = dobotTargetPos.at<double>(2, 0);
			dobotFinalTargetPos.x = dobotTargetPos.at<double>(0, 0) / s;
			dobotFinalTargetPos.y = dobotTargetPos.at<double>(1, 0) / s;
		}
	}
	break;
	default:
		break;
	}
}