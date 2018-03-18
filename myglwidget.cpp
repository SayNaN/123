#include<windows.h>
#include<math.h>
#include"myglwidget.h"
#include<QtWidgets>
#include<GL/GL.H>
#include<GL/GLU.H>

MyGLWidget::MyGLWidget(QWidget *parent,Data_Container *DB):QOpenGLWidget(parent)
{
  data=DB;
  drawGeo=true;
  drawMesh=false;
  rangeleft=-1;
  rangeright=1;
  rangebottom=-1;
  rangetop=1;
  rangenear=-1000;
  rangefar=1000;
}

void MyGLWidget::cleardisplay()
{
  drawGeo=false;
  drawMesh=false;
  update();
}

void MyGLWidget::drawGeomDisplay()
{
  set_range(data->geom.minx,data->geom.maxx,data->geom.miny,data->geom.maxy,data->geom.minz-50*(data->geom.maxz-data->geom.minz),data->geom.maxz+50*(data->geom.maxz-data->geom.minz));
  update();
}

void MyGLWidget::drawMeshDisplay()
{
  set_range(data->mesh.minx,data->mesh.maxx,data->mesh.miny,data->mesh.maxy,data->mesh.minz-50*(data->mesh.maxz-data->mesh.minz),data->mesh.maxz+50*(data->mesh.maxz-data->mesh.minz));
  update();
}

void MyGLWidget::wheelEvent(QWheelEvent *event)
{
  makeCurrent();
  QPoint eventscale=event->angleDelta();
  double positionx,positiony;
  double newtop,newbottom,newleft,newright;
  double localRatio;
  positionx=(double)event->x()/width_fun;
  positiony=(double)event->y()/height_fun;
  if(eventscale.y()>0)
    localRatio=1.25;
  else
    localRatio=0.8;
  if((showright-showleft)<(showtop-showbottom))
    {
      newtop   =showtop -(showtop-showbottom)*positiony+(showtop-showbottom)*localRatio* positiony;
      newbottom=showtop -(showtop-showbottom)*positiony-(showtop-showbottom)*localRatio*(1-positiony);
      newleft  =showleft+(showright-showleft)*positionx-(showtop-showbottom)*localRatio* positionx   *width_fun/height_fun;
      newright =showleft+(showright-showleft)*positionx+(showtop-showbottom)*localRatio*(1-positionx)*width_fun/height_fun;
    }
  else
    {
      newleft  =showleft+(showright-showleft)*positionx-(showright-showleft)*localRatio* positionx;
      newright =showleft+(showright-showleft)*positionx+(showright-showleft)*localRatio*(1-positionx);
      newtop   =showtop -(showtop-showbottom)*positiony+(showright-showleft)*localRatio* positiony   *height_fun/width_fun;
      newbottom=showtop -(showtop-showbottom)*positiony-(showright-showleft)*localRatio*(1-positiony)*height_fun/width_fun;
    }
  showleft=newleft;
  showright=newright;
  showtop=newtop;
  showbottom=newbottom;
  update();
}

void MyGLWidget::mousePressEvent(QMouseEvent *e)
{
  switch(e->button())
    {
    case Qt::LeftButton:button_type=1;break;
    case Qt::MidButton:button_type=2;break;
    case Qt::RightButton:button_type=3;break;
    default:button_type=0;break;
    }
  if(button_type==3)
    {
      makeCurrent();
      init_showrange();
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      update();
    }
  else
    {
      mousex=e->x();
      mousey=e->y();
    }
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *event)
{
  if(button_type==1)
    {
      makeCurrent();
      double s=0.5;
      glMatrixMode(GL_MODELVIEW);
      glGetDoublev(GL_MODELVIEW_MATRIX,comat);
      glLoadIdentity();
      glRotatef(s*(event->y()-mousey), 1., 0., 0.);
      glRotatef(s*(event->x()-mousex), 0., 1., 0.);
      glMultMatrixd(comat);
      update();
      mousex=event->x();
      mousey=event->y();
    }
  if(button_type==2)
    {
      makeCurrent();
      double matP[16];
      double matM[16];
      int portV[16];
      double win[3];
      double obj[3];
      double scale;
      glGetDoublev(GL_PROJECTION_MATRIX,matP);
      glGetDoublev(GL_MODELVIEW_MATRIX,matM);
      glGetIntegerv(GL_VIEWPORT,portV);
      
      gluProject(0,0,0,matM,matP,portV,&win[0],&win[1],&win[2]);
      gluUnProject(win[0],win[1]+1,win[2],matM,matP,portV,&obj[0],&obj[1],&obj[2]);
      
      scale=sqrt(obj[0]*obj[0]+obj[1]*obj[1]+obj[2]*obj[2]);
      glMatrixMode(GL_MODELVIEW);
      glGetDoublev(GL_MODELVIEW_MATRIX,comat);
      glLoadIdentity();
      glTranslatef(scale*(event->x()-mousex),scale*(mousey-event->y()), 0.0);
      glMultMatrixd(comat);
      update();
      mousex=event->x();
      mousey=event->y();
    }
}

