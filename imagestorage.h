#ifndef IMAGESTORAGE_H
#define IMAGESTORAGE_H

#include <QObject>
#include<QImage>

#define storageLimit 25//畫布儲存器儲存上限

class ImageNode: public QImage{
    friend class ImageStorage;
    friend class GraphLayerObject;

public:
    ImageNode(QImage imgData=QImage(0,0,QImage::Format_ARGB32)){
        img=imgData;
        next=NULL;
        pre=NULL;
    }

    QImage Image(){return img;}

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
    QImage front() const;
    ImageNode* back()const;
    void pop_back();
    void pop_front();
    void returnBTBSImage();
    int size() const;

private:
    int storageSize;
    ImageNode *frontImage;
    ImageNode *backImage;
    ImageNode *CancelBox;
signals:

};

#endif // IMAGESTORAGE_H
