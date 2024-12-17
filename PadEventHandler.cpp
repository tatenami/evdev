#include "PadEventHandler.hpp"

namespace pad {

  void PadEventHandler::setDeadzone(uint16_t deadzone) {
    this->deadzone_ = deadzone;
  }
  
  void PadEventHandler::editEvent(PadReader& reader) {
    this->event_ = reader.getPadEvent();

    switch (event_.type) {
      case (EventType::Button): {
        handleButtonEvent();
        break;
      }
      case (EventType::Axis): {
        handleAxisEvent();
        break;
      }
    }
  }

}
