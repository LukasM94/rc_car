
#include <MainWindow.h>
#include <debug.h>
#include <ui_MainWindow.h>
#include <QThread>
#include <GamePadInstance.h>
#include <GamePad.h>
#include <ThreadHandler.h>
#include <VideoDisplay.h>
#include <StatusDisplay.h>
#include <Image.h>

MainWindow::MainWindow(QWidget *parent) : 
  QMainWindow(parent), 
  ui_(new Ui::MainWindow),
  lock_("MainWindow::lock_"),
  graph_(0),
  status_display_(0),
  video_display_(0)
{
  debug(MAIN_WINDOW, "ctor\n");
  ui_->setupUi(this);
  setWindowTitle("Camera");
  setWindowOpacity(0.98);
  setMinimumSize(650, 600);
  setMaximumSize(650, 600);

  setFont(ui_->button_start);
  setFont(ui_->button_stop);
  setFont(ui_->left_status, 16);
  setFont(ui_->right_status, 14);

  ui_->button_start->show();
  ui_->button_stop->hide();

  ui_->button_start->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  ui_->button_stop->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  ui_->label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  ui_->left_status->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  ui_->right_status->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  connect(ui_->button_start, SIGNAL(clicked()), SLOT(start()));
  connect(ui_->button_stop, SIGNAL(clicked()), SLOT(stop()));

  status_display_ = new StatusDisplay(this);
  video_display_ = new VideoDisplay(this);
}

MainWindow::~MainWindow()
{
  if (graph_ != 0)
  {
    delete graph_;
  }
  debug(MAIN_WINDOW, "dtor\n");
}

void MainWindow::setFont(QPushButton* button)
{
  QFont font("Newyork", 19);
  font.setStyleHint(QFont::SansSerif);
  button->setFont(font);
}

void MainWindow::setFont(QLabel* label, int size)
{
  QFont font("Newyork", size);
  font.setStyleHint(QFont::SansSerif);
  label->setFont(font);
}

void MainWindow::stop()
{
  lock_.lock();
  ui_->button_stop->hide();
  ui_->button_start->show();
  lock_.unlock();

  debug(MAIN_WINDOW, "stop\n");
  status_display_->cancel();
  video_display_->cancel();
  ThreadHandler::waitTillThreadFinished(status_display_);
  ThreadHandler::waitTillThreadFinished(video_display_);
}

void MainWindow::start()
{
  lock_.lock();
  ui_->button_start->hide();
  ui_->button_stop->show();
  lock_.unlock();

  debug(MAIN_WINDOW, "start\n");
  ThreadHandler::startExternThread(status_display_);
  ThreadHandler::startExternThread(video_display_);
}

void MainWindow::setStatusLeft(std::string& left)
{
  lock_.lock();
  ui_->left_status->setText(left.c_str());
  lock_.unlock();
}

void MainWindow::setStatusRight(std::string& right)
{
  lock_.lock();
  ui_->right_status->setText(right.c_str());
  lock_.unlock();
}

void MainWindow::setImage(Image* image)
{
  lock_.lock();
  QImage* temp = new QImage((const uchar *)image->getData(), 
      image->getWidth(), image->getHeight(), QImage::Format_RGB888);
  ui_->label->setPixmap(QPixmap::fromImage(*temp));
  qApp->processEvents();
  if (graph_ != 0)
  {
    delete graph_;
  }
  graph_ = temp;
  lock_.unlock();
}