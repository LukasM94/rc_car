
#include <CameraService.h>
#include <debug.h>
#include <Image.h>
#include <ServerHandler.h>
#include <string.h>

CameraService::CameraService(ServerHandler* server_handler) :
  WorkingThread("CameraService"),
  image_json_data_(0),
  state_(START),
  server_handler_(server_handler),
  image_(0)
{
  debug(CAM_SERVICE, "ctor: service_handler <%p>\n", server_handler_);
}

CameraService::~CameraService()
{
  debug(CAM_SERVICE, "dtor\n");
}

void CameraService::stateStart()
{
  if (image_json_data_ == 0)
  {
    image_json_data_ = new struct ImageJsonData({0, -1, 0, -1});
  }
  else
  {
    delete image_json_data_->header_;
    image_json_data_->header_ = 0;
    image_json_data_->header_length_ = -1;
    delete image_json_data_->body_;
    image_json_data_->body_ = 0;
    image_json_data_->body_lenght_ = -1;
  }
  state_ = HEADER;
  debug(CAM_SERVICE, "stateStart: Goto state header\n");
}

void CameraService::stateHeader()
{
  int ret;
  if ((ret = server_handler_->receive()) != 0)
  {
    return;
  }
  ret = Image::getSizeOfBody(server_handler_->input_buffer_, &image_json_data_->body_lenght_);
  if (ret != 0)
  {
    return;
  }
  memcpy(image_json_data_->header_, server_handler_->input_buffer_, server_handler_->BUFFER_SIZE);
  state_ = BODY;
  debug(CAM_SERVICE, "stateHeader: Goto state body\n");
}

void CameraService::stateBody()
{
  int count = image_json_data_->body_lenght_ / server_handler_->BUFFER_SIZE;
}

void CameraService::stateEnd()
{

}

void CameraService::run()
{
  debug(CAM_SERVICE, "run: Start\n");
  while (server_handler_->connected_)
  {
    state_ = START;
    while (state_ != END)
    {
      switch (state_)
      {
      case START:
        stateStart();
        break;
      case HEADER:
        stateHeader();
        break;
      case BODY:
        stateBody();
        break;
      default:
        stateEnd();
        break;
      }
    }
    debug(CAM_SERVICE, "run: Got message\n");
  }
  debug(CAM_SERVICE, "run: Exit\n");
}