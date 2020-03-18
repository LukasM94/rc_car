
#include <MainWindow.h>
#include <debug.h>
#include <ui_MainWindow.h>
#include <Image.h>
#include <ImageInstance.h>
#include <QThread>
#include <GamePadInstance.h>
#include <GamePad.h>
#include <string>
#include <ThreadHandler.h>

MainWindow::MainWindow(QWidget *parent) : 
  QMainWindow(parent), 
  ui_(new Ui::MainWindow),
  running_(1),
  tid_(-1),
  graph_(0),
  image_(0)
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
  setFont(ui_->right_status, 16);

  ui_->button_stop->hide();

  ui_->button_start->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  ui_->button_stop->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  ui_->label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  ui_->left_status->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  connect(ui_->button_start, SIGNAL(clicked()), SLOT(start()));
  connect(ui_->button_stop, SIGNAL(clicked()), SLOT(stop()));
}

MainWindow::~MainWindow()
{
  if (graph_ != 0)
  {
    delete graph_;
  }
  if (image_ != 0)
  {
    delete image_;
  }
  debug(MAIN_WINDOW, "dtor\n");
}

void MainWindow::setFont(QPushButton* button)
{
  QFont font("Newyork", 18);
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
  ui_->button_stop->hide();
  ui_->button_start->show();
  debug(MAIN_WINDOW, "stop\n");
  running_ = 0;
}

void MainWindow::start()
{
  ui_->button_start->hide();
  ui_->button_stop->show();
  debug(MAIN_WINDOW, "start\n");
  running_ = 1;
  ThreadHandler::startExternThread(&tid_, &wrapperStart, this);
}

void MainWindow::run()
{
  debug(MAIN_WINDOW, "run: Start\n");

  GamePad* game_pad = GamePadInstance::instance()->getGamePad();

  QImage* graph_tmp = 0;
  Image*  image_tmp = 0;
  Image*  image_new = 0;

  debug(MAIN_WINDOW, "run: Start\n");
  while (running_)
  {
    // IMAGE
    graph_tmp = graph_;
    image_tmp = image_;

    image_new = ImageInstance::instance()->loadImage();
    if (image_new != 0)
    {
      debug(MAIN_WINDOW, "run: Load image_\n");
      image_ = image_new;
      graph_ = new QImage((const uchar *)image_->getData(), 
          image_->getWidth(), image_->getHeight(), QImage::Format_RGB888);
      debug(MAIN_WINDOW, "run: Set new image_\n");
      ui_->label->setPixmap(QPixmap::fromImage(*graph_));
      qApp->processEvents();

      if (graph_tmp != 0)
      {
        delete graph_tmp;
      }
      if (image_tmp != 0)
      {
        delete image_tmp;
      }

      // GAME PAD DATA
      std::string data;
      game_pad->getPrintableString(data);
      ui_->left_status->setText(data.c_str());

      // RC CAR
    }
    QThread::msleep(20);
  }
  ui_->left_status->setText("");

  debug(MAIN_WINDOW, "run: Exit\n");
}