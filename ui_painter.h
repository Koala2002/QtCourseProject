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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "painterlabel.h"

QT_BEGIN_NAMESPACE

class Ui_Painter
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_3;
    QTabWidget *WorkTabObject;
    QWidget *ToolTab;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_10;
    QHBoxLayout *horizontalLayout_6;
    QHBoxLayout *TabLayout;
    QHBoxLayout *horizontalLayout_5;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout;
    QPushButton *SelectTool;
    QSpacerItem *verticalSpacer;
    QPushButton *DrawPen;
    QSpacerItem *verticalSpacer_2;
    QPushButton *Eraser;
    QSpacerItem *verticalSpacer_3;
    QPushButton *Bucket;
    QSpacerItem *horizontalSpacer_5;
    QSpinBox *PenSizeControl;
    QSpacerItem *horizontalSpacer_6;
    PainterLabel *ColorDisplayer;
    QSpacerItem *horizontalSpacer_7;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_16;
    QCheckBox *RedColor;
    QSpacerItem *horizontalSpacer;
    QCheckBox *GreenColor;
    QSpacerItem *horizontalSpacer_2;
    QCheckBox *BlackColor;
    QSpacerItem *horizontalSpacer_12;
    QCheckBox *WhiteColor;
    QSpacerItem *horizontalSpacer_14;
    QCheckBox *OrangeColor;
    QSpacerItem *horizontalSpacer_18;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_17;
    QCheckBox *YellowColor;
    QSpacerItem *horizontalSpacer_3;
    QCheckBox *BlueColor;
    QSpacerItem *horizontalSpacer_4;
    QCheckBox *PurpleColor;
    QSpacerItem *horizontalSpacer_13;
    QCheckBox *PinkColor;
    QSpacerItem *horizontalSpacer_15;
    QCheckBox *CyanColor;
    QSpacerItem *horizontalSpacer_19;
    QSpacerItem *horizontalSpacer_8;
    QVBoxLayout *verticalLayout_4;
    QPushButton *AddGraphLayer;
    QSpacerItem *verticalSpacer_6;
    QPushButton *MergeGraphLayer;
    QSpacerItem *horizontalSpacer_9;
    QScrollArea *GraphLayerDisplayerScrollArea;
    QWidget *scrollAreaWidgetContents_2;
    QSpacerItem *horizontalSpacer_11;
    QWidget *SceneWatchTab;
    QPushButton *ZoomIn;
    QPushButton *pushButton_2;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QSpacerItem *verticalSpacer_5;
    QSpacerItem *verticalSpacer_4;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Painter)
    {
        if (Painter->objectName().isEmpty())
            Painter->setObjectName(QString::fromUtf8("Painter"));
        Painter->resize(1000, 909);
        centralwidget = new QWidget(Painter);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_3 = new QVBoxLayout(centralwidget);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        WorkTabObject = new QTabWidget(centralwidget);
        WorkTabObject->setObjectName(QString::fromUtf8("WorkTabObject"));
        WorkTabObject->setMaximumSize(QSize(16777215, 200));
        WorkTabObject->setIconSize(QSize(16, 16));
        ToolTab = new QWidget();
        ToolTab->setObjectName(QString::fromUtf8("ToolTab"));
        horizontalLayout_7 = new QHBoxLayout(ToolTab);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalSpacer_10 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_10);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        TabLayout = new QHBoxLayout();
        TabLayout->setObjectName(QString::fromUtf8("TabLayout"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        SelectTool = new QPushButton(ToolTab);
        SelectTool->setObjectName(QString::fromUtf8("SelectTool"));
        SelectTool->setMinimumSize(QSize(80, 30));
        SelectTool->setMaximumSize(QSize(80, 30));

        verticalLayout->addWidget(SelectTool);

        verticalSpacer = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        DrawPen = new QPushButton(ToolTab);
        DrawPen->setObjectName(QString::fromUtf8("DrawPen"));
        DrawPen->setMinimumSize(QSize(80, 30));
        DrawPen->setMaximumSize(QSize(80, 30));

        verticalLayout->addWidget(DrawPen);

        verticalSpacer_2 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_2);

        Eraser = new QPushButton(ToolTab);
        Eraser->setObjectName(QString::fromUtf8("Eraser"));
        Eraser->setMinimumSize(QSize(80, 30));
        Eraser->setMaximumSize(QSize(80, 30));

        verticalLayout->addWidget(Eraser);

        verticalSpacer_3 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_3);

        Bucket = new QPushButton(ToolTab);
        Bucket->setObjectName(QString::fromUtf8("Bucket"));
        Bucket->setMinimumSize(QSize(80, 30));
        Bucket->setMaximumSize(QSize(80, 30));

        verticalLayout->addWidget(Bucket);


        horizontalLayout_3->addLayout(verticalLayout);

        horizontalSpacer_5 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        PenSizeControl = new QSpinBox(ToolTab);
        PenSizeControl->setObjectName(QString::fromUtf8("PenSizeControl"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PenSizeControl->sizePolicy().hasHeightForWidth());
        PenSizeControl->setSizePolicy(sizePolicy);
        PenSizeControl->setMinimumSize(QSize(50, 100));
        PenSizeControl->setMaximumSize(QSize(50, 100));
        PenSizeControl->setAlignment(Qt::AlignCenter);
        PenSizeControl->setMinimum(5);
        PenSizeControl->setMaximum(32);
        PenSizeControl->setValue(10);

        horizontalLayout_3->addWidget(PenSizeControl);

        horizontalSpacer_6 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_6);


        horizontalLayout_4->addLayout(horizontalLayout_3);

        ColorDisplayer = new PainterLabel(ToolTab);
        ColorDisplayer->setObjectName(QString::fromUtf8("ColorDisplayer"));
        ColorDisplayer->setMinimumSize(QSize(80, 100));
        ColorDisplayer->setMaximumSize(QSize(80, 100));
        ColorDisplayer->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(ColorDisplayer);


        horizontalLayout_5->addLayout(horizontalLayout_4);

        horizontalSpacer_7 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_7);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(-1, -1, -1, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(5);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(10, -1, -1, 0);
        horizontalSpacer_16 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_16);

        RedColor = new QCheckBox(ToolTab);
        RedColor->setObjectName(QString::fromUtf8("RedColor"));
        RedColor->setMinimumSize(QSize(20, 20));
        RedColor->setMaximumSize(QSize(20, 20));
        RedColor->setStyleSheet(QString::fromUtf8(""));
        RedColor->setCheckable(false);

        horizontalLayout_2->addWidget(RedColor);

        horizontalSpacer = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        GreenColor = new QCheckBox(ToolTab);
        GreenColor->setObjectName(QString::fromUtf8("GreenColor"));
        GreenColor->setMinimumSize(QSize(20, 20));
        GreenColor->setMaximumSize(QSize(20, 20));
        GreenColor->setCheckable(false);

        horizontalLayout_2->addWidget(GreenColor);

        horizontalSpacer_2 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        BlackColor = new QCheckBox(ToolTab);
        BlackColor->setObjectName(QString::fromUtf8("BlackColor"));
        BlackColor->setMinimumSize(QSize(20, 20));
        BlackColor->setMaximumSize(QSize(20, 20));
        BlackColor->setCheckable(false);

        horizontalLayout_2->addWidget(BlackColor);

        horizontalSpacer_12 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_12);

        WhiteColor = new QCheckBox(ToolTab);
        WhiteColor->setObjectName(QString::fromUtf8("WhiteColor"));
        WhiteColor->setMinimumSize(QSize(20, 20));
        WhiteColor->setMaximumSize(QSize(20, 20));
        WhiteColor->setCheckable(false);

        horizontalLayout_2->addWidget(WhiteColor);

        horizontalSpacer_14 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_14);

        OrangeColor = new QCheckBox(ToolTab);
        OrangeColor->setObjectName(QString::fromUtf8("OrangeColor"));
        OrangeColor->setMinimumSize(QSize(20, 20));
        OrangeColor->setMaximumSize(QSize(20, 20));
        OrangeColor->setCheckable(false);

        horizontalLayout_2->addWidget(OrangeColor);

        horizontalSpacer_18 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_18);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(5);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(10, -1, -1, 0);
        horizontalSpacer_17 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_17);

        YellowColor = new QCheckBox(ToolTab);
        YellowColor->setObjectName(QString::fromUtf8("YellowColor"));
        YellowColor->setMinimumSize(QSize(20, 20));
        YellowColor->setMaximumSize(QSize(20, 20));
        YellowColor->setCheckable(false);

        horizontalLayout->addWidget(YellowColor);

        horizontalSpacer_3 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        BlueColor = new QCheckBox(ToolTab);
        BlueColor->setObjectName(QString::fromUtf8("BlueColor"));
        BlueColor->setMinimumSize(QSize(20, 20));
        BlueColor->setMaximumSize(QSize(20, 20));
        BlueColor->setCheckable(false);

        horizontalLayout->addWidget(BlueColor);

        horizontalSpacer_4 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        PurpleColor = new QCheckBox(ToolTab);
        PurpleColor->setObjectName(QString::fromUtf8("PurpleColor"));
        PurpleColor->setMinimumSize(QSize(20, 20));
        PurpleColor->setMaximumSize(QSize(20, 20));
        PurpleColor->setCheckable(false);

        horizontalLayout->addWidget(PurpleColor);

        horizontalSpacer_13 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_13);

        PinkColor = new QCheckBox(ToolTab);
        PinkColor->setObjectName(QString::fromUtf8("PinkColor"));
        PinkColor->setMinimumSize(QSize(20, 20));
        PinkColor->setMaximumSize(QSize(20, 20));
        PinkColor->setCheckable(false);

        horizontalLayout->addWidget(PinkColor);

        horizontalSpacer_15 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_15);

        CyanColor = new QCheckBox(ToolTab);
        CyanColor->setObjectName(QString::fromUtf8("CyanColor"));
        CyanColor->setMinimumSize(QSize(20, 20));
        CyanColor->setMaximumSize(QSize(20, 20));
        CyanColor->setCheckable(false);

        horizontalLayout->addWidget(CyanColor);

        horizontalSpacer_19 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_19);


        verticalLayout_2->addLayout(horizontalLayout);


        horizontalLayout_5->addLayout(verticalLayout_2);


        TabLayout->addLayout(horizontalLayout_5);

        horizontalSpacer_8 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        TabLayout->addItem(horizontalSpacer_8);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(-1, -1, -1, 0);
        AddGraphLayer = new QPushButton(ToolTab);
        AddGraphLayer->setObjectName(QString::fromUtf8("AddGraphLayer"));
        AddGraphLayer->setMinimumSize(QSize(80, 30));
        AddGraphLayer->setMaximumSize(QSize(80, 30));

        verticalLayout_4->addWidget(AddGraphLayer);

        verticalSpacer_6 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_4->addItem(verticalSpacer_6);

        MergeGraphLayer = new QPushButton(ToolTab);
        MergeGraphLayer->setObjectName(QString::fromUtf8("MergeGraphLayer"));
        MergeGraphLayer->setMinimumSize(QSize(80, 30));
        MergeGraphLayer->setMaximumSize(QSize(80, 30));

        verticalLayout_4->addWidget(MergeGraphLayer);


        TabLayout->addLayout(verticalLayout_4);


        horizontalLayout_6->addLayout(TabLayout);


        horizontalLayout_7->addLayout(horizontalLayout_6);

        horizontalSpacer_9 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_9);

        GraphLayerDisplayerScrollArea = new QScrollArea(ToolTab);
        GraphLayerDisplayerScrollArea->setObjectName(QString::fromUtf8("GraphLayerDisplayerScrollArea"));
        GraphLayerDisplayerScrollArea->setMinimumSize(QSize(200, 140));
        GraphLayerDisplayerScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        GraphLayerDisplayerScrollArea->setWidgetResizable(true);
        GraphLayerDisplayerScrollArea->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 334, 140));
        GraphLayerDisplayerScrollArea->setWidget(scrollAreaWidgetContents_2);

        horizontalLayout_7->addWidget(GraphLayerDisplayerScrollArea);

        horizontalSpacer_11 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_11);

        WorkTabObject->addTab(ToolTab, QString());
        SceneWatchTab = new QWidget();
        SceneWatchTab->setObjectName(QString::fromUtf8("SceneWatchTab"));
        ZoomIn = new QPushButton(SceneWatchTab);
        ZoomIn->setObjectName(QString::fromUtf8("ZoomIn"));
        ZoomIn->setGeometry(QRect(70, 30, 89, 29));
        pushButton_2 = new QPushButton(SceneWatchTab);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(70, 80, 89, 29));
        WorkTabObject->addTab(SceneWatchTab, QString());

        verticalLayout_3->addWidget(WorkTabObject);

        scrollArea = new QScrollArea(centralwidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy1);
        scrollArea->setMinimumSize(QSize(802, 602));
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        scrollArea->setWidgetResizable(true);
        scrollArea->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 976, 600));
        sizePolicy1.setHeightForWidth(scrollAreaWidgetContents->sizePolicy().hasHeightForWidth());
        scrollAreaWidgetContents->setSizePolicy(sizePolicy1);
        scrollAreaWidgetContents->setMinimumSize(QSize(600, 400));
        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_3->addWidget(scrollArea);

        verticalSpacer_5 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_3->addItem(verticalSpacer_5);

        verticalSpacer_4 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_3->addItem(verticalSpacer_4);

        Painter->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Painter);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1000, 30));
        Painter->setMenuBar(menubar);
        statusbar = new QStatusBar(Painter);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        Painter->setStatusBar(statusbar);

        retranslateUi(Painter);

        WorkTabObject->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Painter);
    } // setupUi

    void retranslateUi(QMainWindow *Painter)
    {
        Painter->setWindowTitle(QCoreApplication::translate("Painter", "Painter", nullptr));
        SelectTool->setText(QCoreApplication::translate("Painter", "\351\201\270\345\217\226", nullptr));
        DrawPen->setText(QCoreApplication::translate("Painter", "\347\225\253\347\255\206", nullptr));
        Eraser->setText(QCoreApplication::translate("Painter", "\346\251\241\347\232\256\346\223\246", nullptr));
        Bucket->setText(QCoreApplication::translate("Painter", "\346\260\264\346\241\266", nullptr));
        ColorDisplayer->setText(QCoreApplication::translate("Painter", "\350\252\277\350\211\262\347\233\244", nullptr));
        RedColor->setText(QString());
        GreenColor->setText(QString());
        BlackColor->setText(QString());
        WhiteColor->setText(QString());
        OrangeColor->setText(QString());
        YellowColor->setText(QString());
        BlueColor->setText(QString());
        PurpleColor->setText(QString());
        PinkColor->setText(QString());
        CyanColor->setText(QString());
        AddGraphLayer->setText(QCoreApplication::translate("Painter", "\346\226\260\345\242\236\345\234\226\345\261\244", nullptr));
        MergeGraphLayer->setText(QCoreApplication::translate("Painter", "\345\220\210\344\275\265\345\234\226\345\261\244", nullptr));
        WorkTabObject->setTabText(WorkTabObject->indexOf(ToolTab), QCoreApplication::translate("Painter", "\345\270\270\347\224\250", nullptr));
        ZoomIn->setText(QCoreApplication::translate("Painter", "\346\224\276\345\244\247\347\225\253\351\235\242", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Painter", "PushButton", nullptr));
        WorkTabObject->setTabText(WorkTabObject->indexOf(SceneWatchTab), QCoreApplication::translate("Painter", "\346\252\242\350\246\226", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Painter: public Ui_Painter {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAINTER_H
