#include <stdio.h>
#include <stdlib.h>
#include "master_ceng.h"

char pl_names[4][10] = {
    "C",
    "C++",
    "Python",
    "Java"};


void insert_instructor(Instructor **list, char *name, float *pl_ratings)
{
     int i=0;
    char *p=name;
    
    while ((*p)!='\0')
    {
        i++;
        p++;
    }

       
    if ( (*list)==NULL)
    {
        int z=0;
  
        *list=(Instructor *)malloc(  sizeof(Instructor)    );
        (*list)->instructor_name= (char *) malloc( (i+1)*sizeof(char)   );

       for ( z = 0; z < i+1; z++)
       {
           (*list)->instructor_name[z]=name[z];
       }
    
        (*list)->pl_ratings=(float *) malloc(4*sizeof(float));

        for ( z = 0; z < 4; z++)
        {
            (*list)->pl_ratings[z]=pl_ratings[z];
        }

        (*list)->next=NULL;
        return;
    }

    else{
        
        int z=0;
        Instructor *ptr=*list;
        
        while ( (ptr->next)!=NULL )
        {
            ptr=ptr->next;
        }

        ptr->next=(Instructor *)malloc(  sizeof(Instructor) );
        ptr->next->instructor_name= (char *) malloc( (i+1)*sizeof(char));

        for ( z = 0; z < i+1; z++)
        {
           ptr->next->instructor_name[z]=name[z];
        } 
    
        ptr->next->pl_ratings=(float *) malloc(4*sizeof(float));

        for (z= 0; z < 4; z++)
        {
            ptr->next->pl_ratings[z]=pl_ratings[z];
        }
        ptr->next->next=NULL;
        return;
    }
    
}


void insert_submission(Submission **list, char *name, int *pl_list)
{
    int i=0;
    char *ptr=name;
    while ((*ptr)!='\0')
    {
        i++;
        ptr++;
    }
    
    if (  (*list)==NULL)
    {
        int t,z;
        *list= (Submission *) malloc(sizeof( Submission  ));
        (*list)->next=NULL;
        (*list)->student_name=(char *) malloc( (i+1)*sizeof(char) );
        for ( z = 0; z < i; z++)
        {
            (*list)->student_name[z]=name[z];
           
        }
        (*list)->student_name[i]='\0';
        (*list)->projects= (Project *) malloc(5*sizeof(Project));
        for ( t = 0; t < 5; t++)
        {
             ((*list)->projects + t)->pl_index =pl_list[t] ;
        }
        return;
    }
   
    else{
        int t,z;
        Submission *p=*list;
        while(p->next!=NULL){
            p=p->next;
        }
        p->next= (Submission *) malloc( sizeof(Submission) );
        p->next->next=NULL;
        p->next->student_name = (char *) malloc( (i+1)*sizeof(char) );
        for ( z = 0; z < i+1; z++)
        {
            p->next->student_name[z]=name[z];
        }
        p->next->projects = (Project *) malloc(5*sizeof(Project));
        for ( t = 0; t < 5; t++)
        {
            ( p->next->projects + t)->pl_index =pl_list[t] ;
        }
    }
}


Score *calculate_submission_scores(Instructor *instructions, Submission *submissions, int **juries, int jury_size)
{
    Score * ptr=NULL;
    int i=1,t=0;
    
    Submission *tmp=submissions;

    while (tmp!=NULL)
    {
        char *haha;
        int size=0, it=0;
        
        
        if ( tmp==submissions )
        {
            ptr=(Score *)  malloc( sizeof(Score) );
        }

        else{
            ptr = (Score *)    realloc(ptr, i*sizeof(Score) );
        }
        
        haha = tmp->student_name;

        while( (*haha)!='\0'){
            haha++;
            size++;
        }
        
        (ptr+(i-1) )->student_name = malloc( (size+1)*sizeof(char) );
        
        for(it=0; it<size+1; it++){
            (ptr+(i-1))->student_name[it]=tmp->student_name[it];
            
        }
        
        for ( t = 0; t <jury_size ; t++)
        {
            int k=0;
            Instructor *ttt=instructions;
            for( ; k< juries[i-1][t]; k++){
                ttt=ttt->next;
            }
            (ptr+i-1)->score+= ttt->pl_ratings[ tmp->projects->pl_index ] ;
            (ptr+i-1)->score+= ttt->pl_ratings[((tmp->projects)+1)->pl_index] ;
            (ptr+i-1)->score+= ttt->pl_ratings[((tmp->projects)+2)->pl_index] ;
            (ptr+i-1)->score+= ttt->pl_ratings[((tmp->projects)+3)->pl_index] ;
            (ptr+i-1)->score+= ttt->pl_ratings[((tmp->projects)+4)->pl_index] ;
        }

        tmp=tmp->next;
        i++;
    }
    return ptr;
}


float find_average_score(Score *scores, Submission *submissions)
{
    float result=0;
    Submission *ptr=submissions;
    Score *t=scores;
    int i=0;
    while (ptr!=NULL)
    {
        result+=t->score;
        i++;
        ptr=ptr->next;
        t++;
    }
    return result/(float)i;
}

Score find_winner(Score *scores, Submission *submissions)
{
    Score winner=*scores;
    Score *ptr=scores;
    float result=scores->score;
    Submission *tmp=submissions;

    while (tmp!=NULL)
    {
        if ( result < ptr->score )
        {
            winner= *ptr;
            result=ptr->score;
        }
        
        tmp=tmp->next;
        ptr++;
    }
    return winner;
}


void print_instructor(Instructor *instructors)
{
    Instructor *ptr=instructors;
    
    while ( ptr!=NULL )
    {
        printf("Name: %s\n", ptr->instructor_name );
        printf("Ratings: %.2f %.2f %.2f %.2f\n", *(ptr->pl_ratings), *((ptr->pl_ratings)+1), *((ptr->pl_ratings)+2), *((ptr->pl_ratings)+3));
        ptr=ptr->next;
    }
}


void print_submission(Submission *submissions)
{
    Submission *ptr=submissions;
    while (ptr!=NULL)
    {
        printf( "Name: %s\n", ptr->student_name);
        printf(" Project-1: %s\n", pl_names[ ptr->projects[0].pl_index ]);
        printf(" Project-2: %s\n", pl_names[ ptr->projects[1].pl_index ]);
        printf(" Project-3: %s\n", pl_names[ ptr->projects[2].pl_index ]);
        printf(" Project-4: %s\n", pl_names[ ptr->projects[3].pl_index ]);
        printf(" Project-5: %s\n", pl_names[ ptr->projects[4].pl_index ]);
        ptr=ptr->next;
    }
}


void print_scores(Submission *submissions, Score *scores)
{
    Submission *ptr=submissions;
    int i=0;
    while( ptr!=NULL ){
        
        printf("Score of %s: %.2f\n", (scores+i)->student_name ,  (scores+i)->score);
        ptr=ptr->next;
        i++;
    }
}
