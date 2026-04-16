#include "common.hpp"
#include "control.hpp"

using namespace pvtui;
using namespace ftxui;

ControlAxis::ControlAxis(pvtui::App& app, const std::string& prefix, const std::string& axis_prefix, const std::string& rb_pvname) :
    val(app, prefix + "Control:" + axis_prefix + "Cmd.VAL", PVPutType::Double),
    twv(app, prefix + "Control:" + axis_prefix + "TweakVal.VAL", PVPutType::Double),
    twf(app, prefix + "Control:" + axis_prefix + "TweakFwd.PROC", "  ", ButtonOption::Animated()),
    twr(app, prefix + "Control:" + axis_prefix + "TweakRev.PROC", "  ", ButtonOption::Animated()),
    egu(app, prefix + "Control:" + axis_prefix + "Cmd.EGU"),
    rbv(app, prefix + rb_pvname + ".VAL")
{

    auto container = Container::Vertical({
        val.component(),
        twr.component(),
        twv.component(),
        twf.component(),
    });
    container |= Renderer([this, axis_prefix](Element){
        return vbox({
            text(axis_prefix) | bold | hcenter,
            separator(),
            rbv.component()->Render()
                | rbv_style(rbv)
                | size(WIDTH, EQUAL, 8) | hcenter,
            hbox({
                separatorEmpty() | size(WIDTH, EQUAL, 4),
                val.component()->Render()
                    | edit_style(val),
                text(" " + egu.value()) | size(WIDTH, EQUAL, 4),
            }),
            hbox({
                twr.component()->Render(),
                vbox({
                    separatorEmpty(),
                    twv.component()->Render()
                        | edit_style(twv)
                        | size(WIDTH, EQUAL, 8),
                    separatorEmpty(),
                }),
                twf.component()->Render(),
            }) | hcenter
        }) | border;
    });

    Add(container);
}

