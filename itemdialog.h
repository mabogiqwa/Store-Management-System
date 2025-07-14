#ifndef ITEMDIALOG_H
#define ITEMDIALOG_H

#include <QDialog>
#include "itemmanager.h"
#include <QVBoxLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>

class ItemDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ItemDialog(QWidget *parent = nullptr);
    QString getItemName() const;
    Itemtype getItemType() const;
    ~ItemDialog();
private slots:
    void onTextChanged();
    void accept();
private:
    QLineEdit *mNameEdit;
    QComboBox *mTypeCombo;
    QPushButton *mOkButton;
    QPushButton *mCancelButton;
    void setupUI();
};

#endif // ITEMDIALOG_H
