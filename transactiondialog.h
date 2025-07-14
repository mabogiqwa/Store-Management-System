#ifndef TRANSACTIONDIALOG_H
#define TRANSACTIONDIALOG_H

#include <QDialog>
#include <QList>
#include "item.h"
#include "itemmanager.h"
#include "customer.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QGroupBox>
#include <QSpinBox>
#include <QMessageBox>
#include <QPushButton>
#include <QListWidget>

class QComboBox;
class Customer;
class Item;
#include "customermanager.h"

struct SelectedItem {
    Item *item;
    int quantity;

    SelectedItem(Item *i, int q) : item(i), quantity(q) {}
};

class TransactionDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TransactionDialog(QWidget *parent = nullptr);
    ~TransactionDialog();

    Customer* getSelectedCustomer() const;
    QList<SelectedItem> getSelectedItems() const;
private slots:
    void onAddItemClicked();
    void onRemovedItemClicked();
    void onCustomerChanged();
    void onItemSelectionChanged();
    void accept() override;
private:
    QComboBox *mCustomerCombo;
    QComboBox *mItemCombo;
    QSpinBox *mQuantitySpinBox;
    QListWidget *mSelectedItemsList;
    QPushButton *mAddItemButton;
    QPushButton *mRemoveItemButton;
    QPushButton *mOkButton;
    QPushButton *mCancelButton;
    QList<SelectedItem> mSelectedItems;

    void setupUI();
    void populateCustomers();
    void populatedItems();
    void updateSelectedItemsList();
    void updateButtons();
};

#endif // TRANSACTIONDIALOG_H
