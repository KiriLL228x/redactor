#include "TXLib.h"
#include <iostream>
#include <fstream>
#include "dirent.h"
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
//????????? ????????
struct Pictures
{
    int x;
    int y;
    string adress;
    int w_scr;
    int h_scr;
    HDC image;
    int w;
    int h;
    string category;
    bool visible;

};
//????????? ??????
struct Button
{
  int x;
  int y;
  const char* text;
  string category;
};
//??????? ????????? ??????

void drawButton(Button btn)
{
    //x=30 y=30
        txSetColor(TX_BLACK);
        txSetFillColor(TX_WHITE);
        Win32::RoundRect (txDC(), btn.x, btn.y, btn.x+150, btn.y+40, 30, 30);
        txSetFillColor(TX_BLACK);

        txSetColor(TX_BLACK);
        txSelectFont("Times  New Roman", 32);
        txDrawText(btn.x, btn.y, btn.x+150,btn.y+40, btn.text);
}

bool click(Button btn)
{
   return( txMouseButtons() == 1 &&
           txMouseX()>=btn.x &&
           txMouseX()<=btn.x+170 &&
           txMouseY()>=btn.y &&
           txMouseY()<=btn.y+70);
}

void drawPicture(Pictures pct)
{
if(pct.visible)
{
    Win32::TransparentBlt(txDC(), pct.x, pct.y, pct.w_scr, pct.h_scr, pct.image, 0, 0, pct.w, pct.h, TX_WHITE);
}

};

int get_w(string adress)
{
              FILE *f1 = fopen(adress.c_str(), "rb");

              unsigned char headerinfo[54];
              fread(headerinfo, sizeof(unsigned char), 54, f1);
              int w = *(int*)&headerinfo[18];

              return w;
}

int get_h(string adress)
{
              FILE *f1 = fopen(adress.c_str(), "rb");

              unsigned char headerinfo[54];
              fread(headerinfo, sizeof(unsigned char), 54, f1);

              int h = *(int*)&headerinfo[22];

               return h;
}

int readFromDir(string adress, Pictures menuPic[], int COUNT_PIC)
{
    DIR *dir;
    struct dirent *ent;
    int lastY = 50;
    if ((dir = opendir (adress.c_str())) != NULL)
    {
      while ((ent = readdir (dir)) != NULL)
      {
        if((string)ent->d_name != "." && (string)ent->d_name != "..")
        {
            menuPic[COUNT_PIC].y = lastY;
            menuPic[COUNT_PIC].adress = adress + (string)ent->d_name;
            COUNT_PIC ++;
            lastY +=70;
        }
      }
      closedir (dir);
    }
    return COUNT_PIC;
}


string runFileDialog(bool isSave)
{
        string fileName = "";

        OPENFILENAME ofn;
        TCHAR szFile[260] = { 0 };

        //
        ZeroMemory(&ofn, sizeof(ofn));
        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = txWindow();
        ofn.lpstrFile = szFile;
        ofn.nMaxFile = sizeof(szFile);
        ofn.lpstrFilter = ("Text\0*.TXT\0");
        ofn.nFilterIndex = 1;
        ofn.lpstrInitialDir = NULL;
        ofn.nMaxFileTitle = 0;
        ofn.lpstrInitialDir = NULL;
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

        if (isSave)
        {
            if (GetSaveFileName(&ofn) == TRUE)
            {
                fileName = ofn.lpstrFile;

                if (fileName.find(".txt") > 1000)
                {
                    fileName = fileName + ".txt";
                }
            }
        }
        else
        {
                if (GetOpenFileName(&ofn) == TRUE)
                {
                    fileName = ofn.lpstrFile;
                }
        }

        return fileName;

}

const int COUNT_BTN = 9;
const int BTN_SAVE = COUNT_BTN - 1;
const int BTN_LOAD = COUNT_BTN - 2;


