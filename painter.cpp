#include "painter.h"
#include "ui_painter.h"

Painter::Painter(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Painter)
{
    ui->setupUi(this);

    //----各事件判斷狀態初值設定----//
    mouse_pressed=false;
    CtrlKeyPressed=false;
    LShiftKeyPressed=false;
    SceneHovered=false;
    //----滑鼠鍵盤按鍵按下初值設定----//

    PainterValueController=new ValueController(ui->ValueControlRegion);


    Ptool=DrawPen;//工具初始化為畫筆
    ui->UseToolIcon->setPixmap(QPixmap::fromImage(QImage(":/icons/brush.png")).scaled(30,30,Qt::KeepAspectRatio));

    mouse_pre=QPointF(-1,-1);//預設前一個滑鼠座標為(-1,-1)

    //----圖層控制器與小圖層顯示物件控制區初始化----//
    GLayer=new GraphLayer(this);
    GDisplayer=new GraphLayerDisplayer();
    ui->GraphLayerDisplayerScrollArea->setWidget(GDisplayer->Widget());
    //----小圖層顯示物件控制區初始化----//

    //----畫布區域初始化----//
    ui->graphicsView->viewport()->installEventFilter(this);
    ui->graphicsView->setMouseTracking(true);
    ui->graphicsView->setScene(GLayer->GraphLayerScene());
    zoomRatio=1.0f;
    //----畫布區域初始化----//

    setAction();//設定動作
    creatMenu();//創建功能表單
    setColor();//設定調色盤
    setTool();//設定工具
    setShape();//設定形狀工具
    UISetting();//UI介面設定
}

Painter::~Painter()
{
    delete ui;
}

void Painter::setAction(){
    //設定開檔動作
    openFile=new QAction(QStringLiteral("開啟檔案"),this);
    openFile->setShortcut(tr("Ctrl+O"));
    connect(openFile,SIGNAL(triggered()),this,SLOT(OpenFile()));

    //設定存檔動作
    saveFile=new QAction(QStringLiteral("儲存檔案"),this);
    saveFile->setShortcut(tr("Ctrl+S"));
    connect(saveFile,SIGNAL(triggered()),this,SLOT(SaveFile()));

    //設定復原動作
    backToPreStep=new QAction(QStringLiteral("復原"),this);
    backToPreStep->setShortcut(tr("Ctrl+Z"));
    connect(backToPreStep,SIGNAL(triggered()),this,SLOT(BackToPreStep()));

    //設定重做動作
    cancelBackToAction=new QAction(QStringLiteral("重做"),this);
    cancelBackToAction->setShortcut(tr("Ctrl+Y"));
    connect(cancelBackToAction,SIGNAL(triggered()),this,SLOT(CancelBackToAction()));

}

void Painter::creatMenu(){
    //將動作加入檔案功能表單
    fileMenu=menuBar()->addMenu(QStringLiteral("檔案"));
    fileMenu->addAction(openFile);
    fileMenu->addAction(saveFile);

    toolMenu=menuBar()->addMenu(QStringLiteral("功能"));
    toolMenu->addAction(backToPreStep);
    toolMenu->addAction(cancelBackToAction);

}

//設定調色盤
void Painter::setColor(){
    //紅色快捷色塊
    ui->RedColor->setStyleSheet(
        "QCheckBox::indicator::unchecked { background-color : rgb(255,0,0); width : 20px; height : 20px; }"
    );
    connect(ui->RedColor,SIGNAL(clicked(bool)),this,SLOT(ColorChange()));

    //綠色快捷色塊
    ui->GreenColor->setStyleSheet(
        "QCheckBox::indicator::unchecked { background-color : rgb(0,255,0); width : 20px; height : 20px; }"
    );
    connect(ui->GreenColor,SIGNAL(clicked(bool)),this,SLOT(ColorChange()));

    //藍色快捷色塊
    ui->BlueColor->setStyleSheet(
        "QCheckBox::indicator::unchecked { background-color : rgb(0,0,255); width : 20px; height : 20px; }"
    );
    connect(ui->BlueColor,SIGNAL(clicked(bool)),this,SLOT(ColorChange()));

    //我也不知道快捷色塊
    ui->PurpleColor->setStyleSheet(
        "QCheckBox::indicator::unchecked { background-color : rgb(255,0,255); width : 20px; height : 20px; }"
    );
    connect(ui->PurpleColor,SIGNAL(clicked(bool)),this,SLOT(ColorChange()));

    //----顏色快速選取區UI設定----//
    ui->BlackColor->setStyleSheet(
        "QCheckBox::indicator::unchecked { background-color : rgb(0,0,0); width : 20px; height : 20px; }"
    );
    connect(ui->BlackColor,SIGNAL(clicked(bool)),this,SLOT(ColorChange()));

    ui->YellowColor->setStyleSheet(
        "QCheckBox::indicator::unchecked { background-color : rgb(255,255,0); width : 20px; height : 20px; }"
    );
    connect(ui->YellowColor,SIGNAL(clicked(bool)),this,SLOT(ColorChange()));

    ui->OrangeColor->setStyleSheet(
        "QCheckBox::indicator::unchecked { background-color : rgb(255,150,0); width : 20px; height : 20px; }"
    );
    connect(ui->OrangeColor,SIGNAL(clicked(bool)),this,SLOT(ColorChange()));

    ui->PinkColor->setStyleSheet(
        "QCheckBox::indicator::unchecked { background-color : rgb(255,100,150); width : 20px; height : 20px; }"
    );
    connect(ui->PinkColor,SIGNAL(clicked(bool)),this,SLOT(ColorChange()));

    ui->WhiteColor->setStyleSheet(
        "QCheckBox::indicator::unchecked { background-color : rgb(255,255,255); width : 20px; height : 20px; }"
    );
    connect(ui->WhiteColor,SIGNAL(clicked(bool)),this,SLOT(ColorChange()));

    ui->CyanColor->setStyleSheet(
        "QCheckBox::indicator::unchecked { background-color : rgb(0,255,255); width : 20px; height : 20px; }"
    );
    connect(ui->CyanColor,SIGNAL(clicked(bool)),this,SLOT(ColorChange()));
    //----顏色快速選取區UI設定----//

}

//設定形狀工具函式連結
void Painter::setShape()
{
    connect(ui->Rectangle,SIGNAL(clicked()),this,SLOT(ShapeChange()));
    connect(ui->Circle,SIGNAL(clicked()),this,SLOT(ShapeChange()));
}

