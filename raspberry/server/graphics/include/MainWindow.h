#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>

class QLabel;
class QImage;

class MainWindow : public QMainWindow
{
  public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void run();

  private:
    Ui::MainWindow* ui_;
    QLabel*         label_;
    QImage*         image_;
};

#endif