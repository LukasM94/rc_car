#include <Graphics.h>
#include <QApplication>
#include <QLabel>

extern char* gdata;
extern int gx;
extern int gy;

int graphics(int argc, char* argv[])
{
  QApplication app(argc, argv);
  QImage graph((uchar *)gdata, gx, gy, QImage::Format_RGB888);
  QLabel *label = new QLabel();
  label->setPixmap(QPixmap::fromImage(graph));
  label->setFixedSize(gx, gy);
  label->show();
  return app.exec();
}