#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <atomic>
#include <string>
#include <Lock.h>

class QLabel;
class QImage;
class QPushButton;
class Image;
class StatusDisplay;
class VideoDisplay;

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

    void setStatusLeft(std::string& left);
    void setStatusRight(std::string& right);
    void setImage(Image* image);

  private:
    void setFont(QPushButton* button);
    void setFont(QLabel* label, int size);

    Ui::MainWindow* ui_;
    Lock            lock_;

    std::atomic_bool running_;

    QImage* graph_;

    StatusDisplay* status_display_;
    VideoDisplay*  video_display_;


  public slots:
    void start();
    void stop();
};

#endif