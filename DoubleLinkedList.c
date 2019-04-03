#include<stdio.h>
#include<stdlib.h>

struct doubleCell{
  double data;
  struct doubleCell * next;
};

typedef struct doubleCell DoubleCell;
typedef DoubleCell* DoubleList;
typedef DoubleCell* Cell_P;

DoubleList addData(DoubleList list,double data);
DoubleList addCell(DoubleList list,Cell_P cell);
DoubleList removeCell(DoubleList list,Cell_P cell);
DoubleList join(DoubleList list1,DoubleList list2);
void printList(DoubleList list);
DoubleList fscanList(FILE * fp,DoubleList list);
Cell_P makeCell(double n);

int main(){
  DoubleList l1=NULL;
  DoubleList l2=NULL;
  printf("NULL=%p\n",l1);
  printf("list=%p\n",l1);

  //連結リスト
  FILE *fp1,*fp2;
  fp1=fopen("DoubleData1","r");
  fp2=fopen("DoubleData2","r");
  l1=fscanList(fp1,l1);
  l2=fscanList(fp2,l2);
  fclose(fp2);
  fclose(fp1);

  printf("リスト1を表示します。\n");
  printList(l1);
  printf("リスト2を表示します。\n");
  printList(l2);
  printf("セルを削除します。\n");
  Cell_P r=l1->next;
  l1=removeCell(l1,r);
  printList(l1);
  printf("リスト1とリスト2を連結します。\n");
  l1=join(l1,l2);
  printList(l1);

  return 0;
}

Cell_P makeCell(double n){
  Cell_P new =(Cell_P)malloc(sizeof(DoubleCell));
  new->data=n;
  return new;
}

DoubleList addData(DoubleList list,double data){
  Cell_P newCell;
  newCell=makeCell(data);
  addCell(list,newCell);
}

DoubleList addCell(DoubleList list,Cell_P cell){
  cell->next=list;
  list=cell;
  return list;
}

DoubleList removeCell(DoubleList list,Cell_P cell){
  Cell_P before=list;
  while(before->next !=cell){
    before=before->next;
  }
  before->next=cell->next;
  free(cell);
  return list;
}

DoubleList join(DoubleList list1,DoubleList list2){
  Cell_P p=list1;
  while(p->next!=NULL){
    p=p->next;
  }
  p->next=list2;
  return list1;
}

void printList(DoubleList list){
  Cell_P p=list;
  printf("[");
  while(p!=NULL){
    printf("%3f,",p->data);
    p=p->next;
  }
  printf("]\n");
}

DoubleList fscanList(FILE * fp,DoubleList list){
  double data;
  while(fscanf(fp,"%lf",&data)!=EOF){
    list=addData(list,data);
  }
  return list;
}
