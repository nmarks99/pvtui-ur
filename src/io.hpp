#pragma once
#include <ftxui/component/component.hpp>
#include <pvtui/pvtui.hpp>

class IOTab : public ftxui::ComponentBase {
  public:
    IOTab(pvtui::App& app, const std::string& prefix);
    std::string prefix;

  private:
    pvtui::Monitor<int> connected;

    pvtui::BitsWidget di_standard_bits;
    pvtui::BitsWidget di_config_bits;
    pvtui::BitsWidget di_tool_bits;
    pvtui::BitsWidget do_standard_bits;
    pvtui::BitsWidget do_config_bits;
    pvtui::BitsWidget do_tool_bits;

    pvtui::ChoiceWidget do_standard0;
    pvtui::ChoiceWidget do_standard1;
    pvtui::ChoiceWidget do_standard2;
    pvtui::ChoiceWidget do_standard3;
    pvtui::ChoiceWidget do_standard4;
    pvtui::ChoiceWidget do_standard5;
    pvtui::ChoiceWidget do_standard6;
    pvtui::ChoiceWidget do_standard7;

    pvtui::ChoiceWidget do_config0;
    pvtui::ChoiceWidget do_config1;
    pvtui::ChoiceWidget do_config2;
    pvtui::ChoiceWidget do_config3;
    pvtui::ChoiceWidget do_config4;
    pvtui::ChoiceWidget do_config5;
    pvtui::ChoiceWidget do_config6;
    pvtui::ChoiceWidget do_config7;

    pvtui::ChoiceWidget do_tool0;
    pvtui::ChoiceWidget do_tool1;

    pvtui::InputWidget ao_voltage0;
    pvtui::InputWidget ao_voltage1;
    pvtui::InputWidget ao_current0;
    pvtui::InputWidget ao_current1;

    pvtui::Monitor<std::string> ai0;
    pvtui::Monitor<std::string> ai1;
    pvtui::Monitor<std::string> ao_rbv0;
    pvtui::Monitor<std::string> ao_rbv1;
};
