#include "ImageLoadNode.h"

#include <QtCore/QDir>
#include <QtCore/QEvent>

#include <QtWidgets/QFileDialog>
#include <QVBoxLayout>
#include <qboxlayout.h>
#include <qcolor.h>
#include <qlabel.h>
#include <qnamespace.h>
#include <qpalette.h>

QWidget* ImageLoadNode::embeddedWidget()
{
    if (m_widget)
        return m_widget;

    m_path = new QLabel();
    m_path->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    m_path->setWordWrap(true);

    m_button = new QPushButton("Load image from local file");
    m_button->installEventFilter(this);

    m_thumb = new QLabel("Image");
    m_thumb->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    QFont font = m_thumb->font();
    font.setBold(true);
    m_thumb->setFont(font);
    m_thumb->setMinimumSize(200, 200);
    // m_thumb->setMaximumSize(800, 800);
    m_thumb->installEventFilter(this);

    m_widget = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(m_path, 0);
    layout->addWidget(m_button, 0);
    layout->addWidget(m_thumb, 1);
    m_widget->setLayout(layout);

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

            m_path->setText(fileName);

            m_pixmap = QPixmap(fileName);
            int w = m_thumb->width();
            int h = m_thumb->height();
            m_thumb->setPixmap(m_pixmap.scaled(w, h, Qt::KeepAspectRatio, Qt::FastTransformation));

            Q_EMIT dataUpdated(0);

            return true;
        }
    } else if (object == m_thumb) {
        if (event->type() == QEvent::Resize) {
            qDebug("ImageLoadNode : Thumb resized");
            if (!m_pixmap.isNull()) {
                int w = m_thumb->width();
                int h = m_thumb->height();
                m_thumb->setPixmap(m_pixmap.scaled(w, h, Qt::KeepAspectRatio, Qt::FastTransformation));
            }
        }
    }

    return false;
}
