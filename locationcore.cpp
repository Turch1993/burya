#include "locationcore.h"

locationCore::locationCore()
{
}

//#include <painter.h>
#include <math.h>
#include <iostream>
using namespace std;

const double v=1000;               // скорость АЭ волны в ОК
const double maxStep=10;
const double pi05 = M_PI/2;
const double pi2 = M_PI*2;
const double grad001 = M_PI/18000;
const double grad01 = M_PI/1800;
const double grad1 = M_PI/180;
const double grad2 = M_PI/90;
const double grad3 = M_PI/60;
const double grad5 = M_PI/36;
const double gra10 = M_PI/18;
const double grad15 = M_PI/12;
const double grad30 = M_PI/6;

double xSensors[3];
double ySensors[3];
double t[3];                       // время регистрации АЭ сигнала датчиками
double xLast;
double yLast;
double xx;
double yy;
double s12;
double s13;
double lastMainMistake;
double lastHelpMistake;
double mainMistake;
double helpMistake;
double deltaAlpha;
double lastDeltaAlpha;
double lastDirection;
double direction;
double beginDirection;
double step;
double lastStep;
double distanceToSource[3];
double a;
double a1;
double c;
bool isFindSource;
int clock=1;
int countN;
int countI;
int countStep;
int m=15;

inline void correctDirection()
{
    if (direction>M_PI)
    {
        direction=direction-pi2;
    }
    if (direction<-M_PI)
    {
        direction=direction+pi2;
    }
}

