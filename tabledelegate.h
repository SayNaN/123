#ifndef TABLEDELEGATE_H
#define TABLEDELEGATE_H

#include <QtWidgets>

class EditorWithButton: public QWidget
{
  Q_OBJECT
 public:
  EditorWithButton(QWidget *parent = NULL):QWidget(parent)
    {
      m_pEdit = new QLineEdit();
      QPushButton* pBrowse = new QPushButton(tr("..."));
      pBrowse->setFixedWidth(30);
      QHBoxLayout *layout = new QHBoxLayout(this);
      layout->setContentsMargins(0, 0, 0, 0);
      layout->setSpacing(0);
      layout->addWidget(m_pEdit);
      layout->addWidget(pBrowse);
      connect(pBrowse, &QPushButton::clicked, this, &EditorWithButton::setEditorData);
    }
  QLineEdit* getEditor()
  {
    return m_pEdit;
  }

 private slots:
  void setEditorData()
  {
    QString sFilePath;
    sFilePath=QFileDialog::getOpenFileName(Q_NULLPTR,tr("打开"),QString(),
					   tr("输入文件(*.*)"));
    if(!sFilePath.isEmpty())
      {
	m_pEdit->setText(sFilePath);
      }
  }

 private:
  QLineEdit* m_pEdit;
};

class LeftDelegate: public QItemDelegate
{
  Q_OBJECT
public:
  LeftDelegate(QWidget *parent = NULL);
  ~LeftDelegate(){};

  QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
  void setEditorData(QWidget *editor, const QModelIndex &index) const;  
  void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
};

#endif //TABLEDELEGATE_H
