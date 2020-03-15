#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <atomic>

class QLabel;
class QImage;
class QPushButton;

namespace Ui
{
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

  private:
    void setFont(QPushButton* button);

    Ui::MainWindow*  ui_;
    std::atomic_bool running_;

  public slots:
    void run();
};

#endif