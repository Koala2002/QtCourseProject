#include "valuecontroller.h"


ValueController::ValueController(QStackedWidget *RegionWidget)
{
    widget=RegionWidget;

    //----控制像預設值設定----//
    penSize=10;//畫筆大小
    eraserSize=10;//橡皮擦大小
    blurrySize=10;//模糊工具範圍
    blurryWeight=1;//模糊權重強度
    penTransParentValue=255;//畫筆透明值
    bucketTransParentValue=255;//水桶透明值
    shapeTransParentValue=255;//圖形工具透明度
    shapeWidth=10;//圖形工具邊寬

    shapeLimit=ShapePainter::Solid;//預設為實心
    shape=ShapePainter::Rectangle;//預設為矩形
    PenMode=QPainter::CompositionMode_Source;//畫筆繪圖模式：覆蓋
    //----控制像預設值設定----//

    //----畫筆style預設值設定(雖然應該也只會用這個)----//
    DrawPen.setStyle(Qt::SolidLine);
    DrawPen.setCapStyle(Qt::RoundCap);//不知道
    DrawPen.setJoinStyle(Qt::RoundJoin);//不知道
    //----畫筆style預設值設定(雖然應該也只會用這個)----//

    ColorNow=qRgba(0,0,0,255);//預設顏色為黑色

    ControllerInit();//控制項初始化
    UISetting();//slider控制項UI設定
    ControllerGroupBoxInit();//控制項群組初始化
    SliderConnectInit();//slider 控制項信號槽連結

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


QColor ValueController::getColor(ToolCode code)
{
    QColor returnColor=ColorNow;
    if(code==PenValue)returnColor.setAlpha(penTransParentValue);
    if(code==BucketValue)returnColor.setAlpha(bucketTransParentValue);
    if(code==ShapeValue)returnColor.setAlpha(shapeTransParentValue);
    return returnColor;
}

int ValueController::getBlurryWeight()
{
    return blurryWeight;
}

int ValueController::getShapeWidth()
{
    return shapeWidth;
}

void ValueController::setColor(QColor rgba)
{
    ColorNow=rgba;
}

void ValueController::loadTool(ToolCode code)
{
    if(code==PenValue){
        ColorNow.setAlpha(penTransParentValue);
        DrawPen.setColor(penTransParentValue==0?Qt::transparent:ColorNow);
        DrawPen.setWidth(penSize);
    }
    if(code==EraserValue){
        DrawPen.setColor(Qt::transparent);
        DrawPen.setWidth(eraserSize);
    }
    if(code==BlurryValue){
        DrawPen.setWidth(blurrySize);
    }
    if(code==BucketValue)ColorNow.setAlpha(bucketTransParentValue);
    if(code==ShapeValue)ColorNow.setAlpha(shapeTransParentValue);
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

ShapePainter::ShapeTheme ValueController::ShapeNow()
{
    return shape;
}

ShapePainter::ShapeMode ValueController::ShapeLimit()
{
    return shapeLimit;
}

void ValueController::ControllerInit()
{
    QSlider** slider1[]{
        &penSizeControl,
        &eraserSizeControl,
        &blurrySizeControl,
        &shapeWidthControl
    };
    for(auto &WidthSlider:slider1){
        *WidthSlider=new QSlider(Qt::Horizontal);
        (*WidthSlider)->setMinimumSize(200,10);
        (*WidthSlider)->setMaximumSize(200,10);
        (*WidthSlider)->setMinimum(1);
        (*WidthSlider)->setMaximum(50);
        (*WidthSlider)->setValue(10);
    }

    QSlider **slider2[]{
        &penTransParentControl,
        &bucketTransParentControl,
        &shapeTransParentControl,
    };
    for(auto &TransParentSlider:slider2){
        *TransParentSlider=new QSlider(Qt::Horizontal);
        (*TransParentSlider)->setMinimumSize(200,10);
        (*TransParentSlider)->setMaximumSize(200,10);
        (*TransParentSlider)->setMinimum(0);
        (*TransParentSlider)->setMaximum(255);
        (*TransParentSlider)->setValue(255);
    }

    blurryWeightControl=new QSlider(Qt::Horizontal);
    blurryWeightControl->setMinimumSize(200,10);
    blurryWeightControl->setMaximumSize(200,10);
    blurryWeightControl->setMinimum(1);
    blurryWeightControl->setMaximum(10);
    blurryWeightControl->setValue(1);   

}

void ValueController::ControllerGroupBoxInit()
{

    //----畫筆設定區初始化----//
    QHBoxLayout *PenBoxLayout=new QHBoxLayout();
    PenBoxLayout->setAlignment(Qt::AlignLeft);

    PenBox=new QGroupBox();
    PenBox->setLayout(PenBoxLayout);

    PenBoxLayout->addWidget(PenSizeName1,Qt::AlignLeft);
    PenBoxLayout->addWidget(penSizeControl,Qt::AlignLeft);
    PenBoxLayout->addWidget(PenSizeName2,Qt::AlignLeft);
    PenBoxLayout->addWidget(penTransParentControl,Qt::AlignLeft);
    //----畫筆設定區初始化----//

    //----橡皮擦設定區初始化----//
    QHBoxLayout *EraserBoxLayout=new QHBoxLayout();
    EraserBoxLayout->setAlignment(Qt::AlignLeft);

    EraserBoxLayout->addWidget(EraserSizeName1,Qt::AlignLeft);
    EraserBoxLayout->addWidget(eraserSizeControl,Qt::AlignLeft);

    EraserBox=new QGroupBox();
    EraserBox->setLayout(EraserBoxLayout);
    //----橡皮擦設定區初始化----//


    //----模糊工具設定區初始化----//
    QHBoxLayout *BlurryBoxLayout=new QHBoxLayout();
    BlurryBoxLayout->setAlignment(Qt::AlignLeft);

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


    ShapeChooser->addItem("矩形");
    ShapeChooser->addItem("橢圓");

    ShapeChooser->setIconSize(QSize(20,20));

    ShapeLimitChooser->addItem("實心");
    ShapeLimitChooser->addItem("空心");

    connect(ShapeChooser,SIGNAL(currentIndexChanged(int)),this,SLOT(shapeChange(int)));
    connect(ShapeLimitChooser,SIGNAL(currentIndexChanged(int)),this,SLOT(shapeLimitChange(int)));

    ShapeBox=new QGroupBox();
    ShapeBox->setLayout(ShapeBoxLayout);
    ShapeBoxLayout->addWidget(ShapeName);
    ShapeBoxLayout->addWidget(ShapeChooser);
    ShapeBoxLayout->addWidget(ShapeLimitName);
    ShapeBoxLayout->addWidget(ShapeLimitChooser);


    ShapeBoxLayout->addWidget(ShapeWidthName);


    ShapeBoxLayout->addWidget(shapeWidthControl);
    ShapeBoxLayout->addWidget(ShapeTransParentName);
    ShapeBoxLayout->addWidget(shapeTransParentControl);
    //----畫筆設定區初始化----//

}

void ValueController::UISetting()
{
    //----畫筆控制項UI設定----//
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

    PenSizeName2=new QLabel("不透明度：100.00 %");
    PenSizeName2->setFont(QFont("標楷",10,  QFont::Bold));
    PenSizeName2->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    PenSizeName2->setStyleSheet(
        "background-color:rgb(225,225,225);color:rgb(35,35,35);"
        "border-radius: 4px;border-color:rgb(65,65,65);border-width:2px;border-style:solid;"
    );
    PenSizeName2->setMinimumSize(170,30);
    PenSizeName2->setMaximumSize(170,30);


    //----畫筆控制項UI設定----//

    //----橡皮擦控制項UI設定----//
    EraserSizeName1=new QLabel("尺寸：10 px");
    EraserSizeName1->setFont(QFont("標楷",10,  QFont::Bold));
    EraserSizeName1->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    EraserSizeName1->setStyleSheet(
        "background-color:rgb(225,225,225);color:rgb(35,35,35);"
        "border-radius: 4px;border-color:rgb(65,65,65);border-width:2px;border-style:solid;"
    );
    EraserSizeName1->setMinimumSize(107,30);
    EraserSizeName1->setMaximumSize(107,30);
    //----橡皮擦控制項UI設定----//

    //----模糊工具控制項-UI設定---//
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
    //----模糊工具控制項UI設定----//

    //----水桶控制項UI設定----//
    BucketTransParentName=new QLabel("不透明度：100.00 %");
    BucketTransParentName->setFont(QFont("標楷",10,  QFont::Bold));
    BucketTransParentName->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    BucketTransParentName->setStyleSheet(
        "background-color:rgb(225,225,225);color:rgb(35,35,35);"
        "border-radius: 4px;border-color:rgb(65,65,65);border-width:2px;border-style:solid;"
    );
    BucketTransParentName->setMinimumSize(170,30);
    BucketTransParentName->setMaximumSize(170,30);
    //----水桶控制項UI設定----//

    //----圖形工具控制項UI設定----//
    ShapeName=new QLabel("形狀：矩形");
    ShapeChooser=new QComboBox();

    ShapeName->setFont(QFont("標楷",10,  QFont::Bold));
    ShapeName->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    ShapeName->setStyleSheet(
        "background-color:rgb(225,225,225);color:rgb(35,35,35);"
        "border-radius: 4px;border-color:rgb(65,65,65);border-width:2px;border-style:solid;"
    );
    ShapeName->setMinimumSize(105,30);
    ShapeName->setMaximumSize(105,30);

    ShapeChooser=new QComboBox();

    ShapeChooser->setFont(QFont("標楷",10,  QFont::Bold));
    ShapeChooser->setStyleSheet(
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

    ShapeChooser->setView(new QListView());

    ShapeChooser->setEditable(true);
    ShapeChooser->lineEdit()->setReadOnly(true);
    ShapeChooser->lineEdit()->setAlignment(Qt::AlignCenter);

    ShapeChooser->setMinimumSize(60,30);
    ShapeChooser->setMaximumSize(60,30);

    ShapeLimitName=new QLabel("模式：實心");
    ShapeLimitChooser=new QComboBox();

    ShapeLimitName->setFont(QFont("標楷",10,  QFont::Bold));
    ShapeLimitName->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    ShapeLimitName->setStyleSheet(
        "background-color:rgb(225,225,225);color:rgb(35,35,35);"
        "border-radius: 4px;border-color:rgb(65,65,65);border-width:2px;border-style:solid;"
    );
    ShapeLimitName->setMinimumSize(105,30);
    ShapeLimitName->setMaximumSize(105,30);

    ShapeLimitChooser=new QComboBox();

    ShapeLimitChooser->setFont(QFont("標楷",10,  QFont::Bold));
    ShapeLimitChooser->setStyleSheet(
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

    ShapeLimitChooser->setView(new QListView());

    ShapeLimitChooser->setEditable(true);
    ShapeLimitChooser->lineEdit()->setReadOnly(true);
    ShapeLimitChooser->lineEdit()->setAlignment(Qt::AlignLeft);

    ShapeLimitChooser->setMinimumSize(60,30);
    ShapeLimitChooser->setMaximumSize(60,30);


    ShapeWidthName=new QLabel("邊寬：10 px");
    ShapeWidthName->setFont(QFont("標楷",10,  QFont::Bold));
    ShapeWidthName->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    ShapeWidthName->setStyleSheet(
        "text-align:left;"
        "background-color:rgb(225,225,225);color:rgb(35,35,35);"
        "border-radius: 4px;border-color:rgb(65,65,65);border-width:2px;border-style:solid;"
    );
    ShapeWidthName->setMinimumSize(107,30);
    ShapeWidthName->setMaximumSize(107,30);

    ShapeTransParentName=new QLabel("不透明度：100.00 %");
    ShapeTransParentName->setFont(QFont("標楷",10,  QFont::Bold));
    ShapeTransParentName->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    ShapeTransParentName->setStyleSheet(
        "background-color:rgb(225,225,225);color:rgb(35,35,35);"
        "border-radius: 4px;border-color:rgb(65,65,65);border-width:2px;border-style:solid;"
    );
    ShapeTransParentName->setMinimumSize(170,30);
    ShapeTransParentName->setMaximumSize(170,30);


    //----圖形工具控制項UI設定----//

    //----Slider物件UI設定----//
    QSlider** sliders[]={
        &penSizeControl,//畫筆大小控制項
        &penTransParentControl,//畫筆透明度控制項
        &eraserSizeControl,//橡皮擦大小控制項
        &blurrySizeControl,//模糊區域大小控制項
        &blurryWeightControl,//模糊深度控制項
        &shapeWidthControl,//矩形邊寬控制項
        &shapeTransParentControl,//矩形透明度控制項
        &bucketTransParentControl//水桶透明度控制項
    };
    for(auto &obj:sliders){
        (*obj)->setStyleSheet(
            "QSlider{"
                "min-height: 20px;"
                "max-height: 20px;"
                "background-color: rgba(120,120,120,0);"
                "border: 5px;"
                "color:rgb(200,200,200);"
                "border-radius: 10px;"
            "}"

            "QSlider::groove:horizontal {"
                "border-radius: 5px;"
                "height: 10px;"
                "margin: 20px;"
                "background-color: rgb(150, 150, 150);"
            "}"
            "QSlider::groove:horizontal:hover {"
                "background-color: rgb(150, 150, 150);"
            "}"

            "QSlider::handle:horizontal {"
                "background-color: rgb(50,90,140);"
                "height: 8px;"
                "width: 8px;"
                "margin: -4px;"
                "border-radius: 4px;"
                "padding:=-4px;"
            "}"

            "QSlider::handle:horizontal:hover {"
                "background-color: rgb(100,140,190);"
                "height: 8px;"
                "width: 8px;"
                "margin: -4px;"
                "border-radius: 4px;"
                "padding:=-4px;"
            "}"

            "QSlider::handle:horizontal:pressed {"
                "background-color: rgb(75,115,165);"
                "height: 8px;"
                "width: 8px;"
                "margin: -4px;"
                "border-radius: 4px;"
                "padding:=-4px;"
            "}"
        );
    }
}

void ValueController::SliderConnectInit()
{
    connect(penSizeControl,SIGNAL(valueChanged(int)),this,SLOT(valueSet(int)));
    connect(eraserSizeControl,SIGNAL(valueChanged(int)),this,SLOT(valueSet(int)));
    connect(blurrySizeControl,SIGNAL(valueChanged(int)),this,SLOT(valueSet(int)));
    connect(blurryWeightControl,SIGNAL(valueChanged(int)),this,SLOT(valueSet(int)));
    connect(penTransParentControl,SIGNAL(valueChanged(int)),this,SLOT(valueSet(int)));
    connect(bucketTransParentControl,SIGNAL(valueChanged(int)),this,SLOT(valueSet(int)));
    connect(shapeTransParentControl,SIGNAL(valueChanged(int)),this,SLOT(valueSet(int)));
    connect(shapeWidthControl,SIGNAL(valueChanged(int)),this,SLOT(valueSet(int)));
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
        penTransParentValue=value;
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
        bucketTransParentValue=value;
        BucketTransParentName->setText("不透明度："+QString::number((float)value/255*100,'f',2)+" %");
    }
    if(slider==shapeWidthControl){
        shapeWidth=value;
        ShapeWidthName->setText("邊寬："+QString::number(value));
    }
    if(slider==shapeTransParentControl){
        shapeTransParentValue=value;
        ShapeTransParentName->setText("不透明度："+QString::number((float)value/255*100,'f',2)+" %");
    }
}

void ValueController::shapeChange(int shapeMode)
{
    if(shapeMode==0){
        shape=ShapePainter::Rectangle;
        ShapeName->setText("形狀：矩形");
    }
    if(shapeMode==1){
        shape=ShapePainter::Circle;
        ShapeName->setText("形狀：橢圓");
    }
}

void ValueController::shapeLimitChange(int limit)
{
    if(limit==0){
        shapeLimit=ShapePainter::Solid;
        ShapeLimitName->setText("模式：實心");
    }
    if(limit==1){
        shapeLimit=ShapePainter::Hollow;
        ShapeLimitName->setText("模式：空心");
    }
}
