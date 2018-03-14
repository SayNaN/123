#include"mesh_1D.h"

Mesh1D::Mesh1D(ZTService *pService, QWidget *parent):QWidget(parent)
{
  m_pService = pService;
  m_pData = m_pService->meshRes();
  m_pLocalParam = m_pService->localParam();
  m_pGlobalParam = m_pService->globalParam();
}

void Mesh1D::run()
{
  int nSegCount = m_pData->size();
  int nSubCount = 0;
  double dStartPos = 0;
  double dCellLenght = 0;
  SimuInfoRes structLeftBound;
  
  structLeftBound.coorX = 0.0;
  m_pData->push_back(structLeftBound);
  
  for(int i=1; i<nCount-1; i++)
    {
      nSubCount = m_pLocalParam->at(i).subMeshNum;
      dCellLenght = m_pLocalParam->at(i).length / (double)nSubCount;
      for(int j=0; j<nSubCount; j++)
	{
	  SimuInfoRes structTemp;
	  structTemp.coorX = dStartPos + dCellLenght;
	  dStartPos = structTemp.coorX;
	  m_pData->push_back(structTemp);
	}
    }



}
