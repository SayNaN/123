#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QtWidgets>
#include"threeD_display.h"

class MainWindow :public QMainWindow
{
  Q_OBJECT
 public:
  MainWindow(QWidget *parent=0);
  ~MainWindow(){};
  QSplitter *splittermain;
  QSplitter *splitterright;
  Data_Container *data;
 private:
  QMenu *menu_file;
  QMenu *menu_simulation;
  QMenu *menu_output;
  QMenu *menu_help;
  QToolBar *filetoolbar;
  QToolBar *edittoolbar;
  QAction *new_project;
  QAction *open_project;
  QAction *save_project;
  QAction *save_project_as;
  QAction *connect_to_server;
  QAction *disconnect_to_server;
  QAction *exit_program;
  QAction *link_grid;
  QAction *upload_grid;
  QAction *upload_protype;
  QAction *start_restart;
  QAction *stop_simulation;
  QAction *export_res;
  QAction *help_topics;
  QAction *tutorials;
  QAction *about;
  void inimenu();
  void initoolbar();
  void inicentralwidget();
  MyGLWidget *text3D;
  /* protected:
     void closeEvent(QCloseEvent *event);*/
 private slots:
  void opengridfile();
  /*
  void filenew();
  void fileopen();
  void filesave();
  void filesaveas();*/
};
#endif
