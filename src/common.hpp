#pragma once
#include <ftxui/component/component.hpp>
#include <pvtui/pvtui.hpp>

inline ftxui::Decorator rbv_style(pvtui::WidgetBase& w) {
    return pvtui::EPICSColor::custom(w, color(ftxui::Color::RGB(175, 127, 212)));
}

inline ftxui::Decorator edit_style(pvtui::WidgetBase& w) {
    return pvtui::EPICSColor::custom(w, color(ftxui::Color::Black) | bgcolor(ftxui::Color::RGB(179, 194, 227)));
}

inline ftxui::Element labelled_rbv(pvtui::WidgetBase& w, const std::string& label = "") {
    return ftxui::hbox({
        label.length() ? ftxui::text(label) : ftxui::emptyElement(),
        w.component()->Render() | rbv_style(w)
    });
}
