#ifndef TECPLOTPARSER_H
#define TECPLOTPARSER_H

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

class TecplotParser : public QObject
{
 public:
  TecplotParser(const QString strFileName);

  int getFrameCount();

  int getZoneCount(int nFrameIndex);

  bool getValue(int nFrameIndex, int nZoneIndex, std::vector<int>& vecDim, std::vector<double>& vecData);

 private:
  void readFrame(const QString& oFirstLine, QTextStream& oIn);
  void readZone(const QString& oFirstLine, QTextStream& oIn);
  
  TecplotContent m_oData;
  bool m_bOpenSuc;
};

/*
Title="example: 2d finite-element data"
variables ="x","y","S1"
zone N=8,E=3, datapacking=block
varlocation=([3]=cellcentered)
zonetype=fequadrilateral
0 0 0 0 1 1 1 1 
0 1 2 3 0 1 2 3
10
-5
1.0
1 5 6 2
2 6 7 3
3 7 8 4
*/

#endif //TECPLOTPARSER_H
