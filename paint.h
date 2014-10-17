#ifndef PAINT_H
#define PAINT_H

#include <header.h>

class paint: public QGLWidget
{

private:
    GLuint m_nPyramid;
    GLfloat m_xRotate;
    GLfloat m_yRotate;
    QPoint m_ptPosition;
    GLfloat fsize;
    GLfloat scale;

protected:
    virtual void initializeGL();
    virtual void resizeGL(int nWidth, int nHeight);
    virtual void paintGL();
    virtual void mousePressEvent(QMouseEvent *pe);
    virtual void mouseMoveEvent(QMouseEvent *pe);
    virtual void wheelEvent(QWheelEvent *p);
    virtual void keyPressEvent(QKeyEvent *k);
    GLuint createPyramid (GLfloat fsize);
};

#endif // PAINT_H
