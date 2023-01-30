#include<bits/stdc++.h>
#include "structure.cpp"
#include<graphics.h>




void screenText(int x, int y, string s)
{

    char *c = new char[s.size()];
    strcpy(c, s.c_str());
    outtextxy(x, y, c);
}

int savex, savey, saveszx, saveszy;
void create_button(int x, int y, int szx, int szy, string s)
{

    line(x, y, x+szx, y);
    line(x, y, x, y+szy);
    line(x+szx, y, x+szx, y+szy);
    line(x, y+szy, x+szx, y+szy);

    screenText( x+szy/4, y+szy/3, s);


}





int imgx, imgy, imgszx, imgszy;
bool check_img(int x, int y){
    return x<=(imgx+imgszx) && x>=imgx && y<=(imgy+imgszy) && y>=imgy;
}




bool checkSave(int x, int y){
    return (x<=savex+saveszx) && x>=savex && y>=savey && y<=savey+saveszy;
}


int codeSize=15;
int drawCode(nassy *Node, int x, int y, int lx){
    screenText(x, y, Node->code);
    return codeSize;
}


int ifSize=45;
int drawIf(nassy *Node, int x, int y, int lx){

    line(x, y, x+lx, y);
    line(x, y, x, y+ifSize);
    line(x, y+ifSize, x+lx, y+ifSize);
    line(x+lx, y, x+lx, y+ifSize);

    line(x, y, x+(lx/2), y+ifSize );
    line(x+lx, y, x+(lx/2), y+ifSize );

    screenText(x+(lx/2)-(Node->condition.size()+6)*4/2, y, Node->condition);
    screenText(x, y+10, "true");
    screenText(x+lx-7*5, y+10, "false");
    return ifSize;
}



int whilex=20, whiley=20;
int drawWhile(nassy *Node, int x, int y, int lx){

screenText(x, y,Node->whileStatement);
return whiley;
}

int drawWhileDo(nassy *Node, int x, int y, int lx){
screenText(x, y, Node->whileDoStatement);
return whiley;
}

int drawFor(nassy *Node, int x, int y, int lx){
screenText(x, y, Node->forStatement);
return whiley;
}

int drawSwitch(nassy *Node, int x, int y, int lx){
screenText(x, y, Node->switchStatement);
line(x, y+20, x+lx, y+20);
return 20;
}



int drawCase(nassy * Node, int x, int y, int lx){
screenText(x, y, Node->caseStatement);
line(x, y+20, x+lx, y+20);
return 20;
}

int drawNassy(nassy *Node, int x, int y, int lx){
int ly = 0;
if(Node->tp=="code"){
    ly=drawCode(Node, x, y, lx);
}

if(Node->tp=="if"){
    int sz=drawIf(Node, x, y, lx);
    int sz1=0;
    int sz2=0;
    for(int i=1; i<=Node->cntChildren; i++){
        sz1+=drawNassy(Node->children[i], x, y+sz1+sz, lx/2);
    }
    if(Node->hasElse){
        sz2+=drawNassy(Node->thisElse, x+lx/2, y+sz2+sz, lx/2);
    }
   ly=sz+max(sz1, sz2);
}

if( (Node->tp=="else") || (Node->tp=="main") ){
    int sz=0;
    for(int i=1; i<=Node->cntChildren; i++){
        sz+=drawNassy(Node->children[i], x, y+sz, lx);
    }
    ly=sz;
}

if(Node->tp=="while"){
    int sz = drawWhile(Node, x, y, lx);
    for(int i=1; i<=Node->cntChildren; i++){
        sz+=drawNassy(Node->children[i], x+whilex, y+sz, lx-whilex);
    }
    ly=sz;
}

if(Node->tp=="while do"){
    int sz = drawWhileDo(Node, x, y, lx);
    for(int i=1; i<=Node->cntChildren; i++){
        sz+=drawNassy(Node->children[i], x+whilex, y+sz, lx-whilex);
    }
    ly=sz;
}

if(Node->tp=="switch"){
    drawSwitch(Node, x, y, lx);
    int sz = 20;
    int dx = lx/Node->cntChildren;
    for(int i=1; i<=Node->cntChildren; i++){
        sz=max(drawNassy(Node->children[i], x+(i-1)*dx, y+20, dx)+20, sz);
    }
    ly=sz;
}

if(Node->tp=="case"){
    drawCase(Node, x, y, lx);
    int sz = 20;
    for(int i=1; i<=Node->cntChildren; i++){
        sz+=drawNassy(Node->children[i], x, y+sz, lx);
    }
    ly=sz;
}

if(Node->tp=="for"){
    int sz = drawFor(Node, x, y, lx);
    for(int i=1; i<=Node->cntChildren; i++){
        sz+=drawNassy(Node->children[i], x+whilex, y+sz, lx-whilex);
    }
    ly=sz;
}


line(x, y, x, y+ly);
line(x, y, x+lx, y);
line(x+lx, y, x+lx, y+ly);
line(x, y+ly, x+lx, y+ly);
return ly;
}





int maxy, maxx;







void drawWindow(nassy *Node, string s[], int n, int x, int y, int lx)
{

    initwindow(800, 800, "Nassy-Shcneidermann");
//settextstyle(8, 0, 7);
    int ly=drawNassy(Node, x, y, lx);

    savex=50, savey=50, saveszx=120, saveszy=30;
    create_button(savex, savey, saveszx, saveszy, "Save in text file");


    imgx=220, imgy=50, imgszx=120, imgszy=30;
    //create_button(imgx, imgy, imgszx, imgszy, "Save as image");

    while(true){
        int mouseX, mouseY;
        getmouseclick(WM_LBUTTONDOWN, mouseX, mouseY);
        if(checkSave(mouseX, mouseY)){
            cout<<"someSave\n";
            ofstream fout("fileStruct.nassy");
            fout<<n<<"\n";
            for(int i=1; i<=n; i++){
                fout<<s[i]<<"\n";
                cout<<s[i]<<"wow\n";
            }
            fout.close();
        }
        /*
        if(check_img(mouseX, mouseY)){
            void *ptr;
            int mxx=getmaxx();
            int mxy=getmaxy();
            getimage(0, 90, mxx, mxy, ptr);
            FILE *fp = fopen("image.BMP", "wb");
            fwrite(ptr, 1, sizeof(ptr), fp);
            fclose(fp);
        }
        */
    }

}