//設定工具函式連結
void Painter::setTool(){
    connect(ui->DrawPen,SIGNAL(clicked()),this,SLOT(ToolChange()));//畫筆信號槽連結
    connect(ui->Eraser,SIGNAL(clicked()),this,SLOT(ToolChange()));//橡皮擦信號槽連結
    connect(ui->Bucket,SIGNAL(clicked()),this,SLOT(ToolChange()));//水桶信號槽連結
    connect(ui->DragTool,SIGNAL(clicked()),this,SLOT(ToolChange()));//拖曳工具信號槽連結
    connect(ui->DrawShape,SIGNAL(clicked()),this,SLOT(ToolChange()));//圖形工具信號槽連接
    connect(ui->BlurryTool,SIGNAL(clicked()),this,SLOT(ToolChange()));//模糊工具信號槽連接

    connect(ui->AddGraphLayer,SIGNAL(clicked()),this,SLOT(addGraphLayer()));
    connect(ui->MergeGraphLayer,SIGNAL(clicked()),this,SLOT(mergeGraphLayer()));
    connect(ui->HideGraphLayer,SIGNAL(clicked()),this,SLOT(hideGraphLayer()));
    connect(ui->DeleteGraphLayer,SIGNAL(clicked()),this,SLOT(deleteGraphLayer()));
    connect(ui->CopyGraphLayer,SIGNAL(clicked()),this,SLOT(copyGraphLayer()));
}

//UI介面設定
void Painter::UISetting(){
    ui->graphicsView->setBackgroundRole(QPalette::NoRole);

    //----工具列Layout內容物對齊----//
    for(int idx=0;idx<ui->ToolLayout->count();idx++){
        ui->ToolLayout->setAlignment(ui->ToolLayout->itemAt(idx)->widget(),Qt::AlignHCenter);
    }
    ui->ZoomRatioLayout->setAlignment(ui->ZoomRatioLayout->itemAt(0)->widget(),Qt::AlignHCenter);
    //----工具列內容物對齊----//

    //----圖形工具形狀快捷鍵顯示UI設定----//
    ui->Rectangle->setStyleSheet("");
    //----圖形工具形狀快捷鍵顯示UI設定----//

    //----調色盤預設顏色ui設定----//
    ui->ColorDisplayer->setText("");
    QColor c(PainterValueController->getColor());
    ui->ColorDisplayer->setStyleSheet(
        "border-radius: 25px;"
        "background-color:rgb("+QString::number(c.red())+","+QString::number(c.green())+","+QString::number(c.blue())+");"
    );
    //----調色盤預設顏色ui設定----//

    //----主視窗顏色設定----//
    this->setStyleSheet("background-color:rgb(65,65,65);");
    //----主視窗顏色設定----//

    //----工作區內部QPushButton顏色設定----//
    QList<QPushButton*> ButtonList=this->findChildren<QPushButton*>();
    for(auto &child:ButtonList){
        if(child==ui->Circle||child==ui->Rectangle){
            child->setStyleSheet(
                "QPushButton {\
                    background-color: rgba(0,0,0,0);\
                    border-radius: 5px;\
                }"

                "QPushButton:hover {\
                    background-color: rgb(55,55,55);\
                }"

                "QPushButton:pressed, QPushButton:checked {\
                    background-color: rgb(45,45,45);\
                }"
            );
            continue;
        }
        if(child==ui->CopyGraphLayer||child==ui->DeleteGraphLayer
            ||child==ui->MergeGraphLayer||child==ui->HideGraphLayer){
            child->setIconSize(QSize(20,20));
            setCloseModeIcon(child);
            child->setEnabled(false);

            child->setStyleSheet(
                "QPushButton {"
                    "background-color: rgb(100,100,100);"
                    "border: 2px solid rgb(200,200,200);"
                    "padding: 10px;"
                    "border-radius: 10px;"
                "}"
            );

            continue;
        }

        child->setIconSize(QSize(20,20));
        setOpenModeIcon(child);
        child->setStyleSheet(
            "QPushButton {"
                "background-color: rgb(25,25,25);"
                "border: 2px solid rgb(245,245,245);"
                "padding: 10px;"
                "border-radius: 10px;"
            "}"

            "QPushButton:hover {"
                "background-color: rgb(55,55,55);"
                "border: 2px solid rgb(255,255,255);"
            "}"

            "QPushButton:pressed {"
                "background-color: rgb(55,55,55);"
                "border: 2px solid rgb(220,220,220);"
            "}"
        );
    }
    //----主視窗內部QPushButton顏色設定----//

    //----主視窗內部QScrollArea顏色設定----//
    QList<QScrollArea*> ScrollAreaList=this->findChildren<QScrollArea*>();
    for(auto &child:ScrollAreaList){
        child->setStyleSheet("background-color:rgba(100,100,100,255)");
    }

    ui->GraphLayerDisplayerScrollArea->verticalScrollBar()->setStyleSheet("QScrollBar {width:0px;}");
    //----主視窗內部QScrollArea顏色設定----//

    //----功能選單UI Background Color設定----//
    menuBar()->setStyleSheet(
        "QMenuBar::item{"
            "color:rgb(35,35,35);"
            "background-color:rgb(235,235,235);"
        "}"
        "QMenuBar::item:selected {"
            "color:rgb(35,35,35);"
            "background-color:rgb(205,205,205);"
        "}"
        "QMenuBar::item:pressed {"
            "color:rgb(35,35,35);"
            "background-color:rgb(205,205,205);"
        "}"
    );

    fileMenu->setStyleSheet(
        "QMenu{"
            "background-color:rgb(235,235,235);"
        "}"
        "QMenu::item{"
            "color:rgb(35,35,35);"
            "background-color:rgb(235,235,235);"
        "}"
        "QMenu::item:selected {"
            "color:rgb(35,35,35);"
            "background-color:rgb(205,205,205);"
        "}"
        "QMenu::item:pressed {"
            "color:rgb(35,35,35);"
            "background-color:rgb(205,205,205);"
        "}"
    );
    toolMenu->setStyleSheet(
        "QMenu{"
            "background-color:rgb(235,235,235);"
        "}"
        "QMenu::item{"
            "color:rgb(35,35,35);"
            "background-color:rgb(235,235,235);"
        "}"
        "QMenu::item:selected {"
            "color:rgb(35,35,35);"
            "background-color:rgb(205,205,205);"
        "}"
        "QMenu::item:pressed {"
            "color:rgb(35,35,35);"
            "background-color:rgb(205,205,205);"
        "}"
    );
    //----功能選單UI Background Color設定----//

    ui->GraphLayerOperatorLayout->setAlignment(Qt::AlignHCenter);

    //----PainterToolBoxLayout 設定----//
    ui->PainterToolBoxLayout->setAlignment(Qt::AlignHCenter);
    //----PainterToolBoxLayout 設定----//

    //----縮放倍率顯示器UI初始化設定----//
    ui->ZoomRatioLayout->setAlignment(Qt::AlignBottom);
    ui->ZoomRatioDisplayer->setText(QString::number(std::round(zoomRatio*10000)/100)+QString("%"));
    ui->ZoomRatioDisplayer->setStyleSheet(
        "background-color:rgba(255,255,255,200);"
    );
    //----縮放倍率顯示器UI設定----//

    //----shape Icon Set----//
    ui->Circle->setIconSize(QSize(20,20));
    ui->Circle->setIcon(QIcon(QPixmap(":/icons/CircleIcon.png")));
    ui->Rectangle->setIconSize(QSize(20,20));
    ui->Rectangle->setIcon(QIcon(QPixmap(":/icons/RectangleIcon.png")));

    //----Icon Set----//
}

