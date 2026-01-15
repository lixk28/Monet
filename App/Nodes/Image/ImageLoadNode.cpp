#include "ImageLoadNode.h"

#include <QtCore/QDir>
#include <QtCore/QEvent>

#include <QtWidgets/QFileDialog>

ImageLoadNode::ImageLoadNode()
    : m_label(new QLabel("Double click to load image"))
{
    m_label->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

    QFont f = m_label->font();
    f.setBold(true);
    f.setItalic(true);

    m_label->setFont(f);

    m_label->setMinimumSize(200, 200);
    m_label->setMaximumSize(500, 300);

    m_label->installEventFilter(this);
}

unsigned int ImageLoadNode::nPorts(PortType portType) const
{
    unsigned int result = 1;

    switch (portType) {
    case PortType::In:
        result = 0;
        break;

    case PortType::Out:
        result = 1;

    default:
        break;
    }

    return result;
}

bool ImageLoadNode::eventFilter(QObject *object, QEvent *event)
{
    if (object == m_label) {
        int w = m_label->width();
        int h = m_label->height();

        if (event->type() == QEvent::MouseButtonPress) {
            QString fileName = QFileDialog::getOpenFileName(nullptr,
                                                            tr("Open Image"),
                                                            QDir::homePath(),
                                                            tr("Image Files (*.png *.jpg *.bmp)"));

            m_pixmap = QPixmap(fileName);

            m_label->setPixmap(m_pixmap.scaled(w, h, Qt::KeepAspectRatio));

            Q_EMIT dataUpdated(0);

            return true;
        } else if (event->type() == QEvent::Resize) {
            if (!m_pixmap.isNull())
                m_label->setPixmap(m_pixmap.scaled(w, h, Qt::KeepAspectRatio));
        }
    }

    return false;
}

NodeDataType ImageLoadNode::dataType(PortType const, PortIndex const) const
{
    return PixmapData().type();
}

std::shared_ptr<NodeData> ImageLoadNode::outData(PortIndex)
{
    return std::make_shared<PixmapData>(m_pixmap);
}
