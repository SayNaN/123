#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include"cspline.h"

Cspline::Cspline():
  x(NULL), y(NULL), s(NULL),
  Mx(NULL), My(NULL), slope(NULL),
  ax(NULL), ay(NULL), bx(NULL),
  by(NULL), cx(NULL), cy(NULL),
  dx(NULL), dy(NULL)  
{
}

Cspline::~Cspline()
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

void Cspline::gen(double *xcoor,double *ycoor,int n)
{
  double af,a0,az,hj;
  double *u=NULL,*ru=NULL,*fx=NULL,*fy=NULL,*beta=NULL,*yx=NULL,*yy=NULL;
  num=n;
  if(x!=NULL)
    {
      free(x);
      x=NULL;
    }
  if(y!=NULL)
    {
      free(y);
      y=NULL;
    }
  if(s!=NULL)
    {
      free(s);
      s=NULL;
    }
  if(Mx!=NULL)
    {
      free(Mx);
      Mx=NULL;
    }
  if(My!=NULL)
    {
      free(My);
      My=NULL;
    }
  if(slope!=NULL)
    {
      free(slope);
      slope=NULL;
    }
  if(ax!=NULL)
    {
      free(ax);
      ax=NULL;
    }
  if(ay!=NULL)
    {
      free(ay);
      ay=NULL;
    }
  if(bx!=NULL)
    {
      free(bx);
      bx=NULL;
    }
  if(by!=NULL)
    {
      free(by);
      by=NULL;
    }
  if(cx!=NULL)
    {
      free(cx);
      cx=NULL;
    }
  if(cy!=NULL)
    {
      free(cy);
      cy=NULL;
    }
  if(dx!=NULL)
    {
      free(dx);
      dx=NULL;
    }
  if(dy!=NULL)
    {
      free(dy);
      dy=NULL;
    }
  x=(double *)malloc(sizeof(double)*num);
  y=(double *)malloc(sizeof(double)*num);
  s=(double *)malloc(sizeof(double)*num);
  u=(double *)malloc(sizeof(double)*num);
  ru=(double *)malloc(sizeof(double)*num);
  fx=(double *)malloc(sizeof(double)*num);
  fy=(double *)malloc(sizeof(double)*num);
  beta=(double *)malloc(sizeof(double)*num);
  yx=(double *)malloc(sizeof(double)*num);
  yy=(double *)malloc(sizeof(double)*num);
  Mx=(double *)malloc(sizeof(double)*num);
  My=(double *)malloc(sizeof(double)*num);
  slope=(double *)malloc(sizeof(double)*num);
  ax=(double *)malloc(sizeof(double)*(num-1));
  ay=(double *)malloc(sizeof(double)*(num-1));
  bx=(double *)malloc(sizeof(double)*(num-1));
  by=(double *)malloc(sizeof(double)*(num-1));
  cx=(double *)malloc(sizeof(double)*(num-1));
  cy=(double *)malloc(sizeof(double)*(num-1));
  dx=(double *)malloc(sizeof(double)*(num-1));
  dy=(double *)malloc(sizeof(double)*(num-1));
  
  for(i=0;i<num;i++)
    {
      x[i]=xcoor[i];
      y[i]=ycoor[i];
    }
  s[0]=0;
  for(i=1;i<num;i++)
    {
      s[i]=s[i-1]+CH(x[i],x[i-1],y[i],y[i-1]);
    }
  u[0]=0;
  u[num-1]=0;
  ru[0]=0;
  ru[num-1]=0;
  fx[0]=0;
  fx[num-1]=0;
  fy[0]=0;
  fy[num-1]=0;
  for(i=1;i<num-1;i++)
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
  beta[num-1]=0;
  for(i=1;i<num-1;i++)
    {
      beta[i]=ru[i]/(2.0-u[i]*beta[i-1]);
    }
  yx[0]=fx[0]/2.0;
  yy[0]=fy[0]/2.0;
  for(i=1;i<num;i++)
    {
      yx[i]=(fx[i]-u[i]*yx[i-1])/(2.0-u[i]*beta[i-1]);
      yy[i]=(fy[i]-u[i]*yy[i-1])/(2.0-u[i]*beta[i-1]);
    }
  Mx[num-1]=yx[num-1];
  My[num-1]=yy[num-1];
  for(i=num-2;i>=0;i--)
    {
      Mx[i]=yx[i]-beta[i]*Mx[i+1];
      My[i]=yy[i]-beta[i]*My[i+1];
    }
  for(i=0;i<num-1;i++)
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

  i=(int)((num-1)/2);
  slope[num-1]=(3*ay[num-2]*s[num-1]*s[num-1]+2*by[num-2]*s[num-1]+cy[num-2])/(3*ax[num-2]*s[num-1]*s[num-1]+2*bx[num-2]*s[num-1]+cx[num-2]);
  free(u);
  free(ru);
  free(fx);
  free(fy);
  free(beta);
  free(yx);
  free(yy);
}

