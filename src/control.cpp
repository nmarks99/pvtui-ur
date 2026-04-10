#include "control.hpp"

using namespace pvtui;
using namespace ftxui;

ControlAxis::ControlAxis(pvtui::App& app, const std::string& prefix, const std::string& axis_prefix, const std::string& rb_pvname) :
    val(app, prefix + "Control:" + axis_prefix + "Cmd.VAL", PVPutType::Double),
    twv(app, prefix + "Control:" + axis_prefix + "TweakVal.VAL", PVPutType::Double),
    twf(app, prefix + "Control:" + axis_prefix + "TweakFwd.PROC", " > "),
    twr(app, prefix + "Control:" + axis_prefix + "TweakRev.PROC", " < "),
    rbv(app, prefix + rb_pvname) {

    auto container = Container::Vertical({
        val.component(),
        twr.component(),
        twv.component(),
        twf.component(),
    });
    container |= Renderer([this,axis_prefix](Element){
        return vbox({
            text(axis_prefix) | bold | hcenter,
            separator(),
            rbv.component()->Render()
                | color(Color::Blue)
                | size(WIDTH, EQUAL, 8) | hcenter,
            val.component()->Render()
                | EPICSColor::custom(val, bgcolor(Color::GrayDark))
                | size(WIDTH, EQUAL, 8) | hcenter,
            hbox({
                twr.component()->Render(),
                twv.component()->Render()
                    | EPICSColor::custom(twv, bgcolor(Color::GrayDark))
                    | size(WIDTH, EQUAL, 8),
                twf.component()->Render(),
            }) | hcenter
        }) | border;
    });

    Add(container);
}

Control::Control(pvtui::App& app, const std::string& prefix) : prefix(prefix),
    axis1(Make<ControlAxis>(app, prefix, "J1", "Receive:Joint1.VAL")),
    axis2(Make<ControlAxis>(app, prefix, "J2", "Receive:Joint2.VAL")),
    axis3(Make<ControlAxis>(app, prefix, "J3", "Receive:Joint3.VAL")),
    axis4(Make<ControlAxis>(app, prefix, "J4", "Receive:Joint4.VAL")),
    axis5(Make<ControlAxis>(app, prefix, "J5", "Receive:Joint5.VAL")),
    axis6(Make<ControlAxis>(app, prefix, "J6", "Receive:Joint6.VAL")),
    axis7(Make<ControlAxis>(app, prefix, "PoseX", "Receive:PoseX.VAL")),
    axis8(Make<ControlAxis>(app, prefix, "PoseY", "Receive:PoseY.VAL")),
    axis9(Make<ControlAxis>(app, prefix, "PoseZ", "Receive:PoseZ.VAL")),
    axis10(Make<ControlAxis>(app, prefix, "PoseRoll", "Receive:PoseRoll.VAL")),
    axis11(Make<ControlAxis>(app, prefix, "PosePitch", "Receive:PosePitch.VAL")),
    axis12(Make<ControlAxis>(app, prefix, "PoseYaw", "Receive:PoseYaw.VAL")),
    auto_movej(app, prefix + "Control:AutoMoveJ.VAL", ChoiceStyle::Horizontal),
    auto_movel(app, prefix + "Control:AutoMoveL.VAL", ChoiceStyle::Horizontal),
    stopj(app, prefix + "Control:StopJ.PROC", " STOP "),
    stopl(app, prefix + "Control:StopL.PROC", " STOP "),
    movej(app, prefix + "Control:moveJ.PROC", " Move "),
    movel(app, prefix + "Control:moveL.PROC", " Move ")
{
    auto joints_top = Container::Horizontal({
        auto_movej.component(),
        stopj.component(),
        movej.component()
    }) | Renderer([this](Element){
        return vbox({
            text("Joint Move") | bold | underlined | size(WIDTH, EQUAL, 10),
            separatorEmpty(),
            hbox({
                text("Go: "),
                auto_movej.component()->Render(),
                separatorEmpty(),
                separatorEmpty(),
                separatorEmpty(),
                stopj.component()->Render() | bgcolor(Color::Red) | color(Color::Yellow),
                separatorEmpty(),
                movej.component()->Render() | bgcolor(Color::SteelBlue) | color(Color::Black)
            }),
            separatorEmpty(),
        });
    });

    auto joints_row = Container::Horizontal({
        axis1,axis2,axis3,axis4,axis5,axis6,
    });

    auto pose_top = Container::Horizontal({
        auto_movel.component(),
        stopl.component(),
        movel.component()
    }) | Renderer([this](Element){
        return vbox({
            text("Cartesian Move") | bold | underlined | size(WIDTH, EQUAL, 14),
            separatorEmpty(),
            hbox({
                text("Go: "),
                auto_movel.component()->Render(),
                separatorEmpty(),
                separatorEmpty(),
                separatorEmpty(),
                stopl.component()->Render() | bgcolor(Color::Red) | color(Color::Yellow),
                separatorEmpty(),
                movel.component()->Render() | bgcolor(Color::SteelBlue) | color(Color::Black)
            }),
            separatorEmpty(),
        });
    });

    auto pose_row = Container::Horizontal({
        axis7,axis8,axis9,axis10,axis11,axis12,
    });

    auto container = Container::Vertical({
        Container::Vertical({
            joints_top,
            joints_row
        }) | borderHeavy,

        Container::Vertical({
            pose_top,
            pose_row
        }) | borderHeavy,
    }) | size(WIDTH, EQUAL, 120);

    Add(container);
}
