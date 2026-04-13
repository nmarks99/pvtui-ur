#pragma once
#include <ftxui/component/component.hpp>
#include <pvtui/pvtui.hpp>

class Status : public ftxui::ComponentBase {
  public:
    Status(pvtui::App& app, const std::string& prefix);
    std::string prefix;

  private:
    pvtui::ButtonWidget reconnect;
    pvtui::ButtonWidget disconnect;
    pvtui::BitsWidget safety_bits;
    pvtui::Monitor<std::string> uptime;
    pvtui::Monitor<std::string> runtime_state;
    pvtui::Monitor<int> connected;
    pvtui::Monitor<std::string> joint1;
    pvtui::Monitor<std::string> joint2;
    pvtui::Monitor<std::string> joint3;
    pvtui::Monitor<std::string> joint4;
    pvtui::Monitor<std::string> joint5;
    pvtui::Monitor<std::string> joint6;
    pvtui::Monitor<std::string> pose1;
    pvtui::Monitor<std::string> pose2;
    pvtui::Monitor<std::string> pose3;
    pvtui::Monitor<std::string> pose4;
    pvtui::Monitor<std::string> pose5;
    pvtui::Monitor<std::string> pose6;
};
