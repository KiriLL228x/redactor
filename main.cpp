#include "TXLib.h"
//структура картинки
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
//структура кнопки
struct Button
{
  int x;
  int y;
  const char* text;
  string category;
};
//функция рисования кнопки

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

    //Массив
        Button btn[COUNT_BTN];
        btn[0] = {30,30,"Части стен","Стены"};
        btn[1] = {200,30,"Крыша","Крыша"};
        btn[2] = {370,30,"Земля","Земля"};
        btn[3] = {540,30,"Окна","Окна"};
        btn[4] = {710,30,"Двери","Двери"};

        //картинок меню
        Pictures menuPic[COUNT_PIC];
        menuPic[0] = {1000, 400, txLoadImage("img/Building/Wall_A_02.bmp"), 320, 320, 90,90, false,"Стены"};
        menuPic[1] = {1000, 300, txLoadImage("img/Building/Wall_B_02.bmp"), 320, 320, 90,90, false,"Стены"};
        menuPic[2] = {1000, 200, txLoadImage("img/Building/Wall_C_02.bmp"), 320, 320, 90,90, false,"Стены"};
        menuPic[3] = {1000, 400, txLoadImage("img/Platformer/Ground_10.bmp"), 128, 128, 90,90, false,"Земля"};
        menuPic[4] = {1000, 300, txLoadImage("img/Platformer/Ground_11.bmp"), 128, 128, 90,90, false,"Земля"};
        menuPic[5] = {1000, 200, txLoadImage("img/Platformer/Ground_12.bmp"), 128, 128, 90,90, false,"Земля"};
        menuPic[6] = {1000, 400, txLoadImage("img/Building/Roof_A_04.bmp"), 352, 160, 90,40, false,"Крыша"};
        menuPic[7] = {1000, 300, txLoadImage("img/Building/Roof_A_05.bmp"), 352, 160, 90,40, false,"Крыша"};
        menuPic[8] = {1000, 200, txLoadImage("img/Building/Roof_B_04.bmp"), 352, 160, 90,40, false,"Крыша"};
        menuPic[9] = {1000, 100, txLoadImage("img/Building/Roof_B_05.bmp"), 352, 160, 90,40, false,"Крыша"};
        menuPic[10] = {1000, 400, txLoadImage("img/Building/Window_01.bmp"), 128, 128, 64,64, false,"Окна"};
        menuPic[11] = {1000, 300, txLoadImage("img/Building/Window_02.bmp"), 128, 128, 64,64, false,"Окна"};
        menuPic[12] = {1000, 200, txLoadImage("img/Building/Window_03.bmp"), 128, 128, 64,64, false,"Окна"};
        menuPic[13] = {1000, 100, txLoadImage("img/Building/Door_01.bmp"), 128, 256, 64,128, false,"Двери"};
        menuPic[14] = {1000, 250, txLoadImage("img/Building/Door_02.bmp"), 128, 256, 64,128, false,"Двери"};
        menuPic[15] = {1000, 400, txLoadImage("img/Building/Door_03.bmp"), 128, 256, 64,128, false,"Двери"};
        menuPic[16] = {1000, 550, txLoadImage("img/Building/Door_04.bmp"), 128, 256, 64,128, false,"Двери"};

         //центральные картинки
        Pictures centralPic[COUNT_PIC];
        centralPic[0] = {250, 200, txLoadImage("img/Building/Wall_A_02.bmp"), 320, 320, 320, 320, false,"Стены"};
        centralPic[1] = {250, 200, txLoadImage("img/Building/Wall_B_02.bmp"), 320, 320, 320, 320, false,"Стены"};
        centralPic[2] = {250, 200, txLoadImage("img/Building/Wall_C_02.bmp"), 320, 320, 320, 320, false,"Стены"};
        centralPic[3] = {250, 200, txLoadImage("img/Platformer/Ground_10.bmp"), 128, 128, 128, 128, false,"Земля"};
        centralPic[4] = {250, 200, txLoadImage("img/Platformer/Ground_11.bmp"), 128, 128, 128, 128, false,"Земля"};
        centralPic[5] = {250, 200, txLoadImage("img/Platformer/Ground_12.bmp"), 128, 128, 128, 128, false,"Земля"};
        centralPic[6] = {250, 200, txLoadImage("img/Building/Roof_A_04.bmp"), 352, 160, 352, 160, false,"Крыша"};
        centralPic[7] = {250, 200, txLoadImage("img/Building/Roof_A_05.bmp"), 352, 160, 352, 160, false,"Крыша"};
        centralPic[8] = {250, 200, txLoadImage("img/Building/Roof_B_04.bmp"), 352, 160, 352, 160, false,"Крыша"};
        centralPic[9] = {250, 200, txLoadImage("img/Building/Roof_B_05.bmp"), 352, 160, 352, 160, false,"Крыша"};
        centralPic[10] = {250, 200, txLoadImage("img/Building/Window_01.bmp"), 128, 128, 128,128, false,"Окна"};
        centralPic[11] = {250, 200, txLoadImage("img/Building/Window_02.bmp"), 128, 128, 128,128, false,"Окна"};
        centralPic[12] = {250, 200, txLoadImage("img/Building/Window_03.bmp"), 128, 128, 128,128, false,"Окна"};
        centralPic[13] = {250, 200, txLoadImage("img/Building/Door_01.bmp"), 128, 256, 128,256, false,"Двери"};
        centralPic[14] = {250, 200, txLoadImage("img/Building/Door_02.bmp"), 128, 256, 128,256, false,"Двери"};
        centralPic[15] = {250, 200, txLoadImage("img/Building/Door_03.bmp"), 128, 256, 128,256, false,"Двери"};
        centralPic[16] = {250, 200, txLoadImage("img/Building/Door_04.bmp"), 128, 256, 128,256, false,"Двери"};

    while(!GetAsyncKeyState(VK_ESCAPE))
    {
        txBegin();
        txSetColor(TX_WHITE);
        txClear();
        txBitBlt(txDC(), 0, 0, 1200, 900, Fon3);

        //Рисование кнопок
        for(int nk=0; nk<5; nk++)
        {
            drawButton(btn[nk]);
        }
    //рисование картинок меню
        for(int npic=0; npic < COUNT_PIC; npic++)
        {
            drawPicture(menuPic[npic]);
        }
   //рисование центральных картинок
        for(int npic=0; npic < COUNT_PIC; npic++)
        {
            drawPicture(centralPic[npic]);
        }

        //видимость картинок меню по  категории
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

        //видимость центральных картинок по  категории
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
