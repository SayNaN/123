#include "tabledelegate.h"

LeftDelegate::LeftDelegate(QWidget* parent)
  :QItemDelegate(parent)
{}

QWidget* LeftDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
  if(index.column() == 4)
    {
      EditorWithButton* pTmp = new EditorWithButton(parent);
      return pTmp;
    }
  return QItemDelegate::createEditor(parent, option, index);
}

void LeftDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
  if(index.column() == 4)
    {
      static_cast<EditorWithButton*>(editor)->getEditor()->setText(index.model()->data(index, Qt::EditRole).toString());
    }
  else
    {
      QItemDelegate::setEditorData(editor, index);
    }
}

void LeftDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
  if(index.column() ==4)
    {
      QString value =  static_cast<EditorWithButton*>(editor)->getEditor()->text();
      qDebug()<<value;
      model->setData(index, value, Qt::EditRole);
      qDebug()<<index.model()->data(index, Qt::EditRole).toString();
    }
  else
    {
      QItemDelegate::setModelData(editor, model, index);
    }
}
