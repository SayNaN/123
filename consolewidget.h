#ifndef CONSOLEWIDGET_H
#define CONSOLEWIDGET_H

class consoleWidget: public QObject
{
  Q_OBJECT

 signals:
  void message(QtMsgType type, const QString &msg);

/*
 public:
  static consoleWidget* getInstance();
  
 private:
  static consoleWidget* p_instance;
  class consoleWidgetGarbo
  {
  private:
    ~consoleWidgetGarbo()
      {
	if(NULL != p_instance)
	  {
	    delete p_instance;
	  }
      }
  };
*/
};

#endif
