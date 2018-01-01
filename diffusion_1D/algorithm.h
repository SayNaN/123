#ifndef DIFFUSION1D_ALOGRITHM_H
#define DIFFUSION1D_ALOGRITHM_H
#include <QtWidgets>
#include <QVector>
#include <QVector3D>
#include <stdio.h>
#include <stdlib.h>

struct settingParam
{
  double dCoorX;
  double dSpecificHeatCap;
  double cellSize;
  std::vector<double>* vecArea;
  std::vector<double>* vecHConductivity;
  
};

class diffusion1D: public QThread
{
  Q_OBJECT
    
 public:
  diffusion1D(QObject* parent = NULL);
  ~diffusion1D();

  static diffusion1D* getInstance();

 private:
  QVector<settingParam> m_SettingParam;
  static diffusion1D* p_instance;

 protected:
  virtual void run();
  
}


#endif
