#ifndef OPERATE_H
#define OPERATE_H

class Operate
{
  Q_OBJECT
 public:
  Operate(ZTService *pService);
  ~Operate(){}

  void setProjectNmae(QString sText);
  QString getProjectName();

  void readProjectFile(QString sText);
  void writeProjectFile();
  void writeResFile(QString sText);

 private:
  ZTService* m_pService;
  QString m_sFullProjectPath;
  QString m_sProjectPath;
  QString m_sProjectName;
  QString m_sResFileName;
};

#endif
