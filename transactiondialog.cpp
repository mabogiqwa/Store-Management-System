#include "transactiondialog.h"

TransactionDialog::TransactionDialog(QWidget *parent)
{
    setupUI();
    setWindowTitle("Create Transaction");
    setModal(true);
    resize(500,400);
}

TransactionDialog::~TransactionDialog()
{

}

Customer *TransactionDialog::getSelectedCustomer() const
{

}

QList<SelectedItem> TransactionDialog::getSelectedItems() const
{

}

void TransactionDialog::onAddItemClicked()
{

}

void TransactionDialog::onRemovedItemClicked()
{

}

void TransactionDialog::onCustomerChanged()
{

}

void TransactionDialog::onItemSelectionChanged()
{

}

void TransactionDialog::accept()
{

}

void TransactionDialog::setupUI()
{

}

void TransactionDialog::populateCustomers()
{

}

void TransactionDialog::populatedItems()
{

}

void TransactionDialog::updateSelectedItemsList()
{

}

void TransactionDialog::updateButtons()
{

}
