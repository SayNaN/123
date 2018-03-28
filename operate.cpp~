#include<QWidget>

#include"operate.h"

Operate::Operate(ZTService *pService):
  m_pService(pService),
  m_sFullProjectPath(""),
  m_sProjectPath(""),
  m_sProjectName(""),
  m_sResFileName("")
{
}

void Operate::readProjectFile()
{
  
}

void Operate::setProjectName(QString sText)
{
  m_sFullProjectPath = sText;
  m_sProjectPath = sText.section("/",0,-2)+tr("/");
  m_sProjectName = sText.section("/",-1,-1).section(".",0,0);
}

QString Operate::getProjectName()
{
  return m_sProjectName;
}

void Operate::writeProjectFile()
{
  
}

void Operate::writeResFile(QString sText)
{
  
}
