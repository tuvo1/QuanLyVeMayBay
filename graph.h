#ifndef _GRAPH_H // 1 man hinh dai 210, rong 52
#define _GRAPH_H

#include"mylib.h"
#include <iostream>
#include <stdio.h>
#include <windows.h> 
#include <cstdlib>
#include <ctime>
#include <conio.h>
using namespace std;

//============================VE KHUNG=============================
void VeKhung() // 160:45 (Ti le 16:9)
{
	
	//gotoxy(1,1);
	char doc = 186;
	char ngang = 205;
	char traitren = 201;
	char traiduoi = 200;
	char phaitren = 187;
	char phaiduoi = 188;
	gotoxy(24,3);
	for (int i = 1; i <= 45; i++)
	{
		for (int j = 1; j <= 160; j++)
		{
			if (i == 1 || i == 45)
			{
				if (i == 1)
				{
					if (j == 1)
					{
						cout << traitren;
					}
					else
					{
						if (j == 160)
						{
							cout << phaitren;
						}
						else
						{
							cout << ngang;
						}
					}
				}
				else
				{
					if (j == 1)
					{
						cout << traiduoi;
					}
					else
					{
						if (j == 160)
						{
							cout << phaiduoi;
						}
						else
						{
							cout << ngang;
						}
					}
				}
			}
			else
			{
				if (j == 1 || j == 160)
				{
					cout << doc;
				}
				else
				{
					cout << " ";
				}
			}
		}
		gotoxy(24,3+i);
//		cout << endl;
	}
}
// ========================= CAC HAM XU LY CUA MENU =====================
void XoayLen (string *Menu)
{
	for (int i = 0; i < 11; i++)
	{
		Menu[i] = Menu[i+1];
	}
/*	Menu[0] = Menu[1]; // Menu[0] vai tro la o nho tam
	Menu[1] = Menu[2];
	Menu[2] = Menu[3];
	Menu[3] = Menu[4];
	Menu[4] = Menu[5]; */
	Menu[11] = Menu[0];
}
void XoayXuong(string *Menu)
{
	Menu[0] = Menu[11]; // Menu[0] vai tro la bien tam
	for (int i = 11; i > 0; i--)
	{
		Menu[i] = Menu[i-1];
	}
	/*
	Menu[5] = Menu[4];
	Menu[4] = Menu[3];
	Menu[3] = Menu[2];
	Menu[2] = Menu[1];
	Menu[1] = Menu[0];  */
}
//============================MENU CHINH==============================
int MainMenu(int a)
{
	
	string *Menu = new string[12];
	Menu[0] = ""; // bien tam
	Menu[1] = "1.THEM MAY BAY";
	Menu[2] = "2.XOA MAY BAY";
	Menu[3] = "3.HIEU CHINH MAY BAY";
	Menu[4] = "4.LAP CHUYEN BAY MOI";
	Menu[5] = "5.HIEU CHINH CHUYEN BAY";
	Menu[6] = "6.CAC CHUYEN BAY DEN X TRONG NGAY";
	Menu[7] = "7.DAT VE";
	Menu[8] = "8.HUY VE";
	Menu[9] = "9.IN DANH SACH HANH KHACH THUOC CHUYEN BAY";
	Menu[10] = "10.IN DANH SACH GHE CON TRONG CUA CHUYEN BAY";
	Menu[11] = "11.THONG KE LUOT THUC HIEN";
	AnConTro();
	string tam = Menu[a];
	for (int j = 0; j <= 11; j++)
	{
		if (Menu[6] == tam)
		{
			break;
		}
		XoayXuong(Menu);
	}
	for (int i = 1; i <= 11; i++)
	{
		if (i < 6)
		{
			ChangeColor(15);
			for (int j = 1; j <= i-1; j++)
			{
				cout << "  ";
			}
			cout << Menu[i] << endl << endl;
		}
		if (i == 6)
		{
			ChangeColor(15);
			cout << ">> ";
			for(int j = 3; j <= i -1; j++)
			{
				cout << "  ";
			}
			cout << Menu[6] << endl << endl;
			
			
		}
		if (i > 6)
		{
			ChangeColor(15);
			for (int j = 1; j <= 10-2*(i-6); j++)
			{
				cout << " ";
			}
			cout << Menu[i] << endl << endl;
		}
	}
	int i = a;
	int hoanhdo = wherex();
	int tungdo = wherey();
	while (!kbhit())
	{
		ChangeColor(15);
		gotoxy(175,0);
		InThoiGian();
	}
	gotoxy(hoanhdo,tungdo);
	ChangeColor(8);
	char x = getch();
	bool kytu;
	if (x == -32 || x == 0)
	{
		x = getch();
		kytu = 0;
	}
	else
	{
		kytu = 1;
	}
	while (x != 27 && x != 13) // Enter or Esc
	{
		if (x == 72 && !kytu) // Up
		{
			if (i != 1)
			{
				i--;
			}
			else
			{
				i = 11;
			}
			XoayXuong(Menu);
			gotoxy(0,0);
			for (int i = 1; i <= 11; i++) // Xu ly hinh anh
			{
				if (i < 6)
				{
					ChangeColor(8);
					cout << "                                                         ";
					gotoxy(0,wherey());
					for (int j = 1; j <= i-1; j++)
					{
						cout << "  ";
					}
					cout << Menu[i] << endl << endl;
				}
				if (i == 6)
				{
					ChangeColor(15);
					cout << "                                                         ";
					gotoxy(0,wherey());
					cout << ">> ";
					for(int j = 3; j <= i -1; j++)
					{
						cout << "  ";
					}
					cout << Menu[6] << endl << endl;
				}
				if (i > 6)
				{
					ChangeColor(8);
					cout << "                                                         ";
					gotoxy(0,wherey());
					for (int j = 1; j <= 10-2*(i-6); j++)
					{
						cout << " ";
					}
					cout << Menu[i] << endl << endl;
				}
			}
		//	gotoxy(0,60);
		//	cout << "Phim Up voi char la " << int(x);
		}
		if (x == 80 && !kytu) // Down
		{
			if (i != 11)
			{
				i++;
			}
			else
			{
				i = 1;
			}
			XoayLen(Menu);
			gotoxy(0,0);
			for (int i = 1; i <= 11; i++) // Xu ly hinh anh
			{
				if (i < 6)
				{
					ChangeColor(8);
					cout << "                                                         ";
					gotoxy(0,wherey());
					for (int j = 1; j <= i-1; j++)
					{
						cout << "  ";
					}
					cout << Menu[i] << endl << endl;
				}
				if (i == 6)
				{
					ChangeColor(15);
					cout << "                                                         ";
					gotoxy(0,wherey());
					cout << ">> ";
					for(int j = 3; j <= i -1; j++)
					{
						cout << "  ";
					}
					cout << Menu[6] << endl << endl;
				}
				if (i > 6)
				{
					ChangeColor(8);
					cout << "                                                         ";
					gotoxy(0,wherey());
					for (int j = 1; j <= 10-2*(i-6); j++)
					{
						cout << " ";
					}
					cout << Menu[i] << endl << endl;
				}
			}
		//	gotoxy(0,0);
		//	cout << "Phim Down voi char la " << int(x);
		}
		int hoanhdo = wherex();
		int tungdo = wherey();
		while (!kbhit())
		{
			ChangeColor(8);
			gotoxy(175,0);
			InThoiGian();
		}
		gotoxy(hoanhdo,tungdo);
		ChangeColor(8);
		x = getch();
		if (x == -32 || x == 0)
		{
			x = getch();
			kytu = 0;
		}
		else
		{
			kytu = 1;
		}
	}
	if (x == 13) // Enter
	{
		gotoxy(0,30);
		return i;
	}
	if (x == 27)
	{
		gotoxy(0,30);
		return 0;
	}
}