//顏色改變
void Painter::ColorChange(){
    QCheckBox *colorBox=qobject_cast<QCheckBox*>(sender());

    if(colorBox==ui->RedColor)PainterValueController->setColor(QColor(255,0,0,255));
    if(colorBox==ui->GreenColor)PainterValueController->setColor(QColor(0,255,0,255));
    if(colorBox==ui->BlueColor)PainterValueController->setColor(QColor(0,0,255,255));
    if(colorBox==ui->PurpleColor)PainterValueController->setColor(QColor(255,0,255,255));
    if(colorBox==ui->BlackColor)PainterValueController->setColor(QColor(0,0,0,255));
    if(colorBox==ui->YellowColor)PainterValueController->setColor(QColor(255,255,0,255));
    if(colorBox==ui->CyanColor)PainterValueController->setColor(QColor(0,255,255,255));
    if(colorBox==ui->OrangeColor)PainterValueController->setColor(QColor(255,150,0,255));
    if(colorBox==ui->WhiteColor)PainterValueController->setColor(QColor(255,255,255,255));
    if(colorBox==ui->PinkColor)PainterValueController->setColor(QColor(255,100,150,255));

    //----調色盤預設顏色ui設定----//
    QColor c(PainterValueController->getColor());
    ui->ColorDisplayer->setStyleSheet(
        "border-radius: 25px;"
        "background-color:rgb("+QString::number(c.red())+","+QString::number(c.green())+","+QString::number(c.blue())+");"
    );
    //----調色盤預設顏色ui設定----//
}

//圖形工具使用形狀改變
void Painter::ShapeChange()
{
    QPushButton *shapeBox=qobject_cast<QPushButton*>(sender());
    if(shapeBox==ui->Rectangle)ShapeTool.setShape(ShapePainter::Rectangle);
    if(shapeBox==ui->Circle)ShapeTool.setShape(ShapePainter::Circle);
}

//工具切換
void Painter::ToolChange(){
    QPushButton *btn=qobject_cast<QPushButton*>(sender());

    if(btn==ui->DrawPen){
        Ptool=DrawPen;
        PainterValueController->setPage(ValueController::PenPage);
        ui->UseToolIcon->setPixmap(QPixmap::fromImage(QImage(":/icons/brush.png")).scaled(30,30,Qt::KeepAspectRatio));
    }
    if(btn==ui->Eraser){
        Ptool=Eraser;
        PainterValueController->setPage(ValueController::EraserPage);
        ui->UseToolIcon->setPixmap(QPixmap::fromImage(QImage(":/icons/eraser.png")).scaled(30,30,Qt::KeepAspectRatio));
    }
    if(btn==ui->Bucket){
        Ptool=Bucket;
        PainterValueController->setPage(ValueController::BucketPage);
        ui->UseToolIcon->setPixmap(QPixmap::fromImage(QImage(":/icons/paint-bucket.png")).scaled(30,30,Qt::KeepAspectRatio));
    }
    if(btn==ui->DragTool){
        Ptool=DragTool;
        PainterValueController->setPage(ValueController::DragPage);
        ui->UseToolIcon->setPixmap(QPixmap::fromImage(QImage(":/icons/drag.png")).scaled(30,30,Qt::KeepAspectRatio));
    }
    if(btn==ui->DrawShape){
        Ptool=DrawShape;
        PainterValueController->setPage(ValueController::ShapePage);
        ui->UseToolIcon->setPixmap(QPixmap::fromImage(QImage(":/icons/shapetool.png")).scaled(30,30,Qt::KeepAspectRatio));
    }
    if(btn==ui->BlurryTool){
        Ptool=Blurry;
        PainterValueController->setPage(ValueController::BlurryPage);
        ui->UseToolIcon->setPixmap(QPixmap::fromImage(QImage(":/icons/blurry.png")).scaled(30,30,Qt::KeepAspectRatio));
    }
}

void Painter::setToolCursor(PainterTools tool)
{
    if(tool==DrawPen)setCursor(QPixmap(":/icons/penCursor.png").scaled(20,20,Qt::KeepAspectRatio));
    if(tool==Eraser)setCursor(QPixmap(":/icons/eraserCursor.png").scaled(20,20,Qt::KeepAspectRatio));
    if(tool==Bucket)setCursor(QPixmap(":/icons/bucketCursor.png").scaled(20,20,Qt::KeepAspectRatio));
    if(tool==DrawShape)setCursor(QPixmap(":/icons/penCursor.png").scaled(20,20,Qt::KeepAspectRatio));
    if(tool==Blurry)setCursor(QPixmap(":/icons/blurryCursor.png").scaled(20,20,Qt::KeepAspectRatio));
    if(tool==DragTool)setCursor(QCursor(Qt::OpenHandCursor));

}

void Painter::setCloseModeIcon(QWidget *obj)
{
    if(obj==ui->DrawPen)ui->DrawPen->setIcon(QIcon(QPixmap(":/icons/Closebrush.png")));
    if(obj==ui->Eraser)ui->Eraser->setIcon(QIcon(QPixmap(":/icons/Closeeraser.png")));
    if(obj==ui->Bucket)ui->Bucket->setIcon(QIcon(QPixmap(":/icons/Closepaint-bucket.png")));
    if(obj==ui->DragTool)ui->DragTool->setIcon(QIcon(QPixmap(":/icons/Closedrag.png")));
    if(obj==ui->DrawShape)ui->DrawShape->setIcon(QIcon(QPixmap(":/icons/Closeshapetool.png")));
    if(obj==ui->BlurryTool)ui->BlurryTool->setIcon(QIcon(QPixmap(":/icons/Closeblurry.png")));
    if(obj==ui->AddGraphLayer)ui->AddGraphLayer->setIcon(QIcon(QPixmap(":/icons/Closeadd.png")));
    if(obj==ui->DeleteGraphLayer)ui->DeleteGraphLayer->setIcon(QIcon(QPixmap(":/icons/Closedelete.png")));
    if(obj==ui->MergeGraphLayer)ui->MergeGraphLayer->setIcon(QIcon(QPixmap(":/icons/Closemerge.png")));
    if(obj==ui->CopyGraphLayer)ui->CopyGraphLayer->setIcon(QIcon(QPixmap(":/icons/Closecopy.png")));
    if(obj==ui->HideGraphLayer)ui->HideGraphLayer->setIcon(QIcon(QPixmap(":/icons/Closehide.png")));
}

