
#include <MainWindow.h>
#include <debug.h>
#include <unistd.h>

MainWindow::MainWindow(QWidget *parent) : 
  QMainWindow(parent), 
  ui_(new Ui::MainWindow) 
{
  ui_->setupUi(this);
  setWindowTitle("Camera");
  setWindowOpacity(0.98);
  setMinimumSize(380, 450);
  setMaximumSize(380, 450);

  ui_->radioButtonStart->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  connect(ui_->radioButtonStart, SIGNAL(toggle(bool)), SLOT(run()));
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