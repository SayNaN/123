#ifndef LEFTWIDGET_H
#define LEFTWIDGET_H
#include<QtWidgets>

class ZTService;

class LeftWidget:public QFrame
{
  Q_OBJECT
 public:
  LeftWidget(ZTService *pService, QWidget *parent = NULL);
  ~LeftWidget(){};

 private:
  void initializeUI();
  void refreshTable();

 private:
  QLineEdit* m_pTimeStepEdit;
  QLineEdit* m_pStepNumEdit;
  QLineEdit* m_pTimeSchemeEdit;
  QLineEdit* m_pInitTempEdit;
  
  QComboBox* m_pInletBoundaryTypeBox;
  QLineEdit* m_pInletTempEdit;
  QLineEdit* m_pInletHeatFluxEdit;
  QLineEdit* m_pInletInfinityTempEdit;
  QLineEdit* m_pInletConvectiveCoeffEdit;
  
  QComboBox* m_pOutletBoundaryTypeBox;
  QLineEdit* m_pOutletTempEdit;
  QLineEdit* m_pOutletHeatFluxEdit;
  QLineEdit* m_pOutletInfinityTempEdit;
  QLineEdit* m_pOutletConvectiveCoeffEdit;
  
  QComboBox* m_pCalcSchemeBox;
  QTableWidget* m_pTableWidget;
  QMenu* m_pRightMenu;
  ZTService* m_pService;

 signals:
  void clearshow();
  void treeSelectIndex(int);

  /*
 public slots:
  void processRes();
  void INTYPE_fun(int);
  void IEXTIO_fun(int);
  void ILIN_fun(int);
  void ILOUT_fun(int);
  void IEXTUP_fun(int);
  void IEXTDN_fun(int);
  */
};

#endif
