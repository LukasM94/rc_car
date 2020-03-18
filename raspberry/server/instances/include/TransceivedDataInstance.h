#ifndef TRANSMIITED_DATA_INSTANCE_H
#define TRANSMIITED_DATA_INSTANCE_H

#include <atomic>

class TransceivedDataInstance
{
  public:
    static TransceivedDataInstance* instance();
    ~TransceivedDataInstance();
    inline unsigned long getTransmittedBytes()
    {
      return transmitted_bytes_.load();
    }
    inline unsigned long getReceivedBytes()
    {
      return received_bytes_.load();
    }
    inline unsigned long getReceivedImages()
    {
      return received_images_.load();
    }
    inline void addTransmittedBytes(unsigned long bytes)
    {
      transmitted_bytes_ += bytes;
    }
    inline void addReceivedBytes(unsigned long bytes)
    {
      received_bytes_ += bytes;
    }
    inline void addReceivedImage()
    {
      received_images_ += 1;
    }
    inline void reset()
    {
      received_images_   = 0;
      transmitted_bytes_ = 0;
      received_bytes_    = 0;
    }
  private:
    TransceivedDataInstance();
    static TransceivedDataInstance* instance_;
    std::atomic_uint64_t received_images_;
    std::atomic_uint64_t transmitted_bytes_;
    std::atomic_uint64_t received_bytes_;
};

#endif