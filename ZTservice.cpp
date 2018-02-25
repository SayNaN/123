#include"ZTservice.h"

ZTservice::ZTservice()
{
  m_Console = new consolewidget();
  resetService();
}

ZTservice* ZTService::getInstance()
{
  if(NULL == p_instance)
    {
      p_instance = new ZTservice();
    }
  return p_instance;
}

MeshRes* ZTService::meshRes()
{
  return &m_MeshRes;
}

GlobalParam* ZTService::globalParam()
{
  return &m_GlobalParam;
}

LocalParam* ZTService::localParam()
{
  return &m_LocalParam;
}

void ZTService::resetService()
{
  m_MeshRes.clear();
  m_LocalParam.clear();
  
  m_GlobalParam.type   = CELLCENTER;
  m_GlobalParam.f      = 1;
  m_GlobalParam.deltaT = 0.1;
  m_GlobalParam.segNum = 0;
  m_GlobalParam.meshNum= 0;
}

consoleWidget* console()
{
  return m_Console;
}