inline int getSgn (double k)
{
    if(k>0)
    {
        return 1;
    }
    else if (k<0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

inline void computeDistanceToSource()
{
    for (int i=0; i<=2; i++)
    distanceToSource[i]=sqrt(pow((xx-xSensors[i]),2)+pow((yy-ySensors[i]),2));
}

inline void computeMistakes ()
{
    computeDistanceToSource();
    mainMistake = distanceToSource[1]-distanceToSource[0]-(t[1]-t[0])*v;
    helpMistake = distanceToSource[2]-distanceToSource[0]-(t[2]-t[0])*v;
}

inline void computeDirection (double x1, double y1, double x2, double y2, double ratio)
{
    double dx;
    double dy;
    dx=x2-x1;
    dy=y2-y1;
    xx=x1+dx*ratio;
    yy=y1+dy*ratio;
    if (dx==0)
    {
        direction = pi05*getSgn(dy);
    }
    else
    {
        direction=atan(dy/dx);
    }
    if (dx<0)
    {
        direction = direction-M_PI;
    }
    direction=direction-pi05;
    correctDirection();
}

inline void computeCoordinateAfterStep (double x1, double y1, double direction1, double step1)
{
    xx=x1+step1*cos(direction1);
    yy=y1+step1*sin(direction1);
}
void paint()
//void painter::paintEvent(QPaintEvent *event)
{
    //QPainter p(this);
    //p.translate(100,100);
    /*Тест 1 20;15
    t[0]=0.01118;
    t[1]=0.01;
    t[2]=0.025;
    xSensors[0]=10;ySensors[0]=20;
    xSensors[1]=20;ySensors[1]=5;
    xSensors[2]=40;ySensors[2]=30;*/
    //Тест 2 15;45
    t[0]=0.025495;
    t[1]=0.02031;
    t[2]=0.02915;
    xSensors[0]=10;ySensors[0]=20;
    xSensors[1]=20;ySensors[1]=5;
    xSensors[2]=40;ySensors[2]=30;

   /* t[0]=0.025495;
    t[1]=0.02031;
    t[2]=0.02915;
    xSensors[0]=10;ySensors[0]=20;
    xSensors[1]=20;ySensors[1]=5;
    xSensors[2]=40;ySensors[2]=30;*/
    /*for (int i=0; i<=50; i++)
    {
        if ((i%10)==0)
        {
            p.setPen(QPen(Qt::black, 2, Qt::SolidLine));
            p.drawLine(i*m, 0, i*m, 50*m);
            p.drawLine(0, i*m, 50*m, i*m);
        }
        else
        {
            p.setPen(QPen(Qt::black, 1, Qt::SolidLine));
            p.drawLine(i*m, 0, i*m, 50*m);
            p.drawLine(0, i*m, 50*m, i*m);
        }
    }
    p.setPen(QPen(Qt::blue, 2, Qt::DashLine));
    p.drawLine(xSensors[0]*m,ySensors[0]*m,xSensors[1]*m,ySensors[1]*m);
    p.drawLine(xSensors[1]*m,ySensors[1]*m,xSensors[2]*m,ySensors[2]*m);
    p.drawLine(xSensors[0]*m,ySensors[0]*m,xSensors[2]*m,ySensors[2]*m);
    p.setPen(QPen(Qt::red, 5, Qt::SolidLine));
    p.drawPoint(xSensors[0]*m,ySensors[0]*m);
    p.drawPoint(xSensors[1]*m,ySensors[1]*m);
    p.drawPoint(xSensors[2]*m,ySensors[2]*m);
    p.setPen(QPen(Qt::yellow, 1, Qt::SolidLine));*/
    isFindSource=false;
    s12=sqrt(pow((xSensors[1]-xSensors[0]),2)+pow((ySensors[1]-ySensors[0]),2));
    s13=sqrt(pow((xSensors[2]-xSensors[0]),2)+pow((ySensors[2]-ySensors[0]),2));
    a=(s12-(t[1]-t[0])*v)/2;
    a1=a/s12;
    computeDirection(xSensors[0], ySensors[0], xSensors[1], ySensors[1], a1);
    xLast=xx;
    yLast=yy;
    lastDirection=direction;
    beginDirection=direction;
    deltaAlpha=M_PI/90;
    step=1;
    lastStep=step;
    clock=1;
    computeMistakes();
    if (fabs(helpMistake)<0.1)
    {
        isFindSource=true;
    }
    lastHelpMistake=helpMistake;
    computeCoordinateAfterStep(xLast, yLast, direction, step);
    computeMistakes();
    //p.drawLine(xx*m,yy*m,xLast*m,yLast*m);
    if (getSgn(lastHelpMistake)*getSgn(helpMistake)<0)
    {
        lastStep=step;
        step=step*fabs(lastHelpMistake)/(fabs(lastHelpMistake)+fabs(helpMistake));
        if (step<2)
        {
            isFindSource=true;
        }
        lastMainMistake=mainMistake*step/lastStep;
        deltaAlpha=grad5*getSgn(mainMistake)*clock;
        direction=beginDirection+deltaAlpha;
        correctDirection();
    }
    else
    {
        c=helpMistake;
        direction=beginDirection+M_PI;
        correctDirection();
        computeCoordinateAfterStep(xLast, yLast, direction, step);
        computeMistakes();
        //p.drawLine(xx*m,yy*m,xLast*m,yLast*m);
        if (getSgn(lastHelpMistake)*getSgn(helpMistake)<0)
        {
            clock=-1;
            lastStep=step;
            step=step*fabs(lastHelpMistake)/(fabs(lastHelpMistake)+fabs(helpMistake));
            if (step<2)
            {
                isFindSource=true;
            }
            lastMainMistake=mainMistake*step/lastStep;
            deltaAlpha=grad5*getSgn(mainMistake)*clock;
            beginDirection=direction;
            lastDirection=direction;
            direction=direction+deltaAlpha;
            correctDirection();
        }
        else
        {
            if (fabs(c)<fabs(helpMistake))
            {
                lastMainMistake=mainMistake;
                deltaAlpha=grad5*getSgn(mainMistake)*clock;
                direction=beginDirection+deltaAlpha;
                correctDirection();
            }
            else
            {
                clock=-1;
                lastMainMistake=mainMistake;
                deltaAlpha=grad5*getSgn(mainMistake)*clock;
                beginDirection=direction;
                lastDirection=direction;
                direction=direction+deltaAlpha;
                correctDirection();
            }
        }

    }

  while ((!isFindSource)&&(countI<=200)&&(countN<=20))
  {
      countI=countI+1;
      countN=countN+1;
      computeCoordinateAfterStep(xLast, yLast, direction, step);
      computeMistakes();
      //p.drawLine(xx*m,yy*m,xLast*m,yLast*m);
      if (fabs(mainMistake)>0.1)
      {
          if ((getSgn(lastMainMistake)*getSgn(mainMistake))>0)
          {
              lastDeltaAlpha=deltaAlpha;
              if (fabs(mainMistake)<fabs(lastMainMistake))
              {
                  deltaAlpha=deltaAlpha*fabs(mainMistake)/(fabs(lastMainMistake)-fabs(mainMistake));
                  lastDirection=direction;
                  lastMainMistake=mainMistake;
              }
              else
              {
                  deltaAlpha=-deltaAlpha*fabs(lastMainMistake)/(fabs(mainMistake)-fabs(lastMainMistake));
              }
              if (fabs(deltaAlpha)>(2*fabs(lastDeltaAlpha)))
              {
                  deltaAlpha=2*getSgn(deltaAlpha)*fabs(lastDeltaAlpha);
              }
              if (fabs(deltaAlpha)>grad15)
              {
                  deltaAlpha=getSgn(deltaAlpha)*grad15;
              }
          }
          else
          {
              if (fabs(lastMainMistake)>fabs(mainMistake))
              {
                  deltaAlpha=deltaAlpha*fabs(mainMistake)/(fabs(lastMainMistake)+fabs(mainMistake));
                  deltaAlpha=-deltaAlpha;
                  lastDirection=direction;
                  lastMainMistake=mainMistake;
              }
              else
              {
                  deltaAlpha=deltaAlpha*fabs(lastMainMistake)/(fabs(lastMainMistake)+fabs(mainMistake));
              }
          }
          direction=lastDirection+deltaAlpha;
          correctDirection();
          continue;
      }
      else
      {
          if (fabs(helpMistake)<0.1)
          {
              isFindSource=true;
              break;
          }
          if ((getSgn(lastHelpMistake)*getSgn(helpMistake))<0)
          {
              lastStep=step;
              step=step*fabs(lastHelpMistake)/(fabs(lastHelpMistake)+fabs(helpMistake));
              if ((lastStep-step)<2)
              {
                  isFindSource=true;
                  break;
              }
              countN=0;
          }
          else
          {
              if (fabs(lastHelpMistake)<fabs(helpMistake))
              {
                  if (countStep==0)
                  {
                      deltaAlpha=direction-beginDirection;
                      correctDirection();
                      deltaAlpha=-deltaAlpha;
                      beginDirection=beginDirection+M_PI;
                      if (beginDirection>M_PI)
                      {
                          beginDirection=beginDirection-pi2;
                      }
                      if (beginDirection<-M_PI)
                      {
                          beginDirection=beginDirection+pi2;
                      }
                      direction=beginDirection+deltaAlpha;
                      lastDeltaAlpha=beginDirection;
                      countStep=countStep+1;
                      clock=-1*clock;
                      continue;
                  }
                  break;
              }
              else
              {
                  lastDirection=direction;
                  lastStep=step;
                  step=step*fabs(helpMistake)/fabs(lastHelpMistake-helpMistake);
                  if (step<2)
                  {
                      isFindSource=true;
                      break;
                  }
                  if (step>(lastStep*2))
                  {
                      step=lastStep*2;
                  }
                  if (step>maxStep)
                  {
                      step=maxStep;
                  }
              }
          }
      }
      beginDirection=direction;
      lastDirection=direction;
      lastHelpMistake=helpMistake;
      xLast=xx;
      yLast=yy;
      countStep=countStep+1;
      countN=0;
      computeCoordinateAfterStep(xLast, yLast, direction, step);
      computeMistakes();
      //p.drawLine(xx*m,yy*m,xLast*m,yLast*m);
      lastMainMistake=mainMistake;
      lastDirection=direction;
      deltaAlpha=grad1*mainMistake*clock;
      if (fabs(deltaAlpha)<grad01)
      {
          deltaAlpha=grad01*getSgn(deltaAlpha);
      }
      if (fabs(deltaAlpha)>grad5)
      {
          deltaAlpha=grad5*getSgn(deltaAlpha);
      }
  }
  if (isFindSource)
  {
  //p.setPen(QPen(Qt::green, 5, Qt::SolidLine));
  //p.drawPoint(xx*m,yy*m);
  cout<<xx<<";"<<yy<<endl;
  cout<<countI<<endl;
  countI=0;
  }
}
