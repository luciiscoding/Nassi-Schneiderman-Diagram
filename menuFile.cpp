#include<bits/stdc++.h>
#include "reader.cpp"
//#include "structure.cpp"


int32_t main(){
            ifstream fin("fileStruct.nassy");
            fin>>n;
            for(int i=1; i<=n; i++){
                fin>>s[i];
            }
            int i=1;
            nassy *Main = new nassy();
            Main->tp = "main";
            build(Main, i, n, s);
            drawWindow(Main, s, n, 100, 100, 500);
            fin.close();
}