int main()
{
    txCreateWindow (1500, 800);
    txDisableAutoPause();
    txTextCursor (false);

    HDC Fon1 = txLoadImage("img/fon1.bmp");
    HDC menufon = txLoadImage("img/fon3.bmp");
    HDC fonhelp = txLoadImage("img/fonhelp.bmp");

    int COUNT_PIC = 0;
    int vybor = -1;
    int nCentralPic = 0;
    bool mouse_free = false;
    string PAGE = "????";


    //??????
        Button btn[COUNT_BTN];
        btn[0] = {30,30,"????? ????","?????"};
        btn[1] = {200,30,"?????","?????"};
        btn[2] = {370,30,"?????","?????"};
        btn[3] = {540,30,"????","????"};
        btn[4] = {710,30,"?????","?????"};
        btn[5] = {880,30,"?????","?????"};
        btn[6] = {1050,30,"?????2","?????2"};
        btn[7] = {1220,30,"?????????",""};
        btn[8] = {1220,80,"?????????",""};

        //???????? ????
        Pictures menuPic[1000];

        //??????????? ????????
        Pictures centralPic[1000];
        COUNT_PIC = readFromDir("img/?????/", menuPic, COUNT_PIC);
        COUNT_PIC = readFromDir("img/?????/", menuPic, COUNT_PIC);
        COUNT_PIC = readFromDir("img/????/",  menuPic, COUNT_PIC);
        COUNT_PIC = readFromDir("img/?????/", menuPic, COUNT_PIC);
        COUNT_PIC = readFromDir("img/?????/", menuPic, COUNT_PIC);
        COUNT_PIC = readFromDir("img/?????/", menuPic, COUNT_PIC);
        COUNT_PIC = readFromDir("img/?????2/", menuPic, COUNT_PIC);

       for(int npic=0; npic < COUNT_PIC; npic++)
       {
         menuPic[npic].visible = false;

         menuPic[npic].x = 1400;



         menuPic[npic].image = txLoadImage (menuPic[npic].adress.c_str());

         menuPic[npic].w = get_w(menuPic[npic].adress);
         menuPic[npic].h = get_h(menuPic[npic].adress);

        int pos_1 = menuPic[npic].adress.find("/");
        int pos_2 = menuPic[npic].adress.find("/", pos_1+1);
        menuPic[npic].category = menuPic[npic].adress.substr(pos_1+1, pos_2-pos_1-1);



         if(menuPic[npic].category == "?????" || menuPic[npic].category == "?????" || menuPic[npic].category == "?????" ||  menuPic[npic].category == "?????" || menuPic[npic].category == "?????2")
         {
          menuPic[npic].w_scr = menuPic[npic].w / 5;
          menuPic[npic].h_scr = menuPic[npic].h / 5;
         }
         else
         {
             menuPic[npic].w_scr = menuPic[npic].w / 2;
             menuPic[npic].h_scr = menuPic[npic].h / 2;
         }
       }




    while(true)
{
    txClear();




    if(PAGE=="????")
    {

        txSetColor(TX_WHITE,3);
        txSetFillColor(TX_BLACK);
        txBitBlt(txDC(), 0, 0, 1800, 900, menufon);
        //?????? ??? ??????
         Win32::RoundRect (txDC(), 200, 150, 400, 200, 30, 30);
        txDrawText(200,150,400,200, "START");
        //??????? ?? ?????? ?????
        if(txMouseX() >= 200 && txMouseY()>= 150 &&
           txMouseX() <= 400 && txMouseY()<= 200 &&
            txMouseButtons() == 1)
        {
            PAGE="start";
        }

        //?????? ??????
       Win32::RoundRect (txDC(),200,250,400,300,30,30);
        txDrawText(200,250,400,300, "HELP");
        //??????? ?? ?????? ?????
        if(txMouseX() >= 200 && txMouseY()>= 250 &&
        txMouseX() <= 400 && txMouseY()<= 300 &&
        txMouseButtons() == 1)
        {
            PAGE="help";
        }

        //?????? Exit
        txRectangle(200,550,400,600);
        txDrawText(200,550,400,600, "EXIT");
        //??????? ?? ?????? ??????
        if(txMouseX() >= 200 && txMouseY()>= 550 &&
        txMouseX() <= 400 && txMouseY()<= 600 &&
        txMouseButtons() == 1)
        {
            return 0;
        }

    }

    if(PAGE=="help")
    {

        txSetColor(TX_WHITE,5);
        txSetFillColor(TX_BLACK);
        txBitBlt(txDC(), 0, 0, 1800, 900, fonhelp);
        txRectangle(100,200,300,250);
        txDrawText(100,200,300,250, "BACK");
        //??????? ?? ?????? BACK
        if(txMouseX() >= 100 && txMouseY()>=200 &&
        txMouseX() <= 300 && txMouseY()<=250 &&
        txMouseButtons() == 1)
        {
            PAGE="????";
        }

        txSelectFont("Arial",25);
        txDrawText(300,100,900,600,"??????????:\n"
                                "??? - ??????? ?????????,\n"
                                "up,down,left,right - ???????????"
        );
    }



    if(PAGE=="start")
    {
        txBegin();
        txSetColor(TX_WHITE);
        txBitBlt(txDC(), 0, 0, 1500, 800, Fon1);

        //????????? ??????
        for(int nk=0; nk<COUNT_BTN; nk++)
        {
            drawButton(btn[nk]);
        }
    //????????? ???????? ????
        for(int npic=0; npic < COUNT_PIC; npic++)
        {
            drawPicture(menuPic[npic]);
        }
   //????????? ??????????? ????????
        for(int npic=0; npic < nCentralPic; npic++)
        {
            drawPicture(centralPic[npic]);
        }

        //????????? ???????? ???? ??  ?????????
        for(int nk=0; nk<COUNT_BTN; nk++)
        {
            if(click(btn[nk]))
            {
                for(int npic=0; npic < COUNT_PIC; npic++)
                {
                    menuPic[npic].visible= false;
                    if(menuPic[npic].category == btn[nk].category)
                    {
                        menuPic[npic].visible=true;
                    }
                }
            }
        }

             //????????? ??????????? ???????? ??  ?????????
     for(int npic=0; npic < COUNT_PIC; npic++)
        {
          if( txMouseButtons() == 1 &&
           menuPic[npic].visible &&
           txMouseX()>=menuPic[npic].x &&
           txMouseX()<=menuPic[npic].x + menuPic[npic].w_scr &&
           txMouseY()>=menuPic[npic].y &&
           txMouseY()<=menuPic[npic].y + menuPic[npic].h_scr)
             {
                while(txMouseButtons() == 1)
                {
                    txSleep(10);
                }
                centralPic[nCentralPic] = { 250,
                                            200,
                                            menuPic[npic].adress,
                                            menuPic[npic].w,
                                            menuPic[npic].h,
                                            menuPic[npic].image,
                                            menuPic[npic].w,
                                            menuPic[npic].h,
                                            menuPic[npic].category,
                                            menuPic[npic].visible
                                          };
                nCentralPic++;
             }
         }


        //????? ??????????? ????????
        for(int npic=0; npic < COUNT_PIC; npic++)
        {
          if(  txMouseButtons() == 1 &&
               centralPic[npic].visible &&
               txMouseX()>=centralPic[npic].x &&
               txMouseX()<=centralPic[npic].x + centralPic[npic].w &&
               txMouseY()>=centralPic[npic].y &&
               txMouseY()<=centralPic[npic].y + centralPic[npic].h)
             {
               vybor=npic;
               mouse_free = false;
             }
        }


        // ???????????? ???????? ??????????? ????????
       if(vybor>=0)
        {
          if(GetAsyncKeyState(VK_RIGHT)) centralPic[vybor].x += 14;
          if(GetAsyncKeyState(VK_LEFT)) centralPic[vybor].x -= 14;
          if(GetAsyncKeyState(VK_UP)) centralPic[vybor].y -= 14;
          if(GetAsyncKeyState(VK_DOWN)) centralPic[vybor].y += 14;
        }

        //??????????


     if(click(btn[BTN_SAVE]))
         {
            string fileName = runFileDialog(true);
            if (fileName != "")
            {
                ofstream fout;
                fout.open(fileName);

                for (int npic = 0; npic < COUNT_PIC; npic++)
                {
                    if (centralPic[npic].visible)
                    {
                     fout << centralPic[npic].x << endl;
                     fout << centralPic[npic].y << endl;
                     fout << centralPic[npic].adress << endl;
                    }
                }
                fout.close();

                txMessageBox("?????????", "???????", MB_ICONINFORMATION);
            }
         }

        //????????

        if (click(btn[BTN_LOAD]))
        {

            string fileName = runFileDialog(false);
            if(fileName != "")
            {
              for (int npic = 0; npic < COUNT_PIC; npic++)
              {
                centralPic[npic].visible = false;
              }

              char buff[50];
              ifstream fin(fileName);

              while (fin.good())
              {
                    fin.getline(buff, 50);
                    int x = atoi(buff);
                    fin.getline(buff,50);
                    int y = atoi(buff);
                    fin.getline(buff, 50);
                    string adress = (buff);

                    for (int npic = 0; npic < COUNT_PIC; npic++)
                    {

                        if(menuPic[npic].adress == adress)
                        {
                          centralPic[nCentralPic] = {
                                            x,
                                            y,
                                            menuPic[npic].adress,
                                            menuPic[npic].w,
                                            menuPic[npic].h,
                                            menuPic[npic].image,
                                            menuPic[npic].w,
                                            menuPic[npic].h,
                                            menuPic[npic].category,
                                            true
                                          };
                         nCentralPic++;

                        }
                    }
               }
            //txMessageBox("?????????", "???????", MB_ICONINFORMATION);
            fin.close();
            }
         }









        // ???????? ??????????? ???????? ? ??????
        if(vybor>=0 && GetAsyncKeyState(VK_DELETE))
        {
            centralPic[vybor] = centralPic[nCentralPic - 1];
            nCentralPic--;
            vybor=-1;
            mouse_free = true;
        }

        txEnd();
}
        txSleep(50);


}

            for(int npic=0; npic < COUNT_PIC; npic++)
            {
                txDeleteDC(menuPic[npic].image);
            }



    return 0;
}
//   txSetFillColor(TX_BLUE);
//    Win32::RoundRect (txDC(), 55, 105, 205, 145, 30, 30);
