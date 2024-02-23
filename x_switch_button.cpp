
#pragma execution_character_set("utf-8")
#include "x_switch_button.h"
#include <QPainter>

X_Switch_Button::X_Switch_Button(QWidget *parent) : QWidget(parent)
{
    i_space = 2;
    i_radius = 5;
    b_checked = false;
    b_showText = true;
    b_animation = true;

    bg_color_on = QColor(0, 180, 255);
    bg_color_off = QColor(100, 100, 100);

    slider_color_on= QColor(255, 255, 255);
    slider_color_off = QColor(255, 255, 255);

    text_color = QColor(255, 255, 255);

    text_str_on = "开启";
    text_str_off = "关闭";

    slide_Step = 0;
    ani_StartX = 0;
    ani_EndX = 0;


    ani_timer = new QTimer(this);
    ani_timer->setInterval(30);
    connect(ani_timer, SIGNAL(timeout()), this, SLOT(updateValue()));

#ifdef ENABLE_LOADING
    b_loading = true;
    loading_color = bg_color_off;
    ani_count = 0;

    m_outRadiuslist[0] = 4;
    m_outRadiuslist[1] = 3;
    m_outRadiuslist[2] = 3;
    m_outRadiuslist[3] = 2;
    m_outRadiuslist[4] = 2;
    m_outRadiuslist[5] = 1;
    m_outRadiuslist[6] = 1;
    m_outRadiuslist[7] = 1;
#endif
}

void X_Switch_Button::drawBackGround(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);

    QColor bgColor = b_checked ? bg_color_on : bg_color_off;
    if ( ! isEnabled()) {
        bgColor.setAlpha(150);
    }

    painter->setBrush(bgColor);

    QRect rect(0, 0, width(), height());
    int side = qMin(width(), height());

    //左侧半圆
    QPainterPath path1;
    path1.addEllipse(rect.x(), rect.y(), side, side);

    //右侧半圆
    QPainterPath path2;
    path2.addEllipse(rect.width() - side, rect.y(), side, side);

    //中间的矩形
    QPainterPath path3;
    path3.addRect(rect.x() + side / 2, rect.y(), rect.width() - side, height());

    QPainterPath path = path1 + path2 + path3;
    painter->drawPath(path);

    //绘制文本
    //滑块半径
    int sliderWidth = qMin(height(), width()) - i_space * 2 - 5;
    if (b_checked){
        QRect textRect(0, 0, width() - sliderWidth, height());
        painter->setPen(QPen(text_color));
        if(showText()) painter->drawText(textRect, Qt::AlignCenter, text_str_on);
    } else {
        QRect textRect(sliderWidth, 0, width() - sliderWidth, height());
        painter->setPen(QPen(text_color));
        if(showText()) painter->drawText(textRect, Qt::AlignCenter, text_str_off);
    }

    painter->restore();
}

void X_Switch_Button::drawSlider(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);

    QColor color = b_checked ? slider_color_on : slider_color_off;

    painter->setBrush(QBrush(color));

    slider_width = qMin(width(), height()) - i_space * 2;
    QRect rect(i_space + ani_StartX, i_space, slider_width, slider_width);
    painter->drawEllipse(rect);

    painter->restore();
}

#ifdef ENABLE_LOADING
void X_Switch_Button::startLoading()
{
    //设为不可点击
    this->setDisabled(true);
    m_displayedWhenStopped = false;
    ani_count = 0;
    for (int var = 0; var < 8; var++) {
        loading_point[var].setX(ani_StartX + m_rel_X_list[var]);
    }
    ani_timer->start();
}

void X_Switch_Button::stopLoading()
{
    //设为可点击
    this->setDisabled(false);
    ani_timer->stop();
    m_displayedWhenStopped = true;
    update();
}

void X_Switch_Button::drawLoading(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);

    for (int var = 0; var < 8; ++var) {
        QPen pen(loading_color);//定义画笔
        pen.setWidth(1);//
        pen.setStyle(Qt::CustomDashLine);
        painter->setPen(pen);
        painter->setBrush(QBrush(loading_color, Qt::SolidPattern));
        painter->drawEllipse(loading_point[var],m_outRadiuslist[var],m_outRadiuslist[var]);
    }

    painter->restore();
}
#endif

void X_Switch_Button::resizeEvent(QResizeEvent *ev)
{
    slider_width = qMin(width(), height()) - i_space * 2;
#ifdef ENABLE_LOADING
    m_outRadius = slider_width/2 + i_space;
    m_inRadius = slider_width/2 - i_space*2;

    int x_offset = slider_width/2 + i_space;
    m_rel_X_list[0] = x_offset + m_inRadius;
    m_rel_X_list[1] = x_offset + m_inRadius*3/4;
    m_rel_X_list[2] = x_offset;
    m_rel_X_list[3] = x_offset - m_inRadius*3/4;
    m_rel_X_list[4] = x_offset - m_inRadius;
    m_rel_X_list[5] = x_offset - m_inRadius*3/4;
    m_rel_X_list[6] = x_offset;
    m_rel_X_list[7] = x_offset + m_inRadius*3/4;


    loading_point[0] = QPoint(ani_StartX + m_rel_X_list[0], m_outRadius);//左
    loading_point[1] = QPoint(ani_StartX + m_rel_X_list[1], m_outRadius-m_inRadius*3/4);//左上
    loading_point[2] = QPoint(ani_StartX + m_rel_X_list[2], m_outRadius-m_inRadius);//上
    loading_point[3] = QPoint(ani_StartX + m_rel_X_list[3], m_outRadius-m_inRadius*3/4);//右上
    loading_point[4] = QPoint(ani_StartX + m_rel_X_list[4], m_outRadius);//右
    loading_point[5] = QPoint(ani_StartX + m_rel_X_list[5], m_outRadius+m_inRadius*3/4);//右下
    loading_point[6] = QPoint(ani_StartX + m_rel_X_list[6], m_outRadius+m_inRadius);//下
    loading_point[7] = QPoint(ani_StartX + m_rel_X_list[7], m_outRadius+m_inRadius*3/4);//左下
#endif
}

