#include <QtNodes/DataFlowGraphModel>
#include <QtNodes/DataFlowGraphicsScene>
#include <QtNodes/GraphicsView>
#include <QtNodes/NodeData>
#include <QtNodes/NodeDelegateModelRegistry>

#include <QtNodes/StyleCollection>

#include <QtGui/QScreen>
#include <QtWidgets/QApplication>

#include "Nodes/Image/ImageLoadNode.h"
#include "Nodes/Image/ImagePreviewNode.h"

using namespace QtNodes;

static std::shared_ptr<NodeDelegateModelRegistry> registerDataModels()
{
    auto ret = std::make_shared<NodeDelegateModelRegistry>();
    ret->registerModel<ImageLoadNode>();
    ret->registerModel<ImagePreviewNode>();
    return ret;
}
static void setStyle()
{
    StyleCollection::flowViewStyle().setStyle(R"(
    {
        "GraphicsViewStyle": {
            "BackgroundColor": "lightgray",
            "FineGridColor": "gainsboro",
            "CoarseGridColor": "white"
        }
    }
    )");


    StyleCollection::nodeStyle().setNodeStyle(R"(
    {
        "NodeStyle": {
            "NormalBoundaryColor": "dimgray",
            "SelectedBoundaryColor": "black",
            "GradientColor0": "whitesmoke",
            "GradientColor1": "whitesmoke",
            "GradientColor2": "whitesmoke",
            "GradientColor3": "whitesmoke",
            "ShadowColor": "darkgray",
            "ShadowEnabled": true,
            "FontColor": "black",
            "FontColorFaded": "dimgray",
            "ConnectionPointColor": "slategray",
            "FilledConnectionPointColor": "dodgerblue",
            "ErrorColor": "darkred",
            "WarningColor": "darkorange",

            "PenWidth": 2,
            "HoveredPenWidth": 3,

            "ConnectionPointDiameter": 10.0,

            "Opacity": 0.9
        }
    }
    )");

    StyleCollection::connectionStyle().setConnectionStyle(R"(
    {
        "ConnectionStyle": {
            "ConstructionColor": "blue",
            "NormalColor": "royablue",
            "SelectedColor": [100, 100, 100],
            "SelectedHaloColor": "orange",
            "HoveredColor": "blue",

            "LineWidth": 4.0,
            "ConstructionLineWidth": 6.0,
            "PointDiameter": 10.0,

            "UseDataDefinedColors": false
        }
    }
    )");
}


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    std::shared_ptr<NodeDelegateModelRegistry> registry = registerDataModels();

    setStyle();

    DataFlowGraphModel dataFlowGraphModel(registry);

    DataFlowGraphicsScene scene(dataFlowGraphModel);

    GraphicsView view(&scene);

    view.setWindowTitle("Data Flow: Resizable Images");
    view.resize(1600, 1000);
    // Center window.
    view.move(QApplication::primaryScreen()->availableGeometry().center() - view.rect().center());
    view.show();

    return app.exec();
}
