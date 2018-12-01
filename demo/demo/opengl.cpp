#include "opengl.h"

OpenGL::OpenGL(QWidget *parent)
	: QGLWidget(parent), number(0)
{
	cam.open(0);
	//cam.set(CV_CAP_PROP_FRAME_WIDTH, IMAGE_WIDTH);
	//cam.set(CV_CAP_PROP_FRAME_HEIGHT, IMAGE_HEIGHT);
	//video.open("F:\\MOVIE\\NBA\\2016年06月20日 NBA总决赛 骑士VS勇士 ILP 720P 30fps.mp4");
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
	loadGLTextures();		//加载图片文件
	glEnable(GL_TEXTURE_2D);//启用纹理
	glShadeModel(GL_SMOOTH);
	glClearColor(0, 0, 0.0, 0.0);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void OpenGL::initWidget()
{
	setGeometry(0, 0, IMAGE_WIDTH, IMAGE_HEIGHT);//设置窗口位置及大小
	setWindowTitle(tr("opengl demo"));
}

void OpenGL::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();//重置坐标系至屏幕中央 上+下- 左-右+ 里-外+
	glTranslatef(3.2f, -0.6f, -100);//讲显示背景沿Z轴向后移动足够距离，防止遮挡渲染物体
	glScalef(8.35f, 8.35f, 1.0f);//平移 放大 实现窗口填充-
	//绑定纹理
	glBindTexture(GL_TEXTURE_2D, texturFrame);
	glBegin(GL_QUADS);//绘制图形接口，与glEnd()对应

	glTexCoord2f(0.0, 0.0); glVertex3f(-4, -3, 0);//
	glTexCoord2f(1.0, 0.0); glVertex3f(4, -3, 0);
	glTexCoord2f(1.0, 1.0); glVertex3f(4, 3, 0);
	glTexCoord2f(0.0, 1.0); glVertex3f(-4, 3, 0);

	glEnd();
	//将变换矩阵统一进行渲染
	if (RotationMatrix.size())
	{
		for (int i = 0; i < RotationMatrix.size(); i++)
		{
			glLoadIdentity();//重置坐标系至屏幕中央 上+下- 左-右+ 里-外+
			for (int j = 0; j < 16; j++)
				rotMat[j] = RotationMatrix[i][j];
			glLoadMatrixd(rotMat);//加载变换矩阵
			glTranslatef(0, 0, -WINDOW_SIZE);//将物体向外移动WINDOW_SIZE个单位
			//glRotatef(m_x, 1.0, 0.0, 0.0);//旋转
			//glRotatef(m_y, 0.0, 1.0, 0.0);
			//glRotatef(m_z, 0.0, 0.0, 1.0);
			glBindTexture(GL_TEXTURE_2D, texturImage);
			//glLoadMatrixd();
			glBegin(GL_QUADS);//绘制图形接口，与glEnd()对应
			//glBegin(GL_LINE_STRIP);//绘制图形接口，与glEnd()对应
			/*这里有两个接口函数：
			glTexCoord2f( x, y );
			glVertex3f( x, y, z );

			glTexCoord2f这个用于表示原图片的坐标，这样更容易理解，	就是以 在x,y 轴的平面里面， （0，0）表示图片的左下角，
			（0，1） 表示左上角， （1，1）表示右上角， （1，0）表示右下角。

			而对应的glVertex3f则对应为 (-1, -1) , (-1, 1) , (1, 1), (1, -1)

			我们怎么来理解这种对应关系呢？？

			1.需要贴图的坐标必须一一对应，就是我们如果顺时针写，对应的坐都要顺时针，如果逆时针写，对应的坐标都要逆时针，一一对应。
			2.我们的贴图是一张图片，所以它一定是一个平面。所以坐标从（0，0）开始，这个容易使用。而我们需要贴图的立体图形，
			虽然每个面是平面图形，但它在坐标系中，始终以立体图形的中心为坐标原点，所以，它是一个三维坐标，三维坐标与二维的对应，就只有以相同的平面顶点
			E旋转顺序来对应了。*/
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
	//纹理资源释放
	glDeleteTextures(1, &texturFrame);
	//glDeleteTextures(1, &texturImage);

	//glLoadIdentity();//重置坐标系至屏幕中央 上+下- 左-右+ 里-外+
}

void OpenGL::resizeGL(int width, int height)
{
	if (0 == height) {
		height = 1;
	}

	glViewport(0, 0, (GLint)width, (GLint)height);//重置当前的物体显示位置
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);//选择矩阵模式
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
	//导入相机内部参数模型
	glMultMatrixf(projection_matrix);

	//glLoadMatrixf(projection_matrix);
	//glEnableClientState(GL_VERTEX_ARRAY);  //启用客户端的某项功能
	//glEnableClientState(GL_NORMAL_ARRAY);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void OpenGL::updateWindow()
{
	//获取摄像头图像并进行格式转换
	cam >> frame; // imshow("frame",frame);
	cvtColor(frame, frame, CV_BGR2RGB);
	for (char i = 0; i < 4; i++)
	{
		circle(frame, srcRect[i], 8, Scalar(255, 0, 0), -1, 8, 0);
	}
	circle(frame, Point(dobotPos.at<double>(0, 0), dobotPos.at<double>(1, 0)), 5, Scalar(0, 255, 255), -1, 8);
	imageProcess(frame);
	QImage buf, tex;
	//将Mat类型转换成QImage
	buf = QImage((const unsigned char*)frame.data, frame.cols, frame.rows, frame.cols * frame.channels(), QImage::Format_RGB888);
	tex = QGLWidget::convertToGLFormat(buf);
	glGenTextures(1, &texturFrame);//对应图片的纹理定义
	glBindTexture(GL_TEXTURE_2D, texturFrame);//进行纹理绑定
	//纹理创建
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
	//imshow("二值化",tempImage);
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
	vector<Point> approxCurve;//返回结果为多边形，用点集表示//相似形状

	for (size_t i = 0; i < contours.size(); i++)
	{
		/*近似一个多边形逼近，为了减少轮廓的像素。这样比较好，可筛选出非标记区域，因为标记总能被四个顶点的多边形表示。如果多边形的顶点多于或少于四个，就绝对不是本项目想要的标记。通过点集近似多边形，第三个参数为epsilon代表近似程度，即原始轮廓及近似多边形之间的距离，第四个参数表示多边形是闭合的。*/
		double eps = contours[i].size()*0.05;
		//输入图像的2维点集，输出结果，估计精度，是否闭合。输出多边形的顶点组成的点集//使多边形边缘平滑，得到近似的多边形 
		approxPolyDP(contours[i], approxCurve, eps, true);

		//我们感兴趣的多边形只有四个顶点
		if (approxCurve.size() != 4)
			continue;

		//检查轮廓是否是凸边形
		if (!isContourConvex(approxCurve))
			continue;

		//确保连续点之间的距离是足够大的。//确保相邻的两点间的距离“足够大”－大到是一条边而不是短线段就是了
		//float minDist = numeric_limits<float>::max();//代表float可以表示的最大值，numeric_limits就是模板类，这里表示max（float）;3.4e038
		float minDist = 1e10;//这个值就很大了

		//求当前四边形各顶点之间的最短距离
		for (int j = 0; j < 4; j++)
		{
			Point side = approxCurve[j] - approxCurve[(j + 1) % 4];//这里应该是2维的相减
			float squaredSideLength = side.dot(side);//求2维向量的点积，就是XxY
			minDist = min(minDist, squaredSideLength);//找出最小的距离
		}
		//检查距离是不是特别小，小的话就退出本次循环，开始下一次循环
		if (minDist < MIN_LENGTH*MIN_LENGTH)
			continue;
		//所有的测试通过了，保存标识候选，当四边形大小合适，则将该四边形maker放入possibleMarkers容器内 //保存相似的标记   
		drawContours(frame, contours, i, Scalar(255, 0, 255), 1, 8);
		for (int j = 0; j < 4; j++){
			Ximage.push_back(approxCurve[j]);
		}
		// Sort the points in anti - clockwise
		Point2f v1 = Ximage[1] - Ximage[0];
		Point2f v2 = Ximage[2] - Ximage[0];
		if (v1.cross(v2) > 0)	//由于图像坐标的Y轴向下，所以大于零才代表逆时针
		{
			swap(Ximage[1], Ximage[3]);
		}
		//possible_markers.push_back(marker);
		Mat rvec, tvec;
		solvePnP(Xworld, Ximage, cameraMatrix, distCoeffs, rvec, tvec);
		Mat rmat;
		Rodrigues(rvec, rmat);

		//绕X轴旋转180度，从OpenCV坐标系变换为OpenGL坐标系
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
	glGenTextures(1, &texturImage);//对应图片的纹理定义
	glBindTexture(GL_TEXTURE_2D, texturImage);//进行纹理绑定
	//纹理创建
	glTexImage2D(GL_TEXTURE_2D, 0, 3, tex.width(), tex.height(), 0,
		GL_RGBA, GL_UNSIGNED_BYTE, tex.bits());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	/*
	//加载视频纹理
	video >> frame; cvtColor(frame, frame, CV_BGR2RGB);
	buf = QImage((const unsigned char*)frame.data, frame.cols, frame.rows, frame.cols * frame.channels(), QImage::Format_RGB888);
	tex = QGLWidget::convertToGLFormat(buf);
	glGenTextures(1, &texturImage);//对应图片的纹理定义
	glBindTexture(GL_TEXTURE_2D, texturImage);//进行纹理绑定
	//纹理创建
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
			srcRect[number].x = float(mouseEvent->windowPos().x());//记录起始点
			srcRect[number].y = float(mouseEvent->windowPos().y());//记录起始点
			number++;

			if (number == 4)
				warpMat = getPerspectiveTransform(srcRect, dstRect);
		}
		else
		{
			dobotPos.at<double>(0, 0) = mouseEvent->windowPos().x();
			dobotPos.at<double>(1, 0) = mouseEvent->windowPos().y();
			dobotPos.at<double>(2, 0) = 1;
			dobotTargetPos = warpMat*dobotPos;//计算映射矩阵
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