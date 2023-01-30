#include<bits/stdc++.h>
#include "reader.cpp"
#include <Windows.h>
#include "MMSystem.h"
#include "mingw.thread.h"
//#include "structure.cpp"
using namespace std;




int exitx, exity, exitszx, exitszy;
int writex, writey, writeszx, writeszy;
int file_textx, file_texty, file_textszx, file_textszy;
int file_structx, file_structy, file_structszx, file_structszy;
int mouseX, mouseY;





bool checkExit(int x, int y)
{

    return (x>=exitx)&&
           (x<=(exitx+exitszx)) &&
           (y>=exity) &&
           (y<=(exity+exitszy));

}

bool checkFileText(int x, int y)
{

    return (x>=file_textx)&&
           (x<=(file_textx+file_textszx)) &&
           (y>=file_texty)&&
           (y<=(file_texty+file_textszy));

}

bool checkFileStruct(int x, int y)
{

    return (x>=file_structx)&&
           (x<=(file_structx+file_structszx)) &&
           (y>=file_structy)&&
           (y<=(file_structy+file_structszy));

}

//Ovidiule, asta e functia care o sa ruleze in background muzica
void play_music()
{
    PlaySound("song.wav", NULL, SND_FILENAME|SND_LOOP|SND_ASYNC);
}

int main()
{

    //std::thread Music(play_music); // Music o sa fie o variabila 'speciala' care e de fapt sunetul nostru
    //Music.join(); // asa ii zicems a inceapa
    initwindow(800, 800, "Nassy-Shcneidermann, Menu");

    exitx=300, exity=300, exitszx=200, exitszy=60;
    create_button(exitx, exity, exitszx, exitszy, "EXIT");


    //Ia vezi bossule
    file_textx=300, file_texty=200, file_textszx=200, file_textszy=60;
    create_button(file_textx, file_texty, file_textszx, file_textszy, "TYPE YOUR CODE HERE!");

    file_structx=300, file_structy=100, file_structszx=200, file_structszy=60;
    create_button(file_structx, file_structy, file_structszx, file_structszy, "GET CODE FROM FILE");



    while(true)
    {


        getmouseclick(WM_LBUTTONDOWN, mouseX, mouseY);
        if(checkExit(mouseX, mouseY))
        {
            closegraph();
            return 0;
        }
        if(checkFileText(mouseX, mouseY))
        {

            ShellExecute(NULL, "open", "menuText.exe", NULL, NULL, SW_SHOWNA);


        }
        if(checkFileStruct(mouseX, mouseY))
        {

            ShellExecute(NULL, "open", "menuFile.exe", NULL, NULL, SW_SHOWNA);

        }
    }


    return 0;
}

/*
    PlaySound(TEXT("song.wav"), NULL, SND_SYNC);
    system("pause");
*/