Control::Control(pvtui::App& app, const std::string& prefix) : prefix(prefix),
    axis1(Make<ControlAxis>(app, prefix, "J1", "Receive:Joint1")),
    axis2(Make<ControlAxis>(app, prefix, "J2", "Receive:Joint2")),
    axis3(Make<ControlAxis>(app, prefix, "J3", "Receive:Joint3")),
    axis4(Make<ControlAxis>(app, prefix, "J4", "Receive:Joint4")),
    axis5(Make<ControlAxis>(app, prefix, "J5", "Receive:Joint5")),
    axis6(Make<ControlAxis>(app, prefix, "J6", "Receive:Joint6")),
    axis7(Make<ControlAxis>(app, prefix, "PoseX", "Receive:PoseX")),
    axis8(Make<ControlAxis>(app, prefix, "PoseY", "Receive:PoseY")),
    axis9(Make<ControlAxis>(app, prefix, "PoseZ", "Receive:PoseZ")),
    axis10(Make<ControlAxis>(app, prefix, "PoseRoll", "Receive:PoseRoll")),
    axis11(Make<ControlAxis>(app, prefix, "PosePitch", "Receive:PosePitch")),
    axis12(Make<ControlAxis>(app, prefix, "PoseYaw", "Receive:PoseYaw")),
    auto_movej(app, prefix + "Control:AutoMoveJ.VAL", ChoiceStyle::Horizontal),
    auto_movel(app, prefix + "Control:AutoMoveL.VAL", ChoiceStyle::Horizontal),
    stopj(app, prefix + "Control:stopJ.PROC", " STOP "),
    stopl(app, prefix + "Control:stopL.PROC", " STOP "),
    movej(app, prefix + "Control:moveJ.PROC", " Move "),
    movel(app, prefix + "Control:moveL.PROC", " Move "),
    disconnect(app, prefix + "Control:Disconnect.PROC",                      "  Disconnect   "),
    reconnect(app, prefix + "Control:Reconnect.PROC",                        "   Connect     "),
    stop_ctrl_script(app, prefix + "Control:StopControlScript.PROC",         "  Stop Script  "),
    reupload_ctrl_script(app, prefix + "Control:ReuploadControlScript.PROC", "Reupload Script"),
    stop(app, prefix + "Control:Stop.PROC", " STOP "),
    tcp_offset_x(app, prefix + "Control:TCPOffset_X.VAL", PVPutType::Double),
    tcp_offset_y(app, prefix + "Control:TCPOffset_Y.VAL", PVPutType::Double),
    tcp_offset_z(app, prefix + "Control:TCPOffset_Z.VAL", PVPutType::Double),
    tcp_offset_roll(app, prefix + "Control:TCPOffset_Roll.VAL", PVPutType::Double),
    tcp_offset_pitch(app, prefix + "Control:TCPOffset_Pitch.VAL", PVPutType::Double),
    tcp_offset_yaw(app, prefix + "Control:TCPOffset_Yaw.VAL", PVPutType::Double),
    teach(app, prefix + "Control:TeachMode.VAL", ChoiceStyle::Horizontal),
    connected(app, prefix + "Control:Connected.RVAL"),
    moving(app, prefix + "Control:Moving.VAL"),
    speed_slider(app, prefix + "IO:SpeedSlider.VAL", {0.0, 1.0, 0.05}, Color::RGB(179, 194, 227), Color::GrayDark)
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
                stopj.component()->Render() | EPICSColor::custom(stopl, bgcolor(Color::Red) | color(Color::Yellow)),
                separatorEmpty(),
                movej.component()->Render() | edit_style(movel)
            }),
            separatorEmpty(),
        });
    });

    auto joints_row = Container::Horizontal({
        axis1,axis2,axis3,axis4,axis5,axis6,
    }) | Renderer([](Element inner){
            return vbox({
                inner,
                separatorEmpty(),
                separatorEmpty(),
            });
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
                stopl.component()->Render() | EPICSColor::custom(stopl, bgcolor(Color::Red) | color(Color::Yellow)),
                separatorEmpty(),
                movel.component()->Render() | edit_style(movel)
            }),
            separatorEmpty(),
        });
    });

    auto pose_row = Container::Horizontal({
        axis7,axis8,axis9,axis10,axis11,axis12,
    });


    auto make_offset_entry = [](WidgetBase& w, const std::string& label) {
        return vbox({
            text(label),
            w.component()->Render()
                | edit_style(w)
                | size(WIDTH, EQUAL, 10)
        });
    };

    auto tcp_offset_container = Container::Horizontal({
        tcp_offset_x.component(),
        tcp_offset_y.component(),
        tcp_offset_z.component(),
        tcp_offset_roll.component(),
        tcp_offset_pitch.component(),
        tcp_offset_yaw.component(),
    }) | Renderer([&](Element){
        return hbox({
            vbox({
                separatorEmpty(),
                text("TCP Offset: "),
            }),
            make_offset_entry(tcp_offset_x, "X"),
            separatorEmpty(),
            make_offset_entry(tcp_offset_y, "Y"),
            separatorEmpty(),
            make_offset_entry(tcp_offset_z, "Z"),
            separatorEmpty(),
            make_offset_entry(tcp_offset_roll, "Roll"),
            separatorEmpty(),
            make_offset_entry(tcp_offset_pitch, "Pitch"),
            separatorEmpty(),
            make_offset_entry(tcp_offset_yaw, "Yaw"),
            vbox({
                separatorEmpty(),
                text(" mm, rad"),
            }),
        });
    });

    auto top = Container::Vertical({
        reconnect.component(),
        disconnect.component(),
        stop_ctrl_script.component(),
        reupload_ctrl_script.component(),
        teach.component(),
        tcp_offset_container,
        speed_slider.component(),
        stop.component()
    }) | Renderer([this, tcp_offset_container](Element){
        return vbox({
            connected.value()
                ? text("Connected") | EPICSColor::custom(connected, color(Color::Green)) | bold
                : text("Disconnected") | EPICSColor::custom(connected, color(Color::Red)) | bold,
            hbox({
                reconnect.component()->Render() | edit_style(reconnect) | italic,
                separatorEmpty(),
                disconnect.component()->Render() | edit_style(disconnect) | italic,
            }),
            separatorEmpty(),
            hbox({
                stop_ctrl_script.component()->Render() | edit_style(stop_ctrl_script) | italic,
                separatorEmpty(),
                reupload_ctrl_script.component()->Render() | edit_style(reupload_ctrl_script) | italic,
            }),
            separatorEmpty(),
            hbox({
                text("Teach Mode: "),
                teach.component()->Render()
            }),
            separatorEmpty(),
            tcp_offset_container->Render(),
            separatorEmpty(),
            hbox({
                text("Speed: "),
                speed_slider.component()->Render(),
                separatorEmpty(),
                stop.component()->Render() | bgcolor(Color::Red) | color(Color::Yellow),
                filler(),
                moving.value().index
                    ? text("Moving") | EPICSColor::custom(connected, color(Color::Green)) | bold | italic
                    : emptyElement(),
                filler(),
            }),
            separatorEmpty()
        });
        // | size(WIDTH, EQUAL, 120);
    });

    auto container = Container::Vertical({
        top | Renderer([](Element inner) { return vbox({inner, separatorEmpty()}); }),
        Container::Vertical({
            joints_top,
            joints_row
        }),

        Container::Vertical({
            pose_top,
            pose_row
        }),
    });
    // | size(WIDTH, EQUAL, 120);

    Add(container);
}