void MyGLWidget::initializeGL()
{
  initializeOpenGLFunctions();

  glClearColor(1.0, 1.0, 1.0, 0.0);
  //glClearDepth(1.0);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glShadeModel(GL_SMOOTH);  
  glDepthFunc(GL_LEQUAL);

  GLfloat LightAmbient[]= { 0.2, 0.2, 0.2, 1.0 };
  GLfloat LightDiffuse[]= { 0.8, 0.8, 0.8, 1.0 };
  GLfloat lightSpecular[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat LightPosition[]= { 1.0, 1.0, 1.0, 0.0 };
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
  glLightfv(GL_LIGHT1, GL_SPECULAR, lightSpecular);
  glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);
  glPopMatrix();
  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT,LightAmbient);
  glEnable(GL_LIGHT1);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
  glEnable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);
  //glDepthMask(GL_FALSE);
  //glEnable(GL_COLOR_MATERIAL);
}

void MyGLWidget::set_range(double left,double right,double bottom,double top,double near_1,double far_1)
{
  rangeleft=left;
  rangeright=right;
  rangebottom=bottom;
  rangetop=top;
  rangenear=near_1;
  rangefar=far_1;
  init_showrange();
}

void MyGLWidget::init_showrange()
{
  if((rangeright-rangeleft)/(rangetop-rangebottom)<width_fun/height_fun)
    {
      showtop   =1.1*rangetop   -0.1*rangebottom;
      showbottom=1.1*rangebottom-0.1*rangetop;
      showleft  =(rangeleft+rangeright)/2.0-width_fun/height_fun*(showtop-showbottom)/2.0;
      showright =(rangeleft+rangeright)/2.0+width_fun/height_fun*(showtop-showbottom)/2.0;
    }
  else
    {
      showleft  =1.1*rangeleft -0.1*rangeright;
      showright =1.1*rangeright-0.1*rangeleft;
      showtop   =(rangetop+rangebottom)/2.0+height_fun/width_fun*(showright-showleft)/2.0;
      showbottom=(rangetop+rangebottom)/2.0-height_fun/width_fun*(showright-showleft)/2.0;
    }
}

void MyGLWidget::resizeGL(int w, int h)
{
  width_fun=w;
  height_fun=h;
  glViewport(0, 0, w, h);
  double newtop,newbottom,newleft,newright;
  if((rangeright-rangeleft)/(rangetop-rangebottom)<width_fun/height_fun)
    {
      newtop   =showtop;
      newbottom=showbottom;
      newleft  =(showright+showleft)/2.0-(showtop-showbottom)/2.0*width_fun/height_fun;
      newright =(showright+showleft)/2.0+(showtop-showbottom)/2.0*width_fun/height_fun;
    }
  else
    {
      newleft  =showleft;
      newright =showright;
      newtop   =(showtop+showbottom)/2.0+(showright-showleft)/2.0*height_fun/width_fun;
      newbottom=(showtop+showbottom)/2.0-(showright-showleft)/2.0*height_fun/width_fun;
    }
  showleft=newleft;
  showright=newright;
  showtop=newtop;
  showbottom=newbottom;
}

