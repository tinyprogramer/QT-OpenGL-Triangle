#include "mywidget.h"
#include <QDebug>


static GLfloat vertices[] = {//我们所准备的需要提供给openGL的顶点数据
    // 位置              // 颜色
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部
};



MyWidget::MyWidget(QWidget* parent)
    :QOpenGLWidget(parent)
{

}

MyWidget::~MyWidget()
//建议在析构函数中手动销毁openGL相关的对象，
//文档中特意提到QT的回收机制难以保证回收所有openGL使用的资源
//不销毁的话在关闭程序时可能会出现异常
{
    makeCurrent();
    m_vao.destroy();
    m_vbo.destroy();
    doneCurrent();
}


void MyWidget::initializeGL()
{

    initializeOpenGLFunctions();


    // 创建并绑定着色器程序
    program = new QOpenGLShaderProgram;
    program->bind();
    //向program中添加顶点着色器
    if(!program->addShaderFromSourceFile(QOpenGLShader::Vertex,":/triangle.vert"))
    {
        qDebug()<< (program->log());
        return;
    }
    //向program中添加片段着色器
    if(!program->addShaderFromSourceFile(QOpenGLShader::Fragment,":/triangle.frag"))
    {
        qDebug()<< (program->log());
        return;
    }
    if(!program->link())
    {
        qDebug()<< (program->log());
        return;
    }

    //创建并绑定VAO
    m_vao.create();
    m_vao.bind();

    //创建并绑定VBO
    m_vbo.create();
    m_vbo.bind();
    m_vbo.allocate(vertices, sizeof(vertices));//向VBO传递我们准备好的数据(本文件起始部分的静态数组)

    //向顶点着色器传递其中定义为"aPos"的变量所需的数据
    m_attr=program->attributeLocation("aPos");
    program->setAttributeBuffer(m_attr,GL_FLOAT, 0, 3,6*sizeof(GLfloat));
    program->enableAttributeArray(m_attr);

    //向顶点着色器传递其中定义为"aColor"的变量所需的数据
    m_color=program->attributeLocation("aColor");
    program->setAttributeBuffer(m_color,GL_FLOAT,3*sizeof(GLfloat),3,6*sizeof(GLfloat));
    program->enableAttributeArray(m_color);

    program->release();//解绑程序

}

void MyWidget::paintGL()
{
    //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    //glClear(GL_COLOR_BUFFER_BIT);


    program->bind();//绑定绘制所要使用的openGL程序
    m_vao.bind();//绑定包含openGL程序所需信息的VAO

    glDrawArrays(GL_TRIANGLES, 0, 3);//绘制
    m_vao.release();//解绑VAO
    program->release();//解绑程序

    //update();//调用update()函数会执行paintGL，现在绘制一个静态的三角形可以不使用
    //也可以用定时器连接update()函数来控制帧率，直接在paintGL函数中调用update()大概是60帧
}

void MyWidget::resizeGL(int width, int height)
{

}