void Painter::setOpenModeIcon(QWidget *obj)
{
    if(obj==ui->DrawPen)ui->DrawPen->setIcon(QIcon(QPixmap(":/icons/brush.png")));
    if(obj==ui->Eraser)ui->Eraser->setIcon(QIcon(QPixmap(":/icons/eraser.png")));
    if(obj==ui->Bucket)ui->Bucket->setIcon(QIcon(QPixmap(":/icons/paint-bucket.png")));
    if(obj==ui->DragTool)ui->DragTool->setIcon(QIcon(QPixmap(":/icons/drag.png")));
    if(obj==ui->DrawShape)ui->DrawShape->setIcon(QIcon(QPixmap(":/icons/shapetool.png")));
    if(obj==ui->BlurryTool)ui->BlurryTool->setIcon(QIcon(QPixmap(":/icons/blurry.png")));
    if(obj==ui->AddGraphLayer)ui->AddGraphLayer->setIcon(QIcon(QPixmap(":/icons/add.png")));
    if(obj==ui->DeleteGraphLayer)ui->DeleteGraphLayer->setIcon(QIcon(QPixmap(":/icons/delete.png")));
    if(obj==ui->MergeGraphLayer)ui->MergeGraphLayer->setIcon(QIcon(QPixmap(":/icons/merge.png")));
    if(obj==ui->CopyGraphLayer)ui->CopyGraphLayer->setIcon(QIcon(QPixmap(":/icons/copy.png")));
    if(obj==ui->HideGraphLayer)ui->HideGraphLayer->setIcon(QIcon(QPixmap(":/icons/hide.png")));
}

//事件過濾器，用於過濾graphicView抓取到的事件
bool Painter::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type()==QHoverEvent::Enter){
        SceneHovered=true;
        setToolCursor(Ptool);
        return true;
    }
    if(event->type()==QHoverEvent::Leave){
        SceneHovered=false;
        setCursor(QCursor(Qt::ArrowCursor));
        return true;
    }
    if(event->type()==QEvent::MouseMove){
        QMouseEvent *ent=static_cast<QMouseEvent*>(event);
        Painter::mouseMoveEvent(ent);
        return true;
    }
    if(event->type()==QEvent::MouseButtonPress){
        QMouseEvent *ent=static_cast<QMouseEvent*>(event);
        Painter::mousePressEvent(ent);
        return true;
    }
    if(event->type()==QEvent::MouseButtonRelease){
        QMouseEvent *ent=static_cast<QMouseEvent*>(event);
        Painter::mouseReleaseEvent(ent);
        return true;
    }
    if(event->type()==QEvent::MouseButtonDblClick){
        ui->graphicsView->setFocus();
        QMouseEvent *ent=static_cast<QMouseEvent*>(event);
        Painter::mousePressEvent(ent);
        return true;
    }

    return QObject::eventFilter(obj,event);
}

//滑鼠按下
void Painter::mousePressEvent(QMouseEvent *event)
{

    if(Ptool==DragTool&&SceneHovered==true)setCursor(QCursor(Qt::ClosedHandCursor));
    else if(SceneHovered==false)setCursor(QCursor(Qt::ArrowCursor));

    if(ui->graphicsView->hasFocus()==false)return;
    if(CtrlKeyPressed==true)return;
    mouse_pressed=true;

    if(event->buttons()!=Qt::LeftButton)return;
    if(GLayer->Top()==NULL)return;
    getMouse(event);//取得滑鼠座標

    //超出範圍
    if(mouse_now.x()<GLayer->Top()->x()-ui->graphicsView->horizontalScrollBar()->value()*zoomRatio||
            mouse_now.y()<GLayer->Top()->y()-ui->graphicsView->verticalScrollBar()->value()*zoomRatio){

        mouse_pressed=false;
        return;
    }
    //超出範圍
    if(mouse_now.x()>=GLayer->Top()->width()+GLayer->Top()->x()-ui->graphicsView->horizontalScrollBar()->value()*zoomRatio||
            mouse_now.y()>=GLayer->Top()->height()+GLayer->Top()->y()-ui->graphicsView->verticalScrollBar()->value()*zoomRatio){

        mouse_pressed=false;
        return;
    }

    if(Ptool==Bucket||Ptool==DrawPen||Ptool==Eraser){//繪圖工具使用
        MousePositionOffset();
        QImage newImage(drawingImage());//畫新圖
        updatingImage(newImage);//更新畫布
    }

    if(Ptool==DragTool){//選取工具使用
        if(mouse_pre==QPointF(-1,-1))mouse_pre=mouse_now;
        GLayer->Top()->move(GLayer->Top()->pos()+(mouse_now-mouse_pre).toPoint());
    }

    if(Ptool==DrawShape){
        MousePositionOffset();
        if(mouse_pre==QPointF(-1,-1))mouse_pre=mouse_now;

        ShapeTool.CreatNewShape();
        QImage shapeImg(1,1,QImage::Format_ARGB32_Premultiplied);
        if(ShapeTool.Shape()==ShapePainter::Rectangle)shapeImg.fill(PainterValueController->getColor());
        if(ShapeTool.Shape()==ShapePainter::Circle){
            shapeImg.fill(Qt::transparent);
        }
        ShapeTool.SetNewImage(shapeImg);
        ShapeTool.DrawShapePosMove(mouse_now,mouse_now);
        GLayer->GraphLayerScene()->addWidget(ShapeTool.getDrawShapeLabel())->setZValue(100000);
    }

    if(Ptool==Blurry){
        MousePositionOffset();
        PainterValueController->loadTool(ValueController::BlurryValue);
        QImage newImg=BlurryTool.Blurrying(
            GLayer->Top()->pixmap(Qt::ReturnByValue).toImage(),
            mouse_now.toPoint(),
            PainterValueController->getPen().width(),
            PainterValueController->getBlurryWeight()
        );
        updatingImage(newImg);
    }
    mouse_pre=mouse_now;
}

