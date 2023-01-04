#include "imagestorage.h"
#include<QDebug>
ImageStorage::ImageStorage(QObject *parent)
    : QObject{parent}
{
    storageSize=0;
    frontImage=NULL;
    backImage=NULL;
    CancelBox=NULL;
}

ImageStorage::~ImageStorage()
{
    while(storageSize>0){
        this->pop_back();
    }
}

void ImageStorage::push(QImage img)
{
    ImageNode *newnode=new ImageNode(img);
    while(CancelBox!=NULL){
        ImageNode* temp=CancelBox;
        CancelBox=CancelBox->next;
        delete temp;
    }
    if(storageSize<storageLimit){

        newnode->next=frontImage;

        if(storageSize>0)frontImage->pre=newnode;

        frontImage=newnode;

        if(storageSize==0)backImage=frontImage;
    }
    else{
        this->pop_back();
        newnode->next=frontImage;
        frontImage->pre=newnode;
        frontImage=newnode;
    }
    storageSize++;//儲存槽內容物加1
}

QImage ImageStorage::front() const
{
    return frontImage->img;
}
ImageNode* ImageStorage::back() const
{
    return backImage;
}

void ImageStorage::pop_front(){
    if(storageSize==0)return;
    ImageNode *temp=frontImage;
    frontImage=frontImage->next;

    if(CancelBox==NULL){
        CancelBox=temp;
        temp->next=NULL;
    }
    else {
        temp->next=CancelBox;
        CancelBox=temp;
    }

    storageSize--;
}

//返回復原的圖片
void ImageStorage::returnBTBSImage()
{
    if(CancelBox==NULL)return;
    ImageNode *temp=CancelBox;
    CancelBox=CancelBox->next;
    temp->next=frontImage;
    frontImage=temp;
    storageSize++;
}

//取得畫布儲存槽現存畫布數量
int ImageStorage::size() const
{
    return storageSize;
}


//畫布總數超出容量，捨去過去的畫布
void ImageStorage::pop_back()
{
    ImageNode *temp=backImage;
    backImage=backImage->pre;
    delete temp;
    storageSize--;
}
