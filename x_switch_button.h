#ifndef X_SWITCH_BUTTON_H
#define X_SWITCH_BUTTON_H

#include <QWidget>
#include <QTimer>
#include <QColor>

#define ENABLE_LOADING 1

class X_Switch_Button : public QWidget
{
    Q_OBJECT

public:
    explicit X_Switch_Button(QWidget *parent = 0);
    ~X_Switch_Button(){}


private slots:
    void updateValue();

private:
    void drawBackGround(QPainter *painter);
    void drawSlider(QPainter *painter);

protected:
    void resizeEvent(QResizeEvent *ev);
    void paintEvent(QPaintEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
    void statChanged();

private:
    int i_space;                //滑块距离边界距离
    int i_radius;               //圆角角度

    bool b_checked;             //是否选中
    bool b_showText;            //是否显示文字
    bool b_animation;           //是否使用动画
#ifdef ENABLE_LOADING
    bool b_loading;             //是否使用加载动画
    QColor loading_color;
    QPoint loading_point[8];
    int m_inRadius;
    int m_outRadius;
    int m_outRadiuslist[8];
    int m_rel_X_list[8];
    bool m_displayedWhenStopped = true;//加载动画执行标志
    int ani_count;              //动画计时器执行计数，控制loading帧率

    void startLoading();
    void stopLoading();
    void drawLoading(QPainter *painter);
#endif

    QColor bg_color_on;         //打开时候的背景色
    QColor bg_color_off;        //关闭时候的背景色
    QColor slider_color_on;     //打开时候滑块颜色
    QColor slider_color_off;    //关闭时候滑块颜色
    QColor text_color;          //文字颜色

    QString text_str_on;        //打开时候的文字
    QString text_str_off;       //关闭时候的文字

    QTimer  *ani_timer;         //动画定时器
    int     slide_Step;         //动画步长
    int     slider_width;       //滑块宽度
    int     ani_StartX;         //滑块开始X轴坐标
    int     ani_EndX;           //滑块结束X轴坐标

public:
    int space()                 const;
    int radius()                const;
    bool checked()              const;
    bool showText()             const;
    bool animation()            const;
#ifdef ENABLE_LOADING
    bool loading();
#endif

    QColor bgcolor_on()         const;
    QColor bgcolor_off()        const;
    QColor slidercolor_on()      const;
    QColor slidercolor_off()    const;
    QColor textcolor()          const;

    QString textstr_on()        const;
    QString textstr_off()       const;

    int slideStep()             const;
    int aniStartX()             const;
    int aniEndX()               const;


public Q_SLOTS:
    void setSpace(int space);
    void setRadius(int radius);
    void setChecked(bool checked);
    void setShowText(bool show);
    void setAnimation(bool ok);
#ifdef ENABLE_LOADING
    void setLoading(bool enabled);
#endif

    void setBgColorOn(const QColor &color);
    void setBgColorOff(const QColor &color);
    void setSliderColorOn(const QColor &color);
    void setSliderColorOff(const QColor &color);
    void setTextColor(const QColor &color);

    void setTextOn(const QString &text);
    void setTextOff(const QString &text);

//    void setStep(int step);
//    void setStartX(int startX);
//    void setEndX(int endX);


};

#endif // X_SWITCH_BUTTON_H
