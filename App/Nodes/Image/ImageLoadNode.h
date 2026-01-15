#pragma once

#include <iostream>

#include <QObject>
#include <QLabel>

#include <QtNodes/NodeDelegateModel>
#include <QtNodes/NodeDelegateModelRegistry>

#include "PixmapData.h"

using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDelegateModel;
using QtNodes::PortIndex;
using QtNodes::PortType;

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class ImageLoadNode : public NodeDelegateModel
{
    Q_OBJECT

public:
    ImageLoadNode();

    ~ImageLoadNode() = default;

public:
    QString caption() const override { return QString("Image Load"); }

    QString name() const override { return QString("ImageLoadNode"); }

public:
    virtual QString modelName() const { return QString("Source Image"); }

    unsigned int nPorts(PortType const portType) const override;

    NodeDataType dataType(PortType const portType, PortIndex const portIndex) const override;

    std::shared_ptr<NodeData> outData(PortIndex const port) override;

    void setInData(std::shared_ptr<NodeData>, PortIndex const portIndex) override {}

    QWidget *embeddedWidget() override { return m_label; }

    bool resizable() const override { return true; }

protected:
    bool eventFilter(QObject *object, QEvent *event) override;

private:
    QLabel *m_label;

    QPixmap m_pixmap;
};
