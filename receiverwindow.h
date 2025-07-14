#ifndef RECEIVERWINDOW_H
#define RECEIVERWINDOW_H

#include <QMainWindow>
class QTextEdit;
class QAction;
class QMenu;
class QStatusBar;
class UdpReceiver;
class QVBoxLayout;
class QApplication;
class QMessageBox;

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
    QMenu *mHelpMenu;
    QAction *mStartListeningAction;
    QAction *mStopListeningAction;
    QAction *clearDataAction;
    QAction *mExitAction;
    QAction *mAboutAction;
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
