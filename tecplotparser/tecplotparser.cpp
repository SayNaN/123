#include"tecplotparser.h"

enum ZoneType
  {
    BLOCK,
    POINT,
    FEPOINT
  };

struct ZoneBlock
{
  ZoneType eType;
  std::vector<int> vecDim;
  std::vector<double> vecData;
  std::vector<int> vecIndex;
};

struct FrameBlock
{
  QStringList strDim;
  std::vector<ZoneBlock> vecZone;
};

struct TecplotContent
{
  QString strTitle;
  std::vector<FrameBlock> vecFrames;
};

const QRegExp oTitle("^\\s*title\\s*=\\s*\".*\".*$");
  
const QRegExp oVariables("^\\s*variables\\s*=\\s*\".*\"(,\".*\")*.*$");
const QRegExp oCapString("\".*\"\\s*,?");

const QRegExp oZone("^\\s*zone\\s*=\\s*(\\D+\\s*=\\s*.*)(,\\D+\\s*=\\s*.*)$");
const QRegExp oCapDim("=\\s*\\d+\\s*,?");
const QRegExp oCapStructType("(block|point|fepoint)");
const QRegExp oCapInt("\\d+");

const QRegExp oCapValue("(\\s|^)[+|-]?\\d*(\\.\\d*)?(e[+|-]\\d+)?(\\s|$)");

TecplotParser::TecplotParser(const wchar* strFileName)
  :m_bOpenSuc(true)
{
  QString oFileName = QString::fromWCharArray(strFileName);
  QFile oFile(oFileName);

  if(!oFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
      qInfo()<<tr("无法打开:")<<oFileName;
      m_bOpenSuc = false;
      return;
    }
  QTextStream oIn(*oFile);
  QString oStrTmp;
  while(!oIn.atEnd())
    {
      oStrTmp = oIn.readLine().toLower();
      if(oTitle.exactMatch(oStrTmp))
	{
	  m_oData.strTitle = oCapString.cap();
	}
      else if(oVariables.exactMatch(oStrTmp))
	{
	  readFrame(oStrTmp, oIn);
	}
    }
  oFile.close();
}

void TecplotParser::readFrame(const QString& oFirstLine, const QTextStream& oIn)
{
  if(-1 == oCapString.indexIn(oFirstLine))
    {
      return;
    }
  m_oData.vecFrames.push_back(FrameBlock());
  m_oData.vecFrames.back().strDim = oCapString.capturedTexts();
  QString oStrTmp;
  while(!oIn.atEnd())
    {
      oStrTmp = oIn.readLine().toLower();
      if(oZone.exactMatch(oStrTmp))
	{
	  readZone(oStrTmp, oIn);
	}
    }
}
  
void TecplotParser:readZone(const QString& oFirstLine, const QTextStream& oIn)
{
  if(-1 == oCapDim.indexIn(oFirstLine))
    {
      return;
    }
  m_oData.vecFrames.back().vecZone.push_back(ZoneBlock());
  ZoneBlock* pZone = &(m_oData.vecFrames.back().vecZone.back());
  
  pZone->vecDim.resize(oCapDim.captureCount());
  int nTotalCount = 1;
  for(int i=0; i<oCapDim.captureCount(); ++i)
    {
      pZone->vecDim[i] = oCapDim.cap(i).toInt();
      nTotalCount *= pZone=>vecDim[i];
    }
  if(-1 == oCapStructType.indexIn(oFirstLine))
    {
      pZone->eType = POINT;
    }
  else
    {
      QString strType = oCapStructType.cap();
      if("block" == strType)
	{
	  pZone->eType = BLOCK;
	}
      else if("point" == strType)
	{
	  pZone->eType = POINT;
	}
      else
	{
	  pZone->eType = FEPOINT;
	}
    }

  QString oStrTmp;
  while(!oIn.atEnd())
    {
      oStrTmp = oIn.readLine().toLower();
      if(-1 != oCapValue.indexIn(oStrTmp))
	{
	  for(int i=0; i<oCapValue.captureCount(); ++i)
	    {
	      pZone->vecData.push_back(oCapValue.cap(i).toDouble());
	    }
	}
      else if(oVariables.exactMatch(oStrTmp))
	{
	  readFrame(oStrTmp, oIn);
	}
      if(oZone.exactMatch(oStrTmp))
	{
	  readZone(oStrTmp, oIn);
	}
    }
}

int TecplotParser::getFrameCount()
{
  return m_oData.vecFrames.size();
}

int TecplotParser::getZoneCount(int nFrameIndex)
{
  if(m_oData.vecFrames.size() <= nFrameIndex)
    {
      return -1;
    }
  return m_oData.vecFrames[nFrameIndex].vecZone.size();
}

bool TecplotParser::getValue(int nFrameIndex, int nZoneIndex, const std::vector<int>& vecDim, std::vector<double>& vecData)
{
  if(m_oData.vecFrames.size() <= nFrameIndex ||
     m_oData.vecFrames[nFrameIndex].vecZone.size() <= nZoneIndex)
    {
      return false;
    }
  vecDim  = m_oData.vecFrames[nFrameIndex].vecZone[nZoneIndex].vecDim;
  vecData = m_oData.vecFrames[nFrameIndex].vecZone[nZoneIndex].vecData;
  return true;
}
