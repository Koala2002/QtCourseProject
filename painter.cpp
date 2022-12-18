#include "painter.h"
#include "ui_painter.h"

Painter::Painter(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Painter)
{
    ui->setupUi(this);

    mouse_pressed=false;
    key_pressed=false;

    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);

    ColorNow=qRgba(0,0,0,255);//預設顏色為黑色
    Ptool=DrawPen;//工具初始化為畫筆
    penSize=10;//畫筆大小初始化
    ui->PenSizeControl->setValue(10);//畫筆大小調整工具初始化

    mouse_pre=QPoint(-1,-1);

    setAction();//設定動作
    creatMenu();//創建功能表單
    setColor();//設定調色盤
    setTool();//設定工具
    UISetting();//UI介面設定

    GDisplayer=new GraphLayerDisplayer();
    ui->GraphLayerDisplayerScrollArea->setWidget(GDisplayer->Widget());

    ui->scrollArea->setWidgetResizable(true);//scrollArea內部widget大小自動調整


}

Painter::~Painter()
{
    delete ui;
}

void Painter::setAction(){
    //設定開檔動作
    openFile=new QAction(QStringLiteral("開啟檔案"),this);
    openFile->setShortcut(tr("Ctrl+O"));
    openFile->setStatusTip(QStringLiteral("開啟檔案"));
    connect(openFile,SIGNAL(triggered()),this,SLOT(OpenFile()));

    //設定存檔動作
    saveFile=new QAction(QStringLiteral("儲存檔案"),this);
    saveFile->setShortcut(tr("Ctrl+S"));
    saveFile->setStatusTip(QStringLiteral("儲存檔案"));
    connect(saveFile,SIGNAL(triggered()),this,SLOT(SaveFile()));

    //設定復原動作
    backToPreStep=new QAction(QStringLiteral("復原"),this);
    backToPreStep->setShortcut(tr("Ctrl+Z"));
    backToPreStep->setStatusTip(QStringLiteral("復原"));
    connect(backToPreStep,SIGNAL(triggered()),this,SLOT(BackToPreStep()));

    //設定重做動作
    cancelBackToAction=new QAction(QStringLiteral("重做"),this);
    cancelBackToAction->setShortcut(tr("Ctrl+Y"));
    cancelBackToAction->setStatusTip(QStringLiteral("重做"));
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
}

//設定工具
void Painter::setTool(){
    connect(ui->DrawPen,SIGNAL(clicked()),this,SLOT(ToolChange()));//畫筆信號槽連結
    connect(ui->Eraser,SIGNAL(clicked()),this,SLOT(ToolChange()));//橡皮擦信號槽連結
    connect(ui->Bucket,SIGNAL(clicked()),this,SLOT(ToolChange()));//水桶信號槽連結
    connect(ui->SelectTool,SIGNAL(clicked()),this,SLOT(ToolChange()));//選取工具信號槽連結
}

