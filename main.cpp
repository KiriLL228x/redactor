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
};
//структура кнопки
struct Button
{
  int x;
  int y;
  const char* text;
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

    //Массив
        Button btn[10];
        btn[0] = {30,30,"Части стен"};
        btn[1] = {200,30,"Крыша"};
        btn[2] = {370,30,"Земли"};

        Pictures menuPic[10];
        menuPic[0] = {1000, 400, txLoadImage("img/Imgmenu/Wall1.bmp"), 90,90, false};
        menuPic[1] = {1000, 300, txLoadImage("img/Imgmenu/Wall2.bmp"), 90,90, false};
        menuPic[2] = {1000, 200, txLoadImage("img/Imgmenu/Wall3.bmp"), 90,90, false};
        menuPic[3] = {1000, 400, txLoadImage("img/Imgmenu/Ground_10.bmp"), 90,90, false};
        menuPic[4] = {1000, 300, txLoadImage("img/Imgmenu/Ground_11.bmp"), 90,90, false};
        menuPic[5] = {1000, 200, txLoadImage("img/Imgmenu/Ground_12.bmp"), 90,90, false};
        menuPic[6] = {1000, 400, txLoadImage("img/Imgmenu/Roof_A_04.bmp"), 90,40, false};
        menuPic[7] = {1000, 300, txLoadImage("img/Imgmenu/Roof_A_05.bmp"), 90,40, false};
        menuPic[8] = {1000, 200, txLoadImage("img/Imgmenu/Roof_B_04.bmp"), 90,40, false};
        menuPic[9] = {1000, 100, txLoadImage("img/Imgmenu/Roof_B_05.bmp"), 90,40, false};


    while(!GetAsyncKeyState(VK_ESCAPE))
    {
        txBegin();
        txSetColor(TX_WHITE);
        txClear();
        txBitBlt(txDC(), 0, 0, 1200, 900, Fon3);

        //Рисование кнопок
        for(int nk=0; nk<3; nk++)
        {
            drawButton(btn[nk]);
        }
//видимость картинок меню
        if(click(btn[0]))
        {
            menuPic[0].visible=true;
            menuPic[1].visible=true;
            menuPic[2].visible=true;
        }
        if(click(btn[1]))
        {
            menuPic[3].visible=true;
            menuPic[4].visible=true;
            menuPic[5].visible=true;
        }
        if(click(btn[2]))
        {
            menuPic[6].visible=true;
            menuPic[7].visible=true;
            menuPic[8].visible=true;
            menuPic[9].visible=true;
        }


         for(int npic=0; npic <= 9; npic++)
            {
             txDeleteDC(menuPic[npic].image);
            }


        txSleep(50);
        txEnd();

    }

                for(int npic=0; npic <= 9; npic++)
            {
             txDeleteDC(menuPic[npic].image);
            }



    return 0;
}
//   txSetFillColor(TX_BLUE);
//    Win32::RoundRect (txDC(), 55, 105, 205, 145, 30, 30);
