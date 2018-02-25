#include <stdio.h>
#include <stdlib.h>

diffusion1D* diffusion1D::p_instance = NULL;

//#define freeMem

diffusion1D::diffusion1D(QObject* parent): QThread(parent), m_meshNode(0)
{}

diffusion1D::~diffusion1D();
{
  freeArray();
}

diffusion1D* diffusion1D::getInstance()
{
  if(NULL == p_instance)
    {
      p_instance = new diffusion1D;
      p_service = ZTService::getInstance();
    }
  return p_instance;
}

void diffusion1D::run()
{
  m_meshNode = p_service->info()->size();
  calcaE();
  calcaW();
  calcaP0();
  calcaP();
  calcaL();
}

void diffusion1D::freeArray()
{
  if(m_aW)
    {
      free(m_aW);
      m_aW = NULL;
    }
  if(m_aE)
    {
      free(m_aE);
      m_aE = NULL;
    }
  if(m_aP0)
    {
      free(m_aP0);
      m_aP0 = NULL;
    }
  if(m_aP)
    {
      free(m_aP);
      m_aP = NULL;
    }
  if(m_aL)
    {
      free(m_aL);
      m_aL = NULL;
    }
}

void diffusion1D::initArray()
{
  freeArray();
  m_aW = (double*)malloc(sizeof(double)*m_meshNode);
  m_aE = (double*)malloc(sizeof(double)*m_meshNode);
  m_aP0= (double*)malloc(sizeof(double)*m_meshNode);
  m_aP = (double*)malloc(sizeof(double)*m_meshNode);
  m_aL = (double*)malloc(sizeof(double)*m_meshNode);
}

void diffusion1D::calcaE()
{
  for(int i=0; i<m_meshNode; i++)
    {
      simuInfo* pCache = p_service->info()->at(i);
      m_aE[i] = pCache->labde * pCache->areae / pCache->xe;
    }
}

void diffusion1D::calcaW()
{
  for(int i=0; i<m_meshNode; i++)
    {
      simuInfo* pCache = p_service->info()->at(i);
      m_aW[i] = pCache->labdw * pCache->areaw / pCache->xw;
    }
}

void diffusion1D::calcaP0()
{
  double deltaT = p_service->globalPrarm()->deltaT;
  double f = p_service->globalPrarm()->f;
  double Sp = p_service->globalPrarm()->Sp;
  for(int i=0; i<m_meshNode; i++)
    {
      simuInfo* pCache = p_service->info()->at(i);
      m_aP0[i] = pCache->density * (pCache->heatCapw*pCache->xw +
				    pCache->heatCape*pCache->xe)
	* pCache->areap / deltaT
	- (1-f)*(m_aE[i] + m_aW[i]) + (1-f)*Sp*pCache->areap*pCache->cellLenght;
    }
}

double diffusion1D::calcaP()
{
  double f = p_service->globalPrarm()->f;
  double Sp = p_service->globalPrarm()->Sp;
  for(int i=0; i<m_meshNode; i++)
    {
      simuInfo* pCache = p_service->info()->at(i);
      m_aP[i] = f*m_aE[i] + f*m_aW[i] + m_aP0[i] - f*Sp*pCache->areap*pCache->cellLenght;
    }
}

double diffusion1D::calcaL()
{
  double Sc = p_service->globalPrarm()->Sc;
  for(int i=0; i<m_meshNode; i++)
    {
      simuInfo* pCache = p_service->info()->at(i);
      dCache = Sc*pCache->areap*pCache->cellLenght;
    }
}