void Cspline::fillet(double end_x,double end_y,double *x_coor,double *y_coor,int coor_num)
{
  double x_cs[3],y_cs[3];
  double step_0,step_n;
  double param_0,param_n;

  param_0=s[1]/9.0*8;
  param_n=s[num-2]+(s[num-1]-s[num-2])/9.0;
  x_cs[0]=ax[0]*pow(param_0,3)+bx[0]*pow(param_0,2)+cx[0]*param_0+dx[0];
  y_cs[0]=ay[0]*pow(param_0,3)+by[0]*pow(param_0,2)+cy[0]*param_0+dy[0];
  x_cs[2]=ax[num-2]*pow(param_n,3)+bx[num-2]*pow(param_n,2)+cx[num-2]*param_n+dx[num-2];
  y_cs[2]=ay[num-2]*pow(param_n,3)+by[num-2]*pow(param_n,2)+cy[num-2]*param_n+dy[num-2];
  x_cs[1]=end_x;
  y_cs[1]=end_y;

  Cspline abc;
  abc.gen(x_cs,y_cs,3);
  
  x_coor[0]=end_x;
  y_coor[0]=end_y;

  step_0=abc.s[1]/5.0;
  step_n=(abc.s[2]-abc.s[1])/5.0;

  for(i=1;i<6;i++)
    {
      param_0=abc.s[1]-step_0*(i);
      param_n=abc.s[1]+step_n*(i);
      x_coor[i]         =abc.ax[0]*pow(param_0,3)+abc.bx[0]*pow(param_0,2)+abc.cx[0]*param_0+abc.dx[0];
      y_coor[i]         =abc.ay[0]*pow(param_0,3)+abc.by[0]*pow(param_0,2)+abc.cy[0]*param_0+abc.dy[0];
      x_coor[coor_num-i]=abc.ax[1]*pow(param_n,3)+abc.bx[1]*pow(param_n,2)+abc.cx[1]*param_n+abc.dx[1];
      y_coor[coor_num-i]=abc.ay[1]*pow(param_n,3)+abc.by[1]*pow(param_n,2)+abc.cy[1]*param_n+abc.dy[1];
    }
}

void Cspline::interpolate_r(double *res,double *x,double *y,int n,double *inter_r,int x_control_index)
{
  Cspline abc;
  abc.gen(x,y,n);
  res[0]=abc.project(inter_r[0],0);
  res[1]=abc.project(inter_r[1],x_control_index);
  res[2]=abc.project(inter_r[2],x_control_index);
}

double Cspline::project(double interpo_x,int n)
{
  double interpo_y;
  double X[4]={0,0,0,0};
  int i,j;
  //hj=s[n+1]-s[n];
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
      //interpo_y=My[n]*pow((s[n+1]-X[0]),3)/6/hj+My[n+1]*pow((X[0]-s[n]),3)/6/hj+(y[n]-My[n]*hj*hj/6)/hj*(s[n+1]-X[0])+(y[n+1]-My[n+1]*hj*hj/6)/hj*(X[0]-s[n]);
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
