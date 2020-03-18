
#include <MainWindow.h>
#include <debug.h>
#include <ui_MainWindow.h>
#include <Image.h>
#include <ImageInstance.h>
#include <QThread>

MainWindow::MainWindow(QWidget *parent) : 
  QMainWindow(parent), 
  ui_(new Ui::MainWindow),
  running_(1)
{
  debug(MAIN_WINDOW, "ctor\n");
  ui_->setupUi(this);
  setWindowTitle("Camera");
  setWindowOpacity(0.98);
  setMinimumSize(650, 600);
  setMaximumSize(650, 600);

  setFont(ui_->button_start);

  ui_->button_start->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  ui_->label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  connect(ui_->button_start, SIGNAL(clicked()), SLOT(run()));
}

MainWindow::~MainWindow()
{
  debug(MAIN_WINDOW, "dtor\n");
}

void MainWindow::setFont(QPushButton* button)
{
  QFont font("Newyork", 18);
  font.setStyleHint(QFont::SansSerif);
  button->setFont(font);
}

void MainWindow::run()
{
  debug(MAIN_WINDOW, "run: Start\n");
  running_ = 1;
  ui_->button_start->hide();

  QImage* graph_tmp = 0;
  QImage* graph     = 0;
  Image*  image_tmp = 0;
  Image*  image     = 0;
  Image*  image_new = 0;

  QLabel* status_label_left = new QLabel();

  debug(MAIN_WINDOW, "run: Start\n");
  while (running_)
  {
    graph_tmp = graph;
    image_tmp = image;

    image_new = ImageInstance::instance()->loadImage();
    if (image_new != 0)
    {
      debug(MAIN_WINDOW, "run: Load image\n");
      image = image_new;
      graph = new QImage((const uchar *)image->getData(), 
          image->getWidth(), image->getHeight(), QImage::Format_RGB888);
      debug(MAIN_WINDOW, "run: Set new image\n");
      ui_->label->setPixmap(QPixmap::fromImage(*graph));
      qApp->processEvents();

      if (graph_tmp != 0)
      {
        delete graph_tmp;
      }
      if (image_tmp != 0)
      {
        delete image_tmp;
      }
    }
    QThread::msleep(20);
  }
  debug(MAIN_WINDOW, "run: Exit\n");
}