void Painter::UISetting(){
    ui->scrollArea->setBackgroundRole(QPalette::NoRole);

    //----調色盤預設顏色ui設定----//
    QImage ColorDisplayColor(80,100, QImage::Format_ARGB32);
    ColorDisplayColor.fill(ColorNow);
    ui->ColorDisplayer->setPixmap(QPixmap::fromImage(ColorDisplayColor));
    //----調色盤預設顏色ui設定----//

    //----主視窗顏色設定----//
    this->setStyleSheet("background-color:rgb(65,65,65);");
    //----主視窗顏色設定----//

    //----主視窗內部QPushButton顏色設定----//
    QList<QPushButton*> ButtonList=this->findChildren<QPushButton*>();
    for(auto &child:ButtonList){
        child->setStyleSheet(
            "background-color:rgb(235,235,235);"
            "color:rgb(35,35,35);"
        );
    }
    //----主視窗內部QPushButton顏色設定----//

    //----主視窗內部QScrollArea顏色設定----//
    QList<QScrollArea*> ScrollAreaList=this->findChildren<QScrollArea*>();
    for(auto &child:ScrollAreaList){
        child->setStyleSheet("background-color:rgba(100,100,100,255);");
    }
    //----主視窗內部QScrollArea顏色設定----//

    //----功能選單UI Background Color設定----//
    menuBar()->setStyleSheet(
        "QMenuBar::item{\
            color:rgb(35,35,35);\
            background-color:rgb(235,235,235);\
        }"
        "QMenuBar::item:selected {\
            color:rgb(35,35,35);\
            background-color:rgb(205,205,205);\
        }"
        "QMenuBar::item:pressed {\
            color:rgb(35,35,35);\
            background-color:rgb(205,205,205);\
        }"
    );

    fileMenu->setStyleSheet(
        "QMenu{\
            background-color:rgb(235,235,235);\
        }"
        "QMenu::item{\
            color:rgb(35,35,35);\
            background-color:rgb(235,235,235);\
        }"
        "QMenu::item:selected {\
            color:rgb(35,35,35);\
            background-color:rgb(205,205,205);\
        }"
        "QMenu::item:pressed {\
            color:rgb(35,35,35);\
            background-color:rgb(205,205,205);\
        }"
    );
    toolMenu->setStyleSheet(
        "QMenu{\
            background-color:rgb(235,235,235);\
        }"
        "QMenu::item{\
            color:rgb(35,35,35);\
            background-color:rgb(235,235,235);\
        }"
        "QMenu::item:selected {\
            color:rgb(35,35,35);\
            background-color:rgb(205,205,205);\
        }"
        "QMenu::item:pressed {\
            color:rgb(35,35,35);\
            background-color:rgb(205,205,205);\
        }"
    );
    //----功能選單UI Background Color設定----//
}
//顏色改變
void Painter::ColorChange(){
    QCheckBox *ckBox=qobject_cast<QCheckBox*>(sender());

    if(ckBox==ui->RedColor)ColorNow=qRgba(255,0,0,255);
    if(ckBox==ui->GreenColor)ColorNow=qRgba(0,255,0,255);
    if(ckBox==ui->BlueColor)ColorNow=qRgba(0,0,255,255);
    if(ckBox==ui->PurpleColor)ColorNow=qRgba(255,0,255,255);
    if(ckBox==ui->BlackColor)ColorNow=qRgba(0,0,0,255);
    if(ckBox==ui->YellowColor)ColorNow=qRgba(255,255,0,255);
    if(ckBox==ui->CyanColor)ColorNow=qRgba(0,255,255,255);
    if(ckBox==ui->OrangeColor)ColorNow=qRgba(255,150,0,255);
    if(ckBox==ui->WhiteColor)ColorNow=qRgba(255,255,255,255);
    if(ckBox==ui->PinkColor)ColorNow=qRgba(255,100,150,255);

    QImage ColorDisplayColor(80,100, QImage::Format_ARGB32);
    ColorDisplayColor.fill(ColorNow);
    ui->ColorDisplayer->setPixmap(QPixmap::fromImage(ColorDisplayColor));
}

//工具切換
void Painter::ToolChange(){
    QPushButton *btn=qobject_cast<QPushButton*>(sender());

    if(btn==ui->DrawPen)Ptool=DrawPen;
    if(btn==ui->Eraser)Ptool=Eraser;
    if(btn==ui->Bucket)Ptool=Bucket;
    if(btn==ui->SelectTool)Ptool=SelectTool;
}

//滑鼠按下
void Painter::mousePressEvent(QMouseEvent *event)
{
    if(key_pressed==true)return;
    mouse_pressed=true;
    if(event->buttons()!=Qt::LeftButton)return;
    if(GLayer.Top()==NULL)return;

    getMouse(event);//取得滑鼠座標

    //超出範圍
    if(mouse_now.x()<GLayer.Top()->x()-ui->scrollArea->horizontalScrollBar()->value()||
            mouse_now.y()<GLayer.Top()->y()-ui->scrollArea->verticalScrollBar()->value()){

        return;
    }
    //超出範圍
    if(mouse_now.x()>=GLayer.Top()->width()+GLayer.Top()->x()+ui->scrollArea->horizontalScrollBar()->value()||
            mouse_now.y()>=GLayer.Top()->height()+GLayer.Top()->y()+ui->scrollArea->verticalScrollBar()->value()){

        return;
    }

    if(Ptool==Bucket||Ptool==DrawPen||Ptool==Eraser){//繪圖工具使用
        MousePositionOffset();
        QImage newImage(drawingImage());//畫新圖
        updatingImage(newImage);//更新畫布
    }
    else if(Ptool==SelectTool){//選取工具使用
        if(mouse_pre==QPoint(-1,-1))mouse_pre=mouse_now;
        GLayer.Top()->move(GLayer.Top()->pos()+(mouse_now-mouse_pre));
    }

    mouse_pre=mouse_now;
}

