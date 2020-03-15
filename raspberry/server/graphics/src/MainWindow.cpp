
#include <MainWindow.h>
#include <debug.h>
#include <unistd.h>
#include <ui_MainWindow.h>
#include <Image.h>
#include <ImageInstance.h>

MainWindow::MainWindow(QWidget *parent) : 
  QMainWindow(parent), 
  ui_(new Ui::MainWindow),
  running_(1)
{
  debug(MAIN_WINDOW, "ctor\n");
  ui_->setupUi(this);
  setWindowTitle("Camera");
  setWindowOpacity(0.98);
  setMinimumSize(650, 530);
  setMaximumSize(650, 530);

  setFont(ui_->button_start);

  ui_->button_start->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
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
  running_ = 1;
  QImage* graph_tmp = 0;
  QImage* graph     = 0;
  Image*  image;
  debug(MAIN_WINDOW, "run: Start\n");
  while (running_)
  {
    debug(MAIN_WINDOW, "run: Want to load a image\n");

    image     = ImageInstance::instance()->loadImage();
    graph_tmp = graph;

    graph = new QImage((const uchar *)image->getData(), 
        image->getWidth(), image->getHeight(), QImage::Format_RGB888);
    ui_->label->setPixmap(QPixmap::fromImage(*graph));
    ui_->label->show();
    if (graph_tmp == 0)
    {
      delete graph_tmp;
    }
  }
  debug(MAIN_WINDOW, "run: Exit\n");
}