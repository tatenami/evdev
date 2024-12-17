#include "PadReader.hpp"

namespace pad {

  void PadReader::findDeviceName(std::string devname, std::ifstream& read_stream) {
    bool is_found = false;
    std::string read_buf;

    while (std::getline(read_stream, read_buf)) {
      if (read_buf.find(devname) != std::string::npos) {
        is_found = true;
        break;
      }
    }

    if (!is_found) {
      throw std::string("Fail to find target device");
    }
  }

  void PadReader::findDeviceHandler(std::ifstream& read_stream) {
    std::string read_buf;
    std::regex  regex_devfile(R"(event(\d+))");
    std::smatch smatch;

    while (std::getline(read_stream, read_buf)) {
      if (read_buf.find("Handlers=") != std::string::npos) break;
    }

    if (std::regex_search(read_buf, smatch, regex_devfile)) {
      devfile_.path = devfile_path + smatch[0].str();
      std::cout << "devfile: " << devfile_.path << std::endl;
    }
    else { 
      throw std::string("Fail to find device file");
    }
  }

  void PadReader::openDeviceFile() {
    devfile_.fd = open(devfile_.path.c_str(), O_RDONLY | O_NONBLOCK);

    if (devfile_.fd == -1) {
      throw std::string("Fail to open device file");
    }
  }

  bool PadReader::connect(std::string devname) {
    std::ifstream read_stream(devlist_file);
    bool is_readable = false;

    try {
      findDeviceName(devname, read_stream);
      findDeviceHandler(read_stream);
      openDeviceFile();
      is_readable = true; 
    }
    catch (std::string msg) {
      std::cout << "[ ERROR ] -> [ " << msg << " ]" << std::endl;
    }

    connection_state_ = is_readable;
    event_ = {EventType::None, 0, 0};

    read_stream.close();
    return is_readable;
  }


  PadReader::PadReader() {}

  PadReader::~PadReader() { disconnect(); }

  bool PadReader::readEvent() {
    if (read(devfile_.fd, &(raw_event_), sizeof(raw_event_)) > 0) {

      if (raw_event_.type == EV_SYN) {
        return false;
      }

      switch (raw_event_.type) {
        case EV_ABS: event_.type = EventType::Axis;   break;
        case EV_KEY: event_.type = EventType::Button; break;
      }

      event_.code  = raw_event_.code;
      event_.value = raw_event_.value; 

      return true;
    }
    else {
      if (errno != EAGAIN) {
        connection_state_ = false;
      }

      return false;
    }
  }

  void PadReader::disconnect() { close(devfile_.fd); }

}