#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include"cspline.h"

void Cspline::release()
{
  freeAndNil(x);
  freeAndNil(y);
  freeAndNil(s);
  freeAndNil(Mx);
  freeAndNil(My);
  freeAndNil(slope);
  freeAndNil(ax);
  freeAndNil(ay);
  freeAndNil(bx);
  freeAndNil(by);
  freeAndNil(cx);
  freeAndNil(cy);
  freeAndNil(dx);
  freeAndNil(dy);
}

void Cspline::freeAndNil(double *array)
{
  if(NULL != array)
    {
      free(array);
    }
  array = NULL;
}

void Cspline::initArray()
{
  x=(double *)malloc(sizeof(double)*m_nCount);
  y=(double *)malloc(sizeof(double)*m_nCount);
  s=(double *)malloc(sizeof(double)*m_nCount);
  ax=(double *)malloc(sizeof(double)*(m_nCount-1));
  ay=(double *)malloc(sizeof(double)*(m_nCount-1));
  bx=(double *)malloc(sizeof(double)*(m_nCount-1));
  by=(double *)malloc(sizeof(double)*(m_nCount-1));
  cx=(double *)malloc(sizeof(double)*(m_nCount-1));
  cy=(double *)malloc(sizeof(double)*(m_nCount-1));
  dx=(double *)malloc(sizeof(double)*(m_nCount-1));
  dy=(double *)malloc(sizeof(double)*(m_nCount-1));
  Mx=(double *)malloc(sizeof(double)*m_nCount);
  My=(double *)malloc(sizeof(double)*m_nCount);
  slope=(double *)malloc(sizeof(double)*m_nCount);
}

void Cspline::gen(double *xcoor,double *ycoor,int n)
{
  double af,a0,az,hj;
  double *u=NULL,*ru=NULL,*fx=NULL,*fy=NULL,*beta=NULL,*yx=NULL,*yy=NULL;
  m_nCount = n;

  release();
  initArray();
  
  u=(double *)malloc(sizeof(double)*m_nCount);
  ru=(double *)malloc(sizeof(double)*m_nCount);
  fx=(double *)malloc(sizeof(double)*m_nCount);
  fy=(double *)malloc(sizeof(double)*m_nCount);
  beta=(double *)malloc(sizeof(double)*m_nCount);
  yx=(double *)malloc(sizeof(double)*m_nCount);
  yy=(double *)malloc(sizeof(double)*m_nCount);
  
  for(int i=0; i<m_nCount; i++)
    {
      x[i]=xcoor[i];
      y[i]=ycoor[i];
    }
  s[0]=0;
  for(int i=1; i<m_nCount; i++)
    {
      s[i]=s[i-1]+CH(x[i],x[i-1],y[i],y[i-1]);
    }
  u[0]=0;
  u[m_nCount-1]=0;
  ru[0]=0;
  ru[m_nCount-1]=0;
  fx[0]=0;
  fx[m_nCount-1]=0;
  fy[0]=0;
  fy[m_nCount-1]=0;
  for(int i=1; i<m_nCount-1; i++)
    {
      af=s[i]-s[i-1];
      az=s[i+1]-s[i];
      a0=s[i+1]-s[i-1];
      u[i]=af/a0;
      ru[i]=az/a0;
      fx[i]=6*((x[i+1]-x[i])/az-(x[i]-x[i-1])/af)/a0;
      fy[i]=6*((y[i+1]-y[i])/az-(y[i]-y[i-1])/af)/a0;
    }
  beta[0]=0;
  beta[m_nCount-1]=0;
  for(int i=1; i<m_nCount-1; i++)
    {
      beta[i]=ru[i]/(2.0-u[i]*beta[i-1]);
    }
  yx[0]=fx[0]/2.0;
  yy[0]=fy[0]/2.0;
  for(int i=1; i<m_nCount; i++)
    {
      yx[i]=(fx[i]-u[i]*yx[i-1])/(2.0-u[i]*beta[i-1]);
      yy[i]=(fy[i]-u[i]*yy[i-1])/(2.0-u[i]*beta[i-1]);
    }
  Mx[m_nCount-1]=yx[m_nCount-1];
  My[m_nCount-1]=yy[m_nCount-1];
  for(int i=m_nCount-2; i>=0; i--)
    {
      Mx[i]=yx[i]-beta[i]*Mx[i+1];
      My[i]=yy[i]-beta[i]*My[i+1];
    }
  for(int i=0; i<m_nCount-1; i++)
    {
      hj=s[i+1]-s[i];
      ax[i]=(Mx[i+1]-Mx[i])/6.0/hj;
      bx[i]=(s[i+1]*Mx[i]-s[i]*Mx[i+1])/2.0/hj;
      cx[i]=(3*s[i]*s[i]*Mx[i+1]-3*s[i+1]*s[i+1]*Mx[i]-6*x[i]+Mx[i]*hj*hj+6*x[i+1]-Mx[i+1]*hj*hj)/6.0/hj;
      dx[i]=(Mx[i]*s[i+1]*s[i+1]*s[i+1]-Mx[i+1]*s[i]*s[i]*s[i]+(6*x[i]-Mx[i]*hj*hj)*s[i+1]-(6*x[i+1]-Mx[i+1]*hj*hj)*s[i])/6.0/hj;
      ay[i]=(My[i+1]-My[i])/6.0/hj;
      by[i]=(s[i+1]*My[i]-s[i]*My[i+1])/2.0/hj;
      cy[i]=(3*s[i]*s[i]*My[i+1]-3*s[i+1]*s[i+1]*My[i]-6*y[i]+My[i]*hj*hj+6*y[i+1]-My[i+1]*hj*hj)/6.0/hj;
      dy[i]=(My[i]*s[i+1]*s[i+1]*s[i+1]-My[i+1]*s[i]*s[i]*s[i]+(6*y[i]-My[i]*hj*hj)*s[i+1]-(6*y[i+1]-My[i+1]*hj*hj)*s[i])/6.0/hj;
      slope[i]=(3*ay[i]*s[i]*s[i]+2*by[i]*s[i]+cy[i])/(3*ax[i]*s[i]*s[i]+2*bx[i]*s[i]+cx[i]);
    }

  slope[m_nCount-1]=(3*ay[m_nCount-2]*s[m_nCount-1]*s[m_nCount-1]+
		     2*by[m_nCount-2]*s[m_nCount-1]+cy[m_nCount-2])/
                    (3*ax[m_nCount-2]*s[m_nCount-1]*s[m_nCount-1]+
		     2*bx[m_nCount-2]*s[m_nCount-1]+cx[m_nCount-2]);
  free(u);
  free(ru);
  free(fx);
  free(fy);
  free(beta);
  free(yx);
  free(yy);
}

