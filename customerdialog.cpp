#include "customerdialog.h"

CustomerDialog::CustomerDialog(QWidget *parent) : QDialog(parent)
{
    setupUI();
    setWindowTitle("Add Customer");
    setModal(true);
    resize(300,120);
}

CustomerDialog::~CustomerDialog() {}

QString CustomerDialog::getCustomerName() const
{
    return mNameEdit->text().trimmed();
}

void CustomerDialog::onTextChanged()
{
    mOkButton->setEnabled(!mNameEdit->text().trimmed().isEmpty());
}

void CustomerDialog::accept()
{
    QString name = getCustomerName();
    if (name.isEmpty()) {
        QMessageBox::warning(this, "Invalid Input", "Please enter an item name");
        return;
    }

    ItemManager *manager = ItemManager::getInstance();
    if (manager->findItem(name)) {
        QMessageBox::warning(this, "Duplicate Item", "An item with this name already exists.");
        return;
    }

    QDialog::accept();
}

void CustomerDialog::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QLabel *label = new QLabel("Customer Name:", this);
    mainLayout->addWidget(label);

    mNameEdit = new QLineEdit(this);
    mNameEdit->setPlaceholderText("Enter customer name: ");
    connect(mNameEdit, &QLineEdit::textChanged, this, &CustomerDialog::onTextChanged);
    mainLayout->addWidget(mNameEdit);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    mOkButton = new QPushButton("OK", this);
    mCancelButton = new QPushButton("Cancel", this);

    mOkButton->setEnabled(false);

    connect(mOkButton, &QPushButton::clicked, this, &CustomerDialog::accept);
    connect(mCancelButton, &QPushButton::clicked, this, &QDialog::reject);

    buttonLayout->addWidget(mOkButton);
    buttonLayout->addWidget(mCancelButton);

    mainLayout->addLayout(buttonLayout);

    mNameEdit->setFocus();
}
