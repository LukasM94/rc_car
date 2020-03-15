
#include <MainWindow.h>
#include <debug.h>
#include <unistd.h>
#include <ui_MainWindow.h>

MainWindow::MainWindow(QWidget *parent) : 
  QMainWindow(parent), 
  ui_(new Ui::MainWindow) 
{
  debug(MAIN_WINDOW, "ctor\n");
  ui_->setupUi(this);
  setWindowTitle("Camera");
  setWindowOpacity(0.98);
  setMinimumSize(640, 510);
  setMaximumSize(640, 510);

  ui_->buttonStart->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  connect(ui_->buttonStart, SIGNAL(clicked()), SLOT(run()));
}

MainWindow::~MainWindow()
{
  debug(MAIN_WINDOW, "dtor\n");
}

void MainWindow::run()
{
  debug(MAIN_WINDOW, "run: Start\n");
  while (1)
  {
    sleep(10);
  }
  debug(MAIN_WINDOW, "run: Exit\n");
}