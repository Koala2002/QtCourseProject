/********************************************************************************
** Form generated from reading UI file 'painter.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAINTER_H
#define UI_PAINTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "painterlabel.h"

QT_BEGIN_NAMESPACE

class Ui_Painter
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_5;
    QGroupBox *ToolUseNowDisplayLayout;
    QVBoxLayout *verticalLayout_7;
    QLabel *UseToolIcon;
    QStackedWidget *ValueControlRegion;
    QHBoxLayout *WorkRegion;
    QGroupBox *PainterToolBox;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *PainterToolBoxLayout;
    QVBoxLayout *ToolLayout;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_4;
    QPushButton *DragTool;
    QPushButton *DrawPen;
    QPushButton *Eraser;
    QVBoxLayout *verticalLayout_5;
    QPushButton *DrawShape;
    QPushButton *Bucket;
    QPushButton *BlurryTool;
    PainterLabel *ColorDisplayer;
    QGroupBox *ColorBox;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *ColorChooseLayout2;
    QCheckBox *OrangeColor;
    QCheckBox *WhiteColor;
    QCheckBox *BlackColor;
    QCheckBox *GreenColor;
    QCheckBox *RedColor;
    QVBoxLayout *ColorChooseLayout1;
    QCheckBox *CyanColor;
    QCheckBox *PinkColor;
    QCheckBox *PurpleColor;
    QCheckBox *BlueColor;
    QCheckBox *YellowColor;
    QGroupBox *GraphicsBox;
    QHBoxLayout *horizontalLayout;
    QPushButton *Rectangle;
    QPushButton *Circle;
    QVBoxLayout *ZoomRatioLayout;
    QLabel *ZoomRatioDisplayer;
    QGraphicsView *graphicsView;
    QVBoxLayout *verticalLayout_3;
    QScrollArea *GraphLayerDisplayerScrollArea;
    QWidget *scrollAreaWidgetContents_2;
    QVBoxLayout *GraphLayerOperatorLayout;
    QPushButton *AddGraphLayer;
    QPushButton *HideGraphLayer;
    QPushButton *DeleteGraphLayer;
    QPushButton *CopyGraphLayer;
    QPushButton *MergeGraphLayer;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Painter)
    {
        if (Painter->objectName().isEmpty())
            Painter->setObjectName(QString::fromUtf8("Painter"));
        Painter->resize(1150, 780);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Painter->sizePolicy().hasHeightForWidth());
        Painter->setSizePolicy(sizePolicy);
        Painter->setMinimumSize(QSize(1088, 750));
        Painter->setMouseTracking(true);
        centralwidget = new QWidget(Painter);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_6 = new QVBoxLayout(centralwidget);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        ToolUseNowDisplayLayout = new QGroupBox(centralwidget);
        ToolUseNowDisplayLayout->setObjectName(QString::fromUtf8("ToolUseNowDisplayLayout"));
        ToolUseNowDisplayLayout->setMinimumSize(QSize(125, 60));
        ToolUseNowDisplayLayout->setMaximumSize(QSize(125, 60));
        verticalLayout_7 = new QVBoxLayout(ToolUseNowDisplayLayout);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        UseToolIcon = new QLabel(ToolUseNowDisplayLayout);
        UseToolIcon->setObjectName(QString::fromUtf8("UseToolIcon"));
        UseToolIcon->setAlignment(Qt::AlignCenter);

        verticalLayout_7->addWidget(UseToolIcon);


        horizontalLayout_5->addWidget(ToolUseNowDisplayLayout);

        ValueControlRegion = new QStackedWidget(centralwidget);
        ValueControlRegion->setObjectName(QString::fromUtf8("ValueControlRegion"));
        ValueControlRegion->setMinimumSize(QSize(0, 60));
        ValueControlRegion->setMaximumSize(QSize(16777215, 60));

        horizontalLayout_5->addWidget(ValueControlRegion);


        verticalLayout_6->addLayout(horizontalLayout_5);

        WorkRegion = new QHBoxLayout();
        WorkRegion->setObjectName(QString::fromUtf8("WorkRegion"));
        PainterToolBox = new QGroupBox(centralwidget);
        PainterToolBox->setObjectName(QString::fromUtf8("PainterToolBox"));
        PainterToolBox->setMinimumSize(QSize(125, 0));
        PainterToolBox->setMaximumSize(QSize(125, 16777215));
        PainterToolBox->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
        horizontalLayout_2 = new QHBoxLayout(PainterToolBox);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        PainterToolBoxLayout = new QVBoxLayout();
        PainterToolBoxLayout->setObjectName(QString::fromUtf8("PainterToolBoxLayout"));
        ToolLayout = new QVBoxLayout();
        ToolLayout->setSpacing(10);
        ToolLayout->setObjectName(QString::fromUtf8("ToolLayout"));
        ToolLayout->setContentsMargins(-1, 20, -1, 5);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(10);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(10);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        DragTool = new QPushButton(PainterToolBox);
        DragTool->setObjectName(QString::fromUtf8("DragTool"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(DragTool->sizePolicy().hasHeightForWidth());
        DragTool->setSizePolicy(sizePolicy1);
        DragTool->setMinimumSize(QSize(50, 50));
        DragTool->setMaximumSize(QSize(50, 50));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        DragTool->setFont(font);

        verticalLayout_4->addWidget(DragTool);

        DrawPen = new QPushButton(PainterToolBox);
        DrawPen->setObjectName(QString::fromUtf8("DrawPen"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(DrawPen->sizePolicy().hasHeightForWidth());
        DrawPen->setSizePolicy(sizePolicy2);
        DrawPen->setMinimumSize(QSize(50, 50));
        DrawPen->setMaximumSize(QSize(50, 50));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setItalic(false);
        font1.setUnderline(false);
        font1.setStrikeOut(false);
        font1.setKerning(true);
        DrawPen->setFont(font1);

        verticalLayout_4->addWidget(DrawPen);

        Eraser = new QPushButton(PainterToolBox);
        Eraser->setObjectName(QString::fromUtf8("Eraser"));
        Eraser->setMinimumSize(QSize(50, 50));
        Eraser->setMaximumSize(QSize(50, 50));
        Eraser->setFont(font);

        verticalLayout_4->addWidget(Eraser);


        horizontalLayout_3->addLayout(verticalLayout_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(10);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        DrawShape = new QPushButton(PainterToolBox);
        DrawShape->setObjectName(QString::fromUtf8("DrawShape"));
        sizePolicy2.setHeightForWidth(DrawShape->sizePolicy().hasHeightForWidth());
        DrawShape->setSizePolicy(sizePolicy2);
        DrawShape->setMinimumSize(QSize(50, 50));
        DrawShape->setMaximumSize(QSize(50, 50));
        DrawShape->setFont(font);

        verticalLayout_5->addWidget(DrawShape);

        Bucket = new QPushButton(PainterToolBox);
        Bucket->setObjectName(QString::fromUtf8("Bucket"));
        Bucket->setMinimumSize(QSize(50, 50));
        Bucket->setMaximumSize(QSize(50, 50));
        Bucket->setFont(font);

        verticalLayout_5->addWidget(Bucket);

        BlurryTool = new QPushButton(PainterToolBox);
        BlurryTool->setObjectName(QString::fromUtf8("BlurryTool"));
        BlurryTool->setMinimumSize(QSize(50, 50));
        BlurryTool->setMaximumSize(QSize(50, 50));
        BlurryTool->setFont(font);
        BlurryTool->setLayoutDirection(Qt::LeftToRight);

        verticalLayout_5->addWidget(BlurryTool);


        horizontalLayout_3->addLayout(verticalLayout_5);


        ToolLayout->addLayout(horizontalLayout_3);

        ColorDisplayer = new PainterLabel(PainterToolBox);
        ColorDisplayer->setObjectName(QString::fromUtf8("ColorDisplayer"));
        sizePolicy.setHeightForWidth(ColorDisplayer->sizePolicy().hasHeightForWidth());
        ColorDisplayer->setSizePolicy(sizePolicy);
        ColorDisplayer->setMinimumSize(QSize(50, 50));
        ColorDisplayer->setMaximumSize(QSize(50, 50));
        ColorDisplayer->setAlignment(Qt::AlignCenter);

        ToolLayout->addWidget(ColorDisplayer);

        ColorBox = new QGroupBox(PainterToolBox);
        ColorBox->setObjectName(QString::fromUtf8("ColorBox"));
        ColorBox->setMinimumSize(QSize(100, 140));
        ColorBox->setMaximumSize(QSize(100, 140));
        ColorBox->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
        horizontalLayout_4 = new QHBoxLayout(ColorBox);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 5, 0, 6);
        ColorChooseLayout2 = new QVBoxLayout();
        ColorChooseLayout2->setSpacing(8);
        ColorChooseLayout2->setObjectName(QString::fromUtf8("ColorChooseLayout2"));
        ColorChooseLayout2->setSizeConstraint(QLayout::SetDefaultConstraint);
        ColorChooseLayout2->setContentsMargins(0, 2, -1, 4);
        OrangeColor = new QCheckBox(ColorBox);
        OrangeColor->setObjectName(QString::fromUtf8("OrangeColor"));
        OrangeColor->setMinimumSize(QSize(20, 20));
        OrangeColor->setMaximumSize(QSize(20, 20));
        OrangeColor->setCheckable(false);

        ColorChooseLayout2->addWidget(OrangeColor);

        WhiteColor = new QCheckBox(ColorBox);
        WhiteColor->setObjectName(QString::fromUtf8("WhiteColor"));
        WhiteColor->setMinimumSize(QSize(20, 20));
        WhiteColor->setMaximumSize(QSize(20, 20));
        WhiteColor->setCheckable(false);

        ColorChooseLayout2->addWidget(WhiteColor);

        BlackColor = new QCheckBox(ColorBox);
        BlackColor->setObjectName(QString::fromUtf8("BlackColor"));
        BlackColor->setMinimumSize(QSize(20, 20));
        BlackColor->setMaximumSize(QSize(20, 20));
        BlackColor->setCheckable(false);

        ColorChooseLayout2->addWidget(BlackColor);

        GreenColor = new QCheckBox(ColorBox);
        GreenColor->setObjectName(QString::fromUtf8("GreenColor"));
        GreenColor->setMinimumSize(QSize(20, 20));
        GreenColor->setMaximumSize(QSize(20, 20));
        GreenColor->setCheckable(false);

        ColorChooseLayout2->addWidget(GreenColor);

        RedColor = new QCheckBox(ColorBox);
        RedColor->setObjectName(QString::fromUtf8("RedColor"));
        RedColor->setMinimumSize(QSize(20, 20));
        RedColor->setMaximumSize(QSize(20, 20));
        RedColor->setStyleSheet(QString::fromUtf8(""));
        RedColor->setCheckable(false);

        ColorChooseLayout2->addWidget(RedColor);


        horizontalLayout_4->addLayout(ColorChooseLayout2);

        ColorChooseLayout1 = new QVBoxLayout();
        ColorChooseLayout1->setSpacing(8);
        ColorChooseLayout1->setObjectName(QString::fromUtf8("ColorChooseLayout1"));
        ColorChooseLayout1->setSizeConstraint(QLayout::SetDefaultConstraint);
        ColorChooseLayout1->setContentsMargins(0, 2, -1, 4);
        CyanColor = new QCheckBox(ColorBox);
        CyanColor->setObjectName(QString::fromUtf8("CyanColor"));
        CyanColor->setMinimumSize(QSize(20, 20));
        CyanColor->setMaximumSize(QSize(20, 20));
        CyanColor->setCheckable(false);

        ColorChooseLayout1->addWidget(CyanColor);

        PinkColor = new QCheckBox(ColorBox);
        PinkColor->setObjectName(QString::fromUtf8("PinkColor"));
        PinkColor->setMinimumSize(QSize(20, 20));
        PinkColor->setMaximumSize(QSize(20, 20));
        PinkColor->setCheckable(false);

        ColorChooseLayout1->addWidget(PinkColor);

        PurpleColor = new QCheckBox(ColorBox);
        PurpleColor->setObjectName(QString::fromUtf8("PurpleColor"));
        PurpleColor->setMinimumSize(QSize(20, 20));
        PurpleColor->setMaximumSize(QSize(20, 20));
        PurpleColor->setCheckable(false);

        ColorChooseLayout1->addWidget(PurpleColor);

        BlueColor = new QCheckBox(ColorBox);
        BlueColor->setObjectName(QString::fromUtf8("BlueColor"));
        BlueColor->setMinimumSize(QSize(20, 20));
        BlueColor->setMaximumSize(QSize(20, 20));
        BlueColor->setCheckable(false);

        ColorChooseLayout1->addWidget(BlueColor);

        YellowColor = new QCheckBox(ColorBox);
        YellowColor->setObjectName(QString::fromUtf8("YellowColor"));
        YellowColor->setMinimumSize(QSize(20, 20));
        YellowColor->setMaximumSize(QSize(20, 20));
        YellowColor->setCheckable(false);

        ColorChooseLayout1->addWidget(YellowColor);


        horizontalLayout_4->addLayout(ColorChooseLayout1);


        ToolLayout->addWidget(ColorBox);

        GraphicsBox = new QGroupBox(PainterToolBox);
        GraphicsBox->setObjectName(QString::fromUtf8("GraphicsBox"));
        GraphicsBox->setMinimumSize(QSize(100, 60));
        GraphicsBox->setMaximumSize(QSize(100, 60));
        GraphicsBox->setAlignment(Qt::AlignCenter);
        horizontalLayout = new QHBoxLayout(GraphicsBox);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        Rectangle = new QPushButton(GraphicsBox);
        Rectangle->setObjectName(QString::fromUtf8("Rectangle"));
        sizePolicy2.setHeightForWidth(Rectangle->sizePolicy().hasHeightForWidth());
        Rectangle->setSizePolicy(sizePolicy2);
        Rectangle->setMinimumSize(QSize(30, 30));
        Rectangle->setMaximumSize(QSize(40, 30));

        horizontalLayout->addWidget(Rectangle);

        Circle = new QPushButton(GraphicsBox);
        Circle->setObjectName(QString::fromUtf8("Circle"));
        sizePolicy2.setHeightForWidth(Circle->sizePolicy().hasHeightForWidth());
        Circle->setSizePolicy(sizePolicy2);
        Circle->setMinimumSize(QSize(30, 30));
        Circle->setMaximumSize(QSize(40, 30));

        horizontalLayout->addWidget(Circle);


        ToolLayout->addWidget(GraphicsBox);


        PainterToolBoxLayout->addLayout(ToolLayout);

        ZoomRatioLayout = new QVBoxLayout();
        ZoomRatioLayout->setObjectName(QString::fromUtf8("ZoomRatioLayout"));
        ZoomRatioLayout->setContentsMargins(-1, 20, -1, 20);
        ZoomRatioDisplayer = new QLabel(PainterToolBox);
        ZoomRatioDisplayer->setObjectName(QString::fromUtf8("ZoomRatioDisplayer"));
        ZoomRatioDisplayer->setMinimumSize(QSize(100, 30));
        QFont font2;
        font2.setPointSize(14);
        ZoomRatioDisplayer->setFont(font2);
        ZoomRatioDisplayer->setAlignment(Qt::AlignCenter);

        ZoomRatioLayout->addWidget(ZoomRatioDisplayer);


        PainterToolBoxLayout->addLayout(ZoomRatioLayout);


        horizontalLayout_2->addLayout(PainterToolBoxLayout);


        WorkRegion->addWidget(PainterToolBox);

        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setMinimumSize(QSize(800, 600));
        graphicsView->setMouseTracking(true);
        graphicsView->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        WorkRegion->addWidget(graphicsView);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(10);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(-1, 0, -1, 5);
        GraphLayerDisplayerScrollArea = new QScrollArea(centralwidget);
        GraphLayerDisplayerScrollArea->setObjectName(QString::fromUtf8("GraphLayerDisplayerScrollArea"));
        GraphLayerDisplayerScrollArea->setMinimumSize(QSize(125, 185));
        GraphLayerDisplayerScrollArea->setMaximumSize(QSize(125, 16777215));
        GraphLayerDisplayerScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        GraphLayerDisplayerScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        GraphLayerDisplayerScrollArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        GraphLayerDisplayerScrollArea->setWidgetResizable(true);
        GraphLayerDisplayerScrollArea->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 123, 402));
        GraphLayerDisplayerScrollArea->setWidget(scrollAreaWidgetContents_2);

        verticalLayout_3->addWidget(GraphLayerDisplayerScrollArea);

        GraphLayerOperatorLayout = new QVBoxLayout();
        GraphLayerOperatorLayout->setSpacing(7);
        GraphLayerOperatorLayout->setObjectName(QString::fromUtf8("GraphLayerOperatorLayout"));
        GraphLayerOperatorLayout->setContentsMargins(-1, 0, -1, 0);
        AddGraphLayer = new QPushButton(centralwidget);
        AddGraphLayer->setObjectName(QString::fromUtf8("AddGraphLayer"));
        AddGraphLayer->setMinimumSize(QSize(95, 30));
        AddGraphLayer->setMaximumSize(QSize(95, 30));
        AddGraphLayer->setFont(font);

        GraphLayerOperatorLayout->addWidget(AddGraphLayer);

        HideGraphLayer = new QPushButton(centralwidget);
        HideGraphLayer->setObjectName(QString::fromUtf8("HideGraphLayer"));
        HideGraphLayer->setMinimumSize(QSize(95, 30));
        HideGraphLayer->setMaximumSize(QSize(95, 30));

        GraphLayerOperatorLayout->addWidget(HideGraphLayer);

        DeleteGraphLayer = new QPushButton(centralwidget);
        DeleteGraphLayer->setObjectName(QString::fromUtf8("DeleteGraphLayer"));
        DeleteGraphLayer->setMinimumSize(QSize(95, 30));
        DeleteGraphLayer->setMaximumSize(QSize(95, 30));
        DeleteGraphLayer->setFont(font);

        GraphLayerOperatorLayout->addWidget(DeleteGraphLayer);

        CopyGraphLayer = new QPushButton(centralwidget);
        CopyGraphLayer->setObjectName(QString::fromUtf8("CopyGraphLayer"));
        CopyGraphLayer->setMinimumSize(QSize(95, 30));
        CopyGraphLayer->setMaximumSize(QSize(95, 30));
        CopyGraphLayer->setFont(font);

        GraphLayerOperatorLayout->addWidget(CopyGraphLayer);

        MergeGraphLayer = new QPushButton(centralwidget);
        MergeGraphLayer->setObjectName(QString::fromUtf8("MergeGraphLayer"));
        MergeGraphLayer->setMinimumSize(QSize(95, 30));
        MergeGraphLayer->setMaximumSize(QSize(95, 30));
        MergeGraphLayer->setFont(font);

        GraphLayerOperatorLayout->addWidget(MergeGraphLayer);


        verticalLayout_3->addLayout(GraphLayerOperatorLayout);


        WorkRegion->addLayout(verticalLayout_3);


        verticalLayout_6->addLayout(WorkRegion);

        Painter->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Painter);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setEnabled(true);
        menubar->setGeometry(QRect(0, 0, 1150, 30));
        sizePolicy.setHeightForWidth(menubar->sizePolicy().hasHeightForWidth());
        menubar->setSizePolicy(sizePolicy);
        menubar->setMaximumSize(QSize(16777215, 16777215));
        menubar->setDefaultUp(false);
        menubar->setNativeMenuBar(true);
        Painter->setMenuBar(menubar);
        statusbar = new QStatusBar(Painter);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        Painter->setStatusBar(statusbar);

        retranslateUi(Painter);

        QMetaObject::connectSlotsByName(Painter);
    } // setupUi

    void retranslateUi(QMainWindow *Painter)
    {
        Painter->setWindowTitle(QCoreApplication::translate("Painter", "Painter", nullptr));
        ToolUseNowDisplayLayout->setTitle(QString());
        UseToolIcon->setText(QString());
        PainterToolBox->setTitle(QString());
        DragTool->setText(QString());
        DrawPen->setText(QString());
        Eraser->setText(QString());
        DrawShape->setText(QString());
        Bucket->setText(QString());
        BlurryTool->setText(QString());
        ColorDisplayer->setText(QCoreApplication::translate("Painter", "\350\252\277\350\211\262\347\233\244", nullptr));
        ColorBox->setTitle(QString());
        OrangeColor->setText(QString());
        WhiteColor->setText(QString());
        BlackColor->setText(QString());
        GreenColor->setText(QString());
        RedColor->setText(QString());
        CyanColor->setText(QString());
        PinkColor->setText(QString());
        PurpleColor->setText(QString());
        BlueColor->setText(QString());
        YellowColor->setText(QString());
        GraphicsBox->setTitle(QString());
        Rectangle->setText(QString());
        Circle->setText(QString());
        ZoomRatioDisplayer->setText(QCoreApplication::translate("Painter", "\347\270\256\346\224\276\345\200\215\347\216\207", nullptr));
        AddGraphLayer->setText(QString());
        HideGraphLayer->setText(QString());
        DeleteGraphLayer->setText(QString());
        CopyGraphLayer->setText(QString());
        MergeGraphLayer->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Painter: public Ui_Painter {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAINTER_H