void MyGLWidget::paintGL()
{
  glMatrixMode(GL_MODELVIEW);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(showleft,showright,showbottom,showtop,rangenear,rangefar);
  glMatrixMode(GL_MODELVIEW);
  glEnable(GL_LIGHTING);
  if(drawMesh)
    { draw3DGrid(); }
  if(drawGeo)
    { draw3DGeo(); }
  
  glDisable(GL_LIGHTING);
  glGetDoublev(GL_MODELVIEW_MATRIX,comat);
  comat[3]=0;
  comat[7]=0;
  comat[11]=0;
  comat[12]=0;
  comat[13]=0;
  comat[14]=0;
  comat[15]=1;
  glPushMatrix();
  glClear(GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(-width_fun,width_fun,-height_fun,height_fun,-1000,1000);
  glMatrixMode(GL_MODELVIEW);
  glTranslatef(0.7*width_fun,-0.8*height_fun,0);
  glMultMatrixd(comat);
  double ra;
  if(width_fun<height_fun)
    { ra=width_fun*0.1; }
  else
    { ra=height_fun*0.1; }

  glBegin(GL_QUAD_STRIP);
  glColor3f(0.0,0.0,1.0);
  glVertex3f(0.0,ra,0.0);
  glVertex3f(0.0,0.0,0.0);
  glVertex3f(ra,ra,0.0);
  glVertex3f(ra,0.0,0.0);
  glVertex3f(ra,ra,ra);
  glVertex3f(ra,0.0,ra);
  glVertex3f(0.0,ra,ra);
  glVertex3f(0.0,0.0,ra);
  glVertex3f(0.0,ra,0.0);
  glVertex3f(0.0,0.0,0.0);
  glEnd();
  glBegin(GL_QUADS);
  glVertex3f(0.0,ra,0.0);
  glVertex3f(ra,ra,0.0);
  glVertex3f(ra,ra,ra);
  glVertex3f(0.0,ra,ra);
  glEnd();
  glBegin(GL_QUADS);
  glVertex3f(ra,0.0,0.0);
  glVertex3f(0.0,0.0,0.0);
  glVertex3f(0.0,0.0,ra);
  glVertex3f(ra,0.0,ra);
  glEnd();
  glBegin(GL_LINES);
  glColor3f(0.0,0.0,0.0);
  glVertex3f(0.0,0.0,0.0);
  glVertex3f(1.5*ra,0.0,0.0);
  glVertex3f(0.0,0.0,0.0);
  glVertex3f(0.0,1.5*ra,0.0);
  glVertex3f(0.0,0.0,0.0);
  glVertex3f(0.0,0.0,1.5*ra);
  glVertex3f(ra,0.0,0.0);
  glVertex3f(ra,ra,0.0);
  glVertex3f(ra,0.0,0.0);
  glVertex3f(ra,0.0,ra);
  glVertex3f(0.0,ra,0.0);
  glVertex3f(ra,ra,0.0);
  glVertex3f(0.0,ra,0.0);
  glVertex3f(0.0,ra,ra);
  glVertex3f(0.0,0.0,ra);
  glVertex3f(ra,0.0,ra);
  glVertex3f(0.0,0.0,ra);
  glVertex3f(0.0,ra,ra);
  glVertex3f(ra,ra,ra);
  glVertex3f(0.0,ra,ra);
  glVertex3f(ra,ra,ra);
  glVertex3f(ra,0.0,ra);
  glVertex3f(ra,ra,ra);
  glVertex3f(ra,ra,0.0);
  glEnd();
  glRasterPos3f(1.8*ra,0.0,0.0);
  drawstring("X");
  glRasterPos3f(0.0,1.8*ra,0.0);
  drawstring("Y");
  glRasterPos3f(0.0,0.0,1.8*ra);
  drawstring("Z");
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
  //glDisable(GL_LIGHTING);
  glFlush();
}

void MyGLWidget::drawstring(const char *str)
{
  int len=0,i;
  wchar_t *wstring;
  HDC hdc=wglGetCurrentDC();
  GLuint list=glGenLists(1);
  for(i=0;str[i]!='\0';i++)
    {
      if(IsDBCSLeadByte(str[i]))
	i++;
      len++;
    }
  wstring=(wchar_t*)malloc((len+1)*sizeof(wchar_t));
  MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,str,-1,wstring,len);
  wstring[len]=L'\0';
  for(i=0;i<len;i++)
    {
      wglUseFontBitmapsW(hdc,wstring[i],1,list);
      glCallList(list);
    }
  free(wstring);
  glDeleteLists(list,1);
}

