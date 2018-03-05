#include"leftwidget.h"

LeftWidget::LeftWidget(QWidget *parent):QFrame(parent)
{
  initializeUI();
  m_pService = ZTService::getInstance();
}

void LeftWidget::initializeUI()
{
  int linenum=0;

  QGroupBox *globalParamGrp = new QGroupBox(QString::fromLocal8Bit("全局参数"));

  QLabel *timeStepLabel = new QLabel(QString::fromLocal8Bit("时间步长"));
  timeStepEdit = new QLineEdit(QString::number(ZTservice::getInstance->globalParam()->deltaT));
  connect(timeStepEdit, &QLineEdit::editingFinished, [this](){
      bool b;
      double dCache;
      dCache = timeStepEdit->text().toDouble(&b);
      if(b){
	ZTservice::getInstance->globalParam()->deltaT = dCache;
      }else{
	timeStepEdit->setText(QString::number(ZTservice::getInstance->globalParam()->deltaT));
      }
    });

  QLabel *timeSchemeLable = new QLabel(QString::fromLocal8Bit("时间离散格式(0:显式~1:隐式)"));
  timeSchemeEdit = new QLineEdit(QString::number(ZTService::getInstance->globalPrarm()->f));
  connect(timeSchemeEdit, &QLineEdit::editingFinished, [this](){
      bool b;
      double dCache;
      dCache = timeStepEdit->text().toDouble(&b);
      if(b){
	if(dCache>=1.0){
	  timeSchemeEdit->setText(QString::number(1));
	  ZTService::getInstance->globalPrarm()->f = 1.0;
	}else if(dCache<=0){
	  timeSchemeEdit->setText(QString::number(0));
	  ZTService::getInstance->globalPrarm()->f = 0.0;
	}else{
	  ZTService::getInstance->globalPrarm()->f = dCache;
	}
      }else{
	timeSchemeEdit->setText(QString::number(ZTService::getInstance->globalPrarm()->f));
      }
    });

  QLabel *calcSchemeLabel = new QLabel(QString::fromLocal8Bit("计算格式"));
  calcSchemeBox = new QComboBox;
  calcSchemeBox->addItem(QString::fromLocal8Bit("内节点"));
  calcSchemeBox->addItem(QString::fromLocal8Bit("外节点"));
  calcSchemeBox->setCurrentIndex(0);
  connect(calcSchemeBox, &QComboBox::currentIndexChanged, [this](int nIndex){
      if(nIndex==0){
	ZTService::getInstance->globalPrarm()->type = CELLCENTER;
      }else{
	ZTService::getInstance->globalPrarm()->type = MESHNODE;
      }
    });
  QGridLayout* globalParamLayout = new QGridLayout(globalParamGrp);
  linenum = 0;
  globalParamLayout->addWidget(timeStepLabel, linenum, 0);
  globalParamLayout->addWidget(timeStepEdit,  linenum, 1);
  linenum++;
  globalParamLayout->addWidget(timeSchemeLable, linenum, 0);
  globalParamLayout->addWidget(timeSchemeEdit,  linenum, 1);
  linenum++;
  globalParamLayout->addWidget(calcSchemeLabel, linenum, 0);
  globalParamLayout->addWidget(calcSchemeBox,   linenum, 1);

  QGroupBox *localParamGrp = new QGroupBox(QString::fromLocal8Bit("各段参数"));
  
  tableWidget = new QTableWidget(1, 5, localParamGrp);
  QStringList horiHeader;
  horiHeader<<QString::fromLocal8Bit("段长度")
	    <<QString::fromLocal8Bit("网格数")
	    <<QString::fromLocal8Bit("热容")
	    <<QString::fromLocal8Bit("密度")
	    <<QString::fromLocal8Bit("导热系数");
  tableWidget->setHorizontalHeaderLabels(horiHeader);    

  rightMenu=new QMenu(tableWidget);
  tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
  QAction* addSeg    = new QAction(QString::fromLocal8Bit("添加导热段"));
  QAction* removeSeg = new QAction(QString::fromLocal8Bit("删除导热段"));
  rightMenu->addAction(addSeg);
  rightMenu->addAction(removeSeg);
  
  connect(tableWidget, &QWidget::customContextMenuRequested, [this](QPoint &pos){
      if(rowIndex!=-1)
	{ rightMenu->exec(QCursor::pos()); }
    });
  
  connect(addSeg, &QAction::triggered, [this](){
      tableWidget->insertRow(tableWidget->currentIndex());
      m_pService->addSegment(tableWidget->currentIndex());
      refreshTable();
    });
  
  connect(removeSeg, &QAction::triggered, [this](){
      tableWidget->removeRow(tableWidget->currentIndex());
      m_pService->removeSegment(tableWidget->currentIndex());
      refreshTable();
    });
}

void LeftWidget::refreshTable()
{
  LocalParam* pTemp = m_pService->LocalParam();
  for(int i=0; i<pTemp->size(); i++)
    {
      tableWidget->item(i, 0)->setText(QString::number(pTemp->at[i].length));
      tableWidget->item(i, 1)->setText(QString::number(pTemp->at[i].subMeshNum));
      tableWidget->item(i, 2)->setText(QString::number(pTemp->at[i].heatCap));
      tableWidget->item(i, 3)->setText(QString::number(pTemp->at[i].density));
      tableWidget->item(i, 4)->setText(QString::number(pTemp->at[i].thermalConductivity));
    }
}
