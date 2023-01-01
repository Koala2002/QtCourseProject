#include "valuecontroller.h"


ValueController::ValueController(QStackedWidget *RegionWidget)
{
    widget=RegionWidget;

    //----控制像預設值設定----//
    penSize=10;
    eraserSize=10;
    blurrySize=10;
    blurryWeight=1;
    transParentValue=255;
    PenMode=QPainter::CompositionMode_Source;
    //----控制像預設值設定----//

    //----畫筆style預設值設定(雖然應該也只會用這個)----//
    DrawPen.setCapStyle(Qt::RoundCap);
    DrawPen.setJoinStyle(Qt::RoundJoin);
    //----畫筆style預設值設定(雖然應該也只會用這個)----//

    ColorNow=qRgba(0,0,0,255);//預設顏色為黑色

    ControllerInit();
    ControllerGroupBoxInit();
    SliderConnectInit();
    SliderUISetting();

    widget->addWidget(PenBox);
    widget->addWidget(EraserBox);
    widget->addWidget(BucketBox);
    widget->addWidget(BlurryBox);
    widget->addWidget(DragBox);
    widget->addWidget(ShapeBox);

    widget->setCurrentIndex(0);
}

QPen ValueController::getPen()
{
    return DrawPen;
}

QPainter::CompositionMode ValueController::getPenMode()
{
    return PenMode;
}

QColor ValueController::getColor()
{
    return transParentValue==0?QColor(0,0,0,0):ColorNow;
}

int ValueController::getBlurryWeight()
{
    return blurryWeight;
}

void ValueController::setColor(QColor rgba)
{
    ColorNow=rgba;
}

void ValueController::loadTool(ToolCode code)
{
    if(code==PenValue){
        ColorNow.setAlpha(transParentValue);
        DrawPen.setColor(transParentValue==0?QColor(0,0,0,0):ColorNow);
        DrawPen.setWidth(penSize);
    }
    if(code==EraserValue){
        DrawPen.setColor(Qt::transparent);
         DrawPen.setWidth(eraserSize);
    }
    if(code==BlurryValue){
        DrawPen.setWidth(blurrySize);
    }
    if(code==BucketValue)ColorNow.setAlpha(transParentValue);
}

void ValueController::setPage(PageCode code)
{
    if(code==PenPage)widget->setCurrentIndex(0);
    if(code==EraserPage)widget->setCurrentIndex(1);
    if(code==BucketPage)widget->setCurrentIndex(2);
    if(code==BlurryPage)widget->setCurrentIndex(3);
    if(code==DragPage)widget->setCurrentIndex(4);
    if(code==ShapePage)widget->setCurrentIndex(5);
}

void ValueController::ControllerInit()
{
    penSizeControl=new QSlider(Qt::Horizontal);
    penSizeControl->setMinimumSize(200,10);
    penSizeControl->setMaximumSize(200,10);
    penSizeControl->setMinimum(1);
    penSizeControl->setMaximum(50);
    penSizeControl->setValue(10);

    eraserSizeControl=new QSlider(Qt::Horizontal);
    eraserSizeControl->setMinimumSize(200,10);
    eraserSizeControl->setMaximumSize(200,10);
    eraserSizeControl->setMinimum(1);
    eraserSizeControl->setMaximum(50);
    eraserSizeControl->setValue(10);

    blurrySizeControl=new QSlider(Qt::Horizontal);
    blurrySizeControl->setMinimumSize(200,10);
    blurrySizeControl->setMaximumSize(200,10);
    blurrySizeControl->setMinimum(1);
    blurrySizeControl->setMaximum(50);
    blurrySizeControl->setValue(10);

    blurryWeightControl=new QSlider(Qt::Horizontal);
    blurryWeightControl->setMinimumSize(200,10);
    blurryWeightControl->setMaximumSize(200,10);
    blurryWeightControl->setMinimum(1);
    blurryWeightControl->setMaximum(10);
    blurryWeightControl->setValue(1);

    penTransParentControl=new QSlider(Qt::Horizontal);
    penTransParentControl->setMinimumSize(200,10);
    penTransParentControl->setMaximumSize(200,10);
    penTransParentControl->setMinimum(0);
    penTransParentControl->setMaximum(255);
    penTransParentControl->setValue(255);

    bucketTransParentControl=new QSlider(Qt::Horizontal);
    bucketTransParentControl->setMinimumSize(200,10);
    bucketTransParentControl->setMaximumSize(200,10);
    bucketTransParentControl->setMinimum(0);
    bucketTransParentControl->setMaximum(255);
    bucketTransParentControl->setValue(255);
}

