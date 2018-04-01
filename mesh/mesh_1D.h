#ifndef MESH_1D_H
#define MESH_1D_H

#include<QWidget>
#include"ZTtype.h"

class ZTService;

class Mesh1D
{
 public:
  Mesh1D(ZTService* pService);
  ~Mesh1D(){}
  void run();

 private:
  ZTService* m_pService;
  MeshRes* m_pData;
  GlobalParam* m_pGlobalParam;
  LocalParam* m_pLocalParam;
};

#endif
