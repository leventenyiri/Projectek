#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "debugmalloc.h"


typedef struct datum
{
    int ev,honap,nap;
}datum;

typedef struct allat
{
    char allat_neve[50];
    int eletkor;
    char betegseg[50];
    datum kkezdet;
    datum kvege;
}allat;

typedef struct listelem_allat
{
    char allat_neve[50];
    int eletkor;
    char betegseg[50];
    datum kkezdet;
    datum kvege;
    struct listelem_allat *prev;
    struct listelem_allat *next;
}listelem_allat;

typedef struct rendeles
{
    char orvos_neve[50];
    datum rendeles_napja;

}rendeles;

typedef struct listelem_rendeles
{
    char orvos_neve[50];
    datum rendeles_napja;
    struct listelem_rendeles *next;
}listelem_rendeles;

listelem_allat* filebol_listaba_A(FILE *p)
{
    p=fopen("ALLATOK.txt","r");
    if(p==NULL)
    return NULL;
    char zs[50];
    listelem_allat *head_a,*q,*g,*strazsa,*tail;
    g=head_a;
    allat a={0};
    int i=0,j=0;
    strazsa=malloc(sizeof(listelem_allat));
    strazsa->prev=NULL;
    tail=malloc(sizeof(listelem_allat));
    tail->next=NULL;
        while(fscanf(p,"%d%d.%d.%d%d.%d.%d",&a.eletkor,&a.kkezdet.ev,&a.kkezdet.honap,&a.kkezdet.nap,&a.kvege.ev,&a.kvege.honap,&a.kvege.nap)==7)
        {                  
            fgets(zs,50,p);
            q=malloc(sizeof(listelem_allat));
            if(j==0)
            {
                head_a=q; 
                g=head_a;
                strazsa->next=head_a;
                head_a->prev=strazsa;
            }
            if(j!=0)
            {
                head_a->next=q;
                q->prev=head_a;
                head_a=head_a->next;
            }
            fgets(a.allat_neve,50,p);
            for(int i=0;a.allat_neve[i-1]!='\n';i++)//Ez arra kell, hogy kivegye a név végéről a '\n'-t
        {   
            if(a.allat_neve[i]=='\0')
            break;
            if(a.allat_neve[i]=='\n')
            {
                a.allat_neve[i]='\0';
                break;
            }
        }
            while(a.allat_neve[i]!=0)
            {
                q->allat_neve[i]=a.allat_neve[i];
                i++;
            }
            q->allat_neve[i]='\0';
            i=0;
            fgets(a.betegseg,50,p);
            for(int i=0;a.betegseg[i-1]!='\n';i++)
        {   
            if(a.betegseg[i]=='\0')
            break;
            if(a.betegseg[i]=='\n')
            {
                a.betegseg[i]='\0';
                break;
            }
        }
            while(a.betegseg[i]!=0)
            {
                q->betegseg[i]=a.betegseg[i];
                i++;
            }
            q->betegseg[i]='\0';
            i=0;
            q->eletkor=a.eletkor;
            q->kkezdet=a.kkezdet;
            q->kvege=a.kvege;
            j++;
        }
        q->next=tail;
        tail->prev=q;
        head_a=g;
        if(fclose(p)!=0)
        printf("Nem sikerult bezarni");
        if(j==0)
        printf("Üres file");
        return strazsa;

}

listelem_rendeles* filebol_listaba_B(FILE  *w)
{
    w=fopen("RENDELES.txt","r");
    if(w==NULL)
    return NULL;
    listelem_rendeles *head_b,*v,*k;
    rendeles b={0};
    int i=0,j=0;
    while(fscanf(w,"%d.%d.%d",&b.rendeles_napja.ev,&b.rendeles_napja.honap,&b.rendeles_napja.nap)==3)
    {
        fgets(b.orvos_neve,50,w); 
        for(int i=0;b.orvos_neve[i-1]!='\n';i++)//Ez arra kell, hogy kivegye a név végéről a '\n'-t
        {   
            if(b.orvos_neve[i]=='\0')
            break;
            if(b.orvos_neve[i]=='\n')
            {
                b.orvos_neve[i]='\0';
                break;
            }
        }
        v=malloc(sizeof(listelem_rendeles));
        if(j==0)
        {
            head_b=v;
            k=v;
        }
        if(j!=0)
        {
            head_b->next=v;
            head_b=head_b->next;
        }
        while(b.orvos_neve[i]!=0)
            {
                v->orvos_neve[i]=b.orvos_neve[i];
                i++;
            }
        v->orvos_neve[i]='\0';
        i=0;
        v->rendeles_napja=b.rendeles_napja;
        j++;
    }
    v->next=NULL;
    head_b=k;
    if(fclose(w)!=0)
    printf("Nem sikerült bezárni");
    if(j==0)
    printf("Üres lista");
    return head_b;
}