void ValueController::ControllerGroupBoxInit()
{
    //----畫筆設定區(包括UI)初始化----//
    QHBoxLayout *PenBoxLayout=new QHBoxLayout();
    PenBoxLayout->setAlignment(Qt::AlignLeft);

    PenSizeName1=new QLabel("尺寸：10 px");
    PenSizeName1->setFont(QFont("標楷",10,  QFont::Bold));
    PenSizeName1->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    PenSizeName1->setStyleSheet(
        "text-align:left;"
        "background-color:rgb(225,225,225);color:rgb(35,35,35);"
        "border-radius: 4px;border-color:rgb(65,65,65);border-width:2px;border-style:solid;"
    );
    PenSizeName1->setMinimumSize(107,30);
    PenSizeName1->setMaximumSize(107,30);

    PenSizeName2=new QLabel("不透明度：100 %");
    PenSizeName2->setFont(QFont("標楷",10,  QFont::Bold));
    PenSizeName2->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    PenSizeName2->setStyleSheet(
        "background-color:rgb(225,225,225);color:rgb(35,35,35);"
        "border-radius: 4px;border-color:rgb(65,65,65);border-width:2px;border-style:solid;"
    );
    PenSizeName2->setMinimumSize(170,30);
    PenSizeName2->setMaximumSize(170,30);

    PenModeName=new QLabel("模式：覆蓋");
    PenModeName->setFont(QFont("標楷",10,  QFont::Bold));
    PenModeName->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    PenModeName->setStyleSheet(
        "background-color:rgb(225,225,225);color:rgb(35,35,35);"
        "border-radius: 4px;border-color:rgb(65,65,65);border-width:2px;border-style:solid;"
    );
    PenModeName->setMinimumSize(105,30);
    PenModeName->setMaximumSize(105,30);

    penModeChoser=new QComboBox();

    penModeChoser->setFont(QFont("標楷",10,  QFont::Bold));
    penModeChoser->setStyleSheet(
        "QComboBox{"
            "color:rgb(65,65,65);"
            "background-color:rgb(225,225,225);"
            "border:2px solid rgb(75,75,75);"
            "border-radius:4px;"
        "}"

        "QComboBox:hover{"
            "color:rgb(65,65,65);"
            "background-color:rgb(200,200,200);"
            "border:2px solid rgb(75,75,75);"
            "border-radius:4px;"
        "}"

        "QComboBox::drop-down{"
            "subcontrol-origin:padding;"
            "subcontrol-position:top right;"
            "width:60px;"
            "border-left-width:1px;"
            "border-top-right-radius:2px;"
            "border-bottom-right-radius:2px;"
            ""
            ""
        "}"

        "QComboBox::down-arrow {"
            "image: url(:/icons/penModeControlArrow.png);"
            "width: 20px;"
            "height: 20px;"
        "}"

        "QComboBox QAbstractItemView{"
            "outline: 0px;"
        "}"

        "QComboBox QListView::item:selected{"
            "color:rgb(65,65,65);"
            "background-color:rgb(205,205,205);"
        "}"

        "QComboBox QListView::item:hover{"
            "color:rgb(65,65,65);"
            "background-color:rgb(205,205,205);"
        "}"

        "QComboBox QListView:item{"
            "color:rgb(75,75,75);"
            "background-color:rgb(235,235,235);"
        "}"

        "QComboBox QListView::item{"
            "padding:10px;"
            "height:10px;"
        "}"
    );



    penModeChoser->setView(new QListView());

    penModeChoser->setEditable(true);
    penModeChoser->lineEdit()->setReadOnly(true);
    penModeChoser->lineEdit()->setAlignment(Qt::AlignLeft);

    penModeChoser->setMinimumSize(60,30);
    penModeChoser->setMaximumSize(60,30);


    penModeChoser->addItem("覆蓋");
    penModeChoser->addItem("疊加");

    connect(penModeChoser,SIGNAL(currentIndexChanged(int)),this,SLOT(PenModeChange(int)));

    PenBox=new QGroupBox();
    PenBox->setLayout(PenBoxLayout);

    PenBoxLayout->addWidget(PenModeName,Qt::AlignLeft);
    PenBoxLayout->addWidget(penModeChoser,Qt::AlignLeft);
    PenBoxLayout->addWidget(PenSizeName1,Qt::AlignLeft);
    PenBoxLayout->addWidget(penSizeControl,Qt::AlignLeft);
    PenBoxLayout->addWidget(PenSizeName2,Qt::AlignLeft);
    PenBoxLayout->addWidget(penTransParentControl,Qt::AlignLeft);
    //----畫筆設定區(包括UI)初始化----//

    //----橡皮擦設定區初始化----//
    QHBoxLayout *EraserBoxLayout=new QHBoxLayout();
    EraserBoxLayout->setAlignment(Qt::AlignLeft);

    EraserSizeName1=new QLabel("尺寸：10 px");
    EraserSizeName1->setFont(QFont("標楷",10,  QFont::Bold));
    EraserSizeName1->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    EraserSizeName1->setStyleSheet(
        "background-color:rgb(225,225,225);color:rgb(35,35,35);"
        "border-radius: 4px;border-color:rgb(65,65,65);border-width:2px;border-style:solid;"
    );
    EraserSizeName1->setMinimumSize(107,30);
    EraserSizeName1->setMaximumSize(107,30);

    EraserBoxLayout->addWidget(EraserSizeName1,Qt::AlignLeft);
    EraserBoxLayout->addWidget(eraserSizeControl,Qt::AlignLeft);

    EraserBox=new QGroupBox();
    EraserBox->setLayout(EraserBoxLayout);
    //----橡皮擦設定區初始化----//

    //----模糊工具設定區初始化----//
    QHBoxLayout *BlurryBoxLayout=new QHBoxLayout();
    BlurryBoxLayout->setAlignment(Qt::AlignLeft);

    BlurrySizeName=new QLabel("尺寸：10 px");
    BlurrySizeName->setFont(QFont("標楷",10,  QFont::Bold));
    BlurrySizeName->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    BlurrySizeName->setStyleSheet(
        "background-color:rgb(225,225,225);color:rgb(35,35,35);"
        "border-radius: 4px;border-color:rgb(65,65,65);border-width:2px;border-style:solid;"
    );
    BlurrySizeName->setMinimumSize(107,30);
    BlurrySizeName->setMaximumSize(107,30);

    BlurryWeightName=new QLabel("強度： 1");
    BlurryWeightName->setFont(QFont("標楷",10,  QFont::Bold));
    BlurryWeightName->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    BlurryWeightName->setStyleSheet(
        "background-color:rgb(225,225,225);color:rgb(35,35,35);"
        "border-radius: 4px;border-color:rgb(65,65,65);border-width:2px;border-style:solid;"
    );
    BlurryWeightName->setMinimumSize(90,30);
    BlurryWeightName->setMaximumSize(90,30);

    BlurryBoxLayout->addWidget(BlurrySizeName,Qt::AlignLeft);
    BlurryBoxLayout->addWidget(blurrySizeControl,Qt::AlignLeft);
    BlurryBoxLayout->addWidget(BlurryWeightName,Qt::AlignLeft);
    BlurryBoxLayout->addWidget(blurryWeightControl,Qt::AlignLeft);

    BlurryBox=new QGroupBox();
    BlurryBox->setLayout(BlurryBoxLayout);
    //----模糊工具設定區初始化----//


    //----水桶設定區初始化----//
    QHBoxLayout *BucketBoxLayout=new QHBoxLayout();
    BucketBoxLayout->setAlignment(Qt::AlignLeft);

    BucketTransParentName=new QLabel("不透明度：100 %");
    BucketTransParentName->setFont(QFont("標楷",10,  QFont::Bold));
    BucketTransParentName->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    BucketTransParentName->setStyleSheet(
        "background-color:rgb(225,225,225);color:rgb(35,35,35);"
        "border-radius: 4px;border-color:rgb(65,65,65);border-width:2px;border-style:solid;"
    );
    BucketTransParentName->setMinimumSize(170,30);
    BucketTransParentName->setMaximumSize(170,30);

    BucketBox=new QGroupBox();
    BucketBox->setLayout(BucketBoxLayout);
    BucketBoxLayout->addWidget(BucketTransParentName);
    BucketBoxLayout->addWidget(bucketTransParentControl);
    //----水桶設定區初始化----//

    //----拖曳工具設定區初始化----//
    QHBoxLayout *DragBoxLayout=new QHBoxLayout();
    DragBoxLayout->setAlignment(Qt::AlignLeft);
    DragBox=new QGroupBox();
    DragBox->setLayout(DragBoxLayout);
    //----畫筆設定區初始化----//

    //----圖形工具設定區初始化----//
    QHBoxLayout *ShapeBoxLayout=new QHBoxLayout();
    ShapeBoxLayout->setAlignment(Qt::AlignLeft);
    ShapeBox=new QGroupBox();
    ShapeBox->setLayout(ShapeBoxLayout);
    //----畫筆設定區初始化----//

}

