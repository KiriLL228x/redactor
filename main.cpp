#include "TXLib.h"

void drawButton(int x, int y, const char* text)
{
    //x=30 y=30
        txSetColor(TX_BLACK);
        txSetFillColor(TX_WHITE);
        Win32::RoundRect (txDC(), x, y, x+150, y+40, 30, 30);
        txSetFillColor(TX_BLACK);

        txSetColor(TX_BLACK);
        txSelectFont("Times  New Roman", 32);
        txDrawText(x, y, x+150,y+40, text);
}

int main()
{
    txCreateWindow (1200, 800);
    txDisableAutoPause();
    txTextCursor (false);

    HDC Fon2 = txLoadImage("img/Fon2.bmp");
    HDC block1 = txLoadImage("img/Imgmenu/Wall1.bmp");
    HDC block2 = txLoadImage("img/Imgmenu/Wall2.bmp");
    HDC block3 = txLoadImage("img/Imgmenu/Wall3.bmp");




    while(!GetAsyncKeyState(VK_ESCAPE))
    {
        txBegin();
        txSetColor(TX_WHITE);
        txClear();
         txBitBlt(txDC(), 0, 0, 1200, 900, Fon2);

        //Кнопка 1
         drawButton(30,30,"Части стен");
        //Кнопка 2
         drawButton(200,30,"Крыша");
        //Кнопка 3
         drawButton(370,30,"Земли");

        txTransparentBlt(txDC(), 1000, 400, 90, 90, block1, 0, 0, TX_WHITE);
        txTransparentBlt(txDC(), 1000, 300, 90, 90, block2, 0, 0, TX_WHITE);
        txTransparentBlt(txDC(), 1000, 200, 90, 90, block3, 0, 0, TX_WHITE);


        txSleep(50);
        txEnd();

    }



    txDeleteDC(block1);
//    txDeleteDC(block2);
 //   txDeleteDC(block3);


    return 0;
}
//   txSetFillColor(TX_BLUE);
//    Win32::RoundRect (txDC(), 55, 105, 205, 145, 30, 30);
