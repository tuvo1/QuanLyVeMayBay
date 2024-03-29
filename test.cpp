
#define _MYLIB_H



#include<iostream>
#include<conio.h>
#include<windows.h>
#include<ctime>
#define MAXLIST 300
using namespace std;
void fullscreen()
{
	keybd_event(VK_MENU,0x38,0,0);
	keybd_event(VK_RETURN,0x1c,0,0);
	keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0);
	keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);
}
int wherex()
{
HANDLE hConsoleOutput;
hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
return screen_buffer_info.dwCursorPosition.X;
}
//=========================TRA VE VI TRI Y CUA CON TRO============================
int wherey( void )
{
HANDLE hConsoleOutput;
hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
return screen_buffer_info.dwCursorPosition.Y;
}
//==============================AN CO TRO MAN HINH CONSOLE=======================
void AnConTro()
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = FALSE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}
//==============================HIEN CON TRO MAN HINH CONSOLE================
void HienConTro()
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = TRUE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}
void gotoxy(int x, int y) // Di chuyen toa do con tro trong he toa do De-cat
{
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}
void menu(){

	bool kt = true;
//	ListMayBay listmaybay;
	while(true)
	{
		
		system("cls");
		gotoxy(104,19);
		cout << "1. Them may bay" << endl;
	//	gotoxy(104,19);
		cout << "2. Xuat danh sach may bay" << endl;
		cout <<"0. Thoat" << endl;
		int luachon;
		cout << "Nhap lua chon: "; cin >> luachon; 
//		switch(luachon)
//		{
//			case 1:
//				{
//					ThemMayBay(listmaybay);
//					break;
//				}
//			case 0:
//				{
//					kt = false;
//					break;
//				}
//		}
	}





}
















