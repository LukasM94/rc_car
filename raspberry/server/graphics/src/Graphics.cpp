#include <Graphics.h>
#include <QApplication>
#include <debug.h>
#include <ImageInstance.h>
#include <Image.h>
#include <unistd.h>
#include <MainWindow.h>

Graphics::Graphics() :
  WorkingThread("Graphics"),
  argv_(0),
  argc_(0),
  app_(0),
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

  int argc = 1;
  char* argv[] = {"./main", 0};
  QApplication a(argc, argv);
  MainWindow window;
  window.show();
  a.exec();
  debug(GRAPHICS, "run: Exec finished\n");
}