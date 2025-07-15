#include "transactiondialog.h"

TransactionDialog::TransactionDialog(QWidget *parent)
{
    setupUI();
    setWindowTitle("Create Transaction");
    setModal(true);
    resize(500,400);
}

TransactionDialog::~TransactionDialog()
{}

Customer *TransactionDialog::getSelectedCustomer() const
{
    int index = mCustomerCombo->currentIndex();
    if (index >= 0) {
        return static_cast<Customer*>(mCustomerCombo->itemData(index).value<void*>());
    }
    return nullptr;
}

QList<SelectedItem> TransactionDialog::getSelectedItems() const
{
    return mSelectedItems;
}

void TransactionDialog::onAddItemClicked()
{
    int index = mItemCombo->currentIndex();
    if (index >= 0) {
        Item *item = static_cast<Item*>(mItemCombo->itemData(index).value<void*>());
        int quantity = mQuantitySpinBox->value();

        for (int i = 0; i < mSelectedItems.size(); i++) {
            if (mSelectedItems[i].item == item) {
                mSelectedItems[i].quantity += quantity;
                updateSelectedItemsList();
                return;
            }
        }

        mSelectedItems.append(SelectedItem(item, quantity));
        updateSelectedItemsList();

        mQuantitySpinBox->setValue(1);
    }
}

void TransactionDialog::onRemovedItemClicked()
{
    int row = mSelectedItemsList->currentRow();
    if (row >= 0 && row < mSelectedItems.size()) {
        mSelectedItems.removeAt(row);
        updateSelectedItemsList();
    }
}

void TransactionDialog::onCustomerChanged()
{
    updateButtons();
}

void TransactionDialog::onItemSelectionChanged()
{
    updateButtons();
}

void TransactionDialog::accept()
{
    if (!getSelectedCustomer()) {
        QMessageBox::warning(this, "No customer", "Please select a customer.");
        return;
    }

    if (mSelectedItems.isEmpty()) {
        QMessageBox::warning(this, "No Items", "Please add at least one item to the transaction.");
        return;
    }

    QDialog::accept();
}

void TransactionDialog::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    //Customer selection
    QGroupBox *customerGroup = new QGroupBox("Customer", this);
    QVBoxLayout *customerLayout = new QVBoxLayout(customerGroup);

    mCustomerCombo = new QComboBox(this);
    connect(mCustomerCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &TransactionDialog::onCustomerChanged);
    customerLayout->addWidget(mCustomerCombo);

    mainLayout->addWidget(customerGroup);

    //Item selection
    QGroupBox *itemGroup = new QGroupBox("Add items", this);
    QGridLayout *itemLayout = new QGridLayout(itemGroup);

    itemLayout->addWidget(new QLabel("Item:", this),0,0);
    mItemCombo = new QComboBox(this);
    connect(mItemCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &TransactionDialog::onItemSelectionChanged);
    itemLayout->addWidget(mItemCombo,0,1);

    itemLayout->addWidget(new QLabel("Quantity:",this), 1, 0);
    mQuantitySpinBox = new QSpinBox(this);
    mQuantitySpinBox->setMinimum(1);
    mQuantitySpinBox->setMaximum(999);
    mQuantitySpinBox->setValue(1);
    itemLayout->addWidget(mQuantitySpinBox, 1, 1);

    mAddItemButton = new QPushButton("Add Item", this);
    connect(mAddItemButton, &QPushButton::clicked, this, &TransactionDialog::onAddItemClicked);
    itemLayout->addWidget(mQuantitySpinBox,1,1);

    mAddItemButton = new QPushButton("Add Item", this);
    connect(mAddItemButton, &QPushButton::clicked, this, &TransactionDialog::onAddItemClicked);
    itemLayout->addWidget(mAddItemButton,2,0,1,2);

    mainLayout->addWidget(itemGroup);

    QGroupBox *selectedGroup = new QGroupBox("Selected Items", this);
    QVBoxLayout *selectedLayout = new QVBoxLayout(selectedGroup);

    mSelectedItemsList = new QListWidget(this);
    selectedLayout->addWidget(mSelectedItemsList);

    mRemoveItemButton = new QPushButton("Remove Selected", this);
    connect(mRemoveItemButton, &QPushButton::clicked, this, &TransactionDialog::onRemovedItemClicked);
    selectedLayout->addWidget(mRemoveItemButton);

    mainLayout->addWidget(selectedGroup);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    mOkButton = new QPushButton("Create Transaction", this);
    mCancelButton = new QPushButton("Cancel", this);

    connect(mOkButton, &QPushButton::clicked, this, &TransactionDialog::accept);
    connect(mCancelButton, &QPushButton::clicked, this, &QDialog::reject);

    buttonLayout->addWidget(mOkButton);
    buttonLayout->addWidget(mCancelButton);

    mainLayout->addLayout(buttonLayout);

    populateCustomers();
    populatedItems();
    updateButtons();
}

void TransactionDialog::populateCustomers()
{
    mCustomerCombo->clear();

    CustomerManager *manager = CustomerManager::getInstance();
    QList<Customer*> customers = manager->getCustomers();

    for (Customer *customer : customers) {
        mCustomerCombo->addItem(customer->getName(), QVariant::fromValue(static_cast<void*>(customer)));
    }

    updateButtons();
}

void TransactionDialog::populatedItems()
{
    mItemCombo->clear();

    ItemManager *manager = ItemManager::getInstance();
    QList<Item*> items = manager->getItems();

    for (Item *item : items) {
        QString displayText = QString("%1 (%2)").arg(item->getName(), item->getTypeString());
        mItemCombo->addItem(displayText, QVariant::fromValue(static_cast<void*>(item)));
    }

    updateButtons();
}

void TransactionDialog::updateSelectedItemsList()
{
    mSelectedItemsList->clear();

    for (const SelectedItem &selectedItem : mSelectedItems) {
        QString text = QString("%1 (%2) - Quantity: %3").arg(selectedItem.item->getName()).arg(selectedItem.item->getTypeString()).arg(selectedItem.quantity);
        mSelectedItemsList->addItem(text);
    }

    updateButtons();
}

void TransactionDialog::updateButtons()
{
    mAddItemButton->setEnabled(mItemCombo->count() > 0);
    mRemoveItemButton->setEnabled(mSelectedItemsList->currentRow() >= 0);
    mOkButton->setEnabled(mCustomerCombo->count() > 0 && !mSelectedItems.isEmpty());
}
