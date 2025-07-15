#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void onAddCustomer();
    void onAddItem();
    void onCreateTransaction();
    void onRestoreItems();
    void onStartBroadcast();
    void onStopBroadcast();
    void onAbout();
    void onHelp();
    void onExit();

    void onTransactionAdded();
    void onBroadcastSent(const QString &data);
private:
    //UI comps
    QTreeView *mTransactionView;
    QTextEdit *mLogTextEdit;
    QSplitter *mSplitter;

    //Model
    TransactionModel *mTransactionModel;

    //Menus
    QMenu *mFileMenu;
    QMenu *mDataMenu;
    QMenu *mNetworkMenu;
    QMenu *mHelpMenu;

    //Actions
    QAction *mAddCustomerAction;
    QAction *mAddItemAction;
    QAction *mCreateTransactionAction;
    QAction *mRestoreItemsAction;
    QAction *mStartBroadcastAction;
    QAction *mStopBroadcastAction;
    QAction *mExitAction;
    QAction *mAboutAction;
    QAction *mHelpAction;

    //Toolbar
    QToolBar *mToolBar;

    //Status bar
    QStatusBar *mStatusBar;

    //Network
    UdpBroadcaster *mBroadcaster;

    void setupUI();
    void setupMenus();
    void setupToolBar();
    void setupStatusBar();
    void setupConnections();

    void updateActions();
    void logMessage(const QString &message);
};
#endif // MAINWINDOW_H
