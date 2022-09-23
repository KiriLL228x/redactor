#include "TXLib.h"
//структура картинки
struct Pictures
{
    int x;
    int y;
    HDC image;
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

int main()
{
    txCreateWindow (1200, 800);
    txDisableAutoPause();
    txTextCursor (false);

    HDC Fon2 = txLoadImage("img/Fon2.bmp");
    HDC block1 = txLoadImage("img/Imgmenu/Wall1.bmp");
    HDC block2 = txLoadImage("img/Imgmenu/Wall2.bmp");
    HDC block3 = txLoadImage("img/Imgmenu/Wall3.bmp");
    //-----------------------------------------------
    HDC ground1 = txLoadImage("img/Imgmenu/Ground_10.bmp");
    HDC ground2 = txLoadImage("img/Imgmenu/Ground_11.bmp");
    HDC ground3 = txLoadImage("img/Imgmenu/Ground_12.bmp");

    bool blockVisible = false;
    bool earthVisible = false;


    while(!GetAsyncKeyState(VK_ESCAPE))
    {
        txBegin();
        txSetColor(TX_WHITE);
        txClear();
         txBitBlt(txDC(), 0, 0, 1200, 900, Fon2);
    //Массив
        Button btn[10];
        btn[0] = {30,30,"Части стен"};
        btn[1] = {200,30,"Крыша"};
        btn[2] = {370,30,"Земли"};
        //Рисование кнопок
        for(int nk=0; nk<3; nk++)
        {
            drawButton(btn[nk]);
        }

        if(click(btn[0]))
        {
            blockVisible = true;
            earthVisible = false;
        }
        if(click(btn[1]))
        {
            blockVisible = false;
            earthVisible = true;
        }
        if(click(btn[2]))
        {
            blockVisible = false;
            earthVisible = true;
        }

        if(blockVisible)
        {
        txTransparentBlt(txDC(), 1000, 400, 90, 90, block1, 0, 0, TX_WHITE);
        txTransparentBlt(txDC(), 1000, 300, 90, 90, block2, 0, 0, TX_WHITE);
        txTransparentBlt(txDC(), 1000, 200, 90, 90, block3, 0, 0, TX_WHITE);
        }



        if(earthVisible)
        {
        txTransparentBlt(txDC(), 1000, 400, 90, 90, ground1, 0, 0, TX_WHITE);
        txTransparentBlt(txDC(), 1000, 300, 90, 90, ground2, 0, 0, TX_WHITE);
        txTransparentBlt(txDC(), 1000, 200, 90, 90, ground3, 0, 0, TX_WHITE);
        }

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
