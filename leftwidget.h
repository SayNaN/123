#ifndef LEFTWIDGET_H
#define LEFTWIDGET_H
#include<QtWidgets>

class LeftWidget:public QFrame
{
  Q_OBJECT
 public:
  LeftWidget(QWidget *parent);
  ~LeftWidget(){};

 private:
  void initializeUI();
  void refreshTable();

  QLineEdit* timeStepEdit;
  QLineEdit* timeSchemeEdit;
  QComboBox* calcSchemeBox;
  QTableWidget* tableWidget;
  QMenu* rightMenu;
  ZTService* m_pService;
  

 signals:
  void clearshow();
  void treeSelectIndex(int);

 public slots:
  void processRes();
  void INTYPE_fun(int);
  void IEXTIO_fun(int);
  void ILIN_fun(int);
  void ILOUT_fun(int);
  void IEXTUP_fun(int);
  void IEXTDN_fun(int);
};

#endif
