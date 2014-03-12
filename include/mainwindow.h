 #ifndef MAINWINDOW_H
 #define MAINWINDOW_H

 #include <QMainWindow>

 class QAction;
 class QActionGroup;
 class QLabel;
 class QMenu;

 class MainWindow : public QMainWindow
 {
     Q_OBJECT

 public:
     MainWindow();

 protected:
     void contextMenuEvent(QContextMenuEvent *event);

 private slots:
     void newFile();
     void about();

 private:
     void createActions();
     void createMenus();

     QMenu *fileMenu;
     QMenu *helpMenu;

     QActionGroup *alignmentGroup;
     QAction *newAct;
     QAction *exitAct;
     QAction *aboutAct;
     QAction *aboutQtAct;
     QLabel *infoLabel;
 };

 #endif
