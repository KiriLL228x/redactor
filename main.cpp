#include "TXLib.h"
//структура картинки
struct Pictures
{
    int x;
    int y;
    HDC image;
    int w;
    int h;
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
    txTransparentBlt(txDC(), pct.x, pct.y, pct.w, pct.h, pct.image, 0, 0, TX_WHITE);
}

};

int main()
{
    txCreateWindow (1200, 800);
    txDisableAutoPause();
    txTextCursor (false);

    HDC Fon3 = txLoadImage("img/fon3.bmp");

    int COUNT_BTN = 5;
    int COUNT_MENU_PIC = 10;

    //Массив
        Button btn[COUNT_BTN];
        btn[0] = {30,30,"Части стен","Стены"};
        btn[1] = {200,30,"Крыша","Крыша"};
        btn[2] = {370,30,"Земля","Земля"};
        btn[3] = {540,30,"Окна","Окна"};
        btn[4] = {710,30,"Двери","Двери"};


        Pictures menuPic[COUNT_MENU_PIC];
        menuPic[0] = {1000, 400, txLoadImage("img/Imgmenu/Wall1.bmp"), 90,90, false,"Стены"};
        menuPic[1] = {1000, 300, txLoadImage("img/Imgmenu/Wall2.bmp"), 90,90, false,"Стены"};
        menuPic[2] = {1000, 200, txLoadImage("img/Imgmenu/Wall3.bmp"), 90,90, false,"Стены"};
        menuPic[3] = {1000, 400, txLoadImage("img/Imgmenu/Ground_10.bmp"), 90,90, false,"Земля"};
        menuPic[4] = {1000, 300, txLoadImage("img/Imgmenu/Ground_11.bmp"), 90,90, false,"Земля"};
        menuPic[5] = {1000, 200, txLoadImage("img/Imgmenu/Ground_12.bmp"), 90,90, false,"Земля"};
        menuPic[6] = {1000, 400, txLoadImage("img/Imgmenu/Roof_A_04.bmp"), 90,40, false,"Крыша"};
        menuPic[7] = {1000, 300, txLoadImage("img/Imgmenu/Roof_A_05.bmp"), 90,40, false,"Крыша"};
        menuPic[8] = {1000, 200, txLoadImage("img/Imgmenu/Roof_B_04.bmp"), 90,40, false,"Крыша"};
        menuPic[9] = {1000, 100, txLoadImage("img/Imgmenu/Roof_B_05.bmp"), 90,40, false,"Крыша"};


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

        for(int npic=0; npic < COUNT_MENU_PIC; npic++)
        {
            drawPicture(menuPic[npic]);
        }

        //видимость картинок меню по  категории
        for(int nk=0; nk<5; nk++)
        {
            if(click(btn[nk]))
            {
                for(int npic=0; npic < COUNT_MENU_PIC; npic++)
                {
                    menuPic[npic].visible= false;
                    if(menuPic[npic].category == btn[nk].category)
                    {
                        menuPic[npic].visible=true;
                    }
                }
            }
        }






        txSleep(50);
        txEnd();

    }

            for(int npic=0; npic < COUNT_MENU_PIC; npic++)
            {
                txDeleteDC(menuPic[npic].image);
            }



    return 0;
}
//   txSetFillColor(TX_BLUE);
//    Win32::RoundRect (txDC(), 55, 105, 205, 145, 30, 30);
