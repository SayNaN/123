#ifndef OPERATE_H
#define OPERATE_H
#include<QObject>

class ZTService;

class Operate: public QObject
{
  Q_OBJECT
 public:
  Operate(ZTService *pService);
  ~Operate(){}

  void setProjectName(QString sText);
  QString getProjectName();

  void readProjectFile();
  void writeProjectFile();
  void writeResFile(QString sText = "");
  void resetProject();

 private:
  ZTService* m_pService;
  QString m_sFullProjectPath;
  QString m_sProjectPath;
  QString m_sProjectName;
  QString m_sResFileName;
};

#endif
