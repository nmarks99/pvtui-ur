#pragma once
#include <ftxui/component/component.hpp>
#include <pvtui/pvtui.hpp>

class Gripper : public ftxui::ComponentBase {
  public:
    Gripper(pvtui::App& app, const std::string& prefix);
    std::string prefix;

  private:
    pvtui::Monitor<int> connected;
    pvtui::Monitor<int> active;
    pvtui::Monitor<int> is_open;
    pvtui::Monitor<int> is_closed;
    pvtui::Monitor<pvtui::PVEnum> move_status;
    pvtui::Monitor<std::string> position;
    pvtui::ButtonWidget connect;
    pvtui::ButtonWidget calibrate;
    pvtui::ButtonWidget activate;
    pvtui::ButtonWidget open;
    pvtui::ButtonWidget close;
    pvtui::InputWidget speed;
    pvtui::InputWidget force;
};
