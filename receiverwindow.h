#ifndef RECEIVERWINDOW_H
#define RECEIVERWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QStatusBar>
#include <QTextEdit>
#include <QAction>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QStatusBar>
#include <QApplication>
#include <QDateTime>
#include "udpreceiver.h"

class UdpReceiver;

class ReceiverWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit ReceiverWindow(QWidget *parent = nullptr);
    ~ReceiverWindow();

private slots:
    void onStartListening();
    void onStopListening();
    void onClearData();
    void onAbout();
    void onExit();

    void onDataReceived(const QString &data);
private:
    QTextEdit *mDataTextEdit;
    QMenu *mFileMenu;
    QMenu *mNetworkMenu;
    QMenu *mHelpMenu;
    QAction *mStartListeningAction;
    QAction *mStopListeningAction;
    QAction *clearDataAction;
    QAction *mExitAction;
    QAction *mAboutAction;
    QAction *mClearDataAction;
    QStatusBar *mStatusBar;
    UdpReceiver *mReceiver;

    void setupUI();
    void setupMenus();
    void setupStatusBar();
    void setupConnections();

    void updateActions();
    void logMessage(const QString &message);
};

#endif // RECEIVERWINDOW_H
