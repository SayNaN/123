#ifndef ZTTYPE_H
#define ZTTYPE_H

#include<vector>
#include"cspline/cspline.h"

enum BoundaryConditionType
{
  FirstClass = 0,
  SecondClass,
  ThirdClass,
};

enum NodeType
{
  CELLCENTER = 0,            // 节点在节点内部
  MESHNODE,           // 节点在网格界面上
};

enum SimuType
{
  Diffuse_1D,
  Convective_Diffusion_1D,
  
  Diffuse_2D,
  Convective_Diffusion_2D,
  
  Diffuse_3D,
  Convective_Diffusion_3D,
};

struct SimuInfoRes
{
  double dCoorX;
  double dXw;
  double dXe;
  double dCellLenght;
  double dLabdw;
  double dLabde;
  double dHpw;
  double dHpe;
  double dAreap;
  double dAreaw;
  double dAreae;
  double dHeatCapMulDensity;
  //double dDensity;
  std::vector<std::pair<double, double>> vecTime_Temperature;
};
typedef std::vector<SimuInfoRes> MeshRes;

struct TabCellContent
{
  double dLength;
  int    nSubMeshNum;
  double dStartP;
  double dHeatCap;
  double dDensity;
  double dThermalConductivity;
  QString sThermalConductivityFilePath;
  Cspline oCspline;
  double dArea;
};
typedef std::vector<TabCellContent> LocalParam; 

struct GlobalParam
{
  NodeType nType;
  double dF;
  double dSc;
  double dSp;           // heat source const part
  double dDeltaT;       // time step
  double dInitTemperature;
  unsigned int nTimeStep;
  unsigned int nSegNum;
  unsigned int nMeshNum;
  
  BoundaryConditionType eInletType;
  double dInletTemp;
  double dInletHeatFlux;
  QString strInletHeatFluxFilePath;
  Cspline oInletHeatFluxFunc;
  double dInletInfinityTemp;
  double dInletConvectiveCoeff;

  BoundaryConditionType eOutletType;
  double dOutletTemp;
  double dOutletHeatFlux;
  QString strOutHeatFluxFilePath;
  Cspline oOutHeatFluxFunc;
  double dOutletInfinityTemp;
  double dOutletConvectiveCoeff;
};

#endif