void X_Switch_Button::paintEvent(QPaintEvent *ev)
{
    //启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制背景
    drawBackGround(&painter);

    //绘制滑块
    drawSlider(&painter);

#ifdef ENABLE_LOADING
    //绘制加载动画
    if(false == m_displayedWhenStopped)
        drawLoading(&painter);
#endif

}

void X_Switch_Button::statChanged()
{
    //计算步长
    slide_Step = width() / 10;

    //计算滑块X轴终点坐标
    if (b_checked) {
        ani_EndX = width() - height();
    } else {
        ani_EndX = 0;
    }

    //判断是否使用动画
    if (b_animation) {
        ani_timer->start();
    } else{
        ani_StartX = ani_EndX;
        update();
    }
}

void X_Switch_Button::mousePressEvent(QMouseEvent *ev)
{
    Q_UNUSED(ev)
#ifdef ENABLE_LOADING
    if(b_loading)
        startLoading();
    else
#endif
    {
        b_checked = !b_checked;
        statChanged();
    }

}

void X_Switch_Button::updateValue()
{
#ifdef ENABLE_LOADING
    if(false == m_displayedWhenStopped){
        if(0 != ++ani_count%3) return;
        ani_count = 0;
        int tmpInt = m_outRadiuslist[0];
        for (int var = 0; var < 7; var++) {
            m_outRadiuslist[var] = m_outRadiuslist[var+1];
        }
        m_outRadiuslist[7] = tmpInt;
    }else
#endif
    {
        if (b_checked) {
            if (ani_StartX < ani_EndX) {
                ani_StartX += slide_Step;
            } else {
                ani_StartX = ani_EndX;
                ani_timer->stop();
            }
        } else {
            if (ani_StartX > ani_EndX) {
                ani_StartX -= slide_Step;
            } else {
                ani_StartX = ani_EndX;
                ani_timer->stop();
            }
        }
    }

    update();
}

int X_Switch_Button::space() const
{
    return i_space;
}

int X_Switch_Button::radius() const
{
    return i_radius;
}

bool X_Switch_Button::checked() const
{
    return b_checked;
}

bool X_Switch_Button::showText() const
{
    return b_showText;
}

bool X_Switch_Button::animation() const
{
    return b_animation;
}

QColor X_Switch_Button::bgcolor_on() const
{
    return bg_color_on;
}

QColor X_Switch_Button::bgcolor_off() const
{
    return bg_color_off;
}

QColor X_Switch_Button::slidercolor_on() const
{
    return slider_color_on;
}

QColor X_Switch_Button::slidercolor_off() const
{
    return slider_color_off;
}

QColor X_Switch_Button::textcolor() const
{
    return text_color;
}

QString X_Switch_Button::textstr_on() const
{
    return text_str_on;
}

QString X_Switch_Button::textstr_off() const
{
    return text_str_off;
}

int X_Switch_Button::slideStep() const
{
    return slide_Step;
}

int X_Switch_Button::aniStartX() const
{
    return ani_StartX;
}

int X_Switch_Button::aniEndX() const
{
    return ani_EndX;
}

void X_Switch_Button::setSpace(int space)
{
    if (i_space != space) {
        i_space = space;
        update();
    }
}

void X_Switch_Button::setRadius(int radius)
{
    if (i_radius != radius) {
        i_radius = radius;
        update();
    }
}

void X_Switch_Button::setChecked(bool checked)
{
    if (b_checked != checked) {
        b_checked = checked;
        update();
    }

#ifdef ENABLE_LOADING
    stopLoading();
#endif
    statChanged();
}

#ifdef ENABLE_LOADING
bool X_Switch_Button::loading(){
    return b_loading;
}

void X_Switch_Button::setLoading(bool enabled){
    b_loading = enabled;
}
#endif

void X_Switch_Button::setShowText(bool show)
{
    if (b_showText != show) {
        b_showText = show;
        update();
    }
}

void X_Switch_Button::setAnimation(bool ok)
{
    if (b_animation != ok) {
        b_animation = ok;
        update();
    }
}

void X_Switch_Button::setBgColorOn(const QColor &color)
{
    if (bg_color_on != color) {
        bg_color_on = color;
        update();
    }
}

void X_Switch_Button::setBgColorOff(const QColor &color)
{
    if (bg_color_off != color) {
        bg_color_off = color;
        update();
    }
}

void X_Switch_Button::setSliderColorOn(const QColor &color)
{
    if (slider_color_on != color) {
        slider_color_on = color;
        update();
    }
}

void X_Switch_Button::setSliderColorOff(const QColor &color)
{
    if (slider_color_off != color) {
        slider_color_off = color;
        update();
    }
}

void X_Switch_Button::setTextColor(const QColor &color)
{
    if (text_color != color) {
        text_color = color;
        update();
    }
}

void X_Switch_Button::setTextOn(const QString &text)
{
    if (text_str_on != text) {
        text_str_on = text;
        update();
    }
}

void X_Switch_Button::setTextOff(const QString &text)
{
    if (text_str_off != text) {
        text_str_off = text;
        update();
    }
}
