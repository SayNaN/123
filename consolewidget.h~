#ifndef CONSOLEWIDGET_H
#define CONSOLEWIDGET_H

class consoleWidget: public QObject
{
  Q_OBJECT
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
  
 signals:
  void message(QtMsgType type, const QString &msg);
};

#endif
