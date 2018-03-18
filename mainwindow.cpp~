#include<QtWidgets>
#include"mainwindow.h"
#include"tabwidget.h"
#include"mesh/mesh_1D.h"

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),
{
  m_pService = ZTService::getInstance();
  setWindowTitle(QString::fromLocal8Bit("一维非稳态导热"));
  inimenu();
  inicentralwidget();
}

void MainWindow::inimenu()
{
  m_pOpenProject=new QAction(QString::fromLocal8Bit("打开工程"),this);
  m_pOpenProject->setShortcut(tr("Ctrl+O"));
  m_pOpenProject->setStatusTip(QString::fromLocal8Bit("打开工程"));
  m_pOpenProject->setToolTip(QString::fromLocal8Bit("打开工程"));

  m_pSaveProject=new QAction(QString::fromLocal8Bit("保存工程"),this);
  m_pSaveProject->setShortcut(tr("Ctrl+S"));
  m_pSaveProject->setStatusTip(tr("Save Project"));
  m_pSaveProject->setToolTip(tr("Save Project"));
  connect(m_pSaveProject,SIGNAL(triggered()),this,SLOT(fileSave()));

  m_pExitProgram=new QAction(tr("&Exit"),this);
  m_pExitProgram->setShortcut(tr("Ctrl+E"));

  m_pStartRestart=new QAction(QString::fromLocal8Bit("开始计算"),this);
  m_pStartRestart->setStatusTip(tr("Start Simulation"));
  m_pStartRestart->setToolTip(tr("Start Simulation"));
  connect(m_pStartRestart, SIGNAL(triggered()), this SLOT(startSimu()));

  //文件菜单
  m_pMenuFile=menuBar()->addMenu(tr("&File"));
  m_pMenuFile->addAction(m_pOpenProject);
  m_pMenuFile->addSeparator();            //分割线
  m_pMenuFile->addAction(m_pSaveProject);
  m_pMenuFile->addAction(m_pExitProgram);

  //模拟菜单
  m_pMenuSimulation=menuBar()->addMenu(tr("&Simulation"));
  m_pMenuSimulation->addAction(m_pStartRestart);
}

void MainWindow::initoolbar()
{
  m_pFileToolBar=addToolBar(tr("&File"));
  m_pFileToolBar->addAction(m_pOpenProject);
  m_pFileToolBar->addAction(m_pSaveProject);

  m_pEditToolBar=addToolBar(tr("&Edit"));
  m_pEditToolBar->addAction(m_pStartRestart);
  m_pEditToolBar->addAction(m_pStopSimulation);
}

void MainWindow::inicentralwidget()
{
  QSplitter *pSplitterMain=new QSplitter(Qt::Horizontal,this);

  QFrame *pLeftFrame=new QFrame(pSplitterMain);

  toolbox=new ToolBox(left_frame,data);

  connect(toolbox,&ToolBox::clearshow,[this](){text3D->cleardisplay();textdrawing->cleardisplay();toolbox->performance_display->cleardisplay();});

  splitterright=new QSplitter(Qt::Vertical,splittermain);

  text3D=new MyGLWidget(splitterright,data);

  textresidual=new QTextEdit(tr("控制台\n"),splitterright);
  textresidual->setReadOnly(true);
  connect(this,SIGNAL(AppendText_resi(QString)),this,SLOT(append_resi(QString)));

  setCentralWidget(splittermain);
  splittermain->show();
}

void MainWindow::startSimu()
{
  if(m_oWorkThread.isFinished())
    {
      diffusion1D *pWork = new diffusion1D(m_pService);
      pWork->moveToThread(m_oWorkThread);
      connect(&m_oWorkThread, &QThread::finished, pWork, &QObject::deleteLater);
      connect(this, &MainWindow::startRun, pWork, &diffusion1D::doIt);
      connect(pWork, &diffusion1D::oneStepFinished, this, &processRes);
      m_oWorkThread.start();
      emit startRun();
    }
}