//滑鼠放開
void Painter::mouseReleaseEvent(QMouseEvent *event){
    if(Ptool==DragTool&&SceneHovered==true)setCursor(QCursor(Qt::OpenHandCursor));
    else if(Ptool==DragTool)setCursor(QCursor(Qt::ArrowCursor));

    if(CtrlKeyPressed==true)return;
    mouse_pressed=false;
    if(GLayer->Top()==NULL)return;
    if(mouse_pre==QPointF(-1,-1)){
        if(GLayer->Top()->pixmap(Qt::ReturnByValue).toImage()!=GLayer->Top()->getPreImage())
            GLayer->Top()->update(GLayer->Top()->pixmap(Qt::ReturnByValue).toImage());
        return;
    }


    if(Ptool==DrawShape){

        //----圖形工具繪圖合併----//
        QImage newImg(GLayer->Top()->size(),QImage::Format_ARGB32_Premultiplied);
        QPainter  painter(&newImg);
        painter.drawImage(0,0,GLayer->Top()->pixmap(Qt::ReturnByValue).toImage());

        getMouse(event);
        MousePositionOffset();
        ShapeTool.DrawShapePosMove(mouse_pre,mouse_now);

        QImage ShapeImage(ShapeTool.DrawShapeImage(mouse_pre,mouse_now));
        if(ShapeTool.Shape()==ShapePainter::Rectangle)ShapeImage.fill(PainterValueController->getColor());
        if(ShapeTool.Shape()==ShapePainter::Circle){
            ShapeImage.fill(Qt::transparent);
            QPainter painter2(&ShapeImage);
            painter2.setPen(QPen(PainterValueController->getColor()));
            painter2.setBrush(QBrush(PainterValueController->getColor()));

            painter2.drawEllipse(0,0,ShapeImage.width()-1,ShapeImage.height()-1);
        }

        painter.drawImage(ShapeTool.DrawShapeDrawPos(mouse_pre,mouse_now)-GLayer->Top()->pos()+QPoint(-1,0),ShapeImage);
        //----圖形工具繪圖合併----//

        //圖片更新
        updatingImage(newImg);
        GLayer->Top()->update(newImg);
        ShapeTool.ShapeComplete();
    }

    if(Ptool==Bucket||Ptool==DrawPen||Ptool==Eraser||Ptool==Blurry){
        GLayer->Top()->update(GLayer->Top()->pixmap(Qt::ReturnByValue).toImage());
    }

    mouse_pre=QPointF(-1,-1);
}

//滑鼠移動
void Painter::mouseMoveEvent(QMouseEvent *event){
    if(ui->graphicsView->hasFocus()==false)return;
    if(CtrlKeyPressed==true)return;
    if(mouse_pressed==false)return;

    if(Ptool==Bucket)return;
    if(event->buttons()!=Qt::LeftButton)return;
    if(GLayer->Top()==NULL)return;

    getMouse(event);//取得滑鼠座標

    //超出範圍
    if(mouse_now.x()<GLayer->Top()->x()-ui->graphicsView->horizontalScrollBar()->value()*zoomRatio||
            mouse_now.y()<GLayer->Top()->y()-ui->graphicsView->verticalScrollBar()->value()*zoomRatio){

        if(Ptool!=DrawShape){
            mouse_pre=QPointF(-1,-1);
            return;
        }
    }
    //超出範圍
    if(mouse_now.x()>=GLayer->Top()->width()+GLayer->Top()->x()-ui->graphicsView->horizontalScrollBar()->value()*zoomRatio||
            mouse_now.y()>=GLayer->Top()->height()+GLayer->Top()->y()-ui->graphicsView->verticalScrollBar()->value()*zoomRatio){

        if(Ptool!=DrawShape){
            mouse_pre=QPointF(-1,-1);
            return;
        }
    }

    if(Ptool==DrawPen||Ptool==Eraser){//繪圖工具使用
        MousePositionOffset();
        QImage newImage(drawingImage());//畫新圖
        updatingImage(newImage);//更新畫布
    }

    if(Ptool==DragTool){//選取工具使用
        if(mouse_pre==QPointF(-1,-1))mouse_pre=mouse_now;
        GLayer->Top()->move(GLayer->Top()->pos()+(mouse_now-mouse_pre).toPoint());

        //避免超過下限範圍
        if(GLayer->Top()->x()<0)GLayer->Top()->move(0,GLayer->Top()->y());
        if(GLayer->Top()->y()<0)GLayer->Top()->move(GLayer->Top()->x(),0);
        //避免超過下限範圍

        GLayer->CanvasUpdate(GLayer->Top());
        GLayer->GraphLayerScene()->setSceneRect(QRect(0,0,GLayer->CanvasSize().width(),GLayer->CanvasSize().height()));

    }

    if(Ptool==DrawShape){//圖形工具使用
        MousePositionOffset();
        ShapeTool.DrawShapePosMove(mouse_pre,mouse_now);//圖形原點校正

        QImage newImg=ShapeTool.DrawShapeImage(mouse_pre,mouse_now);
        if(ShapeTool.Shape()==ShapePainter::Rectangle)newImg.fill(PainterValueController->getColor());
        if(ShapeTool.Shape()==ShapePainter::Circle){
            newImg.fill(Qt::transparent);
            QPainter painter(&newImg);
            painter.setPen(QPen(PainterValueController->getColor()));
            painter.setBrush(QBrush(PainterValueController->getColor()));

            painter.drawEllipse(0,0,newImg.size().width()-1,newImg.size().height()-1);

        }
        ShapeTool.SetSize(newImg.size());
        ShapeTool.SetNewImage(newImg);

        return;
    }

    if(Ptool==Blurry){
        MousePositionOffset();
        PainterValueController->loadTool(ValueController::BlurryValue);
        QImage newImg=BlurryTool.Blurrying(
            GLayer->Top()->pixmap(Qt::ReturnByValue).toImage(),
            mouse_now.toPoint(),
            PainterValueController->getPen().width(),
            PainterValueController->getBlurryWeight()
        );
        updatingImage(newImg);
    }

    mouse_pre=mouse_now;

}

void Painter::wheelEvent(QWheelEvent *event)
{
    if(CtrlKeyPressed==false)return;
    else{
        if(SceneHovered==false)return;
        double ratio=1.15478198;
        if(event->delta()>0&&zoomRatio>0.11){//小數比較所以設下限為0.11避免誤差，實際值為0.1
            ui->graphicsView->scale(ratio,ratio);
            zoomRatio/=ratio;
        }
        else if(event->delta()<0&&zoomRatio<9.0){//小數比較所以設下限為9.0避免誤差，實際值為10.0
            ui->graphicsView->scale(1.0/ratio,1.0/ratio);
            zoomRatio*=ratio;
        }
        ui->ZoomRatioDisplayer->setText(QString::number(std::round((1/zoomRatio)*10000)/100)+QString("%"));
        if(GLayer->Top()==NULL)return;
    }
}

