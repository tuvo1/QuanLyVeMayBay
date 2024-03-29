#ifndef _MYLIB_H
#define _MYLIB_H



#include<iostream>
#include<conio.h>
#include<windows.h>
#include<ctime>
using namespace std;
void fullscreen()
{
	keybd_event(VK_MENU,0x38,0,0);
	keybd_event(VK_RETURN,0x1c,0,0);
	keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0);
	keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);
}
void gotoxy(int x, int y) 
{
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}
int wherex()
{
HANDLE hConsoleOutput;
hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
return screen_buffer_info.dwCursorPosition.X;
}
int wherey( void )
{
HANDLE hConsoleOutput;
hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
return screen_buffer_info.dwCursorPosition.Y;
}

void AnConTro()
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = FALSE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}
void HienConTro()
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = TRUE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}
void ChangeColor(int k)
{
	HANDLE hConsoleColor;
	hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsoleColor, k);
}
//=============================SO NGAY TRONG THANG===================
int DaysOfMounth(int mm, int yy) // So ngay toi da cua thang
{
	if (mm == 4 || mm == 6 || mm == 9 || mm == 11 ) return 30; // Thang co 30 ngay
	if (mm == 2) // Thang 2
	{
		if (yy%4 == 0) return 29; // Nam nhuan
		return 28; // Nam khong nhuan
	}
	return 31; // Thang co 31 ngay
}
//===========================KIEM TRA NGAY HOP LE====================
bool CheckDay(int dd, int mm, int yy)
{
	if (dd > 31 || dd <= 0) return 0; // Ngay khong am hoac lon hon 31
	if (mm > 12 || mm <= 0) return 0; // Khong co thang am hoac lon hon 12
	if (mm == 4 || mm == 6 || mm == 9 || mm == 11) // Thang co 30 ngay
	{
		if (dd > 30) return 0;
	}
	if (mm == 2) // Thang 2
	{
		if (yy%4 == 0) // Nam nhuan
		{
			if (dd > 29) return 0; // Nam nhuan
		}
		if (dd > 28) return 0; // Nam khong nhuan
	}
	if (dd > 31) return 0; // Thang co 31 ngay
	return 1;
}
//==========================DEM KHOANG CÃCH GIUA 2 NGAY====================
int CountDays(int dd1,int mm1,int yy1,int dd2, int mm2, int yy2) // dd1,mm1,yy1 phai truoc dd2,mm2,yy2. Dem khoang cach ngay giua 2 ngay
{
	int count = 0;
	if (mm1 == mm2 && yy1 == yy2) // Cung thang nam
	{
		for (int i = dd1; i <= dd2; i++)
		{
			count++;
		}
		return count - 1;
	}
	if (yy1 == yy2) // Cung nam
	{ 
		count = count + CountDays(dd1,mm1,yy1,DaysOfMounth(mm1,yy1),mm1,yy1); // Tu ngay dd1 thang mm1 den het thang mm1
		for (int i = mm1 + 1; i < mm2; i++)
		{
			count = count + DaysOfMounth(i,yy1); // Cac thang nam giua mm1 va mm2
		}
		return (count + CountDays(1,mm2,yy2,dd2,mm2,yy2) + 1); // Cong them dau thang mm2 den ngay dd2 thang mm2
	}
	// Khac nam
	count = count + CountDays(dd1,mm1,yy1,31,12,yy1); // Tu dd1,mm1,yy1 den het nam yy1
	for (int i = yy1 +1; i < yy2; i++) // Cac nam giua yy1 va yy2
	{
		if (i%4 == 0) count += 366; // Nam nhuan
		else count += 365; // Nam khong nhuan
	}
	return (count + CountDays(1,1,yy2,dd2,mm2,yy2) + 1); // Tu dau nam yy2 den ngay dd2 thang mm2 nam yy2
}
//============================DO DAI SO DUONG==================
int DoDaiSoDuong(int a)
{
	if (a == 0) return 1;
	int dem = 0;
	while (a != 0)
	{
		a = a/10;
		dem++;
	}
	return dem;
}
//=========================LOC LAY SO=================================
int LaySo(int giatri, bool DiChuyenDeThoat, char &a) // Kiem tra Di chuyen co thoat khong va nhan phim vua nhan
{
	int i = DoDaiSoDuong(giatri); // Chong tran bit + khong cho backspace khong hop le
	HienConTro();
	unsigned int so = giatri;
	int b;
//	if (a <= 0) a = getch(); // clear a
	a = getch();
	while (a != 13)
	{
		if  ((DiChuyenDeThoat && a == -32) || a == 27 || a == 19)
		{
			break;
		}
		if ((a >= 48 && a <= 57) && i < 10) // nuot phim khi khong phai la so
		{
			if (so == 0 && a == 48)
			{
				
			}
			else
			{
				i++;
				b = a - 48;
				cout << b;
				so = so * 10 + b;
			}
		}
		if (a == 8 && i > 0) // Nguoi dung nhan backspace
		{
			i--;
			so = so/10;
			int x = wherex();
   			int y = wherey();
			gotoxy(x-1, y);
			cout << " ";
			if (!x) gotoxy(0,0);
			else gotoxy(x-1,y);
		}
		a = getch();
	}
	return so;
}
void CanhGiua(int vitrigiua, int dodai)
{
	int tungdo = wherey();
	gotoxy(vitrigiua - dodai/2, tungdo);
}
int LaySoCMND(string &x,char &a, bool &kytu)
{
	int dodaichuoi = x.length();

	cout << x;
	HienConTro();

	while (1)
	{
		while (!(a == 77 && !kytu) && a != 27) 
		{
			if (a == 8) 
			{
				if (dodaichuoi <= 0)
				{
					AnConTro();
					char doc = 179;
					int hoanhdo = wherex();
					int tungdo = wherey();
					cout << "Khong the xoa";
					Sleep(500);
					gotoxy(hoanhdo,tungdo);
					cout << "          " << doc << "      ";
					gotoxy(hoanhdo,tungdo);
					HienConTro();
				}
				else
				{
					int hoanhdo = wherex();
					int tungdo = wherey();
					gotoxy(hoanhdo - 1, tungdo);
					cout << " ";
					gotoxy(hoanhdo - 1, tungdo);
				
					x.erase(x.end() - 1, x.end());
					dodaichuoi--;
				}
			}
			if ((a >= 48 && a <= 57) && kytu) // 0->9
			{
				if (dodaichuoi == 9)
				{
					int hoanhdo = wherex();
					int tungdo = wherey();
					gotoxy(hoanhdo - 9,tungdo);
					cout << "Qua 9 ky tu";
					Sleep(300);
					gotoxy(hoanhdo - 9,tungdo);
					char doc = 179;
					cout << "          " << doc;
					gotoxy(hoanhdo - 9,tungdo);
					cout << x;
				}
				else
				{
					cout << a;
					x = x + a;
					dodaichuoi++;
				}
			}
		//	cout << "trong";
			a = getch();
			if (a == -32 || a == 0)
			{
				kytu = 0;
				a = getch();
			}
			else
			{
				kytu = 1;
			}
			
		}
		if (a == 27)
		{
			return 0;
		}
		if (dodaichuoi < 9)
		{
			AnConTro();
			int hoanhdo = wherex();
			int tungdo = wherey();
			gotoxy(hoanhdo - dodaichuoi,tungdo);
			cout << "Du 9 ky tu";
			Sleep(300);
			gotoxy(hoanhdo - dodaichuoi, tungdo);
			cout << "          ";
			gotoxy(hoanhdo,tungdo);
			HienConTro();
		}
		else
		{
			return 1;
		}
	//		cout << "ngoai";
		a = getch();
	
		if (a == -32 || a == 0)
		{
			kytu = 0;
			a = getch();
		}
		else
		{
			kytu = 1;
		}
		if (a == 27)
		{
			return 0;
		}
	}
}
//=================================CHU IN HOA=====================
char InHoa(char a)
{
	if (a >= 97 && a <= 122) // tu 'a' toi 'z'
	{
		a = a - 32;
	}
	return a;
}
//============================= NHAP HO VA TEN ============================
int NhapHoTen(string &name, char &x, bool &kytu)
{
	cout << name;
	x = getch();
	int dodaichuoi = name.length();
	if (x == -32 || x == 0)
	{
		kytu = 0;
		x = getch();
	}
	else
	{
		kytu = 1;
	}
	while (1)
	{
	while (!((x == 75 || x == 77) && !kytu) && x != 27) 
	{
		if (x == 8) 
		{
			if (dodaichuoi > 0)
			{
				int hoanhdo = wherex();
				int tungdo = wherey();
				gotoxy(hoanhdo - 1, tungdo);
				cout << " ";
				gotoxy(hoanhdo - 1, tungdo);
				dodaichuoi--;
				name.erase(name.end() - 1, name.end());
			}
			else
			{
				CanhGiua(35,33);
				cout << "Khong the xoa";
				Sleep(300);
				CanhGiua(35,13);
				cout << "             ";
				gotoxy(35,wherey());
			}
		}
		if (((x >= 97 && x <= 122) || (x >= 65 && x <= 90) || x == 32) && kytu)
		{
			if (x != 32)
			{
				AnConTro();
				x = InHoa(x);
				dodaichuoi++;
				name = name + x;
				gotoxy(19,32);
				cout << "                                 ";
				CanhGiua(35,name.length());
				cout << name;
				HienConTro();
			}
			else
			{
				if (name[name.length()-1] != 32)
				{
					AnConTro();
					cout << x;
					dodaichuoi++;
					name = name + x;
					gotoxy(19,32);
					cout << "                                 ";
					CanhGiua(35,name.length());
					cout << name;
					HienConTro();
				}
			}
		}
		x = getch();
		if (x == -32 || x == 0)
		{
			kytu = 0;
			x = getch();
		}
		else
		{
			kytu = 1;
		}
	}
	if (name[name.length()-1] == 32 && name.length() > 0)
	{
		name.erase(name.length()-1,name.length());
	}
	if (dodaichuoi == 0 && x != 27)
	{
		AnConTro();
		CanhGiua(35,34);
		cout << "Khong bo trong";
		Sleep(500);
		CanhGiua(35,34);
		cout << "              ";
		gotoxy(35,wherey());
		HienConTro();
	}
	else
	{
		if (x == 27)
		{ 
			return 0;
		}
		return 1;
	}
	x = getch();
	if (x == -32 || x == 0)
	{
		kytu = 0;
		x = getch();
	}
	else
	{
		kytu = 1;
	}
	}
}
void InThoiGian()
{
	time_t hientai = time(0);
	tm *thoigian = localtime(&hientai);
	switch (thoigian->tm_wday)
	{
		case 1:
			{
				cout << "Monday";
				break;
			}
		case 2:
			{
				cout << "Tuesday";
				break;
			}
		case 3:
			{
				cout << "Wednesday";
				break;
			}
		case 4:
			{
				cout << "Thursday";
				break;
			}
		case 5:
			{
				cout << "Friday";
				break;
			}
		case 6:
			{
				cout << "Saturday";
				break;
			}
		case 7:
			{
				cout << "Sunday";
				break;
			}
	}
	cout <<  ", " << thoigian->tm_mday << "/" << thoigian->tm_mon + 1 << "/" << 1900 + thoigian->tm_year;
	gotoxy(wherex() - 11, wherey() + 2);
	cout << thoigian->tm_hour;
	if (thoigian->tm_sec % 2 == 0)
	{
		cout << " ";
	}
	else
	{
		cout << ":" ;
	}
	if (thoigian->tm_min < 10)
	{
		cout << "0" << thoigian->tm_min;
	}
	else
	{
		cout << thoigian->tm_min;
	}
}
int SoSanhChuoiSo(string &a, string &b)
{
	for (int i = 0; i < a.length(); i++)
	{
		if (a[i] > b[i])
		{
			return 1;
		}
		if (a[i] < b[i])
		{
			return -1;
		}
	}
	return 0;
}
bool KiemTraThoiGian(int hh, int min, int dd, int mm, int yy)
{
	time_t hientai = time(0);
	tm *thoigian = localtime(&hientai);
	if (yy > 1900 + thoigian->tm_year)
	{
		return 1;
	}
	if (yy < 1900 + thoigian->tm_year)
	{
		return 0;
	}
	if (mm > 1 + thoigian->tm_mon)
	{
		return 1;
	}
	if (mm < 1 + thoigian->tm_mon)
	{
		return 0;
	}
	if (dd > thoigian->tm_mday)
	{
		return 1;
	}
	if (dd < thoigian->tm_mday)
	{
		return 0;
	}
	if (hh * 60 + min >= (thoigian->tm_hour)*60 + thoigian->tm_min)
	{
		return 1;
	}
	return 0;
}
// ==================== KIEM TRA THOI GIAN GIUA 2 KHOANG THOI GIAN CACH NHAU 3H ==============================
bool KiemTraHaiKhoangThoiGian(int hh1, int min1, int dd1, int mm1, int yy1, int hh2, int min2, int dd2, int mm2, int yy2)
{
	if (yy1 > yy2)
	{
		return 1;
	}
	if (yy1 < yy2)
	{
		return 1;
	}
	if (mm1 > mm2)
	{
		return 1;
	}
	if (mm1 < mm2)
	{
		return 1;
	}
	if (dd1 > dd2)
	{
		return 1;
	}
	if (dd1 < dd2)
	{
		return 1;
	}
	if (hh1*60+min1 > hh2*60+min2 + 180)
	{
		return 1;
	}
	if (hh2*60+min2 > 180 + hh1*60+min1)
	{
		return 1;
	}
	return 0;
}
// ==================== XOA MAN HINH ========================
void XoaManHinh()
{
	system("cls");
	gotoxy(180,45);
	ChangeColor(11);
	ChangeColor(15);
	gotoxy(0,0);
}
#endif