void MyGLWidget::draw3DGeo()
{
  int i,j,nr;
  ROWDATA *p;

  GLfloat mat_ambient[]  = {0.8f, 0.0f, 0.0f, 1.0f};
  GLfloat mat_diffuse[]  = {0.4f, 0.1f, 0.1f, 1.0f};
  GLfloat mat_specular[] = {0.3f, 0.1f, 0.1f, 1.0f};
  GLfloat mat_emission[] = {0.0f, 0.0f, 0.0f, 1.0f};
  GLfloat mat_shininess=100.0f;

  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,mat_ambient);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,mat_diffuse);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,mat_specular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION,mat_emission);
  glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS,mat_shininess);

  for(nr=0;nr<data->geom.nrs;nr++)
    {
      p=&data->geom.row[nr];
      for(j=0;j<p->blade.nsects-1;j++)
	{
	  glBegin(GL_TRIANGLE_STRIP);
	  for(i=0;i<p->blade.ss[j].npts;i++)
	    {
	      glNormal3f(p->blade.ss[j].norm[i][0]  ,p->blade.ss[j].norm[i][1]  ,p->blade.ss[j].norm[i][2]  );
	      glVertex3f(p->blade.ss[j].coor[i][0]  ,p->blade.ss[j].coor[i][1]  ,p->blade.ss[j].coor[i][2]  );
	      glNormal3f(p->blade.ss[j+1].norm[i][0],p->blade.ss[j+1].norm[i][1],p->blade.ss[j+1].norm[i][2]);
	      glVertex3f(p->blade.ss[j+1].coor[i][0],p->blade.ss[j+1].coor[i][1],p->blade.ss[j+1].coor[i][2]);
	    }
	  glEnd();
	  glBegin(GL_TRIANGLE_STRIP);
	  for(i=0;i<p->blade.ps[j].npts;i++)
	    {
	      glNormal3f(p->blade.ps[j].norm[i][0]  ,p->blade.ps[j].norm[i][1]  ,p->blade.ps[j].norm[i][2]  );
	      glVertex3f(p->blade.ps[j].coor[i][0]  ,p->blade.ps[j].coor[i][1]  ,p->blade.ps[j].coor[i][2]  );
	      glNormal3f(p->blade.ps[j+1].norm[i][0],p->blade.ps[j+1].norm[i][1],p->blade.ps[j+1].norm[i][2]);
	      glVertex3f(p->blade.ps[j+1].coor[i][0],p->blade.ps[j+1].coor[i][1],p->blade.ps[j+1].coor[i][2]);
	    }
	  glEnd();
	}
      if(p->isplt)
	{
	  for(j=0;j<p->splitter.nsects-1;j++)
	    {
	      glBegin(GL_TRIANGLE_STRIP);
	      for(i=0;i<p->splitter.ss[j].npts;i++)
		{
		  glNormal3f(p->splitter.ss[j].norm[i][0]  ,p->splitter.ss[j].norm[i][1]  ,p->splitter.ss[j].norm[i][2]  );
		  glVertex3f(p->splitter.ss[j].coor[i][0]  ,p->splitter.ss[j].coor[i][1]  ,p->splitter.ss[j].coor[i][2]  );
		  glNormal3f(p->splitter.ss[j+1].norm[i][0],p->splitter.ss[j+1].norm[i][1],p->splitter.ss[j+1].norm[i][2]);
		  glVertex3f(p->splitter.ss[j+1].coor[i][0],p->splitter.ss[j+1].coor[i][1],p->splitter.ss[j+1].coor[i][2]);
		}
	      glEnd();
	      glBegin(GL_TRIANGLE_STRIP);
	      for(i=0;i<p->splitter.ps[j].npts;i++)
		{
		  glNormal3f(p->splitter.ps[j].norm[i][0]  ,p->splitter.ps[j].norm[i][1]  ,p->splitter.ps[j].norm[i][2]  );
		  glVertex3f(p->splitter.ps[j].coor[i][0]  ,p->splitter.ps[j].coor[i][1]  ,p->splitter.ps[j].coor[i][2]  );
		  glNormal3f(p->splitter.ps[j+1].norm[i][0],p->splitter.ps[j+1].norm[i][1],p->splitter.ps[j+1].norm[i][2]);
		  glVertex3f(p->splitter.ps[j+1].coor[i][0],p->splitter.ps[j+1].coor[i][1],p->splitter.ps[j+1].coor[i][2]);
		}
	      glEnd();
	    }  
	}
    }
  
}

