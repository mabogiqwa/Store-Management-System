#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), mTransactionView(nullptr), mLogTextEdit(nullptr), mSplitter(nullptr), mTransactionModel(nullptr), mBroadcaster(nullptr)
{
    setupUI();
    setupMenus();
    setupToolBar();
    setupStatusBar();
    setupConnections();

    setWindowTitle("Store Management System");
    resize(800,600);

    logMessage("App started");
    updateActions();
}

MainWindow::~MainWindow()
{
    if (mBroadcaster) {
        mBroadcaster->stopBroadcasting();
        delete mBroadcaster;
    }
}

void MainWindow::onAddCustomer()
{
    CustomerDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        QString name = dialog.getCustomerName();
        CustomerManager::getInstance()->addCustomer(name);
        logMessage(QString("Customer added: %1").arg(name));
        mStatusBar->showMessage(QString("Customer '%1' added").arg(name), 3000);
    }
}

void MainWindow::onAddItem()
{
    ItemDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        QString name = dialog.getItemName();
        Itemtype type = dialog.getItemType();
        ItemManager::getInstance()->addItem(name, type);
        logMessage(QString("Item added: %1 (%2)").arg(name, type == Itemtype::Book ? "Book" : "Magazine"));
        mStatusBar->showMessage(QString("Item '%1' added").arg(name), 3000);
    }
}

void MainWindow::onCreateTransaction()
{

}

void MainWindow::onRestoreItems()
{

}

void MainWindow::onStartBroadcast()
{

}

void MainWindow::onStopBroadcast()
{

}

void MainWindow::onAbout()
{

}

void MainWindow::onHelp()
{

}

void MainWindow::onExit()
{

}

void MainWindow::onTransactionAdded()
{

}

void MainWindow::onBroadcastSent(const QString &data)
{

}

void MainWindow::setupUI()
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    mSplitter = new QSplitter(Qt::Vertical, this);

    //Transaction view
    mTransactionView = new QTreeView(this);
    mTransactionModel = new TransactionModel(this);
    mTransactionView->setModel(mTransactionModel);
    mTransactionView->setRootIsDecorated(true);
    mTransactionView->setAlternatingRowColors(true);
    mTransactionView->header()->setStretchLastSection(true);
    mTransactionView->expandAll();

    mSplitter->addWidget(mTransactionView);

    mLogTextEdit = new QTextEdit(this);
    mLogTextEdit->setReadOnly(true);
    mLogTextEdit->setMaximumHeight(150);
    mLogTextEdit->setPlaceholderText("Application log messages appear here");

    mSplitter->setSizes({400,150});

    mainLayout->addWidget(mSplitter);
}

void MainWindow::setupMenus()
{
    mFileMenu = menuBar()->addMenu("&File");

    mExitAction = new QAction("&Exit", this);
    mExitAction->setShortcut(QKeySequence::Quit);
    mExitAction->setStatusTip("Exit the application");
    mFileMenu->addAction(mExitAction);

    mDataMenu = menuBar()->addMenu("&Data");

    mAddCustomerAction = new QAction("&Add Customer", this);
    mAddCustomerAction->setShortcut(QKeySequence("Ctrl+U"));
    mAddCustomerAction->setStatusTip("Add a new customer.");
    mDataMenu->addAction(mAddItemAction);

    mDataMenu->addSeparator();

    mCreateTransactionAction = new QAction("Create &Transaction", this);
    mCreateTransactionAction->setShortcut(QKeySequence("Ctrl+T"));
    mCreateTransactionAction->setStatusTip("Create a new transaction");
    mDataMenu->addAction(mCreateTransactionAction);

    mDataMenu->addSeparator();

    mRestoreItemsAction = new QAction("&Restore Items", this);
    mRestoreItemsAction->setStatusTip("Restore items from backup");
    mDataMenu->addAction(mRestoreItemsAction);

    //Network Menu
    mNetworkMenu = menuBar()->addMenu("&Network");

    mStartBroadcastAction = new QAction("&Start Broadcasting", this);
    mStartBroadcastAction->setStatusTip("Start broadcasting transaction data");
    mNetworkMenu->addAction(mStartBroadcastAction);

    mStopBroadcastAction = new QAction("&Stop Broadcasting", this);
    mStopBroadcastAction->setStatusTip("Stop broadcasting transaction data");
    mStopBroadcastAction->setEnabled(false);
    mNetworkMenu->addAction(mStopBroadcastAction);

    //Add help menu later
}

void MainWindow::setupToolBar()
{
    mToolBar = addToolBar("Main Toolbar");

    mToolBar->addAction(mAddCustomerAction);
    mToolBar->addAction(mAddItemAction);
    mToolBar->addSeparator();
    mToolBar->addAction(mCreateTransactionAction);
    mToolBar->addSeparator();
    mToolBar->addAction(mStartBroadcastAction);
    mToolBar->addAction(mStopBroadcastAction);
}

void MainWindow::setupStatusBar()
{
    mStatusBar = statusBar();
    mStatusBar->showMessage("ready");
}

void MainWindow::setupConnections()
{
    //menu actions
    connect(mAddCustomerAction, &QAction::triggered, this, &MainWindow::onAddCustomer);
    connect(mAddItemAction, &QAction::triggered, this, &MainWindow::onAddItem);
    connect(mCreateTransactionAction, &QAction::triggered, this, &MainWindow::onCreateTransaction);
    connect(mRestoreItemsAction, &QAction::triggered, this, &MainWindow::onRestoreItems);
    connect(mStartBroadcastAction, &QAction::triggered, this, &MainWindow::onStartBroadcast);
    connect(mStopBroadcastAction, &QAction::triggered, this, &MainWindow::onStopBroadcast);
    connect(mExitAction, &QAction::triggered, this, &MainWindow::onExit);
    connect(mAboutAction, &QAction::triggered, this, &MainWindow::onAbout);
    connect(mHelpAction, &QAction::triggered, this, &MainWindow::onHelp);

    //Manager connections
    TransactionManager *transactionManager = TransactionManager::getInstance();
    connect(transactionManager, &TransactionManager::transactionAdded, this, &MainWindow::onTransactionAdded);

    CustomerManager *customerManager = CustomerManager::getInstance();
    connect(customerManager, &CustomerManager::customerAdded, this, &MainWindow::updateActions);

    ItemManager *itemManager = ItemManager::getInstance();
    connect(itemManager, &ItemManager::itemAdded, this, &MainWindow::updateActions);
    connect(itemManager, &ItemManager::itemsRestored, this, &MainWindow::updateActions);
}

void MainWindow::updateActions()
{

}

void MainWindow::logMessage(const QString &message)
{

}
