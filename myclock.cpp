#include"sdlutils.cpp"
//#include<ctime.h>
//#include"x11utils.cpp"

#include<time.h>

#include<stdio.h>
///                 0            1            2           3             4            5            6            7          8              9
char font[11]={1+2+4+8+16+32,   2+4,      1+2+64+16+8, 1+2+64+4+8,  32+64+2+4,  1+32+64+4+8, 1+32+64+4+8+16, 1+2+4,1+2+4+8+16+32+64,  1+2+4+8+32+64};
char bits[7]={1,2,4,8,16,32,64};
char str[4];
char str_err[4];
            ///   1         2       4           8          16          32         64
char  flines[7][4]={{0,0,1,0},{1,0,1,1},{1,1,1,2}, {1,2,0,2}, {0,2,0,1},  {0,1,0,0},  {0,1,1,1}};



void string2str(char*a,char*b){
    while(*a){
        int c;
        c=*a-'0';
        if(c<0||c>10)
            c=10;            
        *b=font[c];
        a++;
        b++;    
    }    
}
void drawSym(SDL_Surface*screen,int x1,int y1,int x2,int y2,char sym){
    int i,w,h;
    w=x2-x1;
    h=y2-y1;
    for(i=0;i<7;i++){
        if(sym&bits[i]){
            drawLine(screen,x1+w*flines[i][0],y1+h*flines[i][1]/2,x1+w*flines[i][2],y1+h*flines[i][3]/2,0x00ff00);
        }
    
    }
    
    
    
}
void drawStr(SDL_Surface*screen,char*str){
    fade(screen,255);
    int i;
    for(i=0;i<4;i++){
        drawSym(screen,i*screen->w*8/10/4 +screen->w/10,screen->h/10,(i+0.8)*screen->w*8/10/4 +screen->w/10,screen->h*9/10,str[i]);
    }

        SDL_Flip( screen ); 


}
int makeError(int a){
    int e;
    e=rand()%7;
///    printf("rand=%d\n",e);
    return a ^ bits[e];
}
int inFont(int a){
    for(int i=0;i<10;i++)
        if(font[i]==a)
            return 1;
    
    return 0;
}
void makeError(char*a,char*b){
    int i,c,ce,j,co;
    int rnd[7];
    for(i=0;i<4;i++,a++,b++){
        c=*a;
        printf("makeError symbol %d -> ",c);
        int t;
        t=0;
       while(1){
            if(t<10)
                ce=makeError(c);
            else if(t<17){
                if(t==10){
                    for(j=0;j<7;j++)
                        rnd[j]=j;
                    for(j=0;j<7;j++){
                        int t,jj;
                        jj=rand()%7;
                        t=rnd[j];
                        rnd[j]=rnd[jj];
                        rnd[jj]=t;
                    }
                    printf("RND:\n");
                    for(j=0;j<7;j++)
                        printf("%d ",rnd[j]);
                       
                    printf("\n");
                    
                }
                ce=c^bits[rnd[t-10]];
            
            }else{
                ce=c;
                break;
            }
            t++;
            printf("c=%d ce=%d\n",c,ce);
            if(c==ce)
                continue;
            if(inFont(ce)){
                printf("ce in font\n");
                continue;
            }
            co=0;
            
            for(j=0;j<7;j++){
                if((c!=(ce^bits[j])) && inFont(ce^bits[j])){
                    printf("ce xor %d in font(c=%d cee=%d)\n",bits[j],c,ce^bits[j]);
                    co=1;
                    break;
                }
                    
            
            }
            if(co){
                continue;
            }
            break;
        }
        printf(" %d\n",ce);
        
        *b=ce;
    }


}        

int main(int aa,char*ab[]){
    SDL_Surface* screen=makeScreen();
    int hm,lhm;
    lhm=-1;
    srand (time(NULL));
    while(readKey()<0){
        char s[32];
        time_t t = time(0);   // get time now
        struct tm * now = localtime( & t );
        int m=now->tm_min;
        int h=now->tm_hour;
        hm=h*60+m;
        if(lhm!=hm){
            sprintf(s,"%02d%02d",h,m);
            string2str(s,str);
            makeError(str,str_err);        
            drawStr(screen,str_err);
            lhm=hm;
       }
       usleep(1000);
    }
    return 0;
}



