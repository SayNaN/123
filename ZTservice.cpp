#include<stdlib.h>
#include<QDebug>

#include"ZTservice.h"
#include"consolewidget.h"
#include"operate.h"

ZTService::ZTService(): m_bIsModified(false)
{
  m_pOperate = new Operate(this);
  resetService();
}

bool ZTService::isModified()
{
  return m_bIsModified;
}

void ZTService::modified(bool bValue)
{
  m_bIsModified = bValue;
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

void ZTService::info(const char * msg)
{
  m_pConsole->msg(msg);
}

bool ZTService::canStartSimu()
{
  if(0 == m_oGlobalParam.nTimeStep)
    {
      return false;
    }
  if(0 == m_oLocalParam.size())
    {
      return false;
    }
  return true;
}

void ZTService::resetService()
{
  m_oMeshRes.clear();
  m_oLocalParam.clear();
  TabCellContent oStructTemp;
  oStructTemp.dLength = 1;
  oStructTemp.nSubMeshNum = 1;
  oStructTemp.dStartP = 0;
  oStructTemp.dHeatCap = 0;
  oStructTemp.dDensity = 0;
  oStructTemp.dThermalConductivity = 0;
  oStructTemp.dArea = 1;
  m_oLocalParam.push_back(oStructTemp);
  m_oGlobalParam.nType   = CELLCENTER;
  m_oGlobalParam.dF      = 1;
  m_oGlobalParam.dDeltaT = 0.1;
  m_oGlobalParam.nSegNum = 0;
  m_oGlobalParam.nMeshNum= 0;
}

void ZTService::addSegment(int nIndex)
{
  modified(true);
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
  m_oLocalParam.erase(m_oLocalParam.begin()+nIndex);
}

consoleWidget* ZTService::console()
{
  m_pConsole = consoleWidget::instance();
  return m_pConsole;
}

Operate* ZTService::operate()
{
  return m_pOperate;
}

/*
ZTService* ZTService::getInstance()
{
  if(NULL == m_pInstance)
    {
      m_pInstance = new ZTService();
    }
  return m_pInstance;
}
*/
