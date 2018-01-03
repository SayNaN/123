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

#typedef std::vector<meshInfo> ZTMesh;
#typedef std::vector< std::vector<double> > ZTRes;

struct ZTLocalParam
{
  double heatCap;
  double density;
};

struct ZTGlobalParam
{
  NodeType type;
  double f;
  double Sc;
  double Sp;
  double deltaT;
};


struct ZTParm
{
  std::vector<ZTLocalParam> localParam; 
  ZTGlobalParam globalParam;
};

#endif
