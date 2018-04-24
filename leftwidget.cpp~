#include<QWidget>
#include<QObject>
#include<QDebug>
#include"leftwidget.h"
#include"ZTService.h"

LeftWidget::LeftWidget(ZTService *pService, QWidget *parent):
  QFrame(parent),m_pService(pService)
{
  initializeUI();
  refreshTable();
}

void LeftWidget::resetGUI()
{
  m_pTimeStepEdit->setText(QString::number(m_pService->globalParam()->dDeltaT));

  m_pStepNumEdit->setText(QString::number(m_pService->globalParam()->nTimeStep));

  m_pTimeSchemeEdit->setText(QString::number(m_pService->globalParam()->dF));

  m_pInitTempEdit->setText(QString::number(m_pService->globalParam()->dInitTemperature));

  m_pCalcSchemeBox->setCurrentIndex((int)(m_pService->globalParam()->nType));

  refreshTable();

  m_pInletBoundaryTypeBox->setCurrentIndex((int)(m_pService->globalParam()->eInletType));

  m_pInletTempEdit->setText(QString::number(m_pService->globalParam()->dInletTemp));
  
  m_pInletHeatFluxEdit->setText(QString::number(m_pService->globalParam()->dInletHeatFlux));

  m_pInletInfinityTempEdit->setText(QString::number(m_pService->globalParam()->dInletInfinityTemp));

  m_pInletConvectiveCoeffEdit->setText(QString::number(m_pService->globalParam()->dInletConvectiveCoeff));

  m_pOutletBoundaryTypeBox->setCurrentIndex((int)(m_pService->globalParam()->eOutletType));

  m_pOutletTempEdit->setText(QString::number(m_pService->globalParam()->dOutletTemp));

  m_pOutletHeatFluxEdit->setText(QString::number(m_pService->globalParam()->dOutletHeatFlux));

  m_pOutletInfinityTempEdit->setText(QString::number(m_pService->globalParam()->dOutletInfinityTemp));

  m_pOutletConvectiveCoeffEdit->setText(QString::number(m_pService->globalParam()->dOutletConvectiveCoeff));
}

