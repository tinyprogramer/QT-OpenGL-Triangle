#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>


class MyWidget : public QOpenGLWidget,protected QOpenGLFunctions
{

    Q_OBJECT

public:
    MyWidget(QWidget* parent=0);
    ~MyWidget();

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;

private:
    QOpenGLShaderProgram* program;
    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer m_vbo;

    int m_attr;
    int m_color;


};

#endif // MYWIDGET_H
