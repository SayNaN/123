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
  QLineEdit* timeStepEdit;
  QLineEdit* timeSchemeEdit;
  QComboBox* calcSchemeBox;
  QTableWidget* tableWidget;
  QMenu* rightMenu;

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

class CombWidget : public myScrollArea
{
  Q_OBJECT
 public:
  CombWidget(QWidget *parent,Data_Container *DB);
  ~CombWidget(){};
 private:
  Data_Container *data;
  QLineEdit *N1;
  QLineEdit *M1;
  QLineEdit *SM1;
  QLineEdit *SM2;
  QLineEdit *KMARKD;
  QLineEdit *KMARKU;
  QLineEdit *SND;
  QLineEdit *SNU;
};

#endif