void LeftWidget::initializeUI()
{
  int nLineNum=0;

  QGroupBox *pGlobalParamGrp = new QGroupBox(tr("全局参数"));

  QLabel *pTimeStepLabel = new QLabel(tr("时间步长"));
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

  QLabel *pStepNumLabel = new QLabel(tr("计算步数"));
  m_pStepNumEdit = new QLineEdit(QString::number(m_pService->globalParam()->nTimeStep));
  connect(m_pStepNumEdit, &QLineEdit::editingFinished, [this](){
      bool b;
      int nCache;
      nCache = m_pStepNumEdit->text().toInt(&b);
      if(b){
	m_pService->globalParam()->nTimeStep = nCache;
      }else{
	m_pStepNumEdit->setText(QString::number(m_pService->globalParam()->nTimeStep));
      }
    });

  QLabel *pTimeSchemeLable = new QLabel(tr("时间离散格式(0:显式~1:隐式)"));
  m_pTimeSchemeEdit = new QLineEdit(QString::number(m_pService->globalParam()->dF));
  connect(m_pTimeSchemeEdit, &QLineEdit::editingFinished, [this](){
      bool b;
      double dCache;
      dCache = m_pTimeStepEdit->text().toDouble(&b);
      if(b){
	if(dCache>=1.0){
	  m_pTimeSchemeEdit->setText(QString::number(1));
	  m_pService->globalParam()->dF = 1.0;
	}else if(dCache<=0){
	  m_pTimeSchemeEdit->setText(QString::number(0));
	  m_pService->globalParam()->dF = 0.0;
	}else{
	  m_pService->globalParam()->dF = dCache;
	}
      }else{
	m_pTimeSchemeEdit->setText(QString::number(m_pService->globalParam()->dF));
      }
    });

  QLabel *pInitTempLabel = new QLabel(tr("初始温度(k)"));
  m_pInitTempEdit = new QLineEdit(QString::number(m_pService->globalParam()->dInitTemperature));
  connect(m_pInitTempEdit, &QLineEdit::editingFinished, [this](){
      bool b;
      double dCache;
      dCache = m_pInitTempEdit->text().toDouble(&b);
      if(b){
	m_pService->globalParam()->dInitTemperature = dCache;
      }else{
	m_pInitTempEdit->setText(QString::number(m_pService->globalParam()->dInitTemperature));
      }
    });

  QLabel *pCalcSchemeLabel = new QLabel(tr("计算格式"));
  m_pCalcSchemeBox = new QComboBox;
  m_pCalcSchemeBox->addItem(tr("内节点"));
  m_pCalcSchemeBox->addItem(tr("外节点"));
  m_pCalcSchemeBox->setCurrentIndex(0);
  connect(m_pCalcSchemeBox, &QComboBox::currentTextChanged, [this](QString strText){
      if(tr("内节点") == strText){
	m_pService->globalParam()->nType = CELLCENTER;
      }else{
	m_pService->globalParam()->nType = MESHNODE;
      }
    });
  QGridLayout* pGlobalParamLayout = new QGridLayout(pGlobalParamGrp);
  nLineNum = 0;
  pGlobalParamLayout->addWidget(pTimeStepLabel, nLineNum, 0);
  pGlobalParamLayout->addWidget(m_pTimeStepEdit, nLineNum, 1);
  nLineNum++;
  pGlobalParamLayout->addWidget(pStepNumLabel, nLineNum, 0);
  pGlobalParamLayout->addWidget(m_pStepNumEdit, nLineNum ,1);
  nLineNum++;
  pGlobalParamLayout->addWidget(pTimeSchemeLable, nLineNum, 0);
  pGlobalParamLayout->addWidget(m_pTimeSchemeEdit, nLineNum, 1);
  nLineNum++;
  pGlobalParamLayout->addWidget(pInitTempLabel, nLineNum, 0);
  pGlobalParamLayout->addWidget(m_pInitTempEdit, nLineNum, 1);
  nLineNum++;
  pGlobalParamLayout->addWidget(pCalcSchemeLabel, nLineNum, 0);
  pGlobalParamLayout->addWidget(m_pCalcSchemeBox,   nLineNum, 1);

  QGroupBox *pLocalParamGrp = new QGroupBox(tr("各段参数"));
  
  m_pTableWidget = new QTableWidget(1, 5, pLocalParamGrp);
  QStringList oHoriHeader;
  oHoriHeader<<tr("段长度")
	     <<tr("网格数")
	     <<tr("热容")
	     <<tr("密度")
	     <<tr("导热系数");
  m_pTableWidget->setHorizontalHeaderLabels(oHoriHeader);
  
  m_pRightMenu=new QMenu(m_pTableWidget);
  m_pTableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
  QAction* pAddSeg    = new QAction(tr("添加导热段"));
  QAction* pRemoveSeg = new QAction(tr("删除导热段"));
  m_pRightMenu->addAction(pAddSeg);
  m_pRightMenu->addAction(pRemoveSeg);

  connect(m_pTableWidget, &QWidget::customContextMenuRequested, [this](const QPoint &pos){
      Q_UNUSED(pos);
      m_pRightMenu->exec(QCursor::pos()); 
    });
  
  connect(pAddSeg, &QAction::triggered, [this](){
      m_pService->addSegment(m_pTableWidget->currentRow()+1);
      refreshTable();
    });
  
  connect(pRemoveSeg, &QAction::triggered, [this](){
      m_pService->removeSegment(m_pTableWidget->currentRow());
      refreshTable();
    });
  QGridLayout* pLocalParamLayout = new QGridLayout(pLocalParamGrp);
  nLineNum =0;
  pLocalParamLayout->addWidget(m_pTableWidget, nLineNum, 0);

  QGroupBox* pBoundarySettingGrp = new QGroupBox(tr("边界条件"));
  QGroupBox* pInletBoundaryGrp = new QGroupBox(tr("进口边界"));
  QLabel *pInletBoundaryTypeLabel = new QLabel(tr("边界类型"));
  m_pInletBoundaryTypeBox = new QComboBox;
  m_pInletBoundaryTypeBox->addItem(tr("第一类边界条件"));
  m_pInletBoundaryTypeBox->addItem(tr("第二类边界条件"));
  m_pInletBoundaryTypeBox->addItem(tr("第三类边界条件"));

  QFrame *pInletFirstTypeFrame = new QFrame;
  QLabel *pInletTempLabel = new QLabel(tr("进口温度"));
  m_pInletTempEdit = new QLineEdit(QString::number(m_pService->globalParam()->dInletTemp));
  connect(m_pInletTempEdit, &QLineEdit::editingFinished, [this](){
      bool b;
      double dCache;
      dCache = m_pInletTempEdit->text().toDouble(&b);
      if(b){
	m_pService->globalParam()->dInletTemp = dCache;
      }else{
	m_pInletTempEdit->setText(QString::number(m_pService->globalParam()->dInletTemp));
      }
    });
  QGridLayout *pInletFirstTypeLayout = new QGridLayout(pInletFirstTypeFrame);
  nLineNum = 0;
  pInletFirstTypeLayout->addWidget(pInletTempLabel, nLineNum, 0);
  pInletFirstTypeLayout->addWidget(m_pInletTempEdit, nLineNum, 1);
  
  QFrame *pInletSecondTypeFrame = new QFrame;
  QLabel *pInletHeatFluxLabel = new QLabel(tr("进口热流"));
  m_pInletHeatFluxEdit = new QLineEdit(QString::number(m_pService->globalParam()->dInletHeatFlux));
  connect(m_pInletHeatFluxEdit, &QLineEdit::editingFinished, [this](){
      bool b;
      double dCache;
      dCache = m_pInletHeatFluxEdit->text().toDouble(&b);
      if(b){
	m_pService->globalParam()->dInletHeatFlux = dCache;
      }else{
	m_pInletHeatFluxEdit->setText(QString::number(m_pService->globalParam()->dInletHeatFlux));
      }
    });
  QGridLayout *pInletSecondTypeLayout = new QGridLayout(pInletSecondTypeFrame);
  nLineNum = 0;
  pInletSecondTypeLayout->addWidget(pInletHeatFluxLabel, nLineNum, 0);
  pInletSecondTypeLayout->addWidget(m_pInletHeatFluxEdit, nLineNum, 1);

  QFrame *pInletThirdTypeFrame = new QFrame;
  QLabel *pInletInfinityTempLabel = new QLabel(tr("环境温度(k)"));
  m_pInletInfinityTempEdit = new QLineEdit(QString::number(m_pService->globalParam()->dInletInfinityTemp));
  connect(m_pInletInfinityTempEdit, &QLineEdit::editingFinished, [this](){
      bool b;
      double dCache;
      dCache = m_pInletInfinityTempEdit->text().toDouble(&b);
      if(b){
	m_pService->globalParam()->dInletInfinityTemp = dCache;
      }else{
	m_pInletInfinityTempEdit->setText(QString::number(m_pService->globalParam()->dInletInfinityTemp));
      }
    });

  QLabel *pInletConvectiveCoeffLabel = new QLabel(tr("对流系数"));
  m_pInletConvectiveCoeffEdit = new QLineEdit(QString::number(m_pService->globalParam()->dInletConvectiveCoeff));
  connect(m_pInletConvectiveCoeffEdit, &QLineEdit::editingFinished, [this](){
      bool b;
      double dCache;
      dCache = m_pInletConvectiveCoeffEdit->text().toDouble(&b);
      if(b){
	m_pService->globalParam()->dInletConvectiveCoeff = dCache;
      }else{
	m_pInletConvectiveCoeffEdit->setText(QString::number(m_pService->globalParam()->dInletConvectiveCoeff));
      }
    });

  QGridLayout* pInletThirdTypeLayout = new QGridLayout(pInletThirdTypeFrame);
  nLineNum = 0; 
  pInletThirdTypeLayout->addWidget(pInletInfinityTempLabel, nLineNum, 0);
  pInletThirdTypeLayout->addWidget(m_pInletInfinityTempEdit, nLineNum, 1);
  nLineNum ++;
  pInletThirdTypeLayout->addWidget(pInletConvectiveCoeffLabel, nLineNum, 0);
  pInletThirdTypeLayout->addWidget(m_pInletConvectiveCoeffEdit, nLineNum, 1);

  QStackedLayout* pInletBoundaryStackedLayout = new QStackedLayout;
  pInletBoundaryStackedLayout->addWidget(pInletFirstTypeFrame);
  pInletBoundaryStackedLayout->addWidget(pInletSecondTypeFrame);
  pInletBoundaryStackedLayout->addWidget(pInletThirdTypeFrame);

  connect(m_pInletBoundaryTypeBox, SIGNAL(currentIndexChanged(int)),
	  pInletBoundaryStackedLayout, SLOT(setCurrentIndex(int)));
  connect(m_pInletBoundaryTypeBox, &QComboBox::currentTextChanged, [this](QString strText){
      if(tr("第一类边界条件") == strText){
	m_pService->globalParam()->eInletType = FirstClass;
      }if(tr("第二类边界条件") == strText){
	m_pService->globalParam()->eInletType = SecondClass;
      }else{
	m_pService->globalParam()->eInletType = ThirdClass;
      }
    });
	  

  QGridLayout* pInletBoundaryLayout = new QGridLayout(pInletBoundaryGrp);
  nLineNum = 0;
  pInletBoundaryLayout->addWidget(pInletBoundaryTypeLabel, nLineNum, 0);
  pInletBoundaryLayout->addWidget(m_pInletBoundaryTypeBox, nLineNum, 1);
  nLineNum ++;
  pInletBoundaryLayout->addLayout(pInletBoundaryStackedLayout, nLineNum, 0, 1, 2);
  
  QGroupBox* pOutletBoundaryGrp = new QGroupBox(tr("出口边界"));
  QLabel *pOutletBoundaryTypeLabel = new QLabel(tr("边界类型"));
  m_pOutletBoundaryTypeBox = new QComboBox;
  m_pOutletBoundaryTypeBox->addItem(tr("第一类边界条件"));
  m_pOutletBoundaryTypeBox->addItem(tr("第二类边界条件"));
  m_pOutletBoundaryTypeBox->addItem(tr("第三类边界条件"));

  QFrame *pOutletFirstTypeFrame = new QFrame;
  QLabel *pOutletTempLabel = new QLabel(tr("出口温度"));
  m_pOutletTempEdit = new QLineEdit(QString::number(m_pService->globalParam()->dOutletTemp));
  connect(m_pOutletTempEdit, &QLineEdit::editingFinished, [this](){
      bool b;
      double dCache;
      dCache = m_pOutletTempEdit->text().toDouble(&b);
      if(b){
	m_pService->globalParam()->dOutletTemp = dCache;
      }else{
	m_pOutletTempEdit->setText(QString::number(m_pService->globalParam()->dOutletTemp));
      }
    });
  QGridLayout *pOutletFirstTypeLayout = new QGridLayout(pOutletFirstTypeFrame);
  nLineNum = 0;
  pOutletFirstTypeLayout->addWidget(pOutletTempLabel, nLineNum, 0);
  pOutletFirstTypeLayout->addWidget(m_pOutletTempEdit, nLineNum, 1);
  
  QFrame *pOutletSecondTypeFrame = new QFrame;
  QLabel *pOutletHeatFluxLabel = new QLabel(tr("出口热流"));
  m_pOutletHeatFluxEdit = new QLineEdit(QString::number(m_pService->globalParam()->dOutletHeatFlux));
  connect(m_pOutletHeatFluxEdit, &QLineEdit::editingFinished, [this](){
      bool b;
      double dCache;
      dCache = m_pOutletHeatFluxEdit->text().toDouble(&b);
      if(b){
	m_pService->globalParam()->dOutletHeatFlux = dCache;
      }else{
	m_pOutletHeatFluxEdit->setText(QString::number(m_pService->globalParam()->dOutletHeatFlux));
      }
    });
  QGridLayout *pOutletSecondTypeLayout = new QGridLayout(pOutletSecondTypeFrame);
  nLineNum = 0;
  pOutletSecondTypeLayout->addWidget(pOutletHeatFluxLabel, nLineNum, 0);
  pOutletSecondTypeLayout->addWidget(m_pOutletHeatFluxEdit, nLineNum, 1);
  
  QFrame *pOutletThirdTypeFrame = new QFrame;
  QLabel *pOutletInfinityTempLabel = new QLabel(tr("环境温度(k)"));
  m_pOutletInfinityTempEdit = new QLineEdit(QString::number(m_pService->globalParam()->dOutletInfinityTemp));
  connect(m_pOutletInfinityTempEdit, &QLineEdit::editingFinished, [this](){
      bool b;
      double dCache;
      dCache = m_pOutletInfinityTempEdit->text().toDouble(&b);
      if(b){
	m_pService->globalParam()->dOutletInfinityTemp = dCache;
      }else{
	m_pInletInfinityTempEdit->setText(QString::number(m_pService->globalParam()->dInletInfinityTemp));
      }
    });
    
  QLabel *pOutletConvectiveCoeffLabel = new QLabel(tr("对流系数"));
  m_pOutletConvectiveCoeffEdit = new QLineEdit(QString::number(m_pService->globalParam()->dOutletConvectiveCoeff));
  connect(m_pOutletConvectiveCoeffEdit, &QLineEdit::editingFinished, [this](){
      bool b;
      double dCache;
      dCache = m_pOutletConvectiveCoeffEdit->text().toDouble(&b);
      if(b){
	m_pService->globalParam()->dOutletConvectiveCoeff = dCache;
      }else{
	m_pOutletConvectiveCoeffEdit->setText(QString::number(m_pService->globalParam()->dOutletConvectiveCoeff));
      }
    });

  QGridLayout* pOutletThirdTypeLayout = new QGridLayout(pOutletThirdTypeFrame);
  nLineNum = 0; 
  pOutletThirdTypeLayout->addWidget(pOutletInfinityTempLabel, nLineNum, 0);
  pOutletThirdTypeLayout->addWidget(m_pOutletInfinityTempEdit, nLineNum, 1);
  nLineNum ++;
  pOutletThirdTypeLayout->addWidget(pOutletConvectiveCoeffLabel, nLineNum, 0);
  pOutletThirdTypeLayout->addWidget(m_pOutletConvectiveCoeffEdit, nLineNum, 1);

  QStackedLayout* pOutletBoundaryStackedLayout = new QStackedLayout;
  pOutletBoundaryStackedLayout->addWidget(pOutletFirstTypeFrame);
  pOutletBoundaryStackedLayout->addWidget(pOutletSecondTypeFrame);
  pOutletBoundaryStackedLayout->addWidget(pOutletThirdTypeFrame);

  connect(m_pOutletBoundaryTypeBox, SIGNAL(activated(int)),
	  pOutletBoundaryStackedLayout, SLOT(setCurrentIndex(int)));

  connect(m_pOutletBoundaryTypeBox, &QComboBox::currentTextChanged, [this](QString strText){
      if(tr("第一类边界条件") == strText){
	m_pService->globalParam()->eOutletType = FirstClass;
      }if(tr("第二类边界条件") == strText){
	m_pService->globalParam()->eOutletType = SecondClass;
      }else{
	m_pService->globalParam()->eOutletType = ThirdClass;
      }
    });

  QGridLayout* pOutletBoundaryLayout = new QGridLayout(pOutletBoundaryGrp);
  nLineNum = 0;
  pOutletBoundaryLayout->addWidget(pOutletBoundaryTypeLabel, nLineNum, 0);
  pOutletBoundaryLayout->addWidget(m_pOutletBoundaryTypeBox, nLineNum, 1);
  nLineNum ++;
  pOutletBoundaryLayout->addLayout(pOutletBoundaryStackedLayout, nLineNum, 0, 1, 2);

  QGridLayout *pBoundarySettingLayout = new QGridLayout(pBoundarySettingGrp);
  nLineNum = 0;
  pBoundarySettingLayout->addWidget(pInletBoundaryGrp, nLineNum, 0);
  nLineNum ++;
  pBoundarySettingLayout->addWidget(pOutletBoundaryGrp, nLineNum, 0);

  QGridLayout *pMainLayout = new QGridLayout(this);
  nLineNum = 0;
  pMainLayout->addWidget(pGlobalParamGrp, nLineNum, 0);
  nLineNum ++;
  pMainLayout->addWidget(pLocalParamGrp, nLineNum, 0);
  nLineNum ++;
  pMainLayout->addWidget(pBoundarySettingGrp, nLineNum, 0);
}

void LeftWidget::refreshTable()
{
  LocalParam* pTmp = m_pService->localParam();
  m_pTableWidget->setRowCount(pTmp->size());
  m_pTableWidget->setColumnCount(5);
  for(unsigned int i=0; i<pTmp->size(); i++)
    {
      m_pTableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(pTmp->at(i).dLength)));
      m_pTableWidget->setItem(i, 1, new QTableWidgetItem(QString::number(pTmp->at(i).nSubMeshNum)));
      m_pTableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(pTmp->at(i).dHeatCap)));
      m_pTableWidget->setItem(i, 3, new QTableWidgetItem(QString::number(pTmp->at(i).dDensity)));
      m_pTableWidget->setItem(i, 4, new QTableWidgetItem(QString::number(pTmp->at(i).dThermalConductivity)));
    }
}
