#ifndef ZTTYPE_H
#define ZTTYPE_H

#include"vector.h"

enum NodeType
  {
    INTHECELL,            // 节点在节点内部
    ONTHEBOUND,           // 节点在网格界面上
  };

struct meshInfo
{
  double coorX;
  double xw;
  double xwp;             // xe+
  double xwm;             // xe-
  double xe;
  double xep;
  double xem;
};

#typedef std::vector<double> ZTMesh;
#typedef std::vector<mesh> ZTRes;

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
};


struct ZTParm
{
  std::vector<ZTLocalParam> localParam; 
  ZTGlobalParam globalParam;
};

#endif