//滑鼠放開
void Painter::mouseReleaseEvent(QMouseEvent *event){
    if(key_pressed==true)return;
    mouse_pressed=false;
    if(mouse_pre==QPoint(-1,-1))return;
    mouse_pre=QPoint(-1,-1);

    if(GLayer.Top()==NULL)return;
    GLayer.Top()->setImage(GLayer.Top()->pixmap()->toImage());
    GLayer.Top()->update(GLayer.Top()->pixmap()->toImage());
}

//滑鼠移動
void Painter::mouseMoveEvent(QMouseEvent *event){
    if(key_pressed==true)return;
    if(mouse_pressed==false)return;
    if(Ptool==Bucket)return;
    if(event->buttons()!=Qt::LeftButton)return;
    if(GLayer.Top()==NULL)return;

    getMouse(event);//取得滑鼠座標

    //超出範圍
    if(mouse_now.x()<GLayer.Top()->x()-ui->scrollArea->horizontalScrollBar()->value()||
            mouse_now.y()<GLayer.Top()->y()-ui->scrollArea->verticalScrollBar()->value()){

        mouse_pre=QPoint(-1,-1);
        return;
    }
    //超出範圍
    if(mouse_now.x()>=GLayer.Top()->width()+GLayer.Top()->x()+ui->scrollArea->horizontalScrollBar()->value()||
            mouse_now.y()>=GLayer.Top()->height()+GLayer.Top()->y()+ui->scrollArea->verticalScrollBar()->value()){

        mouse_pre=QPoint(-1,-1);
        return;
    }

    if(Ptool==DrawPen||Ptool==Eraser){//繪圖工具使用
        MousePositionOffset();
        QImage newImage(drawingImage());//畫新圖
        updatingImage(newImage);//更新畫布
    }
    else if(Ptool==SelectTool){//選取工具使用
        if(mouse_pre==QPoint(-1,-1))mouse_pre=mouse_now;
        GLayer.Top()->move(GLayer.Top()->pos()+(mouse_now-mouse_pre));

        //避免超過下限範圍
        if(GLayer.Top()->x()<0)GLayer.Top()->move(0,GLayer.Top()->y());
        if(GLayer.Top()->y()<0)GLayer.Top()->move(GLayer.Top()->x(),0);
        //避免超過下限範圍

        GLayer.CanvasUpdate(GLayer.Top());
        ui->scrollAreaWidgetContents->setMinimumSize(GLayer.CanvasSize()+QSize(25,25));

    }

    mouse_pre=mouse_now;

}

void Painter::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Control){
        key_pressed=true;
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

        QList<QPushButton*> ButtonList=this->findChildren<QPushButton*>();
        for(auto &child:ButtonList){
            if(child!=ui->MergeGraphLayer){
                child->setEnabled(false);
                child->setStyleSheet(
                    "background-color:rgb(150,150,150);"
                    "color:rgb(35,35,35);"
                );
            }
        }
    }
}

void Painter::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Control){
        key_pressed=false;
        if(GDisplayer->Top()!=NULL){
            while(!selectItemList.empty()){
                selectItemList.top()->setSelectState(false);
                selectItemList.pop();
            }
            GDisplayer->setLayer(GDisplayer->Top());
        }
        QList<QPushButton*> ButtonList=this->findChildren<QPushButton*>();
        for(auto &child:ButtonList){
            child->setEnabled(true);
            child->setStyleSheet(
                "background-color:rgb(235,235,235);"
                "color:rgb(35,35,35);"
            );
        }
    }
}

