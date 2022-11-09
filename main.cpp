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

    int COUNT_BTN = 6;
    int COUNT_PIC = 45;
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

        //�������� ����
        Pictures menuPic[COUNT_PIC];
        menuPic[0] = {900, 100, txLoadImage("img/Building/Wall_A_02.bmp"),   320,320, 90,90, false,"�����"};
        menuPic[1] = {900, 200, txLoadImage("img/Building/Wall_B_02.bmp"),   320,320, 90,90, false,"�����"};
        menuPic[2] = {900, 300, txLoadImage("img/Building/Wall_C_02.bmp"),   320,320, 90,90, false,"�����"};
        menuPic[3] = {860, 100, txLoadImage("img/Building/Wall_A_01.bmp"),   128,320, 32,80, false,"�����"};
        menuPic[4] = {1000, 100, txLoadImage("img/Building/Wall_A_03.bmp"),  128,320, 32,80, false,"�����"};
        menuPic[5] = {860, 200, txLoadImage("img/Building/Wall_B_01.bmp"),   128,320, 32,80, false,"�����"};
        menuPic[6] = {1000, 200, txLoadImage("img/Building/Wall_B_03.bmp"),  128,320, 32,80, false,"�����"};
        menuPic[7] = {860, 300, txLoadImage("img/Building/Wall_C_01.bmp"),   128,320, 32,80, false,"�����"};
        menuPic[8] = {1000, 300, txLoadImage("img/Building/Wall_C_03.bmp"),  128,320, 32,80, false,"�����"};

        menuPic[9] = {930, 100, txLoadImage("img/Building/Roof_A_01.bmp"),   128,160, 64,80, false,"�����"};
        menuPic[10] = {1000, 100, txLoadImage("img/Building/Roof_A_02.bmp"), 128,160, 64,80, false,"�����"};
        menuPic[11] = {1070, 100, txLoadImage("img/Building/Roof_A_03.bmp"), 128,160, 64,80, false,"�����"};
        menuPic[12] = {1050, 200, txLoadImage("img/Building/Roof_A_04.bmp"), 352,160, 90,40, false,"�����"};
        menuPic[13] = {950, 200, txLoadImage("img/Building/Roof_A_05.bmp"),  352,160, 90,40, false,"�����"};
        menuPic[14] = {930, 300, txLoadImage("img/Building/Roof_B_01.bmp"),  128,160, 64,80, false,"�����"};
        menuPic[15] = {1000, 300, txLoadImage("img/Building/Roof_B_02.bmp"), 128,160, 64,80, false,"�����"};
        menuPic[16] = {1070, 300, txLoadImage("img/Building/Roof_B_03.bmp"), 128,160, 64,80, false,"�����"};
        menuPic[17] = {1050, 400, txLoadImage("img/Building/Roof_B_04.bmp"), 352,160, 90,40, false,"�����"};
        menuPic[18] = {950, 400, txLoadImage("img/Building/Roof_B_05.bmp"),  352,160, 90,40, false,"�����"};


        menuPic[19] = {900, 100, txLoadImage("img/Building/Window_01.bmp"),        128,128, 64,64, false,"����"};
        menuPic[20] = {900, 200, txLoadImage("img/Building/Window_02.bmp"),        128,128, 64,64, false,"����"};
        menuPic[21] = {900, 300, txLoadImage("img/Building/Window_03.bmp"),        128,128, 64,64, false,"����"};
        menuPic[22] = {1050, 100, txLoadImage("img/Building/Stone_Window_01.bmp"), 160,160, 80,80, false,"����"};
        menuPic[23] = {1050, 200, txLoadImage("img/Building/Stone_Window_02.bmp"), 160,160, 80,80, false,"����"};
        menuPic[24] = {1050, 300, txLoadImage("img/Building/Stone_Window_03.bmp"), 160,160, 80,80, false,"����"};

        menuPic[25] = {900, 100, txLoadImage("img/Building/Door_01.bmp"),          128,256, 64,128, false,"�����"};
        menuPic[26] = {900, 250, txLoadImage("img/Building/Door_02.bmp"),          128,256, 64,128, false,"�����"};
        menuPic[27] = {900, 400, txLoadImage("img/Building/Door_03.bmp"),          128,256, 64,128, false,"�����"};
        menuPic[28] = {900, 550, txLoadImage("img/Building/Door_04.bmp"),          128,256, 64,128, false,"�����"};
        menuPic[29] = {1050, 100, txLoadImage("img/Building/Wide_Door_01.bmp"),    256,256, 128,128, false,"�����"};
        menuPic[30] = {1050, 250, txLoadImage("img/Building/Wide_Door_02.bmp"),    256,256, 128,128, false,"�����"};
        menuPic[31] = {1050, 400, txLoadImage("img/Building/Wide_Door_03.bmp"),    256,256, 128,128, false,"�����"};
        menuPic[32] = {1050, 550, txLoadImage("img/Building/Wide_Door_04.bmp"),    256,256, 128,128, false,"�����"};

        menuPic[33] = {900, 100, txLoadImage("img/Platformer/Ground_10.bmp"),  128,128, 90,90, false,"�����"};
        menuPic[34] = {900, 200, txLoadImage("img/Platformer/Ground_11.bmp"),  128,128, 90,90, false,"�����"};
        menuPic[35] = {900, 300, txLoadImage("img/Platformer/Ground_12.bmp"),  128,128, 90,90, false,"�����"};
        menuPic[36] = {900, 400, txLoadImage("img/Platformer/Ground_01.bmp"),  128,128, 90,90, false,"�����"};
        menuPic[37] = {1050, 100, txLoadImage("img/Platformer/Ground_02.bmp"), 128,128, 90,90, false,"�����"};
        menuPic[38] = {1050, 200, txLoadImage("img/Platformer/Ground_03.bmp"), 128,128, 90,90, false,"�����"};
        menuPic[39] = {1050, 300, txLoadImage("img/Platformer/Ground_06.bmp"), 128,128, 90,90, false,"�����"};

        menuPic[40] = {900, 100, txLoadImage("img/Environment/Wooden_Barrel.bmp"), 128,128, 64,64, false,"�����"};
        menuPic[41] = {900, 200, txLoadImage("img/Environment/Wooden_Crate.bmp"),  128,128, 64,64, false,"�����"};
        menuPic[42] = {900, 300, txLoadImage("img/Environment/Well.bmp"),          480,480, 120,120, false,"�����"};
        menuPic[43] = {900, 400, txLoadImage("img/Environment/Street_Lantern.bmp"),480,480, 120,120, false,"�����"};
        menuPic[44] = {900, 500, txLoadImage("img/Environment/Decor_Cart.bmp"),    256,256, 128,128, false,"�����"};



         //����������� ��������
        Pictures centralPic[1000];


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
                                            menuPic[npic].image,
                                            menuPic[npic].w,
                                            menuPic[npic].h,
                                            menuPic[npic].w,
                                            menuPic[npic].h,
                                            menuPic[npic].visible,
                                            menuPic[npic].category
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