char* orvos_beolvaso(char* str)
{
    fgets(str,50,stdin);//A vezeték és keresztnév közti space miatt kell így
    for(int i=0;str[i-1]!='\n';i++)//Ez arra kell, hogy kivegye a név végéről a '\n'-t
    {
        if(str[i]=='\n')
        {
            str[i]='\0';
            break;
        }
    }
    return str;
}

int datum_osszehasonlito(datum a,datum b) 
{   //-1 ha a<b ,1 ha a>b ,0 ha a==b
  if((a.ev)<(b.ev))
  return -1;
  if((a.ev)==(b.ev) && (a.honap)<(b.honap))
  return -1;
  if((a.ev)==(b.ev) && (a.honap)==(b.honap) && (a.nap)<(b.nap))
  return -1;
  if((a.ev)>(b.ev))
  return 1;
  if((a.ev)==(b.ev) && (a.honap)>(b.honap))
  return 1;
  if((a.ev)==(b.ev) && (a.honap)==(b.honap) && (a.nap)>(b.nap))
  return 1;
  if((a.ev)==(b.ev) && (a.honap)==(b.honap) && (a.nap)==(b.nap))
  return 0;
}

void allat_kereso(listelem_rendeles *t,listelem_allat *z,char a[50])
{   
    listelem_allat *temp,*g;
    listelem_allat *head=z;
    int i=0;
    g=head;
    while(t!=NULL)
    {   
        z=head->next;
        if(strcmp(a,t->orvos_neve)==0)
        {
            i++;
            while(z!=NULL)//ha kkezdet<rendeles_napja és kvege>rendeles napja, az azt jelenti, hogy találkoztak
                          //ki kell szedni a listából azokat, akikkel találkozhatott
                {
                
                if(datum_osszehasonlito(z->kkezdet,t->rendeles_napja)==-1 && datum_osszehasonlito(z->kvege,t->rendeles_napja)==1)
                {
                    temp=z;
                    z=z->next;
                    z->prev=temp->prev;
                    temp->prev->next=z;
                    free(temp);                   

                }
                if(z==NULL)
                    break;
                z=z->next;
                
            }
            
        }
        t=t->next; 
    }
    if(i==0)
    {
        printf("Ilyen nevu allatorvos nem dolgozik itt");
        return;
    }
    z=head->next;
    printf("\n");//Ezt csak azért, hogy a beolvasott név után legyen egy sor a terminálban
    while(z->next!=NULL)//Itt írom ki azokat az állatokat, akikkel nem találkozhatott
    {
        printf("%s",z->allat_neve);
        printf("\n");
        z=z->next;
    }
    
    
}

void felszabadito1(listelem_rendeles *rendeles_a)
{
    while(rendeles_a!=NULL)
    {
        listelem_rendeles *temp = rendeles_a->next;
        free(rendeles_a);
        rendeles_a = temp;
    }

}

void felszabadito2(listelem_allat *allat_a)
{
    listelem_allat* temp;
    while(allat_a!=NULL)
        {
                        temp = allat_a;
                       allat_a=allat_a->next;
                        if(allat_a==NULL)
                        break;
                        allat_a->prev=temp->prev;
                        free(temp);
        }
        free(temp);
}

int main()
{
    FILE *p,*w;
    
    listelem_allat *allat_a;
    allat_a=filebol_listaba_A(p); //ezzel a fv-el beolvasom a filebol az adatokat egy lancolt listaba

    listelem_rendeles *rendeles_a;
    rendeles_a=filebol_listaba_B(w);

    char orvos_neve[50];
    char *m;

    m=orvos_beolvaso(orvos_neve);
    
    allat_kereso(rendeles_a,allat_a,orvos_neve);

    //listakat itt felszabaditom, hogy ne szivarogjon a memoria
    felszabadito1(rendeles_a);

    felszabadito2(allat_a);


    return 0;
}