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

    HDC block1 = txLoadImage("img/block1.bmp");
    HDC block2 = txLoadImage("img/block2.bmp");
    HDC block3 = txLoadImage("img/block3.bmp");




    while(!GetAsyncKeyState(VK_ESCAPE))
    {
        txBegin();
        txSetColor(TX_WHITE);
        txSetFillColor(TX_YELLOW);
        txClear();

        //Кнопка 1
         drawButton(30,30,"Блоки");
        //Кнопка 2
         drawButton(200,30,"Крыша");
        //Кнопка 3
         drawButton(370,30,"Земли");

        txTransparentBlt(txDC(), 1000, 400, 80, 72, block1, 0, 0, TX_WHITE);
        txTransparentBlt(txDC(), 1000, 300, 80, 72, block2, 0, 0, TX_WHITE);
        txTransparentBlt(txDC(), 1000, 200, 80, 72, block3, 0, 0, TX_WHITE);




        txSleep(50);
        txEnd();

    }



    txDeleteDC(block1);
    txDeleteDC(block2);
    txDeleteDC(block3);


    return 0;
}
//   txSetFillColor(TX_BLUE);
//    Win32::RoundRect (txDC(), 55, 105, 205, 145, 30, 30);