void Painter::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Control){
        if(mouse_pressed==true&&Ptool==DrawShape)return;
        CtrlKeyPressed=true;
        mouse_pre=QPointF(-1,-1);

        ui->graphicsView->verticalScrollBar()->setEnabled(false);
        ui->graphicsView->horizontalScrollBar()->setEnabled(false);

        if(GDisplayer->Top()!=NULL){
            QList<GraphLayerDisplayerItem*> GraphDisplayerItem=GDisplayer->Top()->parent()->findChildren<GraphLayerDisplayerItem*>();

            for(auto &child:GraphDisplayerItem){
                child->setStyleSheet(
                    "QLabel{\
                        border:1px solid rgba(255,255,255,100);\
                    }"
                );                
            }
        }

        //取消所有Button功能使用
        QList<QPushButton*> ButtonList=this->findChildren<QPushButton*>();
        for(auto &child:ButtonList){

            if(child==ui->Circle||child==ui->Rectangle)continue;
            setCloseModeIcon(child);
            child->setEnabled(false);

            child->setStyleSheet(
                "QPushButton {\
                    background-color: rgb(100,100,100);\
                    border: 2px solid rgb(200,200,200);\
                    padding: 10px;\
                    border-radius: 10px;\
                }"
            );
        }

        return;
    }
    if(event->nativeScanCode()==42){//判斷是不是LShift按下
        LShiftKeyPressed=true;
        ShapeTool.setShapeMode(ShapePainter::Square);
    }
}

void Painter::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Control){
        CtrlKeyPressed=false;

        ui->graphicsView->verticalScrollBar()->setEnabled(true);
        ui->graphicsView->horizontalScrollBar()->setEnabled(true);

        if(GDisplayer->Top()!=NULL){
            //----清空選取區內容----//
            while(!selectItemList.empty()){
                selectItemList.top()->setSelectState(false);
                selectItemList.pop();
            }
            //----清空選取區內容----//

            GDisplayer->setLayer(GDisplayer->Top());

        }

        QList<QPushButton*> ButtonList=this->findChildren<QPushButton*>();
        for(auto &child:ButtonList){
            child->setEnabled(true);
            if(child==ui->Circle||child==ui->Rectangle){
                child->setStyleSheet(
                    "QPushButton {\
                        background-color: rgba(0,0,0,0);\
                        border-radius: 5px;\
                    }"

                    "QPushButton:hover {\
                        background-color: rgb(55,55,55);\
                    }"

                    "QPushButton:pressed, QPushButton:checked {\
                        background-color: rgb(45,45,45);\
                    }"
                );
                continue;
            }

            if(child==ui->CopyGraphLayer||child==ui->DeleteGraphLayer
                ||child==ui->MergeGraphLayer||child==ui->HideGraphLayer){
                setCloseModeIcon(child);
                child->setEnabled(false);

                child->setStyleSheet(
                    "QPushButton {\
                        background-color: rgb(100,100,100);\
                        border: 2px solid rgb(200,200,200);\
                        padding: 10px;\
                        border-radius: 10px;\
                    }"
                );
                continue;
            }
            setOpenModeIcon(child);
            child->setStyleSheet(
                "QPushButton {\
                    background-color: rgb(25,25,25);\
                    border: 2px solid rgb(245,245,245);\
                    padding: 10px;\
                    border-radius: 10px;\
                }"

                "QPushButton:hover {\
                    background-color: rgb(55,55,55);\
                    border: 2px solid rgb(255,255,255);\
                }"

                "QPushButton:pressed {\
                    background-color: rgb(55,55,55);\
                    border: 2px solid rgb(200,200,200);\
                }"
            );
        }
        return;
    }

    if(event->nativeScanCode()==42){//判斷是不是LShift放開
        LShiftKeyPressed=false;
        ShapeTool.setShapeMode(ShapePainter::NotLimit);
        return;
    }

}    

//存檔
void Painter::SaveFile()
{
    if(GLayer->Top()==NULL)return;
    QString filepath= QFileDialog::getSaveFileName(this, tr("Save File"),"", tr("JPEG (*.jpg *.jpeg);;PNG (*.png)" ));
    if (!filepath.isEmpty()){
        GLayer->Top()->pixmap(Qt::ReturnByValue).save(filepath);
    }
}


//開檔
void Painter::OpenFile()
{
    QString filepath= QFileDialog::getOpenFileName(
                this,
                "請選擇圖片",
                "新圖片",
                tr("JPEG (*.jpg *.jpeg);;PNG (*.png)"));//取得檔案路徑

    if(filepath.isEmpty())return;//如果檔案路徑是空的


    QImage image(filepath);

    qDebug()<<GLayer->CanvasSize();
    qDebug()<<image.size();
    image=image.convertToFormat(QImage::Format_ARGB32_Premultiplied);
    if(GLayer->Top()!=NULL){
        updatingImage(image);
        GLayer->Top()->update(GLayer->Top()->pixmap(Qt::ReturnByValue).toImage());
    }
    else addGraphLayer(image);

    GLayer->Top()->setMinimumSize(GLayer->Top()->pixmap(Qt::ReturnByValue).size());
    GLayer->Top()->setMaximumSize(GLayer->Top()->pixmap(Qt::ReturnByValue).size());
    GLayer->CanvasUpdate(GLayer->Top());
    qDebug()<<GLayer->CanvasSize();
    GLayer->GraphLayerScene()->setSceneRect(QRect(0,0,GLayer->CanvasSize().width(),GLayer->CanvasSize().height()));


}

