#include"consolewidget.h"

consoleWidget* consoleWidget::p_instance =NULL;

consoleWidget* consoleWidget::getInstance()
{
  static QMutex mutex;
  if(!m_instance)
    {
      QMutexLocker Locker(&mutex);
      p_instance = new consoleWidget;
    }
  return p_instance;
}
