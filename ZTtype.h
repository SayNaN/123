#ifndef ZTTYPE_H
#define ZTTYPE_H

#include"vector.h"

enum NodeType{
  CELLCENTER,            // 节点在节点内部
  MESHNODE,           // 节点在网格界面上
};

enum SimuType{
  Diffuse_1D,
  Convective_Diffusion_1D,
  
  Diffuse_2D,
  Convective_Diffusion_2D,
  
  Diffuse_3D,
  Convective_Diffusion_3D,
};

struct SimuInfoRes{
  double coorX;
  double xw;
  double xe;
  double cellLenght;
  double labdw;
  double labde;
  double hpw;
  double hpe;
  double areap;
  double areaw;
  double areae;
  double heatCap;
  double density;
  std::map<double, double> Res;
};

#typedef std::vector<SimuInfoRes> MeshRes;

struct TabCellContent{
  double length;
  int    subMeshNum;
  double startP;
  double heatCap;
  double density;
  double thermalConductivity;
  double area;
};

#typedef std::vector<TabCellContent> LocalParam; 

struct GlobalParam
{
  NodeType type;
  double f;
  double Sc;
  double Sp;           // heat source const part
  double deltaT;       // time step
  int segNum;
  int meshNum;
};

#endif