//復原
void Painter::BackToPreStep()
{
    if(GLayer->Top()==NULL)return;
    GLayer->Top()->update(GraphLayerObject::UpdateAction::BackStep);//復原
    GDisplayer->Top()->setPixmap(GLayer->Top()->pixmap(Qt::ReturnByValue).scaled(100,100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    GLayer->Top()->setMinimumSize(GLayer->Top()->pixmap(Qt::ReturnByValue).size());
    GLayer->Top()->setMaximumSize(GLayer->Top()->pixmap(Qt::ReturnByValue).size());
    GLayer->GraphLayerScene()->setSceneRect(QRect(0,0,GLayer->CanvasSize().width(),GLayer->CanvasSize().height()));
}

//重做
void Painter::CancelBackToAction()
{
    if(GLayer->Top()==NULL)return;
    GLayer->Top()->update(GraphLayerObject::UpdateAction::Cancel);//重做
    GDisplayer->Top()->setPixmap(GLayer->Top()->pixmap(Qt::ReturnByValue).scaled(100,100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    GLayer->Top()->setMinimumSize(GLayer->Top()->pixmap(Qt::ReturnByValue).size());
    GLayer->Top()->setMaximumSize(GLayer->Top()->pixmap(Qt::ReturnByValue).size());
    GLayer->GraphLayerScene()->setSceneRect(QRect(0,0,GLayer->CanvasSize().width(),GLayer->CanvasSize().height()));
}

//調色盤被點擊
void Painter::on_ColorDisplayer_clicked()
{
    QColor PenColor=QColorDialog::getColor();//選色
    if(!PenColor.isValid())return;//顏色不合理取消後續動作

    PainterValueController->setColor(PenColor);//顏色更新

    //----調色盤預設顏色ui設定----//
    QColor c(PainterValueController->getColor());
    ui->ColorDisplayer->setStyleSheet(
        "border-radius: 25px;"
        "background-color:rgb("+QString::number(c.red())+","+QString::number(c.green())+","+QString::number(c.blue())+");"
    );
    //----調色盤預設顏色ui設定----//
}

//取得滑鼠座飆
void Painter::getMouse(QMouseEvent *event){
    mouse_now=event->screenPos();//先取得滑鼠在ui上的座標

    //----畫布原點坐標計算----//
    QPointF GraphViewPosFromGlobal=mapToGlobal(ui->graphicsView->pos());
    GraphViewPosFromGlobal.setY(GraphViewPosFromGlobal.y()+25);
   //----畫布原點坐標計算----//

    mouse_now=(mouse_now-GraphViewPosFromGlobal)*zoomRatio;//將原先儲存的座標轉換成在scrollArea上的座標
}

//滑鼠座標偏移
void Painter::MousePositionOffset(){
    QPointF DrawPos=GLayer->Top()->pos();//作畫目標座標
    QPointF scrollBarOffset(ui->graphicsView->horizontalScrollBar()->value(),ui->graphicsView->verticalScrollBar()->value());

    //----座標偏移----//   
    if(Ptool!=DrawShape)mouse_now-=DrawPos;
    mouse_now+=(scrollBarOffset*zoomRatio);

    mouse_now.setX(std::floor(mouse_now.x())-(Ptool==DrawShape?0:1));
    mouse_now.setY(std::floor(mouse_now.y()));
    //----座標偏移----//
}

//畫圖
QImage Painter::drawingImage(){

    QPixmap pic=GLayer->Top()->pixmap(Qt::ReturnByValue);//抓取圖片
    QImage sourceImage=pic.toImage();//來源圖片
    QImage destImage(sourceImage.width(), sourceImage.height(), QImage::Format_ARGB32_Premultiplied);//轉換圖片
    destImage.fill(Qt::transparent);
    QPainter painter(&destImage);
    if(Ptool!=Eraser)painter.setCompositionMode(PainterValueController->getPenMode());
    else painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.drawImage(0, 0, sourceImage);
    painter.setBackgroundMode(Qt::OpaqueMode);
    painter.setBackground(Qt::transparent);

    if(Ptool==DrawPen||Ptool==Eraser){
        PainterValueController->loadTool((Ptool==DrawPen)?ValueController::PenValue:ValueController::EraserValue);//讀取畫筆資料
        painter.setPen(PainterValueController->getPen());
        Draw(&painter);//畫圖
    }
    if(Ptool==Bucket)BucketDraw(&destImage);
    return destImage;
}


//使用畫筆或橡皮擦作畫
void Painter::Draw(QPainter* painter){

    painter->drawPoint(mouse_now);
    painter->drawLine((mouse_pre==QPointF(-1,-1)?mouse_now:mouse_pre),mouse_now);
}

//使用水桶作畫
void Painter::BucketDraw(QImage* img){
    PainterValueController->loadTool(ValueController::BucketValue);
    BucketPainter bucket(img,PainterValueController->getColor());
    bucket.ColorDiffuse(mouse_now.toPoint());
}

//更新圖片
void Painter::updatingImage(QImage img){
    GLayer->Top()->setImage(img);
    GDisplayer->Top()->setPixmap(QPixmap::fromImage(img).scaled(100,100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void Painter::addGraphLayer(QImage img,QPoint pos)
{
    GraphLayerObject *newObj=new GraphLayerObject(GLayer,img);

    newObj->move(pos);
    GLayer->addGraphLayer(newObj);
    QGraphicsProxyWidget *PainterDrawRegionWidget=GLayer->GraphLayerScene()->addWidget(newObj);
    GraphLayerDisplayerItem *layer=new GraphLayerDisplayerItem(GDisplayer,GLayer->Top(),PainterDrawRegionWidget,GDisplayer->total());
    GDisplayer->addLayer(layer);
    connect(layer,SIGNAL(clicked()),this,SLOT(on_GraphLayerDisplayerItemClicked()));

    GLayer->Top()->setMinimumSize(GLayer->Top()->pixmap(Qt::ReturnByValue).size());
    GLayer->Top()->setMaximumSize(GLayer->Top()->pixmap(Qt::ReturnByValue).size());

    if(pos.x()==0)ui->graphicsView->horizontalScrollBar()->setValue(0);
    if(pos.y()==0)ui->graphicsView->verticalScrollBar()->setValue(0);
    newObj->setMouseTracking(true);
    layer->getWidgetIdx()->setZValue(GLayer->layerDepth()++);
    GLayer->GraphLayerScene()->setSceneRect(QRect(0,0,GLayer->CanvasSize().width(),GLayer->CanvasSize().height()));//視窗自動調整大小

    ui->graphicsView->setFocus();
}

void Painter::hideGraphLayer()
{
    if(selectItemList.size()<1)return;

    while(!selectItemList.empty()){
        selectItemList.top()->hideLayer();
        selectItemList.top()->setSelectState(false);
        selectItemList.pop();
    }

    //----圖層按鈕重設----//
    for(int a=0;a<ui->GraphLayerOperatorLayout->count();a++){
        ui->GraphLayerOperatorLayout->itemAt(a)->widget()->setEnabled(false);
        setCloseModeIcon(ui->GraphLayerOperatorLayout->itemAt(a)->widget());
        ui->GraphLayerOperatorLayout->itemAt(a)->widget()->setStyleSheet(
            "QPushButton {"
                "background-color: rgb(100,100,100);"
                "border: 2px solid rgb(200,200,200);"
                "padding: 10px;"
                "border-radius: 10px;"
            "}"
        );
    }
    //----圖層按鈕重設----//
}

void Painter::deleteGraphLayer(){
    if(selectItemList.size()<1)return;

    while(!selectItemList.empty()){
        selectItemList.top()->deleteLayer();
        selectItemList.pop();
    }

    //----圖層按鈕重設----//
    for(int a=0;a<ui->GraphLayerOperatorLayout->count();a++){
        ui->GraphLayerOperatorLayout->itemAt(a)->widget()->setEnabled(false);
        setCloseModeIcon(ui->GraphLayerOperatorLayout->itemAt(a)->widget());
        ui->GraphLayerOperatorLayout->itemAt(a)->widget()->setStyleSheet(
            "QPushButton {"
                "background-color: rgb(100,100,100);"
                "border: 2px solid rgb(200,200,200);"
                "padding: 10px;"
                "border-radius: 10px;"
            "}"
        );
    }
    //----圖層按鈕重設----//
}

void Painter::copyGraphLayer(){
    if(selectItemList.size()<1)return;

    std::stack<GraphLayerDisplayerItem*> items;
    while(!selectItemList.empty()){
        items.push(selectItemList.top());
        selectItemList.top()->setSelectState(false);
        selectItemList.pop();
    }

    while(!items.empty()){
        addGraphLayer(items.top()->getIdx()->pixmap(Qt::ReturnByValue).toImage(),items.top()->getIdx()->pos());
        *(GLayer->Top())=*(items.top()->getIdx());
        items.pop();
    }

    //----圖層按鈕重設----//
    for(int a=0;a<ui->GraphLayerOperatorLayout->count();a++){
        setCloseModeIcon(ui->GraphLayerOperatorLayout->itemAt(a)->widget());
        ui->GraphLayerOperatorLayout->itemAt(a)->widget()->setEnabled(false);
        ui->GraphLayerOperatorLayout->itemAt(a)->widget()->setStyleSheet(
            "QPushButton {"
                "background-color: rgb(100,100,100);"
                "border: 2px solid rgb(200,200,200);"
                "padding: 10px;"
                "border-radius: 10px;"
            "}"
        );
    }
    //----圖層按鈕重設----//
}

//合併圖層
void Painter::mergeGraphLayer()
{
    if(selectItemList.size()<=1)return;
    //QSize newGraphLayerSize(0,0);

    QPoint range(0,0);

    //----找出最左上放的點----//
    QPoint minPos(INT_MAX,INT_MAX);

    std::queue<GraphLayerDisplayerItem*> itemProcess;

    while(!selectItemList.empty()){
        GraphLayerObject *Gobj=selectItemList.top()->getIdx();

        minPos.setX(std::min(minPos.x(),Gobj->x()));
        minPos.setY(std::min(minPos.y(),Gobj->y()));

        range.setY(std::max(range.y(),Gobj->y()+Gobj->height()));
        range.setX(std::max(range.x(),Gobj->x()+Gobj->width()));
        itemProcess.push(selectItemList.top());
        selectItemList.pop();
    }
    //----找出最左上放的點----//

    //----合併----//
    QImage newImg(range.x()-minPos.x(),range.y()-minPos.y(),QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&newImg);
    while(!itemProcess.empty()){
        GraphLayerObject *Gobj=itemProcess.front()->getIdx();
        painter.drawImage(Gobj->pos()-minPos,Gobj->pixmap(Qt::ReturnByValue).toImage());

        GraphLayerDisplayerItem *deleteLayer=itemProcess.front();

        itemProcess.pop();

        deleteLayer->deleteLayer();
    }
    //----合併----//

    addGraphLayer(newImg,minPos);

    //----加入合併的圖層後先預設關閉小圖層的功能按鈕使用----//
    GDisplayer->Top()->setStyleSheet(
        "QLabel{"
            "border:1px solid rgba(255,255,255,100);"
        "}"
    );

    //----加入合併的圖層後先預設關閉小圖層的功能按鈕使用----//

    //----圖層按鈕重設----//
    for(int a=0;a<ui->GraphLayerOperatorLayout->count();a++){
        setCloseModeIcon(ui->GraphLayerOperatorLayout->itemAt(a)->widget());
        ui->GraphLayerOperatorLayout->itemAt(a)->widget()->setEnabled(false);
        ui->GraphLayerOperatorLayout->itemAt(a)->widget()->setStyleSheet(
            "QPushButton {"
                "background-color: rgb(100,100,100);"
                "border: 2px solid rgb(200,200,200);"
                "padding: 10px;"
                "border-radius: 10px;"
            "}"
        );
    }
    //----圖層按鈕重設----//

}

//圖層管理小圖層顯示物件被點擊
void Painter::on_GraphLayerDisplayerItemClicked()
{
    GraphLayerDisplayerItem *layer=qobject_cast<GraphLayerDisplayerItem*>(sender());
    if(!CtrlKeyPressed){
        GDisplayer->setLayer(layer);
        GLayer->setLayer(layer->getIdx());

        //----圖層上下關係設定----/
        layer->getWidgetIdx()->setZValue(GLayer->layerDepth()++);
        //----圖層上下關係設定----//
    }
    else {
        //檢查是否已被選取
        if(layer->isSelect()==false){
            selectItemList.push(layer);
            layer->setSelectState(true);
            if(selectItemList.size()>=1){
                setOpenModeIcon(ui->HideGraphLayer);
                ui->HideGraphLayer->setEnabled(true);
                ui->HideGraphLayer->setStyleSheet(
                    "QPushButton {"
                        "background-color: rgb(35,35,35);"
                        "border: 1px solid rgb(255,255,255);"
                        "padding: 10px;"
                        "border-radius: 10px;"
                    "}"

                    "QPushButton:hover {"
                        "background-color: rgb(55,55,55);"
                        "border: 1px solid rgb(255,255,255);"
                    "}"

                    "QPushButton:pressed {"
                        "background-color: rgb(55,55,55);"
                        "border: 1px solid rgb(200,200,200);"
                    "}"
                );
                setOpenModeIcon(ui->CopyGraphLayer);
                ui->CopyGraphLayer->setEnabled(true);
                ui->CopyGraphLayer->setStyleSheet(
                    "QPushButton {"
                        "background-color: rgb(35,35,35);"
                        "border: 1px solid rgb(255,255,255);"
                        "padding: 10px;"
                        "border-radius: 10px;"
                    "}"

                    "QPushButton:hover {"
                        "background-color: rgb(55,55,55);"
                        "border: 1px solid rgb(255,255,255);"
                    "}"

                    "QPushButton:pressed {"
                        "background-color: rgb(55,55,55);"
                        "border: 1px solid rgb(200,200,200);"
                    "}"
                );

                setOpenModeIcon(ui->DeleteGraphLayer);
                ui->DeleteGraphLayer->setEnabled(true);
                ui->DeleteGraphLayer->setStyleSheet(
                    "QPushButton {"
                        "background-color: rgb(35,35,35);"
                        "border: 1px solid rgb(255,255,255);"
                        "padding: 10px;"
                        "border-radius: 10px;"
                    "}"

                    "QPushButton:hover {"
                        "background-color: rgb(55,55,55);"
                        "border: 1px solid rgb(255,255,255);"
                    "}"

                    "QPushButton:pressed {"
                        "background-color: rgb(55,55,55);"
                        "border: 1px solid rgb(200,200,200);"
                    "}"
                );
            }
            if(selectItemList.size()>=2){
                setOpenModeIcon(ui->MergeGraphLayer);
                ui->MergeGraphLayer->setEnabled(true);
                ui->MergeGraphLayer->setStyleSheet(
                    "QPushButton {"
                        "background-color: rgb(35,35,35);"
                        "border: 2px solid rgb(255,255,255);"
                        "padding: 10px;"
                        "border-radius: 10px;"
                    "}"

                    "QPushButton:hover {"
                        "background-color: rgb(55,55,55);"
                        "border: 2px solid rgb(255,255,255);"
                    "}"

                    "QPushButton:pressed {"
                        "background-color: rgb(55,55,55);"
                        "border: 2px solid rgb(200,200,200);"
                    "}"
                );
            }
        }
        layer->setStyleSheet(
            "QLabel{"
                "border:1px solid red;"
            "}"
        );
    }
}



