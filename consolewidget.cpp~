#include<QMutex>
#include"consolewidget.h"

consoleWidget *consoleWidget::m_pInstance=NULL;

consoleWidget *consoleWidget::instance()
{
  static QMutex mutex;
  if(!m_pInstance)
    {
      QMutexLocker Locker(&mutex);
      m_pInstance = new consoleWidget;
      //connect(this, &consoleWidget::message, this, &consoleWidget::handleMessage);
    }
  return m_pInstance;
}
