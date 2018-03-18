#include<QtWidgets>
#include"leftwidget.h"


LeftWidget::LeftWidget(ZTService *pService, QWidget *parent):
  QFrame(parent),m_pService(pService)
{
  initializeUI();
}

void LeftWidget::initializeUI()
{
  int nLineNum=0;

  QGroupBox *pGlobalParamGrp = new QGroupBox(QString::fromLocal8Bit("全局参数"));

  QLabel *pTimeStepLabel = new QLabel(QString::fromLocal8Bit("时间步长"));
  m_pTimeStepEdit = new QLineEdit(QString::number(m_pService->globalParam()->dDeltaT));
  connect(m_pTimeStepEdit, &QLineEdit::editingFinished, [this](){
      bool b;
      double dCache;
      dCache = m_pTimeStepEdit->text().toDouble(&b);
      if(b){
	m_pService->globalParam()->dDeltaT = dCache;
      }else{
	m_pTimeStepEdit->setText(QString::number(m_pService->globalParam()->dDeltaT));
      }
    });

  QLabel *pStepNumLabel = new QLabel(QString::fromLocal8Bit("计算步数"));
  m_pStepNumEdit = new QLineEdit(QString::number(m_pService->globalPrarm()->nTimeStep));
  connect(m_pStepNumEdit, &QLineEdit::editingFinished, [this](){
      bool b;
      int nCache;
      nCache = m_pStepNumEdit->text().toInt(&b);
      if(b){
	m_pService->globalPrarm()->nTimeStep = nCache;
      }else{
	m_pStepNumEdit->setText(QString::number(m_pService->globalPrarm()->nTimeStep));
      }
    });

  QLabel *pTimeSchemeLable = new QLabel(QString::fromLocal8Bit("时间离散格式(0:显式~1:隐式)"));
  m_pTimeSchemeEdit = new QLineEdit(QString::number(ZTService::getInstance->globalPrarm()->f));
  connect(m_pTimeSchemeEdit, &QLineEdit::editingFinished, [this](){
      bool b;
      double dCache;
      dCache = m_pTimeStepEdit->text().toDouble(&b);
      if(b){
	if(dCache>=1.0){
	  m_pTimeSchemeEdit->setText(QString::number(1));
	  m_pService->globalPrarm()->dF = 1.0;
	}else if(dCache<=0){
	  m_pTimeSchemeEdit->setText(QString::number(0));
	  m_pService->globalPrarm()->dF = 0.0;
	}else{
	  m_pService->globalPrarm()->dF = dCache;
	}
      }else{
	m_pTimeSchemeEdit->setText(QString::number(m_pService->globalPrarm()->dF));
      }
    });

  QLabel *pInitTempLabel = new QLabel(QString::fromLocal8Bit("初始温度(k)"));
  m_pInitTempEdit = new QLineEdit(QString::number(m_pService->globalPrarm()->dInitTemperature));
  connect(m_pInitTempEdit, &QLineEdit::editingFinished, [this](){
      bool b;
      double dCache;
      dCache = m_pInitTempEdit->text().toDouble(&b);
      if(b){
	m_pService->globalPrarm()->dInitTemperature = dCache;
      }else{
	m_pInitTempEdit->setText(QString::number(m_pService->globalPrarm()->dInitTemperature));
      }
    });

  QLabel *pCalcSchemeLabel = new QLabel(QString::fromLocal8Bit("计算格式"));
  m_pCalcSchemeBox = new QComboBox;
  m_pCalcSchemeBox->addItem(QString::fromLocal8Bit("内节点"));
  m_pCalcSchemeBox->addItem(QString::fromLocal8Bit("外节点"));
  m_pCalcSchemeBox->setCurrentIndex(0);
  connect(m_pCalcSchemeBox, &QComboBox::currentIndexChanged, [this](int nIndex){
      if(nIndex==0){
	m_pService->globalPrarm()->nType = CELLCENTER;
      }else{
	m_pService->globalPrarm()->nType = MESHNODE;
      }
    });
  QGridLayout* pGlobalParamLayout = new QGridLayout(pGlobalParamGrp);
  linenum = 0;
  pGlobalParamLayout->addWidget(pTimeStepLabel, linenum, 0);
  pGlobalParamLayout->addWidget(m_pTimeStepEdit,  linenum, 1);
  linenum++;
  pGlobalParamLayout->addWidget(pStepNumLabel, linenum, 0);
  pGlobalParamLayout->addWidget(m_pStepNumEdit, linenum ,1);
  linenum++;
  pGlobalParamLayout->addWidget(pTimeSchemeLable, linenum, 0);
  pGlobalParamLayout->addWidget(m_pTimeSchemeEdit, linenum, 1);
  linenum++;
  pGlobalParamLayout->addWidget(pInitTempLabel, linenum, 0);
  pGlobalParamLayout->addWidget(m_pInitTempEdit, linenum, 1);
  linenum++;
  pGlobalParamLayout->addWidget(calcSchemeLabel, linenum, 0);
  pGlobalParamLayout->addWidget(calcSchemeBox,   linenum, 1);

  QGroupBox *pLocalParamGrp = new QGroupBox(QString::fromLocal8Bit("各段参数"));
  
  m_pTableWidget = new QTableWidget(1, 5, pLocalParamGrp);
  QStringList oHoriHeader;
  oHoriHeader<<QString::fromLocal8Bit("段长度")
	     <<QString::fromLocal8Bit("网格数")
	     <<QString::fromLocal8Bit("热容")
	     <<QString::fromLocal8Bit("密度")
	     <<QString::fromLocal8Bit("导热系数");
  m_pTableWidget->setHorizontalHeaderLabels(oHoriHeader);    

  m_pRightMenu=new QMenu(m_pTableWidget);
  m_pTableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
  QAction* pAddSeg    = new QAction(QString::fromLocal8Bit("添加导热段"));
  QAction* pRemoveSeg = new QAction(QString::fromLocal8Bit("删除导热段"));
  m_pRightMenu->addAction(pAddSeg);
  m_pRightMenu->addAction(pRemoveSeg);

  connect(m_pTableWidget, &QWidget::customContextMenuRequested, [this](QPoint &pos){
      rightMenu->exec(QCursor::pos()); 
    });
  
  connect(pAddSeg, &QAction::triggered, [this](){
      m_pTableWidget->insertRow(m_pTableWidget->currentIndex());
      m_pService->addSegment(m_pTableWidget->currentIndex());
      refreshTable();
    });
  
  connect(pRemoveSeg, &QAction::triggered, [this](){
      m_pTableWidget->removeRow(m_pTableWidget->currentIndex());
      m_pService->removeSegment(m_pTableWidget->currentIndex());
      refreshTable();
    });
  QGridLayout* pLocalParamLayout = new QGridLayout(pLocalParamGrp);
  linenum =0;
  pLocalParamLayout->addWidget(m_pTableWidget, linenum, 0);

  QGroupBox* pBoundarySettingGrp = new QGroupBox(QString::fromLocal8Bit("边界条件"));
  QGroupBox* pInletBoundaryGrp = new QGroupBox(QString::fromLocal8Bit("进口边界"));
  QLabel *pInletBoundaryTypeLabel = new QLabel(QString::fromLocal8Bit("边界类型"));
  m_pInletBoundaryTypeBox = new QComboBox;
  m_pInletBoundaryTypeBox->addItem(QString::fromLocal8Bit("第一类边界条件"));
  m_pInletBoundaryTypeBox->addItem(QString::fromLocal8Bit("第二类边界条件"));
  m_pInletBoundaryTypeBox->addItem(QString::fromLocal8Bit("第三类边界条件"));

  QFrame *pInletFirstTypeFrame = new QFrame;
  QLabel *pInletTempLabel = new QLabel(QString::fromLocal8Bit("进口温度"));
  m_pInletTempEdit = new QLineEdit(QString::number(m_pService->globalPrarm()->dInletTemp));
  connect(m_pInletTempEdit, &QLineEdit::editingFinished, [this](){
      bool b;
      double dCache;
      nCache = m_pInletTempEdit->text().toDouble(&b);
      if(b){
	m_pService->globalPrarm()->dInletTemp = nCache;
      }else{
	m_pInletTempEdit->setText(QString::number(m_pService->globalPrarm()->dInletTemp));
      }
    });
  QGridLayout *pInletFirstTypeLayout = new QGridLayout(pInletFirstTypeFrame);
  nLineNum = 0;
  pInletFirstTypeLayout->addWidget(pInletTempLabel, nLineNum, 0);
  pInletFirstTypeLayout->addWidget(m_pInletTempEdit, nLineNum, 1);
  
  QFrame *pInletSecondTypeFrame = new QFrame;
  QLabel *pInletHeatFluxLabel = new QLabel(QString::fromLocal8Bit("进口热流"));
  m_pInletHeatFluxEdit = new QLineEdit(QString::number(m_pService->globalPrarm()->dInletHeatFlux));
  connect(m_pInletHeatFluxEdit, &QLineEdit::editingFinished, [this](){
      bool b;
      double dCache;
      nCache = m_pInletHeatFluxEdit->text().toDouble(&b);
      if(b){
	m_pService->globalPrarm()->dInletHeatFlux = nCache;
      }else{
	m_pInletHeatFluxEdit->setText(QString::number(m_pService->globalPrarm()->dInletHeatFlux));
      }
    });
  QGridLayout *pInletSecondTypeLayout = new QGridLayout(pInletSecondTypeFrame);
  nLineNum = 0;
  pInletSecondTypeLayout->addWidget(pInletHeatFluxLabel, nLineNum, 0);
  pInletSecondTypeLayout->addWidget(m_pInletHeatFluxEdit, nLineNum, 1);

  QFrame *pInletThirdTypeFrame = new QFrame;
  QLabel *pInletInfinityTempLabel = new QLabel(QString::fromLocal8Bit("环境温度(k)"));
  m_pInletInfinityTempEdit = new QLineEdit(QString::number(m_pService->globalPrarm()->dInletInfinityTemp));
  connect(m_pInletInfinityTempEdit, &QLineEdit::editingFinished, [this](){
      bool b;
      double dCache;
      nCache = m_pInletInfinityTempEdit->text().toDouble(&b);
      if(b){
	m_pService->globalPrarm()->dInletInfinityTemp = nCache;
      }else{
	m_pInletInfinityTempEdit->setText(QString::number(m_pService->globalPrarm()->dInletInfinityTemp));
      }
    });

  QLabel *pInletConvectiveCoeffLabel = new QLabel(QString::fromLocal8Bit("对流系数"));
  m_pInletConvectiveCoeffEdit = new QLineEdit(QString::number(m_pService->globalPrarm()->dInletConvectiveCoeff));
  connect(m_pInletConvectiveCoeffEdit, &QLineEdit::editingFinished, [this](){
      bool b;
      double dCache;
      nCache = m_pInletConvectiveCoeffEdit->text().toDouble(&b);
      if(b){
	m_pService->globalPrarm()->dInletConvectiveCoeff = nCache;
      }else{
	m_pInletConvectiveCoeffEdit->setText(QString::number(m_pService->globalPrarm()->dInletConvectiveCoeff));
      }
    });

  QGridLayout* pInletThirdTypeLayout = new QGridLayout(pInletThirdTypeFrame);
  linenum = 0; 
  pInletThirdTypeLayout->addWidget(pInletInfinityTempLabel, linenum, 0);
  pInletThirdTypeLayout->addWidget(m_pInletInfinityTempEdit, linenum, 1);
  linenum ++;
  pInletThirdTypeLayout->addWidget(pInletConvectiveCoeffLabel, linenum, 0);
  pInletThirdTypeLayout->addWidget(m_pInletConvectiveCoeffEdit, linenum, 1);

  QStackedLayout* pInletBoundaryStackedLayout = new QStackedLayout;
  pInletBoundaryStackedLayout->addWidget(pInletFirstTypeFrame);
  pInletBoundaryStackedLayout->addWidget(pInletSecondTypeFrame);
  pInletBoundaryStackedLayout->addWidget(pInletThirdTypeFrame);

  connect(m_pInletBoundaryTypeBox, SIGNAL(activated(int)),
	  pInletBoundaryStackedLayout, SLOT(setCurrentIndex(int)));

  QGridLayout* pInletBoundaryLayout = new QGridLayout(pInletBoundaryGrp);
  linenum = 0;
  pInletBoundaryLayout->addWidget(pInletBoundaryTypeLabel, linenum, 0);
  pInletBoundaryLayout->addWidget(m_pInletBoundaryTypeBox, linenum, 1);
  linenum ++;
  pInletBoundaryLayout->addLayout(pInletBoundaryStackedLayout, linenum, 0, 1, 2);
  
  QGroupBox* pOutletBoundaryGrp = new QGroupBox(QString::fromLocal8Bit("出口边界"));
  QLabel *pOutletBoundaryTypeLabel = new QLabel(QString::fromLocal8Bit("边界类型"));
  m_pOutletBoundaryTypeBox = new QComboBox;
  m_pOutletBoundaryTypeBox->addItem(QString::fromLocal8Bit("第一类边界条件"));
  m_pOutletBoundaryTypeBox->addItem(QString::fromLocal8Bit("第二类边界条件"));
  m_pOutletBoundaryTypeBox->addItem(QString::fromLocal8Bit("第三类边界条件"));

  QFrame *pOutletFirstTypeFrame = new QFrame;
  QLabel *pOutletTempLabel = new QLabel(QString::fromLocal8Bit("出口温度"));
  m_pOutletTempEdit = new QLineEdit(QString::number(m_pService->globalPrarm()->dOutletTemp));
  connect(m_pOutletTempEdit, &QLineEdit::editingFinished, [this](){
      bool b;
      double dCache;
      nCache = m_pOutletTempEdit->text().toDouble(&b);
      if(b){
	m_pService->globalPrarm()->dOutletTemp = nCache;
      }else{
	m_pOutletTempEdit->setText(QString::number(m_pService->globalPrarm()->dOutletTemp));
      }
    });
  QGridLayout *pOutletFirstTypeLayout = new QGridLayout(pOutletFirstTypeFrame);
  nLineNum = 0;
  pOutletFirstTypeLayout->addWidget(pOutletTempLabel, nLineNum, 0);
  pOutletFirstTypeLayout->addWidget(m_pOutletTempEdit, nLineNum, 1);
  
  QFrame *pOutletSecondTypeFrame = new QFrame;
  QLabel *pOutletHeatFluxLabel = new QLabel(QString::fromLocal8Bit("出口热流"));
  m_pOutletHeatFluxEdit = new QLineEdit(QString::number(m_pService->globalPrarm()->dOutletHeatFlux));
  connect(m_pOutletHeatFluxEdit, &QLineEdit::editingFinished, [this](){
      bool b;
      double dCache;
      nCache = m_pOutletHeatFluxEdit->text().toDouble(&b);
      if(b){
	m_pService->globalPrarm()->dOutletHeatFlux = nCache;
      }else{
	m_pOutletHeatFluxEdit->setText(QString::number(m_pService->globalPrarm()->dOutletHeatFlux));
      }
    });
  QGridLayout *pOutletSecondTypeLayout = new QGridLayout(pOutletSecondTypeFrame);
  nLineNum = 0;
  pOutletSecondTypeLayout->addWidget(pOutletHeatFluxLabel, nLineNum, 0);
  pOutletSecondTypeLayout->addWidget(m_pOutletHeatFluxEdit, nLineNum, 1);
  
  QFrame *pOutletThirdTypeFrame = new QFrame;
  QLabel *pOutletInfinityTempLabel = new QLabel(QString::fromLocal8Bit("环境温度(k)"));
  m_pOutletInfinityTempEdit = new QLineEdit(QString::number(m_pService->globalPrarm()->dOutletInfinityTemp));
  connect(m_pOutletInfinityTempEdit, &QLineEdit::editingFinished, [this](){
      bool b;
      double dCache;
      nCache = m_pOutletInfinityTempEdit->text().toDouble(&b);
      if(b){
	m_pService->globalPrarm()->dOutletInfinityTemp = nCache;
      }else{
	m_pInletInfinityTempEdit->setText(QString::number(m_pService->globalPrarm()->dInletInfinityTemp));
      }
    });
    
  QLabel *pOutletConvectiveCoeffEdit; = new QLabel(QString::fromLocal8Bit("对流系数"));
  m_pOutletConvectiveCoeffEdit = new QLineEdit(QString::number(m_pService->globalPrarm()->dOutletConvectiveCoeff));
  connect(m_pOutletConvectiveCoeffEdit, &QLineEdit::editingFinished, [this](){
      bool b;
      double dCache;
      nCache = m_pOutletConvectiveCoeffEdit->text().toDouble(&b);
      if(b){
	m_pService->globalPrarm()->dOutletConvectiveCoeff = nCache;
      }else{
	m_pOutletConvectiveCoeffEdit->setText(QString::number(m_pService->globalPrarm()->dOutletConvectiveCoeff));
      }
    });

  QGridLayout* pOutletThirdTypeLayout = new QGridLayout(pOutletThirdTypeFrame);
  linenum = 0; 
  pOutletThirdTypeLayout->addWidget(pOutletInfinityTempLabel, linenum, 0);
  pOutletThirdTypeLayout->addWidget(m_pOutletInfinityTempEdit, linenum, 1);
  linenum ++;
  pOutletThirdTypeLayout->addWidget(pOutletConvectiveCoeffLabel, linenum, 0);
  pOutletThirdTypeLayout->addWidget(m_pOutletConvectiveCoeffEdit, linenum, 1);

  QStackedLayout* pOutletBoundaryStackedLayout = new QStackedLayout;
  pOutletBoundaryStackedLayout->addWidget(pOutletFirstTypeFrame);
  pOutletBoundaryStackedLayout->addWidget(pOutletSecondTypeFrame);
  pOutletBoundaryStackedLayout->addWidget(pOutletThirdTypeFrame);

  connect(m_pOutletBoundaryTypeBox, SIGNAL(activated(int)),
	  pOutletBoundaryStackedLayout, SLOT(setCurrentIndex(int)));

  QGridLayout* pOutletBoundaryLayout = new QGridLayout(pOutletBoundaryGrp);
  linenum = 0;
  pOutletBoundaryLayout->addWidget(pOutletBoundaryTypeLabel, linenum, 0);
  pOutletBoundaryLayout->addWidget(m_pOutletBoundaryTypeBox, linenum, 1);
  linenum ++;
  pOutletBoundaryLayout->addLayout(pOutletBoundaryStackedLayout, linenum, 0, 1, 2);

  QGridLayout *pBoundarySettingLayout = new QGridLayout(pBoundarySettingGrp);
  linenum = 0;
  pBoundarySettingLayout->addWidget(pInletBoundaryGrp, linenum, 0);
  linenum ++;
  pBoundarySettingLayout->addWidget(pOutletBoundaryGrp, linenum ,0);

  QGridLayout *pMainLayout = new QGridLayout(this);
  linenum = 0;
  pMainLayout->addWidget(pGlobalParamGrp, linenum, 0);
  linenum ++;
  pMainLayout->addWidget(pLocalParamGrp, linenum, 0);
  linenum ++;
  pMainLayout->addWidget(pBoundarySettingGrp, linenum, 0);
}

void LeftWidget::refreshTable()
{
  LocalParam* pTmp = m_pService->LocalParam();
  for(int i=0; i<pTemp->size(); i++)
    {
      tableWidget->item(i, 0)->setText(QString::number(pTmp->at[i].dLength));
      tableWidget->item(i, 1)->setText(QString::number(pTmp->at[i].nSubMeshNum));
      tableWidget->item(i, 2)->setText(QString::number(pTmp->at[i].dHeatCap));
      tableWidget->item(i, 3)->setText(QString::number(pTmp->at[i].dDensity));
      tableWidget->item(i, 4)->setText(QString::number(pTmp->at[i].dThermalConductivity));
    }
}
