#include <Graphics.h>
#include <QApplication>
#include <QLabel>
#include <debug.h>
#include <ImageInstance.h>
#include <Image.h>
#include <unistd.h>
#include <MainWindow.h>

Graphics::Graphics() :
  WorkingThread("Graphics")
{
  debug(GRAPHICS, "ctor\n");
}

Graphics::~Graphics()
{
  debug(GRAPHICS, "dtor\n");
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