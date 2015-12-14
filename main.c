#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct local{
    int distance,id,isReachable,color,check;
    struct local *pi;
    struct path *next;
}local;

typedef struct path{
    int weight;
    local *from,*to;
    struct path *next;
}path;

/*Struct for queue, an auxiliary struct to help in BFS algorithm*/
typedef struct Queue{
    local *aut;
    struct Queue *next;
    
}Queue;


void Bellman(local*,int,int,int);
int Relax(local*,local*,int );
void insertBegin(local *,int ,int,int);
void markAll(local *a,int offset);
int BFS(local *a,int Pe);
void insertEnd(local *a);
local *removeBegin();

Queue *front, *rear;

int main(){
    
    int N,C,hQ,i,u,v,w;
    local *vertexList;
    
    if(scanf("%d %d",&N,&C)==1){}
    vertexList=calloc(sizeof(local),N);
    if(scanf("%d",&hQ)==1){}
    for(i=0;i<N;i++){
        (vertexList+i)->distance=INT_MAX;
        (vertexList+i)->pi=NULL;
        (vertexList+i)->id=i+1;
        (vertexList+i)->isReachable=1;
        (vertexList+i)->color=0;
        (vertexList+i)->check=1;
    }
    (vertexList+hQ-1)->distance=0;
    (vertexList+hQ-1)->isReachable=0;
    (vertexList+hQ-1)->check=0;
    
    for(i=0;i<C;i++){
        if(scanf("%d %d %d",&u,&v,&w)==1){}
        insertBegin(vertexList,u,v,w);
        
    }
    /*for(i=0;i<N;i++){
        if((vertexList+i)->next!=NULL){
        path *temp=(vertexList+i)->next;
        while(temp->next!=NULL){
            printf("from:%d to:%d weight:%d\n",temp->from->id,temp->to->id,temp->weight);
            temp=temp->next;
            }
        printf("from:%d to:%d weight:%d\n",temp->from->id,temp->to->id,temp->weight);
        }

    }*/
    Bellman(vertexList,hQ,N,C);

    
    for(i=0;i<N;i++){
        local *temp=(vertexList+i);
        if(temp->isReachable==-1)
                printf("I\n");
        else if(temp->isReachable==0)
                printf("%d\n",(vertexList+i)->distance);
        else if(temp->isReachable==1 && temp->distance==INT_MAX)
            printf("U\n");
    
    }
return 0;    
}



void Bellman(local *vertlist,int hQ,int vertexNumb,int edgeNumb){
    int i,j,finish;
    path *temp;
    
    for(i=0;i<vertexNumb-2;i++){
        finish=0;
        for(j=0;j<vertexNumb;j++){
            if((vertlist+j)->next!=NULL){
                temp=(vertlist+j)->next;
                if((vertlist+j)->check==0){
                    while(temp->next!=NULL){
                        if(Relax(temp->from,temp->to,temp->weight)==0){
                            temp->to->isReachable=0;
                            finish=1;
                            temp->to->check=0;
                        }
                        temp=temp->next;
                    }
                    if(Relax(temp->from,temp->to,temp->weight)==0){
                        temp->to->isReachable=0;
                        finish=1;
                        temp->to->check=0;
                    }
                }
                (vertlist+j)->check=1;
            }
            
        }
            
            
    if(finish==0)
        break;
    }
    
        for(j=0;j<vertexNumb;j++){
            if((vertlist+j)->next!=NULL){
                temp=(vertlist+j)->next;
                while(temp->next!=NULL){
                    if((Relax(temp->from,temp->to,temp->weight)==0)  && (temp->from->isReachable!=-1)){
                         BFS(vertlist,(vertlist+j)->id);
                        temp->to->isReachable=-1;
                    }
                    temp=temp->next;
                }
                if((Relax(temp->from,temp->to,temp->weight)==0) && temp->from->isReachable!=-1){
                    BFS(vertlist,(vertlist+j)->id);
                    temp->to->isReachable=-1;
                }
            }
            
        }
    
    
}


int Relax(local *from,local *to,int weight){
    int dist;
    if(from->distance!=INT_MAX){
        dist=from->distance + weight;
        if(to->distance>weight+ from->distance){
            to->distance=dist;
            to->pi=from;
            return 0;
        }
    }
    return -1;
    
}

void insertBegin(local *vertexList,int offsetFrom,int offsetTo,int w){
    path *newPath;
    local *temp;
    temp=(vertexList+offsetFrom-1);
    newPath=calloc(sizeof(local),1);
    newPath->from=(vertexList+offsetFrom-1);
    newPath->to=(vertexList+offsetTo-1);
    newPath->next=(vertexList+offsetFrom-1)->next;
    newPath->weight=w;
    temp->next=newPath;
    
}

/*BFS algorithm to find the biggest distance from Pe to all other nodes*/
int BFS(local *a,int Pe){
    
    int maxD=0;
    (a+Pe-1)->color=1;
    markAll(a,Pe-1);
    insertEnd(a+Pe-1);
    while(front!=NULL){
            int aux=(removeBegin()->id)-1;
            if((a+aux)->next!=NULL)
                markAll(a,aux);
    }
    return maxD;
    
}

/*Function which marks all of the nodes next to a marking them as passed and putting
them on the queue*/
void markAll(local *a,int offset){
    path *temp=(a+offset)->next;
    (a+offset)->color=1;
    (a+offset)->isReachable=-1;
    while(temp->next!=NULL){
        if(temp->to->color==0){
            insertEnd(temp->to);
            temp->to->isReachable=-1;
            temp->to->color=1;
        }
             temp=temp->next;
    }

     if(temp->to->color==0){
        insertEnd(temp->to);
        temp->to->isReachable=-1;
        temp->to->color=1;
    }

}

/*Inserts a new node of the queue in the end containing the local a*/
void insertEnd(local *a){
    Queue *newQ=(Queue*)calloc(sizeof(Queue),1);
    if(front==NULL){
        newQ->aut=a;
        newQ->next=NULL;
        front=newQ;
        rear=front;
        
        
    }
    else{
        
        newQ->aut=a;
        newQ->next=NULL;
        rear->next=newQ;
        rear=newQ;
    }
    
}

/*Removes a node from the queue and returns the local which was in that node*/
local *removeBegin(){
    local *temp=front->aut;
    Queue *next=front->next;
    free(front);
    front=next;
    return temp;
    
}

