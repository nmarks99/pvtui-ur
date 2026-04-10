#include <ftxui/component/component.hpp>
#include <pvtui/pvtui.hpp>

class Dashboard : public ftxui::ComponentBase {
  public:
    Dashboard(pvtui::App& app, const std::string& prefix);
    std::string prefix;

  private:
    pvtui::Monitor<std::string> mode;
    pvtui::Monitor<std::string> safety_str;
    pvtui::Monitor<std::string> connected;
    pvtui::Monitor<std::string> remote;
    pvtui::Monitor<std::string> safety;
    pvtui::Monitor<std::string> prog;
    pvtui::Monitor<std::string> progstate;
    pvtui::ButtonWidget connect;
    pvtui::ButtonWidget disconnect;
    pvtui::ButtonWidget poweron;
    pvtui::ButtonWidget poweroff;
    pvtui::ButtonWidget play;
    pvtui::ButtonWidget pause;
    pvtui::ButtonWidget stop;
    pvtui::InputWidget urp;
};
