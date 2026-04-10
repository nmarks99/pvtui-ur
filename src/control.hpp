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
};
