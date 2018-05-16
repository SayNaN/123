#ifndef TABLEDELEGATE_H
#define TABLEDELEGATE_H

#include <QtWidgets>

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
