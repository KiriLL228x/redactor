#include "TXLib.h"
//структура картинки
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

//int wh()
//{
//    menuPic[npic].w_scr = menuPic[npic].w / 3;
 //   menuPic[npic].h_scr = menuPic[npic].h / 3;
//return 1;
//}

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

    //Массив
        Button btn[COUNT_BTN];
        btn[0] = {30,30,"Части стен","Стены"};
        btn[1] = {200,30,"Крыша","Крыша"};
        btn[2] = {370,30,"Земля","Земля"};
        btn[3] = {540,30,"Окна","Окна"};
        btn[4] = {710,30,"Двери","Двери"};
        btn[5] = {880,30,"Декор","Декор"};

        //картинок меню
        Pictures menuPic[COUNT_PIC];
        menuPic[0] = {900, 100, "img/Стены/Wall_A_02.bmp" };
        menuPic[1] = {900, 200, "img/Стены/Wall_B_02.bmp" };
        menuPic[2] = {900, 300, "img/Стены/Wall_C_02.bmp" };
        menuPic[3] = {860, 100, "img/Стены/Wall_A_01.bmp" };
        menuPic[4] = {1000,100, "img/Стены/Wall_A_03.bmp"};
        menuPic[5] = {860, 200, "img/Стены/Wall_B_01.bmp" };
        menuPic[6] = {1000,200, "img/Стены/Wall_B_03.bmp"};
        menuPic[7] = {860, 300, "img/Стены/Wall_C_01.bmp" };
        menuPic[8] = {1000,300, "img/Стены/Wall_C_03.bmp"};

        menuPic[9] = {930, 100, "img/Крыша/Roof_A_01.bmp"};
        menuPic[10] = {1000, 100, "img/Крыша/Roof_A_02.bmp"};
        menuPic[11] = {1070, 100, "img/Крыша/Roof_A_03.bmp"};
        menuPic[12] = {1050, 200, "img/Крыша/Roof_A_04.bmp"};
        menuPic[13] = {950, 200, "img/Крыша/Roof_A_05.bmp"};
        menuPic[14] = {930, 300, "img/Крыша/Roof_B_01.bmp"};
        menuPic[15] = {1000, 300, "img/Крыша/Roof_B_02.bmp"};
        menuPic[16] = {1070, 300, "img/Крыша/Roof_B_03.bmp"};
        menuPic[17] = {1050, 400, "img/Крыша/Roof_B_04.bmp"};
        menuPic[18] = {950, 400, "img/Крыша/Roof_B_05.bmp"};


        menuPic[19] = {900, 100,"img/Окна/Window_01.bmp"};
        menuPic[20] = {900, 200, "img/Окна/Window_02.bmp"};
        menuPic[21] = {900, 300, "img/Окна/Window_03.bmp"};
        menuPic[22] = {1050, 100, "img/Окна/Stone_Window_01.bmp"};
        menuPic[23] = {1050, 200, "img/Окна/Stone_Window_02.bmp"};
        menuPic[24] = {1050, 300, "img/Окна/Stone_Window_03.bmp"};

        menuPic[25] = {900, 100, "img/Двери/Door_01.bmp"};
        menuPic[26] = {900, 250, "img/Двери/Door_02.bmp"};
        menuPic[27] = {900, 400, "img/Двери/Door_03.bmp"};
        menuPic[28] = {900, 550, "img/Двери/Door_04.bmp"};
        menuPic[29] = {1050, 100, "img/Двери/Wide_Door_01.bmp"};
        menuPic[30] = {1050, 250, "img/Двери/Wide_Door_02.bmp"};
        menuPic[31] = {1050, 400, "img/Двери/Wide_Door_03.bmp"};
        menuPic[32] = {1050, 550,"img/Двери/Wide_Door_04.bmp"};

        menuPic[33] = {900, 100,"img/Земля/Ground_10.bmp"};
        menuPic[34] = {900, 200, "img/Земля/Ground_11.bmp"};
        menuPic[35] = {900, 300, "img/Земля/Ground_12.bmp"};
        menuPic[36] = {900, 400, "img/Земля/Ground_01.bmp"};
        menuPic[37] = {1050, 100, "img/Земля/Ground_02.bmp"};
        menuPic[38] = {1050, 200, "img/Земля/Ground_03.bmp"};
        menuPic[39] = {1050, 300, "img/Земля/Ground_06.bmp"};

        menuPic[40] = {900, 100, "img/Декор/Wooden_Barrel.bmp"};
        menuPic[41] = {900, 200, "img/Декор/Wooden_Crate.bmp"};
        menuPic[42] = {900, 300, "img/Декор/Well.bmp"};
        menuPic[43] = {900, 400, "img/Декор/Street_Lantern.bmp"};
        menuPic[44] = {900, 500, "img/Декор/Decor_Cart.bmp"};

       for(int npic=0; npic < COUNT_PIC; npic++)
       {
         menuPic[npic].visible = false;

         menuPic[npic].w = get_w(menuPic[npic].adress);
         menuPic[npic].h = get_h(menuPic[npic].adress);

         menuPic[npic].w_scr = menuPic[npic].w / 3;
         menuPic[npic].h_scr = menuPic[npic].h / 3;




         menuPic[npic].image = txLoadImage (menuPic[npic].adress.c_str());

         int pos_1 = menuPic[npic].adress.find("/");
         int pos_2 = menuPic[npic].adress.find("/", pos_1+1);

         menuPic[npic].category = menuPic[npic].adress.substr(pos_1+1, pos_2-pos_1-1);

       }

         //центральные картинки
        Pictures centralPic[1000];


    while(!GetAsyncKeyState(VK_ESCAPE))
    {
        txBegin();
        txSetColor(TX_WHITE);
        txClear();
        txBitBlt(txDC(), 0, 0, 1200, 900, Fon3);

        //Рисование кнопок
        for(int nk=0; nk<COUNT_BTN; nk++)
        {
            drawButton(btn[nk]);
        }
    //рисование картинок меню
        for(int npic=0; npic < COUNT_PIC; npic++)
        {
            drawPicture(menuPic[npic]);
        }
   //рисование центральных картинок
        for(int npic=0; npic < nCentralPic; npic++)
        {
            drawPicture(centralPic[npic]);
        }

        //видимость картинок меню по  категории
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


        //выбор центральных картинок
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


        // передвижение выбраной центральной картинки
       if(vybor>=0)
        {
          if(GetAsyncKeyState(VK_RIGHT)) centralPic[vybor].x += 5;
          if(GetAsyncKeyState(VK_LEFT)) centralPic[vybor].x -= 5;
          if(GetAsyncKeyState(VK_UP)) centralPic[vybor].y -= 5;
          if(GetAsyncKeyState(VK_DOWN)) centralPic[vybor].y += 5;
        }



        // Удаление центральной картинки с экрана
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