//存檔
void Painter::SaveFile()
{
    if(GLayer.Top()==NULL)return;
    QString filepath= QFileDialog::getSaveFileName(this, tr("Save File"),"", tr("JPEG (*.jpg *.jpeg);;PNG (*.png)" ));
    if (!filepath.isEmpty()){
        GLayer.Top()->pixmap()->save(filepath);
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

    image=image.convertToFormat(QImage::Format_ARGB32);
    if(GLayer.Top()!=NULL)GLayer.Top()->setImage(image);
    else addGraphLayer(image);

    GDisplayer->Top()->setPixmap(QPixmap::fromImage(image).scaled(100,100, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    GLayer.Top()->setMinimumSize(GLayer.Top()->pixmap()->size());
    GLayer.Top()->setMaximumSize(GLayer.Top()->pixmap()->size());
    ui->scrollAreaWidgetContents->setMinimumSize(GLayer.CanvasSize()+QSize(25,25));
}

//復原
void Painter::BackToPreStep()
{
    if(GLayer.Top()==NULL)return;
    GLayer.Top()->update(GraphLayerObject::UpdateAction::BackStep);//復原
    GDisplayer->Top()->setPixmap(GLayer.Top()->pixmap()->scaled(100,100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

//重做
void Painter::CancelBackToAction()
{
    if(GLayer.Top()==NULL)return;
    GLayer.Top()->update(GraphLayerObject::UpdateAction::Cancel);//重做
    GDisplayer->Top()->setPixmap(GLayer.Top()->pixmap()->scaled(100,100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

//調色盤被點擊
void Painter::on_ColorDisplayer_clicked()
{
    QColor PenColor=QColorDialog::getColor();//選色
    if(!PenColor.isValid())return;//顏色不合理取消後續動作

    ColorNow=PenColor.rgba();//顏色更新

    //----調色盤預設顏色ui設定----//
    QImage ColorDisplayColor(80,100, QImage::Format_ARGB32);
    ColorDisplayColor.fill(ColorNow);
    ui->ColorDisplayer->setPixmap(QPixmap::fromImage(ColorDisplayColor));
    //----調色盤預設顏色ui設定----//
}

//取得滑鼠座飆
void Painter::getMouse(QMouseEvent *event){
    mouse_now=event->globalPos();//先取得滑鼠在ui上的座標
    mouse_now=ui->scrollArea->mapFromGlobal(mouse_now);//將原先儲存的座標轉換成在scrollArea上的座標
}

//滑鼠座標偏移
void Painter::MousePositionOffset(){
    QPoint p=GLayer.Top()->pos();//作畫目標座標

    //----座標偏移----//
    if(Ptool==DrawPen||Ptool==Eraser){
        QScrollBar *Yoffect=ui->scrollArea->verticalScrollBar();
        QScrollBar *Xoffect=ui->scrollArea->horizontalScrollBar();

        mouse_now.setY(mouse_now.y()+Yoffect->value()-p.y());
        mouse_now.setX(mouse_now.x()+Xoffect->value()-p.x());
    }
    //----座標偏移----//
}

//畫圖
QImage Painter::drawingImage(){

    QPixmap pic=*GLayer.Top()->pixmap();//抓取圖片
    QImage sourceImage=pic.toImage();//來源圖片
    QImage destImage(sourceImage.width(), sourceImage.height(), QImage::Format_ARGB32);//轉換圖片
    destImage.fill(Qt::transparent);
    QPainter painter(&destImage);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.drawImage(0, 0, sourceImage);
    painter.setBackgroundMode(Qt::OpaqueMode);
    painter.setBackground(Qt::transparent);
    loadingPen(painter);//讀取畫筆

    if(Ptool==DrawPen||Ptool==Eraser)Draw(&painter);//畫圖
    else if(Ptool==Bucket)BucketDraw(&destImage);
    return destImage;
}

//讀取畫筆
void Painter::loadingPen(QPainter &painter){

    pen.setWidth(penSize);
    if(Ptool==DrawPen){
        pen.setColor(ColorNow);
        painter.setPen(pen);
    }
    else {
        pen.setColor(Qt::transparent);
    }

    painter.setPen(pen);
}

//使用畫筆或橡皮擦作畫
void Painter::Draw(QPainter* painter){

    painter->drawPoint(mouse_now);
    painter->drawLine((mouse_pre==QPoint(-1,-1)?mouse_now:mouse_pre),mouse_now);
}

//使用水桶作畫
void Painter::BucketDraw(QImage* img){
    BucketPainter bucket(img,ColorNow);
    bucket.ColorDiffuse(mouse_now-GLayer.Top()->pos());
}

//更新圖片
void Painter::updatingImage(QImage img){
    GLayer.Top()->setImage(img);
    GDisplayer->Top()->setPixmap(QPixmap::fromImage(img).scaled(100,100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void Painter::addGraphLayer(QImage img,QPoint pos)
{
    GraphLayerObject *newObj=new GraphLayerObject(ui->scrollAreaWidgetContents,&GLayer,img);
    newObj->move(pos);
    GLayer.addGraphLayer(newObj);

    GraphLayerDisplayerItem *layer=new GraphLayerDisplayerItem(GDisplayer,GLayer.Top(),GDisplayer->total());
    GDisplayer->addLayer(layer);
    connect(layer,SIGNAL(clicked()),this,SLOT(on_GraphLayerDisplayerItemClicked()));

    GLayer.Top()->setMinimumSize(GLayer.Top()->pixmap()->size());
    GLayer.Top()->setMaximumSize(GLayer.Top()->pixmap()->size());
    ui->scrollAreaWidgetContents->setMinimumSize(GLayer.CanvasSize()+QSize(25,25));
    ui->scrollArea->horizontalScrollBar()->setValue(0);
    ui->scrollArea->verticalScrollBar()->setValue(0);
}

//合併圖層
void Painter::mergeGraphLayer()
{
    if(selectItemList.size()<=1)return;
    //QSize newGraphLayerSize(0,0);

    QPoint range(0,0);

    QPoint minPos(INT_MAX,INT_MAX);

    std::queue<GraphLayerDisplayerItem*> itemProcess;

    while(!selectItemList.empty()){
        GraphLayerObject *Gobj=selectItemList.top()->getidx();

        minPos.setX(std::min(minPos.x(),Gobj->x()));
        minPos.setY(std::min(minPos.y(),Gobj->y()));

        range.setY(std::max(range.y(),Gobj->y()+Gobj->height()));
        range.setX(std::max(range.x(),Gobj->x()+Gobj->width()));
        itemProcess.push(selectItemList.top());
        selectItemList.pop();
    }

    QImage newImg(range.x()-minPos.x(),range.y()-minPos.y(),QImage::Format_ARGB32);
    QPainter painter(&newImg);
    while(!itemProcess.empty()){
        GraphLayerObject *Gobj=itemProcess.front()->getidx();
        painter.drawImage(Gobj->pos()-minPos,Gobj->pixmap()->toImage());

        GraphLayerDisplayerItem *deleteLayer=itemProcess.front();

        itemProcess.pop();
        deleteLayer->deleteLayer();
    }
    addGraphLayer(newImg,minPos);

}


//畫筆大小改變
void Painter::on_PenSizeControl_valueChanged(int arg1)
{
    penSize=ui->PenSizeControl->value();
}

//圖層管理小圖層顯示物件被點擊
void Painter::on_GraphLayerDisplayerItemClicked()
{
    GraphLayerDisplayerItem *layer=qobject_cast<GraphLayerDisplayerItem*>(sender());
    if(!key_pressed){
        GDisplayer->setLayer(layer);
        GLayer.setLayer(layer->getidx());
        layer->getidx()->raise();
    }
    else {
        //檢查是否已被選取
        if(layer->isSelect()==false){
            selectItemList.push(layer);
            layer->setSelectState(true);
        }
        layer->setStyleSheet(
            "QLabel{\
                border:1px solid red;\
            }"
        );
    }
}


void Painter::on_AddGraphLayer_clicked()
{
    emit addGraphLayer();
}


void Painter::on_MergeGraphLayer_clicked()
{
    emit mergeGraphLayer();
}

