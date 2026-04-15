#include "common.hpp"
#include "io.hpp"

using namespace pvtui;
using namespace ftxui;

IOTab::IOTab(pvtui::App& app, const std::string& prefix)
    : prefix(prefix),
      connected(app, prefix + "Receive:Connected.RVAL"),
      di_standard_bits(app, prefix + "Receive:DigitalInputBits.VAL", {0, 8}, Color::Green),
      di_config_bits(app, prefix + "Receive:DigitalInputBits.VAL", {8, 16}, Color::Green),
      di_tool_bits(app, prefix + "Receive:DigitalInputBits.VAL", {16, 18}, Color::Green),
      do_standard_bits(app, prefix + "Receive:DigitalOutputBits.VAL", {0, 8}, Color::Green),
      do_config_bits(app, prefix + "Receive:DigitalOutputBits.VAL", {8, 16}, Color::Green),
      do_tool_bits(app, prefix + "Receive:DigitalOutputBits.VAL", {16, 18}, Color::Green),
      do_standard0(app, prefix + "IO:SetStandardDO0.VAL", ChoiceStyle::Horizontal),
      do_standard1(app, prefix + "IO:SetStandardDO1.VAL", ChoiceStyle::Horizontal),
      do_standard2(app, prefix + "IO:SetStandardDO2.VAL", ChoiceStyle::Horizontal),
      do_standard3(app, prefix + "IO:SetStandardDO3.VAL", ChoiceStyle::Horizontal),
      do_standard4(app, prefix + "IO:SetStandardDO4.VAL", ChoiceStyle::Horizontal),
      do_standard5(app, prefix + "IO:SetStandardDO5.VAL", ChoiceStyle::Horizontal),
      do_standard6(app, prefix + "IO:SetStandardDO6.VAL", ChoiceStyle::Horizontal),
      do_standard7(app, prefix + "IO:SetStandardDO7.VAL", ChoiceStyle::Horizontal),
      do_config0(app, prefix + "IO:SetConfigurableDO0.VAL", ChoiceStyle::Horizontal),
      do_config1(app, prefix + "IO:SetConfigurableDO1.VAL", ChoiceStyle::Horizontal),
      do_config2(app, prefix + "IO:SetConfigurableDO2.VAL", ChoiceStyle::Horizontal),
      do_config3(app, prefix + "IO:SetConfigurableDO3.VAL", ChoiceStyle::Horizontal),
      do_config4(app, prefix + "IO:SetConfigurableDO4.VAL", ChoiceStyle::Horizontal),
      do_config5(app, prefix + "IO:SetConfigurableDO5.VAL", ChoiceStyle::Horizontal),
      do_config6(app, prefix + "IO:SetConfigurableDO6.VAL", ChoiceStyle::Horizontal),
      do_config7(app, prefix + "IO:SetConfigurableDO7.VAL", ChoiceStyle::Horizontal),
      do_tool0(app, prefix + "IO:SetToolDO0.VAL", ChoiceStyle::Horizontal),
      do_tool1(app, prefix + "IO:SetToolDO1.VAL", ChoiceStyle::Horizontal),
      ao_voltage0(app, prefix + "IO:SetVoltageAO0.VAL", PVPutType::Double),
      ao_voltage1(app, prefix + "IO:SetVoltageAO1.VAL", PVPutType::Double),
      ao_current0(app, prefix + "IO:SetCurrentAO0.VAL", PVPutType::Double),
      ao_current1(app, prefix + "IO:SetCurrentAO1.VAL", PVPutType::Double),
      ai0(app, prefix + "Receive:AnalogInput0.VAL"),
      ai1(app, prefix + "Receive:AnalogInput1.VAL"),
      ao_rbv0(app, prefix + "Receive:AnalogOutput0.VAL"),
      ao_rbv1(app, prefix + "Receive:AnalogOutput1.VAL")
{
    auto container = Container::Vertical({
        do_standard0.component(),
        do_standard1.component(),
        do_standard2.component(),
        do_standard3.component(),
        do_standard4.component(),
        do_standard5.component(),
        do_standard6.component(),
        do_standard7.component(),
        do_config0.component(),
        do_config1.component(),
        do_config2.component(),
        do_config3.component(),
        do_config4.component(),
        do_config5.component(),
        do_config6.component(),
        do_config7.component(),
        do_tool0.component(),
        do_tool1.component(),
        ao_voltage0.component(),
        ao_voltage1.component(),
        ao_current0.component(),
        ao_current1.component(),
    });

    container |= Renderer([&](Element) {
        auto do_choice_col = [](auto&... choices) {
            return vbox({choices.component()->Render()...});
        };

        auto outputs_section = vbox({
            text("Standard:") | bold,
            hbox({
                do_choice_col(do_standard0, do_standard1, do_standard2,
                              do_standard3, do_standard4, do_standard5,
                              do_standard6, do_standard7),
                separatorEmpty(),
                do_standard_bits.component()->Render(),
            }),
            separatorEmpty(),
            text("Configurable:") | bold,
            hbox({
                do_choice_col(do_config0, do_config1, do_config2,
                              do_config3, do_config4, do_config5,
                              do_config6, do_config7),
                separatorEmpty(),
                do_config_bits.component()->Render(),
            }),
            separatorEmpty(),
            text("Tool:") | bold,
            hbox({
                do_choice_col(do_tool0, do_tool1),
                separatorEmpty(),
                do_tool_bits.component()->Render(),
            }),
        });

        auto inputs_section = vbox({
            text("Standard:") | bold,
            di_standard_bits.component()->Render(),
            separatorEmpty(),
            text("Configurable:") | bold,
            di_config_bits.component()->Render(),
            separatorEmpty(),
            text("Tool:") | bold,
            di_tool_bits.component()->Render(),
        });

        auto digital_section = hbox({
            vbox({
                text("Outputs") | bold | underlined,
                separatorEmpty(),
                outputs_section,
            }),
            separatorEmpty(),
            separator(),
            separatorEmpty(),
            vbox({
                text("Inputs") | bold | underlined,
                separatorEmpty(),
                inputs_section,
            }),
        }) | border;

        auto analog_section = vbox({
            hbox({
                text("           ") | size(WIDTH, EQUAL, 11),
                text("AO0") | bold | size(WIDTH, EQUAL, 12) | hcenter,
                text("AO1") | bold | size(WIDTH, EQUAL, 12) | hcenter,
                separatorEmpty(),
                text("AI0") | bold | size(WIDTH, EQUAL, 12) | hcenter,
                text("AI1") | bold | size(WIDTH, EQUAL, 12) | hcenter,
            }),
            hbox({
                text(" Readback:") | size(WIDTH, EQUAL, 11),
                ao_rbv0.component()->Render()
                    | rbv_style(ao_rbv0)
                    | size(WIDTH, EQUAL, 12),
                ao_rbv1.component()->Render()
                    | rbv_style(ao_rbv1)
                    | size(WIDTH, EQUAL, 12),
                separatorEmpty(),
                ai0.component()->Render()
                    | rbv_style(ai0)
                    | size(WIDTH, EQUAL, 12),
                ai1.component()->Render()
                    | rbv_style(ai1)
                    | size(WIDTH, EQUAL, 12),
            }),
            hbox({
                text(" Voltage: ") | size(WIDTH, EQUAL, 11),
                ao_voltage0.component()->Render()
                    | edit_style(ao_voltage0)
                    | size(WIDTH, EQUAL, 12),
                ao_voltage1.component()->Render()
                    | edit_style(ao_voltage1)
                    | size(WIDTH, EQUAL, 12),
            }),
            hbox({
                text(" Current: ") | size(WIDTH, EQUAL, 11),
                ao_current0.component()->Render()
                    | edit_style(ao_current0)
                    | size(WIDTH, EQUAL, 12),
                ao_current1.component()->Render()
                    | edit_style(ao_current1)
                    | size(WIDTH, EQUAL, 12),
            }),
        }) | border;

        return vbox({
            connected.value()
                ? text("Connected") | color(Color::Green) | bold
                : text("Disconnected") | color(Color::Red) | bold,
            separatorEmpty(),
            digital_section,
            separatorEmpty(),
            text("Analog I/O") | bold | underlined,
            analog_section,
        }) | size(WIDTH, EQUAL, 62);
    });

    Add(container);
}
