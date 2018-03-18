#include"ZTservice.h"

ZTservice::ZTservice()
{
  m_pConsole = new consolewidget();
  m_pOpearate = new Opearate();
  resetService();
}

ZTservice* ZTService::getInstance()
{
  if(NULL == p_instance)
    {
      m_pInstance = new ZTservice();
    }
  return m_pInstance;
}

MeshRes* ZTService::meshRes()
{
  return &m_oMeshRes;
}

GlobalParam* ZTService::globalParam()
{
  return &m_oGlobalParam;
}

LocalParam* ZTService::localParam()
{
  return &m_oLocalParam;
}

void ZTService::resetService()
{
  m_oMeshRes.clear();
  
  m_oLocalParam.clear();
  
  m_oGlobalParam.nType   = CELLCENTER;
  m_oGlobalParam.dF      = 1;
  m_oGlobalParam.dDeltaT = 0.1;
  m_oGlobalParam.nSegNum = 0;
  m_oGlobalParam.nMeshNum= 0;
}

void ZTService::addSegment(int nIndex)
{
  TabCellContent oStructTemp;
  oStructTemp.dLength = 1;
  oStructTemp.nSubMeshNum = 1;
  oStructTemp.dStartP = 0;
  oStructTemp.dHeatCap = 0;
  oStructTemp.dDensity = 0;
  oStructTemp.dThermalConductivity = 0;
  oStructTemp.dArea = 1;
  
  m_oLocalParam.insert(m_oLocalParam.begin()+nIndex, oStructTemp);
}

void ZTService::removeSegment(int nIndex)
{
  m_oLocalParam.earse(m_oLocalParam.begin()+nIndex);
}

consoleWidget* ZTService::console()
{
  return m_pConsole;
}

Opearate* ZTService::opearate()
{
  return m_pOpearate;
}
