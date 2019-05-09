#include <QtGlobal>

#include "LEDWidget.h"

LEDWidget::LEDWidget(QWidget *parent) :
    QWidget(parent),
    mTimer(new QTimer)
{
    connect(mTimer, SIGNAL(timeout()), this, SLOT(toggleState()));
}

double LEDWidget::diameter() const
{
    return mDiameter;
}

void LEDWidget::setDiameter(double diameter)
{
    if ( qFuzzyCompare(mDiameter, diameter) )
        return;

    mDiameter = diameter;

    update();
}

QColor LEDWidget::color() const
{
    return mColor;
}

void LEDWidget::setColor(const QColor &color)
{
    if ( mColor == color )
        return;

    mColor = color;

    update();
}

Qt::Alignment LEDWidget::alignment() const
{
    return mAlignment;
}

void LEDWidget::setAlignment(Qt::Alignment alignment)
{
    if ( mAlignment == alignment )
        return;

    mAlignment = alignment;

    update();
}

bool LEDWidget::
state() const
{
    return mState;
}

bool LEDWidget::isFlashing() const
{
    return mFlashing;
}

int LEDWidget::flashRate() const
{
    return mFlashRate;
}

void LEDWidget::
setState(bool state)
{
    if ( mState == state )
        return;

    mState = state;

    update();
}

void LEDWidget::toggleState()
{
    //mFlashing = !mFlashing;
    mState = !mState;

    update();
}

void LEDWidget::setFlashing(bool flashing)
{
    if ( mFlashing == flashing )
        return;

    mFlashing = flashing;
    update();
}

void LEDWidget::setFlashRate(int rate)
{
    if ( mFlashRate == rate )
        return;

    mFlashRate = rate;
    update();
}

void LEDWidget::startFlashing()
{
    if ( mFlashing )
        return;

    mFlashing = true;
    update();
}

void LEDWidget::stopFlashing()
{
    if ( !mFlashing )
        return;

    mFlashing = false;
    update();
}

int LEDWidget::heightForWidth(int width) const
{
    return width;
}

QSize LEDWidget::sizeHint() const
{
    return QSize(mDiameter+1, mDiameter+1);
}

QSize LEDWidget::minimumSizeHint() const
{
    return QSize(mDiameter+1, mDiameter+1);
}

void LEDWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter p(this);

    QRect geo = geometry();
    int width = geo.width();
    int height = geo.height();

    int x=0, y=0;
    if ( mAlignment & Qt::AlignLeft )
        x = 0;
    else if ( mAlignment & Qt::AlignRight )
        x = width-mDiameter;
    else if ( mAlignment & Qt::AlignHCenter )
        x = (width-mDiameter)/2;
    else if ( mAlignment & Qt::AlignJustify )
        x = 0;

    if ( mAlignment & Qt::AlignTop )
        y = 0;
    else if ( mAlignment & Qt::AlignBottom )
        y = height-mDiameter;
    else if ( mAlignment & Qt::AlignVCenter )
        y = (height-mDiameter)/2;

    QRadialGradient g(x+mDiameter/2, y+mDiameter/2, mDiameter*0.4,
        mDiameter*0.4, mDiameter*0.4);

    g.setColorAt(0, Qt::white);
    if ( mState )
        g.setColorAt(1, mColor);
    else
        g.setColorAt(1, Qt::black);
    QBrush brush(g);

    if ( mState )
        p.setPen(mColor);
    else {
        p.setPen(Qt::black);
    }
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setBrush(brush);
    p.drawEllipse(x, y, mDiameter-1, mDiameter-1);

    if ( mFlashRate > 0 && mFlashing )
        mTimer->start(mFlashRate);
    else
        mTimer->stop();
}