double Cspline::project(double interpo_x,int n)
{
  double interpo_y;
  double X[4]={0,0,0,0};
  int i,j;
  if(n==0)
    {
      if(x[0]==x[1])
	{return y[0];}
      else
	{
	  interpo_y=(y[1]-y[0])/(x[1]-x[0])*(interpo_x-x[0])+y[0];
	  return interpo_y;
	}
    }
  else
    {
      FanShengjin(ax[n],bx[n],cx[n],dx[n]-interpo_x,X);
      for(i=0;i<X[3];i++)
	{
	  if(X[i]>s[n+1]||X[i]<s[n])
	    {
	      X[3]=X[3]-1;
	      for(j=i;j<X[3];j++)
		{
		  X[j]=X[j+1];
		}
	      i--;
	    }
	}

      interpo_y=ay[n]*pow(X[0],3)+by[n]*pow(X[0],2)+cy[n]*X[0]+dy[n];
      return interpo_y;
    }
}

double Cspline::CH(double a,double b,double c,double d)
{
  double ch;
  ch=sqrt((a-b)*(a-b)+(c-d)*(c-d));
  return ch;
}

void Cspline::FanShengjin(double a,double b,double c,double d,double *X)
{
  double A,B,C,delta,Y1,Y2,T,theta,mid;
  int i,j;
  A=b*b-3*a*c;
  B=b*c-9*a*d;
  C=c*c-3*b*d;
  delta=B*B-4*A*C;
  if(A==0&&B==0)
    {
      X[0]=-b/3.0/a;
      X[3]=1;
    }
  else if (delta>0)
    {
      Y1=A*b+3*a*(-B+sqrt(delta))/2.0;
      Y2=A*b+3*a*(-B-sqrt(delta))/2.0;
      X[0]=(-b-fabs(Y1)/Y1*pow(fabs(Y1),1.0/3.0)-fabs(Y2)/Y2*pow(fabs(Y2),1.0/3.0))/3.0/a;
      X[3]=1;
    }
  else if(delta==0)
    {
      X[0]=-b/a+B/A;
      X[1]=-B/A/2.0;
      if(X[0]<X[1])
	{
	  mid=X[0];
	  X[0]=X[1];
	  X[1]=mid;
	}
      X[3]=2;
    }
  else if(delta<0)
    {
      T=(2*A*b-3*a*B)/2.0/pow(A,1.5);
      theta=acos(T);
      X[0]=(-b-2*sqrt(A)*cos(theta/3.0))/3.0/a;
      X[1]=(-b+sqrt(A)*(cos(theta/3.0)+sqrt(3.0)*sin(theta/3.0)))/3.0/a;
      X[2]=(-b+sqrt(A)*(cos(theta/3.0)-sqrt(3.0)*sin(theta/3.0)))/3.0/a;
      for(i=0;i<3;i++)
	{
	  for(j=0;j<3;j++)
	    {
	      if(X[j]<X[j+1])
		{
		  mid=X[j];
		  X[j]=X[j+1];
		  X[j+1]=mid;
		}
	    }
	}
      X[3]=3;
    }
}

Cspline::Cspline():
  x(NULL),
  y(NULL),
  s(NULL),
  Mx(NULL),
  My(NULL),
  slope(NULL),
  ax(NULL),
  ay(NULL),
  bx(NULL),
  by(NULL),
  cx(NULL),
  cy(NULL),
  dx(NULL),
  dy(NULL)  
{
}

Cspline::~Cspline()
{
  release();
}
