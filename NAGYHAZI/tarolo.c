allat* filebol_tombbe(FILE *p)
{
    allat *t;
    allat a;
    int n=0;
    while(fscanf(p,"%s%d%s%d.%d.%d%d.%d.%d",&a.allat_neve,&a.eletkor,&a.betegseg,&a.kkezdet.ev,&a.kkezdet.honap,&a.kkezdet.nap,&a.kvege.ev,&a.kvege.honap,&a.kvege.nap)==9)
    n++;
    t=malloc(n*sizeof(allat));
    for(int i=0;i<n;i++)
    {
        //while(fscanf(p,"%c",&a.allat_neve)==1);
        //while(fscanf(p,"%c",&a.betegseg)==1);
        
        fscanf(p,"%s%d%s%d.%d.%d%d.%d.%d",&a.allat_neve,&a.eletkor,&a.betegseg,&a.kkezdet.ev,&a.kkezdet.honap,&a.kkezdet.nap,&a.kvege.ev,&a.kvege.honap,&a.kvege.nap);
        t[i]=a;
    }


    while(fscanf(p,"%s%s%d%s%d.%d.%d%d.%d.%d",&a.allat_neve,&a.eletkor,&a.betegseg,&a.kkezdet.ev,&a.kkezdet.honap,&a.kkezdet.nap,&a.kvege.ev,&a.kvege.honap,&a.kvege.nap)==9)
        {
            q=malloc(sizeof(listelem_allat));
            if(j==0)
            head=q;
            if(j!=0)
            head->next=q;
            while(a.allat_neve[i]!=0)
            {
                q->allat_neve[i]=a.allat_neve[i];
                i++;
            }
            q->allat_neve[i]='\0';
            i=0;
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
        q->next=NULL;
        return head;

}



temp=z;
                    z=z->next;
                    g->next->next=z; //itt lesz a baj
                    g=g->next;
                    if(temp->next->next==NULL)
                    {
                        while(g->next!=NULL)
                        g=g->next;
                        g=NULL;
                    }//ha a g->next == NULL,akkor a g legyen NULL
                    free(temp); //temp->prev->next==NULL ezt kene