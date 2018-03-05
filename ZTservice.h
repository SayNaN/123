#ifndef ZTSERVICE_H
#define ZTSERVICE_H

#include"ZTtype.h"
#include"operate.h"

class ZTService
{
 public:
  static ZTService* getInstance();

  MeshRes* meshRes();
  GlobalParam* globalParam();
  LocalParam* localParam();
  void resetService();
  consoleWidget* console();

 public:
  bool 

 private:
  static ZTService* p_instance;
  MeshRes m_oMeshRes;
  LocalParam m_oLocalParam;
  GlobalParam m_oGlobalParam;
  Operate* m_pOperate;
  consoleWidget* m_pConsole;

  ZTService();
  ~ZTService(){};

  class ZTServiceGarbo
  {
  public:
    ~ZTServiceGarbo()
      {
	if(NULL != p_instance)
	  {
	    delete p_instance;
	  }
      }
  };
};

#endif
