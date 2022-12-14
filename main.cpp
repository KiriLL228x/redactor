#include "TXLib.h"
#include <iostream>
#include <fstream>
#include "dirent.h"
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
//��������� ��������
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
//��������� ������
struct Button
{
  int x;
  int y;
  const char* text;
  string category;
};
//������� ��������� ������

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
            lastY +=50;
        }
      }
      closedir (dir);
    }
    return COUNT_PIC;
}

const int COUNT_BTN = 8;
const int BTN_SAVE = COUNT_BTN - 1;
const int BTN_LOAD = COUNT_BTN - 2;

int main()
{
    txCreateWindow (1200, 800);
    txDisableAutoPause();
    txTextCursor (false);

    HDC Fon3 = txLoadImage("img/fon3.bmp");

    int COUNT_BTN = 8;
    int COUNT_PIC = 0;
    int vybor = -1;
    int nCentralPic = 0;
    bool mouse_free = false;

    //������
        Button btn[COUNT_BTN];
        btn[0] = {30,30,"����� ����","�����"};
        btn[1] = {200,30,"�����","�����"};
        btn[2] = {370,30,"�����","�����"};
        btn[3] = {540,30,"����","����"};
        btn[4] = {710,30,"�����","�����"};
        btn[5] = {880,30,"�����","�����"};
        btn[6] = {1050,30,"���������",""};
        btn[7] = {1050,80,"���������",""};

        //�������� ����
        Pictures menuPic[1000];

        //����������� ��������
        Pictures centralPic[1000];
        COUNT_PIC = readFromDir("img/�����/", menuPic, COUNT_PIC);
        COUNT_PIC = readFromDir("img/�����/", menuPic, COUNT_PIC);
        COUNT_PIC = readFromDir("img/����/",  menuPic, COUNT_PIC);
        COUNT_PIC = readFromDir("img/�����/", menuPic, COUNT_PIC);
        COUNT_PIC = readFromDir("img/�����/", menuPic, COUNT_PIC);
        COUNT_PIC = readFromDir("img/�����/", menuPic, COUNT_PIC);

       for(int npic=0; npic < COUNT_PIC; npic++)
       {
         menuPic[npic].visible = false;

         menuPic[npic].x = 900;

         menuPic[npic].image = txLoadImage (menuPic[npic].adress.c_str());

         menuPic[npic].w = get_w(menuPic[npic].adress);
         menuPic[npic].h = get_h(menuPic[npic].adress);

         menuPic[npic].w_scr = menuPic[npic].w / 3;
         menuPic[npic].h_scr = menuPic[npic].h / 3;

        int pos_1 = menuPic[npic].adress.find("/");
        int pos_2 = menuPic[npic].adress.find("/", pos_1+1);
        menuPic[npic].category = menuPic[npic].adress.substr(pos_1+1, pos_2-pos_1-1);
       }




    while(!GetAsyncKeyState(VK_ESCAPE))
    {
        txBegin();
        txSetColor(TX_WHITE);
        txClear();
        txBitBlt(txDC(), 0, 0, 1200, 900, Fon3);

        //��������� ������
        for(int nk=0; nk<COUNT_BTN; nk++)
        {
            drawButton(btn[nk]);
        }
    //��������� �������� ����
        for(int npic=0; npic < COUNT_PIC; npic++)
        {
            drawPicture(menuPic[npic]);
        }
   //��������� ����������� ��������
        for(int npic=0; npic < nCentralPic; npic++)
        {
            drawPicture(centralPic[npic]);
        }

        //��������� �������� ���� ��  ���������
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

             //��������� ����������� �������� ��  ���������
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


        //����� ����������� ��������
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


        // ������������ �������� ����������� ��������
       if(vybor>=0)
        {
          if(GetAsyncKeyState(VK_RIGHT)) centralPic[vybor].x += 5;
          if(GetAsyncKeyState(VK_LEFT)) centralPic[vybor].x -= 5;
          if(GetAsyncKeyState(VK_UP)) centralPic[vybor].y -= 5;
          if(GetAsyncKeyState(VK_DOWN)) centralPic[vybor].y += 5;
        }

        //����������
         if(click(btn[BTN_SAVE]))
         {
            string fileName = "1.txt";
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

                txMessageBox("���������", "�������", MB_ICONINFORMATION);
            }
         }

        //��������

        if (click(btn[BTN_LOAD]))
        {

            string fileName = "1.txt";
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

                        if(centralPic[npic].adress == adress)
                        {
                         centralPic[npic].x = x;
                         centralPic[npic].y = y;
                         centralPic[npic].visible = true;

                        }
                    }
               }
            txMessageBox("���������", "�������", MB_ICONINFORMATION);
               fin.close();
            }
         }



        // �������� ����������� �������� � ������
        if(vybor>=0 && GetAsyncKeyState(VK_DELETE))
        {
            centralPic[vybor] = centralPic[nCentralPic - 1];
            nCentralPic--;
            vybor=-1;
            mouse_free = true;
        }


        txSleep(50);
        txEnd();

        }

            for(int npic=0; npic < COUNT_PIC; npic++)
            {
                txDeleteDC(menuPic[npic].image);
            }



    return 0;
}
//   txSetFillColor(TX_BLUE);
//    Win32::RoundRect (txDC(), 55, 105, 205, 145, 30, 30);
