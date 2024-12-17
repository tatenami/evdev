#pragma once

#include "PadData.hpp"
#include "PadEvent.hpp"
#include "PadEventHandler.hpp"
#include "PadReader.hpp"

namespace pad {

  enum class Connect {
    USB, Bluetooth
  };

  using EventHandler_p = std::unique_ptr<PadEventHandler>;

  template <class T>
  class GamePad {
   protected:
    PadReader    reader_;
    EventHandler_p handler_;
    ButtonDataList buttons_;
    AxisDataList   axes_;
    bool is_connected_{false};

   public:
    GamePad() {
      handler_ = std::make_unique<T>();
    }

    ~GamePad() {
      reader_.disconnect();
    }

    bool isConnected() {
      return is_connected_;
    }
    
    virtual void update() = 0;
  };

}