void ValueController::SliderUISetting()
{
    penSizeControl->setStyleSheet(
        ""
        ""
    );
}

void ValueController::SliderConnectInit()
{
    connect(penSizeControl,SIGNAL(valueChanged(int)),this,SLOT(valueSet(int)));
    connect(eraserSizeControl,SIGNAL(valueChanged(int)),this,SLOT(valueSet(int)));
    connect(blurrySizeControl,SIGNAL(valueChanged(int)),this,SLOT(valueSet(int)));
    connect(blurryWeightControl,SIGNAL(valueChanged(int)),this,SLOT(valueSet(int)));
    connect(penTransParentControl,SIGNAL(valueChanged(int)),this,SLOT(valueSet(int)));
    connect(bucketTransParentControl,SIGNAL(valueChanged(int)),this,SLOT(valueSet(int)));
}

void ValueController::valueSet(int value)
{
    QSlider *slider=qobject_cast<QSlider*>(sender());

    if(slider==penSizeControl){
        penSize=value;
        PenSizeName1->setText("尺寸："+QString::number(value)+" px");
    }
    if(slider==eraserSizeControl){
        eraserSize=value;
        EraserSizeName1->setText("尺寸："+QString::number(value)+" px");
    }
    if(slider==penTransParentControl){
        transParentValue=value;
        PenSizeName2->setText("不透明度："+QString::number((float)value/255*100,'f',2)+" %");
    }
    if(slider==blurrySizeControl){
        blurrySize=value;
        BlurrySizeName->setText("尺寸："+QString::number(value)+" px");
    }
    if(slider==blurryWeightControl){
        blurryWeight=value;
        BlurryWeightName->setText("強度："+QString::number(value));
    }
    if(slider==bucketTransParentControl){
        transParentValue=value;
        BucketTransParentName->setText("不透明度："+QString::number((float)value/255*100,'f',2)+" %");
    }
}

void ValueController::PenModeChange(int mode)
{

    if(mode==0){
        PenMode=QPainter::CompositionMode_Source;
        PenModeName->setText("模式：覆蓋");
    }
    if(mode==1){
        PenMode=QPainter::CompositionMode_SourceOver;
        PenModeName->setText("模式：疊加");
    }
}
