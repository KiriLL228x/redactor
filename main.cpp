#include "TXLib.h"
//��������� ��������
struct Pictures
{
    int x;
    int y;
    HDC image;
    int w;
    int h;
    int w_scr;
    int h_scr;
    bool visible;
    string category;
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

int main()
{
    txCreateWindow (1200, 800);
    txDisableAutoPause();
    txTextCursor (false);

    HDC Fon3 = txLoadImage("img/fon3.bmp");

    int COUNT_BTN = 5;
    int COUNT_PIC = 17;

    //������
        Button btn[COUNT_BTN];
        btn[0] = {30,30,"����� ����","�����"};
        btn[1] = {200,30,"�����","�����"};
        btn[2] = {370,30,"�����","�����"};
        btn[3] = {540,30,"����","����"};
        btn[4] = {710,30,"�����","�����"};

        //�������� ����
        Pictures menuPic[COUNT_PIC];
        menuPic[0] = {1000, 400, txLoadImage("img/Building/Wall_A_02.bmp"), 320, 320, 90,90, false,"�����"};
        menuPic[1] = {1000, 300, txLoadImage("img/Building/Wall_B_02.bmp"), 320, 320, 90,90, false,"�����"};
        menuPic[2] = {1000, 200, txLoadImage("img/Building/Wall_C_02.bmp"), 320, 320, 90,90, false,"�����"};
        menuPic[3] = {1000, 400, txLoadImage("img/Platformer/Ground_10.bmp"), 128, 128, 90,90, false,"�����"};
        menuPic[4] = {1000, 300, txLoadImage("img/Platformer/Ground_11.bmp"), 128, 128, 90,90, false,"�����"};
        menuPic[5] = {1000, 200, txLoadImage("img/Platformer/Ground_12.bmp"), 128, 128, 90,90, false,"�����"};
        menuPic[6] = {1000, 400, txLoadImage("img/Building/Roof_A_04.bmp"), 352, 160, 90,40, false,"�����"};
        menuPic[7] = {1000, 300, txLoadImage("img/Building/Roof_A_05.bmp"), 352, 160, 90,40, false,"�����"};
        menuPic[8] = {1000, 200, txLoadImage("img/Building/Roof_B_04.bmp"), 352, 160, 90,40, false,"�����"};
        menuPic[9] = {1000, 100, txLoadImage("img/Building/Roof_B_05.bmp"), 352, 160, 90,40, false,"�����"};
        menuPic[10] = {1000, 400, txLoadImage("img/Building/Window_01.bmp"), 128, 128, 64,64, false,"����"};
        menuPic[11] = {1000, 300, txLoadImage("img/Building/Window_02.bmp"), 128, 128, 64,64, false,"����"};
        menuPic[12] = {1000, 200, txLoadImage("img/Building/Window_03.bmp"), 128, 128, 64,64, false,"����"};
        menuPic[13] = {1000, 100, txLoadImage("img/Building/Door_01.bmp"), 128, 256, 64,128, false,"�����"};
        menuPic[14] = {1000, 250, txLoadImage("img/Building/Door_02.bmp"), 128, 256, 64,128, false,"�����"};
        menuPic[15] = {1000, 400, txLoadImage("img/Building/Door_03.bmp"), 128, 256, 64,128, false,"�����"};
        menuPic[16] = {1000, 550, txLoadImage("img/Building/Door_04.bmp"), 128, 256, 64,128, false,"�����"};

         //����������� ��������
        Pictures centralPic[COUNT_PIC];
        centralPic[0] = {250, 200, txLoadImage("img/Building/Wall_A_02.bmp"), 320, 320, 320, 320, false,"�����"};
        centralPic[1] = {250, 200, txLoadImage("img/Building/Wall_B_02.bmp"), 320, 320, 320, 320, false,"�����"};
        centralPic[2] = {250, 200, txLoadImage("img/Building/Wall_C_02.bmp"), 320, 320, 320, 320, false,"�����"};
        centralPic[3] = {250, 200, txLoadImage("img/Platformer/Ground_10.bmp"), 128, 128, 128, 128, false,"�����"};
        centralPic[4] = {250, 200, txLoadImage("img/Platformer/Ground_11.bmp"), 128, 128, 128, 128, false,"�����"};
        centralPic[5] = {250, 200, txLoadImage("img/Platformer/Ground_12.bmp"), 128, 128, 128, 128, false,"�����"};
        centralPic[6] = {250, 200, txLoadImage("img/Building/Roof_A_04.bmp"), 352, 160, 352, 160, false,"�����"};
        centralPic[7] = {250, 200, txLoadImage("img/Building/Roof_A_05.bmp"), 352, 160, 352, 160, false,"�����"};
        centralPic[8] = {250, 200, txLoadImage("img/Building/Roof_B_04.bmp"), 352, 160, 352, 160, false,"�����"};
        centralPic[9] = {250, 200, txLoadImage("img/Building/Roof_B_05.bmp"), 352, 160, 352, 160, false,"�����"};
        centralPic[10] = {250, 200, txLoadImage("img/Building/Window_01.bmp"), 128, 128, 128,128, false,"����"};
        centralPic[11] = {250, 200, txLoadImage("img/Building/Window_02.bmp"), 128, 128, 128,128, false,"����"};
        centralPic[12] = {250, 200, txLoadImage("img/Building/Window_03.bmp"), 128, 128, 128,128, false,"����"};
        centralPic[13] = {250, 200, txLoadImage("img/Building/Door_01.bmp"), 128, 256, 128,256, false,"�����"};
        centralPic[14] = {250, 200, txLoadImage("img/Building/Door_02.bmp"), 128, 256, 128,256, false,"�����"};
        centralPic[15] = {250, 200, txLoadImage("img/Building/Door_03.bmp"), 128, 256, 128,256, false,"�����"};
        centralPic[16] = {250, 200, txLoadImage("img/Building/Door_04.bmp"), 128, 256, 128,256, false,"�����"};

    while(!GetAsyncKeyState(VK_ESCAPE))
    {
        txBegin();
        txSetColor(TX_WHITE);
        txClear();
        txBitBlt(txDC(), 0, 0, 1200, 900, Fon3);

        //��������� ������
        for(int nk=0; nk<5; nk++)
        {
            drawButton(btn[nk]);
        }
    //��������� �������� ����
        for(int npic=0; npic < COUNT_PIC; npic++)
        {
            drawPicture(menuPic[npic]);
        }
   //��������� ����������� ��������
        for(int npic=0; npic < COUNT_PIC; npic++)
        {
            drawPicture(centralPic[npic]);
        }

        //��������� �������� ���� ��  ���������
        for(int nk=0; nk<5; nk++)
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
                 for(int npicl=0; npicl < COUNT_PIC; npicl++)
                 {
                     if(centralPic[npicl].category == centralPic[npic].category)
                     {
                        centralPic[npicl].visible = false;
                     }
                 }
                centralPic[npic].visible = !centralPic[npic].visible;
                txSleep(100);
             }
         }







        txSleep(50);
        txEnd();

    }

            for(int npic=0; npic < COUNT_PIC; npic++)
            {
                txDeleteDC(menuPic[npic].image);
            }

            for(int npic=0; npic < COUNT_PIC; npic++)
            {
                txDeleteDC(centralPic[npic].image);
            }


    return 0;
}
//   txSetFillColor(TX_BLUE);
//    Win32::RoundRect (txDC(), 55, 105, 205, 145, 30, 30);
