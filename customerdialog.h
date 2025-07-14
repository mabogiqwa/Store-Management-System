#ifndef CUSTOMERDIALOG_H
#define CUSTOMERDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QLabel>
#include <QMessageBox>
#include "customermanager.h"
#include "itemmanager.h"

class CustomerDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CustomerDialog(QWidget *parent = nullptr);
    ~CustomerDialog();

    QString getCustomerName() const;
private slots:
    void onTextChanged();
    void accept() override;
private:
    QLineEdit *mNameEdit;
    QPushButton *mOkButton;
    QPushButton *mCancelButton;

    void setupUI();
};

#endif // CUSTOMERDIALOG_H
