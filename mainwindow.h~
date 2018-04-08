#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QtWidgets>

class ZTService;
class MyGLWidget;
class diffusion1D;
class LeftWidget;

class MainWindow :public QMainWindow
{
  Q_OBJECT
    QThread m_oWorkThread;
 public:
  MainWindow(QWidget *parent=0);
  ~MainWindow(){}

  
  void inimenu();
  void initoolbar();
  void inicentralwidget();
  MyGLWidget *text3D;
  /* protected:
     void closeEvent(QCloseEvent *event);*/
 private slots:
  /*
  void fileNew();
  void fileOpen();
  void fileSave();
  void fileSaveAs();
  */
  void startSimu();

 signals:
  void startRun();
  
 private:
  QMenu *m_pMenuFile;
  QMenu *m_pMenuSimulation;
  QMenu *m_pMenuOutput;
  QMenu *m_pMenuHelp;
  
  QToolBar *m_pFileToolBar;
  QToolBar *m_pEditToolBar;
  
  QAction *m_pNewProject;
  QAction *m_pOpenProject;
  QAction *m_pSaveProject;
  QAction *m_pSaveProjectAs;
  QAction *m_pExitProgram;

  QAction *m_pStartRestart;
  QAction *m_pStopSimulation;
  QAction *m_pExportRes;

  QAction *m_pAbout;
  ZTService *m_pService;

  LeftWidget *m_pLeftWidget;
  MyGLWidget *m_pText3D;
  QPlainTextEdit *m_pTextConsole;
};

#endif
