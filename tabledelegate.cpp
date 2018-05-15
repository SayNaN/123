#include "tabledelegate.h"
#include<QItemDelegate>

LeftDelegate::LeftDelegate(QWidget* parent)
  :QItemDelegate(parent)
{}

QWidget* LeftDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
  if(index.column() == 4)
    {
      QWidget* pTmp = new QWidget();
      QLineEdit* edit = new QLineEdit(k);
      edit->setObjectName("lineeditor");
      QPushButton* browse = new QPushButton(tr("..."));
      browse->setFixedWidth(30);
      QHBoxLayout *layout = new QHBoxLayout(pTmp);
      layout->setContentsMargins(0, 0, 0, 0);
      layout->setSpacing(0);
      layout->addWidget(edit);
      layout->addWidget(browse);

      connect(browse, &QPushButton::clicked, [&](){
	  QString sFilePath;
	  sFilePath=QFileDialog::getOpenFileName(this,tr("打开"),QString(),
						 tr("输入文件(*.*)"));
	  if(!sFilePath.isEmpty())
	    {
	      m_pService->operate()->setProjectName(sFilePath);
	      m_pService->operate()->readProjectFile();
	      m_pText3D->cleardisplay();
	      m_pLeftWidget->resetGUI();
	      setWindowTitle(m_pService->operate()->getProjectName());
	    }
	});

      return pTmp;
    }
  return QItemDelegate::createEditor(parent, option, index);
}

void LeftDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
  if(index.column() == 4)
    {
      QString value = index.model()->data(index, Qt::DisplayRole).toString();
      editor->findChild<QLineEdit*>("lineeditor")->setText(value);
    }
  else
    {
      QItemDelegate::setEditorData(editor, index);
    }
}

void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
  if(index.column() ==4)
    {
      QString value = editor->findChild<QLineEdit*>("lineeditor")->text();
      model->setData(index, value);
    }
  else
    {
      QItemDelegate::setModelData(editor, index);
    }
}
