#pragma once

#include <iostream>

#include <QtCore/QObject>
#include <QtWidgets/QLabel>

#include <QtNodes/NodeDelegateModel>
#include <QtNodes/NodeDelegateModelRegistry>

#include "PixmapData.h"

using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDelegateModel;
using QtNodes::PortIndex;
using QtNodes::PortType;

class ImagePreviewNode : public NodeDelegateModel
{
    Q_OBJECT

public:
    ImagePreviewNode() = default;
    ~ImagePreviewNode() = default;

public:
    QString caption() const override { return QString("Image Preview"); }

    QString name() const override { return QString("ImagePreviewNode"); }

public:
    virtual QString modelName() const { return QString("Resulting Image"); }

    unsigned int nPorts(PortType const portType) const override
    {
        return portType == PortType::In ? 1 : 0;
    }

    bool portCaptionVisible(PortType, PortIndex) const override { return true; }

    QString portCaption(PortType portType, PortIndex portIndex) const override
    {
        if (portType == PortType::In)
            return QStringLiteral("Image");
        return QString();
    }

    NodeDataType dataType(PortType const portType, PortIndex const portIndex) const override
    {
        return PixmapData().type();
    }

    std::shared_ptr<NodeData> outData(PortIndex const port) override
    {
        return m_pixmap;
    }

    void setInData(std::shared_ptr<NodeData> nodeData, PortIndex const port) override;

    QWidget *embeddedWidget() override;

    bool resizable() const override { return true; }

protected:
    bool eventFilter(QObject *object, QEvent *event) override;

private:
    QLabel* m_label;

    std::shared_ptr<PixmapData> m_pixmap;
};
