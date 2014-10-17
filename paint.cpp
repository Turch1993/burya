#include "paint.h"

void paint::initializeGL()
{
    glClearColor(222,222,222,1);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_FLAT);
    fsize=1.2f;
    scale=1.0f;
    m_nPyramid=createPyramid(fsize);
}

void paint::resizeGL(int nWidth, int nHeight)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0,0,(GLint)nWidth, (GLint)nHeight);
    glOrtho(-2.0,2.0,-2.0,2.0,2.0,15.0);
    //glFrustum(-1.0,1.0,-1.0,1.0,1.0,10.0);
}

void paint::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0,0.0,-5.0);
    m_xRotate=20;
    glRotatef(m_xRotate, 1.0,0.0,0.0);
    glRotatef(m_yRotate, 0.0,1.0,0.0);
    glScalef(scale, scale, scale);
    glCallList(m_nPyramid);
}

void paint::mousePressEvent(QMouseEvent *pe)
{
    m_ptPosition = pe->pos();
}

void paint::mouseMoveEvent(QMouseEvent *pe)
{
    m_xRotate+=180*(GLfloat)(pe->y()-m_ptPosition.y())/height();
    m_yRotate+=180*(GLfloat)(pe->x()-m_ptPosition.x())/width();
    updateGL();
    m_ptPosition=pe->pos();
}

GLuint paint::createPyramid(GLfloat fsize)
{
    GLuint n = glGenLists(1);
    glNewList(n, GL_COMPILE);
    int k = 60;
    double x, z;
    double x1, z1;
    double alpha = 0;
    double da = 360/k;
    glBegin(GL_QUAD_STRIP);
    for(int i = 0; i < k; i++)
    {
        x = cos(alpha+da*i);
        z = -sin(alpha+da*i);
        x1 = cos(alpha+da*(i+1));
        z1 = -sin(alpha+da*(i+1));
        qglColor(Qt::green);
        glVertex3d( x,  fsize, z);
        glVertex3d( x, -fsize, z);
        glVertex3d( x1, fsize, z1);
        glVertex3d( x1,-fsize, z1);
    }
    glEnd();
    qglColor(Qt::black);
    glBegin(GL_LINES);
    da=90;
    for (int i=0; i<4; i++)
    {
        x=cos(da*i);
        z=-sin(da*i);
        glVertex3d(x, fsize, z);
        glVertex3d(x, -fsize, z);
    }
    glEnd();
    da=360/k;
    glBegin(GL_TRIANGLES);
    for( int i = 0; i < k; i++ )
    {
        x = cos(alpha+da*i);
        z = -sin(alpha+da*i);
        x1 = cos(alpha+da*(i+1));
        z1 = -sin(alpha+da*(i+1));
        glColor3f(0.0f,0.0f,1.0f);
        glVertex3d( x,  fsize, z);
        glVertex3d( 0,  fsize, 0);
        glVertex3d( x1, fsize, z1);
        glVertex3d( x,  -fsize, z);
        glVertex3d( 0,  -fsize, 0);
        glVertex3d( x1, -fsize, z1);
    }
    glEnd();
    glEndList();
    return n;
}

void paint::wheelEvent(QWheelEvent *p)
{
    if (p->delta()>0)
    {
        scale=scale+0.01;
    }
    else
    {
        scale=scale-0.01;
    }
    updateGL();
}

void paint::keyPressEvent(QKeyEvent *k)
{
    if (k->key()==Qt::Key_Left)
    {
        m_yRotate+=5;
    }
    else if (k->key()==Qt::Key_Right)
    {
        m_yRotate-=5;
    }
    updateGL();
}
