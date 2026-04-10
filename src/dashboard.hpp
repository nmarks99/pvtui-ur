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
    pvtui::Monitor<std::string> polyscope_version;
    pvtui::Monitor<std::string> serial_number;
    pvtui::InputWidget urp;
    pvtui::ButtonWidget connect;
    pvtui::ButtonWidget disconnect;
    pvtui::ButtonWidget poweron;
    pvtui::ButtonWidget poweroff;
    pvtui::ButtonWidget shutdown;
    pvtui::ButtonWidget close_popup;
    pvtui::ButtonWidget close_safety_popup;
    pvtui::ButtonWidget release_brakes;
    pvtui::ButtonWidget restart_safety;
    pvtui::ButtonWidget unlock_prot_stop;
    pvtui::ButtonWidget play;
    pvtui::ButtonWidget pause;
    pvtui::ButtonWidget stop;
};
