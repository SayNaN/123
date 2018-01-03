#ifndef ZTTYPE_H
#define ZTTYPE_H

#include"vector.h"

enum NodeType
  {
    CELLCENTER,            // 节点在节点内部
    MESHNODE,           // 节点在网格界面上
  };

struct simuInfo
{
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
};

#typedef std::vector<simuInfo> ZTSimuInfo;
#typedef std::vector< std::vector<double> > ZTRes;

struct LocalParam
{
  double heatCap;
  double density;
};

#typedef std::vector<LocalParam> ZTLocalParam; 

struct ZTGlobalParam
{
  NodeType type;
  double f;
  double Sc;
  double Sp;
  double deltaT;
};

#endif
