#ifndef IMAGESTORAGE_H
#define IMAGESTORAGE_H

#include <QObject>
#include<QImage>

#define storageLimit 25

class ImageNode: public QImage{
    friend class ImageStorage;
public:
    ImageNode(QImage imgData=QImage(0,0,QImage::Format_ARGB32)){
        img=imgData;
        next=NULL;
        pre=NULL;
    }
private:
    QImage img;
    ImageNode *pre;
    ImageNode *next;
};

//圖片儲存槽
class ImageStorage : public QObject
{
    Q_OBJECT
public:
    explicit ImageStorage(QObject *parent = nullptr);

    void push(QImage img);
    QImage front();
    QImage back();
    void pop_back();
    void pop_front();
    void returnBTBSImage();
    int size();

private:
    int storageSize;
    ImageNode *frontImage;
    ImageNode *backImage;
    ImageNode *CancelBox;
signals:

};

#endif // IMAGESTORAGE_H
