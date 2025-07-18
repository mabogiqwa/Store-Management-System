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
    mFormattedDataTextEdit->setPlaceholderText("Formatted transaction data will appear here...");
    formattedLayout->addWidget(mFormattedDataTextEdit);

    mDataTextEdit = new QTextEdit(this);
    mDataTextEdit->setReadOnly(true);
    mDataTextEdit->hide();

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

    mExitAction = new QAction("&Exit", this);
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
    if (mRawDataTextEdit) {
        mRawDataTextEdit->clear();
    }
    if (mFormattedDataTextEdit) {
        mFormattedDataTextEdit->clear();
    }
    mDataTextEdit->clear();
    mMessageCount = 0;
    if (mStatsLabel) {
        mStatsLabel->setText("Message received: 0");
    }
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
    mMessageCount++;
    QString timeStamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

    mDataTextEdit->append(QString("[%1] Received: %2").arg(timeStamp, data));

    if (mRawDataTextEdit) {
        mRawDataTextEdit->append(QString("=== Message %1 [%2] ===").arg(mMessageCount).arg(timeStamp));
        mRawDataTextEdit->append(data);
        mRawDataTextEdit->append("");
    }

    if (mFormattedDataTextEdit) {
        QString formattedData = formatXMLData(data);
        mFormattedDataTextEdit->append(QString("=== Message %1 [%2] ===").arg(mMessageCount).arg(timeStamp));
        mFormattedDataTextEdit->append(formattedData);
        mFormattedDataTextEdit->append("");
    }

    if (mStatsLabel) {
        mStatsLabel->setText(QString("Messages received: %1").arg(mMessageCount));
    }
}

QString ReceiverWindow::formatXMLData(const QString &xmlData)
{
    // Simple XML parsing to create a more readable format
    QString formatted = "";

    // Parse transactions
    QRegularExpression transactionRegex("<transaction>(.*?)</transaction>");
    transactionRegex.setPatternOptions(QRegularExpression::DotMatchesEverythingOption);

    QRegularExpressionMatchIterator transactionIterator = transactionRegex.globalMatch(xmlData);
    int transactionNum = 1;

    while (transactionIterator.hasNext()) {
        QRegularExpressionMatch transactionMatch = transactionIterator.next();
        QString transactionContent = transactionMatch.captured(1);

        formatted += QString("Transaction #%1:\n").arg(transactionNum++);

        // Extract customer
        QRegularExpression customerRegex("<customer>(.*?)</customer>");
        QRegularExpressionMatch customerMatch = customerRegex.match(transactionContent);
        if (customerMatch.hasMatch()) {
            formatted += QString("  Customer: %1\n").arg(customerMatch.captured(1));
        }

        // Extract datetime
        QRegularExpression datetimeRegex("<datetime>(.*?)</datetime>");
        QRegularExpressionMatch datetimeMatch = datetimeRegex.match(transactionContent);
        if (datetimeMatch.hasMatch()) {
            formatted += QString("  Date/Time: %1\n").arg(datetimeMatch.captured(1));
        }

        // Extract items
        formatted += "  Items:\n";
        QRegularExpression itemRegex("<item>(.*?)</item>");
        itemRegex.setPatternOptions(QRegularExpression::DotMatchesEverythingOption);

        QRegularExpressionMatchIterator itemIterator = itemRegex.globalMatch(transactionContent);

        while (itemIterator.hasNext()) {
            QRegularExpressionMatch itemMatch = itemIterator.next();
            QString itemContent = itemMatch.captured(1);

            QString itemName = "";
            QString itemQuantity = "";

            QRegularExpression nameRegex("<name>(.*?)</name>");
            QRegularExpressionMatch nameMatch = nameRegex.match(itemContent);
            if (nameMatch.hasMatch()) {
                itemName = nameMatch.captured(1);
            }

            QRegularExpression quantityRegex("<quantity>(.*?)</quantity>");
            QRegularExpressionMatch quantityMatch = quantityRegex.match(itemContent);
            if (quantityMatch.hasMatch()) {
                itemQuantity = quantityMatch.captured(1);
            }

            formatted += QString("    - %1 (Qty: %2)\n").arg(itemName, itemQuantity);
        }

        formatted += "\n";
    }

    if (formatted.isEmpty()) {
        formatted = "No transactions found in XML data.";
    }

    return formatted;
}

void ReceiverWindow::updateActions()
{
    // Update action states based on current state
}

/*
void ReceiverWindow::logMessage(const QString &message)
{
    //QString timestamp = QDateTime::currentDateTime().toString("hh:mm:ss");
    // You could add a separate log widget or use status bar
    //mStatusBar->showMessage(QString("[%1] %2").arg(timestamp, message), 5000);
}
*/
