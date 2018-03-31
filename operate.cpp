#include<QWidget>

#include"operate.h"

Operate::Operate(ZTService *pService):
  m_pService(pService),
  m_sFullProjectPath(""),
  m_sProjectPath(""),
  m_sProjectName(""),
  m_sResFileName("")
{
}


void Operate::resetProject()
{
  m_sFullProjectPath = "";
  m_sProjectPath = "";
  m_sProjectName = "";
  m_sResFileName = "";
}

void Operate::setProjectName(QString sText)
{
  m_sFullProjectPath = sText;
  m_sProjectPath = sText.section("/",0,-2)+tr("/");
  m_sProjectName = sText.section("/",-1,-1).section(".",0,0);
}

QString Operate::getProjectName()
{
  return m_sProjectName;
}

void Operate::writeProjectFile()
{
  GlobalParam* pGlobalTmp = m_pService->globalParam();
  QFile file(m_sFullProjectPath);
  if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
      qInfo()<<QString::fromLocal8Bit("无法打开工程文件");
      return;
    }

  QTextStream out(&file);
  out << pGlobalTmp->nType << endl;
  out << pGlobalTmp->dF << endl;
  out << pGlobalTmp->dSc << endl;
  out << pGlobalTmp->dSp << endl;
  out << pGlobalTmp->dDeltaT << endl;       // time step
  out << pGlobalTmp->dInitTemperature << endl;
  out << pGlobalTmp->nTimeStep << endl;
  out << pGlobalTmp->nSegNum << endl;
  out << pGlobalTmp->nMeshNum << endl;
  out << pGlobalTmp->eInletType << endl;
  out << pGlobalTmp->dInletTemp << endl;
  out << pGlobalTmp->dInletHeatFlux << endl;
  out << pGlobalTmp->dInletInfinityTemp << endl;
  out << pGlobalTmp->dInletConvectiveCoeff << endl;
  out << pGlobalTmp->eOutletType << endl;
  out << pGlobalTmp->dOutletTemp << endl;
  out << pGlobalTmp->dOutletHeatFlux << endl;
  out << pGlobalTmp->dOutletInfinityTemp << endl;
  out << pGlobalTmp->dOutletConvectiveCoeff << endl;

  LocalParam* pLocalTmp = m_pService->LocalParam();

  out << pLocalTmp->size() << endl;

  for(int i=0; i<pLocalTmp->size(); i++)
    {
      out << pLocalTmp->dLength << endl;
      out << pLocalTmp->nSubMeshNum << endl;
      out << pLocalTmp->dStartP << endl;
      out << pLocalTmp->dHeatCap << endl;
      out << pLocalTmp->dDensity << endl;
      out << pLocalTmp->dThermalConductivity << endl;
      out << pLocalTmp->dArea << endl;
    }
  file.close();
  
  qInfo()<<QString::fromLocal8Bit("工程文件保存完毕!");
}


void Operate::readProjectFile()
{
  QFile file(m_sFullProjectPath);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
      qInfo()<<QString::fromLocal8Bit("无法打开工程文件");
      return;
    }

  QTextStream in(&file);
  in >> pGlobalTmp->nType;
  in >> pGlobalTmp->dF;
  in >> pGlobalTmp->dSc;
  in >> pGlobalTmp->dSp;
  in >> pGlobalTmp->dDeltaT;
  in >> pGlobalTmp->dInitTemperature;
  in >> pGlobalTmp->nTimeStep;
  in >> pGlobalTmp->nSegNum;
  in >> pGlobalTmp->nMeshNum;
  in >> pGlobalTmp->eInletType;
  in >> pGlobalTmp->dInletTemp;
  in >> pGlobalTmp->dInletHeatFlux;
  in >> pGlobalTmp->dInletInfinityTemp;
  in >> pGlobalTmp->dInletConvectiveCoeff;
  in >> pGlobalTmp->eOutletType;
  in >> pGlobalTmp->dOutletTemp;
  in >> pGlobalTmp->dOutletHeatFlux;
  in >> pGlobalTmp->dOutletInfinityTemp;
  in >> pGlobalTmp->dOutletConvectiveCoeff;

  LocalParam* pLocalTmp = m_pService->LocalParam();
  int nCount;
  
  in >> nCount;

  for(int i=0; i<nCount; i++)
    {
      in >> pLocalTmp->dLength;
      in >> pLocalTmp->nSubMeshNum;
      in >> pLocalTmp->dStartP;
      in >> pLocalTmp->dHeatCap;
      in >> pLocalTmp->dDensity;
      in >> pLocalTmp->dThermalConductivity;
      in >> pLocalTmp->dArea;
    }

  file.close();
  qInfo()<<QString::fromLocal8Bit("工程文件读取完毕!");
}

void Operate::writeResFile(QString sText)
{
  sText = m_sProjectPath+"d1Dres.dat";
  QFile file(sText);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
      qInfo()<<QString::fromLocal8Bit("无法打开结果文件");
      return;
    }

  MeshRes* pMRTmp = m_pService->MeshRes();

  QTextStream out(&file);
  out << "variables =\"x\",\"Temperature\",\"Time\"" << endl;
  out << "ZONE I=" <<pMRTmp->size()<<", J="<< pMRTmp->at(0).vecTime_Temperature.size()<<", F=POINT"<<endl;

  for(int i=0; i<pMRTmp->size(); i++)
    {
      for(int j=0; j<pMRTmp->at(i).vecTime_Temperature.size(); j++)
	{
	  out << pMRTmp->at(i).dCoorX << " "
	      << pMRTmp->at(i).vecTime_Temperature.at(j).second << " "
	      << pMRTmp->at(i).vecTime_Temperature.at(j).first  << endl;

	}
    }
  file.close();
  qInfo()<<QString::fromLocal8Bit("结果文件输出完毕!");
}
