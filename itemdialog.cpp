#include "itemdialog.h"

ItemDialog::ItemDialog(QWidget *parent) : QDialog(parent)
{
    setupUI();
    setWindowTitle("Shop");
    setModal(true);
    resize(300,140);
}

QString ItemDialog::getItemName() const
{
    return mNameEdit->text().trimmed();
}

Itemtype ItemDialog::getItemType() const
{
    return static_cast<Itemtype>(mTypeCombo->currentIndex());
}

ItemDialog::~ItemDialog()
{

}

void ItemDialog::onTextChanged()
{
    mOkButton->setEnabled(!mNameEdit->text().trimmed().isEmpty());
}

void ItemDialog::accept()
{
    QString name = getItemName();
    if (name.isEmpty()) {
        QMessageBox::warning(this, "Invalid Input", "Please enter an item name.");
        return;
    }

    ItemManager *manager = ItemManager::getInstance();
    if (manager->findItem(name)) {
        QMessageBox::warning(this, "Duplicate Item", "An item with this name already exists.");
        return;
    }

    QDialog::accept();
}

void ItemDialog::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QLabel *nameLabel = new QLabel("Item Name:", this);
    mainLayout->addWidget(nameLabel);

    mNameEdit = new QLineEdit(this);
    mNameEdit->setPlaceholderText("Enter item name...");
    connect(mNameEdit, &QLineEdit::textChanged, this, &ItemDialog::onTextChanged);
    mainLayout->addWidget(mNameEdit);

    QLabel *typeLabel = new QLabel("Item Type:", this);
    mainLayout->addWidget(typeLabel);

    mTypeCombo = new QComboBox(this);
    mTypeCombo->addItem("Book");
    mTypeCombo->addItem("Magazine");
    mainLayout->addWidget(mTypeCombo);

    QHBoxLayout *buttonLayout = new QHBoxLayout(this);
    mOkButton = new QPushButton("OK", this);
    mCancelButton = new QPushButton("Cancel", this);

    mOkButton->setEnabled(false);

    connect(mOkButton, &QPushButton::clicked, this, &ItemDialog::accept);
    connect(mCancelButton, &QPushButton::clicked, this, &QDialog::reject);

    buttonLayout->addWidget(mOkButton);
    buttonLayout->addWidget(mCancelButton);

    mainLayout->addLayout(buttonLayout);

    mNameEdit->setFocus();
}

