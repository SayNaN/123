#include"mesh_1D.h"
#include"ZTservice.h"

Mesh1D::Mesh1D(ZTService *pService):
  m_pService(pService)
{
  m_pData = m_pService->meshRes();
  m_pLocalParam = m_pService->localParam();
  m_pGlobalParam = m_pService->globalParam();
}

void Mesh1D::run()
{
  int nSegCount = m_pLocalParam->size();
  int nSubCount = 0;
  int nMeshNum = 0;
  double dStartPos = 0;
  double dCellLenght = 0;

  m_pData->clear();
  m_pGlobalParam->nMeshNum = 1;
  
  SimuInfoRes structLeftBound;
  structLeftBound.dCoorX = 0.0;
  m_pData->push_back(structLeftBound);
  
  for(int i=0; i<nSegCount; i++)
    {
      nSubCount = m_pLocalParam->at(i).nSubMeshNum;
      
      m_pGlobalParam->nMeshNum += nSubCount;
      
      dCellLenght = m_pLocalParam->at(i).dLength / (double)nSubCount;
      
      for(int j=0; j<nSubCount; j++)
	{
	  SimuInfoRes structTemp;

	  dStartPos += dCellLenght;
	  if(CELLCENTER == m_pGlobalParam->nType)
	    {
	      structTemp.dCoorX = dStartPos - dCellLenght/2.0;
	    }
	  else
	    {
	      structTemp.dCoorX = dStartPos;
	    }

	  m_pData->push_back(structTemp);
	}
    }
  if(CELLCENTER == m_pGlobalParam->nType)
    {
      SimuInfoRes structRightBound;
      structRightBound.dCoorX = dStartPos;
      m_pData->push_back(structRightBound);
      m_pGlobalParam->nMeshNum ++;
    }

  nMeshNum = m_pData->size();
  
  for(int i=1; i<nMeshNum-1; i++)
    {
      double dCoorP = m_pData->at(i).dCoorX;
      double dCoorW = m_pData->at(i-1).dCoorX;
      double dCoorE = m_pData->at(i+1).dCoorX;
      m_pData->at(i).dXw = dCoorP - dCoorW;
      m_pData->at(i).dXe = dCoorE - dCoorP;
      m_pData->at(i).dCellLenght = (dCoorE - dCoorW) / 2.0;
    }

  m_pData->at(0).dXw = 0;
  m_pData->at(0).dXe = m_pData->at(1).dXw;
  m_pData->at(0).dCellLenght = m_pData->at(0).dXe / 2.0;

  m_pData->at(nMeshNum-1).dXw = m_pData->at(nMeshNum-2).dXe;
  m_pData->at(nMeshNum-1).dXe = 0;
  m_pData->at(nMeshNum-1).dCellLenght = m_pData->at(nMeshNum-1).dXw / 2.0;
}
