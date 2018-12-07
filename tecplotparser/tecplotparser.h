#ifndef TECPLOTPARSER_H
#define TECPLOTPARSER_H

struct TecplotContent

class TecplotParser
{
 public:
  TecplotParser(const wchar* strFileName);

  bool getValue(int nFrameIndex, int nZoneIndex, const std::vector<int>& vecIndex, std::vector<double>& vecData);

 private:
  void readFrame(const QString& oFirstLine, const QTextStream& oIn);
  void readZone(const QString& oFirstLine, const QTextStream& oIn);
  
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
