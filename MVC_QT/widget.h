#ifndef WIDGET_H
#define WIDGET_H
 
#include <QWidget>
#include <QtSql>
#include <QtGui>
 
namespace Ui {
   class Widget;
}
 
class Widget : public QWidget
{
   Q_OBJECT
 
   public:
      explicit Widget(QWidget *parent = 0);
      ~Widget();
      void populateDataItem();
 
   public slots:
      void addnew();
      void remove();
      void save();
 
   private:
      Ui::Widget *ui;
      QSqlTableModel *model;
      QSqlDatabase db;
 
      bool initDatabase();
      void closeDatabase();
};
#endif   // WIDGET_H
