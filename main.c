#include <stdio.h>
#include <stdlib.h>

typedef struct local{
    int distance,pi;
    struct path *next;


}local;

typedef struct path{
    int weight;
    local *from,*to;
    struct path *next;
}path;


void insertEnd(local *,int ,int,int);

int main(){
    
    int N,C,hQ,i,u,v,w;
    local *vertexList;
    
    if(scanf("%d %d",&N,&C)==1){}
    vertexList=calloc(sizeof(local),N);
    if(scanf("%d",&hQ)==1){}
    for(i=0;i<N;i++){
        if()
    }
    
    for(i=0;i<C;i++){
        if(scanf("%d %d %d",&u,&v,&w)==1){}
        insertEnd(vertexList,u,v,w);
        
    }
    
return 0;    
}



void Bellman(local *list){
    int i;
    for(i=0;i<N;i++){
        local *temp=(list+i)->next;
        while(temp->next!=NULL)
            Relax(temp->from,temp->to,temp->weight);
    } 
    
}


void Relax(local *from,local *to,int weight){
    if()
    
}


void insertEnd(local *list,int offset,int to,int weight){
    path *newPath=calloc(sizeof(path),1);
    newPath->from=list+offset;
    newPath->to=list+to;
    newPath->weight=weight;
    newPath->next=NULL;
    if((list+offset)->next==NULL){
        (list+offset)->next=newPath;
        
    }
    else{
        path *temp=(list+offset)->next;
        while(temp->next!=NULL)
            temp=temp->next;
        temp->next=newPath;
        
    }
        
    
}



