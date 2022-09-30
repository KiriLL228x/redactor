#include "TXLib.h"
//структура картинки
struct Pictures
{
    int x;
    int y;
    HDC image;
    int w;
    int h;
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
  txTransparentBlt(txDC(), pct.x, pct.y, pct.w, pct.h, pct.image, 0, 0, TX_WHITE);
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
        menuPic[0] = {1000, 400, txLoadImage("img/Imgmenu/Wall1.bmp"), 90,90};
        menuPic[1] = {1000, 300, txLoadImage("img/Imgmenu/Wall2.bmp"), 90,90};
        menuPic[2] = {1000, 200, txLoadImage("img/Imgmenu/Wall3.bmp"), 90,90};
        menuPic[3] = {1000, 400, txLoadImage("img/Imgmenu/Ground_10.bmp"), 90,90};
        menuPic[4] = {1000, 300, txLoadImage("img/Imgmenu/Ground_11.bmp"), 90,90};
        menuPic[5] = {1000, 200, txLoadImage("img/Imgmenu/Ground_12.bmp"), 90,90};
        menuPic[6] = {1000, 400, txLoadImage("img/Imgmenu/Roof_A_04.bmp"), 90,40};
        menuPic[7] = {1000, 300, txLoadImage("img/Imgmenu/Roof_A_05.bmp"), 90,40};
        menuPic[8] = {1000, 200, txLoadImage("img/Imgmenu/Roof_B_04.bmp"), 90,40};
        menuPic[9] = {1000, 100, txLoadImage("img/Imgmenu/Roof_B_05.bmp"), 90,40};


    bool blockVisible = false;
    bool earthVisible = false;
    bool roofVisible = false;


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

        if(click(btn[0]))
        {
            blockVisible = true;
            earthVisible = false;
            roofVisible = false;
        }
        if(click(btn[1]))
        {
            blockVisible = false;
            earthVisible = false;
            roofVisible = true;
        }
        if(click(btn[2]))
        {
            blockVisible = false;
            earthVisible = true;
            roofVisible = false;
        }


        if(blockVisible)
        {
            for(int npic=0; npic <= 2; npic++)
            {
            drawPicture(menuPic[npic]);
            }
        }


        if(earthVisible)
        {
            for(int npic=3; npic <= 5; npic++)
            {
             drawPicture(menuPic[npic]);
            }
        }

        if(roofVisible)
        {
            for(int npic=6; npic <= 9; npic++)
            {
             drawPicture(menuPic[npic]);
            }
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
