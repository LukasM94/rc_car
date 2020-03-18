#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <atomic>

class QLabel;
class QImage;
class QPushButton;
class Image;

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
    static void* wrapperStart(void* arg)
    {
      reinterpret_cast<MainWindow*>(arg)->run();
      return 0;
    }
    void run();

  private:
    void setFont(QPushButton* button);
    void setFont(QLabel* label, int size);

    Ui::MainWindow*  ui_;
    std::atomic_bool running_;
    long unsigned int tid_;
    QImage* graph_;
    Image*  image_;

  public slots:
    void start();
    void stop();
};

#endif