#include "ImageLoadNode.h"

#include <QtCore/QDir>
#include <QtCore/QEvent>

#include <QtWidgets/QFileDialog>
#include <QVBoxLayout>
#include <qnamespace.h>
#include <qpalette.h>

QWidget* ImageLoadNode::embeddedWidget()
{
    if (m_widget)
        return m_widget;

    m_button = new QPushButton("Load image from local file");
    m_button->installEventFilter(this);

    m_thumb = new QLabel("Image");
    m_thumb->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    QFont font = m_thumb->font();
    font.setBold(true);
    m_thumb->setFont(font);
    m_thumb->setMinimumSize(200, 200);
    m_thumb->setMaximumSize(800, 800);
    m_thumb->installEventFilter(this);

    QPalette palette = m_thumb->palette();
    palette.setColor(m_thumb->backgroundRole(), Qt::white);
    palette.setColor(m_thumb->foregroundRole(), Qt::black);
    m_thumb->setPalette(palette);

    m_widget = new QWidget();
    m_widget->setLayout(new QVBoxLayout());
    m_widget->layout()->addWidget(m_button);
    m_widget->layout()->addWidget(m_thumb);

    return m_widget;
}

bool ImageLoadNode::eventFilter(QObject *object, QEvent *event)
{
    if (object == m_button) {
        if (event->type() == QEvent::MouseButtonPress) {
            qDebug("ImageLoadNode : Button pressed");
            QString fileName = QFileDialog::getOpenFileName(nullptr,
                                        tr("Open Image"),
                                        QDir::homePath(),
                                        tr("Image Files (*.png *.jpg *.bmp)"));
            if (fileName.isEmpty())
                return true;

            m_pixmap = QPixmap(fileName);
            int w = m_thumb->width();
            int h = m_thumb->height();
            m_thumb->setPixmap(m_pixmap.scaled(w, h, Qt::KeepAspectRatio, Qt::SmoothTransformation));

            Q_EMIT dataUpdated(0);

            return true;
        }
    } else if (object == m_thumb) {
        if (event->type() == QEvent::Resize) {
            qDebug("ImageLoadNode : Thumb resized");
            if (!m_pixmap.isNull()) {
                int w = m_thumb->width();
                int h = m_thumb->height();
                m_thumb->setPixmap(m_pixmap.scaled(w, h, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            }
        }
    }

    return false;
}
