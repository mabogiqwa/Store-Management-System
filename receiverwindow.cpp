#include "receiverwindow.h"

ReceiverWindow::ReceiverWindow(QWidget *parent)
    : QMainWindow(parent)
    , mDataTextEdit(nullptr)
    , mReceiver(nullptr)
{
    setupUI();
    setupMenus();
    setupStatusBar();
    setupConnections();

    setWindowTitle("UDP Receiver");
    resize(600, 400);

    //logMessage("UDP Receiver started");
    updateActions();
}

ReceiverWindow::~ReceiverWindow()
{
    if (mReceiver) {
        mReceiver->stopListening();
        delete mReceiver;
    }
}

void ReceiverWindow::setupUI()
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    QSplitter *splitter = new QSplitter(Qt::Horizontal, this);

    QGroupBox *rawDataGroup = new QGroupBox("Raw XML Data", this);
    QVBoxLayout *rawLayout = new QVBoxLayout(rawDataGroup);

    mRawDataTextEdit = new QTextEdit(this);
    mRawDataTextEdit->setReadOnly(true);
    mRawDataTextEdit->setPlaceholderText("Raw XML data will appear here...");
    mRawDataTextEdit->setFont(QFont("Courier", 10));
    rawLayout->addWidget(mRawDataTextEdit);

    QGroupBox *formattedDataGroup = new QGroupBox("Formatted Transaction Data", this);
    QVBoxLayout *formattedLayout = new QVBoxLayout(formattedDataGroup);

    mFormattedDataTextEdit = new QTextEdit(this);
    mFormattedDataTextEdit->setReadOnly(true);
    mFormattedDataTextEdit->hide();

    splitter->addWidget(rawDataGroup);
    splitter->addWidget(formattedDataGroup);
    splitter->setSizes({400, 500});

    mStatsLabel = new QLabel("Messages received: 0", this);
    mStatsLabel->setStyleSheet("QLabel { color : blue; font-weight: bold; }");

    mainLayout->addWidget(mStatsLabel);
    mainLayout->addWidget(splitter);
}

void ReceiverWindow::setupMenus()
{
    // File Menu
    mFileMenu = menuBar()->addMenu("&File");

    mExitAction = new QAction("E&xit", this);
    mExitAction->setShortcut(QKeySequence::Quit);
    mExitAction->setStatusTip("Exit the application");
    mFileMenu->addAction(mExitAction);

    // Network Menu
    mNetworkMenu = menuBar()->addMenu("&Network");

    mStartListeningAction = new QAction("&Start Listening", this);
    mStartListeningAction->setStatusTip("Start listening for UDP broadcasts");
    mNetworkMenu->addAction(mStartListeningAction);

    mStopListeningAction = new QAction("&Stop Listening", this);
    mStopListeningAction->setStatusTip("Stop listening for UDP broadcasts");
    mStopListeningAction->setEnabled(false);
    mNetworkMenu->addAction(mStopListeningAction);

    mNetworkMenu->addSeparator();

    mClearDataAction = new QAction("&Clear Data", this);
    mClearDataAction->setStatusTip("Clear received data");
    mNetworkMenu->addAction(mClearDataAction);

    // Help Menu
    mHelpMenu = menuBar()->addMenu("&Help");

    mAboutAction = new QAction("&About", this);
    mAboutAction->setStatusTip("Show information about the application");
    mHelpMenu->addAction(mAboutAction);
}

void ReceiverWindow::setupStatusBar()
{
    mStatusBar = statusBar();
    mStatusBar->showMessage("Ready");
}

void ReceiverWindow::setupConnections()
{
    connect(mStartListeningAction, &QAction::triggered, this, &ReceiverWindow::onStartListening);
    connect(mStopListeningAction, &QAction::triggered, this, &ReceiverWindow::onStopListening);
    connect(mClearDataAction, &QAction::triggered, this, &ReceiverWindow::onClearData);
    connect(mExitAction, &QAction::triggered, this, &ReceiverWindow::onExit);
    connect(mAboutAction, &QAction::triggered, this, &ReceiverWindow::onAbout);
}

void ReceiverWindow::onStartListening()
{
    if (!mReceiver) {
        mReceiver = new UdpReceiver(this);
        connect(mReceiver, &UdpReceiver::dataReceived,
                this, &ReceiverWindow::onDataReceived);
    }

    mReceiver->startListening();
    mStartListeningAction->setEnabled(false);
    mStopListeningAction->setEnabled(true);

    //logMessage("Started listening for UDP broadcasts on port 12345");
    mStatusBar->showMessage("Listening for UDP broadcasts");
}

void ReceiverWindow::onStopListening()
{
    if (mReceiver) {
        mReceiver->stopListening();
    }

    mStartListeningAction->setEnabled(true);
    mStopListeningAction->setEnabled(false);

    //logMessage("Stopped listening for UDP broadcasts");
    mStatusBar->showMessage("Stopped listening", 3000);
}

void ReceiverWindow::onClearData()
{
    mDataTextEdit->clear();
    //logMessage("Data cleared");
}

void ReceiverWindow::onAbout()
{
    QMessageBox::about(this, "About UDP Receiver",
                       "UDP Receiver v1.0\n\n"
                       "A Qt application for receiving UDP broadcasts.\n"
                       "Built with Qt6 and C++.\n\n"
                       "COS3711 Assignment 2\n"
                       "© 2025");
}

void ReceiverWindow::onExit()
{
    close();
}

void ReceiverWindow::onDataReceived(const QString &data)
{
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    mDataTextEdit->append(QString("[%1] Received: %2").arg(timestamp, data));
    //logMessage("UDP data received");
}

void ReceiverWindow::updateActions()
{
    // Update action states based on current state
}

QString ReceiverWindow::formatXMLData(const QString &xmlData)
{

}

/*
void ReceiverWindow::logMessage(const QString &message)
{
    //QString timestamp = QDateTime::currentDateTime().toString("hh:mm:ss");
    // You could add a separate log widget or use status bar
    //mStatusBar->showMessage(QString("[%1] %2").arg(timestamp, message), 5000);
}
*/
