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

double diffusion1D::calcAE()
{
  double
}
