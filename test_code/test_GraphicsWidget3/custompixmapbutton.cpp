#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>
#include "custompixmapbutton.h"

CustomPixmapButton::CustomPixmapButton(int id,const QPixmap &normalPixmap, const QPixmap &hoverPixmap, const QPixmap &pressedPixmap)
: m_isPressed(false), m_iconOn(false), m_textOn(false),m_id(id)
{
    m_cnt = 0;
    m_text = "";
    m_icon = QPixmap("");
    m_pixmap = normalPixmap;
    m_normalPixmap = normalPixmap;
    m_hoverPixmap = hoverPixmap;
    m_pressedPixmap = pressedPixmap;
    m_state = STATE::UNCHOOSE;

    setAcceptHoverEvents(true);
}

void CustomPixmapButton::resetPixmap()
{
    update();
}

void CustomPixmapButton::setStyle( Style style )
{
    if ( style == m_style)
    {
        return;
    }
    m_style = style;
    if (IconOnly == style)
    {
        m_iconOn = true;
        m_textOn = false;
    }
    else if (TextOnly == style)
    {
        m_iconOn = false;
        m_textOn = true;
    }
    else
    {
        m_iconOn = true;
        m_textOn = true;
    }
}
void CustomPixmapButton::setText(const QString &string, const QFont &font, const QColor &color)
{
    m_text = string;
    m_textOn = true;
    m_font = font;
    m_color = color;
}
void CustomPixmapButton::setIcon( const QPixmap &icon )
{
    m_icon = icon;
    m_iconOn = true;
}
void CustomPixmapButton::paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(this->m_state == STATE::UNCHOOSE)
    {
       painter->drawPixmap(0 ,0  ,m_normalPixmap );
    }
    else
    {
        painter->drawPixmap(0 ,0 ,m_pressedPixmap);
    }

//    Q_UNUSED(option);
//    Q_UNUSED(widget);
//    const QRect &rect = boundingRect().toRect();
//    setPreferredSize(rect.width(), rect.height());
//    //画button的背景
//    painter->drawPixmap(rect, m_pixmap);
//    if (m_iconOn && !m_icon.isNull())
//    {
//        QRect iconRect(0, 0, m_icon.size().width(), m_icon.size().height());
//        painter->drawPixmap(iconRect, m_icon);
//    }
//    else if (m_textOn && !m_text.isEmpty())
//    {
//        QFontMetrics metrics(m_font);
//        qreal width = metrics.width(m_text);
//        qreal height = metrics.height();
//        QRect textRect(0, 0, width, height);
//        painter->drawText(textRect, Qt::AlignCenter, m_text);
//    }
//    //图标和文本都有
//    if (m_textOn && m_iconOn && !m_icon.isNull() && !m_text.isEmpty())
//    {
//        //文字在图标旁边
//        if(TextBesidesIcon == m_style)
//        {
//            QRect mixRect(0, 0, m_icon.size().width(), rect.height());
//            painter->drawPixmap(mixRect, m_icon);
//            QRect textRect(m_icon.size().width(), 0, rect.width() - m_icon.size().width(), rect.height());
//            painter->drawText(textRect, Qt::AlignCenter, m_text);
//        }
//        //文字在图标下面
//        if (TextUnderIcon == m_style)
//        {
//            QRect mixRect(0, 0, rect.width(), m_icon.size().height());
//            painter->drawPixmap(mixRect, m_icon);
//            QRect textRect(0, m_icon.size().height(), rect.width(), rect.height() - m_icon.size().height());
//            painter->drawText(textRect, Qt::AlignCenter, m_text);
//        }
//    }
}
QRectF CustomPixmapButton::boundingRect()
{
    m_size = m_pixmap.size();
    qreal widthText;
    qreal heightText;
    QSize iconSize;
    qreal totalWidth;
    qreal totalHeight;
    //获取文本信息的宽高
    if (m_textOn)
    {
        QFontMetrics metrics(m_font);
        widthText = metrics.width(m_text);
        heightText = metrics.height();
        //return QRectF(0, 0, widthText, heightText);
    }
    //获取图标的宽高
    if (m_iconOn)
    {
        iconSize = m_icon.size();
    }
    if (2 == m_style)
    {
        totalWidth = widthText + iconSize.width();
        totalHeight = heightText > iconSize.height() ? heightText : iconSize.height();
    }
    else if (3 == m_style)
    {
        totalWidth = widthText > iconSize.width() ? widthText : iconSize.width();
        totalHeight = heightText + iconSize.height();
    }
    else
    {
        totalWidth = widthText + iconSize.width();
        totalHeight = heightText + iconSize.height();
    }
    return QRectF(0, 0, totalWidth, totalHeight);
}
void CustomPixmapButton::setPixmap( State state)
{
    switch (state)
    {
    case NormalState: m_pixmap = m_normalPixmap;
        break;
    case HoverState: m_pixmap = m_hoverPixmap;
        break;
    case PressedState:  m_pixmap = m_pressedPixmap;
        break;
    }
}
void CustomPixmapButton::mousePressEvent( QGraphicsSceneMouseEvent *e )
{
    setStateType(STATE::CHOOSE);

    update();
    emit sig_choose(m_id);

//    if (e->button() == Qt::LeftButton)
//    {
//        m_isPressed = true;
//        setPixmap(PressedState);
//        update();
//    }

}
void CustomPixmapButton::mouseReleaseEvent( QGraphicsSceneMouseEvent *e )
{
    if (e->button() == Qt::LeftButton)
    {
        if (m_isPressed)
            {
                m_cnt++;
                m_isPressed = false;
                setPixmap(NormalState);
                update();
                emit clicked();
            }
    }

}
void CustomPixmapButton::hoverEnterEvent( QGraphicsSceneHoverEvent * )
{
    if (!m_isPressed)
    {
        setPixmap(HoverState);
        update();
    }

}
void CustomPixmapButton::hoverLeaveEvent(QGraphicsSceneHoverEvent *)
{
    if (!m_isPressed)
    {
        setPixmap(NormalState);
        update();
    }

}
QString CustomPixmapButton::getText()
{
    return m_text;
}
