#pragma once

#include <iostream>

#include <QObject>
#include <QLabel>
#include <QPushButton>

#include <QtNodes/NodeDelegateModel>
#include <QtNodes/NodeDelegateModelRegistry>

#include "PixmapData.h"

using namespace QtNodes;


class ImageLoadNode : public NodeDelegateModel
{
    Q_OBJECT

public:
    ImageLoadNode() = default;
    ~ImageLoadNode() = default;

public:
    QString caption() const override { return QString("Load Image"); }

    QString name() const override { return QString("ImageLoadNode"); }

public:
    virtual QString modelName() const { return QString("Source Image"); }

    unsigned int nPorts(PortType const portType) const override
    {
        if (portType == PortType::In)
            return 0;
        else if (portType == PortType::Out)
            return 1;
        return 1;
    }

    bool portCaptionVisible(PortType, PortIndex) const override { return true; }

    QString portCaption(PortType portType, PortIndex portIndex) const override
    {
        if (portType == PortType::In)
            return QString();
        else if (portType == PortType::Out && portIndex == 0)
            return QStringLiteral("Image");
        return QString();
    }

    NodeDataType dataType(PortType const portType, PortIndex const portIndex) const override
    {
        return PixmapData().type();
    }

    std::shared_ptr<NodeData> outData(PortIndex const port) override
    {
        return std::make_shared<PixmapData>(m_pixmap);
    }

    void setInData(std::shared_ptr<NodeData>, PortIndex const portIndex) override {}

    QWidget *embeddedWidget() override;

    bool resizable() const override { return true; }

protected:
    bool eventFilter(QObject *object, QEvent *event) override;

private:
    QWidget* m_widget;

    QLabel* m_path;
    QLabel* m_thumb;
    QPushButton* m_button;

    QPixmap m_pixmap;
};
