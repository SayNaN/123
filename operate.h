#ifndef OPERATE_H
#define OPERATE_H
#include<QObject>
#include"cspline/cspline.h"

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
  bool canSave();

  bool writeTecFile(QString sFileName, QString sHeaderText, int nRowCount, double *x, double *y);
  bool readTecFile(QString sFileName, double **x, double **y, int nCount);

 private:
  ZTService* m_pService;
  QString m_sFullProjectPath;
  QString m_sProjectPath;
  QString m_sProjectName;
  QString m_sResFileName;
};

#endif
