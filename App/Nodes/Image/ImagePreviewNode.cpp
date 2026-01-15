#include "ImagePreviewNode.h"
#include "PixmapData.h"

#include <QtNodes/NodeDelegateModelRegistry>

#include <QtCore/QDir>
#include <QtCore/QEvent>
#include <QtWidgets/QFileDialog>

ImagePreviewNode::ImagePreviewNode()
    : m_label(new QLabel("Image will appear here"))
{
    m_label->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

    QFont f = m_label->font();
    f.setBold(true);
    f.setItalic(true);

    m_label->setFont(f);

    m_label->setMinimumSize(200, 200);

    m_label->installEventFilter(this);
}

unsigned int ImagePreviewNode::nPorts(PortType portType) const
{
    unsigned int result = 1;

    switch (portType) {
    case PortType::In:
        result = 1;
        break;

    case PortType::Out:
        result = 1;

    default:
        break;
    }

    return result;
}

bool ImagePreviewNode::eventFilter(QObject *object, QEvent *event)
{
    if (object == m_label) {
        int w = m_label->width();
        int h = m_label->height();

        if (event->type() == QEvent::Resize) {
            auto d = std::dynamic_pointer_cast<PixmapData>(m_nodeData);
            if (d) {
                m_label->setPixmap(d->pixmap().scaled(w, h, Qt::KeepAspectRatio));
            }
        }
    }

    return false;
}

NodeDataType ImagePreviewNode::dataType(PortType const, PortIndex const) const
{
    return PixmapData().type();
}

std::shared_ptr<NodeData> ImagePreviewNode::outData(PortIndex)
{
    return m_nodeData;
}

void ImagePreviewNode::setInData(std::shared_ptr<NodeData> nodeData, PortIndex const)
{
    m_nodeData = nodeData;

    if (m_nodeData) {
        auto d = std::dynamic_pointer_cast<PixmapData>(m_nodeData);

        int w = m_label->width();
        int h = m_label->height();

        m_label->setPixmap(d->pixmap().scaled(w, h, Qt::KeepAspectRatio));
    } else {
        m_label->setPixmap(QPixmap());
    }

    Q_EMIT dataUpdated(0);
}
