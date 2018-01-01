#include<QtWidgets>
#include"mainwindow.h"
#include"tabwidget.h"
#include"grid_io.h"

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent)
{
  setWindowTitle(QString::fromLocal8Bit("一维非稳态导热"));
  inimenu();
  inicentralwidget();
}

void MainWindow::inimenu()
{
  open_project=new QAction(QString::fromLocal8Bit("导入几何"),this);
  open_project->setShortcut(tr("Ctrl+O"));
  open_project->setStatusTip(QString::fromLocal8Bit("导入几何"));
  open_project->setToolTip(QString::fromLocal8Bit("导入几何"));

  save_project=new QAction(QString::fromLocal8Bit("保存结果"),this);
  save_project->setShortcut(tr("Ctrl+S"));
  save_project->setStatusTip(tr("Save Project"));
  save_project->setToolTip(tr("Save Project"));
  //connect(save_project,SIGNAL(triggered()),this,SLOT(filesave()));

  exit_program=new QAction(tr("&Exit"),this);
  exit_program->setShortcut(tr("Ctrl+E"));

  start_restart=new QAction(QString::fromLocal8Bit("开始计算"),this);
  start_restart->setStatusTip(tr("Start Simulation"));
  start_restart->setToolTip(tr("Start Simulation"));

  //文件菜单
  menu_file=menuBar()->addMenu(tr("&File"));
  menu_file->addAction(open_project);
  menu_file->addSeparator();            //分割线
  menu_file->addAction(save_project);
  menu_file->addAction(exit_program);

  //模拟菜单
  menu_simulation=menuBar()->addMenu(tr("&Simulation"));
  menu_simulation->addAction(start_restart);
}

void MainWindow::initoolbar()
{
  filetoolbar=addToolBar(tr("&File"));
  filetoolbar->addAction(open_project);
  filetoolbar->addAction(save_project);

  edittoolbar=addToolBar(tr("&Edit"));
  edittoolbar->addAction(start_restart);
}

void MainWindow::inicentralwidget()
{
  splittermain=new QSplitter(Qt::Horizontal,this);

  left_frame=new QFrame(splittermain);

  toolbox=new ToolBox(left_frame,data);

  connect(toolbox,&ToolBox::clearshow,[this](){text3D->cleardisplay();textdrawing->cleardisplay();toolbox->performance_display->cleardisplay();});

  splitterright=new QSplitter(Qt::Vertical,splittermain);

  text3D=new MyGLWidget(splitterright,data);

  splitterright_sub=new QSplitter(Qt::Horizontal,splitterright);

  textdrawing=new MyGLWidget2D(splitterright_sub,data);

  textinfo=new QTextEdit(tr("螺旋桨模型信息"),splitterright_sub);
  textinfo->setReadOnly(true);
  connect(this,SIGNAL(AppendText_info(QString)),this,SLOT(append_info(QString)));

  textresidual=new QTextEdit(tr("控制台\n"),splitterright);
  textresidual->setReadOnly(true);
  connect(this,SIGNAL(AppendText_resi(QString)),this,SLOT(append_resi(QString)));

  setCentralWidget(splittermain);
  splittermain->show();
}