void DangNhap ()
{
	//=======================FRONT END===============================
	gotoxy(104,19);
	cout << "DANG NHAP";
	char doc = 186;
	char ngang = 205;
	char traitren = 201;
	char traiduoi = 200;
	char phaitren = 187;
	char phaiduoi = 188;
	gotoxy(87,21);
	for (int i = 1; i <= 10; i++) // Ke khung ngoai
	{
		for (int j = 1; j <= 40; j++)
		{
			if (i == 1 || i == 10)
			{
				if (i == 1)
				{
					if (j == 1)
					{
						cout << traitren;
					}
					else
					{
						if (j == 40)
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
						if (j == 40)
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
				if (j == 1 || j == 40)
				{
					cout << doc;
				}
				else
				{
					cout << " ";
				}
			}
		}
		gotoxy(87,21+i);
	}
	traitren = 218;
	phaitren = 191;
	traiduoi = 192;
	phaiduoi = 217;
	ngang = 196;
	doc = 179;
	gotoxy(89,21+3);
	cout << "Ten dang nhap "; // 14 kytu
	gotoxy(89+14,2+21);
//	gotoxy(0,15);
	for (int i = 1; i <= 3; i++)
	{
		for (int j = 1; j <= 22; j++)
		{
			if (i == 1 || i == 3)
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
						if (j == 22)
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
				if (j == 1 || j == 22)
				{
					cout << doc;
				}
				else
				{
					cout << " ";
				}
			}
		}
	//	cout << endl;
		gotoxy(14+89,i+2+21);
	} 
	gotoxy(89,21+6);
	cout << "Mat khau "; // 9 kytu
	gotoxy(89+14,5+21);
	for (int i = 1; i <= 3; i++)
	{
		for (int j = 1; j <= 22; j++)
		{
			if (i == 1 || i == 3)
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
						if (j == 22)
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
				if (j == 1 || j == 22)
				{
					cout << doc;
				}
				else
				{
					cout << " ";
				}
			}
		}
	//	cout << endl;
		gotoxy(14+89,21+i+5);
	}
	//=======================BACK END=================================
	char a; // Bat phim
	bool kytu;
	int line = 0;
	string user = ""; // Luu ten nguoi dung
	string pass = ""; // Luu password
//	cout << "Ten dang nhap: " << endl;
//	cout << "Mat khau: ";
//	gotoxy(15,line);
	gotoxy(89+16,21+3);
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
	while (1)
	{
		while (a != 13)
		{
			if (((a == 72 || a == 80) && !kytu)||(a == 9 && kytu))
			{
				if (line) // line = 1
				{
					line--; 
					gotoxy(89+16+user.length(),21+3);
				}
				else // line = 0
				{
					line++;
					gotoxy(89+16 + pass.length(),21+6);
				}
			}
			if (line)
			{
				gotoxy(89+16 + pass.length(),21+6); //line = 1
			}
			else
			{
			 	gotoxy(89+16+user.length(),21+3);//line = 0
			}
			if (a == 8 && kytu) // Backspace
			{
				if (!line)
				{
					if (user.length() == 0)
					{
						int hoanhdo = wherex();
						int tungdo = wherey();
						cout << "Khong the xoa";
						AnConTro();
						Sleep(200);
						gotoxy(hoanhdo,tungdo);
						cout << "              ";
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
						//===Xu ly chuoi===========
						user.erase(user.end() - 1, user.end());
					}
				}
				else
				{
					if (pass.length() == 0)
					{
						int hoanhdo = wherex();
						int tungdo = wherey();
						cout << "Khong the xoa";
						AnConTro();
						Sleep(200);
						gotoxy(hoanhdo,tungdo);
						cout << "             ";
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
						//===Xu ly chuoi===========
						pass.erase(pass.end() - 1, pass.end());
					}
				}
			}
			if  (((a >= 48 && a <= 57)||(a >= 65 && a <= 90)||(a >= 97 && a <= 122)) && kytu) // kytu
			{
				if (!line)
				{
					if (user.length() <  15)
					{
						cout << a;
						user = user + a;
					}
					else
					{
						gotoxy(15+90,3+21);
						cout << "Khong qua 15 ky tu";
						AnConTro();
						Sleep(600);
						gotoxy(15+90,3+21);
						cout << "                  ";
						gotoxy(15+90,3+21);
						cout << user;
						HienConTro();
					}
				}
				else
				{
					if (pass.length() < 15 )
					{
						cout << "*";
						pass = pass + a;
					}
					else
					{
						gotoxy(15+90,6+21);
						cout << "Khong qua 15 ky tu";
						AnConTro();
						Sleep(600);
						gotoxy(15+90,6+21);
						cout << "                  ";
						gotoxy(15+90,6+21);
						for (int i = 1; i <= pass.length(); i++)
						{
							cout <<"*";
						}
						HienConTro();
					}
				}
			}
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
		if (user.length() == 0 || pass.length() == 0)
		{
			gotoxy(3+87,8+21);
			cout << "Dien ten dang nhap hoac mat khau";
			AnConTro();
			Sleep(500);
			gotoxy(3+87,8+21);
			cout << "                                 ";
			HienConTro();
			if (user.length() == 0)
			{
				gotoxy(89+16,21+3); //  Quay lai user
				line = 0;
			}
			else
			{
				gotoxy(89+16,21+6); // Quay lai pass
				line = 1;
			}
		}
		else // Co user va pass
		{
			if (user == "admin" && pass == "admin")
			{
				break;
			}
			else
			{
				gotoxy(3+87,8+21);
				cout << "Dang nhap that bai. Xin thu lai";
				AnConTro();
				Sleep(500);
				user = ""; // clear
				pass = ""; // clear
				gotoxy(3+87,8+21);
				cout << "                                ";
				gotoxy(89+16,21+3);
				cout << "                 "; // Clear user
				gotoxy(89+16,21+6);
				cout << "                 "; // Clear pass
				line = 0;
				gotoxy(89+16+user.length(),21+3);
				HienConTro();
			}
		}
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
	gotoxy(10+87,8+21);
	cout << "Dang nhap thanh cong";
	AnConTro();
	Sleep(500);
	HienConTro();
//	gotoxy(0,3);
//	cout << "Dang nhap thanh cong" << endl;
//	Sleep(500);
}

//void ThemMayBay(LisMayBay &listmaybay);

//struct KhachHang{
//	String ho "";
//	String ten = "";
//	String phai = "";
//	int cmnd;
//	int gioitinh;
//};
//struct nodekhachhang{
//	KhachHang kh;
//	nodekhachhang *pright;
//	nodekhachhang *pleft;
//};
//
//nodekhachhang *insert(nodekhachhang *t, int n)
//{
//	if(t == NULL)
//	{
//		nodekhachhang *temp = new nodekhachhang;
//		t->kh = n;
//		t -> pright = NULL;
//		t -> pleft = NULL;
//		return temp;	
//	}	
//	else{
//		if(n < t->kh)
//		{
//			t ->pleft = insert(t->left,x);
//		}
//		else{
//			t -> right = insert(t->right,x);
//		}
//	}
//}
//void menu(){
//	bool kt = true;
//	ListMayBay listmaybay;
//	while(true)
//	{
//		system("cls");
//		cout << "1. Them may bay" << endl;
//		cout << "2. Xuat danh sach may bay" << endl;
//		cout <<"0. Thoat" << endl;
//		int luachon;
//		cout << "Nhap lua chon: "; cin >> luachon; 
//		switch(luachon)
//		{
//			case 1:
//				{
//					ThemMayBay(listmaybay);
//					break;
//				}
//			case 0:
//				{
//					kt = false;
//					break;
//				}
//		}
//	}
//
//}
//
//
//
//
//struct MayBay{
//	string sohieu;
//	int socho;
//	string loai; 
//};
//
//struct ListMayBay{
//	int n;
//	MayBay *data[MAXLIST];
//};
//
//
//void ThemMayBay(ListMayBay &listmaybay)
//{
//	MayBay p = new MayBay;
//	
//	cout << "Nhap so hieu may bay";
//	getline(cin, p->sohieu);
//	cout << "Nhap loai may bay ";
//	getline(cin, p->loai);
//	cout << "Nhap so cho may bay";
//	getline(cin, p->socho);
//	listmaybay.data[listmaybay.n] = p;
//	listmaybay.n++;
//}
//
//




int main()
{
	fullscreen();
//	DangNhap(); 
	 menu();
	return 0;
}
