
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
    if (image_json_data_->header_ != 0)
    {
      delete image_json_data_->header_;
      image_json_data_->header_ = 0;
      image_json_data_->header_length_ = -1;
    }
    if (image_json_data_->body_ != 0)
    {
      delete image_json_data_->body_;
      image_json_data_->body_ = 0;
      image_json_data_->body_lenght_ = -1;
    }
  }
  state_ = HEADER;
  debug(CAM_SERVICE, "stateStart: Goto state header\n");
}

void CameraService::stateHeader()
{
  int ret;
  int size;
  if ((ret = server_handler_->receive()) != 0)
  {
    state_ = ERROR;
    return;
  }
  ret = Image::getSizeOfBody(server_handler_->input_buffer_, &size);
  if (ret != 0)
  {
    state_ = ERROR;
    return;
  }
  image_json_data_->header_length_ = server_handler_->BUFFER_SIZE;
  image_json_data_->header_        = new char[image_json_data_->header_length_];
  image_json_data_->body_lenght_   = size;
  image_json_data_->body_          = new char[image_json_data_->body_lenght_];

  memcpy(image_json_data_->header_, server_handler_->input_buffer_, image_json_data_->header_length_);
  memset(image_json_data_->body_, 0, image_json_data_->body_lenght_);

  state_ = BODY;
  debug(CAM_SERVICE, "stateHeader: Body length is %d\n", image_json_data_->body_lenght_);
  debug(CAM_SERVICE, "stateHeader: Goto state body\n");
}

void CameraService::stateBody()
{
  int count = image_json_data_->body_lenght_ / server_handler_->BUFFER_SIZE;
  int ret;
  while (count--)
  {
    if ((ret = server_handler_->receive()) != 0)
    {
      state_ = ERROR;
      return;
    }
    debug(CAM_SERVICE, "stateBody: Count %d\n", count);
  }
  state_ = END;
}

void CameraService::run()
{
  debug(CAM_SERVICE, "run: Start\n");
  while (server_handler_->connected_)
  {
    state_ = START;
    while (state_ != END)
    {
      if (state_ == START)
      {
        stateStart();
      }
      else if (state_ == HEADER)
      {
        stateHeader();
      }
      else if (state_ == BODY)
      {
        stateBody();
      }
      else
      {
        
      }
    }
    debug(CAM_SERVICE, "run: Got message\n");
  }
  debug(CAM_SERVICE, "run: Exit\n");
}