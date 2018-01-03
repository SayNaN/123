#include <stdio.h>
#include <stdlib.h>

diffusion1D* diffusion1D::p_instance = NULL;

diffusion1D::diffusion1D(QObject* parent): QThread(parent)
{}

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
  
}

double diffusion1D::calcaE()
{
  double dCache;
  dCache = labde * areae / xe;
}

double diffusion1D::calcaW()
{
  double dCache;
  dCache = labdw * areaw / xw;
}

double diffusion1D::calcaP0()
{
  double dCache;
  dCache = density * (heatCapw*xw + heatCape*xe) * areap / deltaT
    - (1-f)*(aE + aW) + (1-f)*Sp*Ap*(xe+xw);
}

double diffusion1D::calcaP()
{
  double dCache;
  dCache = f*aE + f*aW + aP0 - f*Sp*areap*(xe+xw);
}

double diffusion1D::calcaL()
{
  double dCache;
  dCache = Sc*areap*(xe+xw);
}
