#include"ZTservice.h"

ZTservice* ZTService::getInstance()
{
  if(NULL == p_instance)
    {
      p_instance = new ZTservice();
    }
  return p_instance;
}

ZTMesh* ZTService::mesh()
{
  return m_Mesh;
}

ZTGlobalParam* ZTService::globalParam()
{
  return m_GlobalParam();
}

ZTRes* ZTService::res()
{
  return m_Res();
}

ZTLocalParam* ZTService::localParam()
{
  return m_LocalParam();
}
