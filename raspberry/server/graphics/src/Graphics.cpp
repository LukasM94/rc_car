#include <Graphics.h>
#include <QApplication>
#include <QLabel>
#include <debug.h>
#include <ImageInstance.h>
#include <Image.h>
#include <unistd.h>

Graphics::Graphics(const char* name) :
  WorkingThread(name),
  argv_(0),
  argc_(0),
  app_(new QApplication(argv_, argc_)),
  graph_(0),
  label_(0),
  image_(0)
{
  debug(GRAPHICS, "ctor\n");
}

Graphics::~Graphics()
{
  debug(GRAPHICS, "dtor\n");
  delete app_;
  if (graph_ != 0)
  {
    delete graph_;
  }
  if (label_ != 0)
  {
    delete label_;
  }
}

void Graphics::run()
{
  debug(GRAPHICS, "run: Start\n");
  debug(GRAPHICS, "run: Want to load a image\n");

  image_ = ImageInstance::instance()->loadImage();
  image_->print();
  debug(GRAPHICS, "run: Create graphic\n");
  graph_ = new QImage((uchar*)image_->getData(), image_->getWidth(), image_->getHeight(), QImage::Format_RGB888);
  label_ = new QLabel();
  label_->setPixmap(QPixmap::fromImage(*graph_));
  label_->setFixedSize(image_->getWidth(), image_->getHeight());
  label_->show();

  while (running_)
  {
    sleep(10);
  }
  debug(GRAPHICS, "run: Exit\n");
}

// int graphics(int argc, char* argv[])
// {
//   QApplication app(argc, argv);
//   QImage graph((uchar *)gdata, gx, gy, QImage::Format_RGB888);
//   QLabel *label = new QLabel();
//   label->setPixmap(QPixmap::fromImage(graph));
//   label->setFixedSize(gx, gy);
//   label->show();
//   return app.exec();
// }