#include "ImagePreviewNode.h"

#include <QtNodes/NodeDelegateModelRegistry>

#include <QtCore/QDir>
#include <QtCore/QEvent>
#include <QtWidgets/QFileDialog>

QWidget* ImagePreviewNode::embeddedWidget()
{
    if (m_label)
        return m_label;

    m_label = new QLabel;
    m_label->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    QFont f = m_label->font();
    f.setBold(true);
    m_label->setFont(f);
    m_label->setMinimumSize(200, 200);
    m_label->installEventFilter(this);
    return m_label;
}

bool ImagePreviewNode::eventFilter(QObject *object, QEvent *event)
{
    if (object == m_label) {
        int w = m_label->width();
        int h = m_label->height();

        if (event->type() == QEvent::Resize) {
            if (m_pixmap) {
                QPixmap pixmap = m_pixmap->pixmap();
                if (!pixmap.isNull()) {
                    m_label->setPixmap(pixmap.scaled(w, h, Qt::KeepAspectRatio, Qt::SmoothTransformation));
                }
            }
        }
    }

    return false;
}

void ImagePreviewNode::setInData(std::shared_ptr<NodeData> nodeData, PortIndex const)
{
    m_pixmap = std::dynamic_pointer_cast<PixmapData>(nodeData);
    QPixmap pixmap = m_pixmap->pixmap();

    if (!pixmap.isNull()) {
        int w = m_label->width();
        int h = m_label->height();

        m_label->setPixmap(pixmap.scaled(w, h, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    } else {
        m_label->setPixmap(QPixmap());
    }

    Q_EMIT dataUpdated(0);
}
