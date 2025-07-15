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

MainWindow::~MainWindow() {}

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
