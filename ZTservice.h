#ifndef ZTSERVICE_H
#define ZTSERVICE_H

#include"ZTtype.h"

class ZTService
{
 public:
  static ZTService* getInstance();

  MeshRes* meshRes();
  GlobalParam* globalParam();
  LocalParam* localParam();
  void resetService();
  consoleWidget* console();

 private:
  static ZTService* p_instance;
  MeshRes m_MeshRes;
  LocalParam m_LocalParam;
  GlobalParam m_GlobalParam;

  consoleWidget* m_Console;

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
