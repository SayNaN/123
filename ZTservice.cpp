#include"ZTservice.h"

ZTservice::ZTservice()
{
  m_Console = new consolewidget();
  m_pOpearate = new Opearate();
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

void ZTService::addSegment(int index)
{
  TabCellContent structTemp;
  structTemp.length = 1;
  structTemp.subMeshNum = 1;
  structTemp.startP = 0;
  structTemp.heatCap = 0;
  structTemp.density = 0;
  structTemp.thermalConductivity = 0;
  structTemp.area = 1;
  
  m_LocalParam.insert(m_LocalParam.begin()+index, structTemp);
}

void ZTService::removeSegment(int index)
{
  m_LocalParam.earse(m_oLocalParam.begin()+index);
}

consoleWidget* ZTService::console()
{
  return m_pConsole;
}

Opearate* ZTService::opearate()
{
  return m_pOpearate;
}
