#pragma once
#include <ftxui/component/component.hpp>
#include <pvtui/pvtui.hpp>

class ControlAxis : public ftxui::ComponentBase {
  public:
    ControlAxis(pvtui::App& app, const std::string& prefix, const std::string& axis_prefix, const std::string& rbv);
  private:
    pvtui::InputWidget val;
    pvtui::InputWidget twv;
    pvtui::ButtonWidget twr;
    pvtui::ButtonWidget twf;
    pvtui::Monitor<std::string> rbv;
    pvtui::Monitor<std::string> egu;
};

class Control : public ftxui::ComponentBase {
  public:
    Control(pvtui::App& app, const std::string& prefix);
    std::string prefix;

  private:
    ftxui::Component axis1;
    ftxui::Component axis2;
    ftxui::Component axis3;
    ftxui::Component axis4;
    ftxui::Component axis5;
    ftxui::Component axis6;
    ftxui::Component axis7;
    ftxui::Component axis8;
    ftxui::Component axis9;
    ftxui::Component axis10;
    ftxui::Component axis11;
    ftxui::Component axis12;
    pvtui::ChoiceWidget auto_movej;
    pvtui::ChoiceWidget auto_movel;
    pvtui::ButtonWidget stopj;
    pvtui::ButtonWidget stopl;
    pvtui::ButtonWidget movej;
    pvtui::ButtonWidget movel;
    pvtui::ButtonWidget disconnect;
    pvtui::ButtonWidget reconnect;
    pvtui::ButtonWidget stop_ctrl_script;
    pvtui::ButtonWidget reupload_ctrl_script;
    pvtui::ButtonWidget stop;
    pvtui::InputWidget tcp_offset_x;
    pvtui::InputWidget tcp_offset_y;
    pvtui::InputWidget tcp_offset_z;
    pvtui::InputWidget tcp_offset_roll;
    pvtui::InputWidget tcp_offset_pitch;
    pvtui::InputWidget tcp_offset_yaw;
    pvtui::ChoiceWidget teach;
    pvtui::Monitor<int> connected;
    pvtui::Monitor<pvtui::PVEnum> moving;
    pvtui::SliderWidget speed_slider;
};