void MyGLWidget::draw3DGrid()
{
  int i,j,k,nr;
  ROWMESHDATA *p;
  
  GLfloat mat_ambient[]  = {0.5f, 0.5f, 0.5f, 1.0f};
  GLfloat mat_diffuse[]  = {0.4f, 0.4f, 0.4f, 1.0f};
  GLfloat mat_specular[] = {0.3f, 0.3f, 0.3f, 1.0f};
  GLfloat mat_emission[] = {0.0f, 0.0f, 0.0f, 1.0f};
  GLfloat mat_shininess=100.0f;
  
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,mat_ambient);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,mat_diffuse);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,mat_specular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION,mat_emission);
  glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS,mat_shininess);

  //glColor4f(0.0f, 0.f, 0.f, 1.0f);

  //glPolygonMode(GL_FRONT, GL_LINE); 
  //glPolygonMode(GL_BACK, GL_LINE);

  for(nr=0;nr<data->mesh.nrs;nr++)
    {
      p=&data->mesh.row[nr];
      for(j=0;j<p->finalResult.jm-1;j++)
	{
	  glBegin(GL_TRIANGLE_STRIP);
	  for(i=0;i<p->finalResult.im;i++)
	    {
	      glNormal3f(p->finalResult.topNorm[i][j][0],p->finalResult.topNorm[i][j][1],p->finalResult.topNorm[i][j][2]);
	      glVertex3f(p->finalResult.topSurf[i][j][0],p->finalResult.topSurf[i][j][1],p->finalResult.topSurf[i][j][2]);
	      glNormal3f(p->finalResult.topNorm[i][j+1][0],p->finalResult.topNorm[i][j+1][1],p->finalResult.topNorm[i][j+1][2]);
	      glVertex3f(p->finalResult.topSurf[i][j+1][0],p->finalResult.topSurf[i][j+1][1],p->finalResult.topSurf[i][j+1][2]);
	    }
	  glEnd();
	  glBegin(GL_TRIANGLE_STRIP);
	  for(i=0;i<p->finalResult.im;i++)
	    {
	      glNormal3f(p->finalResult.bottomNorm[i][j][0],p->finalResult.bottomNorm[i][j][1],p->finalResult.bottomNorm[i][j][2]);
	      glVertex3f(p->finalResult.bottomSurf[i][j][0],p->finalResult.bottomSurf[i][j][1],p->finalResult.bottomSurf[i][j][2]);
	      glNormal3f(p->finalResult.bottomNorm[i][j+1][0],p->finalResult.bottomNorm[i][j+1][1],p->finalResult.bottomNorm[i][j+1][2]);
	      glVertex3f(p->finalResult.bottomSurf[i][j+1][0],p->finalResult.bottomSurf[i][j+1][1],p->finalResult.bottomSurf[i][j+1][2]);
	    }
	  glEnd();
	}
      for(k=0;k<p->finalResult.km-1;k++)
	{
	  glBegin(GL_TRIANGLE_STRIP);
	  for(i=0;i<p->finalResult.im;i++)
	    {
	      glNormal3f(p->finalResult.frontNorm[i][k][0],p->finalResult.frontNorm[i][k][1],p->finalResult.frontNorm[i][k][2]);
	      glVertex3f(p->finalResult.frontSurf[i][k][0],p->finalResult.frontSurf[i][k][1],p->finalResult.frontSurf[i][k][2]);
	      glNormal3f(p->finalResult.frontNorm[i][k+1][0],p->finalResult.frontNorm[i][k+1][1],p->finalResult.frontNorm[i][k+1][2]);
	      glVertex3f(p->finalResult.frontSurf[i][k+1][0],p->finalResult.frontSurf[i][k+1][1],p->finalResult.frontSurf[i][k+1][2]);
	    }
	  glEnd();
	  glBegin(GL_TRIANGLE_STRIP);
	  for(i=0;i<p->finalResult.im;i++)
	    {
	      glNormal3f(p->finalResult.backNorm[i][k][0],p->finalResult.backNorm[i][k][1],p->finalResult.backNorm[i][k][2]);
	      glVertex3f(p->finalResult.backSurf[i][k][0],p->finalResult.backSurf[i][k][1],p->finalResult.backSurf[i][k][2]);
	      glNormal3f(p->finalResult.backNorm[i][k+1][0],p->finalResult.backNorm[i][k+1][1],p->finalResult.backNorm[i][k+1][2]);
	      glVertex3f(p->finalResult.backSurf[i][k+1][0],p->finalResult.backSurf[i][k+1][1],p->finalResult.backSurf[i][k+1][2]);
	    }
	  glEnd();
	}
      for(k=0;k<p->finalResult.km-1;k++)
	{
	  glBegin(GL_TRIANGLE_STRIP);
	  for(j=0;j<p->finalResult.jm;j++)
	    {
	      glNormal3f(p->finalResult.leftNorm[j][k][0],p->finalResult.leftNorm[j][k][1],p->finalResult.leftNorm[j][k][2]);
	      glVertex3f(p->finalResult.leftSurf[j][k][0],p->finalResult.leftSurf[j][k][1],p->finalResult.leftSurf[j][k][2]);
	      glNormal3f(p->finalResult.leftNorm[j][k+1][0],p->finalResult.leftNorm[j][k+1][1],p->finalResult.leftNorm[j][k+1][2]);
	      glVertex3f(p->finalResult.leftSurf[j][k+1][0],p->finalResult.leftSurf[j][k+1][1],p->finalResult.leftSurf[j][k+1][2]);
	    }
	  glEnd();
	  glBegin(GL_TRIANGLE_STRIP);
	  for(j=0;j<p->finalResult.jm;j++)
	    {
	      glNormal3f(p->finalResult.rightNorm[j][k][0],p->finalResult.rightNorm[j][k][1],p->finalResult.rightNorm[j][k][2]);
	      glVertex3f(p->finalResult.rightSurf[j][k][0],p->finalResult.rightSurf[j][k][1],p->finalResult.rightSurf[j][k][2]);
	      glNormal3f(p->finalResult.rightNorm[j][k+1][0],p->finalResult.rightNorm[j][k+1][1],p->finalResult.rightNorm[j][k+1][2]);
	      glVertex3f(p->finalResult.rightSurf[j][k+1][0],p->finalResult.rightSurf[j][k+1][1],p->finalResult.rightSurf[j][k+1][2]);
	    }
	  glEnd();
	}
      glDisable(GL_LIGHTING);
      for(k=0;k<p->finalResult.km-1;k++)
	{
	  glBegin(GL_LINES);
	  for(i=0;i<p->finalResult.im;i++)
	    {
	      glVertex3f(p->finalResult.frontSurf[i][k][0],p->finalResult.frontSurf[i][k][1],p->finalResult.frontSurf[i][k][2]);
	      glVertex3f(p->finalResult.frontSurf[i][k+1][0],p->finalResult.frontSurf[i][k+1][1],p->finalResult.frontSurf[i][k+1][2]);
	      glVertex3f(p->finalResult.backSurf[i][k][0],p->finalResult.backSurf[i][k][1],p->finalResult.backSurf[i][k][2]);
	      glVertex3f(p->finalResult.backSurf[i][k+1][0],p->finalResult.backSurf[i][k+1][1],p->finalResult.backSurf[i][k+1][2]);
	    }
	  glEnd();
	}
      for(k=0;k<p->finalResult.km-1;k++)
	{
	  glBegin(GL_LINE_STRIP);
	  for(i=0;i<p->finalResult.im;i++)
	    {
	      glVertex3f(p->finalResult.frontSurf[i][k][0],p->finalResult.frontSurf[i][k][1],p->finalResult.frontSurf[i][k][2]);
	    }
	  glEnd();
	  glBegin(GL_LINE_STRIP);
	  for(i=0;i<p->finalResult.im;i++)
	    {
	      glVertex3f(p->finalResult.backSurf[i][k][0],p->finalResult.backSurf[i][k][1],p->finalResult.backSurf[i][k][2]);
	    }
	  glEnd();
	}
      for(j=0;j<p->finalResult.jm-1;j++)
	{
	  glBegin(GL_LINES);
	  for(i=0;i<p->finalResult.im;i++)
	    {
	      glVertex3f(p->finalResult.topSurf[i][j][0],p->finalResult.topSurf[i][j][1],p->finalResult.topSurf[i][j][2]);
	      glVertex3f(p->finalResult.topSurf[i][j+1][0],p->finalResult.topSurf[i][j+1][1],p->finalResult.topSurf[i][j+1][2]);
	      glVertex3f(p->finalResult.bottomSurf[i][j][0],p->finalResult.bottomSurf[i][j][1],p->finalResult.bottomSurf[i][j][2]);
	      glVertex3f(p->finalResult.bottomSurf[i][j+1][0],p->finalResult.bottomSurf[i][j+1][1],p->finalResult.bottomSurf[i][j+1][2]);
	    }
	  glEnd();
	}
      for(j=0;j<p->finalResult.jm;j++)
	{
	  glBegin(GL_LINE_STRIP);
	  for(i=0;i<p->finalResult.im;i++)
	    {
	      glVertex3f(p->finalResult.topSurf[i][j][0],p->finalResult.topSurf[i][j][1],p->finalResult.topSurf[i][j][2]);
	    }
	  glEnd();
	  glBegin(GL_LINE_STRIP);
	  for(i=0;i<p->finalResult.im;i++)
	    {
	      glVertex3f(p->finalResult.bottomSurf[i][j][0],p->finalResult.bottomSurf[i][j][1],p->finalResult.bottomSurf[i][j][2]);
	    }
	  glEnd();
	}
      for(k=0;k<p->finalResult.km-1;k++)
	{
	  glBegin(GL_LINES);
	  for(j=0;j<p->finalResult.jm;j++)
	    {
	      glVertex3f(p->finalResult.leftSurf[j][k][0],p->finalResult.leftSurf[j][k][1],p->finalResult.leftSurf[j][k][2]);
	      glVertex3f(p->finalResult.leftSurf[j][k+1][0],p->finalResult.leftSurf[j][k+1][1],p->finalResult.leftSurf[j][k+1][2]);
	      glVertex3f(p->finalResult.rightSurf[j][k][0],p->finalResult.rightSurf[j][k][1],p->finalResult.rightSurf[j][k][2]);
	      glVertex3f(p->finalResult.rightSurf[j][k+1][0],p->finalResult.rightSurf[j][k+1][1],p->finalResult.rightSurf[j][k+1][2]);
	    }
	  glEnd();
	}
      for(k=0;k<p->finalResult.km-1;k++)
	{
	  glBegin(GL_LINE_STRIP);
	  for(j=0;j<p->finalResult.jm;j++)
	    {
	      glVertex3f(p->finalResult.leftSurf[j][k][0],p->finalResult.leftSurf[j][k][1],p->finalResult.leftSurf[j][k][2]);
	    }
	  glEnd();
	  glBegin(GL_LINE_STRIP);
	  for(j=0;j<p->finalResult.jm;j++)
	    {
	      glVertex3f(p->finalResult.rightSurf[j][k][0],p->finalResult.rightSurf[j][k][1],p->finalResult.rightSurf[j][k][2]);
	    }
	  glEnd();
	}
      glEnable(GL_LIGHTING);
    }
}