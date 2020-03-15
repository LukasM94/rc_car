#include <Graphics.h>
#include <QApplication>
#include <debug.h>
#include <ImageInstance.h>
#include <Image.h>
#include <unistd.h>
#include <MainWindow.h>

Graphics::Graphics(const char* name) :
	WorkingThread(name),
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


	// debug(GRAPHICS, "run: Want to load a image\n");
	// image_ = ImageInstance::instance()->loadImage();
	// int argc = 1;
	// char* argv[] = {"./main", 0};
	// QApplication app(argc, argv);
	// QImage* graph = new QImage((const uchar *)image_->getData(), image_->getWidth(), image_->getHeight(), QImage::Format_RGB888);
	// QLabel* label = new QLabel();
	// label->setPixmap(QPixmap::fromImage(*graph));
	// label->setFixedSize(image_->getWidth(), image_->getHeight());
	// label->show();
  // app.exec();
	// if (fork() == 0)
	// {
	// }
	// else
	// {
	// }
	sleep(1000);
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