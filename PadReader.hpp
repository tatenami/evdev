#pragma once

#include "PadEvent.hpp"

#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <sys/ioctl.h>
#include <stdint.h>

#include <fstream>
#include <iostream>
#include <string>
#include <regex>

namespace pad {

  struct DevFile {
    int fd;
    std::string path;
  };


  class PadReader {
   private:
    const std::string devfile_path = "/dev/input/";
    const std::string devlist_file = "/proc/bus/input/devices";

    bool          connection_state_;
    input_event   raw_event_;
    DevFile    devfile_;
    PadEvent   event_;

    void findDeviceName(std::string devname, std::ifstream& read_stream);
    void findDeviceHandler(std::ifstream& read_stream);
    void openDeviceFile();

   public:
    ~PadReader();

    bool connect(std::string devname);
    void disconnect();
    bool readEvent();
    bool isConnected();
    PadEvent getPadEvent();
  };

  inline bool PadReader::isConnected() { return this->connection_state_; }

  inline PadEvent PadReader::getPadEvent() { return this->event_; }
}