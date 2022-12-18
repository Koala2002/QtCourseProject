#include "canvasrangeoperator.h"
#include <QDebug>
CanvasRangeOperator::CanvasRangeOperator()
{
    xFirst=NULL;
    xEnd=NULL;
    yFirst=NULL;
    yEnd=NULL;
}

QSize CanvasRangeOperator::MaxRange()
{
    if(xFirst==NULL||yFirst==NULL)return QSize(0,0);
    else return QSize(getXRange(xFirst),getYRange(yFirst));
}

//更新畫布範圍
void CanvasRangeOperator::updateRange(GraphLayerObject *nodeData)
{
    RangeNode *Xcurrent=xFirst;
    while(Xcurrent!=NULL){
        if(Xcurrent->obj==nodeData)break;
        else Xcurrent=Xcurrent->xNext;
    }

    while(Xcurrent!=NULL){
        if(Xcurrent->xNext!=NULL){
            if(getXRange(Xcurrent->xNext)>getXRange(Xcurrent)){
               std::swap(Xcurrent->obj,Xcurrent->xNext->obj);
               Xcurrent=Xcurrent->xNext;
            }
            else break;
        }
        else break;
    }

    while(Xcurrent!=NULL){
        if(Xcurrent->xPre!=NULL){
            if(getXRange(Xcurrent->xPre)<getXRange(Xcurrent)){
               std::swap(Xcurrent->obj,Xcurrent->xPre->obj);
                Xcurrent=Xcurrent->xPre;
            }
            else break;
        }
        else break;
    }

    RangeNode *Ycurrent=yFirst;
    while(Ycurrent!=NULL){
        if(Ycurrent->obj==nodeData)break;
        else Ycurrent=Ycurrent->yNext;
    }

    while(Ycurrent!=NULL){
        if(Ycurrent->yNext!=NULL){
            if(getYRange(Ycurrent->yNext)>getYRange(Ycurrent)){
               std::swap(Ycurrent->obj,Ycurrent->yNext->obj);
               Ycurrent=Ycurrent->yNext;
            }
            else break;
        }
        else break;
    }

    while(Ycurrent!=NULL){
        if(Ycurrent->yPre!=NULL){
            if(getYRange(Ycurrent->yPre)<getYRange(Ycurrent)){
               std::swap(Ycurrent->obj,Ycurrent->yPre->obj);
                Ycurrent=Ycurrent->yPre;
            }
            else break;
        }
        else break;
    }
}

//新增範圍
void CanvasRangeOperator::putRange(GraphLayerObject *nodeData)
{
    RangeNode *XnewNode=new RangeNode(nodeData);
    RangeNode *YnewNode=new RangeNode(nodeData);
    if(xFirst==NULL&&yFirst==NULL){
        xFirst=XnewNode;
        yFirst=YnewNode;
        xEnd=XnewNode;
        yEnd=YnewNode;
    }
    else{
        RangeNode *Xcurrent=xFirst;
        RangeNode *XpreNode=NULL;
        while(Xcurrent!=NULL){
            if(getXRange(Xcurrent)<getXRange(XnewNode))break;
            else{
                XpreNode=Xcurrent;
                Xcurrent=Xcurrent->xNext;
            }
        }
        if(XpreNode==NULL){
            XnewNode->xNext=xFirst;
            xFirst->xPre=XnewNode;
            xFirst=XnewNode;
        }
        else{
            XpreNode->xNext=XnewNode;
            XnewNode->xPre=XpreNode;
            XnewNode->xNext=Xcurrent;
            if(Xcurrent==NULL)xEnd=XnewNode;
            else Xcurrent->xPre=XnewNode;
        }

        RangeNode *Ycurrent=yFirst;
        RangeNode *YpreNode=NULL;
        while(Ycurrent!=NULL){
            if(getYRange(Ycurrent)<getYRange(YnewNode))break;
            else{
                YpreNode=Ycurrent;
                Ycurrent=Ycurrent->yNext;
            }
        }
        if(YpreNode==NULL){
            YnewNode->yNext=yFirst;
            yFirst->yPre=YnewNode;
            yFirst=YnewNode;
        }
        else{
            YpreNode->yNext=YnewNode;
            YnewNode->yPre=YpreNode;
            YnewNode->yNext=Ycurrent;
            if(Ycurrent==NULL)yEnd=YnewNode;
            else Ycurrent->yPre=YnewNode;
        }
    }
}

//刪除範圍
void CanvasRangeOperator::deleteRange(GraphLayerObject *nodeData)
{
    RangeNode *Xcurrent=xFirst;
    RangeNode *XpreNode=NULL;
    while(Xcurrent!=NULL) {
        if(Xcurrent->obj==nodeData){
            RangeNode *temp=Xcurrent;
            if(XpreNode==NULL){
                xFirst=Xcurrent->xNext;
                if(xFirst!=NULL){
                    xFirst->xPre=NULL;
                }
            }
            else{
                XpreNode->xNext=Xcurrent->xNext;
                if(XpreNode->xNext!=NULL){
                    XpreNode->xNext->xPre=XpreNode;
                }
                else{
                    xEnd=XpreNode;
                }
            }
            delete temp;
            break;
        }
        else {
            XpreNode=Xcurrent;
            Xcurrent=Xcurrent->xNext;
        }
    }

    RangeNode *Ycurrent=yFirst;
    RangeNode *YpreNode=NULL;
    while(Ycurrent!=NULL) {
        if(Ycurrent->obj==nodeData){
            RangeNode *temp=Ycurrent;
            if(YpreNode==NULL){
                yFirst=Ycurrent->yNext;
                if(yFirst!=NULL){
                    yFirst->yPre=NULL;
                }
            }
            else{
                YpreNode->yNext=Ycurrent->yNext;
                if(YpreNode->yNext!=NULL){
                    YpreNode->yNext->yPre=YpreNode;
                }
                else{
                    yEnd=YpreNode;
                }
            }
            delete temp;
            break;
        }
        else {
            YpreNode=Ycurrent;
            Ycurrent=Ycurrent->yNext;
        }
    }
}


int CanvasRangeOperator::getXRange(RangeNode *node)
{
    return node->obj->width()+node->obj->x();
}

int CanvasRangeOperator::getYRange(RangeNode *node)
{
    return node->obj->height()+node->obj->y();
}
