#ifndef RECEIVERWINDOW_H
#define RECEIVERWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QStatusBar>
#include <QTextEdit>
#include <QAction>
#include <QMenu>
#include <QGroupBox>
#include <QFont>
#include <QSplitter>
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QStatusBar>
#include <QApplication>
#include <QDateTime>
#include <QRegularExpressionMatchIterator>
#include "udpreceiver.h"

class ReceiverWindow : public QMainWindow
{
    Q_OBJECT
public:
    ReceiverWindow(QWidget *parent = nullptr);
    ~ReceiverWindow();
private slots:
    void onStartListening();
    void onStopListening();
    void onClearData();
    void onAbout();
    void onExit();
    void onDataReceived(const QString &data);
private:
    void setupUI();
    void setupMenus();
    void setupStatusBar();
    void setupConnections();
    void updateActions();
    QString formatXMLData(const QString &xmlData);

    //UI comps
    QTextEdit *mDataTextEdit;
    QTextEdit *mRawDataTextEdit;
    QTextEdit *mFormattedDataTextEdit;
    QLabel *mStatsLabel;

    //Menus and Actions
    QMenu *mFileMenu;
    QMenu *mNetworkMenu;
    QMenu *mHelpMenu;
    QAction *mStartListeningAction;
    QAction *mStopListeningAction;
    QAction *mClearDataAction;
    QAction *mExitAction;
    QAction *mAboutAction;

    //Status bar
    QStatusBar *mStatusBar;

    UdpReceiver *mReceiver;

    //Stats
    int mMessageCount;
};

#endif
