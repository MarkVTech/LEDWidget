#ifndef LEDWIDGET_H
#define LEDWIDGET_H

#include <QWidget>

#include <QtDesigner/QtDesigner>
#include <QWidget>

class QTimer;

//class QDESIGNER_WIDGET_EXPORT LEDWidget : public QWidget
class LEDWidget : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(double diameter READ diameter WRITE setDiameter) // mm
    Q_PROPERTY(QColor color READ color WRITE setColor)
    Q_PROPERTY(Qt::Alignment alignment READ alignment WRITE setAlignment)
    Q_PROPERTY(bool state READ state WRITE setState)
    Q_PROPERTY(bool flashing READ isFlashing WRITE setFlashing)
    Q_PROPERTY(int flashRate READ flashRate WRITE setFlashRate)

public:
    explicit LEDWidget(QWidget *parent=nullptr);

    double diameter() const;
    void setDiameter(double diameter);

    QColor color() const;
    void setColor(const QColor& color);

    Qt::Alignment alignment() const;
    void setAlignment(Qt::Alignment alignment);

    bool state() const;
    bool isFlashing() const;
    int flashRate() const;

public slots:
    void setState(bool state);
    void toggleState();
    void setFlashing(bool flashing);
    void setFlashRate(int rate);
    void startFlashing();
    void stopFlashing();

public:
    int heightForWidth(int width) const;
    QSize sizeHint() const;
    QSize minimumSizeHint() const;

protected:
    void paintEvent(QPaintEvent* event);

private:
    double mDiameter=10;
    QColor mColor=QColor("red");
    Qt::Alignment mAlignment=Qt::AlignHCenter | Qt::AlignVCenter;
    bool mState=false;
    bool mFlashing=false;
    int mFlashRate=100;
    //int mDiamX, mDiamY;

    QTimer *mTimer;
};

#endif
