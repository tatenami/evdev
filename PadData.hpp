#pragma once

#include "PadEvent.hpp"
#include "PadEventHandler.hpp"

#include <unordered_map>
#include <cmath>

namespace pad {

  class PadUI {
   protected:
    const uint8_t id_;

   public:
    PadUI(const uint8_t event_num);
    uint8_t getID();
  };

  class Button: public PadUI {
   protected:
    bool state_;
    ButtonAction action_;

   public:
    Button(const uint8_t event_num);
    Button& get();
    void setState(bool state);
    void setAction(ButtonAction action);
    void setEvent(ButtonEvent event);    
    void setEvent(bool state, ButtonAction action);
    bool pressed();
    bool pushed();
    bool released();
  };

  class Axis: public PadUI {
   private:
    int value_;

   public:
    Axis(const uint8_t event_num);
    Axis& get();
    void  setValue(int value);
    int   getValue();
  };


  class TriggerButton: public Button {
   private:
    Axis depth_;

   public:
    TriggerButton(uint8_t b_event_num, uint8_t a_event_num);
    int getDepth();
    Axis& getTriggerAxis();
  };


  class Stick {
   public:
    Axis x;
    Axis y;

    Stick(uint8_t x_event_num, uint8_t y_event_num);
    double angleDeg();
    double angleRad();
  };


  template <class T>
  class PadUIList {
   protected:
    std::unordered_map<uint8_t, T*> list_;

   public:
    virtual void update(PadEventHandler& handler) = 0;
    virtual void clear() = 0;

    void attach(T& element) {
      this->list_[element.getID()] = &element;
    }
  };


  class ButtonDataList: public PadUIList<Button> {
   private:
    ButtonEvent event_{0, button_state::OFF};

   public:
    void update(PadEventHandler& handler) override;
    void clear() override;
    void resetAction();
  };


  class AxisDataList: public PadUIList<Axis> {
   private:
    AxisEvent event_{0, 0};

   public:
    void update(PadEventHandler& handler) override;
    void clear() override;
  };


  // class ButtonDataList;
  // class AxisDataList;

  // class Button {
  //   friend class ButtonDataList;

  //  protected:
  //   const int    id_;
  //   bool         state_{button_state::OFF};
  //   ButtonAction action_{ButtonAction::None};

  //  public:
  //   Button(const int event_number);
  //   Button& get();
  //   bool pressed();
  //   bool pushed();
  //   bool released();
  // };


  // class Axis {
  //   friend class AxisDataList;

  //  private:
  //   const int id_;
  //   int16_t   value_{0};

  //  public:
  //   Axis(int event_number);
  //   Axis& get();
  //   int   getValue();
  // };

  // class TriggerButton: public Button {
  //  private:
  //   Axis depth_;

  //  public:
  //   TriggerButton(int button_event_num, int axis_event_num);
  //   int   getDepth();
  //   Axis& getAxis();
  // };


  // class Stick {
  //  public:
  //   Axis x;
  //   Axis y;

  //   Stick(int x_event_num, int y_event_num);
  // };


  // class ButtonDataList {
  //  private:
  //   std::vector<Button*> list_{nullptr};
  //   ButtonEvent event_{0, button_state::OFF};

  //  public:
  //   void update(PadEventHandler& handler);
  //   void resister(Button& button);
  //   void resetAction();
  //   void clear();
  // };


  // class AxisDataList {
  //  private:
  //   std::vector<Axis*> list_{nullptr};
  //   AxisEvent event_{0, 0};

  //  public:
  //   void update(PadEventHandler& handler);
  //   void resister(Axis& axis);
  //   void clear();
  // };

}