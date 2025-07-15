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

}

void MainWindow::onAddItem()
{

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

}

void MainWindow::setupToolBar()
{

}

void MainWindow::setupStatusBar()
{

}

void MainWindow::setupConnections()
{

}

void MainWindow::updateActions()
{

}

void MainWindow::logMessage(const QString &message)
{

}
