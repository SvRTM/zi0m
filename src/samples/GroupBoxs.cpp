#include "GroupBoxs.h"
#include "gui/widgets/GroupBox.h"
#include "gui/widgets/Button.h"
#include "gui/widgets/Label.h"

GroupBoxs::GroupBoxs(Point pos, Size size, Widget *parent)
    : Widget(pos, size, parent)
{
#ifdef RGB888
    setBackground({ 0x00DEC2B0U });
#elif  RGB565
    setBackground({ 0xDE16U });
#endif
    setupUi();
}

void GroupBoxs::setupUi()
{
    u_color bg = {COLOR_SNOW};

    GroupBox *gr = new GroupBox({5, 5}, {uint16_t(size().width - 10), 20}, this);
    gr->setBackground(bg);
    addWidget(gr);
    smplWidgets.push_back(gr);
    gr = new GroupBox({5, 30}, {60, 50}, this);
    gr->setText(u"Left GroupBox");
    addWidget(gr);
    smplWidgets.push_back(gr);
    gr = new GroupBox({75, 30}, {60, 50}, this);
    gr->setAlignment(Alignment::HCenter);
    gr->setText(u"Center GroupBox");
    addWidget(gr);
    smplWidgets.push_back(gr);
    gr = new GroupBox({145, 30}, {60, 50}, this);
    gr->setAlignment(Alignment::Right);
    gr->setText(u"GroupBox Right");
    addWidget(gr);
    smplWidgets.push_back(gr);
    gr = new GroupBox({220, 30}, {80, 20}, this);
    gr->setAlignment(Alignment::Right);
    gr->setText(u"GroupBox");
    addWidget(gr);
    smplWidgets.push_back(gr);
    gr = new GroupBox({220, 55}, {80, 20}, this);
    gr->setAlignment(Alignment::Left);
    gr->setText(u"GroupBox");
    addWidget(gr);
    smplWidgets.push_back(gr);
    gr = new GroupBox({220, 80}, {80, 20}, this);
    gr->setAlignment(Alignment::HCenter);
    gr->setText(u"ⓧⓧⓧⓧⓧШⓧⓧⓧⓧ");
    addWidget(gr);
    smplWidgets.push_back(gr);
    gr = new GroupBox({5, 85}, {210, 60}, this);
    gr->setAlignment(Alignment::HCenter);
    gr->setText(u"GroupBox");
    Button *bt = new Button({0, 0}, {50, 25}, gr);
    bt->setText(u"Button");
    gr->addWidget(bt);
    gr->setEnabled(false);
    addWidget(gr);
    smplWidgets.push_back(gr);
    gr = new GroupBox({220, 105}, {80, 80}, this);
    gr->setAlignment(Alignment::Center);
    gr->setText(u"X");
    gr->setCheckable(true);
    addWidget(gr);
    smplWidgets.push_back(gr);
    gr = new GroupBox({5, 145}, {60, 50}, this);
    gr->setText(u"ⓧⓧⓧ");
    gr->setCheckable(true);
    gr->setEnabled(false);
    addWidget(gr);
    smplWidgets.push_back(gr);
    gr = new GroupBox({75, 145}, {60, 50}, this);
    gr->setAlignment(Alignment::HCenter);
    //gr->setText(u"Center GroupBox");
    gr->setText(u"55");
    gr->setCheckable(true);
    gr->setChecked(true);
    bt = new Button({0, 0}, {50, 25}, gr);
    bt->setText(u"Button");
    gr->addWidget(bt);
    addWidget(gr);
    smplWidgets.push_back(gr);
    gr = new GroupBox({145, 145}, {60, 50}, this);
    gr->setAlignment(Alignment::Right);
    gr->setText(u"ⓧⓧⓧⓧⓧ");
    gr->setBackground(bg);
    gr->setCheckable(true);
    addWidget(gr);
    smplWidgets.push_back(gr);
}

void GroupBoxs::setFontWidgtes(std::pair<const IFont *, std::u16string> data)
{
    const IFont &font = *data.first;
    for (AbstractTextWidget *const w : smplWidgets)
        w->setFont(font);
    refresh();
}

void GroupBoxs::event(const EventType type, const Point &pos)
{
    this->type = type;
}
void GroupBoxs::paint(MonitorDevice *const pMonitorDevice)
{
    pMonitorDevice->fillRect(screen(), background());
}

