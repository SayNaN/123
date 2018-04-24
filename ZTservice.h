#ifndef ZTSERVICE_H
#define ZTSERVICE_H

#include<QObject>
#include"ZTtype.h"

class Operate;
class consoleWidget;

class ZTService: public QObject
{
 public:
  /*
  static ZTService* getInstance();
  */
  ZTService();
  ~ZTService(){};
  
  void addSegment(int nIndex);
  void removeSegment(int nIndex);
  MeshRes* meshRes();
  GlobalParam* globalParam();
  LocalParam* localParam();
  Operate* operate();
  void resetService();
  consoleWidget* console();
  bool isModified();
  void modified(bool bValue);
  bool canStartSimu();
  void info(const char * msg);

 private:
  //static ZTService* m_pInstance;
  MeshRes m_oMeshRes;
  LocalParam m_oLocalParam;
  GlobalParam m_oGlobalParam;
  Operate* m_pOperate;
  consoleWidget* m_pConsole;
  bool m_bIsModified;
  /*
  class ZTServiceGarbo
  {
  public:
    ~ZTServiceGarbo()
      {
	if(NULL != m_pInstance)
	  {
	    delete m_pInstance;
	  }
      }
  };
  */
};

#endif