// ========================== KHUNG MAY BAY ======================================
void KhungMayBay()
{
	char ngangngoai = 205;
	char docngoai = 186;
	char traitren = 201;
	char phaitren = 187;
	char traiduoi = 200;
	char phaiduoi = 188;
	char ngangtrong = 196;
	char doctrong = 179;
	char ngangxuong = 209;
	char nganglen = 207;
	char docphai = 199;
	char doctrai = 182;
	char ngatu = 197;
	for (int i = 1; i <= 23; i++)
	{
		for (int j = 1; j <= 60; j++)
		{
			if (i == 1 || i == 23)
			{
				if (i == 1)
				{
					if (j == 1)
					{
						cout << traitren;
					}
					else
					{
						if (j == 60)
						{
							cout << phaitren;
						}
						else
						{
							if (j%20 == 0)
							{
								cout << ngangxuong;
							}
							else
							{
								cout << ngangngoai;
							}
						}
					}
				}
				else
				{
					if (j == 1)
					{
						cout << traiduoi;
					}
					else
					{
						if (j == 60)
						{
							cout << phaiduoi;
						}
						else
						{
							if (j%20 == 0)
							{
								cout << nganglen;
							}
							else
							{
								cout << ngangngoai;
							}
						}
					}
				}
			}
			else // khac dong dau va cuoi
			{
					if (i%2 == 1)
					{
						if (j == 1)
						{
							cout << docphai;
						}
						else
						{
							if (j == 60)
							{
								cout << doctrai;
							}
							else
							{
								if (j%20 == 0)
								{
									cout << ngatu;
								}
								else
								{
									cout << ngangtrong;
								}
							}
						}
					}
					else // i%2 == 0
					{
						if (j == 1 || j % 20 == 0)
						{
							if (j == 1 || j == 60)
							{
								cout << docngoai;
							}
							else
							{
								cout << doctrong;
							}
						}
						else
						cout << " ";
					}
			}
		}
		cout << endl;
	}
	gotoxy(7,1);
	cout << "So Hieu";
	gotoxy(28,1);
	cout << "Loai";
	gotoxy(47,1);
	cout << "So Cho";
}
// ============================================= KHUNG CHUYEN BAY ===============================
void KhungChuyenBay()
{
	char ngangngoai = 205;
	char docngoai = 186;
	char traitren = 201;
	char phaitren = 187;
	char traiduoi = 200;
	char phaiduoi = 188;
	char ngangtrong = 196;
	char doctrong = 179;
	char ngangxuong = 209;
	char nganglen = 207;
	char docphai = 199;
	char doctrai = 182;
	char ngatu = 197;
	for (int i = 1; i <= 23; i++)
	{
		for (int j = 1; j <= 120; j++)
		{
			if (i == 1 || i == 23)
			{
				if (i == 1)
				{
					if (j == 1)
					{
						cout << traitren;
					}
					else
					{
						if (j == 120)
						{
							cout << phaitren;
						}
						else
						{
							if (j%20 == 0)
							{
								cout << ngangxuong;
							}
							else
							{
								cout << ngangngoai;
							}
						}
					}
				}
				else
				{
					if (j == 1)
					{
						cout << traiduoi;
					}
					else
					{
						if (j == 120)
						{
							cout << phaiduoi;
						}
						else
						{
							if (j%20 == 0)
							{
								cout << nganglen;
							}
							else
							{
								cout << ngangngoai;
							}
						}
					}
				}
			}
			else // khac dong dau va cuoi
			{
					if (i%2 == 1)
					{
						if (j == 1)
						{
							cout << docphai;
						}
						else
						{
							if (j == 120)
							{
								cout << doctrai;
							}
							else
							{
								if (j%20 == 0)
								{
									cout << ngatu;
								}
								else
								{
									cout << ngangtrong;
								}
							}
						}
					}
					else // i%2 == 0
					{
						if (j == 1 || j % 20 == 0)
						{
							if (j == 1 || j == 120)
							{
								cout << docngoai;
							}
							else
							{
								cout << doctrong;
							}
						}
						else
						cout << " ";
					}
			}
		}
		cout << endl;
	}
	gotoxy(6,1);
	cout << "Ma Chuyen";
	gotoxy(24,1);
	cout << "Khoi hanh luc";
	gotoxy(49,1);
	cout << "Tu";
	gotoxy(68,1);
	cout << "Den";
	gotoxy(85,1);
	cout << "Trang Thai";
	gotoxy(105,1);
	cout << "Ma May bay";
}
// ======================= KHUNG GHE =========================================
void InKhungGhe (int SoLuong)
{
	int a = wherex();
	int b = wherey();
	char traitren = 218;
	char phaitren = 191;
	char traiduoi = 192;
	char phaiduoi = 217;
	char doc = 179;
	char ngang = 196;
	int dai;
	if (SoLuong%4 == 0)
	{
		dai = 4 + 4*(SoLuong/4 )+ 2;
	}
	else
	{
		dai = 4 + 4*(SoLuong/4+1) + 2;
	}
	for (int  i = 1; i <= 12; i++)
	{
		for (int j = 1; j <= dai; j++)
		{
			if (i == 1)
			{
				if (j == 1)
				{
					cout << traitren;
				}
				else
				{
					if (j == dai)
					{
						cout << phaitren;
					}
					else
					{
						cout << ngang;
					}
				}
			}
			else
			{
				if (i == 12)
				{
					if (j == 1)
					{
						cout << traiduoi;
					}
					else
					{
						if (j == dai)
						{
							cout << phaiduoi;
						}
						else
						{
							cout << ngang;
						}
					}
				}
				else
				{
					if (j == 1 || j == dai)
					{
						cout << doc;
					}
					else
					{
						cout << " ";
					}
				}
			}
		}
		gotoxy(wherex()-dai, wherey()+1);
	}
	gotoxy(a-2,b-2);
	for (int i = 1; i <= 4; i++)
	{
		for (int j = 1; j <= SoLuong/4+1; j++)
		{
			if (i == 1)
			{
				if (j == 1)
				{
					gotoxy(a+2,b+2);
				}
				if ((j-1)*4+i <= SoLuong)
				{
					if ((j-1)*4+i <= 9)
					{
						cout << "0" << (j-1)*4+i;
					}
					else
					{
						cout << (j-1)*4+i;
					}
				}
				cout << "  ";
			}
			if (i == 2)
			{
				if (j == 1)
				{
					gotoxy(a+2,b+2+2);
				}
				if ((j-1)*4+i <= SoLuong)
				{
					if ((j-1)*4+i <= 9)
					{
						cout << "0" << (j-1)*4+i;
					}
					else
					{
						cout << (j-1)*4+i;
					}
				}
				cout << "  ";
			}
			if (i == 3)
			{
				if (j == 1)
				{
					gotoxy(a+2,b+2+2+3);
				}
				if ((j-1)*4+i <= SoLuong)
				{
					if ((j-1)*4+i <= 9)
					{
						cout << "0" << (j-1)*4+i;
					}
					else
					{
						cout << (j-1)*4+i;
					}
				}
				cout  << "  ";
			}
			if (i == 4)
			{
				if (j == 1)
				{
					gotoxy(a+2,b+2+2+3+2);
				}
				if ((j-1)*4+i <= SoLuong)
				{
					if ((j-1)*4+i <= 9)
					{
						cout << "0" << (j-1)*4+i;
					}
					else
					{
						cout << (j-1)*4+i;
					}
				}
				cout << "  ";
			}
		}
	}
}
// ================ CUA SO NHAP DU LIEU CHUYEN BAY =============================
void CuaSoChuyenBay()
{
	char ngangngoai = 205;
	char docngoai = 186;
	char traitren = 201;
	char phaitren = 187;
	char traiduoi = 200;
	char phaiduoi = 188;
	char ngangtrong = 196;
	char doctrong = 179;
	char traitrentrong = 218;
	char phaitrentrong = 191;
	char traiduoitrong = 192;
	char phaiduoitrong = 217;

	for (int i = 1; i <= 28; i++)
	{
		for (int j = 1; j <= 41; j++)
		{
			if (i == 1 || i == 28)
			{
				if (i == 1)
				{
					if (j == 1)
					{
						cout << traitren;
					}
					else
					{
						if (j == 41)
						{
							cout << phaitren;
						}
						else
						{
							cout << ngangngoai;
						}
					}
				}
				else
				{
					if (j == 1)
					{
						cout << traiduoi;
					}
					else
					{
						if (j == 41)
						{
							cout << phaiduoi;
						}
						else
						{
							cout << ngangngoai;
						}
					}
				}
			}
			else
			{
				if (j == 1 || j == 41)
				{
					cout << docngoai;
				}
				else
				{
					cout << " ";
				}
			}
		}
		gotoxy(wherex() - 41, wherey()+1);
	}
	int a = wherex();
	int b = wherey();
	// Nut LUU
	gotoxy(wherex()+16,wherey()+1);
	for (int i = 1; i <= 3; i++)
	{
		for (int j = 1; j <= 9; j++)
		{
			if (i == 1)
			{
				if (j == 1)
				{
					cout << traitrentrong;
				}
				else
				{
					if (j == 9)
					{
						cout << phaitrentrong;
					}
					else
					{
						cout << ngangtrong;
					}
				}
			}
			else
			{
				if (i == 2)
				{
					if (j == 1)
					{
						cout << doctrong << "  LUU  " << doctrong;
					}
				}
				else
				{
					if (j == 1)
					{
						cout << traiduoitrong;
					}
					else
					{
						if (j == 9)
						{
							cout << phaiduoitrong;
						}
						else
						{
							cout << ngangtrong;
						}
					}
				}
			}
		}
		gotoxy(wherex()-9,wherey()+1);
	}
	gotoxy(a,b);
	// ========== IN O MA CHUYEN BAY ==============
	gotoxy(wherex() + 2, wherey() - 26);
	cout << "MA CHUYEN BAY  ";
	gotoxy(wherex(), wherey()-1);
	for (int i = 1; i <= 3; i++)
	{
		for (int j = 1; j <= 22; j++)
		{
			if (i == 1)
			{
				if (j == 1)
				{
					cout << traitrentrong;
				}
				else
				{
					if (j == 22)
					{
						cout << phaitrentrong;
					}
					else
					{
						cout << ngangtrong;
					}
				}
			}
			else
			{
				if (i == 3)
				{
					if (j == 1)
					{
						cout << traiduoitrong;
					}
					else
					{
						if (j == 22)
						{
							cout << phaiduoitrong;
						}
						else
						{
							cout << ngangtrong;
						}
					}
				}
				else
				{
					if (j == 1 || j == 22)
					{
						cout << doctrong;
					}
					else
					{
						cout << " ";
					}
				}
			}
		}
		gotoxy(wherex()-22, wherey()+1);
	}
	// =========== IN NGAY GIO KHOI HANH ==============
	gotoxy(wherex() - 6,wherey() + 1);
	cout << "NGAY GIO KHOI HANH";
	gotoxy(wherex() - 21, wherey() + 2); // Khung ngay
	for (int i = 1; i <= 3; i++)
	{
		for (int j = 1; j <= 6; j++)
		{
			if (i == 1)
			{
				if (j == 1)
				{
					cout << traitrentrong;
				}
				else
				{
					if (j == 6)
					{
						cout << phaitrentrong;
					}
					else
					{
						cout << ngangtrong;
					}
				}
			}
			else
			{
				if (i == 3)
				{
					if (j == 1)
					{
						cout << traiduoitrong;
					}
					else
					{
						if (j == 6)
						{
							cout << phaiduoitrong;
						}
						else
						{
							cout << ngangtrong;
						}
					}
				}
				else
				{
					if (j == 1)
					{
						cout << doctrong;
						ChangeColor(8);
						cout << " dd ";
						ChangeColor(15);
						cout << doctrong;
					}
				}
			}
		}
		gotoxy(wherex()-6, wherey() + 1);
	}
	gotoxy(wherex() + 6 + 1, wherey() - 2 );
	cout << "/";
	gotoxy(wherex()+1, wherey()-1); // Khung thang
	for (int i = 1; i <= 3; i++)
	{
		for (int j = 1; j <= 6; j++)
		{
			if (i == 1)
			{
				if (j == 1)
				{
					cout << traitrentrong;
				}
				else
				{
					if (j == 6)
					{
						cout << phaitrentrong;
					}
					else
					{
						cout << ngangtrong;
					}
				}
			}
			else
			{
				if (i == 3)
				{
					if (j == 1)
					{
						cout << traiduoitrong;
					}
					else
					{
						if (j == 6)
						{
							cout << phaiduoitrong;
						}
						else
						{
							cout << ngangtrong;
						}
					}
				}
				else
				{
					if (j == 1)
					{
						cout << doctrong;
						ChangeColor(8);
						cout << " mm ";
						ChangeColor(15);
						cout << doctrong;
					}
				}
			}
		}
		gotoxy(wherex()-6, wherey() + 1);
	}
	gotoxy(wherex()+6+1, wherey() - 2);
	cout << "/";
	gotoxy(wherex()+ 1, wherey()-1); // Khung nam
	for (int i = 1; i <= 3; i++)
	{
		for (int j = 1; j <= 8; j++)
		{
			if (i == 1)
			{
				if (j == 1)
				{
					cout << traitrentrong;
				}
				else
				{
					if (j == 8)
					{
						cout << phaitrentrong;
					}
					else
					{
						cout << ngangtrong;
					}
				}
			}
			else
			{
				if (i == 3)
				{
					if (j == 1)
					{
						cout << traiduoitrong;
					}
					else
					{
						if (j == 8)
						{
							cout << phaiduoitrong;
						}
						else
						{
							cout << ngangtrong;
						}
					}
				}
				else
				{
					if (j == 1)
					{
						cout << doctrong;
						ChangeColor(8);
						cout << " yyyy ";
						ChangeColor(15);
						cout << doctrong;
					}
				}
			}
		}
		gotoxy(wherex()-8, wherey() + 1);
	}
	gotoxy(wherex()-13,wherey() +1); // Khung gio
	for (int i = 1; i <= 3; i++)
	{
		for (int j = 1; j <= 6; j++)
		{
			if (i == 1)
			{
				if (j == 1)
				{
					cout << traitrentrong;
				}
				else
				{
					if (j == 6)
					{
						cout << phaitrentrong;
					}
					else
					{
						cout << ngangtrong;
					}
				}
			}
			else
			{
				if (i == 3)
				{
					if (j == 1)
					{
						cout << traiduoitrong;
					}
					else
					{
						if (j == 6)
						{
							cout << phaiduoitrong;
						}
						else
						{
							cout << ngangtrong;
						}
					}
				}
				else
				{
					if (j == 1)
					{
						cout << doctrong;
						cout << "    ";
						cout << doctrong;
					}
				}
			}
		}
		gotoxy(wherex()-6, wherey() + 1);
	}
	gotoxy(wherex()+6+1, wherey()-2);
	cout << ":";
	gotoxy(wherex()+1, wherey()-1); // Khung phut
	for (int i = 1; i <= 3; i++)
	{
		for (int j = 1; j <= 6; j++)
		{
			if (i == 1)
			{
				if (j == 1)
				{
					cout << traitrentrong;
				}
				else
				{
					if (j == 6)
					{
						cout << phaitrentrong;
					}
					else
					{
						cout << ngangtrong;
					}
				}
			}
			else
			{
				if (i == 3)
				{
					if (j == 1)
					{
						cout << traiduoitrong;
					}
					else
					{
						if (j == 6)
						{
							cout << phaiduoitrong;
						}
						else
						{
							cout << ngangtrong;
						}
					}
				}
				else
				{
					if (j == 1)
					{
						cout << doctrong;
						cout << "    ";
						cout << doctrong;
					}
				}
			}
		}
		gotoxy(wherex()-6, wherey() + 1);
	}
	// ================= DEN =========================
	gotoxy(wherex()-15, wherey()+2);
	cout << "DEN ";
	gotoxy(wherex(), wherey() - 1); // Khung Den;
	for (int i = 1; i <= 3; i++)
	{
		for (int j = 1; j <= 22; j++)
		{
			if (i == 1)
			{
				if (j == 1)
				{
					cout << traitrentrong;
				}
				else
				{
					if (j == 22)
					{
						cout << phaitrentrong;
					}
					else
					{
						cout << ngangtrong;
					}
				}
			}
			else
			{
				if (i == 3)
				{
					if (j == 1)
					{
						cout << traiduoitrong;
					}
					else
					{
						if (j == 22)
						{
							cout << phaiduoitrong;
						}
						else
						{
							cout << ngangtrong;
						}
					}
				}
				else
				{
					if (j == 1 || j == 22)
					{
						cout << doctrong;
					}
					else
					{
						cout << " ";
					}
				}
			}
		}
		gotoxy(wherex()-22, wherey()+1);
	}
	gotoxy(wherex()-4, wherey()+2);
	cout << "TRANG THAI ";
	gotoxy(wherex(),wherey()-1); // Khung trang thai
	for (int i = 1; i <= 3; i++)
	{
		for (int j = 1; j <= 14; j++)
		{
			if (i == 1)
			{
				if (j == 1)
				{
					cout << traitrentrong;
				}
				else
				{
					if (j == 14)
					{
						cout << phaitrentrong;
					}
					else
					{
						cout << ngangtrong;
					}
				}
			}
			else
			{
				if (i == 3)
				{
					if (j == 1)
					{
						cout << traiduoitrong;
					}
					else
					{
						if (j == 14)
						{
							cout << phaiduoitrong;
						}
						else
						{
							cout << ngangtrong;
						}
					}
				}
				else
				{
					if (j == 1 || j == 14)
					{
						cout << doctrong;
					}
					else
					{
						cout << " ";
					}
				}
			}
		}
		gotoxy(wherex()-14, wherey()+1);
	}
	// ===================== MA MAY BAY =============
	gotoxy(wherex()-15, wherey()+2);
	cout << "MA MAY BAY  ";
	gotoxy(wherex(), wherey()-1); // Khung Ma may bay
	for (int i = 1; i <= 3; i++)
	{
		for (int j = 1; j <= 22; j++)
		{
			if (i == 1)
			{
				if (j == 1)
				{
					cout << traitrentrong;
				}
				else
				{
					if (j == 22)
					{
						cout << phaitrentrong;
					}
					else
					{
						cout << ngangtrong;
					}
				}
			}
			else
			{
				if (i == 3)
				{
					if (j == 1)
					{
						cout << traiduoitrong;
					}
					else
					{
						if (j == 22)
						{
							cout << phaiduoitrong;
						}
						else
						{
							cout << ngangtrong;
						}
					}
				}
				else
				{
					if (j == 1 || j == 22)
					{
						cout << doctrong;
					}
					else
					{
						cout << " ";
					}
				}
			}
		}
		gotoxy(wherex()-22, wherey()+1);
	}
}
// ============== KHUNG POP UP NGAY/THANG/NAM ===================
void KhungPopUp()
{
	char ngangngoai = 205;
	char docngoai = 186;
	char traitren = 201;
	char phaitren = 187;
	char traiduoi = 200;
	char phaiduoi = 188;
	char ngangtrong = 196;
//	char doctrong = 179;
//	char ngangxuong = 209;
//	char nganglen = 207;
	char docphai = 199;
	char doctrai = 182;
//	char ngatu = 197;
	for (int i = 1; i <= 14; i++)
	{
		for (int j = 1; j <= 8; j++)
		{
			if (i == 1)
			{
				if (j == 1)
				{
					cout << traitren;
				}
				else
				{
					if (j == 8)
					{
						cout << phaitren;
					}
					else
					{
						cout << ngangngoai;
					}
				}
			}
			else
			{
				if (i == 3)
				{
					if (j == 1)
					{
						cout << docphai;
					}
					else
					{
						if (j == 8)
						{
							cout << doctrai;
						}
						else
						{
							cout << ngangtrong;
						}
					}
				}
				else
				{
					if (i == 14)
					{
						if (j == 1)
						{
							cout << traiduoi;
						}
						else
						{
							if (j == 8)
							{
								cout << phaiduoi;
							}
							else
							{
								cout << ngangngoai;
							}
						}
					}
					else
					{
						if (j == 1 || j == 8)
						{
							cout << docngoai;
						}
						else
						{
							cout << " ";
						}
					}
				}
			}
		}
		gotoxy(wherex()-8, wherey()+1);
	}
}
// =============== CLEAR KHUNG POP UP =====================
void ClearKhungPopUp()
{
	for (int i = 1; i <= 14; i++)
	{
		for (int j = 1; j <= 8; j++)
		{
			cout << " ";
		}
		gotoxy(wherex()-8, wherey()+1);
	}
}
// =================== KHUNG POP UP NOI DEN/TRANG THAI/MA MAY BAY ==================
void KhungPopUp2()
{
	char ngangngoai = 205;
	char docngoai = 186;
	char traitren = 201;
	char phaitren = 187;
	char traiduoi = 200;
	char phaiduoi = 188;
	char ngangtrong = 196;
//	char doctrong = 179;
//	char ngangxuong = 209;
//	char nganglen = 207;
	char docphai = 199;
	char doctrai = 182;
//	char ngatu = 197;
	for (int i = 1; i <= 14; i++)
	{
		for (int j = 1; j <= 22; j++)
		{
			if (i == 1)
			{
				if (j == 1)
				{
					cout << traitren;
				}
				else
				{
					if (j == 22)
					{
						cout << phaitren;
					}
					else
					{
						cout << ngangngoai;
					}
				}
			}
			else
			{
				if (i == 3)
				{
					if (j == 1)
					{
						cout << docphai;
					}
					else
					{
						if (j == 22)
						{
							cout << doctrai;
						}
						else
						{
							cout << ngangtrong;
						}
					}
				}
				else
				{
					if (i == 14)
					{
						if (j == 1)
						{
							cout << traiduoi;
						}
						else
						{
							if (j == 22)
							{
								cout << phaiduoi;
							}
							else
							{
								cout << ngangngoai;
							}
						}
					}
					else
					{
						if (j == 1 || j == 22)
						{
							cout << docngoai;
						}
						else
						{
							cout << " ";
						}
					}
				}
			}
		}
		gotoxy(wherex()-22, wherey()+1);
	}
}
// ================ CLEAR KHUNG POP UP 2 ==================
void ClearKhungPopUp2()
{
	for (int i = 1; i <= 14; i++)
	{
		for (int j = 1; j <= 22; j++)
		{
			cout << " ";
		}
		gotoxy(wherex()-22,wherey()+1);
	}
}
// ================== KHUNG DAT VE ===================
void KhungDatVe()
{
	char ngangngoai = 205;
	char docngoai = 186;
	char traitren = 201;
	char phaitren = 187;
	char traiduoi = 200;
	char phaiduoi = 188;
	char ngangtrong = 196;
	char doctrong = 179;
	char traitrentrong = 218;
	char phaitrentrong = 191;
	char traiduoitrong = 192;
	char phaiduoitrong = 217;
	for (int i = 1; i <= 23; i++)
	{
		for (int j = 1; j <= 50; j++)
		{
			if (i == 1)
			{
				if (j == 1)
				{
					cout << traitren;
				}
				else
				{
					if (j == 50)
					{
						cout << phaitren;
					}
					else
					{
						cout << ngangngoai;
					}
				}
			}
			else
			{
				if (i == 23)
				{
					if (j == 1)
					{
						cout << traiduoi;
					}
					else
					{
						if (j == 50)
						{
							cout << phaiduoi;
						}
						else
						{
							cout << ngangngoai;
						}
					}
				}
				else
				{
					if (j == 1 || j == 50)
					{
						cout << docngoai;
					}
					else
					{
						cout << " ";
					}
				}
			}
		}
		gotoxy(wherex()-50,wherey()+1);
	}
	// ======== CMND ==========
	gotoxy(wherex()+15, wherey()-20);
	cout << "CMND  ";
	gotoxy(wherex(),wherey()-1);
	for (int i = 1; i <= 3; i++ )
	{
		for (int j = 1; j <= 13; j++)
		{
			if (i == 1)
			{
				if (j == 1)
				{
					cout << traitrentrong;
				}
				else
				{
					if (j == 13)
					{
						cout << phaitrentrong;
					}
					else
					{
						cout << ngangtrong;
					}
				}
			}
			else
			{
				if (i == 3)
				{
					if (j == 1)
					{
						cout << traiduoitrong;
					}
					else
					{
						if (j == 13)
						{
							cout << phaiduoitrong;
						}
						else
						{
							cout << ngangtrong;
						}
					}
				}
				else
				{
					if (j == 1 || j == 13)
					{
						cout << doctrong;
					}
					else
					{
						cout << " ";
					}
				}
			}
		}
		gotoxy(wherex()-13,wherey()+1);
	}
//	HienConTro();
// ============ HO VA TEN ===================
	gotoxy(wherex()-19, wherey()+2);
//	char s = getch();
	cout << "HO VA TEN  ";
	gotoxy(wherex(),wherey()-1);
	for (int i = 1; i <= 3; i++ )
	{
		for (int j = 1; j <= 35; j++)
		{
			if (i == 1)
			{
				if (j == 1)
				{
					cout << traitrentrong;
				}
				else
				{
					if (j == 35)
					{
						cout << phaitrentrong;
					}
					else
					{
						cout << ngangtrong;
					}
				}
			}
			else
			{
				if (i == 3)
				{
					if (j == 1)
					{
						cout << traiduoitrong;
					}
					else
					{
						if (j == 35)
						{
							cout << phaiduoitrong;
						}
						else
						{
							cout << ngangtrong;
						}
					}
				}
				else
				{
					if (j == 1 || j == 35)
					{
						cout << doctrong;
					}
					else
					{
						cout << " ";
					}
				}
			}
		}
		gotoxy(wherex()-35,wherey()+1);
	}
	// ================== GIOI TINH ========================
	gotoxy(wherex()+4,wherey()+2);
	cout << "GIOI TINH  ";
	gotoxy(wherex(),wherey()-1);
	for (int i = 1; i <= 3; i++ )
	{
		for (int j = 1; j <= 7; j++)
		{
			if (i == 1)
			{
				if (j == 1)
				{
					cout << traitrentrong;
				}
				else
				{
					if (j == 7)
					{
						cout << phaitrentrong;
					}
					else
					{
						cout << ngangtrong;
					}
				}
			}
			else
			{
				if (i == 3)
				{
					if (j == 1)
					{
						cout << traiduoitrong;
					}
					else
					{
						if (j == 7)
						{
							cout << phaiduoitrong;
						}
						else
						{
							cout << ngangtrong;
						}
					}
				}
				else
				{
					if (j == 1 || j == 7)
					{
						cout << doctrong;
					}
					else
					{
						cout << " ";
					}
				}
			}
		}
		gotoxy(wherex()-7,wherey()+1);
	}
	// ============ MA CHUYEN ==============
	gotoxy(wherex()-21,wherey()+2);
	cout << "MA CHUYEN  ";
	gotoxy(wherex(),wherey()-1);
	for (int i = 1; i <= 3; i++ )
	{
		for (int j = 1; j <= 24; j++)
		{
			if (i == 1)
			{
				if (j == 1)
				{
					cout << traitrentrong;
				}
				else
				{
					if (j == 24)
					{
						cout << phaitrentrong;
					}
					else
					{
						cout << ngangtrong;
					}
				}
			}
			else
			{
				if (i == 3)
				{
					if (j == 1)
					{
						cout << traiduoitrong;
					}
					else
					{
						if (j == 24	)
						{
							cout << phaiduoitrong;
						}
						else
						{
							cout << ngangtrong;
						}
					}
				}
				else
				{
					if (j == 1 || j == 24)
					{
						cout << doctrong;
					}
					else
					{
						cout << " ";
					}
				}
			}
		}
		gotoxy(wherex()-24,wherey()+1);
	}
	// =========== GHE ============
	gotoxy(wherex()-4,wherey()+2);
	cout << "SO GHE  ";
	gotoxy(wherex(),wherey()-1);
	for (int i = 1; i <= 3; i++ )
	{
		for (int j = 1; j <= 7; j++)
		{
			if (i == 1)
			{
				if (j == 1)
				{
					cout << traitrentrong;
				}
				else
				{
					if (j == 7)
					{
						cout << phaitrentrong;
					}
					else
					{
						cout << ngangtrong;
					}
				}
			}
			else
			{
				if (i == 3)
				{
					if (j == 1)
					{
						cout << traiduoitrong;
					}
					else
					{
						if (j == 7)
						{
							cout << phaiduoitrong;
						}
						else
						{
							cout << ngangtrong;
						}
					}
				}
				else
				{
					if (j == 1 || j == 7)
					{
						cout << doctrong;
					}
					else
					{
						cout << " ";
					}
				}
			}
		}
		gotoxy(wherex()-7,wherey()+1);
	}
	gotoxy(wherex()-24+21,wherey()+2); // NUT DAT VE
	for (int i = 1; i <= 3; i++ )
	{
		for (int j = 1; j <= 10; j++)
		{
			if (i == 1)
			{
				if (j == 1)
				{
					cout << traitrentrong;
				}
				else
				{
					if (j == 10)
					{
						cout << phaitrentrong;
					}
					else
					{
						cout << ngangtrong;
					}
				}
			}
			else
			{
				if (i == 3)
				{
					if (j == 1)
					{
						cout << traiduoitrong;
					}
					else
					{
						if (j == 10)
						{
							cout << phaiduoitrong;
						}
						else
						{
							cout << ngangtrong;
						}
					}
				}
				else
				{
					if (j == 1)
					{
						cout << doctrong << " DAT VE " << doctrong;
					}
				}
			}
		}
		gotoxy(wherex()-10,wherey()+1);
	}
}
// =================== KHUNG HANH KHACH THUOC CHUYEN BAY ==================================
void KhungHanhKhachThuocChuyenBay()
{
	int x = wherex();
	int y = wherey();
	char ngangngoai = 205;
	char docngoai = 186;
	char traitren = 201;
	char phaitren = 187;
	char traiduoi = 200;
	char phaiduoi = 188;
	char ngangtrong = 196;
	char doctrong = 179;
	char ngangxuong = 209;
	char nganglen = 207;
	char docphai = 199;
	char doctrai = 182;
	char ngatu = 197;
	for (int i = 1; i <= 23; i++)
	{
		for (int j = 1; j <= 100; j++)
		{
			if (i == 1 || i == 23)
			{
				if (i == 1)
				{
					if (j == 1)
					{
						cout << traitren;
					}
					else
					{
						if (j == 100)
						{
							cout << phaitren;
						}
						else
						{
							if (j%20 == 0)
							{
								cout << ngangxuong;
							}
							else
							{
								cout << ngangngoai;
							}
						}
					}
				}
				else
				{
					if (j == 1)
					{
						cout << traiduoi;
					}
					else
					{
						if (j == 100)
						{
							cout << phaiduoi;
						}
						else
						{
							if (j%20 == 0)
							{
								cout << nganglen;
							}
							else
							{
								cout << ngangngoai;
							}
						}
					}
				}
			}
			else // khac dong dau va cuoi
			{
					if (i%2 == 1)
					{
						if (j == 1)
						{
							cout << docphai;
						}
						else
						{
							if (j == 100)
							{
								cout << doctrai;
							}
							else
							{
								if (j%20 == 0)
								{
									cout << ngatu;
								}
								else
								{
									cout << ngangtrong;
								}
							}
						}
					}
					else // i%2 == 0
					{
						if (j == 1 || j % 20 == 0)
						{
							if (j == 1 || j == 100)
							{
								cout << docngoai;
							}
							else
							{
								cout << doctrong;
							}
						}
						else
						cout << " ";
					}
			}
		}
		gotoxy(wherex()-100,wherey()+1);
	}
	gotoxy(6,1+y);
	CanhGiua(10+x,3);
	cout << "STT";
	gotoxy(24,1+y);
	CanhGiua(30+x,5);
	cout << "SO VE";
	gotoxy(49,1+y);
	CanhGiua(50+x,7);
	cout << "SO CMND";
	gotoxy(68,1+y);
	CanhGiua(70+x, 6);
	cout << "HO TEN";
	gotoxy(85,1+y);
	CanhGiua(90+x,4);
	cout << "PHAI";
}
// ========================= KHUNG DANH SACH CHUYEN BAY DEN X ====================
void KhungChuyenBayDenX()
{
	int x = wherex();
	int y = wherey();
	char ngangngoai = 205;
	char docngoai = 186;
	char traitren = 201;
	char phaitren = 187;
	char traiduoi = 200;
	char phaiduoi = 188;
	char ngangtrong = 196;
	char doctrong = 179;
	char ngangxuong = 209;
	char nganglen = 207;
	char docphai = 199;
	char doctrai = 182;
	char ngatu = 197;
	for (int i = 1; i <= 23; i++)
	{
		for (int j = 1; j <= 60; j++)
		{
			if (i == 1 || i == 23)
			{
				if (i == 1)
				{
					if (j == 1)
					{
						cout << traitren;
					}
					else
					{
						if (j == 60)
						{
							cout << phaitren;
						}
						else
						{
							if (j%20 == 0)
							{
								cout << ngangxuong;
							}
							else
							{
								cout << ngangngoai;
							}
						}
					}
				}
				else
				{
					if (j == 1)
					{
						cout << traiduoi;
					}
					else
					{
						if (j == 60)
						{
							cout << phaiduoi;
						}
						else
						{
							if (j%20 == 0)
							{
								cout << nganglen;
							}
							else
							{
								cout << ngangngoai;
							}
						}
					}
				}
			}
			else // khac dong dau va cuoi
			{
					if (i%2 == 1)
					{
						if (j == 1)
						{
							cout << docphai;
						}
						else
						{
							if (j == 60)
							{
								cout << doctrai;
							}
							else
							{
								if (j%20 == 0)
								{
									cout << ngatu;
								}
								else
								{
									cout << ngangtrong;
								}
							}
						}
					}
					else // i%2 == 0
					{
						if (j == 1 || j % 20 == 0)
						{
							if (j == 1 || j == 60)
							{
								cout << docngoai;
							}
							else
							{
								cout << doctrong;
							}
						}
						else
						cout << " ";
					}
			}
		}
		gotoxy(wherex()-60,wherey()+1);
	}
	gotoxy(0,y+1);
	CanhGiua(x+10,9);
	cout << "Ma Chuyen";
	CanhGiua(x+30,14);
	cout << "Ngay Xuat Phat";
	CanhGiua(x+50,7);
	cout << "Con Ghe";
	
}
#endif
