#ifndef _OBJECT_H
#define _OBJECT_H


#include<iostream>
#include<windows.h>
#include<string>
#include"object.h"
#include<iostream>
#include<string>
#include<stdlib.h>
#include"graph.h"
#include<string.h>
#include<fstream>
using namespace std;
#define MAXLIST  300
//================================== STRUCT KHACH HANG ================================
struct KhachHang
{
	string CMND = "";
	string Name = "";
	int GioiTinh; // 1 la nam, 0 la nu	
};
//=================================== NHAP THONG TIN KHACH HANG ==================================
void NhapThongTinKhachHang(KhachHang &HanhKhach)
{
	// Thieu Graphic
	cout << "Nhap CMND: ";
//	LaySoCMND(HanhKhach.CMND);
	cout << "Nhap Ho Ten: ";
//	NhapHoTen(HanhKhach.Name);
	cout << "Nhap gioi tinh: ";
	cin >> HanhKhach.GioiTinh;
	int hoanhdo = wherex();
	int tungdo = wherey();
	while (HanhKhach.GioiTinh != 1 && HanhKhach.GioiTinh != 0)
	{
		gotoxy(hoanhdo,tungdo);
		cout << "Thong tin khong hop le!";
		Sleep(300);
		gotoxy(hoanhdo,tungdo);
		cout << "                       ";
		gotoxy(hoanhdo,tungdo);
		cin >> HanhKhach.GioiTinh;
	}
}
//================================= STRUCT CAC PHAN TU TRONG CAY ==================================
struct NodeKhachHang
{
	KhachHang HanhKhach; // chua thong tin
	NodeKhachHang *left = NULL;
	NodeKhachHang *right = NULL;
};
//==================================== STRUCT CAY KHACH HANG =============================
struct CayKhachHang
{
	int SoLuong;
	NodeKhachHang *root = NULL;
};
// ================================ TAO NODE KHACH HANG ============================
NodeKhachHang *NewKhachHang()
{
	NodeKhachHang *p = new NodeKhachHang;
	return p;
}
// ==================================== SO SANH CMND ========================
int SoSanhCMND(string a, string b)
{
	for (int i = 0; i < 10; i++)
	{
		if(a[i] > b[i])
		{
			return 1; // a > b
		}
		if (a[i] < b[i])
		{
			return -1;
		}
	}
	return 0;
}
//=================================THEM VAO CAY KHACH HANG====================
int ThemVaoCayKhachHang(CayKhachHang &a, KhachHang HanhKhach)
{
	
	if (a.root == NULL) // Cay rong
	{
		a.root = new NodeKhachHang;
		a.root->HanhKhach.CMND = HanhKhach.CMND;
		string name = HanhKhach.Name;
		for (int i = 0; i < name.length(); i++)
		{
			if (name[i] == ' ')
			{
				name[i] = '0';
			}
		}
		a.root->HanhKhach.Name = name;
		a.root->HanhKhach.GioiTinh = HanhKhach.GioiTinh;
		a.root->left = NULL;
		a.root->right = NULL;
		return 1;
	}
	NodeKhachHang *p = a.root;
	while (1)
	{
		if (SoSanhCMND(p->HanhKhach.CMND, HanhKhach.CMND) == 1) 
		{
			if (p->left == NULL)
			{
				break;
			}
			else
			{
				p = p->left;
			}
		}
		else
		{
			if (SoSanhCMND(p->HanhKhach.CMND, HanhKhach.CMND) == -1)
			{
				if (p->right == NULL)
				{
					break;
				}
				else
				{
					p = p->right;
				}
			}
			else
			{
				break;
			}
		}
		
	}
	string name = HanhKhach.Name;
	for (int i = 0; i < name.length(); i++)
	{
		if (name[i] == ' ')
		{
			name[i] = '0';
		}
	}
	if (SoSanhCMND(p->HanhKhach.CMND, HanhKhach.CMND) == 1 && p->left == NULL)
	{
		a.SoLuong++;
		p->left = new NodeKhachHang;
		p = p->left;
		ofstream outfile;
		outfile.open("dskhachhang.txt",ios::app);
		outfile << endl << HanhKhach.CMND << endl << name << endl << HanhKhach.GioiTinh;
		outfile.close();
		p->HanhKhach.CMND = HanhKhach.CMND;
		p->HanhKhach.GioiTinh = HanhKhach.GioiTinh;
		p->HanhKhach.Name = name;
		p->left = NULL;
		p->right = NULL;
		return 1;
	}
	if (SoSanhCMND(p->HanhKhach.CMND, HanhKhach.CMND) == -1 && p->right == NULL)
	{
		a.SoLuong++;
		p->right = new NodeKhachHang;
		p = p->right;
		ofstream outfile;
		outfile.open("dskhachhang.txt",ios::app);
		outfile << endl << HanhKhach.CMND << endl << name << endl << HanhKhach.GioiTinh;
		outfile.close();
		p->HanhKhach.CMND = HanhKhach.CMND;
		p->HanhKhach.GioiTinh = HanhKhach.GioiTinh;
		p->HanhKhach.Name = name;
		p->left = NULL;
		p->right = NULL;
		return 1;
	}
	p->HanhKhach.CMND = HanhKhach.CMND;
	p->HanhKhach.GioiTinh = HanhKhach.GioiTinh;
	p->HanhKhach.Name = name;
	p->left = NULL;
	p->right = NULL;
	return 1;
}
// ================== TIM KIEM TRONG CAY KHACH HANG ===============
void TimKiemTrongCayKhachHang(CayKhachHang &Cay, string CMND, string &name, int &gioitinh) // tim kiem tra ve ten
{
	NodeKhachHang *p = Cay.root;
	while (p != NULL)
	{
		if (SoSanhCMND(CMND,p->HanhKhach.CMND) == 1)
		{
			p = p->right;
		//	cout << "wowr ";
		}
		else
		{
			if (SoSanhCMND(CMND,p->HanhKhach.CMND) == -1)
			{
				p = p->left;
			//	cout << "wowf ";
			}
			else
			{
				break;
			}
		}
		
	}
	if (p != NULL)
	{
		name = p->HanhKhach.Name;
		gioitinh = p->HanhKhach.GioiTinh;
	}
}
//==================================STRUCT NGAY===========================
struct Day
{
	int dd,mm,yy;	
};
//==================================STRUCT GIO=============================
struct Time
{
	int hour,min;
};
// ===================== DO DAI KY TU CUA NGAY ============================
int DoDaiNgay (Day a)
{
	int dodai = 0;
	dodai = DoDaiSoDuong(a.dd) + DoDaiSoDuong(a.mm) + DoDaiSoDuong(a.yy) + 2; // 2 dau '/'
	return dodai;
}
// ===================== DO DAI KY TU CUA GIO =======================
int DoDaiGio(Time a)
{
	int dodai = 0;
	if (a.min < 10)
	{
		dodai = DoDaiSoDuong(a.hour) + DoDaiSoDuong(a.min) + 2; // Them so '0' voi ':'
	}
	else
	{
		dodai = DoDaiSoDuong(a.hour) + DoDaiSoDuong(a.min) + 1;
	}
	return dodai;
}
// ============================= IN NGAY ============================
void InNgay(Day a)
{
	cout << a.dd << "/" << a.mm << "/" << a.yy;
}
// =================================== IN GIO ====================
void InGio(Time a)
{
	cout << a.hour << ":";
	if (a.min < 10)
	{
		cout << "0" << a.min;
	}
	else
	{
		cout << a.min;
	}
}
//======================================STRUCT VE==================================================
struct Ticket
{
	NodeKhachHang *HanhKhach = NULL;
};
//============================CLASS MAY BAY=================================
class MayBay
{
	public:
		void DatSoHieu(string a); // Chinh sua so hieu
		string LaySoHieu(); // Lay so hieu
		void DatLoai(string a); // Chinh sua loai may bay
		string LayLoai(); // Lay loai may bay
		void DatSoCho(int a); // Chinh sua so cho may bay
		int LaySoCho(); // Lay so cho ngoi may bay, toi da 624 cho ngoi
	//	void DatTrangThai(int a); // Chinh sua trang thai
	//	int LayTrangThai(); // lay trang thai
		
	protected:
		string SoHieu; // So hieu may bay
		string Loai; // Loai may bay
		int SoCho; // So cho ngoi
	//	int TrangThai; // Trang thai may bay; 0 la huy chuyen, 1 la con ve, 2 la het ve, 3 la hoan tat
};

//==========================FUNCTION MAY BAY==================================

void MayBay :: DatSoHieu(string a)
{
	SoHieu = a;
}
string MayBay::LaySoHieu()
{
	return SoHieu;
}
void MayBay::DatLoai(string a)
{
	Loai = a;
}
string MayBay::LayLoai()
{
	return Loai;
}
void MayBay::DatSoCho(int a)
{
	SoCho = a;
}
int MayBay::LaySoCho()
{
	return SoCho;
}


//=====================================DANH SACH MAY BAY===========================================
struct ListMayBay
{
	int n;
	MayBay *data[MAXLIST];
};
//=====================================TAO MOT MAY BAY MOI========================================
MayBay *CreateData()
{
	MayBay *a = new MayBay;
	return a;	
}

//====================================TAO DU VE MOI==========================================
Ticket *NewTicket()
{
	Ticket *p = new Ticket;
	p = NULL;
	return p;	
};
//=============================KIEM TRA DANH SACH MAY BAY RONG================================
bool DanhSachRong(ListMayBay &a)
{
	if (a.n == 0) 
	return 1;
	return 0;
}
//=============================KIEM TRA DANH SACH MAY BAY DAY=================================
bool DanhSachDay(ListMayBay &a)
{
	if (a.n == MAXLIST)
	return 1;
	return 0;
}
// ============================ KIEM TRA TRUNG SO HIEU KHI NHAP ===============================
bool KiemTraSoHieu(ListMayBay a, string SoHieu)
{
	for (int i = 0; i < a.n; i++)
	{
		if (a.data[i]->LaySoHieu() == SoHieu)
		{
			return 1;
		}
	}
	return 0;
}
//============================= KIEM TRA TRUNG SO HIEU MAY BAY KHI SUA ==============================
bool KiemTraSoHieuKhiSua(MayBay Mang[], string SoHieu, int soluong, int vitri)
{
	for (int i = 0; i < soluong; i++)
	{
		if (Mang[i].LaySoHieu() == SoHieu && i != vitri)
		{
			return 1;
		}
	}
	return 0;
}
//================================NHAP DU LIEU MAY BAY=======================================
int NhapDuLieuMayBay(MayBay *a,ListMayBay list)
{
//	InDanhSachMayBay(a,list.n/30+1);
	HienConTro();
	char x; // De chay ham lay so
	bool kytu;
	string SoHieu = "";
	string Loai = "";
	int SoCho = 0;
	//==========================SO HIEU=======================================//
	int dodai = SoHieu.length();
	gotoxy(10,wherey());
	bool kt = 0;
	while (1)
	{
		kt = 0;
		dodai = SoHieu.length();
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
			while (x != 13 && x != 27) // Chua nhan Enter
			{
				if (x == 8) // Backspace
				{
					if (dodai != 0)
					{
						SoHieu.erase(SoHieu.end() - 1, SoHieu.end());
						dodai--;
						//==========================//
					//	int hoanhdo = wherex();
					//	int tungdo = wherey();
						AnConTro();
						gotoxy(8, wherey());
						cout << "     ";
						CanhGiua(10,dodai);
						cout << SoHieu;
						HienConTro();
					}
					else
					{
						int hoanhdo = wherex();
						int tungdo = wherey();
						gotoxy(3,tungdo);
						cout << "Khong the xoa";
						Sleep(300);
						gotoxy(3,tungdo);
						cout << "             ";
						gotoxy(10,tungdo);
					}
				}
				if ((x >= 97 && x <= 122) && kytu) // In hoa chu thuong len em ei =))
				{
					x = InHoa(x);
				}
				if (((x >= 65 && x <= 90) || (x >= 48 && x <= 57)) && kytu) // 0 den 9, A den Z
				{
					if (dodai < 5)
					{
						dodai++;
						SoHieu = SoHieu + x;
						CanhGiua(10,SoHieu.length());
						for (int i = 0; i < SoHieu.length();i++)
						cout << SoHieu[i];
					}
					else
					{
					//	int hoanhdo = wherex();
					//	int tungdo = wherey();
						gotoxy(2,wherey());
						cout << "Khong qua 5 ky tu";
						Sleep(300);
						gotoxy(2,wherey());
						cout << "                 ";
					//	gotoxy(hoanhdo - 5, tungdo);
					//	cout << SoHieu;
						CanhGiua(10,SoHieu.length());
						for (int i = 0; i < SoHieu.length();i++)
						cout << SoHieu[i];
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
			if (x == 27) // Esc
			{
				int hoanhdo = wherex();
				int tungdo = wherey();
				gotoxy(0,30);
				AnConTro();
				cout << "Ban co muon THOAT?";
				cout  << endl << "Nhan Y de ";
				ChangeColor(12);
				cout << "THOAT";
				ChangeColor(15);
				cout << ", hoac nhan BAT KY phim nao de ";
				ChangeColor(12);
				cout << "HUY";
				ChangeColor(15);
				char s = getch();
				bool kytu1;
				if (s == -32 || s == 0)
				{
					kytu1 = 0;
					s = getch();
 				}
 				else
 				{
 					kytu1 = 1;
				}
				if (InHoa(s) == 89)
				{
					return -1;
				}
				else
				{
					AnConTro();
					gotoxy(0,30);
					cout << "                                        " << endl << "                                                                ";
					kt = 1;
					gotoxy(hoanhdo,tungdo);
					HienConTro();
				}
			}
			if (!kt)
			{
				if (SoHieu.length() != 0)
				{
					if (KiemTraSoHieu(list,SoHieu))
					{
						gotoxy(3,wherey());
						cout << "So hieu bi trung";
						Sleep(500);
						gotoxy(2,wherey());
						cout << "Vui long nhap lai";
						Sleep(500);
						gotoxy(2,wherey());
						cout << "                 ";
						SoHieu = "";
					//	cout << SoHieu;
						gotoxy(10,wherey());
					}
					else
					{
						break;
					}
				}
				else
				{
					gotoxy(1,wherey());
					cout << "Khong the de trong";
					Sleep(300);
					gotoxy(1,wherey());
					cout << "                  ";
					CanhGiua(10,SoHieu.length());
				}
			}
	}
	//=====================LOAI============================
//	cout << endl;
//	cout << "Nhap Loai: ";
	dodai = Loai.length();
	gotoxy(30,wherey());
	while (1)
	{
		kt = 0;
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
		while (x != 13 && x != 27) // Chua nhan Enter
		{
			if (x == 8) // Backspace
			{
				if (dodai != 0)
				{
					Loai.erase(Loai.end() - 1, Loai.end());
					dodai--;
			
					AnConTro();
					gotoxy(25, wherey());
					cout << "          ";
					CanhGiua(30,dodai);
					cout << Loai;
					HienConTro();
				}
				else
				{
					int hoanhdo = wherex();
					int tungdo = wherey();
					cout << "Khong the xoa";
					Sleep(300);
					gotoxy(hoanhdo,tungdo);
					cout << "             ";
					gotoxy(30,tungdo);
				}
			}
			if ((x >= 97 && x <= 122) && kytu) // In hoa chu thuo
			{
				x = InHoa(x);
			}
			if (((x >= 65 && x <= 90) || (x >= 48 && x <= 57)) && kytu) // 0 den 9, A den Z
			{
				if (dodai < 10)
				{
					dodai++;
					Loai = Loai + x;
					AnConTro();
					CanhGiua(30,dodai);
					for (int i = 0; i < dodai; i++)
					cout << Loai[i];
					HienConTro();
				}
				else
				{
					AnConTro();
					int hoanhdo = wherex();
					int tungdo = wherey();
					gotoxy(21,tungdo);
					cout << "Khong qua 10 ky tu";
					Sleep(300);
					gotoxy(21,tungdo);
					cout << "                  ";
					CanhGiua(30,dodai);
					cout << Loai;
					HienConTro();
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
			if (x == 27) // Esc
			{
				int hoanhdo = wherex();
				int tungdo = wherey();
				gotoxy(0,30);
				AnConTro();
				cout << "Ban co muon THOAT?";
				cout  << endl << "Nhan Y de ";
				ChangeColor(12);
				cout << "THOAT";
				ChangeColor(15);
				cout << ", hoac nhan BAT KY phim nao de ";
				ChangeColor(12);
				cout << "HUY";
				ChangeColor(15);
				char s = getch();
				bool kytu1;
				if (s == -32 || s == 0)
				{
					kytu1 = 0;
					s = getch();
 				}
 				else
 				{
 					kytu1 = 1;
				}
				if (InHoa(s) == 89)
				{
					return -1;
				}
				else
				{
					AnConTro();
					gotoxy(0,30);
					cout << "                                        " << endl << "                                                                ";
					kt = 1;
					gotoxy(hoanhdo,tungdo);
					HienConTro();
				}
			}
		if (!kt)
		{
			if (Loai.length() != 0)
			{
				break;
			}
			else
			{
				gotoxy(21,wherey());
				cout << "Khong the de trong";
				Sleep(300);
				gotoxy(21,wherey());
				cout << "                  ";
				gotoxy(30,wherey());
			}
		}
	}
	//==================================SO CHO============================== 
//	cout << "Nhap So cho: ";
	gotoxy(50,wherey());
	int hoanhdo = wherex();
	int tungdo = wherey();
	SoCho = LaySo(0,0,x);
	kt = 0;
	if (x == 27) // Esc
			{
				gotoxy(0,30);
				AnConTro();
				cout << "Ban co muon THOAT?";
				cout  << endl << "Nhan Y de ";
				ChangeColor(12);
				cout << "THOAT";
				ChangeColor(15);
				cout << ", hoac nhan BAT KY phim nao de ";
				ChangeColor(12);
				cout << "HUY";
				ChangeColor(15);
				char s = getch();
				bool kytu1;
				if (s == -32 || s == 0)
				{
					kytu1 = 0;
					s = getch();
 				}
 				else
 				{
 					kytu1 = 1;
				}
				if (InHoa(s) == 89)
				{
					return -1;
				}
				else
				{
					AnConTro();
					gotoxy(0,30);
					cout << "                                        " << endl << "                                                                ";
					gotoxy(hoanhdo,tungdo);
					cout << "       ";
					gotoxy(hoanhdo,tungdo);
					HienConTro();
					kt = 1;
				}
			}
	while((SoCho < 20 || SoCho > 100) || kt )
	{
		if(kt)
		{
			SoCho = LaySo(0,0,x);
		}
		kt = 0;
		if (!kt && (SoCho < 20 || SoCho > 100))
		{
			char doc = 179;
			AnConTro();
			gotoxy(39,wherey());
			cout << "So cho > 20 va < 100";
			Sleep(500);
			gotoxy(39,wherey());
			cout << doc << "                   ";
			gotoxy(50,wherey());
			cout << "  ";
			gotoxy(50,wherey());
			SoCho = 0;
			SoCho = LaySo(0,0,x);
		}
		if (x == 27) // Esc
			{
				gotoxy(0,30);
				AnConTro();
				cout << "Ban co muon THOAT?";
				cout  << endl << "Nhan Y de ";
				ChangeColor(12);
				cout << "THOAT";
				ChangeColor(15);
				cout << ", hoac nhan BAT KY phim nao de ";
				ChangeColor(12);
				cout << "HUY";
				ChangeColor(15);
				char s = getch();
				bool kytu1;
				if (s == -32 || s == 0)
				{
					kytu1 = 0;
					s = getch();
 				}
 				else
 				{
 					kytu1 = 1;
				}
				if (InHoa(s) == 89)
				{
					return -1;
				}
				else
				{
					AnConTro();
					gotoxy(0,30);
					cout << "                                        " << endl << "                                                                ";
					gotoxy(hoanhdo,tungdo);
					cout << "         ";
					gotoxy(hoanhdo,tungdo);
					HienConTro();
					kt = 1;
				}
			}
	}
	{
		AnConTro();
		gotoxy(45,wherey());
		cout << "          ";
		CanhGiua(50,DoDaiSoDuong(SoCho));
		cout << SoCho;
	}
	a->DatSoHieu(SoHieu);
	a->DatLoai(Loai);
	a->DatSoCho(SoCho);
}
//====================================IN DANH SACH MAY BAY===================================
void InDanhSachMayBay(ListMayBay a, int trang)
{
	KhungMayBay();
//	ChangeColor(8);
	gotoxy(0,0);
	int maxtrang;
	if (a.n%30 != 0)
	{
		maxtrang = a.n/30 + 1;
	}
	else
	{
		maxtrang = a.n/30;
	}
	if (trang < maxtrang)
	{
		for (int i = (trang - 1)*10; i < trang*10 - 1; i++)
		{
			gotoxy(8,2*((i+1)%10)+1);
			CanhGiua(10,a.data[i]->LaySoHieu().length());
			cout << a.data[i]->LaySoHieu();
			gotoxy(26,2*((i+1)%10)+1);
			CanhGiua(30,a.data[i]->LayLoai().length());
			cout << a.data[i]->LayLoai();
			gotoxy(48,2*((i+1)%10)+1);
			CanhGiua(50,DoDaiSoDuong(a.data[i]->LaySoCho()));
			cout << a.data[i]->LaySoCho();
		}
	}
	else
	{
		for (int i = (trang - 1)*10; i < a.n; i++)
		{
			gotoxy(8,2*((i+1)%10)+1);
			CanhGiua(10,a.data[i]->LaySoHieu().length());
			cout << a.data[i]->LaySoHieu();
			gotoxy(26,2*((i+1)%10)+1);
			CanhGiua(30,a.data[i]->LayLoai().length());
			cout << a.data[i]->LayLoai();
			gotoxy(48,2*((i+1)%10)+1);
			CanhGiua(50,DoDaiSoDuong(a.data[i]->LaySoCho()));
			cout << a.data[i]->LaySoCho();
		}
	}
	gotoxy(25,24);
	cout << "---" << trang << "/";
	if (a.n%10 > 0)
	{
		cout << a.n/10 + 1;
	}
	else
	{
		cout << a.n/10;
	}
	cout << "---" << endl;
}
//====================================THEM MAY BAY=======================================
int ThemMayBay(ListMayBay &a)
{

	char kytu; 
	if (DanhSachDay(a)) return 0; // Tra ve 0 neu khong the them

	{
		gotoxy(0,0);
		if ((a.n) % 10 == 0)
		{
			KhungMayBay();
		}
		else
		{
			InDanhSachMayBay(a,(a.n)/10+1);
		}
		a.n++;
		a.data[a.n - 1] = CreateData();
	//	KhungMayBay();
		int x;
		if (a.n%10 == 0)
		{
			x = 10;
		}
		else
		{
			x = a.n%10;
		}
	
		gotoxy(0,2*x + 1);
		if (NhapDuLieuMayBay(a.data[a.n-1],a) == -1)
		{
			delete a.data[a.n-1];
			a.n--;
			return -1;
		}
		return 1;

	}

}
// ========================= TIM MAY BAY MAY BAY BANG SOHIEU============================
int TimKiemMayBay(ListMayBay a) 
{

	char x;
	string SoHieu = "";
	bool kytu;
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
	while (x != 13 && x != 27) 
	{
		if (((x >= 97 && x <= 122) || (x >= 65 && x <= 90)) && kytu ) // a->z, A->Z
		{
			// front_end cho nay ne
			SoHieu = SoHieu + InHoa(x);
			// Thieu front _ end
			cout << SoHieu;
			for (int i = 0; i < a.n; i++)
			{
				int j = 0;
				for ( j = 0; j < SoHieu.length(); j++)
				{
					if (SoHieu[j] != a.data[i]->LaySoHieu()[j])
					{
						break;
					}
				}
				if (j == SoHieu.length()) // So sanh dung den phan tu cuoi cung
				{
					
					cout << a.data[i]->LaySoHieu();
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
}
//====================================== CLASS CHUYEN BAY ============================================
class ChuyenBay : public MayBay
{
	protected:
		string DiemDen;
		string MaChuyen; // Ma chuyen bay
		Ticket *Ve;
		Day Ngay; // Ngay thang nam
		Time Gio; // Gio phut
		int TrangThai; // 0: Huy chuyen, 1: Con ve, 2: Het ve, 3: Hoan tat
	public:
		void DatDiemDen(string a);
		void DatMaChuyen(string a);
		void DatNgay(Day a);
		void DatGio(Time a);
		void DatTrangThai(int a);
		void TaoDanhSachVe();
		string LayDiemDen();
		string LayMaChuyen();
		Day LayNgay();
		Time LayGio();
		int LayTrangThai();
		Ticket *LayDanhSachVe();
};
//===============================FUNCTION CHUYEN BAY=====================================
void ChuyenBay::DatDiemDen(string a)
{
	DiemDen = a;
}
void ChuyenBay::DatMaChuyen(string a)
{
	MaChuyen = a;
}
void ChuyenBay::TaoDanhSachVe()
{
	Ve = new Ticket [SoCho]; 
	for (int i = 0; i < SoCho; i++)
	{
		Ve[i].HanhKhach = NULL; 
	}
}
void ChuyenBay::DatNgay(Day a)
{
	Ngay.dd = a.dd;
	Ngay.mm = a.mm;
	Ngay.yy = a.yy;
}
void ChuyenBay::DatGio(Time a)
{
	Gio.hour = a.hour;
	Gio.min = a.min;
}
void ChuyenBay::DatTrangThai(int a)
{
	TrangThai = a;
}
string ChuyenBay::LayDiemDen()
{
	return DiemDen;
}
string ChuyenBay::LayMaChuyen()
{
	return MaChuyen;
}
Day ChuyenBay::LayNgay()
{
	return Ngay;
}
Time ChuyenBay::LayGio()
{
	return Gio;
}
int ChuyenBay::LayTrangThai()
{
	return TrangThai;
}
Ticket *ChuyenBay::LayDanhSachVe()
{
	return Ve;
}
// =============================== DANH SACH LIEN KET CHUYEN BAY ====================
struct CacChuyenBay
{
	ChuyenBay chuyenbay;
	CacChuyenBay *next = NULL;
};
// ========================= LIST CHUYEN BAY ========================================
struct ListChuyenBay
{
	int SoLuong;
	CacChuyenBay *Head = NULL;
	CacChuyenBay *Tail = NULL;
};
// ========================== TAO CHUYEN BAY ==========================================
CacChuyenBay *NewChuyenBay()
{
	CacChuyenBay *p = new CacChuyenBay;
	return p;
}
// ================================== KIEM TRA TRUNG MA CHUYEN BAY =====================================
bool KiemTraTrungMaChuyenBay(ListChuyenBay a, string MaChuyenBay)
{
	CacChuyenBay *p = a.Head;
	while (p != NULL)
	{
		if (p->chuyenbay.LayMaChuyen() == MaChuyenBay)
		{
			return 1;
		}
		p = p->next;
	}
	return 0;
}
//====================================XOA MAY BAY KHOI DANH SACH============================
int XoaMayBay(ListMayBay &a, ListChuyenBay &b)
{
	ChangeColor(15);
	char docngoai = 186;
	char doctrong = 179;
	char kytu; 
	if (DanhSachRong(a)) return 0;
	InDanhSachMayBay(a,1);
	int line = 1;
	int trang;
	if (line%10 == 0)
	{
		trang = line/10;
	}  
	else
	{
		trang = line/10 + 1;
	}
	//================ HIGHLIGHT DONG XOA ================
	ChangeColor(240);
	gotoxy(0,2*(line%10) + 1);
	for (int i = 1; i <= 60; i++)
	{
		if (i == 1 || i == 60)
		{
			cout << docngoai;
		}
		else
		{
			if (i%20 == 0)
			{
				cout << doctrong;
			}
			else
			{
				cout << " ";
			}
		}
	}
	CanhGiua(10,a.data[0]->LaySoHieu().length());
	cout << a.data[0]->LaySoHieu();
	CanhGiua(30,a.data[0]->LayLoai().length());
	cout << a.data[0]->LayLoai();
	CanhGiua(50,DoDaiSoDuong(a.data[0]->LaySoCho()));
	cout << a.data[0]->LaySoCho();
	char x = getch();
	bool kytu1;
	if (x == -32 || x == 0)
	{
		kytu1 = 0;
		x = getch();
	}
	else
	{
		kytu1 = 1;
	}
	while (1)
	{
		while (x != 27 && x != 13)
		{
			if (x == 72 && !kytu1) // Up
			{
				if (line != 1)
				{
					ChangeColor(15);
					gotoxy(0,2*(line%10) + 1);
					for (int i = 1; i <= 60; i++)
					{
						if (i == 1 || i == 60)
						{
							cout << docngoai;
						}
						else
						{
							if (i%20 == 0)
							{
								cout << doctrong;
							}
							else
							{
								cout << " ";
							}
						}
					}
					CanhGiua(10,a.data[line-1]->LaySoHieu().length());
					cout << a.data[line-1]->LaySoHieu();
					CanhGiua(30,a.data[line-1]->LayLoai().length());
					cout << a.data[line-1]->LayLoai();
					CanhGiua(50,DoDaiSoDuong(a.data[line-1]->LaySoCho()));
					cout << a.data[line-1]->LaySoCho();
					line--;
					if (line%10 == 0)
					{
						trang = line/10;
					}
					else
					{
						trang = line/10 + 1;
					}
					// ================= HIGH LIGHT ==========================
						ChangeColor(240);
						gotoxy(0,2*(line%10) + 1);
						for (int i = 1; i <= 60; i++)
						{
							if (i == 1 || i == 60)
							{
								cout << docngoai;
							}
							else
							{
								if (i%20 == 0)
								{
									cout << doctrong;
								}
								else
								{
									cout << " ";
								}
							}
						}
						CanhGiua(10,a.data[line-1]->LaySoHieu().length());
						cout << a.data[line-1]->LaySoHieu();
						CanhGiua(30,a.data[line-1]->LayLoai().length());
						cout << a.data[line-1]->LayLoai();
						CanhGiua(50,DoDaiSoDuong(a.data[line-1]->LaySoCho()));
						cout << a.data[line-1]->LaySoCho();
				}
			}
			if (x == 80 && !kytu1) // Down
			{
				if (line != a.n)
				{
					ChangeColor(15);
					gotoxy(0,2*(line%10) + 1);
					for (int i = 1; i <= 60; i++)
					{
						if (i == 1 || i == 60)
						{
							cout << docngoai;
						}
						else
						{
							if (i%20 == 0)
							{
								cout << doctrong;
							}
							else
							{
								cout << " ";
							}
						}
					}
					CanhGiua(10,a.data[line-1]->LaySoHieu().length());
					cout << a.data[line-1]->LaySoHieu();
					CanhGiua(30,a.data[line-1]->LayLoai().length());
					cout << a.data[line-1]->LayLoai();
					CanhGiua(50,DoDaiSoDuong(a.data[line-1]->LaySoCho()));
					cout << a.data[line-1]->LaySoCho();
					line++;
					//======================== CAP NHAT TRANG ===================
					if (line%10 == 0)
					{
						trang = line/10;
					}
					else
					{
						trang = line/10 + 1;
					}
					// ================= HIGH LIGHT ==========================
						ChangeColor(240);
						gotoxy(0,2*(line%10) + 1);
						for (int i = 1; i <= 60; i++)
						{
							if (i == 1 || i == 60)
							{
								cout << docngoai;
							}
							else
							{
								if (i%20 == 0)
								{
									cout << doctrong;
								}
								else
								{
									cout << " ";
								}
							}
						}
						CanhGiua(10,a.data[line-1]->LaySoHieu().length());
						cout << a.data[line-1]->LaySoHieu();
						CanhGiua(30,a.data[line-1]->LayLoai().length());
						cout << a.data[line-1]->LayLoai();
						CanhGiua(50,DoDaiSoDuong(a.data[line-1]->LaySoCho()));
						cout << a.data[line-1]->LaySoCho();
				}
			}
			x = getch();
			if (x == -32 || x == 0)
			{
				kytu1 = 0;
				x = getch();
			}
			else
			{
				kytu1 = 1;
			}
		}
		if (x == 27) // Esc
		{
			return -1;
		}
		if (x == 13) // Enter
		{
			AnConTro();
			gotoxy(0,25);
			ChangeColor(15);
			cout << "Ban co muon XOA?";
			cout  << endl << "Nhan Y de ";
			ChangeColor(12);
			cout << "XOA";
			ChangeColor(15);
			cout << ", hoac nhan BAT KY phim nao de ";
			ChangeColor(12);
			cout << "HUY";
			ChangeColor(15);
			x = getch();
			if (x == -32 || x == 0)
			{
				kytu1 = 0;
				x = getch();
			}
			else
			{
				kytu1 = 1;
			}
			if (kytu1 && InHoa(x) == 89)
			{
				CacChuyenBay *p;
				for (p = b.Head; p != NULL; p = p->next)
				{
					if (p->chuyenbay.LaySoHieu() == a.data[line-1]->LaySoHieu())
					{
						break;
					}
				}
				if (p != NULL)
				{
					gotoxy(0,30);
					cout << "Khong the xoa";
					Sleep(500);
					gotoxy(0,30);
					cout << "             ";
					gotoxy(0,25);
					cout << "                                                                                         ";
					gotoxy(0,26);
					cout << "                                                           ";
				}
				else
				{
					delete a.data[line-1]; // Thu hoi vung nho
					for (int i = line - 1; i < a.n - 1; i++)
					{
						a.data[i] = a.data[i+1];
					}
					a.n--;
					return 1;
				}
			}
			else
			{
				gotoxy(0,25);
				cout << "                                                                                         ";
				gotoxy(0,26);
				cout << "                                                ";
			}
		}
	}
//	return 1;
}
//=================================== CHINH SUA MAY BAY =======================================
int ChinhSuaMayBay(ListMayBay &a, ListChuyenBay b)
{

	int currentpage;
	if (a.n == 0) return 0;
	XoaManHinh();
	gotoxy(0,0);
	InDanhSachMayBay(a,1);
	HienConTro();
	MayBay MangPhu[a.n]; // Chua data	
    //====================== SAO CHEP DU LIEU ====================
	for (int i = 0; i < a.n; i++) // Sao chep du lieu vao mang phu
	{
		MangPhu[i].DatSoHieu(a.data[i]->LaySoHieu());
		MangPhu[i].DatLoai(a.data[i]->LayLoai());
		MangPhu[i].DatSoCho(a.data[i]->LaySoCho());
	}

	int line = 0;
	currentpage = line/30;	
	AnConTro();
	gotoxy(0,2*(line/3 + 1) + 1); 
	CanhGiua(10,a.data[line/3]->LaySoHieu().length());
	gotoxy(wherex() + a.data[line/3]->LaySoHieu().length(),wherey()); // Di chuyen den dung vi tri
	HienConTro();
	bool kytu;
	char x = getch();
	if (x != -32 && x != 8) // Khong phai chuc nang hoac Backspace
	{
		kytu = 1;
	}
	if (x == -32 || x == 0) // Phim chuc nang
	{
		kytu = 0;
		x = getch();
	} 
	while (x != 19 && x != 27)
	{
		currentpage = line/30;
		if (x == 72 && !kytu ) // Up
		{
			if (line > 2)
			{
				line = line - 3;
			}
		}
		if (x == 80 && !kytu) // Down
		{
			if (line <= (a.n - 1)*3 - 1)
			{
				line = line + 3;
			}
			
		}
		if (x == 75 && !kytu) // Left
		{
			if (line > 0)
			{
				line--;
			}
		}
		if (x == 77 && !kytu) // Right
		{
			if (line != a.n*3 - 1)
			{
				line++;
			}
		}
		AnConTro();
		if (line/30 != currentpage)
		{
			gotoxy(0,0);
			InDanhSachMayBay(a,line/30);
		}
	
		if (line%3 == 0) // So Hieu
		{
		//	while (1)
		//	{
				AnConTro();
				gotoxy(0,2*((line%30)/3 + 1) + 1);
				CanhGiua(10,MangPhu[line/3].LaySoHieu().length());
				gotoxy(wherex() + MangPhu[line/3].LaySoHieu().length(),wherey());
				HienConTro();
				int dodaichuoi = MangPhu[line/3].LaySoHieu().length();
			//================NHAN BACKSPACE TU NGOAI VONG==============
				if (x == 8 && line == 0) // Backspace
				{
					if (dodaichuoi > 0) // Duoc quyen xoa
					{
						//=============XU LY CHUOI===========
						dodaichuoi--;
						string SoHieu = MangPhu[line/4].LaySoHieu();
						SoHieu.erase(SoHieu.end()-1,SoHieu.end());
						MangPhu[line/4].DatSoHieu(SoHieu);
						
					//=============XU LY HINH ANH=========
						AnConTro();
						gotoxy(8,wherey());
						cout << "     ";
						CanhGiua(10,MangPhu[line/3].LaySoHieu().length());
						cout << MangPhu[line/3].LaySoHieu();
						HienConTro();
					}
					else
					{
						AnConTro();
						gotoxy(4,wherey());
						cout << "Khong the xoa";
						Sleep(500);
						gotoxy(4,wherey());
						cout << "              ";
						gotoxy(10,wherey());
						HienConTro();
					} 
				}
			//===============NHAN KY TU VONG NGOAI=====================
				if (((x >= 94 && x <= 122) || (x >= 65 && x <= 90) || (x >= 48 && x <=57)) && kytu && line == 0) // a toi z, A toi Z, 0 toi 9
				{
					dodaichuoi++;
					InHoa(x);
					MangPhu[line/4].DatSoHieu(MangPhu[line/4].LaySoHieu() + InHoa(x));
					AnConTro();
					CanhGiua(10,MangPhu[line/3].LaySoHieu().length());
					cout << MangPhu[line/3].LaySoHieu();
					HienConTro();
				} 
				x = getch(); // Ban muon thao tac gi voi line nay?
				while (1)
				{
				//============XU LY NHAN PHIM=================
					if (x != -32 && x != 0)
					{
						kytu = 1;
					}
					else
					{
						kytu = 0;
						x = getch();
					}
				//================NHAN BACKSPACE==============
					if (x == 8 && kytu) // Backspace
					{
						if (dodaichuoi > 0) // Duoc quyen xoa
						{
							//=============XU LY CHUOI===========
								dodaichuoi--;
								string SoHieu = MangPhu[line/3].LaySoHieu();
								SoHieu.erase(SoHieu.end()-1,SoHieu.end());
								MangPhu[line/3].DatSoHieu(SoHieu);
							//=============XU LY HINH ANH=========
								AnConTro();
								gotoxy(8,wherey());
								cout << "     ";
								CanhGiua(10,dodaichuoi);
								cout << MangPhu[line/3].LaySoHieu();
								HienConTro();
						}
						else
						{
							AnConTro();
							gotoxy(4,wherey());
							cout << "Khong the xoa";
							Sleep(300);
							gotoxy(4,wherey());
							cout << "             ";
							gotoxy(10,wherey());
							HienConTro();
						} 
					}
				//===============NHAN PHIM CHUC NANG==============
					if (((x == 72 || x == 80 || x == 77 || x == 75) && !kytu) || x == 27 || x == 19) // 19 la Ctrl + S
					{
						if (MangPhu[line/3].LaySoHieu() != "")
						{
							if (KiemTraSoHieuKhiSua(MangPhu,MangPhu[line/3].LaySoHieu(),a.n,line/3)) // Trung So Hieu
							{
								AnConTro();
								gotoxy(4,wherey());
								cout << "Trung So Hieu";
								Sleep(500);
								gotoxy(4,wherey());
								cout << "             ";
								gotoxy(7,wherey());
								cout << "Thu lai";
								Sleep(500);
								gotoxy(7,wherey());
								cout << "       ";
								gotoxy(10,wherey());
								CanhGiua(10,MangPhu[line/3].LaySoHieu().length());
								cout << MangPhu[line/3].LaySoHieu();
							//	dodaichuoi = 0;
							//	MangPhu[line/3].DatSoHieu("");
								HienConTro();
							}
							else
							{
								break; // Khong con thao tac tren dong nay nua
							}
						}
						else
						{
							AnConTro();
							gotoxy(1,wherey());
							cout << "Khong the bo trong";
							Sleep(300);
							gotoxy(1,wherey());
							cout << "                  ";
							gotoxy(10,wherey());
							HienConTro();
						}
					}
				//===============NHAN KY TU=====================
					if (((x >= 94 && x <= 122) || (x >= 65 && x <= 90) || (x >= 48 && x <=57)) && kytu) // a toi z, A toi Z, 0 toi 9
					{
						if (dodaichuoi == 5)
						{
							AnConTro();
							gotoxy(2,wherey());
							cout << "Khong qua 5 ky tu";
							Sleep(300);
							gotoxy(2,wherey());
							cout << "                 ";
							CanhGiua(10,5);
							cout << MangPhu[line/3].LaySoHieu();
							HienConTro();
							
						}
						else
						{
							dodaichuoi++;
							InHoa(x);
							MangPhu[line/3].DatSoHieu(MangPhu[line/3].LaySoHieu() + InHoa(x));
							AnConTro();
							CanhGiua(10,dodaichuoi);
							cout << MangPhu[line/3].LaySoHieu();
							HienConTro();
						}
					}
					x = getch();
			
			}
		}
		if (line%3 == 1) // Loai
		{
			AnConTro();
			gotoxy(0,2*((line%30)/3 + 1) + 1);
			CanhGiua(30,MangPhu[line/3].LayLoai().length());
			gotoxy(wherex()+MangPhu[line/3].LayLoai().length(),wherey()); // Dua dung vi tri
			HienConTro();
			int dodaichuoi = MangPhu[line/3].LayLoai().length();
			x = getch(); // Ban muon thao tac gi tren dong nay?
			while(1)
			{
				if (x != -32 && x != 0)
				{
					kytu = 1;
				}
				else
				{
					kytu = 0;
					x = getch();
				}
			//==============BACKSPACE=====================
				if (x == 8 && kytu)
				{
					if (dodaichuoi > 0)
					{
					//==================XU LY CHUOI===================
						dodaichuoi--;
						string Loai = MangPhu[line/3].LayLoai();
						Loai.erase(Loai.end()-1,Loai.end());
						MangPhu[line/3].DatLoai(Loai);
					//=================XU LY HINH ANH=================
						AnConTro();
						gotoxy(25,wherey());
						cout << "          ";
						CanhGiua(30,dodaichuoi);
						cout << MangPhu[line/3].LayLoai();
						HienConTro();
					}	
					else
					{
						AnConTro();
						gotoxy(24,wherey());
						cout << "Khong the xoa";
						Sleep(300);
						gotoxy(24,wherey());
						cout << "             ";
						gotoxy(30,wherey());
						HienConTro();
					}	
				}
			//==============CHUC NANG======================
				if (((x == 72 || x == 80 || x == 75 || x == 77) && !kytu)  || x == 27 || x == 19)
				{
					if (MangPhu[line/3].LayLoai() != "")
					{
						break; // Khong con thao tac tren dong nay nua
					}
					else
					{
						AnConTro();
						gotoxy(21,wherey());
						cout << "Khong the bo trong";
						Sleep(300);
						gotoxy(21,wherey());
						cout << "                  ";
						gotoxy(30,wherey());
						HienConTro();
					}
				}	
			//=============NHAN CHU CAI====================
				if (((x >= 94 && x <= 122) || (x >= 65 && x <= 90) || (x >= 48 && x <=57)) && kytu) // a toi z, A toi Z, 0 toi 9 
				{
					if (dodaichuoi == 10)
					{
						AnConTro();
						gotoxy(21,wherey());
						cout << "Khong qua 10 ky tu";
						Sleep(300);
						gotoxy(21,wherey());
						cout << "                  ";
						CanhGiua(30,10);
						cout << MangPhu[line/3].LayLoai();
						HienConTro();
					}
					else
					{
						dodaichuoi++;
						InHoa(x);
						MangPhu[line/3].DatLoai(MangPhu[line/3].LayLoai() + InHoa(x));
						AnConTro();
						CanhGiua(30,dodaichuoi);
						cout << MangPhu[line/3].LayLoai();
						HienConTro();
					}
				}
				x = getch();
			}
		}
		if (line%3 == 2) // So Cho
		{
			AnConTro();
			gotoxy(0,2*((line%30)/3 + 1) + 1);
			CanhGiua(50,DoDaiSoDuong(MangPhu[line/3].LaySoCho()));
			gotoxy(wherex() + DoDaiSoDuong(MangPhu[line/3].LaySoCho()),wherey()); \
			HienConTro();
			int SoCho = MangPhu[line/3].LaySoCho();
			SoCho = LaySo(SoCho,1,x);
			while (SoCho < 20)
			{
				AnConTro();
				gotoxy(45,wherey());
				cout << "So cho > 20";
				Sleep(300);
				gotoxy(45,wherey());
				cout << "           ";
				gotoxy(50,wherey());
				HienConTro();
				SoCho = LaySo(0,1,x);
			}
			AnConTro();
			gotoxy(40,wherey());
			cout << "                   ";
			CanhGiua(50,DoDaiSoDuong(SoCho));
			cout << SoCho;
			HienConTro();
			if (x == -32 || x == 0)
			{
				kytu = 0;
				if (x == -32 || x == 0)
				{
					x = getch();
				}
			}
			MangPhu[line/3].DatSoCho(SoCho);
		}
	}
	if (x == 27)
	{
		int tungdo,hoanhdo = - 1;
		while (1) // So nhat la nguoi dung thich mua lua =))
		{
			
			gotoxy(0,28);
			cout << "Ban co muon luu thay doi?" << endl;
			cout << "Nhan 0 de huy hoac nhan 1 de luu ";
			x = getch();
			if (x == 48) // Phim 0
			{
				cout << endl;
				hoanhdo = wherex();
				tungdo = wherey();
				cout << "Ban co chan khong luu?" << endl;
				cout << "Nhan 0 de huy hoac nhan 1 de xac nhan khong luu ";
				x = getch();
				if (x == 49) 
				{
					cout << x;
					return 0;
				}
				if ((hoanhdo!= -1 && tungdo != -1) && x == 48)
				{
					gotoxy(hoanhdo,tungdo);
					cout << "                                      ";
					gotoxy(hoanhdo,tungdo+1);
					cout << "                                                     ";
				}	
			
			}
			if (x == 49) break; // So phim -32 lam =))
		}
	}
	for (int i = 0; i < a.n; i++)
	{
		for (CacChuyenBay *p = b.Head; p != NULL; p = p->next )
		{
			if (a.data[i]->LaySoHieu() == p->chuyenbay.LaySoHieu())
			{
				a.data[i]->DatSoHieu(MangPhu[i].LaySoHieu());
				p->chuyenbay.DatSoHieu(a.data[i]->LaySoHieu());
				a.data[i]->DatLoai(MangPhu[i].LayLoai());
				p->chuyenbay.DatLoai(a.data[i]->LayLoai());
				a.data[i]->DatSoCho(MangPhu[i].LaySoCho());
				p->chuyenbay.DatSoCho(a.data[i]->LaySoCho());
			}
		}
	}
	XoaManHinh();
	cout << "Luu thanh cong!"; 
	Sleep(500);
	return 1;
}
// ===================== SO LUONG MAY BAY KHA DUNG ====================================
int SoLuongMayBayKhaDung(ListChuyenBay a, ListMayBay b, int  hh, int min, int dd , int mm , int yy)
{
	int SoLuong = 0;
	for (int i = 0; i < b.n; i++)
	{
		CacChuyenBay *p = a.Head;
		while (p != NULL)
		{
			if (p->chuyenbay.LaySoHieu() == b.data[i]->LaySoHieu())
			{
				int gio = p->chuyenbay.LayGio().hour;
				int phut = p->chuyenbay.LayGio().min;
				int ngay = p->chuyenbay.LayNgay().dd;
				int thang = p->chuyenbay.LayNgay().mm;
				int nam = p->chuyenbay.LayNgay().yy;
				if(!KiemTraHaiKhoangThoiGian(hh,min,dd,mm,yy,gio,phut,ngay,thang,nam) && p->chuyenbay.LayTrangThai() != 0)
				{
					break;
				}
			}
			p = p->next;
		}
		if (p == NULL)
		{
			SoLuong++;
		}
	}
	return SoLuong;
}
int SoLuongMayBayKhaDungKhiSua(ListChuyenBay a, ListMayBay b, int hh, int min, int dd, int mm, int yy, CacChuyenBay *chuyenbay)
{
	int SoLuong = 0;
	for (int i = 0; i < b.n; i++)
	{
		CacChuyenBay *p = a.Head;
		while (p != NULL)
		{
			if (p->chuyenbay.LaySoHieu() == b.data[i]->LaySoHieu())
			{
				int gio = p->chuyenbay.LayGio().hour;
				int phut = p->chuyenbay.LayGio().min;
				int ngay = p->chuyenbay.LayNgay().dd;
				int thang = p->chuyenbay.LayNgay().mm;
				int nam = p->chuyenbay.LayNgay().yy;
				if  (p->chuyenbay.LaySoCho() < chuyenbay->chuyenbay.LaySoCho())
				{
					break;
				}
				if (p != chuyenbay)
				{
					if((!KiemTraHaiKhoangThoiGian(hh,min,dd,mm,yy,gio,phut,ngay,thang,nam) && p->chuyenbay.LayTrangThai() != 0) )
					{
						break;
					}
				}
			}
			p = p->next;
		}
		if (p == NULL)
		{
			SoLuong++;
		}
	}
	return SoLuong;
}
// ================== LAY DANH SACH MA MAY BAY KHA DUNG ================================
void DanhSachMaMayBayKhaDung(ListChuyenBay a, ListMayBay b, int hh, int min, int dd, int mm , int yy, string *p, int SoLuong)
{
//	p = new string[SoLuong];
	int dem = 0;
	for (int i = 0; i < b.n; i++)	
	{
		CacChuyenBay *q = a.Head;
		while (q != NULL)
		{
			if (q->chuyenbay.LaySoHieu() == b.data[i]->LaySoHieu())
			{
				int gio = q->chuyenbay.LayGio().hour;
				int phut = q->chuyenbay.LayGio().min;
				int ngay = q->chuyenbay.LayNgay().dd;
				int thang = q->chuyenbay.LayNgay().mm;
				int nam = q->chuyenbay.LayNgay().yy;
				if(!KiemTraHaiKhoangThoiGian(hh,min,dd,mm,yy,gio,phut,ngay,thang,nam) && q->chuyenbay.LayTrangThai() != 0)
				{
					break;
				}
			}
			q = q->next;
		}
		if (q == NULL)
		{
			p[dem] = b.data[i]->LaySoHieu();
			dem++;
		}
	}
	
}
// ========================= LAY DANH SACH MAY BAY KHA DUNG KHI SUA ==========================================
void DanhSachMaMayBayKhaDungKhiSua(ListChuyenBay a, ListMayBay b, int hh, int min, int dd, int mm , int yy, string *p, int SoLuong, CacChuyenBay *chuyenbay)
{
//	p = new string[SoLuong];
	int dem = 0;
	for (int i = 0; i < b.n; i++)	
	{
		CacChuyenBay *q = a.Head;
		while (q != NULL)
		{
			if (q->chuyenbay.LaySoHieu() == b.data[i]->LaySoHieu())
			{
				int gio = q->chuyenbay.LayGio().hour;
				int phut = q->chuyenbay.LayGio().min;
				int ngay = q->chuyenbay.LayNgay().dd;
				int thang = q->chuyenbay.LayNgay().mm;
				int nam = q->chuyenbay.LayNgay().yy;
				if (q->chuyenbay.LaySoCho() < chuyenbay->chuyenbay.LaySoCho())
				{
					break;
				}
				if ( q != chuyenbay)
				{
					if(!KiemTraHaiKhoangThoiGian(hh,min,dd,mm,yy,gio,phut,ngay,thang,nam) && q->chuyenbay.LayTrangThai() != 0)
					{
						break;
					}
				}
			}
			q = q->next;
		}
		if (q == NULL)
		{
			p[dem] = b.data[i]->LaySoHieu();
			dem++;
		}
	}
	
}
//===================================NHAP DU LIEU CHUYEN BAY===================================
CacChuyenBay *NhapDuLieuChuyenBay(ListChuyenBay &a, ListMayBay &b) 
{

	string MaChuyenBay = "";
	int dd = 0;
	int mm = 0;
	int yy = 0;
	int gio = 0;
	int phut = 0;
	string den = "";
	int trangthai = -1;
	string MaMayBay1 = "";
	int SoLuongMayBay = -1;
	int dodaichuoi = MaChuyenBay.length();
	gotoxy (130,0);
	CuaSoChuyenBay();
	int line = 1;
	gotoxy(158,2); // Ma chuyen bay
	HienConTro();
	char x = getch();
	bool kytu;
	if (x == -32 || x == 0)
	{
		kytu = 0;
		x = getch();
	}
	else
	{
		kytu = 1;
	}
	bool kt = 0; 
	bool luu = 0;
	int maxtrangthai = 3;
	while (1 && !luu)
	{
		luu = 0;
		while (x != 27 && !luu ) // Esc
		{
			kt = 0;
			if (x == 75 && !kytu) // left
			{
				if (line > 1)
				{
					line--;
				}
			}
			if (x == 77 && !kytu) // right
			{
				if (line == 1)
				{
					if (KiemTraTrungMaChuyenBay(a,MaChuyenBay))
					{
						AnConTro();
						gotoxy(158-9,2);
						cout << "Trung Ma chuyen bay";
						Sleep(500);
						gotoxy(158-9,2);
						cout << "                   ";
						gotoxy(158-3,2);
						cout << "Thu lai";
						Sleep(500);
						gotoxy(158-3,2);
						cout << "       ";
						CanhGiua(158,MaChuyenBay.length());
						HienConTro();
					}
					else
					{
						if (dodaichuoi == 0)
						{
							AnConTro();
							gotoxy(158-9,2);
							cout << "Khong the bo trong";
							Sleep(500);
							gotoxy(158-9,2);
							cout << "                  ";
							gotoxy(158,2);
							HienConTro();
						}
						else
						{
							if (line < 10)
							{
								line++;
							}
						}
					}
				}
				else
				{
					if (line < 10)
					{
						line++;
					}
				}
			}
			switch (line)
			{
				case 1: // Ma Chuyen bay
					{
						AnConTro();
						gotoxy(0,2);
						CanhGiua(158, MaChuyenBay.length());
						cout << MaChuyenBay;
						HienConTro();
						if (x == 8) // Backspace
						{
							if (dodaichuoi == 0)
							{
								AnConTro();
								gotoxy(158-6,2);
								cout << "Khong the xoa";
								Sleep(500);
								gotoxy(158-6,2);
								cout << "             ";
								gotoxy(158,2);
								HienConTro();
							}
							else
							{
								AnConTro();
								gotoxy(149,2);
								cout << "                  ";
								MaChuyenBay.erase(MaChuyenBay.length()-1,MaChuyenBay.length());
								dodaichuoi--;
								CanhGiua(158,MaChuyenBay.length());
								cout << MaChuyenBay;
								HienConTro();
							}
						}
						if (((x >= 95 && x <= 122) || (x >= 65 && x <= 90) || (x >= 48 && x <= 57)) && kytu) // a -> z, A -> Z, 0 -> 9
						{
							if (dodaichuoi < 15)
							{
								AnConTro();
								gotoxy(149,2);
								cout << "                  ";
								MaChuyenBay = MaChuyenBay + InHoa(x);
								dodaichuoi++;
								CanhGiua(158,MaChuyenBay.length());
								cout << MaChuyenBay;
								HienConTro();
							}
							else
							{
								AnConTro();
								gotoxy(158-9,2);
								cout << "Khong qua 15 ky tu";
								Sleep(500);
								gotoxy(158-9,2);
								cout << "                  ";
								CanhGiua(158,MaChuyenBay.length());
								cout << MaChuyenBay;
								HienConTro();
							}
						}

						break;
					}
				case 2: // dd
					{
						AnConTro();
						gotoxy(140,8);
						cout << "  ";
						gotoxy(171, wherey());
						cout << "->";
						gotoxy(wherex() +1, wherey()-1);
						KhungPopUp();
						gotoxy(0,8);
						CanhGiua(178,2);
						cout << "DD";
						//===== MENU NGAY ==========
						int max = DaysOfMounth(mm,yy);
						int *Ngay = new int[max];
						for (int i = 0; i < max; i++) // Khoi tao
						{
							Ngay[i] = i+1;
						}
						// Lay du lieu cu
						if (dd != 0)
						{
							if (dd > DaysOfMounth(mm,yy))
							{
								dd = DaysOfMounth(mm,yy);
							}
							while (Ngay[0] != dd)
							{
								int temp = Ngay[max-1];
								for (int i = max-1; i >= 1; i--)
								{
									Ngay[i] = Ngay[i-1];
								}
								Ngay[0] = temp;
							}
						}
						// HIGH LIGHT
						gotoxy(175,10);
						ChangeColor(240);
						if (Ngay[0] <= 9)
						{
							cout << "  0" << Ngay[0] << "  ";
						}
						else
						{
							cout << "  " << Ngay[0] << "  ";
						}
						ChangeColor(15);
						for (int i = 1; i <= 9; i++) // In ngay
						{
							gotoxy(177,10+i);
							if (Ngay[i] <= 9)
							{
								cout << "0" << Ngay[i];
							}
							else
							{
								cout << Ngay[i];
							}
						}
						gotoxy(140,8);
						if (Ngay[0] <= 9)
						{
							cout << "0" << Ngay[0];
						}
						else
						{
							cout << Ngay[0];
						}
						HienConTro();
						// ============== CHON NGAY ============
						char s = getch();
						bool kytu1;
						if (s == -32 || s == 0)
						{
							kytu1 = 0;
							s = getch();
						}
						else
						{
							kytu1 = 1;
						}
						while (s != 27)
						{
							if(s == 75 && !kytu1)// Left
							{
								x = 75;
								kytu = 0;
								kt = 1;
								dd = Ngay[0];
								break;
							}
							if(s == 77 && !kytu1)// Right
							{
								x = 77;
								kytu = 0;
								kt = 1;
								dd = Ngay[0];
								break;
							}
							if (s == 72 && !kytu1) // Up
							{
								int temp = Ngay[max-1];
								for (int i = max-1; i >= 1; i--)
								{
									Ngay[i] = Ngay[i-1];
								}
								Ngay[0] = temp;
							}
							if (s == 80 && !kytu1) // Down
							{
								int temp = Ngay[0];
								for (int i = 0; i <= max-2; i++)
								{
									Ngay[i] =  Ngay[i+1];
								}
								Ngay[max-1] = temp;
							}
							for (int i = 0; i <= 9; i++) // In Ngay
							{
								gotoxy(175,10+i);
								if (Ngay[i] <= 9)
								{
									cout << "  0" << Ngay[i] << "  "; 
								}
								else
								{
									cout << "  " << Ngay[i] << "  ";
								}
							}
							// Highlight
							ChangeColor(240);
							gotoxy(175,10);
							if (Ngay[0] <= 9 )
							{
								cout << "  0" << Ngay[0] << "  ";
							}
							else
							{
								cout << "  " << Ngay[0] << "  ";
							}
							ChangeColor(15);
							gotoxy(140,8);
							if (Ngay[0] <= 9)
							{
								cout << "0" << Ngay[0];
							}
							else
							{
								cout << Ngay[0];
							}
							s = getch();
							if (s == -32 || s == 0)
							{
								kytu1 = 0;
								s = getch();
							}
							else
							{
								kytu1 = 1;
							}
							HienConTro();
						}
						AnConTro();
						gotoxy(171,8);
						cout << "   ";
						gotoxy(wherex(), wherey()-1);
						ClearKhungPopUp();
						if (s == 27)
						{
							x = 27;
							kt = 1;
						}
						break;
					}
				case 3: // mm
					{
						AnConTro();
						gotoxy(149,8);
						cout << "  ";
						gotoxy(171,wherey());
						cout << "-> ";
						gotoxy(wherex(), wherey()-1);
						KhungPopUp();
						gotoxy(0,8);
						CanhGiua(178,2);
						cout << "MM";
						int Thang[12];
						for (int i = 0; i < 12; i++)
						{
							Thang[i] = i+1;
						}
						// Lay du lieu cu
						if (mm != 0)
						{
							while (Thang[0] != mm)
							{
								int temp = Thang[11];
								for (int i = 11; i >= 1; i-- )
								{
									Thang[i] = Thang[i - 1];
								}
								Thang[0] = temp;
							}
						}
						for (int i = 0; i < 10; i++)
						{
							gotoxy(175,10+i);
							if (Thang[i] <= 9)
							{
								cout << "  0" << Thang[i] << "  ";
							}
							else
							{
								cout << "  " << Thang[i] << "  ";
							}
						}
						// Highlight
						gotoxy(175,10);
						ChangeColor(240);
						gotoxy(175,10);
						if (Thang[0] <= 9)
						{
							cout << "  0" << Thang[0] << "  ";
						}
						else
						{
							cout << "  " << Thang[0] << "  ";
						}
						ChangeColor(15);
						gotoxy(149,8);
						if (Thang[0] <= 9)
						{
							cout << "0" << Thang[0];
						}
						else
						{
							cout << Thang[0];
						}
						HienConTro();
						char s = getch();
						bool kytu1;
						if (s == -32 || s == 0)
						{
							kytu1 = 0;
							s = getch();
						}
						else
						{
							kytu1 = 1;
						}
						while (s != 27) // Khong phai Esc
						{
							AnConTro();
							if (s == 75 && !kytu1) // Left
							{
								mm = Thang[0];
								if (dd > DaysOfMounth(mm,yy))
								{
									dd = DaysOfMounth(mm,yy);
									gotoxy(140,8);
									cout << dd;
								//	HienConTro();
								}
								x = 75; 
								kytu = 0;
								kt = 1;
								break;
							}
							if (s == 77 && !kytu1) // Right
							{
								x = 77;
								kytu = 0;
								kt = 1;
								mm = Thang[0];
								if (dd > DaysOfMounth(mm,yy))
								{
									dd = DaysOfMounth(mm,yy);
									gotoxy(140,8);
									cout << dd;
								//	HienConTro();
								}
								break;
							}
							if (s == 72 && !kytu1) // Up
							{
								int temp = Thang[11];
								for (int i = 11; i >= 1; i-- )
								{
									Thang[i] = Thang[i - 1];
								}
								Thang[0] = temp;
							}
							if (s == 80 && !kytu1) // Down
							{
								int temp = Thang[0];
								for (int i = 0; i < 11; i++)
								{
									Thang[i] = Thang[i + 1];
								}
								Thang[11] = temp;
							}
							for (int i = 0; i <= 9; i++) // In thang
							{
								gotoxy(175,10+i);
								if (Thang[i] <= 9)
								{
									cout << "  0" << Thang[i] << "  ";
								}
								else
								{
									cout << "  " << Thang[i] << "  ";
								}
							}
							// Highlight
							gotoxy(175,10);
							ChangeColor(240);
							if  (Thang[0] <= 9)
							{
								cout << "  0" << Thang[0] << "  ";
							}
							else
							{
								cout << "  " << Thang[0] << "  ";
							}
							ChangeColor(15);
							gotoxy(148,8);
							if (Thang[0] <= 9)
							{
								cout << " 0" << Thang[0];
							}
							else
							{
								cout << " " << Thang[0];
							}
							HienConTro();
							s = getch();
							if (s == -32 || s == 0)
							{
								kytu1 = 0;
								s = getch();
							}
							else
							{
								kytu1 = 1;
							}
						}
						// Ket thuc
						AnConTro();
						gotoxy(171,8);
						cout << "   ";
						gotoxy(wherex(), wherey()-1);
						ClearKhungPopUp();
						if (s == 27)
						{
							x = 27;
							kt = 1;
						}
						break;
					}
				case 4: // yy
					{
						AnConTro();
						int so;
						gotoxy(158,8);
						cout << "    ";
						gotoxy(171,wherey());
						cout << "-> ";
						gotoxy(wherex(),wherey()-1);
						KhungPopUp();
						gotoxy(0,8);
						CanhGiua(178,4);
						cout << "YYYY";
						int Nam[4];
						for (int i = 0; i < 4; i++)
						{
							Nam[i] = i + 2022;
							gotoxy(175,i+10);
							cout << " " << Nam[i] << " ";
						}
						// HIGH LIGHT
						if (yy != 0)
						{
							gotoxy(175,10 + (yy-2022));
							ChangeColor(240);
							cout << " " << yy << " ";
							ChangeColor(15);
							gotoxy(158,8);
							cout << yy;
							so = yy - 2022;
							HienConTro();
						}
						else
						{
							gotoxy(175,10);
							ChangeColor(240);
							cout << " " << Nam[0] << " ";
							ChangeColor(15);
							gotoxy(158,8);
							cout << Nam[0];
							so = 0;
							HienConTro();
						}
						char s = getch();
						bool kytu1;
						if (s == -32 || s == 0)
						{
							kytu1 = 0;
							s = getch();
						}
						else
						{
							kytu1 = 1;
						}
						while (s != 27 && s != 13) // Khac Esc or Enter
						{
							AnConTro();
							if (s == 75 && !kytu1) // Left
							{
								// Khong o thao tac nay
								x = 75;
								kytu = 0;
								kt = 1;
								yy = Nam[so];
								if (dd > DaysOfMounth(mm,yy))
								{
									dd = DaysOfMounth(mm,yy);
									gotoxy(140,8);
									cout << dd;
								//	HienConTro();
								}
								break;
							}
							if (s == 77 && !kytu1) // Right
							{
								// Khong con o thao tac nay
								x = 77; 
								kytu = 0;
								kt = 1;
								yy = Nam[so];
								if (dd > DaysOfMounth(mm,yy))
								{
									dd = DaysOfMounth(mm,yy);
									gotoxy(140,8);
									cout << dd;
								//	HienConTro();
								}
								break;
							} 
							if (s == 72 && !kytu1) // Up
							{
								if (so > 0)
								{
									so--;
								}
							}
							if (s == 80 && !kytu1)
							{
								if (so < 3)
								{
									so++;
								}
							}
							// In ds nam
							for (int i = 0; i < 4; i++)
							{
								gotoxy(175,i+10);
								cout << " " << Nam[i] << " ";
							}
							// high light
							gotoxy(175,so+10);
							ChangeColor(240);
							cout << " " << Nam[so] << " ";
							ChangeColor(15);
							gotoxy(158,8);
							cout << Nam[so];
							HienConTro();
							s = getch();
							if (s == -32 || s == 0)
							{
								kytu1 = 0;
								s = getch();
							}
							else
							{
								kytu1 = 1;
							}
						}
						// Ket thuc 
						AnConTro();
						gotoxy(171,8);
						cout << "   ";
						gotoxy(wherex(), wherey()-1);
						ClearKhungPopUp();
						if (s == 27)
						{
							x = 27;
							kt = 1;
						}
						break;
					}
				case 5: //gio
					{
						AnConTro();
						gotoxy(145,12);
						cout << "  ";
						gotoxy(171,12);
						cout << "-> ";
						gotoxy(wherex(), wherey()-1);
						KhungPopUp();
						gotoxy(0,12);
						CanhGiua(178,4);
						cout << "HOUR";
						int Gio[24];
						for (int i = 0; i < 24; i++)
						{
							Gio[i] = i;
						}
						// Lay gio cu
						while (Gio[0] != gio)
						{
							int temp = Gio[0];
							for (int i = 0; i <= 22; i++)
							{
								Gio[i] = Gio[i+1];
							}
							Gio[23] = temp;
						}
						for (int i = 0; i < 10; i++)
						{
							AnConTro();
							gotoxy(175,14+i);
							if (Gio[i] <= 9)
							{
								cout << "  0" << Gio[i] << "  ";
							}
							else
							{
								cout << "  " << Gio[i] << "  ";
							}
						}
						// Highlight
						gotoxy(175,14);
						ChangeColor(240);
						if (Gio[0] <= 9)
						{
							cout << "  0" << Gio[0] << "  ";
						}
						else
						{
							cout << "  " << Gio[0] << "  ";
						}
						ChangeColor(15);
						gotoxy(145,12);
						if (Gio[0] <= 9)
						{
							cout << "0" << Gio[0];
						}
						else
						{
							cout << Gio[0];
						}
						HienConTro();
						char s = getch();
						bool kytu1;
						if (s == -32 || s == 0)
						{
							kytu1 = 0;
							s = getch();
						}
						else
						{
							kytu1 = 1;
						}
						while (s != 27)
						{
							if (s == 75 && !kytu) // Left
							{
								x = 75;
								kytu = 0;
								kt = 1;
								gio = Gio[0];
								break;
							}
							if (s == 77 && !kytu1) // Right
							{
								x = 77;
								kytu = 0;
								kt = 1;
								gio = Gio[0];
								break;
							} 
							if (s == 72 && !kytu1) // Up
							{
								int temp = Gio[23];
								for (int i = 23; i >= 1; i--)
								{
									Gio[i] = Gio[i-1];
								}
								Gio[0] = temp;
							}
							if (s == 80 && !kytu1) // Down
							{
								int temp = Gio[0];
								for (int i = 0; i <= 22; i++)
								{
									Gio[i] = Gio[i+1];
								}
								Gio[23] = temp;
							}
							for (int i = 0; i < 10; i++)
							{
								AnConTro();
								gotoxy(175,14+i);
								if (Gio[i] <= 9)
								{
									cout << "  0" << Gio[i] << "  ";
								}
								else
								{
									cout << "  " << Gio[i] << "  ";
								}
							}
							// Highlight
							gotoxy(175,14);
							ChangeColor(240);
							if (Gio[0] <= 9)
							{
								cout << "  0" << Gio[0] << "  ";
							}
							else
							{
								cout << "  " << Gio[0] << "  ";
							}
							ChangeColor(15);
							gotoxy(145,12);
							if(Gio[0] <= 9)
							{
								cout << "0" << Gio[0];
							}
							else
							{
								cout << Gio[0];
							}
							HienConTro();
							s = getch();
							if (s == -32 || s == 0)
							{
								kytu1 = 0;
								s = getch();
							}
							else
							{
								kytu1 = 1;
							}
						}
						// Ket thuc
						gotoxy(171,12);
						cout << "   ";
						gotoxy(wherex(),wherey()-1);
						ClearKhungPopUp();
						if (s == 27)
						{
							x = 27;
							kt = 1;
						}
						break;
					}
				case 6: // min
					{
						AnConTro();
						gotoxy(154,12);
						cout << "  ";
						gotoxy(171,12);
						cout << "-> ";
						gotoxy(wherex(), wherey()-1);
						KhungPopUp();
						gotoxy(0,12);
						CanhGiua(178,3);
						cout << "MIN";
						gotoxy(154,12);
						int Phut[60];
						for (int i = 0; i < 60; i++)
						{
							Phut[i] = i;
						}
						// Lay phut cu
						while (Phut[0] != phut)
						{
							int temp = Phut[0];
							for (int i = 0; i <= 58; i++)
							{
								Phut[i] = Phut[i+1];
							}
							Phut[59] = temp;
						}
						for (int i = 0; i < 10; i++)
						{
							AnConTro();
							gotoxy(175,14+i);
							if (Phut[i] <= 9)
							{
								cout << "  0" << Phut[i] << "  ";
							}
							else
							{
								cout << "  " << Phut[i] << "  ";
							}
						}
						// Highlight
						gotoxy(175,14);
						ChangeColor(240);
						if (Phut[0] <= 9)
						{
							cout << "  0" << Phut[0] << "  ";
						}
						else
						{
							cout << "  " << Phut[0] << "  ";
						}
						ChangeColor(15);
						gotoxy(154,12);
						if (Phut[0] <= 9)
						{
							cout << "0" << Phut[0];
						}
						else
						{
							cout << Phut[0];
						}
						HienConTro();
						char s = getch();
						bool kytu1;
						if (s == -32 || s == 0)
						{
							kytu1 = 0;
							s = getch();
						}
						else
						{
							kytu1 = 1;
						}
						while (s != 27)
						{
							if (s == 75 && !kytu) // Left
							{
								x = 75;
								kytu = 0;
								kt = 1;
								phut = Phut[0];
								break;
							}
							if (s == 77 && !kytu1) // Right
							{
								x = 77;
								kytu = 0;
								kt = 1;
								phut = Phut[0];
								break;
							} 
							if (s == 72 && !kytu1) // Up
							{
								int temp = Phut[59];
								for (int i = 59; i >= 1; i--)
								{
									Phut[i] = Phut[i-1];
								}
								Phut[0] = temp;
							}
							if (s == 80 && !kytu1) // Down
							{
								int temp = Phut[0];
								for (int i = 0; i <= 58; i++)
								{
									Phut[i] = Phut[i+1];
								}
								Phut[59] = temp;
							}
							for (int i = 0; i < 10; i++)
							{
								AnConTro();
								gotoxy(175,14+i);
								if (Phut[i] <= 9)
								{
									cout << "  0" << Phut[i] << "  ";
								}
								else
								{
									cout << "  " << Phut[i] << "  ";
								}
							}
							// Highlight
							gotoxy(175,14);
							ChangeColor(240);
							if (Phut[0] <= 9)
							{
								cout << "  0" << Phut[0] << "  ";
							}
							else
							{
								cout << "  " << Phut[0] << "  ";
							}
							ChangeColor(15);
							gotoxy(154,12);
							if(Phut[0] <= 9)
							{
								cout << "0" << Phut[0];
							}
							else
							{
								cout << Phut[0];
							}
							HienConTro();
							s = getch();
							if (s == -32 || s == 0)
							{
								kytu1 = 0;
								s = getch();
							}
							else
							{
								kytu1 = 1;
							}
						}
						// Ket thuc
						gotoxy(171,12);
						cout << "   ";
						gotoxy(wherex(),wherey()-1);
						ClearKhungPopUp();
						
						if (s == 27)
						{
							x = 27;
							kt = 1;
						}
						break;
					}
				case 7: // Den
					{
						AnConTro();
						gotoxy(142,16);
						cout << "                  ";
						gotoxy(171,16);
						cout << "-> ";
						gotoxy(wherex(),wherey()-1);
						KhungPopUp2();
						gotoxy(0,16);
						CanhGiua(185,3);
						cout << "DEN";
						string Den[21];
						{
							Den[0] = "Vung Tau";
							Den[1] = "Binh Dinh";
							Den[2] = "Ca Mau";
							Den[3] = "Can Tho";
							Den[4] = "Dak Lak";
							Den[5] = "Da Nang";
							Den[6] = "Dien Bien";
							Den[7] = "Gia Lai";
							Den[8] = "Hai Phong";
							Den[9] = "Ha Noi";
							Den[10] = "Khanh Hoa";
							Den[11] = "Rach Gia";
							Den[12] = "Phu Quoc";
							Den[13] = "Lam Dong";
							Den[14] = "Nghe An";
							Den[15] = "Phu Yen";
							Den[16] = "Quang Binh";
							Den[17] = "Quang Nam";
							Den[18] = "Hue";
							Den[19] = "Thanh Hoa";
							Den[20] = "Quang Ninh";
						}
						if (den.length() != 0) 
						{
							while (Den[0] != den)
							{
								string temp = Den[0];
								for (int i = 0; i <= 19; i++)
								{
									Den[i] = Den[i+1];
								}
								Den[20] = temp;
							}
						}
						for (int i = 0; i < 10; i++)
						{
							AnConTro();
							gotoxy(175,18+i);
							cout << "                    ";
							CanhGiua(185,Den[i].length());
							cout << Den[i];
						}
						gotoxy(175,18);
						ChangeColor(240);
						cout << "                    ";
						CanhGiua(185,Den[0].length());
						cout << Den[0];
						ChangeColor(15);
						gotoxy(0,16);
						CanhGiua(151,Den[0].length());
						cout << Den[0];
						HienConTro();
						char s = getch();
						bool kytu1;
						if (s == -32 || s == 0)
						{
							kytu1 = 0;
							s = getch();
						}
						else
						{
							kytu1 = 1;
						}
						while (s != 27)
						{
							if (s == 75 && !kytu1) // Left
							{
								den = Den[0];
								x = 75;
								kytu = 0;
								kt = 1;
								break;
							}
							if (s == 77 && !kytu1) // right
							{
								den = Den[0];
								x = 77;
								kytu = 0;
								kt = 1;
								break;
							}
							if (s == 72 && !kytu1) // Up
							{
								string temp = Den[20];
								for (int i = 20; i >= 1; i--)
								{
									Den[i] = Den[i-1];
								}
								Den[0] = temp;
							}
							if (s == 80 && !kytu1) // Down
							{
								string temp = Den[0];
								for (int i = 0; i <= 19; i++)
								{
									Den[i] = Den[i+1];
								}
								Den[20] = temp;
							}
							for (int i = 0; i < 10; i++)
							{
								AnConTro();
								gotoxy(175,18+i);
								cout << "                    ";
								CanhGiua(185,Den[i].length());
								cout << Den[i];
							}
							// Highlight
							gotoxy(175,18);
							ChangeColor(240);
							cout << "                    ";
							CanhGiua(185,Den[0].length());
							cout << Den[0];
							ChangeColor(15);
							gotoxy(142,16);
							cout << "                  ";
							CanhGiua(151,Den[0].length());
							cout << Den[0];
							HienConTro();
							s = getch();
							if (s == -32 || s == 0)
							{
								kytu1 = 0;
								s = getch();
							}
							else
							{
								kytu1 = 1;
							}
						}
					//	gotoxy(151,16);
					//	HienConTro();
						gotoxy(171,16);
						cout << "   ";
						gotoxy(wherex(),wherey()-1);
						ClearKhungPopUp2();
						if (s == 27)
						{
							x = 27;
							kt = 1;
						}
						break;
					}
				case 8: 
					{
						AnConTro();
						gotoxy(149,20);
						cout << "           ";
						gotoxy(171,20);
						cout << "-> ";
						gotoxy(wherex(), wherey()-1);
						KhungPopUp2();
						gotoxy(0,20);
						CanhGiua(185,10);
						cout << "TRANG THAI";
						string *TrangThai;
						if (KiemTraThoiGian(gio,phut,dd,mm,yy)) 
						{
							maxtrangthai = 3;
							TrangThai = new string[3];
							TrangThai[0] = "Huy Chuyen";
							TrangThai[1] = "Con ve";
							TrangThai[2] = "Het ve";
//							TrangThai[3] = "Hoan Tat";
						}
						else
						{
							maxtrangthai = 2;
							TrangThai = new string[2];
							TrangThai[0] = "Huy Chuyen";
							TrangThai[1] = "Hoan Tat";
						}
						if (trangthai != -1)
						{
							if (maxtrangthai == 2)
							{
								if (trangthai == 1 || trangthai == 2) // Khong hop le trong truong hop nay
								{
									trangthai = 3; // Dua ve Hoan tat
								}
							}
							else
							{
								if (trangthai != 0)
								{
									trangthai = 1; // Dua ve con ve
								}
							}
						}
						if (trangthai == -1)
						{
							trangthai = 1;
						}
						if (maxtrangthai == 3)
						{
							for (int i = 0; i < 3; i++)
							{
								gotoxy(175,22+i);
								cout << "                    ";
								CanhGiua(185,TrangThai[i].length());
								cout << TrangThai[i];
							}
							// highlight
							gotoxy(175,22+trangthai);
							ChangeColor(240);
							cout << "                    ";
							CanhGiua(185,TrangThai[trangthai].length());
							cout << TrangThai[trangthai];
							ChangeColor(15);
							gotoxy(149,20);
							cout << "           ";
							CanhGiua(155,TrangThai[trangthai].length());
							cout << TrangThai[trangthai];
							HienConTro();
						}
						else
						{
							for (int i = 0; i < 3; i++)
							{
								gotoxy(175,22+i);
								cout << "                    ";
								if (i == 0 || i == 1)
								{
									CanhGiua(185,TrangThai[i].length());
									cout << TrangThai[i];
								}
							}
							// highlight
							if (trangthai == 0)
							{
								gotoxy(175,22);
								ChangeColor(240);
								cout << "                    ";
								CanhGiua(185,9);
								cout << "Huy Chuyen";
								ChangeColor(15);
								gotoxy(149,20);
								cout << "           ";
								CanhGiua(155,10);
								cout << "Huy Chuyen";
								HienConTro();
							}
							else
							{
								gotoxy(175,23);
								ChangeColor(240);
								cout << "                    ";
								CanhGiua(185,8);
								cout << "Hoan Tat";
								ChangeColor(15);
								gotoxy(149,20);
								cout << "           ";
								CanhGiua(155,8);
								cout << " Hoan Tat";
								HienConTro();
							}
						}
						char s = getch();
						bool kytu1;
						if (s == -32 || s == 0)
						{
							kytu1 = 0;
							s = getch();
						}
						else
						{
							kytu = 1;
						}
						int dong;
						if (maxtrangthai == 3)
						{
							dong = trangthai;
						}
						else
						{
							if (trangthai == 0)
							{
								dong = 0;
							}
							else
							{
								dong = 1;
							}
						}
						while (s != 27)
						{
							if (s == 75 && !kytu1) // Left
							{
								x = 75;
								kytu = 0;
								kt = 1;
								if (maxtrangthai == 3)
								{
									trangthai = dong;
								}
								else
								{
									if (dong == 0)
									{
										trangthai = dong;
									}
									else
									{
										trangthai = 3;
									}
								}
								break;
							}
							if (s == 77 && !kytu1) // Right
							{
								x = 77;
								kytu = 0;
								kt = 1;
								if (maxtrangthai == 3)
								{
									trangthai = dong;
								}
								else
								{
									if (dong == 0)
									{
										trangthai = dong;
									}
									else
									{
										trangthai = 3;
									}
								}
								break;
							}
							if (s == 72 && !kytu1) // Up
							{
								if (dong > 0)
								{
									dong--;
								}
							}
							if (s == 80 && !kytu1)
							{
								if (maxtrangthai == 3)
								{
									if (dong < 2)
									{
										dong++;
									}
								}
								else
								{
									if (dong < 1)
									{
										dong++;
									}
								}
							}
							if(maxtrangthai == 3)
							{
								for (int i = 0; i < 3; i++)
								{
									AnConTro();
									gotoxy(175,22+i);
									cout << "                    ";
									CanhGiua(185,TrangThai[i].length());
									cout << TrangThai[i];
									// highlight
									gotoxy(175,22+dong);
									ChangeColor(240);
									cout << "                    ";  
									CanhGiua(185,TrangThai[dong].length());
									cout << TrangThai[dong];
									// In Noi dung
									ChangeColor(15);
									gotoxy(149,20);
									cout << "           ";
									CanhGiua(155,TrangThai[dong].length());
									cout << TrangThai[dong];
									HienConTro();
								}
							}
							else
							{
								for (int i = 0; i < 2; i++)
								{
									AnConTro();
									gotoxy(175,22+i);
									cout << "                    ";
									if (i == 0)
									{
										CanhGiua(185,10);
										cout << "Huy Chuyen";
									}
									else
									{
										CanhGiua(185,8);
										cout << "Hoan Tat";
									}
								}
								// highlight
								gotoxy(175,22+dong);
								ChangeColor(240);
								cout << "                    ";
								if (dong == 0)
								{
									CanhGiua(185,10);
									cout << "Huy Chuyen";
								}
								else
								{
									CanhGiua(185,8);
									cout << "Hoan Tat";
								}
								// In Noi dung
								ChangeColor(15);
								gotoxy(149,20);
								cout << "           ";
								if (dong == 0)
								{
									CanhGiua(155,10);
									cout << "Huy Chuyen";
									HienConTro();
								}
								else
								{
									CanhGiua(155,8);
									cout << "Hoan Tat";
									HienConTro();
								}
							}
							s = getch();
							if (s == -32 || s == 0)
							{
								kytu1 = 0;
								s = getch();
							}
							else
							{
								kytu1 = 1;
							}
						}
					//	gotoxy(154,20);
					//	gotoxy(154,20);
						gotoxy(171,20);
						cout << "   ";
						gotoxy(wherex(),wherey()-1);
						ClearKhungPopUp2();
						if (s == 27)
						{
							x = 27;
							kt = 1;
						}
						break;
					}
				case 9: // Ma May Bay
					{
						AnConTro();
						gotoxy(171,24);
						cout << "-> ";
						gotoxy(wherex(),wherey()-1);
						KhungPopUp2();
						gotoxy(0,24);
						CanhGiua(185,10);
						cout << "MA MAY BAY";
						SoLuongMayBay = SoLuongMayBayKhaDung(a,b,gio,phut,dd,mm,yy);
					//	gotoxy(175,30);
					//	cout << SoLuongMayBay;
						string *MaMayBay;
						if (SoLuongMayBay == 0)
						{
							AnConTro();
							gotoxy(147,24);
							cout << "                  ";
							gotoxy(147,24);
							cout << "Khong co may bay";
							Sleep(500);
							gotoxy(147,24);
							cout << "                ";
							gotoxy(152,24);
							cout << "kha dung";
							Sleep(500);
							gotoxy(152,24);
							cout << "        ";
							gotoxy(156,24);
							HienConTro();
							char s = getch();
							bool kytu1;
							if (s == -32 || s == 0)
							{
								kytu1 = 0;
								s = getch();
							}
							else
							{
								kytu1 = 1;
							}
							while (s != 75 && !kytu1) // Left
							{
								s = getch();
								if (s == -32 || s == 0)
								{
									kytu1 = 0;
									s = getch();
								}
								else
								{
									kytu1 = 1;
								}
							}
							x = 75;
							kytu = 0;
							kt = 1;
							gotoxy(171,24);
							cout << "   ";
							gotoxy(wherex(),wherey()-1);
							ClearKhungPopUp2();
							break;
						}
						MaMayBay = new string[SoLuongMayBay];
						DanhSachMaMayBayKhaDung(a,b,gio,phut,dd,mm,yy,MaMayBay,SoLuongMayBay);

						if (MaMayBay1.length() == 0)
						{
							MaMayBay1 = MaMayBay[0];
						}
						else
						{
							for ( int i = 0; i < SoLuongMayBay; i++)
							{
								string temp = MaMayBay[0];
								for (int j = 0; j < SoLuongMayBay-1; j++)
								{
									MaMayBay[j] = MaMayBay[j+1];
								}
								MaMayBay[SoLuongMayBay-1] = temp;
								if(MaMayBay[0] == MaMayBay1)
								{
									break;
								}
							}
							MaMayBay1 = MaMayBay[0];
						}
						if (SoLuongMayBay < 10)
						{
							for (int i = 0; i < SoLuongMayBay; i++)
							{
								gotoxy(175,26+i);
								cout << "                    ";
								CanhGiua(185,MaMayBay[i].length());
								cout << MaMayBay[i];
							}
							// Highlight
							gotoxy(175,26);
							ChangeColor(240);
							cout << "                    ";
							CanhGiua(185,MaMayBay[0].length());
							cout << MaMayBay[0];
							gotoxy(147,24);
							ChangeColor(15);
							cout << "                  ";
							CanhGiua(156,MaMayBay[0].length());
							cout << MaMayBay[0];
							HienConTro();
						}
						else
						{
							for (int i = 0; i < 10; i++)
							{
								gotoxy(175,26+i);
								cout << "                    ";
								CanhGiua(185,MaMayBay[i].length());
								cout << MaMayBay[i];
							}
							// Highlight
							gotoxy(175,26);
							ChangeColor(240);
							cout << "                    ";
							CanhGiua(185,MaMayBay[0].length());
							cout << MaMayBay[0];
							gotoxy(147,24);
							ChangeColor(15);
							cout << "                  ";
							CanhGiua(156,MaMayBay[0].length());
							cout << MaMayBay[0];
							HienConTro();
						}
						char s = getch();
						bool kytu1;
						if (s == -32 || s == 0)
						{
							kytu1 = 0;
							s = getch();
						}
						else
						{
							kytu1 = 1;
						}
						while (s != 27)
						{
							AnConTro();
							if (s == 75 && !kytu1) // Left
							{
								MaMayBay1 = MaMayBay[0];
								kytu = 0;
								x = 75;
								kt = 1;
								break;
							}
							if (s == 77 && !kytu1) // Right
							{
								MaMayBay1 = MaMayBay[0];
								kytu = 0;
								x = 77;
								kt = 1;
								break;
							}
							if (s == 72 && !kytu1) // Up
							{
								string temp = MaMayBay[SoLuongMayBay - 1];
								for (int i = SoLuongMayBay - 1; i >= 1; i--)
								{
									MaMayBay[i] = MaMayBay[i-1];
								}
								MaMayBay[0] = temp;
							}
								if (s == 80 && !kytu1) // Down
							{
								string temp = MaMayBay[0];
								for (int i = 0; i < SoLuongMayBay - 1; i++)
								{
									MaMayBay[i] = MaMayBay[i+1];
								}
								MaMayBay[SoLuongMayBay-1] = temp;
							}
							if (SoLuongMayBay < 10)
							{
								for (int i = 0; i < SoLuongMayBay; i++)
								{
									gotoxy(175,26+i);
									cout << "                    ";
									CanhGiua(185,MaMayBay[i].length());
									cout << MaMayBay[i];
								}
								// Highlight
								gotoxy(175,26);
								ChangeColor(240);
								cout << "                    ";
								CanhGiua(185,MaMayBay[0].length());
								cout << MaMayBay[0];
								gotoxy(147,24);
								ChangeColor(15);
								cout << "                  ";
								CanhGiua(156,MaMayBay[0].length());
								cout << MaMayBay[0];
								HienConTro();
							}
							else
							{
								for (int i = 0; i < 10; i++)
								{
									gotoxy(175,26+i);
									cout << "                    ";
									CanhGiua(185,MaMayBay[i].length());
									cout << MaMayBay[i];
								}
								// Highlight
								gotoxy(175,26);
								ChangeColor(240);
								cout << "                    ";
								CanhGiua(185,MaMayBay[0].length());
								cout << MaMayBay[0];
								gotoxy(147,24);
								ChangeColor(15);
								cout << "                  ";
								CanhGiua(156,MaMayBay[0].length());
								cout << MaMayBay[0];
								HienConTro();
							}
							s = getch();
							if (s == -32 || s == 0)
							{
								kytu1 = 0;
								s = getch();
							}
							else
							{
								kytu1 = 1;
							}
						}
						gotoxy(171,24);
						cout << "   ";
						gotoxy(wherex(),wherey()-1);
						ClearKhungPopUp2();
						if (s == 27)
						{
							x = 27;
							kt = 1;
						}
						break;
					}
				case 10: // LUU
					{
						AnConTro();
						gotoxy(147,30);
						ChangeColor(240);
						cout << "  LUU  ";
						ChangeColor(15);
						char s = getch();
						bool kytu1;
						if (s == -32 || s == 0)
						{
							kytu1 = 0;
							s = getch();
						}
						else
						{
							kytu = 1;
						}
						if (s == 13) // Enter
						{
							luu = 1; // Xac nhan luu
							kt = 1;
						}
						else
						{
							if (s == 75 && !kytu1) // Left
							{
								gotoxy(147,30);
								ChangeColor(15);
								cout << "  LUU  ";
								x = 75;
								kytu = 0;
								kt = 1;
								
							}
							if (s == 27)
							{
								x = 27;
								kt = 1;
							}
						}
						break;
					}
			}
		//	HienConTro();
			if (!kt)
			{
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
		if (x == 27)
		{
			gotoxy(0,30);
			cout << "Ban co muon THOAT?";
			cout  << endl << "Nhan Y de ";
			ChangeColor(12);
			cout << "THOAT";
			ChangeColor(15);
			cout << ", hoac nhan BAT KY phim nao de ";
			ChangeColor(12);
			cout << "HUY";
			ChangeColor(15);
//			HienConTro();
			char t = getch();
			bool kytu1;
			if (t == -32 || t == 0)
			{
				kytu1 = 0;
				t = getch();
			}
			else
			{
				kytu1 = 1;
			}
			if (kytu1 == 1)
			{
				if (InHoa(t) == 89)
				{
					return NULL;
				}
			}
			gotoxy(0,30);
			cout << "                                             " << endl << "                                                     ";
			x = 65;
			kytu = 0;
		}
	}
	Day Ngay;
	Ngay.dd = dd;
	Ngay.mm = mm;
	Ngay.yy = yy;
	Time Gio1;
	Gio1.hour = gio;
	Gio1.min = phut;
	string temp = "";
	for (int i = 0; i < den.length(); i++)
	{
		if (den[i] != 32)
		{
			temp = temp + den[i];
		}
		else
		{
			temp = temp + '0';
		}
	}
	CacChuyenBay *p = new CacChuyenBay;
	p->chuyenbay.DatMaChuyen(MaChuyenBay);
	p->chuyenbay.DatNgay(Ngay);
	p->chuyenbay.DatGio(Gio1);
	p->chuyenbay.DatDiemDen(temp);
	p->chuyenbay.DatTrangThai(trangthai);
	p->chuyenbay.DatSoHieu(MaMayBay1);
	for (int j = 0; j < b.n; j++) 
	{
		{
			if (p->chuyenbay.LaySoHieu() == b.data[j]->LaySoHieu())
			{
				p->chuyenbay.DatLoai(b.data[j]->LayLoai());
				p->chuyenbay.DatSoCho(b.data[j]->LaySoCho());
				p->chuyenbay.TaoDanhSachVe();
			}
		}
	}
	return p;
}
// ============================== CAP NHAT TRANG THAI CHUYEN BAY===============================
void CapNhatTrangThaiChuyenBay(ListChuyenBay &a)
{
	CacChuyenBay *p = a.Head;
	for (p = a.Head; p != NULL; p = p->next)
	{
		int hh = p->chuyenbay.LayGio().hour;
		int min = p->chuyenbay.LayGio().min;
		int dd = p->chuyenbay.LayNgay().dd;
		int mm = p->chuyenbay.LayNgay().mm;
		int yy = p->chuyenbay.LayNgay().yy;
		if (!KiemTraThoiGian(hh,min,dd,mm,yy))
		{
			if (p->chuyenbay.LayTrangThai() != 0)
			{
				p->chuyenbay.DatTrangThai(3);
			}
		}
		else
		{
			if (p->chuyenbay.LayTrangThai() != 0)
			{
				int i;
				for ( i = 0; i < p->chuyenbay.LaySoCho(); i++)
				{
					if (p->chuyenbay.LayDanhSachVe()[i].HanhKhach == NULL)
					{
						break;
					}
				}
				if (i == p->chuyenbay.LaySoCho())
				{
					p->chuyenbay.DatTrangThai(2);
				}
				else
				{
					p->chuyenbay.DatTrangThai(1);
				}
			}
		}
	}
}
// ============================== IN DANH SACH CHUYEN BAY ====================================
void InDanhSachChuyenBay (ListChuyenBay a, int trang)
{
	AnConTro();
	gotoxy(0,0);
	ChangeColor(15);
	int i = 0;
	KhungChuyenBay();
	int maxtrang;
	if (a.SoLuong % 10 == 0)
	{
		maxtrang = a.SoLuong/10;
	}
	else
	{
		maxtrang = a.SoLuong/10 + 1;
	}
//	CapNhatTrangThaiChuyenBay(a);
	CacChuyenBay *p = a.Head;
//	cout << p->chuyenbay.LayMaChuyen();
	if (trang == maxtrang) // Nhieu hon 10 chuyen bay
	{
		while (p != NULL)
		{
			if (i >= (maxtrang - 1)*10  && i < a.SoLuong)
			{
				int DoDaiThoiGian = DoDaiNgay(p->chuyenbay.LayNgay()) + DoDaiGio(p->chuyenbay.LayGio()) + 1;
				gotoxy(0,2*(i%10 + 1) + 1);
				CanhGiua(10,p->chuyenbay.LayMaChuyen().length()); 
				cout << p->chuyenbay.LayMaChuyen();
				CanhGiua(30,DoDaiThoiGian); 
				InGio(p->chuyenbay.LayGio());
				cout << " ";
				InNgay(p->chuyenbay.LayNgay());
				CanhGiua(50,5); 
				cout << "TPHCM";
				CanhGiua(70,p->chuyenbay.LayDiemDen().length()); 
				for (int i = 0; i < p->chuyenbay.LayDiemDen().length(); i++)
				{
					if (p->chuyenbay.LayDiemDen()[i] == 48) 
					{
						cout << " ";
					}
					else
					{
						cout << p->chuyenbay.LayDiemDen()[i];
					}
				}
				//========= TRANG THAI ================
				switch (p->chuyenbay.LayTrangThai())
				{
					case 0:
						{
							CanhGiua(90,9);
							cout << "Huy Chuyen";
							break;
						}
					case 1:
						{
							CanhGiua(90,6);
							cout << "Con Ve";
							break;
						}
					case 2:
						{
							CanhGiua(90,6);
							cout << "Het Ve";
							break;
						}
					case 3:
						{
							CanhGiua(90,8);
							cout << "Hoan Tat";
							break;
						}
				}
			}
			// ==================== MA MAY BAY ============================
			CanhGiua(110,p->chuyenbay.LaySoHieu().length());
			cout << p->chuyenbay.LaySoHieu();
			i++;
			p = p->next;
		}
	}
	else
	{
		while (p != NULL)
		{
			if (i >= (trang - 1 )*10 && i <= trang*10 - 1)
			{
				int DoDaiThoiGian = DoDaiNgay(p->chuyenbay.LayNgay()) + DoDaiGio(p->chuyenbay.LayGio()) + 1;
				gotoxy(0,2*(i%10 + 1) + 1);
				CanhGiua(10,p->chuyenbay.LayMaChuyen().length()); // In Ma Chuyen
				cout << p->chuyenbay.LayMaChuyen();
				CanhGiua(30,DoDaiThoiGian); // In Gio Xuat Phat
				InGio(p->chuyenbay.LayGio());
				cout << " ";
				InNgay(p->chuyenbay.LayNgay());
				CanhGiua(50,5); // In Dia Diem xuat phat
				cout << "TPHCM";
				CanhGiua(70,p->chuyenbay.LayDiemDen().length()); // In Dia Diem den
				for (int i = 0; i < p->chuyenbay.LayDiemDen().length(); i++)
				{
					if (p->chuyenbay.LayDiemDen()[i] == 48) // so '0'
					{
						cout << " ";
					}
					else
					{
						cout << p->chuyenbay.LayDiemDen()[i];
					}
				}
				//========= TRANG THAI ================
				switch (p->chuyenbay.LayTrangThai())
				{
					case 0:
						{
							CanhGiua(90,9);
							cout << "Huy Chuyen";
							break;
						}
					case 1:
						{
							CanhGiua(90,6);
							cout << "Con Ve";
							break;
						}
					case 2:
						{
							CanhGiua(90,6);
							cout << "Het Ve";
							break;
						}
					case 3:
						{
							CanhGiua(90,8);
							cout << "Hoan Tat";
							break;
						}
				}
			}
			CanhGiua(110,p->chuyenbay.LaySoHieu().length());
			cout << p->chuyenbay.LaySoHieu();
			i++;
			p = p->next;
		}
	}
	gotoxy(56,25);
	cout << "---" << trang << "/" << maxtrang << "---";
}
// ========================= THEM VAO DANH SACH CHUYEN BAY ==========================
int ThemChuyenBay (ListChuyenBay &a, ListMayBay &b)
{
	// ======== IN CAC CHUYEN BAY TRUOC DO========
	if (a.SoLuong%10 != 0)
	{
		InDanhSachChuyenBay(a,a.SoLuong/10 + 1);
		AnConTro();
//		gotoxy(0,2*(a.SoLuong%10 + 1) + 1); // Di chuyen den dung line
	}
	else
	{
		InDanhSachChuyenBay(a,a.SoLuong/10);
		AnConTro();
	}
	CacChuyenBay *p = NhapDuLieuChuyenBay(a,b);
	if (p == NULL)
	{
		return 0;
	}
	if (a.Head == NULL)
	{
		a.Head = p;
		a.Tail = p;
	}
	else
	{
		a.Tail->next = p;
		p->next = NULL;
		a.Tail = p;
	}
	a.SoLuong++;
	return 1;
}
// =========================== CHINH SUA CHUYEN BAY =======================================
int ChinhSuaChuyenBay(ListChuyenBay &a, ListMayBay &b)
{
	// ===== SAO CHEP DU LIEU =========
	ListChuyenBay Phu;
	Phu.SoLuong = a.SoLuong;
	for (CacChuyenBay *p = a.Head; p != NULL; p = p->next)
	{
		CacChuyenBay *q = NewChuyenBay();
		q->chuyenbay.DatSoHieu(p->chuyenbay.LaySoHieu());
		q->chuyenbay.DatNgay(p->chuyenbay.LayNgay());
		q->chuyenbay.DatGio(p->chuyenbay.LayGio());
		q->chuyenbay.DatDiemDen(p->chuyenbay.LayDiemDen());
		q->chuyenbay.DatMaChuyen(p->chuyenbay.LayMaChuyen());
		q->chuyenbay.DatTrangThai(p->chuyenbay.LayTrangThai());
		for (int i = 0; i < b.n; i++) // Sao Loai, SoCho
		{
			if (b.data[i]->LaySoHieu() == q->chuyenbay.LaySoHieu())
			{
				q->chuyenbay.DatLoai(b.data[i]->LayLoai());
				q->chuyenbay.DatSoCho(b.data[i]->LaySoCho());
			}
		}
		q->chuyenbay.TaoDanhSachVe();
		for (int i = 0; i < q->chuyenbay.LaySoCho(); i++ )
		{
			q->chuyenbay.LayDanhSachVe()[i].HanhKhach = p->chuyenbay.LayDanhSachVe()[i].HanhKhach; // clgt? @@
		}
		if (Phu.Head == NULL)
		{
			
			Phu.Head = q;
			Phu.Tail = q;
		}
		else
		{
			Phu.Tail->next = q;
			q->next = NULL;
			Phu.Tail = q;
		}
	}
	// Xu ly
	int line1 = 1;
	int currentpage = 1;
	char docngoai = 186;
	char doctrong = 179;
	if (line1%10 != 0)
	{
		InDanhSachChuyenBay(Phu,line1/10+1);
		gotoxy(0,2*(line1%10)+ 1);
	}
	else
	{
		InDanhSachChuyenBay(Phu,line1);
		gotoxy(0,2*10+1);
	}
	ChangeColor(240);
	for (int i = 1; i <= 120; i++) // highlight
	{
		if (i == 1 || i == 120)
		{
			cout << docngoai;
		}
		else
		{
			if (i%20 == 0)
			{
				cout << doctrong;
			}
			else
			{
				cout << " ";
			}
		}
	}
	gotoxy(wherex()+10,0);
	ChangeColor(15);
	CuaSoChuyenBay();
	gotoxy(135,29);
	cout << "                                     ";
	gotoxy(135,30);
	cout << "                            ";
	gotoxy(135,31);
	cout << "                               ";
	ChangeColor(240);
	CacChuyenBay *p = Phu.Head;
	for (int i = 1; i < line1; i++)
	{
		if (p == NULL) break;
		p = p->next;
	}
	int DoDaiThoiGian = DoDaiNgay(p->chuyenbay.LayNgay()) + DoDaiGio(p->chuyenbay.LayGio()) + 1;
	gotoxy(0,2*((line1-1)%10 + 1) + 1);
	CanhGiua(10,p->chuyenbay.LayMaChuyen().length()); // In Ma Chuyen
	cout << p->chuyenbay.LayMaChuyen();
	CanhGiua(30,DoDaiThoiGian); // In Gio Xuat Phat
	InGio(p->chuyenbay.LayGio());
	cout << " ";
	InNgay(p->chuyenbay.LayNgay());
	CanhGiua(50,5); // In Dia Diem xuat phat
	cout << "TPHCM";
	CanhGiua(70,p->chuyenbay.LayDiemDen().length()); // In Dia Diem den
	for (int i = 0; i < p->chuyenbay.LayDiemDen().length(); i++)
	{
		if (p->chuyenbay.LayDiemDen()[i] == 48) // so '0'
		{
			cout << " ";
		}
		else
		{
			cout << p->chuyenbay.LayDiemDen()[i];
		}
	}
	//========= TRANG THAI ================
	switch (p->chuyenbay.LayTrangThai())
	{
		case 0:
		{
			CanhGiua(90,9);
			cout << "Huy Chuyen";
			break;
		}	
		case 1:
		{
			CanhGiua(90,6);
			cout << "Con Ve";
			break;
		}
		case 2:
		{
			CanhGiua(90,6);
			cout << "Het Ve";
			break;
		}
		case 3:
		{
			CanhGiua(90,8);
			cout << "Hoan Tat";
			break;
		}
	}
	CanhGiua(110,p->chuyenbay.LaySoHieu().length());
	cout << p->chuyenbay.LaySoHieu();
	// In vo cua so
	ChangeColor(15);
	AnConTro();
	gotoxy(149,2); // Ma Chuyen Bay
	cout << "                  ";
	CanhGiua(158,p->chuyenbay.LayMaChuyen().length());
	cout << p->chuyenbay.LayMaChuyen();
	gotoxy(140,8); // Ngay
	if (p->chuyenbay.LayNgay().dd <= 9)
	{
		cout << "0" << p->chuyenbay.LayNgay().dd;
	}
	else
	{
		cout << p->chuyenbay.LayNgay().dd;
	}
	gotoxy(149,8); // Thang
	if (p->chuyenbay.LayNgay().mm <= 9)
	{
		cout << "0" << p->chuyenbay.LayNgay().mm;
	}
	else
	{
		cout << p->chuyenbay.LayNgay().mm;
	}
	gotoxy(0,8);
	CanhGiua(160,4); // Nam
	cout << p->chuyenbay.LayNgay().yy;
	gotoxy(145,12); // Gio
	if (p->chuyenbay.LayGio().hour <= 9)
	{
		cout << "0" << p->chuyenbay.LayGio().hour;
	}
	else
	{
		cout << p->chuyenbay.LayGio().hour;
	}
	gotoxy(154,12); // Phut
	if (p->chuyenbay.LayGio().min <= 9)
	{
		cout << "0" << p->chuyenbay.LayGio().min;
	}
	else
	{
		cout << p->chuyenbay.LayGio().min;
	}
	gotoxy(142,16); // Den
	cout << "                  ";
	CanhGiua(151,p->chuyenbay.LayDiemDen().length());
	for (int i = 0; i < p->chuyenbay.LayDiemDen().length(); i++)
	{
		if (p->chuyenbay.LayDiemDen()[i] != 48)
		{
			cout << p->chuyenbay.LayDiemDen()[i];
		}
		else
		{
			cout << " ";
		}
	}
	gotoxy(150,20); // Trang thai
	cout << "           ";
	switch(p->chuyenbay.LayTrangThai())
	{
		case 0:
			{
				CanhGiua(155,10);
				cout << "Huy Chuyen";
				break;
			}
		case 1:
			{
				CanhGiua(155,6);
				cout << "Con Ve";
				break;
			}
		case 2:
			{
				CanhGiua(155,6);
				cout << "Het ve";
				break;
			}
		case 3:
			{
				CanhGiua(155,8);
				cout << "Hoan tat";
				break;
			}
	}
	gotoxy(147,24); // Ma May Bay
	cout << "                  ";
	CanhGiua(156,p->chuyenbay.LaySoHieu().length());
	cout << p->chuyenbay.LaySoHieu();
	gotoxy(0,30);
	char t = getch();
	bool kytu2;
	if (t == -32 || t == 0)
	{
		kytu2 = 0;
		t = getch();
	}
	else
	{
		kytu2 = 1;
	}
	bool kt1 = 0;
	CacChuyenBay *q = Phu.Head;
	while (t != 27) // Esc
	{
		kt1 = 0;
		if (t == 72 && !kytu2) // Up
		{
			if (line1 > 1)
			{
				if (currentpage == ((line1-1-1)/10 + 1))
				{
					if (line1%10 == 0)
					{
						gotoxy(0,2*10+1);
						ChangeColor(15);
					}
					else
					{
						gotoxy(0,2*line1+1);
						ChangeColor(15);
					}
					// ===== UNHIGHLIGHT=================
					for (int i = 1; i <= 120; i++)
					{
						if (i == 1 || i == 120)
						{
							cout << docngoai;
						}
						else
						{
							if (i%20 == 0)
							{
								cout << doctrong;
							}
							else
							{
								cout << " ";
							}
						}
					}
					gotoxy(wherex()+10,0);

					q = Phu.Head;
					for (int i = 1; i < line1; i++)
					{
						if (q == NULL) break;
						q = q->next;
					}
					int DoDaiThoiGian1 = DoDaiNgay(q->chuyenbay.LayNgay()) + DoDaiGio(q->chuyenbay.LayGio()) + 1;
					gotoxy(0,2*((line1-1)%10 + 1) + 1);
					CanhGiua(10,q->chuyenbay.LayMaChuyen().length()); // In Ma Chuyen
					cout << q->chuyenbay.LayMaChuyen();
					CanhGiua(30,DoDaiThoiGian); // In Gio Xuat Phat
					InGio(q->chuyenbay.LayGio());
					cout << " ";
					InNgay(q->chuyenbay.LayNgay());
					CanhGiua(50,5); // In Dia Diem xuat phat
					cout << "TPHCM";
					CanhGiua(70,q->chuyenbay.LayDiemDen().length()); // In Dia Diem den
					for (int i = 0; i < q->chuyenbay.LayDiemDen().length(); i++)
					{
						if (q->chuyenbay.LayDiemDen()[i] == '0') // so '0'
						{
							cout << " ";
						}
						else
						{
							cout << q->chuyenbay.LayDiemDen()[i];
						}
					}
					//========= TRANG THAI ================
					switch (q->chuyenbay.LayTrangThai())
					{
						case 0:
						{
							CanhGiua(90,9);
							cout << "Huy Chuyen";
							break;
						}	
						case 1:
						{
							CanhGiua(90,6);
							cout << "Con Ve";
							break;
						}
						case 2:
						{
							CanhGiua(90,6);
							cout << "Het Ve";
							break;
						}
						case 3:
						{
							CanhGiua(90,8);
							cout << "Hoan Tat";
							break;
						}
					}
					CanhGiua(110,q->chuyenbay.LaySoHieu().length());
					cout << q->chuyenbay.LaySoHieu();
					// ========== XU LY TOAN HOC ========
					line1--;
					// ========== HIGHLIGHT============
					if (line1%10 == 0)
					{
						gotoxy(0,2*10+1);
						ChangeColor(240);
					}
					else
					{
						gotoxy(0,2*line1+1);
						ChangeColor(240);
					}
					for (int i = 1; i <= 120; i++) // highlight
					{
						if (i == 1 || i == 120)
						{
							cout << docngoai;
						}
						else
						{
							if (i%20 == 0)
							{
								cout << doctrong;
							}
							else
							{
								cout << " ";
							}
						}
					}
					gotoxy(wherex()+10,0);
	//				ChangeColor(15);
	//				CuaSoChuyenBay();
	//				ChangeColor(240);
					q = Phu.Head;
					for (int i = 1; i < line1; i++)
					{
						if (q == NULL) break;
						q = q->next;
					}
					DoDaiThoiGian1 = DoDaiNgay(q->chuyenbay.LayNgay()) + DoDaiGio(q->chuyenbay.LayGio()) + 1;
					gotoxy(0,2*((line1-1)%10 + 1) + 1);
					CanhGiua(10,q->chuyenbay.LayMaChuyen().length()); // In Ma Chuyen
					cout << q->chuyenbay.LayMaChuyen();
					CanhGiua(30,DoDaiThoiGian1); // In Gio Xuat Phat
					InGio(q->chuyenbay.LayGio());
					cout << " ";
					InNgay(q->chuyenbay.LayNgay());
					CanhGiua(50,5); // In Dia Diem xuat phat
					cout << "TPHCM";
					CanhGiua(70,q->chuyenbay.LayDiemDen().length()); // In Dia Diem den
					for (int i = 0; i < q->chuyenbay.LayDiemDen().length(); i++)
					{
						if (q->chuyenbay.LayDiemDen()[i] == 48) // so '0'
						{
							cout << " ";
						}
						else
						{
							cout << q->chuyenbay.LayDiemDen()[i];
						}
					}
					//========= TRANG THAI ================
					switch (q->chuyenbay.LayTrangThai())
					{
						case 0:
						{
							CanhGiua(90,9);
							cout << "Huy Chuyen";
							break;
						}	
						case 1:
						{
							CanhGiua(90,6);
							cout << "Con Ve";
							break;
						}
						case 2:
						{
							CanhGiua(90,6);
							cout << "Het Ve";
							break;
						}
						case 3:
						{
							CanhGiua(90,8);
							cout << "Hoan Tat";
							break;
						}
					}
					CanhGiua(110,q->chuyenbay.LaySoHieu().length());
					cout << q->chuyenbay.LaySoHieu();
					
				}
				else
				{
					line1--;
					if (line1%10 != 0)
					{
						InDanhSachChuyenBay(Phu,line1/10+1);
						gotoxy(0,2*(line1%10)+ 1);
					}
					else
					{
						InDanhSachChuyenBay(Phu,line1);
						gotoxy(0,2*10+1);
					}
					ChangeColor(240);
					for (int i = 1; i <= 120; i++) // highlight
					{
						if (i == 1 || i == 120)
						{
							cout << docngoai;
						}
						else
						{
							if (i%20 == 0)
							{
								cout << doctrong;
							}
							else
							{
								cout << " ";
							}
						}
					}
					gotoxy(wherex()+10,0);
					ChangeColor(15);
				//	CuaSoChuyenBay();
					ChangeColor(240);
					q = Phu.Head;
					for (int i = 1; i < line1; i++)
					{
						if (q == NULL) break;
						p = q->next;
					}
					DoDaiThoiGian = DoDaiNgay(q->chuyenbay.LayNgay()) + DoDaiGio(q->chuyenbay.LayGio()) + 1;
					gotoxy(0,2*((line1-1)%10 + 1) + 1);
					CanhGiua(10,q->chuyenbay.LayMaChuyen().length()); // In Ma Chuyen
					cout << q->chuyenbay.LayMaChuyen();
					CanhGiua(30,DoDaiThoiGian); // In Gio Xuat Phat
					InGio(q->chuyenbay.LayGio());
					cout << " ";
					InNgay(q->chuyenbay.LayNgay());
					CanhGiua(50,5); // In Dia Diem xuat phat
					cout << "TPHCM";
					CanhGiua(70,q->chuyenbay.LayDiemDen().length()); // In Dia Diem den
					for (int i = 0; i < q->chuyenbay.LayDiemDen().length(); i++)
					{
						if (q->chuyenbay.LayDiemDen()[i] == 48) // so '0'
						{
							cout << " ";
						}
						else
						{
							cout << q->chuyenbay.LayDiemDen()[i];
						}
					}
					//========= TRANG THAI ================
					switch (p->chuyenbay.LayTrangThai())
					{
						case 0:
						{
							CanhGiua(90,9);
							cout << "Huy Chuyen";
							break;
						}	
						case 1:
						{
							CanhGiua(90,6);
							cout << "Con Ve";
							break;
						}
						case 2:
						{
							CanhGiua(90,6);
							cout << "Het Ve";
							break;
						}
						case 3:
						{
							CanhGiua(90,8);
							cout << "Hoan Tat";
							break;
						}
					}
					CanhGiua(110,q->chuyenbay.LaySoHieu().length());
					cout << q->chuyenbay.LaySoHieu();
				}
			}
		}
		if (t == 80 && !kytu2) // Down
		{
			if (line1 < Phu.SoLuong)
			{
				
				if (currentpage == ((line1+1-1)/10 + 1))
				{
					if (line1%10 == 0)
					{
						gotoxy(0,2*10+1);
						ChangeColor(15);
					}
					else
					{
						gotoxy(0,2*line1+1);
						ChangeColor(15);
					}
					// ===== UNHIGHLIGHT=================
					for (int i = 1; i <= 120; i++)
					{
						if (i == 1 || i == 120)
						{
							cout << docngoai;
						}
						else
						{
							if (i%20 == 0)
							{
								cout << doctrong;
							}
							else
							{
								cout << " ";
							}
						}
					}
					gotoxy(wherex()+10,0);
	//				ChangeColor(15);
	//				CuaSoChuyenBay();
	//				ChangeColor(240);
					q = Phu.Head;
					for (int i = 1; i < line1; i++)
					{
						if (q == NULL) break;
						q = q->next;
					}
					DoDaiThoiGian = DoDaiNgay(q->chuyenbay.LayNgay()) + DoDaiGio(q->chuyenbay.LayGio()) + 1;
					gotoxy(0,2*((line1-1)%10 + 1) + 1);
					CanhGiua(10,q->chuyenbay.LayMaChuyen().length()); // In Ma Chuyen
					cout << q->chuyenbay.LayMaChuyen();
					CanhGiua(30,DoDaiThoiGian); // In Gio Xuat Phat
					InGio(q->chuyenbay.LayGio());
					cout << " ";
					InNgay(q->chuyenbay.LayNgay());
					CanhGiua(50,5); // In Dia Diem xuat phat
					cout << "TPHCM";
					CanhGiua(70,q->chuyenbay.LayDiemDen().length()); // In Dia Diem den
					for (int i = 0; i < q->chuyenbay.LayDiemDen().length(); i++)
					{
						if (q->chuyenbay.LayDiemDen()[i] == 48) // so '0'
						{
							cout << " ";
						}
						else
						{
							cout << q->chuyenbay.LayDiemDen()[i];
						}
					}
					//========= TRANG THAI ================
					switch (q->chuyenbay.LayTrangThai())
					{
						case 0:
						{
							CanhGiua(90,9);
							cout << "Huy Chuyen";
							break;
						}	
						case 1:
						{
							CanhGiua(90,6);
							cout << "Con Ve";
							break;
						}
						case 2:
						{
							CanhGiua(90,6);
							cout << "Het Ve";
							break;
						}
						case 3:
						{
							CanhGiua(90,8);
							cout << "Hoan Tat";
							break;
						}
					}
					CanhGiua(110,q->chuyenbay.LaySoHieu().length());
					cout << q->chuyenbay.LaySoHieu();
					// ========== XU LY TOAN HOC ========
					line1++;
					if (line1%10 == 0)
					{
						gotoxy(0,2*10+1);
						ChangeColor(240);
					}
					else
					{
						gotoxy(0,2*line1+1);
						ChangeColor(240);
					}
					// ========== HIGHLIGHT============
					for (int i = 1; i <= 120; i++) // highlight
					{
						if (i == 1 || i == 120)
						{
							cout << docngoai;
						}
						else
						{
							if (i%20 == 0)
							{
								cout << doctrong;
							}
							else
							{
								cout << " ";
							}
						}
					}
					gotoxy(wherex()+10,0);
	//				ChangeColor(15);
	//				CuaSoChuyenBay();
	//				ChangeColor(240);
					q = Phu.Head;
					for (int i = 1; i < line1; i++)
					{
						if (q == NULL) break;
						q = q->next;
					}
					int DoDaiThoiGian1 = DoDaiNgay(q->chuyenbay.LayNgay()) + DoDaiGio(q->chuyenbay.LayGio()) + 1;
					gotoxy(0,2*((line1-1)%10 + 1) + 1);
					CanhGiua(10,q->chuyenbay.LayMaChuyen().length()); // In Ma Chuyen
					cout << q->chuyenbay.LayMaChuyen();
					CanhGiua(30,DoDaiThoiGian); // In Gio Xuat Phat
					InGio(q->chuyenbay.LayGio());
					cout << " ";
					InNgay(q->chuyenbay.LayNgay());
					CanhGiua(50,5); // In Dia Diem xuat phat
					cout << "TPHCM";
					CanhGiua(70,q->chuyenbay.LayDiemDen().length()); // In Dia Diem den
					for (int i = 0; i < q->chuyenbay.LayDiemDen().length(); i++)
					{
						if (q->chuyenbay.LayDiemDen()[i] == 48) // so '0'
						{
							cout << " ";
						}
						else
						{
							cout << q->chuyenbay.LayDiemDen()[i];
						}
					}
					//========= TRANG THAI ================
					switch (q->chuyenbay.LayTrangThai())
					{
						case 0:
						{
							CanhGiua(90,9);
							cout << "Huy Chuyen";
							break;
						}	
						case 1:
						{
							CanhGiua(90,6);
							cout << "Con Ve";
							break;
						}
						case 2:
						{
							CanhGiua(90,6);
							cout << "Het Ve";
							break;
						}
						case 3:
						{
							CanhGiua(90,8);
							cout << "Hoan Tat";
							break;
						}
					}
					CanhGiua(110,q->chuyenbay.LaySoHieu().length());
					cout << q->chuyenbay.LaySoHieu();
					
				}
				else
				{
					line1++;
					if (line1%10 != 0)
					{
						InDanhSachChuyenBay(Phu,line1/10+1);
						gotoxy(0,2*(line1%10)+ 1);
					}
					else
					{
						InDanhSachChuyenBay(Phu,line1);
						gotoxy(0,2*10+1);
					}
					ChangeColor(240);
					for (int i = 1; i <= 120; i++) // highlight
					{
						if (i == 1 || i == 120)
						{
							cout << docngoai;
						}
						else
						{
							if (i%20 == 0)
							{
								cout << doctrong;
							}
							else
							{
								cout << " ";
							}
						}
					}
					gotoxy(wherex()+10,0);
					ChangeColor(15);
				//	CuaSoChuyenBay();
					ChangeColor(240);
					q = Phu.Head;
					for (int i = 1; i < line1; i++)
					{
						if (q == NULL) break;
						q = q->next;
					}
					int DoDaiThoiGian1 = DoDaiNgay(q->chuyenbay.LayNgay()) + DoDaiGio(q->chuyenbay.LayGio()) + 1;
					gotoxy(0,2*((line1-1)%10 + 1) + 1);
					CanhGiua(10,q->chuyenbay.LayMaChuyen().length()); // In Ma Chuyen
					cout << q->chuyenbay.LayMaChuyen();
					CanhGiua(30,DoDaiThoiGian); // In Gio Xuat Phat
					InGio(q->chuyenbay.LayGio());
					cout << " ";
					InNgay(q->chuyenbay.LayNgay());
					CanhGiua(50,5); // In Dia Diem xuat phat
					cout << "TPHCM";
					CanhGiua(70,q->chuyenbay.LayDiemDen().length()); // In Dia Diem den
					for (int i = 0; i < q->chuyenbay.LayDiemDen().length(); i++)
					{
						if (q->chuyenbay.LayDiemDen()[i] == 48) // so '0'
						{
							cout << " ";
						}
						else
						{
							cout << q->chuyenbay.LayDiemDen()[i];
						}
					}
					//========= TRANG THAI ================
					switch (q->chuyenbay.LayTrangThai())
					{
						case 0:
						{
							CanhGiua(90,9);
							cout << "Huy Chuyen";
							break;
						}	
						case 1:
						{
							CanhGiua(90,6);
							cout << "Con Ve";
							break;
						}
						case 2:
						{
							CanhGiua(90,6);
							cout << "Het Ve";
							break;
						}
						case 3:
						{
							CanhGiua(90,8);
							cout << "Hoan Tat";
							break;
						}
					}
					CanhGiua(110,q->chuyenbay.LaySoHieu().length());
					cout << q->chuyenbay.LaySoHieu();
				}
			}
		}
		// In vo cua so
		ChangeColor(15);
		AnConTro();
		gotoxy(149,2); // Ma Chuyen Bay
		cout << "                  ";
		CanhGiua(158,q->chuyenbay.LayMaChuyen().length());
		cout << q->chuyenbay.LayMaChuyen();
		gotoxy(140,8); // Ngay
		if (q->chuyenbay.LayNgay().dd <= 9)
		{
			cout << "0" << q->chuyenbay.LayNgay().dd;
		}
		else
		{
			cout << q->chuyenbay.LayNgay().dd;
		}
		gotoxy(149,8); // Thang
		if (q->chuyenbay.LayNgay().mm <= 9)
		{
			cout << "0" << q->chuyenbay.LayNgay().mm;
		}
		else
		{
			cout << q->chuyenbay.LayNgay().mm;
		}
		gotoxy(0,8);
		CanhGiua(160,4); // Nam
		cout << q->chuyenbay.LayNgay().yy;
		gotoxy(145,12); // Gio
		if (q->chuyenbay.LayGio().hour <= 9)
		{
			cout << "0" << q->chuyenbay.LayGio().hour;
		}
		else
		{
			cout << q->chuyenbay.LayGio().hour;
		}
		gotoxy(154,12); // Phut
		if (q->chuyenbay.LayGio().min <= 9)
		{
			cout << "0" << q->chuyenbay.LayGio().min;
		}
		else
		{
			cout << q->chuyenbay.LayGio().min;
		}
		gotoxy(142,16); // Den
		cout << "                  ";
		CanhGiua(151,q->chuyenbay.LayDiemDen().length());
		for (int i = 0; i < q->chuyenbay.LayDiemDen().length(); i++)
		{
			if (q->chuyenbay.LayDiemDen()[i] != 48)
			{
				cout << q->chuyenbay.LayDiemDen()[i];
			}
			else
			{
				cout << " ";
			}
		}
		gotoxy(150,20); // Trang thai
		cout << "           ";
		switch(q->chuyenbay.LayTrangThai())
		{
			case 0:
				{
					CanhGiua(155,10);
					cout << "Huy Chuyen";
					break;
				}
			case 1:
				{
					CanhGiua(155,6);
					cout << "Con Ve";
					break;
				}
			case 2:
				{
					CanhGiua(155,6);
					cout << "Het ve";
					break;
				}
			case 3:
				{
					CanhGiua(155,8);
					cout << "Hoan tat";
					break;
				}
		}
		gotoxy(147,24); // Ma May Bay
		cout << "                  ";
		CanhGiua(156,q->chuyenbay.LaySoHieu().length());
		cout << q->chuyenbay.LaySoHieu();
		if (t == 27)
		{
			gotoxy(0,30);
			cout << "Ban co muon THOAT?";
			cout  << endl << "Nhan Y de ";
			ChangeColor(12);
			cout << "THOAT";
			ChangeColor(15);
			cout << ", hoac nhan BAT KY phim nao de ";
			ChangeColor(12);
			cout << "HUY";
			ChangeColor(15);
//			HienConTro();
			char s = getch();
			bool kytu1;
			if (s == -32 || s == 0)
			{
				kytu1 = 0;
				s = getch();
			}
			else
			{
				kytu1 = 1;
			}
			if (kytu1 == 1)
			{
				if (InHoa(s) == 89)
				{
					return 0;
				}
			}
	//		gotoxy(0,30);
	//		cout << "                                             " << endl << "                                                     ";
		//	x = 65;
		//	kytu = 0;
		}
		if (t == 13) // Enter
		{
			string MaChuyenBay = q->chuyenbay.LayMaChuyen();
			int dd = q->chuyenbay.LayNgay().dd;
			int mm = q->chuyenbay.LayNgay().mm;
			int yy = q->chuyenbay.LayNgay().yy;
			int gio = q->chuyenbay.LayGio().hour;
			int phut = q->chuyenbay.LayGio().min;
			string den;
			for (int i = 0 ; i <= q->chuyenbay.LayDiemDen().length(); i++)
			{
				if (q->chuyenbay.LayDiemDen()[i] == '0')
				{
					den = den + ' ';
				}
				else
				{
					den = den + q->chuyenbay.LayDiemDen()[i];
				}
			}
			den.erase(den.length()-1,den.length());
		//	gotoxy(0,30);
		//	cout << den << "jhjj";
			int trangthai = q->chuyenbay.LayTrangThai();
			string MaMayBay1 = q->chuyenbay.LaySoHieu();
			int SoLuongMayBay = -1;
			int dodaichuoi = MaChuyenBay.length();
		//	gotoxy (130,0);
		//	CuaSoChuyenBay();
			int line = 1;
			gotoxy(158,2); // Ma chuyen bay
			CanhGiua(158,q->chuyenbay.LayMaChuyen().length());
			gotoxy(wherex()+q->chuyenbay.LayMaChuyen().length(),wherey());
			HienConTro();
			char x = getch();
			bool kytu;
			if (x == -32 || x == 0)
			{
				kytu = 0;
				x = getch();
			}
			else
			{
				kytu = 1;
			}
			bool kt = 0; // Kiem tra ngat
			bool luu = 0;
			int maxtrangthai = 3;
			while (1 && !luu)
			{
				luu = 0;
				while (x != 27 && !luu ) // Khong phai la Esc
				{
					kt = 0;
					if (x == 75 && !kytu) // left
					{
						if (line > 1)
						{
							line--;
						}
					}
					if (x == 77 && !kytu) // right
					{
						if (line == 1)
						{
							CacChuyenBay *h;
							for (h = Phu.Head; h != NULL; h = h->next)
							{
								if (h->chuyenbay.LayMaChuyen() == MaChuyenBay && h != q)
								{
									AnConTro();
									gotoxy(158-9,2);
									cout << "Trung Ma chuyen bay";
									Sleep(500);
									gotoxy(158-9,2);
									cout << "                   ";
									gotoxy(158-3,2);
									cout << "Thu lai";
									Sleep(500);
									gotoxy(158-3,2);
									cout << "       ";
									CanhGiua(158,MaChuyenBay.length());
									HienConTro();
									break;
								}
							//	gotoxy(0,30);
							//	cout << q << " " << h;
							//	system("pause");
							}
							if (h == NULL)
							{
								if (dodaichuoi == 0)
								{
									AnConTro();
									gotoxy(158-9,2);
									cout << "Khong the bo trong";
									Sleep(500);
									gotoxy(158-9,2);
									cout << "                  ";
									gotoxy(158,2);
									HienConTro();
								}
								else
								{
									if (line < 9)
									{
										line++;
									}
								}
							}
						}
						else
						{
							if (line < 9)
							{
								line++;
							}
						}
					}
					switch (line)
					{
						case 1: // Ma Chuyen bay
							{
								AnConTro();
								gotoxy(0,2);
								CanhGiua(158, MaChuyenBay.length());
								cout << MaChuyenBay;
								HienConTro();
								if (x == 8) // Backspace
								{
									if (dodaichuoi == 0)
									{
										AnConTro();
										gotoxy(158-6,2);
										cout << "Khong the xoa";
										Sleep(500);
										gotoxy(158-6,2);
										cout << "             ";
										gotoxy(158,2);
										HienConTro();
									}
									else
									{
										AnConTro();
										gotoxy(149,2);
										cout << "                  ";
										MaChuyenBay.erase(MaChuyenBay.length()-1,MaChuyenBay.length());
										dodaichuoi--;
										CanhGiua(158,MaChuyenBay.length());
										cout << MaChuyenBay;
										HienConTro();
									}
								}
								if (((x >= 95 && x <= 122) || (x >= 65 && x <= 90) || (x >= 48 && x <= 57)) && kytu) // a -> z, A -> Z, 0 -> 9
								{
									if (dodaichuoi < 15)
									{
										AnConTro();
										gotoxy(149,2);
										cout << "                  ";
										MaChuyenBay = MaChuyenBay + InHoa(x);
										dodaichuoi++;
										CanhGiua(158,MaChuyenBay.length());
										cout << MaChuyenBay;
										HienConTro();
									}
									else
									{
										AnConTro();
										gotoxy(158-9,2);
										cout << "Khong qua 15 ky tu";
										Sleep(500);
										gotoxy(158-9,2);
										cout << "                  ";
										CanhGiua(158,MaChuyenBay.length());
										cout << MaChuyenBay;
										HienConTro();
									}
								}
		
								break;
							}
						case 2: // dd
							{
								AnConTro();
								gotoxy(140,8);
								cout << "  ";
								gotoxy(171, wherey());
								cout << "->";
								gotoxy(wherex() +1, wherey()-1);
								KhungPopUp();
								gotoxy(0,8);
								CanhGiua(178,2);
								cout << "DD";
								//===== MENU NGAY ==========
								int max = DaysOfMounth(mm,yy);
								int *Ngay = new int[max];
								for (int i = 0; i < max; i++) // Khoi tao
								{
									Ngay[i] = i+1;
								}
								// Lay du lieu cu
								if (dd != 0)
								{
									if (dd > DaysOfMounth(mm,yy))
									{
										dd = DaysOfMounth(mm,yy);
									}
									while (Ngay[0] != dd)
									{
										int temp = Ngay[max-1];
										for (int i = max-1; i >= 1; i--)
										{
											Ngay[i] = Ngay[i-1];
										}
										Ngay[0] = temp;
									}
								}
								// HIGH LIGHT
								gotoxy(175,10);
								ChangeColor(240);
								if (Ngay[0] <= 9)
								{
									cout << "  0" << Ngay[0] << "  ";
								}
								else
								{
									cout << "  " << Ngay[0] << "  ";
								}
								ChangeColor(15);
								for (int i = 1; i <= 9; i++) // In ngay
								{
									gotoxy(177,10+i);
									if (Ngay[i] <= 9)
									{
										cout << "0" << Ngay[i];
									}
									else
									{
										cout << Ngay[i];
									}
								}
								gotoxy(140,8);
								if (Ngay[0] <= 9)
								{
									cout << "0" << Ngay[0];
								}
								else
								{
									cout << Ngay[0];
								}
								HienConTro();
								// ============== CHON NGAY ============
								char s = getch();
								bool kytu1;
								if (s == -32 || s == 0)
								{
									kytu1 = 0;
									s = getch();
								}
								else
								{
									kytu1 = 1;
								}
								while (s != 27)
								{
									if(s == 75 && !kytu1)// Left
									{
										x = 75;
										kytu = 0;
										kt = 1;
										dd = Ngay[0];
										break;
									}
									if(s == 77 && !kytu1)// Right
									{
										x = 77;
										kytu = 0;
										kt = 1;
										dd = Ngay[0];
										break;
									}
									if (s == 72 && !kytu1) // Up
									{
										int temp = Ngay[max-1];
										for (int i = max-1; i >= 1; i--)
										{
											Ngay[i] = Ngay[i-1];
										}
										Ngay[0] = temp;
									}
									if (s == 80 && !kytu1) // Down
									{
										int temp = Ngay[0];
										for (int i = 0; i <= max-2; i++)
										{
											Ngay[i] =  Ngay[i+1];
										}
										Ngay[max-1] = temp;
									}
									for (int i = 0; i <= 9; i++) // In Ngay
									{
										gotoxy(175,10+i);
										if (Ngay[i] <= 9)
										{
											cout << "  0" << Ngay[i] << "  "; 
										}
										else
										{
											cout << "  " << Ngay[i] << "  ";
										}
									}
									// Highlight
									ChangeColor(240);
									gotoxy(175,10);
									if (Ngay[0] <= 9 )
									{
										cout << "  0" << Ngay[0] << "  ";
									}
									else
									{
										cout << "  " << Ngay[0] << "  ";
									}
									ChangeColor(15);
									gotoxy(140,8);
									if (Ngay[0] <= 9)
									{
										cout << "0" << Ngay[0];
									}
									else
									{
										cout << Ngay[0];
									}
									s = getch();
									if (s == -32 || s == 0)
									{
										kytu1 = 0;
										s = getch();
									}
									else
									{
										kytu1 = 1;
									}
									HienConTro();
								}
								AnConTro();
								gotoxy(171,8);
								cout << "   ";
								gotoxy(wherex(), wherey()-1);
								ClearKhungPopUp();
								if (s == 27)
								{
									dd = Ngay[0];
									x = 27;
									kt = 1;
								}
								break;
							}
						case 3: // mm
							{
								AnConTro();
								gotoxy(149,8);
								cout << "  ";
								gotoxy(171,wherey());
								cout << "-> ";
								gotoxy(wherex(), wherey()-1);
								KhungPopUp();
								gotoxy(0,8);
								CanhGiua(178,2);
								cout << "MM";
								int Thang[12];
								for (int i = 0; i < 12; i++)
								{
									Thang[i] = i+1;
								}
								// Lay du lieu cu
								if (mm != 0)
								{
									while (Thang[0] != mm)
									{
										int temp = Thang[11];
										for (int i = 11; i >= 1; i-- )
										{
											Thang[i] = Thang[i - 1];
										}
										Thang[0] = temp;
									}
								}
								for (int i = 0; i < 10; i++)
								{
									gotoxy(175,10+i);
									if (Thang[i] <= 9)
									{
										cout << "  0" << Thang[i] << "  ";
									}
									else
									{
										cout << "  " << Thang[i] << "  ";
									}
								}
								// Highlight
								gotoxy(175,10);
								ChangeColor(240);
								gotoxy(175,10);
								if (Thang[0] <= 9)
								{
									cout << "  0" << Thang[0] << "  ";
								}
								else
								{
									cout << "  " << Thang[0] << "  ";
								}
								ChangeColor(15);
								gotoxy(149,8);
								if (Thang[0] <= 9)
								{
									cout << "0" << Thang[0];
								}
								else
								{
									cout << Thang[0];
								}
								HienConTro();
								char s = getch();
								bool kytu1;
								if (s == -32 || s == 0)
								{
									kytu1 = 0;
									s = getch();
								}
								else
								{
									kytu1 = 1;
								}
								while (s != 27) // Khong phai Esc
								{
									AnConTro();
									if (s == 75 && !kytu1) // Left
									{
										mm = Thang[0];
										if (dd > DaysOfMounth(mm,yy))
										{
											dd = DaysOfMounth(mm,yy);
											gotoxy(140,8);
											cout << dd;
										//	HienConTro();
										}
										x = 75; 
										kytu = 0;
										kt = 1;
										break;
									}
									if (s == 77 && !kytu1) // Right
									{
										x = 77;
										kytu = 0;
										kt = 1;
										mm = Thang[0];
										if (dd > DaysOfMounth(mm,yy))
										{
											dd = DaysOfMounth(mm,yy);
											gotoxy(140,8);
											cout << dd;
										//	HienConTro();
										}
										break;
									}
									if (s == 72 && !kytu1) // Up
									{
										int temp = Thang[11];
										for (int i = 11; i >= 1; i-- )
										{
											Thang[i] = Thang[i - 1];
										}
										Thang[0] = temp;
									}
									if (s == 80 && !kytu1) // Down
									{
										int temp = Thang[0];
										for (int i = 0; i < 11; i++)
										{
											Thang[i] = Thang[i + 1];
										}
										Thang[11] = temp;
									}
									for (int i = 0; i <= 9; i++) // In thang
									{
										gotoxy(175,10+i);
										if (Thang[i] <= 9)
										{
											cout << "  0" << Thang[i] << "  ";
										}
										else
										{
											cout << "  " << Thang[i] << "  ";
										}
									}
									// Highlight
									gotoxy(175,10);
									ChangeColor(240);
									if  (Thang[0] <= 9)
									{
										cout << "  0" << Thang[0] << "  ";
									}
									else
									{
										cout << "  " << Thang[0] << "  ";
									}
									ChangeColor(15);
									gotoxy(148,8);
									if (Thang[0] <= 9)
									{
										cout << " 0" << Thang[0];
									}
									else
									{
										cout << " " << Thang[0];
									}
									HienConTro();
									s = getch();
									if (s == -32 || s == 0)
									{
										kytu1 = 0;
										s = getch();
									}
									else
									{
										kytu1 = 1;
									}
								}
								// Ket thuc
								AnConTro();
								gotoxy(171,8);
								cout << "   ";
								gotoxy(wherex(), wherey()-1);
								ClearKhungPopUp();
								if (s == 27)
								{
									mm = Thang[0];
									x = 27;
									kt = 1;
								}
								break;
							}
						case 4: // yy
							{
								AnConTro();
								int so;
								gotoxy(158,8);
								cout << "    ";
								gotoxy(171,wherey());
								cout << "-> ";
								gotoxy(wherex(),wherey()-1);
								KhungPopUp();
								gotoxy(0,8);
								CanhGiua(178,4);
								cout << "YYYY";
								int Nam[4];
								for (int i = 0; i < 4; i++)
								{
									Nam[i] = i + 2022;
									gotoxy(175,i+10);
									cout << " " << Nam[i] << " ";
								}
								// HIGH LIGHT
								if (yy != 0)
								{
									gotoxy(175,10 + (yy-2022));
									ChangeColor(240);
									cout << " " << yy << " ";
									ChangeColor(15);
									gotoxy(158,8);
									cout << yy;
									so = yy - 2022;
									HienConTro();
								}
								else
								{
									gotoxy(175,10);
									ChangeColor(240);
									cout << " " << Nam[0] << " ";
									ChangeColor(15);
									gotoxy(158,8);
									cout << Nam[0];
									so = 0;
									HienConTro();
								}
								char s = getch();
								bool kytu1;
								if (s == -32 || s == 0)
								{
									kytu1 = 0;
									s = getch();
								}
								else
								{
									kytu1 = 1;
								}
								while (s != 27 && s != 13) // Khac Esc or Enter
								{
									AnConTro();
									if (s == 75 && !kytu1) // Left
									{
										// Khong o thao tac nay
										x = 75;
										kytu = 0;
										kt = 1;
										yy = Nam[so];
										if (dd > DaysOfMounth(mm,yy))
										{
											dd = DaysOfMounth(mm,yy);
											gotoxy(140,8);
											cout << dd;
										//	HienConTro();
										}
										break;
									}
									if (s == 77 && !kytu1) // Right
									{
										// Khong con o thao tac nay
										x = 77; 
										kytu = 0;
										kt = 1;
										yy = Nam[so];
										if (dd > DaysOfMounth(mm,yy))
										{
											dd = DaysOfMounth(mm,yy);
											gotoxy(140,8);
											cout << dd;
										//	HienConTro();
										}
										break;
									} 
									if (s == 72 && !kytu1) // Up
									{
										if (so > 0)
										{
											so--;
										}
									}
									if (s == 80 && !kytu1)
									{
										if (so < 3)
										{
											so++;
										}
									}
									// In ds nam
									for (int i = 0; i < 4; i++)
									{
										gotoxy(175,i+10);
										cout << " " << Nam[i] << " ";
									}
									// high light
									gotoxy(175,so+10);
									ChangeColor(240);
									cout << " " << Nam[so] << " ";
									ChangeColor(15);
									gotoxy(158,8);
									cout << Nam[so];
									HienConTro();
									s = getch();
									if (s == -32 || s == 0)
									{
										kytu1 = 0;
										s = getch();
									}
									else
									{
										kytu1 = 1;
									}
								}
								// Ket thuc 
								AnConTro();
								gotoxy(171,8);
								cout << "   ";
								gotoxy(wherex(), wherey()-1);
								ClearKhungPopUp();
								if (s == 27)
								{
									yy = Nam[so];
									x = 27;
									kt = 1;
								}
								break;
							}
						case 5: //gio
							{
								AnConTro();
								gotoxy(145,12);
								cout << "  ";
								gotoxy(171,12);
								cout << "-> ";
								gotoxy(wherex(), wherey()-1);
								KhungPopUp();
								gotoxy(0,12);
								CanhGiua(178,4);
								cout << "HOUR";
								int Gio[24];
								for (int i = 0; i < 24; i++)
								{
									Gio[i] = i;
								}
								// Lay gio cu
								while (Gio[0] != gio)
								{
									int temp = Gio[0];
									for (int i = 0; i <= 22; i++)
									{
										Gio[i] = Gio[i+1];
									}
									Gio[23] = temp;
								}
								for (int i = 0; i < 10; i++)
								{
									AnConTro();
									gotoxy(175,14+i);
									if (Gio[i] <= 9)
									{
										cout << "  0" << Gio[i] << "  ";
									}
									else
									{
										cout << "  " << Gio[i] << "  ";
									}
								}
								// Highlight
								gotoxy(175,14);
								ChangeColor(240);
								if (Gio[0] <= 9)
								{
									cout << "  0" << Gio[0] << "  ";
								}
								else
								{
									cout << "  " << Gio[0] << "  ";
								}
								ChangeColor(15);
								gotoxy(145,12);
								if (Gio[0] <= 9)
								{
									cout << "0" << Gio[0];
								}
								else
								{
									cout << Gio[0];
								}
								HienConTro();
								char s = getch();
								bool kytu1;
								if (s == -32 || s == 0)
								{
									kytu1 = 0;
									s = getch();
								}
								else
								{
									kytu1 = 1;
								}
								while (s != 27)
								{
									if (s == 75 && !kytu) // Left
									{
										x = 75;
										kytu = 0;
										kt = 1;
										gio = Gio[0];
										break;
									}
									if (s == 77 && !kytu1) // Right
									{
										x = 77;
										kytu = 0;
										kt = 1;
										gio = Gio[0];
										break;
									} 
									if (s == 72 && !kytu1) // Up
									{
										int temp = Gio[23];
										for (int i = 23; i >= 1; i--)
										{
											Gio[i] = Gio[i-1];
										}
										Gio[0] = temp;
									}
									if (s == 80 && !kytu1) // Down
									{
										int temp = Gio[0];
										for (int i = 0; i <= 22; i++)
										{
											Gio[i] = Gio[i+1];
										}
										Gio[23] = temp;
									}
									for (int i = 0; i < 10; i++)
									{
										AnConTro();
										gotoxy(175,14+i);
										if (Gio[i] <= 9)
										{
											cout << "  0" << Gio[i] << "  ";
										}
										else
										{
											cout << "  " << Gio[i] << "  ";
										}
									}
									// Highlight
									gotoxy(175,14);
									ChangeColor(240);
									if (Gio[0] <= 9)
									{
										cout << "  0" << Gio[0] << "  ";
									}
									else
									{
										cout << "  " << Gio[0] << "  ";
									}
									ChangeColor(15);
									gotoxy(145,12);
									if(Gio[0] <= 9)
									{
										cout << "0" << Gio[0];
									}
									else
									{
										cout << Gio[0];
									}
									HienConTro();
									s = getch();
									if (s == -32 || s == 0)
									{
										kytu1 = 0;
										s = getch();
									}
									else
									{
										kytu1 = 1;
									}
								}
								// Ket thuc
								gotoxy(171,12);
								cout << "   ";
								gotoxy(wherex(),wherey()-1);
								ClearKhungPopUp();
								if (s == 27)
								{
									gio = Gio[0];
									x = 27;
									kt = 1;
								}
								break;
							}
						case 6: // min
							{
								AnConTro();
								gotoxy(154,12);
								cout << "  ";
								gotoxy(171,12);
								cout << "-> ";
								gotoxy(wherex(), wherey()-1);
								KhungPopUp();
								gotoxy(0,12);
								CanhGiua(178,3);
								cout << "MIN";
								gotoxy(154,12);
								int Phut[60];
								for (int i = 0; i < 60; i++)
								{
									Phut[i] = i;
								}
								// Lay phut cu
								while (Phut[0] != phut)
								{
									int temp = Phut[0];
									for (int i = 0; i <= 58; i++)
									{
										Phut[i] = Phut[i+1];
									}
									Phut[59] = temp;
								}
								for (int i = 0; i < 10; i++)
								{
									AnConTro();
									gotoxy(175,14+i);
									if (Phut[i] <= 9)
									{
										cout << "  0" << Phut[i] << "  ";
									}
									else
									{
										cout << "  " << Phut[i] << "  ";
									}
								}
								// Highlight
								gotoxy(175,14);
								ChangeColor(240);
								if (Phut[0] <= 9)
								{
									cout << "  0" << Phut[0] << "  ";
								}
								else
								{
									cout << "  " << Phut[0] << "  ";
								}
								ChangeColor(15);
								gotoxy(154,12);
								if (Phut[0] <= 9)
								{
									cout << "0" << Phut[0];
								}
								else
								{
									cout << Phut[0];
								}
								HienConTro();
								char s = getch();
								bool kytu1;
								if (s == -32 || s == 0)
								{
									kytu1 = 0;
									s = getch();
								}
								else
								{
									kytu1 = 1;
								}
								while (s != 27)
								{
									if (s == 75 && !kytu) // Left
									{
										x = 75;
										kytu = 0;
										kt = 1;
										phut = Phut[0];
										break;
									}
									if (s == 77 && !kytu1) // Right
									{
										x = 77;
										kytu = 0;
										kt = 1;
										phut = Phut[0];
										break;
									} 
									if (s == 72 && !kytu1) // Up
									{
										int temp = Phut[59];
										for (int i = 59; i >= 1; i--)
										{
											Phut[i] = Phut[i-1];
										}
										Phut[0] = temp;
									}
									if (s == 80 && !kytu1) // Down
									{
										int temp = Phut[0];
										for (int i = 0; i <= 58; i++)
										{
											Phut[i] = Phut[i+1];
										}
										Phut[59] = temp;
									}
									for (int i = 0; i < 10; i++)
									{
										AnConTro();
										gotoxy(175,14+i);
										if (Phut[i] <= 9)
										{
											cout << "  0" << Phut[i] << "  ";
										}
										else
										{
											cout << "  " << Phut[i] << "  ";
										}
									}
									// Highlight
									gotoxy(175,14);
									ChangeColor(240);
									if (Phut[0] <= 9)
									{
										cout << "  0" << Phut[0] << "  ";
									}
									else
									{
										cout << "  " << Phut[0] << "  ";
									}
									ChangeColor(15);
									gotoxy(154,12);
									if(Phut[0] <= 9)
									{
										cout << "0" << Phut[0];
									}
									else
									{
										cout << Phut[0];
									}
									HienConTro();
									s = getch();
									if (s == -32 || s == 0)
									{
										kytu1 = 0;
										s = getch();
									}
									else
									{
										kytu1 = 1;
									}
								}
								// Ket thuc
								gotoxy(171,12);
								cout << "   ";
								gotoxy(wherex(),wherey()-1);
								ClearKhungPopUp();
								
								if (s == 27)
								{
									phut = Phut[0];
									x = 27;
									kt = 1;
								}
								break;
							}
						case 7: // Den
							{
								AnConTro();
								gotoxy(142,16);
								cout << "                  ";
								gotoxy(171,16);
								cout << "-> ";
								gotoxy(wherex(),wherey()-1);
								KhungPopUp2();
								gotoxy(0,16);
								CanhGiua(185,3);
								cout << "DEN";
								string Den[21];
								{
									Den[0] = "Vung Tau";
									Den[1] = "Binh Dinh";
									Den[2] = "Ca Mau";
									Den[3] = "Can Tho";
									Den[4] = "Dak Lak";
									Den[5] = "Da Nang";
									Den[6] = "Dien Bien";
									Den[7] = "Gia Lai";
									Den[8] = "Hai Phong";
									Den[9] = "Ha Noi";
									Den[10] = "Khanh Hoa";
									Den[11] = "Rach Gia";
									Den[12] = "Phu Quoc";
									Den[13] = "Lam Dong";
									Den[14] = "Nghe An";
									Den[15] = "Phu Yen";
									Den[16] = "Quang Binh";
									Den[17] = "Quang Nam";
									Den[18] = "Hue";
									Den[19] = "Thanh Hoa";
									Den[20] = "Quang Ninh";
								}
								if (den.length() != 0) // Lay vi tri cu
								{
									while (Den[0] != den)
									{
										string temp = Den[0];
										for (int i = 0; i <= 19; i++)
										{
											Den[i] = Den[i+1];
										}
										Den[20] = temp;
									}
								}
								for (int i = 0; i < 10; i++)
								{
									AnConTro();
									gotoxy(175,18+i);
									cout << "                    ";
									CanhGiua(185,Den[i].length());
									cout << Den[i];
								}
								// Highlight
								gotoxy(175,18);
								ChangeColor(240);
								cout << "                    ";
								CanhGiua(185,Den[0].length());
								cout << Den[0];
								ChangeColor(15);
								gotoxy(0,16);
								CanhGiua(151,Den[0].length());
								cout << Den[0];
								HienConTro();
								char s = getch();
								bool kytu1;
								if (s == -32 || s == 0)
								{
									kytu1 = 0;
									s = getch();
								}
								else
								{
									kytu1 = 1;
								}
								while (s != 27)
								{
									if (s == 75 && !kytu1) // Left
									{
										den = Den[0];
										x = 75;
										kytu = 0;
										kt = 1;
										break;
									}
									if (s == 77 && !kytu1) // right
									{
										den = Den[0];
										x = 77;
										kytu = 0;
										kt = 1;
										break;
									}
									if (s == 72 && !kytu1) // Up
									{
										string temp = Den[20];
										for (int i = 20; i >= 1; i--)
										{
											Den[i] = Den[i-1];
										}
										Den[0] = temp;
									}
									if (s == 80 && !kytu1) // Down
									{
										string temp = Den[0];
										for (int i = 0; i <= 19; i++)
										{
											Den[i] = Den[i+1];
										}
										Den[20] = temp;
									}
									for (int i = 0; i < 10; i++)
									{
										AnConTro();
										gotoxy(175,18+i);
										cout << "                    ";
										CanhGiua(185,Den[i].length());
										cout << Den[i];
									}
									// Highlight
									gotoxy(175,18);
									ChangeColor(240);
									cout << "                    ";
									CanhGiua(185,Den[0].length());
									cout << Den[0];
									ChangeColor(15);
									gotoxy(142,16);
									cout << "                  ";
									CanhGiua(151,Den[0].length());
									cout << Den[0];
									HienConTro();
									s = getch();
									if (s == -32 || s == 0)
									{
										kytu1 = 0;
										s = getch();
									}
									else
									{
										kytu1 = 1;
									}
								}
							//	gotoxy(151,16);
							//	HienConTro();
								gotoxy(171,16);
								cout << "   ";
								gotoxy(wherex(),wherey()-1);
								ClearKhungPopUp2();
								if (s == 27)
								{
									den = Den[0];
									x = 27;
									kt = 1;
								}
								break;
							}
						case 8: // Trang thai
							{
								AnConTro();
								gotoxy(149,20);
								cout << "           ";
								gotoxy(171,20);
								cout << "-> ";
								gotoxy(wherex(), wherey()-1);
								KhungPopUp2();
								gotoxy(0,20);
								CanhGiua(185,10);
								cout << "TRANG THAI";
								string *TrangThai;
								if (KiemTraThoiGian(gio,phut,dd,mm,yy)) 
								{
									maxtrangthai = 3;
									TrangThai = new string[3];
									TrangThai[0] = "Huy Chuyen";
									TrangThai[1] = "Con ve";
									TrangThai[2] = "Het ve";
		//							TrangThai[3] = "Hoan Tat";
								}
								else
								{
									maxtrangthai = 2;
									TrangThai = new string[2];
									TrangThai[0] = "Huy Chuyen";
									TrangThai[1] = "Hoan Tat";
								}
								if (trangthai != -1)
								{
									if (maxtrangthai == 2)
									{
										if (trangthai == 1 || trangthai == 2) 
										{
											trangthai = 3;
										}
									}
									else
									{
										if (trangthai != 0)
										{
											trangthai = 1;
										}
									}
								}
								if (trangthai == -1)
								{
									trangthai = 1;
								}
								if (maxtrangthai == 3)
								{
									for (int i = 0; i < 3; i++)
									{
										gotoxy(175,22+i);
										cout << "                    ";
										CanhGiua(185,TrangThai[i].length());
										cout << TrangThai[i];
									}
									// highlight
									gotoxy(175,22+trangthai);
									ChangeColor(240);
									cout << "                    ";
									CanhGiua(185,TrangThai[trangthai].length());
									cout << TrangThai[trangthai];
									ChangeColor(15);
									gotoxy(149,20);
									cout << "           ";
									CanhGiua(155,TrangThai[trangthai].length());
									cout << TrangThai[trangthai];
									HienConTro();
								}
								else
								{
									for (int i = 0; i < 3; i++)
									{
										gotoxy(175,22+i);
										cout << "                    ";
										if (i == 0 || i == 1)
										{
											CanhGiua(185,TrangThai[i].length());
											cout << TrangThai[i];
										}
									}
									// highlight
									if (trangthai == 0)
									{
										gotoxy(175,22);
										ChangeColor(240);
										cout << "                    ";
										CanhGiua(185,9);
										cout << "Huy Chuyen";
										ChangeColor(15);
										gotoxy(149,20);
										cout << "           ";
										CanhGiua(155,10);
										cout << "Huy Chuyen";
										HienConTro();
									}
									else
									{
										gotoxy(175,23);
										ChangeColor(240);
										cout << "                    ";
										CanhGiua(185,8);
										cout << "Hoan Tat";
										ChangeColor(15);
										gotoxy(149,20);
										cout << "           ";
										CanhGiua(155,8);
										cout << " Hoan Tat";
										HienConTro();
									}
								}
								char s = getch();
								bool kytu1;
								if (s == -32 || s == 0)
								{
									kytu1 = 0;
									s = getch();
								}
								else
								{
									kytu = 1;
								}
								int dong;
								if (maxtrangthai == 3)
								{
									dong = trangthai;
								}
								else
								{
									if (trangthai == 0)
									{
										dong = 0;
									}
									else
									{
										dong = 1;
									}
								}
								while (s != 27)
								{
									if (s == 75 && !kytu1) // Left
									{
										x = 75;
										kytu = 0;
										kt = 1;
										if (maxtrangthai == 3)
										{
											trangthai = dong;
										}
										else
										{
											if (dong == 0)
											{
												trangthai = dong;
											}
											else
											{
												trangthai = 3;
											}
										}
										break;
									}
									if (s == 77 && !kytu1) // Right
									{
										x = 77;
										kytu = 0;
										kt = 1;
										if (maxtrangthai == 3)
										{
											trangthai = dong;
										}
										else
										{
											if (dong == 0)
											{
												trangthai = dong;
											}
											else
											{
												trangthai = 3;
											}
										}
										break;
									}
									if (s == 72 && !kytu1) // Up
									{
										if (dong > 0)
										{
											dong--;
										}
									}
									if (s == 80 && !kytu1)
									{
										if (maxtrangthai == 3)
										{
											if (dong < 2)
											{
												dong++;
											}
										}
										else
										{
											if (dong < 1)
											{
												dong++;
											}
										}
									}
									if(maxtrangthai == 3)
									{
										for (int i = 0; i < 3; i++)
										{
											AnConTro();
											gotoxy(175,22+i);
											cout << "                    ";
											CanhGiua(185,TrangThai[i].length());
											cout << TrangThai[i];
											// highlight
											gotoxy(175,22+dong);
											ChangeColor(240);
											cout << "                    ";  
											CanhGiua(185,TrangThai[dong].length());
											cout << TrangThai[dong];
											// In Noi dung
											ChangeColor(15);
											gotoxy(149,20);
											cout << "           ";
											CanhGiua(155,TrangThai[dong].length());
											cout << TrangThai[dong];
											HienConTro();
										}
									}
									else
									{
										for (int i = 0; i < 2; i++)
										{
											AnConTro();
											gotoxy(175,22+i);
											cout << "                    ";
											if (i == 0)
											{
												CanhGiua(185,10);
												cout << "Huy Chuyen";
											}
											else
											{
												CanhGiua(185,8);
												cout << "Hoan Tat";
											}
										}
										// highlight
										gotoxy(175,22+dong);
										ChangeColor(240);
										cout << "                    ";
										if (dong == 0)
										{
											CanhGiua(185,10);
											cout << "Huy Chuyen";
										}
										else
										{
											CanhGiua(185,8);
											cout << "Hoan Tat";
										}
										// In Noi dung
										ChangeColor(15);
										gotoxy(149,20);
										cout << "           ";
										if (dong == 0)
										{
											CanhGiua(155,10);
											cout << "Huy Chuyen";
											HienConTro();
										}
										else
										{
											CanhGiua(155,8);
											cout << "Hoan Tat";
											HienConTro();
										}
									}
									s = getch();
									if (s == -32 || s == 0)
									{
										kytu1 = 0;
										s = getch();
									}
									else
									{
										kytu1 = 1;
									}
								}
							//	gotoxy(154,20);
							//	gotoxy(154,20);
								gotoxy(171,20);
								cout << "   ";
								gotoxy(wherex(),wherey()-1);
								ClearKhungPopUp2();
								if (s == 27)
								{
									if (maxtrangthai == 3)
										{
											trangthai = dong;
										}
										else
										{
											if (dong == 0)
											{
												trangthai = dong;
											}
											else
											{
												trangthai = 3;
											}
										}
										gotoxy(0,30);

									x = 27;
									kt = 1;
								}
								break;
							}
						case 9: // Ma May Bay
							{
								AnConTro();
								gotoxy(171,24);
								cout << "-> ";
								gotoxy(wherex(),wherey()-1);
								KhungPopUp2();
								gotoxy(0,24);
								CanhGiua(185,10);
								cout << "MA MAY BAY";
								SoLuongMayBay = SoLuongMayBayKhaDungKhiSua(Phu,b,gio,phut,dd,mm,yy,q);
							//	gotoxy(175,30);
							//	cout << SoLuongMayBay;
								string *MaMayBay;
								if (SoLuongMayBay == 0)
								{
									AnConTro();
									gotoxy(147,24);
									cout << "                  ";
									gotoxy(147,24);
									cout << "Khong co may bay";
									Sleep(500);
									gotoxy(147,24);
									cout << "                ";
									gotoxy(152,24);
									cout << "kha dung";
									Sleep(500);
									gotoxy(152,24);
									cout << "        ";
									gotoxy(156,24);
									HienConTro();
									char s = getch();
									bool kytu1;
									if (s == -32 || s == 0)
									{
										kytu1 = 0;
										s = getch();
									}
									else
									{
										kytu1 = 1;
									}
									while (s != 75 && !kytu1) // Left
									{
										s = getch();
										if (s == -32 || s == 0)
										{
											kytu1 = 0;
											s = getch();
										}
										else
										{
											kytu1 = 1;
										}
									}
									x = 75;
									kytu = 0;
									kt = 1;
									gotoxy(171,24);
									cout << "   ";
									gotoxy(wherex(),wherey()-1);
									ClearKhungPopUp2();
									break;
								}
								MaMayBay = new string[SoLuongMayBay];
								DanhSachMaMayBayKhaDungKhiSua(Phu,b,gio,phut,dd,mm,yy,MaMayBay,SoLuongMayBay,q);
		//						gotoxy(0,40);
		//						cout << SoLuongMayBay;
								if (MaMayBay1.length() == 0)
								{
									MaMayBay1 = MaMayBay[0];
								}
								else
								{
									for ( int i = 0; i < SoLuongMayBay; i++)
									{
										string temp = MaMayBay[0];
										for (int j = 0; j < SoLuongMayBay-1; j++)
										{
											MaMayBay[j] = MaMayBay[j+1];
										}
										MaMayBay[SoLuongMayBay-1] = temp;
										if(MaMayBay[0] == MaMayBay1)
										{
											break;
										}
									}
									MaMayBay1 = MaMayBay[0];
								}
								if (SoLuongMayBay < 10)
								{
									for (int i = 0; i < SoLuongMayBay; i++)
									{
										gotoxy(175,26+i);
										cout << "                    ";
										CanhGiua(185,MaMayBay[i].length());
										cout << MaMayBay[i];
									}
									// Highlight
									gotoxy(175,26);
									ChangeColor(240);
									cout << "                    ";
									CanhGiua(185,MaMayBay[0].length());
									cout << MaMayBay[0];
									gotoxy(147,24);
									ChangeColor(15);
									cout << "                  ";
									CanhGiua(156,MaMayBay[0].length());
									cout << MaMayBay[0];
									HienConTro();
								}
								else
								{
									for (int i = 0; i < 10; i++)
									{
										gotoxy(175,26+i);
										cout << "                    ";
										CanhGiua(185,MaMayBay[i].length());
										cout << MaMayBay[i];
									}
									// Highlight
									gotoxy(175,26);
									ChangeColor(240);
									cout << "                    ";
									CanhGiua(185,MaMayBay[0].length());
									cout << MaMayBay[0];
									gotoxy(147,24);
									ChangeColor(15);
									cout << "                  ";
									CanhGiua(156,MaMayBay[0].length());
									cout << MaMayBay[0];
									HienConTro();
								}
								char s = getch();
								bool kytu1;
								if (s == -32 || s == 0)
								{
									kytu1 = 0;
									s = getch();
								}
								else
								{
									kytu1 = 1;
								}
								while (s != 27)
								{
									AnConTro();
									if (s == 75 && !kytu1) // Left
									{
										MaMayBay1 = MaMayBay[0];
										kytu = 0;
										x = 75;
										kt = 1;
										break;
									}
								/*	if (s == 77 && !kytu1) // Right
									{
										MaMayBay1 = MaMayBay[0];
										kytu = 0;
										x = 77;
										kt = 1;
										break;
									} */
									if (s == 72 && !kytu1) // Up
									{
										string temp = MaMayBay[SoLuongMayBay - 1];
										for (int i = SoLuongMayBay - 1; i >= 1; i--)
										{
											MaMayBay[i] = MaMayBay[i-1];
										}
										MaMayBay[0] = temp;
									}
										if (s == 80 && !kytu1) // Down
									{
										string temp = MaMayBay[0];
										for (int i = 0; i < SoLuongMayBay - 1; i++)
										{
											MaMayBay[i] = MaMayBay[i+1];
										}
										MaMayBay[SoLuongMayBay-1] = temp;
									}
									if (SoLuongMayBay < 10)
									{
										for (int i = 0; i < SoLuongMayBay; i++)
										{
											gotoxy(175,26+i);
											cout << "                    ";
											CanhGiua(185,MaMayBay[i].length());
											cout << MaMayBay[i];
										}
										// Highlight
										gotoxy(175,26);
										ChangeColor(240);
										cout << "                    ";
										CanhGiua(185,MaMayBay[0].length());
										cout << MaMayBay[0];
										gotoxy(147,24);
										ChangeColor(15);
										cout << "                  ";
										CanhGiua(156,MaMayBay[0].length());
										cout << MaMayBay[0];
										HienConTro();
									}
									else
									{
										for (int i = 0; i < 10; i++)
										{
											gotoxy(175,26+i);
											cout << "                    ";
											CanhGiua(185,MaMayBay[i].length());
											cout << MaMayBay[i];
										}
										// Highlight
										gotoxy(175,26);
										ChangeColor(240);
										cout << "                    ";
										CanhGiua(185,MaMayBay[0].length());
										cout << MaMayBay[0];
										gotoxy(147,24);
										ChangeColor(15);
										cout << "                  ";
										CanhGiua(156,MaMayBay[0].length());
										cout << MaMayBay[0];
										HienConTro();
									}
									s = getch();
									if (s == -32 || s == 0)
									{
										kytu1 = 0;
										s = getch();
									}
									else
									{
										kytu1 = 1;
									}
								}
								gotoxy(171,24);
								cout << "   ";
								gotoxy(wherex(),wherey()-1);
								ClearKhungPopUp2();
								if (s == 27)
								{
									MaMayBay1 = MaMayBay[0];
									x = 27;
									kt = 1;
								}
								break;
							}
						case 10: // LUU
							{
								AnConTro();
								gotoxy(147,30);
								ChangeColor(240);
								cout << "  LUU  ";
								ChangeColor(15);
								char s = getch();
								bool kytu1;
								if (s == -32 || s == 0)
								{
									kytu1 = 0;
									s = getch();
								}
								else
								{
									kytu = 1;
								}
								if (s == 13) // Enter
								{
									luu = 1; // Xac nhan luu
									kt = 1;
								}
								else
								{
									if (s == 75 && !kytu1) // Left
									{
										gotoxy(147,30);
										ChangeColor(15);
										cout << "  LUU  ";
										x = 75;
										kytu = 0;
										kt = 1;
										
									}
									if (s == 27)
									{
										x = 27;
										kt = 1;
									}
								}
								break;
							}
					}
				//	HienConTro();
					if (!kt)
					{
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
				if (x == 27)
				{
					Day Ngay;
					Ngay.dd = dd;
					Ngay.mm = mm;
					Ngay.yy = yy;
					Time Gio;
					Gio.hour = gio;
					Gio.min = phut;
					string diemden;
					for (int i = 0; i < den.length(); i++)
					{
						if (den[i] == ' ')
						{
							diemden = diemden+'0';
						}
						else
						{
							diemden =  diemden + den[i];
						}
					}
					
					q->chuyenbay.DatMaChuyen(MaChuyenBay);
					q->chuyenbay.DatNgay(Ngay);
					q->chuyenbay.DatGio(Gio);
					q->chuyenbay.DatDiemDen(diemden);
					q->chuyenbay.DatTrangThai(trangthai);
					q->chuyenbay.DatSoHieu(MaMayBay1);
					for (int i = 0; i < b.n; i++)
					{
						if (b.data[i]->LaySoHieu() == MaMayBay1)
						{
							p->chuyenbay.DatSoCho(b.data[i]->LaySoCho());  
							p->chuyenbay.DatLoai(b.data[i]->LayLoai());
						}
					}
//					gotoxy(0,32); cout << q->chuyenbay.LayTrangThai()
					// rehighlight
					if (line1%10 == 0)
					{
						gotoxy(0,2*10+1);
						ChangeColor(240);
					}
					else
					{
						gotoxy(0,2*line1+1);
						ChangeColor(240);
					}
					// ========== HIGHLIGHT============
					for (int i = 1; i <= 120; i++) // highlight
					{
						if (i == 1 || i == 120)
						{
							cout << docngoai;
						}
						else
						{
							if (i%20 == 0)
							{
								cout << doctrong;
							}
							else
							{
								cout << " ";
							}
						}
					}
					gotoxy(wherex()+10,0);
	//				ChangeColor(15);
	//				CuaSoChuyenBay();
	//				ChangeColor(240);
					q = Phu.Head;
					for (int i = 1; i < line1; i++)
					{
						if (q == NULL) break;
						q = q->next;
					}
					int DoDaiThoiGian1 = DoDaiNgay(q->chuyenbay.LayNgay()) + DoDaiGio(q->chuyenbay.LayGio()) + 1;
					gotoxy(0,2*((line1-1)%10 + 1) + 1);
					CanhGiua(10,q->chuyenbay.LayMaChuyen().length()); // In Ma Chuyen
					cout << q->chuyenbay.LayMaChuyen();
					CanhGiua(30,DoDaiThoiGian); // In Gio Xuat Phat
					InGio(q->chuyenbay.LayGio());
					cout << " ";
					InNgay(q->chuyenbay.LayNgay());
					CanhGiua(50,5); // In Dia Diem xuat phat
					cout << "TPHCM";
					CanhGiua(70,q->chuyenbay.LayDiemDen().length()); // In Dia Diem den
					for (int i = 0; i < q->chuyenbay.LayDiemDen().length(); i++)
					{
						if (q->chuyenbay.LayDiemDen()[i] == 48) // so '0'
						{
							cout << " ";
						}
						else
						{
							cout << q->chuyenbay.LayDiemDen()[i];
						}
					}
					//========= TRANG THAI ================
					switch (q->chuyenbay.LayTrangThai())
					{
						case 0:
						{
							CanhGiua(90,9);
							cout << "Huy Chuyen";
							break;
						}	
						case 1:
						{
							CanhGiua(90,6);
							cout << "Con Ve";
							break;
						}
						case 2:
						{
							CanhGiua(90,6);
							cout << "Het Ve";
							break;
						}
						case 3:
						{
							CanhGiua(90,8);
							cout << "Hoan Tat";
							break;
						}
					}
					CanhGiua(110,q->chuyenbay.LaySoHieu().length());
					cout << q->chuyenbay.LaySoHieu();
					AnConTro();
					luu = 1;
					break;
				}
			
				
			}
		}
		// Cap nhat page hien tai
		currentpage = (line1-1)/10 + 1;
		t = getch();
		{
			if (t == -32 || t == 0)
			{
				kytu2 = 0;
				t = getch();
			}
			else
			{
				kytu2 = 1;
			}
		}
	}
	
	a.Head = Phu.Head;
	a.Tail = Phu.Tail;

}
// ======================== IN GHE KHA DUNG CUA CHUYEN BAY =======================
void InGheKhaDung (ListChuyenBay a, CacChuyenBay *p)
{
//	CacChuyenBay *p;
//	p->chuyenbay.LayDanhSachVe()[0].HanhKhach = new KhachHang;
	int x = wherex();
	int y = wherey();
	InKhungGhe(p->chuyenbay.LaySoCho());
	gotoxy(x-2,y-2);
	for (int i = 1; i <= 4; i++)
	{
		for (int j = 1; j <= p->chuyenbay.LaySoCho()/4+1; j++)
		{
			if (i == 1 && j == 1)
			{
			//	cout << "adad";
				gotoxy(x+2,y+2);
			}
			if (i == 2 && j == 1)
			{
				gotoxy(x+2,y+2+2);
			}
			if (i == 3 && j == 1)
			{
				gotoxy(x+2,y+2+2+3);
			}
			if (i == 4 && j == 1)
			{
				gotoxy(x+2,y+2+2+3+2);
			}
			if (p->chuyenbay.LayDanhSachVe()[(j-1)*4+i-1].HanhKhach != NULL) // Dat r
			{
				if ((j-1)*4+i <= p->chuyenbay.LaySoCho())
				{
					ChangeColor(207);
					if ((j-1)*4+i <= 9)
					{
						cout << "0" << (j-1)*4+i;
					}
					else
					{
						cout << (j-1)*4+i;
					}
				}
				ChangeColor(15);
				cout  << "  ";
			}
			else
			{
			//	ChangeColor(204);
				if ((j-1)*4+i <= p->chuyenbay.LaySoCho())
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
			//	ChangeColor(15);
				cout  << "  ";
			}
		}
	}
}
// ============================== CHON GHE ================================
int ChonGhe(ListChuyenBay &a, CacChuyenBay *p,int so)
{
	int x = wherex();
	int y = wherey();
	AnConTro();
//	int so;
//	p->chuyenbay.LayDanhSachVe()[18].HanhKhach = new KhachHang;
//	p->chuyenbay.LayDanhSachVe()[22].HanhKhach = new KhachHang;
	InGheKhaDung(a,p);
	if (so == 0)
	{
		for (int i = 1; i <= p->chuyenbay.LaySoCho(); i++)
		{
			if (p->chuyenbay.LayDanhSachVe()[i-1].HanhKhach == NULL)
			{
				so = i;
				break;
			}
		}
	}
	gotoxy(x+2,y+2);
	int i,j;
//	gotoxy(0,0); cout << so;
	if ((so)%4 == 0)
	{
		i = 4;
	}
	else
	{
		i = so%4;
	}
	for ( j = 1; j <= p->chuyenbay.LaySoCho(); j++)
	{
 		if (i == 1 && j == 1)
		{
			gotoxy(x+2,y+2);
		}
		if (i == 2 && j == 1)
		{
			gotoxy(x+2,y+2+2);
		}
		if (i == 3 && j == 1)
		{
			gotoxy(x+2,y+2+2+3);
		}
		if (i == 3 && j == 1)
		{
			gotoxy(x+2,y+2+2+3+2);
		}
		if (j != 1)
		{
			gotoxy(wherex()+4, wherey());
		}
		if ((j-1)*4+i == so)
		{
			if ((j-1)*4+i <= 9)
			{
				ChangeColor(240);
				cout << "0" << (j-1)*4+i;
				ChangeColor(15);
				break;
			}
			else
			{
				ChangeColor(240);
				cout << (j-1)*4+i;
				ChangeColor(15);
				break;
			}
		}
	}
	char s = getch();
	bool kytu;
	if (s == -32 || s == 0)
	{
		s = getch();
		kytu = 0;
	}
	else
	{
		kytu = 1;
	}
//	HienConTro();
	while (s != 27  && s != 13) // Enter or Ecs
	{
		int so1 = so;
		int hoanhdo = wherex();
		int tungdo = wherey();
		if (s == 75 && !kytu) // Left
		{
			int hoanhdo = wherex();
			int tungdo = wherey();
		//	int so1 = so;
			while (so-4 > 0)
			{
				so = so-4;
				if (so + 4 == 100)
				{
					gotoxy(wherex()-5,wherey());
				}
				else
				{
					gotoxy(wherex()-4,wherey());
				}
				if (p->chuyenbay.LayDanhSachVe()[so-1].HanhKhach == NULL)
				{
					break;
				}
			}
			if (p->chuyenbay.LayDanhSachVe()[so-1].HanhKhach == NULL)
			{
				int hd = wherex();
				int td = wherey();
				if (so1 == 100) // Unhighlight
				{
					gotoxy(hoanhdo-3,tungdo);
				}
				else
				{
					gotoxy(hoanhdo-2,tungdo);
				}
				ChangeColor(15);
				if (so1 <= 9)
				{
					cout << "0" << so1;
				}
				else
				{
					cout << so1;
				}
				gotoxy(hd-2,td);
				ChangeColor(240); // highlight
			///	gotoxy(wherex()-2,wherey());
				if (so <= 9)
				{
					cout << "0" << so;
				}
				else
				{
					cout << so;
				}
			}
			else
			{
				gotoxy(hoanhdo,tungdo); // back lai cai cu
				ChangeColor(240);
				gotoxy(hoanhdo-2,tungdo);
				if (so1 <= 9)
				{
					cout << "0" << so1;
				}
				else
				{
					cout << so1;
				}
				ChangeColor(15);
				so = so1;
			}
		}
		if (s == 77 && !kytu) // Right
		{
		//	int so1 = so;
			while (so + 4 <= p->chuyenbay.LaySoCho())
			{
				so = so+4;
				if (so == 100)
				{
					gotoxy(wherex()+5,wherey());
				}
				else
				{
					gotoxy(wherex()+4,wherey());
				}
				if (p->chuyenbay.LayDanhSachVe()[so-1].HanhKhach == NULL)
				{
					break;
				}
			}
			if (p->chuyenbay.LayDanhSachVe()[so-1].HanhKhach == NULL)
			{
				int hd = wherex();
				int td = wherey();
				ChangeColor(15);
				if (so1 == 100)
				{
					gotoxy(hoanhdo-3,tungdo);
				}
				else
				{
					gotoxy(hoanhdo-2,tungdo);
				}
				if (so1 <= 9)
				{
					cout << "0" << so1;
				}
				else
				{
					cout << so1;
				}
				if (so == 100)
				{
					gotoxy(hd-3,td);
				}
				else
				{
					gotoxy(hd-2,td);
				}
			//	gotoxy(wherex()-2,wherey());
				ChangeColor(240); // Highlight
				if (so <= 9)
				{
					cout << "0" << so;
				}
				else
				{
					cout << so;
				}
			}
			else
			{
				so = so1;
				if (so == 100)
				{
					gotoxy(hoanhdo-3,tungdo);
				}
				else
				{
					gotoxy(hoanhdo-2,tungdo);
				}
				ChangeColor(240); // Highlight
				if (so <= 9)
				{
					cout << "0" << so;
				}
				else
				{
					cout << so;
				}
			}
		}
		if (s == 72 && !kytu) // Up
		{
			int hoanhdo = wherex();
			int tungdo = wherey();
			int so1 = so;
			while ((so-1)%4 != 0)
			{
				so = so-1;
				if (so%4 == 2)
				{
					gotoxy(wherex(),wherey()-3);
				}
				else
				{
					if (so+1 == 100)
					{
						gotoxy(wherex()-1,wherey()-2);
					}
					else
					{
						gotoxy(wherex(),wherey()-2);
					}
				}
				if(p->chuyenbay.LayDanhSachVe()[so-1].HanhKhach == NULL)
				{
					break;
				}
			}
			if (p->chuyenbay.LayDanhSachVe()[so-1].HanhKhach == NULL)
			{
				int hd = wherex();
				int td = wherey();
				ChangeColor(15);
				if (so+1 == 100)
				{
					gotoxy(hoanhdo-3,tungdo);
					if (so1 <= 9)
					{
						cout << "0" << so1;
					}
					else
					{
						cout << so1;
					}
				}
				else
				{
					gotoxy(hoanhdo-2,tungdo);
					if (so1 <= 9)
					{
						cout << "0" << so1;
					}
					else
					{
						cout << so1;
					}
				}
				gotoxy(hd-2,td);
				ChangeColor(240); // Highlight
				if (so <= 9)
				{
					cout << "0" << so;
				}
				else
				{
					cout << so;
				}
			}
			else
			{
				so = so1;
				if (so == 100)
				{
					gotoxy(hoanhdo-3,tungdo);
				}
				else
				{
					gotoxy(hoanhdo-2,tungdo);
				}
				ChangeColor(240); // Highlight
				if (so <= 9)
				{
					cout << "0" << so;
				}
				else
				{
					cout << so;
				}
			}
		}
		if (s == 80 && !kytu) // Down
		{
			int hoanhdo = wherex();
			int tungdo = wherey();
			int so1 = so;
			while ((so+1)%4 != 1)
			{
				so = so + 1;
				if (so%4 == 3)
				{
					gotoxy(wherex(),wherey()+3);
				}
				else
				{
					if (so == 100 && p->chuyenbay.LayDanhSachVe()[99].HanhKhach != NULL)
					{
						gotoxy(wherex(),wherey()+2);
					}
					else
					{
						gotoxy(wherex(),wherey()+2);
					}
				}
				if (p->chuyenbay.LayDanhSachVe()[so-1].HanhKhach == NULL)
				{
					break;
				}
			}
			if (p->chuyenbay.LayDanhSachVe()[so-1].HanhKhach == NULL)
			{
				int hd = wherex();
				int td = wherey();	
				ChangeColor(15);
				if (so1 == 100)
				{
					gotoxy(hoanhdo-3,tungdo);
				}
				else
				{
					gotoxy(hoanhdo-2,tungdo);
				}
				if (so1 <= 9)
				{
					cout << "0" << so1;
				}
				else
				{
					cout << so1;
				}
				if (so == 100 && so1 == 100)
				{
					gotoxy(hd-3,td);
				}
				else
				{
					gotoxy(hd-2,td);
				}
				ChangeColor(240); // Highlight
				if (so <= 9)
				{
					cout << "0" << so ;
				}
				else
				{
					cout << so;
				}
			}
			else
			{
				so = so1;
				if (so == 100)
				{
					gotoxy(hoanhdo-3,tungdo);
				}
				else
				{
					gotoxy(hoanhdo-2,tungdo);
				}
				ChangeColor(240); // Highlight
				if (so <= 9)
				{
					cout << "0" << so;
				}
				else
				{
					cout << so << "k";
				}
			}
		}
		s = getch();
		if (s == -32 || s == 0)
		{
			s = getch();
			kytu = 0;
		}
		else
		{
			kytu = 1;
		}
	}
	if (s == 27)
	{
		return 0;
	}
	if (s == 13)
	{
		ChangeColor(15);
		gotoxy(x,y);
			int dai;
			if (p->chuyenbay.LaySoCho()%4 == 0)
			{
				dai = 4 + 4*(p->chuyenbay.LaySoCho()/4 )+ 2;
			}
			else
			{
				dai = 4 + 4*(p->chuyenbay.LaySoCho()/4+1) + 2;
			}
			for (int  i = 1; i <= 12; i++)
			{
				for (int j = 1; j <= dai; j++)
				{
					cout << " ";
				}
				gotoxy(wherex()-dai,wherey()+1);
			}
		return so;
	}
}
// ========================= KIEM TRA HANH KHACH TREN CHUYEN BAY =========================
bool KiemTraHanhKhachTrenChuyenBay(CacChuyenBay *p, string CMND)
{
		for (int i = 0; i < p->chuyenbay.LaySoCho(); i++)
		{
			if (p->chuyenbay.LayDanhSachVe()[i].HanhKhach != NULL)
			{
				if (p->chuyenbay.LayDanhSachVe()[i].HanhKhach->HanhKhach.CMND == CMND)
				{
				//	cout << "Hello";
					return 1;
				}
			}
		}
		return 0;
}
// ======================= CHUYEN BAY KHA DUNG ===================================
void ChuyenBayKhaDung(ListChuyenBay &a, ListChuyenBay &Phu, string CMND, string &den)
{
	string den1;
	Phu.SoLuong = 0;
	for (int i = 0; i < den.length(); i++)
	{
		if (den[i] == ' ')
		{
			den1 = den1+'0';
		}
		else
		{
			den1 = den1 + den[i];
		}
	}
//	gotoxy(175,0);
//	if (den1 == a.Head->chuyenbay.LayDiemDen()) cout << "Dung";
	CacChuyenBay *p = a.Head;
	for (p = a.Head; p != NULL; p = p->next) 
	{
	//	gotoxy(0,175);
	//	cout << KiemTraHanhKhachTrenChuyenBay(p,CMND);
	//	Sleep(1000);
		if (!(KiemTraHanhKhachTrenChuyenBay(p,CMND)))
		{
			if ((p->chuyenbay.LayTrangThai() != 0) && (p->chuyenbay.LayTrangThai() != 2))
			{
				int hh = p->chuyenbay.LayGio().hour;
				int min = p->chuyenbay.LayGio().min;
				int dd = p->chuyenbay.LayNgay().dd;
				int mm = p->chuyenbay.LayNgay().mm;
				int yy = p->chuyenbay.LayNgay().yy;
				if (KiemTraThoiGian(hh,min,dd,mm,yy) && p->chuyenbay.LayDiemDen() == den1)
				{
					CacChuyenBay *q = NULL;
					for (q = a.Head; q != NULL; q = q->next)
					{
						if (q != p)
						{
							int hh1 = q->chuyenbay.LayGio().hour;
							int min1 = q->chuyenbay.LayGio().min;
							int dd1 = q->chuyenbay.LayNgay().dd;
							int mm1 = q->chuyenbay.LayNgay().mm;
							int yy1 = q->chuyenbay.LayNgay().yy;
							if ((KiemTraHanhKhachTrenChuyenBay(q,CMND) && !KiemTraHaiKhoangThoiGian(hh1,min1,dd1,mm1,yy1,hh,min,dd,mm,yy))) // q co hanh khach do va 2 chuyen lien ke nhau
							{
								break; // chuyen bay p khong kha dung
							}
						}
					}
					if (q == NULL)
					{
						Phu.SoLuong++;
						CacChuyenBay *x = new CacChuyenBay;
						x->chuyenbay.DatDiemDen(p->chuyenbay.LayDiemDen());
						x->chuyenbay.DatGio(p->chuyenbay.LayGio());
						x->chuyenbay.DatLoai(p->chuyenbay.LayLoai());
						x->chuyenbay.DatMaChuyen(p->chuyenbay.LayMaChuyen());
						x->chuyenbay.DatNgay(p->chuyenbay.LayNgay());
						x->chuyenbay.DatSoHieu(p->chuyenbay.LaySoHieu());
						x->chuyenbay.DatTrangThai(p->chuyenbay.LayTrangThai());
						if (Phu.Head == NULL)
							{
								Phu.Head = x;
								Phu.Tail = x;
							}
						else
							{
								Phu.Tail->next = x;
								x->next = NULL;
								Phu.Tail = x;
							}
					}
					 //cout << "Hello ";
				}
			}
		}
			
	}
}
// ================== SO HANH KHACH TREN CHUYEN BAY =========================
int SoLuongHanhKhachTrenChuyenBay(CacChuyenBay *p)
{
	int SoLuong = 0;
	for (int i = 0; i < p->chuyenbay.LaySoCho(); i++)
	{
		if (p->chuyenbay.LayDanhSachVe()[i].HanhKhach != NULL)
		{
			SoLuong++;
		}
	}
	return SoLuong;
}
// ======================================== DAT VE ==========================================
int DatVe(ListChuyenBay &a, CayKhachHang &b)
{
	InDanhSachChuyenBay(a,1);
	string CMND = "";
	string name = "";
	int GioiTinh = 0;
	string MaChuyenBay;
	int SoGhe = 0;
	string den = "";
	string Den[21];
	Den[0] = "Vung Tau";
	Den[1] = "Binh Dinh";
	Den[2] = "Ca Mau";
	Den[3] = "Can Tho";
	Den[4] = "Dak Lak";
	Den[5] = "Da Nang";
	Den[6] = "Dien Bien";
	Den[7] = "Gia Lai";
	Den[8] = "Hai Phong";
	Den[9] = "Ha Noi";
	Den[10] = "Khanh Hoa";
	Den[11] = "Rach Gia";
	Den[12] = "Phu Quoc";
	Den[13] = "Lam Dong";
	Den[14] = "Nghe An";
	Den[15] = "Phu Yen";
	Den[16] = "Quang Binh";
	Den[17] = "Quang Nam";
	Den[18] = "Hue";
	Den[19] = "Thanh Hoa";
	Den[20] = "Quang Ninh";
						
//	int SoLuongChuyenBay; // So chuyen bay kha dung
	ListChuyenBay chuyenbaykhadung;
	gotoxy(5,25);
	KhungDatVe();
/*	gotoxy(28,3);
	cout << "111111111";
	gotoxy(19,7);
	cout << "111111111111111111111111111111111";
	gotoxy(34,11);
	cout << "11111";
	gotoxy(24,15);
	cout << "1111111111111111111111";
	gotoxy(28,19);
	cout << "11111"; */
	gotoxy(28,28);
	HienConTro();
	char x = getch();
	bool kytu;
	if (x == -32 || x == 0)
	{
		kytu = 0;
		x = getch();
	}
	else
	{
		kytu = 1;
	}
	int line = 1;
	bool kt;
	bool change = 1;
	while (x != 27 || line == 1) // Esc
	{
		kt = 0;
		if (x == 75 && !kytu) // left
		{
			if (line > 4)
			{
				line--;
			}
		} 
		if (x == 77 && !kytu) // Right
		{
			if (line == 1)
			{
				if (CMND.length() == 0)
				{
					/*AnConTro();
					cout << "Khong de trong";
					Sleep(500);
					gotoxy(wherex()-14,wherey());
					cout << "              ";
					gotoxy(wherex()-14,wherey());
					HienConTro(); */
				}
				else
				{
					line++;
				}
			}
			else
			{
				line++;
			}
		}
		switch(line)
		{
			case 1: // CMND
				{
					AnConTro();
					gotoxy(28,28);
					cout << "         ";
					gotoxy(28,28);
					if (LaySoCMND(CMND,x,kytu) == 0)
					{
					//	system("pause");
					}
				//	gotoxy(175,1);
				//	cout << CMND;
					else
					{
						TimKiemTrongCayKhachHang(b,CMND,name,GioiTinh);
						if (name.length() != 0)
						{
							for (int i = 0; i < name.length(); i++)
							{
								if (name[i] == '0')
								{
									name[i] = ' ';
								}
							}
							change = 0;
						}
						else
						{
							name = "";
						}  
					}
				//	cout << "";
				//	cout << TimKiemTrongCayKhachHang(b,CMND);
				//	cout << name;
				//	gotoxy(0,30);
				//	cout << CMND;
					kt = 1;
					break;
				}
			case 2: // Ho va ten
				{
					AnConTro();
					gotoxy(19,32);
					cout << "                                 ";
					HienConTro();
					CanhGiua(35,name.length());
					if (change)
					{
						if(NhapHoTen(name,x,kytu) == 0)
						{
							kt = 1;
							x = 27;
						}
						kt = 1;
					}
					else
					{
						cout << name;
						x = 77;
						kt = 1;
						kytu = 0;
					}
				//	gotoxy(0,30);
				//	cout << name;
					HienConTro();
					break;
				}
			case 3: // Gioi tinh
				{
					AnConTro();
					string gioitinh[2];
					gioitinh[0] = "Nu";
					gioitinh[1] = "Nam";
					if (change)
					{
						gotoxy(55,36);
						cout << "-> ";
						gotoxy(wherex(),wherey()-1);
						KhungPopUp2();
						gotoxy(0,36);
						CanhGiua(69,9);
						cout << "GIOI TINH";
						gotoxy(59,38);
						cout << "                    ";
						CanhGiua(69,2);
						cout << "Nu";
						gotoxy(59,39);
						cout << "                    ";
						CanhGiua(69,3);
						cout << "Nam";
						ChangeColor(240);
						gotoxy(59,38+GioiTinh);
						cout << "                    ";
						CanhGiua(69,gioitinh[GioiTinh].length());
						cout << gioitinh[GioiTinh];
						gotoxy(34,36);
						ChangeColor(15);
						cout << "     ";
						CanhGiua(36,gioitinh[GioiTinh].length());
						cout << gioitinh[GioiTinh];
						HienConTro();
						char s = getch();
						bool kytu1;
						if (s == -32 || s == 0)
						{
							kytu1 = 0;
							s = getch();
						}
						else
						{
							kytu1 = 1;
						}
						while (s != 27)
						{
							if ((s ==  75 || s == 77) && !kytu1)
							{
							//	cout << "mbgf";
								kt = 1;
								x = s;
								kytu = kytu1;
								break;
							}
							if (s == 72 && !kytu1) // Up
							{
								if (GioiTinh == 1)
								{
									GioiTinh--;
								}
							}
							if (s == 80 && !kytu1)
							{
								if (GioiTinh == 0)
								{
									GioiTinh++;
								}
							}
							gotoxy(59,38);
							cout << "                    ";
							CanhGiua(69,2);
							cout << "Nu";
							gotoxy(59,39);
							cout << "                    ";
							CanhGiua(69,3);
							cout << "Nam";
							ChangeColor(240);
							gotoxy(59,38+GioiTinh);
							cout << "                    ";
							CanhGiua(69,gioitinh[GioiTinh].length());
							cout << gioitinh[GioiTinh];
							gotoxy(34,36);
							ChangeColor(15);
							cout << "     ";
							CanhGiua(36,gioitinh[GioiTinh].length());
							cout << gioitinh[GioiTinh];
							HienConTro();
							s = getch();
							if (s == -32 || s == 0)
							{
								kytu1 = 0;
								s = getch();
							}
							else
							{
								kytu1 = 1;
							}
						}
						gotoxy(55,36);
						cout << "   ";
						gotoxy(wherex(),wherey()-1);
						ClearKhungPopUp2();
						if (s == 27)
						{
							x = 27;
							kt = 1;
						}
					}
					else
					{
						gotoxy(34,36);
						ChangeColor(15);
						cout << "     ";
						CanhGiua(36,gioitinh[GioiTinh].length());
						cout << gioitinh[GioiTinh];
						HienConTro();
						x = 77;
						kt = 1;
						kytu = 0;
					}
				//	ChuyenBayKhaDung(a,)
					break;
				}
			case 4: // Den
				{
					char ngangtrong = 196;
					char doctrong = 179;
					char traitrentrong = 218;
					char phaitrentrong = 191;
					char traiduoitrong = 192;
					char phaiduoitrong = 217;
					gotoxy(60,30);
					cout << "DEN  ";
					gotoxy(wherex(),wherey()-1);
					for (int i = 1; i <= 3; i++ )
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
						gotoxy(wherex()-22,wherey()+1);
					}
					gotoxy(87,30);
					cout << "-> ";
					gotoxy(wherex(),wherey()-1);
					KhungPopUp2();
					gotoxy(0,30);
					CanhGiua(101,3);
					cout << "DEN";
						
/*						if (den.length() != 0) // Lay vi tri cu
						{
							gotoxy(0,157);
							cout << den;
							while (Den[0] != den)
							{
								string temp = Den[0];
								for (int i = 0; i <= 19; i++)
								{
									Den[i] = Den[i+1];
								}
								Den[20] = temp;
							}
						} */
						for (int i = 0; i < 10; i++)
						{
							AnConTro();
							gotoxy(91,32+i);
							cout << "                    ";
							CanhGiua(101,Den[i].length());
							cout << Den[i];
						}
						// Highlight
						gotoxy(91,32);
						ChangeColor(240);
						cout << "                    ";
						CanhGiua(101,Den[0].length());
						cout << Den[0];
						ChangeColor(15);
						gotoxy(0,30);
						CanhGiua(75,Den[0].length());
						cout << Den[0];
						HienConTro();
						char s = getch();
						bool kytu1;
						if (s == -32 || s == 0)
						{
							kytu1 = 0;
							s = getch();
						}
						else
						{
							kytu1 = 1;
						}
						while (s != 27)
						{
							if (s == 75 && !kytu1) // Left
							{
								den = Den[0];
								x = 75;
								kytu = 0;
								kt = 1;
								break;
							}
							if (s == 77 && !kytu1) // right
							{
								den = Den[0];
								x = 77;
								kytu = 0;
								kt = 1;
								break;
							}
							if (s == 72 && !kytu1) // Up
							{
								string temp = Den[20];
								for (int i = 20; i >= 1; i--)
								{
									Den[i] = Den[i-1];
								}
								Den[0] = temp;
							}
							if (s == 80 && !kytu1) // Down
							{
								string temp = Den[0];
								for (int i = 0; i <= 19; i++)
								{
									Den[i] = Den[i+1];
								}
								Den[20] = temp;
							}
							for (int i = 0; i < 10; i++)
							{
								AnConTro();
								gotoxy(91,32+i);
								cout << "                    ";
								CanhGiua(101,Den[i].length());
								cout << Den[i];
							}
							// Highlight
							gotoxy(91,32);
							ChangeColor(240);
							cout << "                    ";
							CanhGiua(101,Den[0].length());
							cout << Den[0];
							ChangeColor(15);
							gotoxy(66,30);
							cout << "                  ";
							CanhGiua(75,Den[0].length());
							cout << Den[0];
							HienConTro();
							s = getch();
							if (s == -32 || s == 0)
							{
								kytu1 = 0;
								s = getch();
							}
							else
							{
								kytu1 = 1;
							}
						}
						if (s == 27)
						{
							x = 27;
							kt = 1;
							gotoxy(87,30);
							cout << "   ";
							gotoxy(wherex(),wherey()-1);
							ClearKhungPopUp2();
							den = Den[0];
						}
						else
						{
							gotoxy(87,30);
							cout << "   ";
							gotoxy(wherex(),wherey()-1);
							ClearKhungPopUp2();
							
							ChuyenBayKhaDung(a,chuyenbaykhadung,CMND,den);
							if (chuyenbaykhadung.SoLuong == 0)
							{
								chuyenbaykhadung.Head = chuyenbaykhadung.Tail = NULL;
							}
						//	gotoxy(185,20);
						//	cout << den;
						//	gotoxy(97,10);
							InDanhSachChuyenBay(chuyenbaykhadung,1);
						
						}
						break;
				}
			case 5: // Ma Chuyen
				{
					int trang = 1;
					int maxtrang;
					if (chuyenbaykhadung.SoLuong%10 == 0)
					{
						maxtrang = chuyenbaykhadung.SoLuong/10;
					}
					else
					{
						maxtrang = chuyenbaykhadung.SoLuong/10 + 1;
					}
					gotoxy(25,40);
					cout << "                    ";
					string MaChuyen[chuyenbaykhadung.SoLuong];
					// ======= SAO CHEP ===========
					CacChuyenBay *q = chuyenbaykhadung.Head;
					for (int i = 0; i < chuyenbaykhadung.SoLuong; i++)
					{
						MaChuyen[i] = q->chuyenbay.LayMaChuyen();
						q = q->next;
					}
					if (chuyenbaykhadung.SoLuong == 0)
					{
						CanhGiua(35,15);
						cout << "K co chuyen bay";
						Sleep(500);
						CanhGiua(35,15);
						cout << "               ";
						CanhGiua(35,8);
						cout << "kha dung";
						Sleep(500);
						CanhGiua(35,8);
						cout << "        ";
						gotoxy(0,0);
						KhungChuyenBay();
						x = 72;
						kt = 1;
						kytu = 0;
						line = 4;
						InDanhSachChuyenBay(a,1);
						break;
					}
					else
					{
						AnConTro();
						gotoxy(56,40);
						cout << "-> ";
						gotoxy(wherex(),wherey()-1);
						KhungPopUp2();
						gotoxy(0,40);
						CanhGiua(70,13);
						cout << "MA CHUYEN BAY";
						for (int i = 0; i < chuyenbaykhadung.SoLuong; i++)
						{
							string temp = MaChuyen[0];
							for (int j = 0; j < chuyenbaykhadung.SoLuong-1; j++)
							{
								MaChuyen[j] = MaChuyen[j+1];
							}
							MaChuyen[chuyenbaykhadung.SoLuong-1] = temp;
							if (MaChuyen[0] == MaChuyenBay)
							{
								break;
							}
						}
						for (int i = 0; i < chuyenbaykhadung.SoLuong; i++)
						{
							gotoxy(60,42+i);
							cout << "                    ";
							CanhGiua(70,MaChuyen[i].length());
							cout << MaChuyen[i];
						}
						// hight light
						ChangeColor(240);
						gotoxy(60,42);
						cout << "                    ";
						CanhGiua(70,MaChuyen[0].length());
						cout << MaChuyen[0];
						ChangeColor(15);
						gotoxy(25,40);
						cout << "                    ";
						CanhGiua(35,MaChuyen[0].length());
						cout << MaChuyen[0];
						HienConTro();
						char s = getch();
						bool kytu1;
						if (s == -32 || s == 0)
						{
							s = getch();
							kytu1 = 0;
						}
						else
						{
							kytu1 = 1;
						}
						while (s != 27)
						{
							if ((s == 75 || s == 77) && !kytu1)
							{
								MaChuyenBay = MaChuyen[0];
								kt = 1;
								x = s;
								kytu = kytu1;
								if (s == 75)
								{
									chuyenbaykhadung.Head = NULL;
									chuyenbaykhadung.Tail = NULL;
									chuyenbaykhadung.SoLuong = 0;
								}
								break;
							}
							if (s == -115 && !kytu1) // Page Up
							{
								if (trang > 1)
								{
									trang--;
									InDanhSachChuyenBay(chuyenbaykhadung,trang);
								}
							//	gotoxy(175,0); cout << "Page UP";
							}
							if (s == -111 && !kytu1)
							{
								if (trang < maxtrang)
								{
									trang++;
									InDanhSachChuyenBay(chuyenbaykhadung,trang);
								}
							}
							if (s == 72 && !kytu1) // Up
							{
								string temp = MaChuyen[chuyenbaykhadung.SoLuong-1];
								for (int i = chuyenbaykhadung.SoLuong-1; i >= 1; i--)
								{
									MaChuyen[i] = MaChuyen[i-1];
								}
								MaChuyen[0] = temp;
							}
							if (s == 80 && kytu1) // Down
							{
								string temp = MaChuyen[chuyenbaykhadung.SoLuong-1];
								for (int i = 0; i < chuyenbaykhadung.SoLuong-1; i++)
								{
									MaChuyen[i] = MaChuyen[i+1];
								}
								MaChuyen[chuyenbaykhadung.SoLuong-1] = temp;
							}
							for (int i = 0; i < chuyenbaykhadung.SoLuong; i++)
							{
								gotoxy(60,42+i);
								cout << "                    ";
								CanhGiua(70,MaChuyen[i].length());
								cout << MaChuyen[i];
							}
							// hight light
							ChangeColor(240);
							gotoxy(60,42);
							cout << "                    ";
							CanhGiua(70,MaChuyen[0].length());
							cout << MaChuyen[0];
							ChangeColor(15);
							gotoxy(25,40);
							cout << "                    ";
							CanhGiua(35,MaChuyen[0].length());
							cout << MaChuyen[0];
							HienConTro();
							s = getch();
							if (s == -32 || s == 0)
							{
								s = getch();
								kytu1 = 0;
							}
							else
							{
								kytu1 = 1;
							}
						}
						if (s == 27)
						{
							x = 27;
							kt = 1;
						}
					}
					gotoxy(56,40);
					cout << "   ";
					gotoxy(wherex(),wherey()-1);
					ClearKhungPopUp2();
					break;
				}
			case 6: // So Ghe
				{
					CacChuyenBay *q = a.Head;
					for (q = a.Head; q != NULL; q = q->next)
					{
						if (q->chuyenbay.LayMaChuyen() == MaChuyenBay)
						{
							break;
						}
					}
					gotoxy(56,40);
					SoGhe = ChonGhe(a,q,SoGhe);
					if (SoGhe == 0)
					{
						x = 27;
						kt = 1;
					}
					AnConTro();
					ChangeColor(15);
					gotoxy(28,44);
					cout << "     ";
					CanhGiua(30,DoDaiSoDuong(SoGhe));
					cout << SoGhe;
					HienConTro();
					break;
				}
			case 7: // Dat Ve
				{
					gotoxy(25,49);
					ChangeColor(240);
					cout << " DAT VE ";
					AnConTro();
					char s = getch();
					bool kytu1;
					if (s == -32 || s == 0)
					{
						s = getch();
						kytu1 = 0;
					}
					else
					{
						kytu1 = 1;
					}
					while (s != 27)
					{
					//	cout << "Hello";
						if (s == 75 && !kytu1) // Left
						{
							ChangeColor(15);
							gotoxy(25,49);
							cout << " DAT VE ";
							kt = 1;
							x = 75;
							kytu = 0;
							break;
							
						}
						if (s == 13) // Enter
						{
						//	gotoxy(175,0);
						//	cout << KiemTraHanhKhachTrenChuyenBay(a.Head,"341918413");
							KhachHang hanhkhach;
							hanhkhach.CMND = CMND;
							hanhkhach.GioiTinh = GioiTinh;
							hanhkhach.Name = name;
							ThemVaoCayKhachHang(b, hanhkhach); 
							NodeKhachHang *h = b.root;
							gotoxy(175,1);
							cout << h;
							while (h != NULL)
							{
								if (SoSanhCMND(h->HanhKhach.CMND, CMND) == 1) // Du lieu can nhap vao  nho hon data tai p
								{
									h = h->left;
								}
								else
								{
									if (SoSanhCMND(h->HanhKhach.CMND, CMND) == -1)
									{
										h = h->right; // Du lieu can nhap vao lon hon data tai p
									}
									else
									{
										break;
									}
								}
								
							}
						//	gotoxy(175,0);
						//	cout << h;
							CacChuyenBay *q = a.Head;
							for (q = a.Head; q != NULL; q = q->next)
							{
								if (q->chuyenbay.LayMaChuyen() == MaChuyenBay)
								{
									q->chuyenbay.LayDanhSachVe()[SoGhe-1].HanhKhach = h;
								}
							}
						//	system("pause");
							return 1;
						}
						s = getch();
						if (s == -32 || s == 0)
						{
							kytu1 = 0;
							s = getch();
						}
						else
						{
							kytu1 = 1;
						}
 					}
					ChangeColor(15);
					if (s == 27)
					{
						x = 27;
						kt = 1;
					}
					break;
				}
		}
		if (!kt)
		{
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
		if (x == 27)
		{
			AnConTro();
			gotoxy(56,35);
			cout << "Ban co muon thoat?"; gotoxy(wherex()-17,wherey()+1);
			cout << "Nhan Y de ";
			ChangeColor(12);
			cout << "THOAT";
			ChangeColor(15);
			cout << ", hoac nhan bat ky phim nao de ";
			ChangeColor(12);
			cout << "HUY";
			ChangeColor(15);
//			HienConTro();
			char s = getch();
			bool kytu1;
			if (s == -32 || s == 0)
			{
				kytu1 = 0;
				s = getch();
			}
			else
			{
				kytu1 = 1;
			}
			if (kytu1 == 1)
			{
				if (InHoa(s) == 89)
				{
					return 0;
				}
			}
			gotoxy(56,35);
			cout << "                  "; gotoxy(wherex()-17,wherey()+1);
			cout << "                                                  ";
			x = 65;
			kytu = 0;
			
		}
	}
}
// ======================= SO LUONG CHUYEN BAY CO THE HUY VE ======================
int SoLuongChuyenBayHuyVe(ListChuyenBay &a)
{
	int SoLuong = 0;
	for (CacChuyenBay *p = a.Head; p != NULL; p = p->next)
	{
		int hh = p->chuyenbay.LayGio().hour;
		int min = p->chuyenbay.LayGio().min;
		int dd = p->chuyenbay.LayNgay().dd;
		int mm = p->chuyenbay.LayNgay().mm;
		int yy = p->chuyenbay.LayNgay().yy;
		if (SoLuongHanhKhachTrenChuyenBay(p) != 0 && KiemTraThoiGian(hh,min,dd,mm,yy))
		{
			SoLuong++;
		}
	}
	return SoLuong;
}
// ===================== LAY DANH SACH CHUYEN BAY CO THE HUY ===========
void LayDanhSachHuyVe(ListChuyenBay &a, string *q)
{
	int dem = 0;
//	gotoxy(175,30);
//	cout << a.Head->chuyenbay.LayMaChuyen();
//	Sleep(1000);
	CacChuyenBay *p;
	for (p = a.Head; p != NULL; p = p->next)
	{
		//cout << ->chuyenbay.LayMaChuyen() << " ";
	//	Sleep(1000);
		int hh = p->chuyenbay.LayGio().hour;
		int min = p->chuyenbay.LayGio().min;
		int dd = p->chuyenbay.LayNgay().dd;
		int mm = p->chuyenbay.LayNgay().mm;
		int yy = p->chuyenbay.LayNgay().yy;
		if (SoLuongHanhKhachTrenChuyenBay(p) != 0 && KiemTraThoiGian(hh,min,dd,mm,yy))
		{
		//	cout << "Day ne: " <<  p->chuyenbay.LayMaChuyen();
			q[dem] = p->chuyenbay.LayMaChuyen();
			dem++;
		}
	}
	return;
}
// =================== HUY VE ===========================
void HuyVe(ListChuyenBay &a, CayKhachHang &caykhachhang)
{
	int maxtrang;
	if (a.SoLuong%10 == 0)
	{
		maxtrang = a.SoLuong/10;
	} 
	else
	{
		maxtrang = a.SoLuong/10 + 1;
	}
	int trang = 1;
	string MaChuyenBay = "";
	InDanhSachChuyenBay(a,1);
	gotoxy(130,0);
	KhungDatVe();
	gotoxy(149,23);
	cout << "                    ";
	gotoxy(wherex()-20,wherey()+1);
	cout << "                    ";
	gotoxy(wherex()-20,wherey()+1);
	cout << "                    ";
	string *chuyenbayhuyve;
	int SoLuong = SoLuongChuyenBayHuyVe(a);
	if (SoLuong != 0)
	{
		chuyenbayhuyve = new string[SoLuong];
		LayDanhSachHuyVe(a,chuyenbayhuyve);
	}
	else
	{
		gotoxy(0,30);
		cout << "Khong co ve de huy";
		Sleep(1000);
		return;
	}
	if (MaChuyenBay.length() != 0)
	{
		for (int i = 0; i <= SoLuong; i++)
		{
			string temp = chuyenbayhuyve[0];
			for (int j = 0; j < SoLuong-1; j++)
			{
				chuyenbayhuyve[j] = chuyenbayhuyve[j+1];
			}
			chuyenbayhuyve[SoLuong-1] = temp;
		}
	}
	AnConTro();
	MaChuyenBay = chuyenbayhuyve[0];
	gotoxy(0,30);
	cout << "MA CHUYEN  ";
	gotoxy(wherex(),wherey()-1);
	char ngangtrong = 196;
	char doctrong = 179;
	char traitrentrong = 218;
	char phaitrentrong = 191;
	char traiduoitrong = 192;
	char phaiduoitrong = 217;
	for (int i = 1; i <= 3; i++ )
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
		gotoxy(wherex()-22,wherey()+1);
	}
	gotoxy(33,30);
	cout << "->  ";
	gotoxy(wherex(),wherey()-1);
	KhungPopUp2();
	gotoxy(0,30);
	CanhGiua(47,9);
	cout << "MA CHUYEN";
	for (int i = 0; i < SoLuong; i++)
	{
		gotoxy(38,32+i);
		cout << "                    ";
		CanhGiua(47,chuyenbayhuyve[i].length());
		cout << chuyenbayhuyve[i];
	}
	ChangeColor(240);
	gotoxy(38,32);
	cout << "                    ";
	CanhGiua(47,chuyenbayhuyve[0].length());
	cout << chuyenbayhuyve[0];
	ChangeColor(15);
	gotoxy(12,30);
	cout << "                    ";
	CanhGiua(22,chuyenbayhuyve[0].length());
	cout << chuyenbayhuyve[0];
	HienConTro();
	char t = getch();
	bool kytu1;
	if (t == -32 || t == 0)
	{
		kytu1 = 0;
		t = getch();
	}
	else
	{
		kytu1 = 1;
	}
	if (t == 27)
		{
			AnConTro();
			gotoxy(75,35);
			cout << "Ban co muon thoat?"; gotoxy(wherex()-17,wherey()+1);
			cout << "Nhan Y de ";
			ChangeColor(12);
			cout << "THOAT";
			ChangeColor(15);
			cout << ", hoac nhan bat ky phim nao de ";
			ChangeColor(12);
			cout << "HUY";
			ChangeColor(15);
//			HienConTro();
			char s = getch();
			bool kytu2;
			if (s == -32 || s == 0)
			{
				kytu2 = 0;
				s = getch();
			}
			else
			{
				kytu2 = 1;
			}
			if (kytu2 == 1)
			{
				if (InHoa(s) == 89)
				{
					return;
				}
			}
			gotoxy(75,35);
			cout << "                  "; gotoxy(wherex()-17,wherey()+1);
			cout << "                                                  ";
			t = 65;
			kytu1 = 1;
		}
	while (t != 27 && t != 13) // Esc
	{
		if (t == 72 && !kytu1) // Up
		{
			string temp = chuyenbayhuyve[SoLuong-1];
			for (int i = SoLuong-1; i >= 1; i--)
			{
				chuyenbayhuyve[i] = chuyenbayhuyve[i-1];
			}
			chuyenbayhuyve[0] = temp;
		}
		if (t == 80 && !kytu1) // Down
		{
			string temp = chuyenbayhuyve[0];
			for (int i = 0; i < SoLuong-1; i++)
			{
				chuyenbayhuyve[i] = chuyenbayhuyve[i+1];
			}
			chuyenbayhuyve[SoLuong-1] = temp;
		}
		if (t == -115 && !kytu1) // Page Up
		{
			if (trang > 1)
			{
				trang--;
				InDanhSachChuyenBay(a,trang);
			}
		}
		if (t == -111 && !kytu1) // Page Down
		{
			if (trang < maxtrang)
			{
				trang++;
				InDanhSachChuyenBay(a,trang);
			}
		}
		for (int i = 0; i < SoLuong; i++)
		{
			gotoxy(38,32+i);
			cout << "                    ";
			CanhGiua(47,chuyenbayhuyve[i].length());
			cout << chuyenbayhuyve[i];
		}
		ChangeColor(240);
		gotoxy(38,32);
		cout << "                    ";
		CanhGiua(47,chuyenbayhuyve[0].length());
		cout << chuyenbayhuyve[0];
		ChangeColor(15);
		gotoxy(12,30);
		cout << "                    ";
		CanhGiua(22,chuyenbayhuyve[0].length());
		cout << chuyenbayhuyve[0];
		HienConTro();
		t = getch();
		if (t == -32 || t == 0)
		{
			kytu1 = 0;
			t = getch();
		}
		else
		{
			kytu1 = 1;
		}
		if (t == 27)
		{
			AnConTro();
			gotoxy(75,35);
			cout << "Ban co muon thoat?"; gotoxy(wherex()-17,wherey()+1);
			cout << "Nhan Y de ";
			ChangeColor(12);
			cout << "THOAT";
			ChangeColor(15);
			cout << ", hoac nhan bat ky phim nao de ";
			ChangeColor(12);
			cout << "HUY";
			ChangeColor(15);
//			HienConTro();
			char s = getch();
			bool kytu2;
			if (s == -32 || s == 0)
			{
				kytu2 = 0;
				s = getch();
			}
			else
			{
				kytu2 = 1;
			}
			if (kytu2 == 1)
			{
				if (InHoa(s) == 89)
				{
					return;
				}
			}
			gotoxy(75,35);
			cout << "                  "; gotoxy(wherex()-17,wherey()+1);
			cout << "                                                  ";
			t = 65;
			kytu1 = 1;
		}
		if (t == 13)
		{
			MaChuyenBay = chuyenbayhuyve[0];
		}
	}
	CacChuyenBay *l;
	for (l = a.Head; l != NULL; l = l->next)
	{
		gotoxy(0,50); 
	//	cout << l->chuyenbay.LayMaChuyen();
	//	cout << MaChuyenBay;
	//	cout << SoLuongChuyenBayHuyVe(a);
		//	Sleep(500);
		if (l->chuyenbay.LayMaChuyen() == MaChuyenBay)
		{
			break;
		//	gotoxy(0,50); 
		//	cout << l->chuyenbay.LayMaChuyen();
		}
	}
	gotoxy(65,30);
	InKhungGhe(l->chuyenbay.LaySoCho());
	int i,j;
	int x = 65;
	int y = 30;
	int so = 1;
		if (l->chuyenbay.LayDanhSachVe()[so-1].HanhKhach != NULL)
		{
			int tungdo = wherex();
			int hoanhdo = wherey();
			ChangeColor(15);
			gotoxy(153,3);
			cout << l->chuyenbay.LayDanhSachVe()[so-1].HanhKhach->HanhKhach.CMND;
			gotoxy(144,7);
			cout << "                                 ";
			string name = l->chuyenbay.LayDanhSachVe()[so-1].HanhKhach->HanhKhach.Name;
			CanhGiua(160,l->chuyenbay.LayDanhSachVe()[so-1].HanhKhach->HanhKhach.Name.length());
			for (int k = 0; k < name.length(); k++)
			{
				if (name[k] == '0')
				{
					cout << ' ';
				}
				else
				{
					cout <<name[k];
				}
			}
			gotoxy(159,11);
			cout << "     ";
			CanhGiua(161,3);
			if (l->chuyenbay.LayDanhSachVe()[so-1].HanhKhach->HanhKhach.GioiTinh == 1)
			{
				cout << "Nam";
			}
			else
			{
				cout << "Nu";
			}
			gotoxy(150,15);
			cout << "                    ";
			CanhGiua(160,l->chuyenbay.LayMaChuyen().length());
			cout << l->chuyenbay.LayMaChuyen();
			gotoxy(153,19);
			cout << "     ";
			CanhGiua(155,DoDaiSoDuong(so));
			cout << so;
			gotoxy(tungdo,hoanhdo);
		}
//	gotoxy(0,0); cout << so;
	if ((so)%4 == 0)
	{
		i = 4;
	}
	else
	{
		i = so%4;
	}
	for ( j = 1; j <= l->chuyenbay.LaySoCho(); j++)
	{
 		if (i == 1 && j == 1)
		{
			gotoxy(x+2,y+2);
		}
		if (i == 2 && j == 1)
		{
			gotoxy(x+2,y+2+2);
		}
		if (i == 3 && j == 1)
		{
			gotoxy(x+2,y+2+2+3);
		}
		if (i == 3 && j == 1)
		{
			gotoxy(x+2,y+2+2+3+2);
		}
		if (j != 1)
		{
			gotoxy(wherex()+4, wherey());
		}
		if ((j-1)*4+i == so)
		{
			if ((j-1)*4+i <= 9)
			{
				ChangeColor(240);
				cout << "0" << (j-1)*4+i;
				ChangeColor(15);
				break;
			}
			else
			{
				ChangeColor(240);
				cout << (j-1)*4+i;
				ChangeColor(15);
				break;
			}
		}
	}
	AnConTro();
	char s = getch();
	bool kytu;
	if (s == -32 || s == 0)
	{
		s = getch();
		kytu = 0;
	}
	else
	{
		kytu = 1;
	}
//	HienConTro();
	if (s == 27)
			{
				int hd = wherex();
				int td = wherey();
				AnConTro();
				ChangeColor(15);
				gotoxy(75,26);
				cout << "Ban co muon thoat?"; gotoxy(wherex()-17,wherey()+1);
				cout << "Nhan Y de ";
				ChangeColor(12);
				cout << "THOAT";
				ChangeColor(15);
				cout << ", hoac nhan bat ky phim nao de ";
				ChangeColor(12);
				cout << "HUY";
				ChangeColor(15);
		//		HienConTro();
				char t = getch();
				bool kytu2;
				if (t == -32 || t == 0)
				{
					kytu2 = 0;
					t = getch();
				}
				else
				{
					kytu2 = 1;
				}
				if (kytu2 == 1)
				{
					if (InHoa(t) == 89)
					{
						return;
					}
				}
				gotoxy(75,26);
				cout << "                  "; gotoxy(wherex()-17,wherey()+1);
				cout << "                                                  ";
				s = 65;
				kytu = 1;
				gotoxy(hd,td);
			}
	while (s != 27  && s != 13) // Enter or Ecs
	{
		int so1 = so;
		int hoanhdo = wherex();
		int tungdo = wherey();
		if (s == 75 && !kytu) // Left
		{
			int hoanhdo = wherex();
			int tungdo = wherey();
		//	int so1 = so;
			while (so-4 > 0)
			{
				so = so-4;
				if (so + 4 == 100)
				{
					gotoxy(wherex()-5,wherey());
				}
				else
				{
					gotoxy(wherex()-4,wherey());
				}
			//	if (p->chuyenbay.LayDanhSachVe()[so-1].HanhKhach == NULL)
			//	{
					break;
			//	} */
			}
		//	if (p->chuyenbay.LayDanhSachVe()[so-1].HanhKhach == NULL)
			{
				int hd = wherex();
				int td = wherey();
				if (so1 == 100) // Unhighlight
				{
					gotoxy(hoanhdo-3,tungdo);
				}
				else
				{
					gotoxy(hoanhdo-2,tungdo);
				}
				ChangeColor(15);
				if (so1 <= 9)
				{
					cout << "0" << so1;
				}
				else
				{
					cout << so1;
				}
				gotoxy(hd-2,td);
				ChangeColor(240); // highlight
			///	gotoxy(wherex()-2,wherey());
				if (so <= 9)
				{
					cout << "0" << so;
				}
				else
				{
					cout << so;
				}
			}
		/*	else
			{
				gotoxy(hoanhdo,tungdo); // back lai cai cu
				ChangeColor(240);
				gotoxy(hoanhdo-2,tungdo);
				if (so1 <= 9)
				{
					cout << "0" << so1;
				}
				else
				{
					cout << so1;
				}
				ChangeColor(15);
				so = so1;
			} */
		}
		if (s == 77 && !kytu) // Right
		{
		//	int so1 = so;
			while (so + 4 <= l->chuyenbay.LaySoCho())
			{
				so = so+4;
				if (so == 100)
				{
					gotoxy(wherex()+5,wherey());
				}
				else
				{
					gotoxy(wherex()+4,wherey());
				}
			//	if (p->chuyenbay.LayDanhSachVe()[so-1].HanhKhach == NULL)
			//	{
					break;
			//	}
			}
		//	if (p->chuyenbay.LayDanhSachVe()[so-1].HanhKhach == NULL)
			{
				int hd = wherex();
				int td = wherey();
				ChangeColor(15);
				if (so1 == 100)
				{
					gotoxy(hoanhdo-3,tungdo);
				}
				else
				{
					gotoxy(hoanhdo-2,tungdo);
				}
				if (so1 <= 9)
				{
					cout << "0" << so1;
				}
				else
				{
					cout << so1;
				}
				if (so == 100)
				{
					gotoxy(hd-3,td);
				}
				else
				{
					gotoxy(hd-2,td);
				}
			//	gotoxy(wherex()-2,wherey());
				ChangeColor(240); // Highlight
				if (so <= 9)
				{
					cout << "0" << so;
				}
				else
				{
					cout << so;
				}
			}
		/*	else
			{
				so = so1;
				if (so == 100)
				{
					gotoxy(hoanhdo-3,tungdo);
				}
				else
				{
					gotoxy(hoanhdo-2,tungdo);
				}
				ChangeColor(240); // Highlight
				if (so <= 9)
				{
					cout << "0" << so;
				}
				else
				{
					cout << so;
				}
			} */
		}
		if (s == 72 && !kytu) // Up
		{
			int hoanhdo = wherex();
			int tungdo = wherey();
			int so1 = so;
			while ((so-1)%4 != 0)
			{
				so = so-1;
				if (so%4 == 2)
				{
					gotoxy(wherex(),wherey()-3);
				}
				else
				{
					if (so+1 == 100)
					{
						gotoxy(wherex()-1,wherey()-2);
					}
					else
					{
						gotoxy(wherex(),wherey()-2);
					}
				}
			//	if(p->chuyenbay.LayDanhSachVe()[so-1].HanhKhach == NULL)
			//	{
					break;
			//	}
			}
	//		if (p->chuyenbay.LayDanhSachVe()[so-1].HanhKhach == NULL)
			{
				int hd = wherex();
				int td = wherey();
				ChangeColor(15);
				if (so+1 == 100)
				{
					gotoxy(hoanhdo-3,tungdo);
					if (so1 <= 9)
					{
						cout << "0" << so1;
					}
					else
					{
						cout << so1;
					}
				}
				else
				{
					gotoxy(hoanhdo-2,tungdo);
					if (so1 <= 9)
					{
						cout << "0" << so1;
					}
					else
					{
						cout << so1;
					}
				}
				gotoxy(hd-2,td);
				ChangeColor(240); // Highlight
				if (so <= 9)
				{
					cout << "0" << so;
				}
				else
				{
					cout << so;
				}
			}
		/*	else
			{
				so = so1;
				if (so == 100)
				{
					gotoxy(hoanhdo-3,tungdo);
				}
				else
				{
					gotoxy(hoanhdo-2,tungdo);
				}
				ChangeColor(240); // Highlight
				if (so <= 9)
				{
					cout << "0" << so;
				}
				else
				{
					cout << so;
				}
			} */
		}
		if (s == 80 && !kytu) // Down
		{
			int hoanhdo = wherex();
			int tungdo = wherey();
			int so1 = so;
			while ((so+1)%4 != 1)
			{
				so = so + 1;
				if (so%4 == 3)
				{
					gotoxy(wherex(),wherey()+3);
				}
				else
				{
					if (so == 100 && l->chuyenbay.LayDanhSachVe()[99].HanhKhach != NULL)
					{
						gotoxy(wherex(),wherey()+2);
					}
					else
					{
						gotoxy(wherex(),wherey()+2);
					}
				}
			//	if (p->chuyenbay.LayDanhSachVe()[so-1].HanhKhach == NULL)
			//	{
					break;
			//	}
			}
		//	if (p->chuyenbay.LayDanhSachVe()[so-1].HanhKhach == NULL)
			{
				int hd = wherex();
				int td = wherey();	
				ChangeColor(15);
				if (so1 == 100)
				{
					gotoxy(hoanhdo-3,tungdo);
				}
				else
				{
					gotoxy(hoanhdo-2,tungdo);
				}
				if (so1 <= 9)
				{
					cout << "0" << so1;
				}
				else
				{
					cout << so1;
				}
				if (so == 100 && so1 == 100)
				{
					gotoxy(hd-3,td);
				}
				else
				{
					gotoxy(hd-2,td);
				}
				ChangeColor(240); // Highlight
				if (so <= 9)
				{
					cout << "0" << so ;
				}
				else
				{
					cout << so;
				}
			}
		/*	else
			{
				so = so1;
				if (so == 100)
				{
					gotoxy(hoanhdo-3,tungdo);
				}
				else
				{
					gotoxy(hoanhdo-2,tungdo);
				}
				ChangeColor(240); // Highlight
				if (so <= 9)
				{
					cout << "0" << so;
				}
				else
				{
					cout << so << "k";
				}
			} */
		}
		if (l->chuyenbay.LayDanhSachVe()[so-1].HanhKhach != NULL)
		{
			int tungdo = wherex();
			int hoanhdo = wherey();
			ChangeColor(15);
			gotoxy(153,3);
			cout << l->chuyenbay.LayDanhSachVe()[so-1].HanhKhach->HanhKhach.CMND;
			gotoxy(144,7);
			cout << "                                 ";
			string name = l->chuyenbay.LayDanhSachVe()[so-1].HanhKhach->HanhKhach.Name;
			CanhGiua(160,l->chuyenbay.LayDanhSachVe()[so-1].HanhKhach->HanhKhach.Name.length());
			for (int k = 0; k < name.length(); k++)
			{
				if (name[k] == '0')
				{
					cout << ' ';
				}
				else
				{
					cout <<name[k];
				}
			}
			gotoxy(159,11);
			cout << "     ";
			CanhGiua(161,3);
			if (l->chuyenbay.LayDanhSachVe()[so-1].HanhKhach->HanhKhach.GioiTinh == 1)
			{
				cout << "Nam";
			}
			else
			{
				cout << "Nu";
			}
			gotoxy(150,15);
			cout << "                    ";
			CanhGiua(160,l->chuyenbay.LayMaChuyen().length());
			cout << l->chuyenbay.LayMaChuyen();
			gotoxy(153,19);
			cout << "     ";
			CanhGiua(155,DoDaiSoDuong(so));
			cout << so;
			gotoxy(tungdo,hoanhdo);
		}
		else
		{
			int tungdo = wherex();
			int hoanhdo = wherey();
			ChangeColor(15);
			gotoxy(153,3);
			cout << "         ";
		//	cout << p->chuyenbay.LayDanhSachVe()[so-1].HanhKhach->HanhKhach.CMND;
			gotoxy(144,7);
			cout << "                                 ";
		//	string name = p->chuyenbay.LayDanhSachVe()[so-1].HanhKhach->HanhKhach.Name;
		/*	CanhGiua(160,p->chuyenbay.LayDanhSachVe()[so-1].HanhKhach->HanhKhach.Name.length());
			for (int k = 0; k < name.length(); k++)
			{
				if (name[k] == '0')
				{
					cout << ' ';
				}
				else
				{
					cout <<name[k];
				}
			} */
			gotoxy(159,11);
			cout << "     ";
		/*	CanhGiua(161,3);
			if (p->chuyenbay.LayDanhSachVe()[so-1].HanhKhach->HanhKhach.GioiTinh == 1)
			{
				cout << "Nam";
			}
			else
			{
				cout << "Nu";
			} */
			gotoxy(150,15);
			cout << "                    ";
		//	CanhGiua(160,p->chuyenbay.LayMaChuyen().length());
		//	cout << p->chuyenbay.LayMaChuyen();
			gotoxy(153,19);
			cout << "     ";
		//	CanhGiua(155,DoDaiSoDuong(so));
		//	cout << so;
			gotoxy(tungdo,hoanhdo);
		}
		s = getch();
		if (s == -32 || s == 0)
		{
			s = getch();
			kytu = 0;
		}
		else
		{
			kytu = 1;
		}
			if (s == 27)
			{
				int hd = wherex();
				int td = wherey();
				AnConTro();
				ChangeColor(15);
				gotoxy(75,26);
				cout << "Ban co muon thoat?"; gotoxy(wherex()-17,wherey()+1);
				cout << "Nhan Y de ";
				ChangeColor(12);
				cout << "THOAT";
				ChangeColor(15);
				cout << ", hoac nhan bat ky phim nao de ";
				ChangeColor(12);
				cout << "HUY";
				ChangeColor(15);
		//		HienConTro();
				char t = getch();
				bool kytu2;
				if (t == -32 || t == 0)
				{
					kytu2 = 0;
					t = getch();
				}
				else
				{
					kytu2 = 1;
				}
				if (kytu2 == 1)
				{
					if (InHoa(t) == 89)
					{
						return;
					}
				}
				gotoxy(75,26);
				cout << "                  "; gotoxy(wherex()-17,wherey()+1);
				cout << "                                                  ";
				s = 65;
				kytu = 1;
				gotoxy(hd,td);
			}
	}
	if (s == 13)
	{
				int hd = wherex();
				int td = wherey();
				AnConTro();
				gotoxy(75,26);
				cout << "Ban co muon HUY VE?"; gotoxy(wherex()-17,wherey()+1);
				cout << "Nhan Y de ";
				ChangeColor(12);
				cout << "HUY VE";
				ChangeColor(15);
				cout << ", hoac nhan bat ky phim nao de ";
				ChangeColor(12);
				cout << "TRO LAI";
				ChangeColor(15);
		//		HienConTro();
				char t = getch();
				bool kytu2;
				if (t == -32 || t == 0)
				{
					kytu2 = 0;
					t = getch();
				}
				else
				{
					kytu2 = 1;
				}
				if (kytu2 == 1)
				{
					if (InHoa(t) == 89)
					{
						delete l->chuyenbay.LayDanhSachVe()[so-1].HanhKhach;
						l->chuyenbay.LayDanhSachVe()[so-1].HanhKhach = NULL;
					}
					return;
				}
				gotoxy(75,26);
				cout << "                  "; gotoxy(wherex()-17,wherey()+1);
				cout << "                                                  ";
	}
}
// ================== SO CHUYEN BAY CO KHACH ==============
int SoLuongChuyenBayCoKhach(ListChuyenBay &a)
{
	int SoLuong = 0;
	for (CacChuyenBay *p = a.Head; p != NULL; p = p->next)
	{
		if (SoLuongHanhKhachTrenChuyenBay(p) != 0)
		{
			SoLuong++;
		}
	}
	return SoLuong;
}
// ==================== CAC CHUYEN BAY CO KHACH ====================
void LayDanhSachChuyenBayCoKhach(ListChuyenBay &a, string *q)
{
	int dem = 0;
	CacChuyenBay *p = new CacChuyenBay;
	for (p = a.Head; p != NULL; p = p->next)
	{
		if (SoLuongHanhKhachTrenChuyenBay(p) != 0)
		{
			q[dem] = p->chuyenbay.LayMaChuyen();
			dem++;
		}
	}
	return;
}
// ==================== GHE CON TRONG CHUYEN BAY ============================
int InGheConTrongChuyenBay(ListChuyenBay &a, string &MaChuyenBay)
{
	string MaChuyen[a.SoLuong];
	int dem = 0;
	for (CacChuyenBay *p = a.Head; p != NULL; p = p->next)
	{
		int hh = p->chuyenbay.LayGio().hour;
		int min = p->chuyenbay.LayGio().min;
		int dd = p->chuyenbay.LayNgay().dd;
		int mm = p->chuyenbay.LayNgay().mm;
		int yy = p->chuyenbay.LayNgay().yy;
		if (KiemTraThoiGian(hh,min,dd,mm,yy))
		{
			MaChuyen[dem] = p->chuyenbay.LayMaChuyen();
			dem++;
		}
	}
	if (dem == 0)
	{
		ChangeColor(12);
		gotoxy(0,0);
		cout << "KHONG CHUYEN BAY KHA DUNG LUC NAY";
		Sleep(500);
		ChangeColor(15);
	}
//	string MaChuyenBay = "";
	for (int i = 0; i <= dem; i++)
	{
		if (MaChuyenBay == MaChuyen[0])
		{
			break;
		}
		string temp = MaChuyen[0];
		for (int j = 0; j < dem-1; j++)
		{
			MaChuyen[j] = MaChuyen[j+1];
		}
		MaChuyen[dem-1] = temp;
	}
	gotoxy(0,2);
	cout << "MA CHUYEN  ";
	gotoxy(wherex(),wherey()-1);
	char ngangtrong = 196;
	char doctrong = 179;
	char traitrentrong = 218;
	char phaitrentrong = 191;
	char traiduoitrong = 192;
	char phaiduoitrong = 217;
	for (int i = 1; i <= 3; i++ )
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
		gotoxy(wherex()-22,wherey()+1);
	}
	gotoxy(33,2);
	cout << "->  ";
	gotoxy(wherex(),wherey()-1);
	KhungPopUp2();
	gotoxy(0,2);
	CanhGiua(48,9);
	cout << "MA CHUYEN";
	for (int i = 0; i <= dem; i++)
	{
		if (MaChuyen[0] == MaChuyenBay)
		{
			break;
		}
		string temp = MaChuyen[0];
		for (int j = 0; j < dem-1; j++)
		{
			MaChuyen[j] = MaChuyen[j+1];
		}
		MaChuyen[dem-1] = temp;
	}
	for (int i = 0; i < dem; i++)
	{
		gotoxy(38,4+i);
		cout << "                    ";
		CanhGiua(48,MaChuyen[i].length());
		cout << MaChuyen[i];
	}
	ChangeColor(240);
	gotoxy(38,4);
	cout << "                    ";
	CanhGiua(48,MaChuyen[0].length());
	cout << MaChuyen[0];
	ChangeColor(15);
	gotoxy(12,2);
	cout << "                    ";
	CanhGiua(22,MaChuyen[0].length());
	cout << MaChuyen[0];
	HienConTro();
	char x = getch();
	bool kytu;
	if (x == -32 || x == 0)
	{
		kytu = 0;
		x = getch();
	}
	else
	{
		kytu = 1;
	}
		if (x == 27)
		{
			AnConTro();
				ChangeColor(15);
				gotoxy(0,15);
				cout << "Ban co muon thoat?"; gotoxy(wherex()-17,wherey()+1);
				cout << "Nhan Y de ";
				ChangeColor(12);
				cout << "THOAT";
				ChangeColor(15);
				cout << ", hoac nhan bat ky phim nao de ";
				ChangeColor(12);
				cout << "HUY";
				ChangeColor(15);
		//		HienConTro();
				char t = getch();
				bool kytu2;
				if (t == -32 || t == 0)
				{
					kytu2 = 0;
					t = getch();
				}
				else
				{
					kytu2 = 1;
				}
				if (kytu2 == 1)
				{
					if (InHoa(t) == 89)
					{
						return 0;
					}
				}
				gotoxy(0,15);
				cout << "                  "; gotoxy(wherex()-17,wherey()+1);
				cout << "                                                  ";
				x = 65;
				kytu = 1;
				//gotoxy(hd,td);
			
		}
		if (x == 13)
		{
			MaChuyenBay = MaChuyen[0];
		}
	while (x != 27 && x != 13) // Esc or Enter
	{
		if (x == 72 && !kytu)
		{
			string temp = MaChuyen[dem-1];
			for (int i = dem-1; i >= 1; i--)
			{
				MaChuyen[i] = MaChuyen[i-1];
			}
			MaChuyen[0] = temp;
		}
		if (x == 80 && !kytu)
		{
			string temp = MaChuyen[0];
			for (int i = 0; i < dem-1; i++)
			{
				MaChuyen[i] = MaChuyen[i+1];
			}
			MaChuyen[dem-1] = temp;
		}
		AnConTro();
		for (int i = 0; i < dem; i++)
		{
			gotoxy(38,4+i);
			cout << "                    ";
			CanhGiua(48,MaChuyen[i].length());
			cout << MaChuyen[i];
		}
		ChangeColor(240);
		gotoxy(38,4);
		cout << "                    ";
		CanhGiua(48,MaChuyen[0].length());
		cout << MaChuyen[0];
		ChangeColor(15);
		gotoxy(12,2);
		cout << "                    ";
		CanhGiua(22,MaChuyen[0].length());
		cout << MaChuyen[0];
		HienConTro();
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
		if (x == 27)
		{
			AnConTro();
			ChangeColor(15);
			gotoxy(0,15);
			cout << "Ban co muon thoat?"; gotoxy(wherex()-17,wherey()+1);
			cout << "Nhan Y de ";
			ChangeColor(12);
			cout << "THOAT";
			ChangeColor(15);
			cout << ", hoac nhan bat ky phim nao de ";
			ChangeColor(12);
			cout << "HUY";
			ChangeColor(15);
		//		HienConTro();
			char t = getch();
			bool kytu2;
			if (t == -32 || t == 0)
			{
				kytu2 = 0;
				t = getch();
			}
			else
			{
				kytu2 = 1;
			}
			if (kytu2 == 1)
			{
				if (InHoa(t) == 89)
				{
					return 1;
				}
			}
			gotoxy(0,15);
			cout << "                  "; gotoxy(wherex()-17,wherey()+1);
			cout << "                                                  ";
			x = 65;
			kytu = 1;
				//gotoxy(hd,td);
			
		}
		if (x == 13)
		{
			MaChuyenBay = MaChuyen[0];
			break;
		}
	}
	CacChuyenBay *q = a.Head;
	for (q = a.Head; q != NULL; q = q->next)
	{
		if (q->chuyenbay.LayMaChuyen() == MaChuyenBay)
		{
			break;
		}
	}
	gotoxy(62,0);
	InGheKhaDung(a,q);
	gotoxy(82,16);
	system("pause");
	gotoxy(62,0);
	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 150; j++)
		{
			cout << " ";
		}
		gotoxy(wherex()-150,wherey()+1);
	}
	gotoxy(82,16);
	cout << "                                ";
	return 1;
}
// ======================== IN DANH SACH HANH KHACH THUOC CHUYEN BAY======================
int InDanhSachHanhKhachThuocChuyenBay(ListChuyenBay &a, string &MaChuyenBay)
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
	string *MaChuyen;
	int dem = SoLuongChuyenBayCoKhach(a);
	if (dem != 0)
	{
		MaChuyen = new string[dem];
		LayDanhSachChuyenBayCoKhach(a,MaChuyen);
	}
	else
	{
		gotoxy(0,30);
		cout << "Khong co chuyen bay kha dung";
		Sleep(1000);
		return 0;
	}
	if (MaChuyenBay.length() != 0)
	{
		for (int i = 0; i <= dem; i++)
		{
			string temp = MaChuyen[0];
			for (int j = 0; j < dem-1; j++)
			{
				MaChuyen[j] = MaChuyen[j+1];
			}
			MaChuyen[dem-1] = temp;
		}
	}
	gotoxy(0,2);
	cout << "MA CHUYEN  ";
	gotoxy(wherex(),wherey()-1);
/* 	char ngangtrong = 196;
	char doctrong = 179; */
	char traitrentrong = 218;
	char phaitrentrong = 191;
	char traiduoitrong = 192;
	char phaiduoitrong = 217; 
	for (int i = 1; i <= 3; i++ )
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
		gotoxy(wherex()-22,wherey()+1);
	}
		gotoxy(33,2);
	cout << "->  ";
	gotoxy(wherex(),wherey()-1);
	KhungPopUp2();
	gotoxy(0,2);
	CanhGiua(48,9);
	cout << "MA CHUYEN";
	for (int i = 0; i <= dem; i++)
	{
		if (MaChuyen[0] == MaChuyenBay)
		{
			break;
		}
		string temp = MaChuyen[0];
		for (int j = 0; j < dem-1; j++)
		{
			MaChuyen[j] = MaChuyen[j+1];
		}
		MaChuyen[dem-1] = temp;
	}
	for (int i = 0; i < dem; i++)
	{
		gotoxy(38,4+i);
		cout << "                    ";
		CanhGiua(48,MaChuyen[i].length());
		cout << MaChuyen[i];
	}
	ChangeColor(240);
	gotoxy(38,4);
	cout << "                    ";
	CanhGiua(48,MaChuyen[0].length());
	cout << MaChuyen[0];
	ChangeColor(15);
	gotoxy(12,2);
	cout << "                    ";
	CanhGiua(22,MaChuyen[0].length());
	cout << MaChuyen[0];
	HienConTro();
	char x = getch();
	bool kytu;
	if (x == -32 || x == 0)
	{
		kytu = 0;
		x = getch();
	}
	else
	{
		kytu = 1;
	}
		if (x == 27)
		{
			AnConTro();
				ChangeColor(15);
				gotoxy(0,15);
				cout << "Ban co muon thoat?"; gotoxy(wherex()-17,wherey()+1);
				cout << "Nhan Y de ";
				ChangeColor(12);
				cout << "THOAT";
				ChangeColor(15);
				cout << ", hoac nhan bat ky phim nao de ";
				ChangeColor(12);
				cout << "HUY";
				ChangeColor(15);
		//		HienConTro();
				char t = getch();
				bool kytu2;
				if (t == -32 || t == 0)
				{
					kytu2 = 0;
					t = getch();
				}
				else
				{
					kytu2 = 1;
				}
				if (kytu2 == 1)
				{
					if (InHoa(t) == 89)
					{
						return 0;
					}
				}
				gotoxy(0,15);
				cout << "                  "; gotoxy(wherex()-17,wherey()+1);
				cout << "                                                  ";
				x = 65;
				kytu = 1;
				//gotoxy(hd,td);
			
		}
		if (x == 13)
		{
			MaChuyenBay = MaChuyen[0];
		}
	while (x != 27 && x != 13) // Esc or Enter
	{
		if (x == 72 && !kytu)
		{
			string temp = MaChuyen[dem-1];
			for (int i = dem-1; i >= 1; i--)
			{
				MaChuyen[i] = MaChuyen[i-1];
			}
			MaChuyen[0] = temp;
		}
		if (x == 80 && !kytu)
		{
			string temp = MaChuyen[0];
			for (int i = 0; i < dem-1; i++)
			{
				MaChuyen[i] = MaChuyen[i+1];
			}
			MaChuyen[dem-1] = temp;
		}
		AnConTro();
		for (int i = 0; i < dem; i++)
		{
			gotoxy(38,4+i);
			cout << "                    ";
			CanhGiua(48,MaChuyen[i].length());
			cout << MaChuyen[i];
		}
		ChangeColor(240);
		gotoxy(38,4);
		cout << "                    ";
		CanhGiua(48,MaChuyen[0].length());
		cout << MaChuyen[0];
		ChangeColor(15);
		gotoxy(12,2);
		cout << "                    ";
		CanhGiua(22,MaChuyen[0].length());
		cout << MaChuyen[0];
		HienConTro();
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
		if (x == 27)
		{
			AnConTro();
				ChangeColor(15);
				gotoxy(0,15);
				cout << "Ban co muon thoat?"; gotoxy(wherex()-17,wherey()+1);
				cout << "Nhan Y de ";
				ChangeColor(12);
				cout << "THOAT";
				ChangeColor(15);
				cout << ", hoac nhan bat ky phim nao de ";
				ChangeColor(12);
				cout << "HUY";
				ChangeColor(15);
		//		HienConTro();
				char t = getch();
				bool kytu2;
				if (t == -32 || t == 0)
				{
					kytu2 = 0;
					t = getch();
				}
				else
				{
					kytu2 = 1;
				}
				if (kytu2 == 1)
				{
					if (InHoa(t) == 89)
					{
						return 0;
					}
				}
				gotoxy(0,15);
				cout << "                  "; gotoxy(wherex()-17,wherey()+1);
				cout << "                                                  ";
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
				
				//gotoxy(hd,td);
			
		}
		if (x == 13)
		{
			MaChuyenBay = MaChuyen[0];
			break;
		}
	}
	CacChuyenBay *q = a.Head;
	for (q = a.Head; q != NULL; q = q->next)
	{
		if (q->chuyenbay.LayMaChuyen() == MaChuyenBay)
		{
			break;
		}
	}
	int SoLuongHanhKhach = SoLuongHanhKhachTrenChuyenBay(q);
	int STT = 1;
	AnConTro();
	gotoxy(40,0);
	CanhGiua(70+50,45);
	cout << "DANH SACH HANH KHACH THUOC CHUYEN BAY " << q->chuyenbay.LayMaChuyen();
	gotoxy(70,3);
	KhungHanhKhachThuocChuyenBay();
	for (int i = 0; i < q->chuyenbay.LaySoCho(); i++)
	{
		if (q->chuyenbay.LayDanhSachVe()[i].HanhKhach != NULL)
		{
			if (STT <= 10)
			{
				gotoxy(0,2*STT+1+3);
				CanhGiua(70+10,DoDaiSoDuong(STT));
				cout << STT;
				CanhGiua(70+30,DoDaiSoDuong(i+1));
				cout << i+1;
				CanhGiua(70+50,9);
				cout << q->chuyenbay.LayDanhSachVe()[i].HanhKhach->HanhKhach.CMND;
				string name = q->chuyenbay.LayDanhSachVe()[i].HanhKhach->HanhKhach.Name;
				CanhGiua(70+70,name.length());
				for (int j = 0; j < name.length(); j++)
				{
					if (name[j] == '0')
					{
						cout << " ";
					}
					else
					{
						cout << name[j];
					}
				}
				CanhGiua(70+90,3);
				if (q->chuyenbay.LayDanhSachVe()[i].HanhKhach->HanhKhach.GioiTinh == 1)
				{
					cout << "Nam";
				}
				else
				{
					cout << "Nu";
				}
			}
			else
		{
			if (STT < SoLuongHanhKhachTrenChuyenBay(q))
			{
				gotoxy(70,2*STT+3);
				cout << doctrong;
				for (int j = 1; j <= 4; j++)
				{
					cout << "                    " << doctrong;
				}
				cout << "                    " << doctrong;
			//	gotoxy(70)
				//============//
				CanhGiua(70+10,DoDaiSoDuong(STT));
				cout << STT;
				CanhGiua(70+30,DoDaiSoDuong(i+1));
				cout << i+1;
				CanhGiua(70+50,9);
				cout << q->chuyenbay.LayDanhSachVe()[i].HanhKhach->HanhKhach.CMND;
				string name = q->chuyenbay.LayDanhSachVe()[i].HanhKhach->HanhKhach.Name;
				CanhGiua(70+70,name.length());
				for (int j = 0; j < name.length(); j++)
				{
					if (name[j] == '0')
					{
						cout << " ";
					}
					else
					{
						cout << name[j];
					}
				}
				CanhGiua(70+90,3);
				if (q->chuyenbay.LayDanhSachVe()[i].HanhKhach->HanhKhach.GioiTinh == 1)
				{
					cout << "Nam";
				}
				else
				{
					cout << "Nu";
				}
				//===================//
				gotoxy(70,2*STT+1+4);
				cout << docphai;
				for (int j = 1; j <= 4; j ++)
				{
					cout << "                    " << doctrong;
				}
				cout << "                    " << doctrai;
				
			}
			else
			{
				gotoxy(70,2*STT+3);
				cout << doctrong;
				for (int j = 1; j <= 4; j++)
				{
					cout << "                    " << doctrong;
				}
				cout << "                    " << doctrong;
				//gotoxy(70)
				//============//
				CanhGiua(70+10,DoDaiSoDuong(STT));
				cout << STT;
				CanhGiua(70+30,DoDaiSoDuong(i+1));
				cout << i+1;
				CanhGiua(70+50,9);
				cout << q->chuyenbay.LayDanhSachVe()[i].HanhKhach->HanhKhach.CMND;
				string name = q->chuyenbay.LayDanhSachVe()[i].HanhKhach->HanhKhach.Name;
				CanhGiua(70+70,name.length());
				for (int j = 0; j < name.length(); j++)
				{
					if (name[j] == '0')
					{
						cout << " ";
					}
					else
					{
						cout << name[j];
					}
				}
				CanhGiua(70+90,3);
				if (q->chuyenbay.LayDanhSachVe()[i].HanhKhach->HanhKhach.GioiTinh == 1)
				{
					cout << "Nam";
				}
				else
				{
					cout << "Nu";
				}
				//===================//
				gotoxy(70,2*STT+1+4);
				cout << docphai;
				for (int j = 1; j <= 4; j ++)
				{
					for (int k = 1; k <= 20; k++)
					{
						cout << ngangngoai;
					}
					cout <<  traiduoi;
				}
				for (int k = 1; k <= 20; k++)
				{
					cout << ngangngoai;
				}
				cout <<  phaiduoi;
			}
		}
		STT++;
	}
		
	}
	gotoxy(175,3);
	system("pause");
	AnConTro();
	gotoxy(70,0);
	if (SoLuongHanhKhachTrenChuyenBay(q) > 10)
	{
		for (int i = 1; i <= SoLuongHanhKhachTrenChuyenBay(q)*2 + 20 ; i++)
		{
			for (int j = 1; j <= 140; j++)
			{
				cout << " ";
			}
			gotoxy(wherex()-140,wherey()+1);
		}
	}
	else
	{
		for (int i = 1; i <= 30 ; i++)
		{
			for (int j = 1; j <= 140; j++)
			{
				cout << " ";
			}
			gotoxy(wherex()-140,wherey()+1);
		}
	}
//	gotoxy(175,3);
//	cout << "                                  ";
	return 1;
}
// ========================= SO LUOT THUC HIEN CUA CHUYEN BAY ===========================
void SoLuotThucHien(ListChuyenBay &a, ListMayBay &b)
{
	int SoLuot[b.n];
	for (int i = 0; i < b.n; i++)
	{
		SoLuot[i] = 0;
	}
	AnConTro();
	gotoxy(15,0);
	cout << "SO LUOT THUC HIEN CUA CAC MAY BAY";
	gotoxy(25,2);
	for (int i = 0; i < b.n; i++)
	{
		CacChuyenBay *p = a.Head;
		for (p = a.Head; p != NULL; p = p->next)
		{
			if (p->chuyenbay.LaySoHieu() == b.data[i]->LaySoHieu() && p->chuyenbay.LayTrangThai() == 3)
			{
				SoLuot[i]++;
			}
			
		}
	}
//	cout << b.data[i]->LaySoHieu() << ":     " << SoLuot;
//	gotoxy(25,wherey()+2);
	int mang[b.n];
	for (int i = 0; i < b.n; i++)
	{
		mang[i] = i+1;
	}
	for (int i = 0; i < b.n; i++ )
	{
		for (int j = 0; j < b.n - 1; j++)
		{
			if (SoLuot[mang[j]-1] < SoLuot[mang[j+1]-1])
			{
				int temp = mang[j];
				mang[j] = mang[j+1];
				mang[j+1] = temp;
			}
		}
	}
	for (int i = 0; i < b.n; i++)
	{
		cout << b.data[mang[i]-1]->LaySoHieu() << ":     " << SoLuot[mang[i]-1];
		gotoxy(25,wherey()+2);
	}
	gotoxy(15,wherey());
	system("pause");
}
// =================== SO GHE CON TRONG ====================
int SoGheConTrong(CacChuyenBay *p)
{
	int SoLuong = 0;
	for (int i = 0; i < p->chuyenbay.LaySoCho(); i++)
	{
		if (p->chuyenbay.LayDanhSachVe()[i].HanhKhach == NULL)
		{
			SoLuong++;
		}
	}
	return SoLuong;
}
// ================== DANH SACH KHOI HANH TRONG NGAY DEN X =======================
void DanhSachChuyenBayDenX(ListChuyenBay &a)
{
	char ngangtrong = 196;
	char doctrong = 179;
	char traitrentrong = 218;
	char phaitrentrong = 191;
	char traiduoitrong = 192;
	char phaiduoitrong = 217;
	string den = "";
	int dd = 1;
	int mm = 1;
	int yy = 0;
	gotoxy(12,1);
	cout << "CHON NGAY";
	gotoxy(3,3);
	for (int i = 1; i <= 3; i++ ) // DAYS
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
		gotoxy(wherex()-6,wherey()+1);
	}
	gotoxy(wherex()+8,wherey()-2);
	cout << "/  ";
	gotoxy(wherex(),wherey()-1);
	for (int i = 1; i <= 3; i++ ) // MONTH
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
		gotoxy(wherex()-6,wherey()+1);
	}
	gotoxy(wherex()+8,wherey()-2);
	cout << "/  ";
	gotoxy(wherex(),wherey()-1);
	for (int i = 1; i <= 3; i++ ) // YEAR
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
		gotoxy(wherex()-8,wherey()+1);
	}
	gotoxy(0,8);
	cout << "DEN  ";
	gotoxy(wherex(),wherey()-1);
	for (int i = 1; i <= 3; i++ ) // DEN			
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
					if (j == 1)
					{
						cout << doctrong;
						ChangeColor(8);
						cout << "                    ";
						ChangeColor(15);
						cout << doctrong;
					}
				}
			}
		}
		gotoxy(wherex()-22,wherey()+1);
	}
	gotoxy(12,10);
	for (int i = 1; i <= 3; i++ ) // XEM			
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
					if (j == 1)
					{
						cout << doctrong;
						ChangeColor(8);
						cout << " XEM ";
						ChangeColor(15);
						cout << doctrong;
					}
				}
			}
		}
		gotoxy(wherex()-7,wherey()+1);
	}
	int line = 1;
	char x;
	bool kytu = 1;
	bool kt = 0;
	while (x != 27)
	{
		kt = 0;
		if (x == 75 && !kytu) // Left
		{
			if (line > 1)
			{
				line--;
			}
		}
		if (x == 77 && !kytu)
		{
			if (line < 5)
			{
				line++;
			}
		}
		switch (line)
		{
			case 1: // day
				{
					int max = DaysOfMounth(mm,yy);
					int Ngay[max];
					for (int i = 0; i < max; i++)
					{
						Ngay[i] = i+1;
					}
					for (int i = 0; i <= max; i++)
					{
						if (dd == Ngay[0])
						{
							break;
						}
						int temp = Ngay[0];
						for (int j = 0; j < max-1; j++)
						{
							Ngay[j] = Ngay[j+1];
						}
						Ngay[max-1] = temp;
					} 
					AnConTro();
					gotoxy(34,4);
					cout << "->  ";
					gotoxy(wherex(),wherey()-1);
					KhungPopUp();
					gotoxy(0,4);
					CanhGiua(42,4);
					cout << "NGAY";
					for (int i = 0; i < 10; i++)
					{
						gotoxy(39,6+i);
						cout << "      ";
						CanhGiua(42,2);
						if (Ngay[i] <= 9)
						{
							cout << "0" << Ngay[i];
						}
						else
						{
							cout << Ngay[i];
						}
					}
					ChangeColor(240);
					gotoxy(39,6);
					cout << "      ";
					CanhGiua(42,2);
					if (Ngay[0] <= 9)
					{
						cout << "0" << Ngay[0];
					}
					else
					{
						cout << Ngay[0];
					}
					ChangeColor(15);
					gotoxy(5,4);
					if (dd <= 9)
					{
						cout << "0" << dd;
					}
					else
					{
						cout << dd;
					}
					HienConTro();
					char s = getch();
					bool kytu1;
					if (s == -32 || s == 0)
					{
						s = getch();
						kytu1 = 0;
					}
					else
					{
						kytu1 = 1;
					}
					while (s != 27)
					{
						if (s == 75 && !kytu1) // Left
						{
							x = 75;
							kytu = 0;
							kt = 1;
							dd = Ngay[0];
							break;
						}
						if (s == 77 && !kytu1) // Right
						{
							x = 77;
							kytu = 0;
							kt = 1;
							dd = Ngay[0];
							break;
						}
						if (s == 72 && !kytu1) // Up
						{
							int temp = Ngay[max-1];
							for (int i = max-1; i >= 1; i--)
							{
								Ngay[i] = Ngay[i-1];
							}
							Ngay[0] = temp;
						}
						if (s == 80 && !kytu1)
						{
							int temp = Ngay[0];
							for (int i = 0; i <= max-2; i++)
							{
								Ngay[i] = Ngay[i+1];
							}
							Ngay[max-1]= temp;
						}
						AnConTro();
						for (int i = 0; i < 10; i++)
						{
							gotoxy(39,6+i);
							cout << "      ";
							CanhGiua(42,2);
							if (Ngay[i] <= 9)
							{
								cout << "0" << Ngay[i];
							}
							else
							{
								cout << Ngay[i];
							}
						}
						ChangeColor(240);
						gotoxy(39,6);
						cout << "      ";
						CanhGiua(42,2);
						if (Ngay[0] <= 9)
						{
							cout << "0" << Ngay[0];
						}
						else
						{
							cout << Ngay[0];
						}
						ChangeColor(15);
						gotoxy(5,4);
						if (Ngay[0] <= 9)
						{
							cout << "0" << Ngay[0];
						}
						else
						{
							cout << Ngay[0];
						}
						HienConTro();
						s = getch();
						if (s == -32 || s == 0)
						{
							kytu1 = 0;
							s = getch();
						}
						else
						{
							kytu = 1;
						}
					}
					if (s == 27)
					{
						dd = Ngay[0];
						kt = 1;
						x = 27;
					}
					gotoxy(34,4);
					cout << "    ";
					gotoxy(wherex(),wherey()-1);
					ClearKhungPopUp();
					break;
				}
			case 2: // month
				{
					int Thang[12];
					for (int i = 0; i < 12; i++)
					{
						Thang[i] = i+1;
					}
					for (int i = 0; i <= 12; i++)
					{
						if (mm == Thang[0])
						{
							break;
						}
						int temp = Thang[0];
						for (int j = 0; j < 11; j++)
						{
							Thang[j] = Thang[j+1];
						}
						Thang[11] = temp;
					}
					AnConTro();
					gotoxy(34,4);
					cout << "->  ";
					gotoxy(wherex(),wherey()-1);
					KhungPopUp();
					gotoxy(0,4);
					CanhGiua(42,4);
					cout << "THANG";
					for (int i = 0; i <= 9; i++)
					{
						gotoxy(39,6+i);
						cout << "      ";
						CanhGiua(42,2);
						if (Thang[i] <= 9)
						{
							cout << "0" << Thang[i];
						}
						else
						{
							cout << Thang[i];
						}
					}
					ChangeColor(240);
					gotoxy(39,6);
					cout << "      ";
					CanhGiua(42,2);
					if (Thang[0] <= 9)
					{
						cout << "0" << Thang[0];
					}
					else
					{
						cout << Thang[0];
					}
					ChangeColor(15);
					gotoxy(16,4);
					if (Thang[0] <= 9)
					{
						cout << "0" << Thang[0];
					}
					else
					{
						cout << Thang[0];
					}
					HienConTro();
					char s = getch();
					bool kytu1;
					if (s == -32 || s == 0)
					{
						s = getch();
						kytu1 = 0;
					}
					else
					{
						kytu1 = 1;
					}
					while (s != 27)
					{
						if (s == 75 && !kytu1)
						{
							mm = Thang[0];
							x = 75;
							kytu = 0;
							kt = 1;
							break;
						}
						if (s == 77 && !kytu1)
						{
							mm = Thang[0];
							x = 77;
							kytu = 0;
							kt = 1;
							break;
						}
						if (s == 72 && !kytu1)
						{
							int temp = Thang[11];
							for (int i = 11; i >= 1; i--)
							{
								Thang[i] = Thang[i-1];
							}
							Thang[0] = temp;
						}
						if (s == 80 && !kytu1)
						{
							int temp = Thang[0];
							for (int i = 0; i <= 10; i++)
							{
								Thang[i] = Thang[i+1];
							}
							Thang[11] = temp;
						}
						for (int i = 0; i <= 9; i++)
						{
							gotoxy(39,6+i);
							cout << "      ";
							CanhGiua(42,2);
							if (Thang[i] <= 9)
							{
								cout << "0" << Thang[i];
							}
							else
							{
								cout << Thang[i];
							}
						}
						ChangeColor(240);
						gotoxy(39,6);
						cout << "      ";
						CanhGiua(42,2);
						if (Thang[0] <= 9)
						{
							cout << "0" << Thang[0];
						}
						else
						{
							cout << Thang[0];
						}
						ChangeColor(15);
						gotoxy(16,4);
						if (Thang[0] <= 9)
						{
							cout << "0" << Thang[0];
						}
						else
						{
							cout << Thang[0];
						}
						HienConTro();
						s = getch();
						if (s == -32 || s == 0)
						{
							s = getch();
							kytu1 = 0;
						}
						else
						{
							kytu1 = 1;
						}
					}
					if (s == 27)
					{
						mm = Thang[0];
						kt = 1;
						x = 27;
					}
					gotoxy(34,4);
					cout << "    ";
					gotoxy(wherex(),wherey()-1);
					ClearKhungPopUp();
					if (dd > DaysOfMounth(mm,yy))
					{
						dd = DaysOfMounth(mm,yy);
						gotoxy(5,4);
						cout << dd;
					}
					break;
				}
			case 3: // yy 
				{
					int so = 0;
					gotoxy(34,4);
					cout << "->  ";
					gotoxy(wherex(),wherey()-1);
					KhungPopUp();
					gotoxy(0,4);
					CanhGiua(41,3);
					cout << "NAM";
					if (yy != 0)
					{
						so = yy - 2022;
					}
					yy = so+2022;
					for (int i = 0; i < 4; i++)
					{
						gotoxy(39,6+i);
						cout << "      ";
						CanhGiua(42,4);
						cout << i + 2022;
					}
					ChangeColor(240);
					gotoxy(39,6+so);
					cout << "      ";
					CanhGiua(42,4);
					cout << so+2022;
					ChangeColor(15);
					gotoxy(27,4);
					cout << so+2022;
					HienConTro();
					char s = getch();
					bool kytu1;
					if (s == -32 || s == 0)
					{
						s  = getch();
						kytu1 = 0;
					}
					else
					{
						kytu1 = 1;
					}
					while (s != 27)
					{
						if (s == 75 && !kytu1)
						{
							kt = 1;
							x = 75;
							kytu = 0;
							yy = so+2022;
							break;
						}
						if (s == 77 && !kytu1)
						{
							kt = 1;
							x = 77;
							kytu = 0;
							yy = so + 2022;
							break;
						}
						if (s == 72 && !kytu1) // Up
						{
							if (so > 0)
							{
								so--;
							}
						}
						if (s == 80 && !kytu1)
						{
							if (so < 3)
							{
								so++;
							}
						}
						AnConTro();
						for (int i = 0; i < 4; i++)
						{
							gotoxy(39,6+i);
							cout << "      ";
							CanhGiua(42,4);
							cout << i + 2022;
						}
						ChangeColor(240);
						gotoxy(39,6+so);
						cout << "      ";
						CanhGiua(42,4);
						cout << so+2022;
						ChangeColor(15);
						gotoxy(27,4);
						cout << so+2022;
						HienConTro();
						s = getch();
						if (s == -32 || s == 0)
						{
							s = getch();
							kytu1 = 0;
						}
						else
						{
							kytu1 = 1;
						}
					}
					if (s == 27)
					{
						x = 27;
						kt = 1;
						yy = so+2022;
					}
					gotoxy(34,4);
					cout << "    ";
					gotoxy(wherex(),wherey()-1);
					ClearKhungPopUp();
					if (dd > DaysOfMounth(mm,yy))
					{
						dd = DaysOfMounth(mm,yy);
						gotoxy(5,4);
						cout << dd;
					}
					break;
				}
			case 4: // den
				{
					AnConTro();
					gotoxy(28,8);
					cout << "->  ";
					gotoxy(wherex(),wherey()-1);
					KhungPopUp2();
					gotoxy(0,8);
					CanhGiua(43,3);
					cout << "DEN";
					string Den[21];
					Den[0] = "Vung Tau";
					Den[1] = "Binh Dinh";
					Den[2] = "Ca Mau";
					Den[3] = "Can Tho";
					Den[4] = "Dak Lak";
					Den[5] = "Da Nang";
					Den[6] = "Dien Bien";
					Den[7] = "Gia Lai";
					Den[8] = "Hai Phong";
					Den[9] = "Ha Noi";
					Den[10] = "Khanh Hoa";
					Den[11] = "Rach Gia";
					Den[12] = "Phu Quoc";
					Den[13] = "Lam Dong";
					Den[14] = "Nghe An";
					Den[15] = "Phu Yen";
					Den[16] = "Quang Binh";
					Den[17] = "Quang Nam";
					Den[18] = "Hue";
					Den[19] = "Thanh Hoa";
					Den[20] = "Quang Ninh";
					if (den.length() != 0)
					{
						for (int i = 0; i <= 21; i++)
						{
							if (den == Den[0])
							{
								break;
							}
							string temp = Den[0];
							for (int j = 0; j <= 19; j++)
							{
								Den[j] = Den[j+1];
							}
							Den[20] = temp;
						}
					}
					for (int i = 0; i < 10; i++)
					{
						gotoxy(33,10+i);
						cout << "                    ";
						CanhGiua(43,Den[i].length());
						cout << Den[i];
					}
					ChangeColor(240);
					gotoxy(33,10);
					cout << "                    ";
					CanhGiua(43,Den[0].length());
					cout << Den[0];
					ChangeColor(15);
					gotoxy(6,8);
					cout << "                    ";
					CanhGiua(16,Den[0].length());
					cout << Den[0];
					HienConTro();
					char s = getch();
					bool kytu1;
					if (s == -32 || s == 0)
					{
						s = getch();
						kytu1 = 0;
					}
					else
					{
						kytu1 = 1;
					}
					while (s != 27)
					{
						if (s == 75 && !kytu1)
						{
							x = 75;
							kytu = 0;
							kt = 1;
							den = Den[0];
							break;
						}
						if (s == 77 && !kytu1)
						{
							x = 77;
							kytu = 0;
							kt = 1;
							den = Den[0];
							break;
						}
						if (s == 72 && !kytu1)
						{
							string temp = Den[20];
							for (int i = 20; i >= 1; i--)
							{
								Den[i] = Den[i-1];
							}
							Den[0] = temp;
						}
						if (s == 80 && !kytu1)
						{
							string temp = Den[0];
							for (int i = 0; i <= 19; i++)
							{
								Den[i] = Den[i+1];
							}
							Den[20] = temp;
						}
						AnConTro();
						for (int i = 0; i < 10; i++)
						{
							gotoxy(33,10+i);
							cout << "                    ";
							CanhGiua(43,Den[i].length());
							cout << Den[i];
						}
						ChangeColor(240);
						gotoxy(33,10);
						cout << "                    ";
						CanhGiua(43,Den[0].length());
						cout << Den[0];
						ChangeColor(15);
						gotoxy(6,8);
						cout << "                    ";
						CanhGiua(16,Den[0].length());
						cout << Den[0];
						HienConTro();
						s = getch();
						if (s == -32 || s == 0)
						{
							kytu1 = 0;
							s = getch();
						}
						else
						{
							kytu1 = 1;
						}
					}
					if (s == 27)
					{
						den = Den[0];
						x = 27;
						kt = 1;
					}
					gotoxy(28,8);
					cout << "    ";
					gotoxy(wherex(),wherey()-1);
					ClearKhungPopUp2();
					break;
				}
			case 5: // xem
			{
				AnConTro();
				ChangeColor(240);
				gotoxy(13,11);
				cout << "     ";
				CanhGiua(15,3);
				cout << "XEM";
				char s = getch();
				bool kytu1;
				if (s == -32 || s == 0)
				{
					kytu1 = 0;
					s = getch();
				}
				else
				{
					kytu1 = 1;
				}
				while (s != 27)
				{
					if (s == 75 && !kytu1)
					{
						ChangeColor(15);
						gotoxy(13,11);
						cout << "     ";
						CanhGiua(15,3);
						cout << "XEM";
						x = 75;
						kytu = 0;
						kt = 1;
						break;
					}
					if (s == 13)
					{
						break;
					}
					s = getch();
					if (s == -32 || s == 0)
					{
						kytu1 = 0;
						s = getch();
					}
					else
					{
						kytu1 = 1;
					}
				}
				if (s == 27)
				{
					x = 27;
					kt = 1;
					break;
				}
				if (s == 13)
				{
					ChangeColor(15);
					AnConTro();
				//	gotoxy(44,2);
				//	KhungChuyenBayDenX();
					int hoanhdo = 44;
					int tungdo = 2;
					int SoLuong = 0;
					CacChuyenBay *Mang[a.SoLuong];
					for (CacChuyenBay *p = a.Head; p != NULL; p = p->next)
					{
						string temp = den;
						for (int i = 0; i < den.length();i++)
						{
							if (temp[i] == ' ')
							{
								temp[i] = '0';
							}
						}
						int ngay = p->chuyenbay.LayNgay().dd;
						int thang = p->chuyenbay.LayNgay().mm;
						int nam = p->chuyenbay.LayNgay().yy;
						if (p->chuyenbay.LayTrangThai() == 1 && CountDays(dd,mm,yy,ngay,thang,nam) == 0 && temp == p->chuyenbay.LayDiemDen())
						{
							Mang[SoLuong] = p;
							SoLuong++;
						}
					}
					if (SoLuong == 0)
					{
						gotoxy(54,7);
						ChangeColor(14);
						cout << "Khong chuyen bay kha dung theo yeu cau!";
						Sleep(1000);
						ChangeColor(15);
						gotoxy(54,7);
						cout << "                                       ";
						x = 65;
						kt = 1;
					}
					else
					{
						int trang = 1;
						int maxtrang;
						if (SoLuong%10 == 0)
						{
							maxtrang = SoLuong/10;
						}
						else
						{
							maxtrang = SoLuong/10+1;
						}
						char t = 65;
						bool kytu2;
						while (t != 27)
						{
							if (t == 75 && !kytu2)
							{
								if (trang  > 1)
								{
									trang--;
								}
							}
							if (t == 77 && !kytu2)
							{
								if (trang < maxtrang)
								{
									trang++;
								}
							}
							gotoxy(hoanhdo,tungdo);
							KhungChuyenBayDenX();
							if (trang < maxtrang)
							{
								for (int i = (trang-1)*10; i < (trang-1)*10 + 9; i++)
								{
									gotoxy(0,2*(i%10)+3+tungdo);
									CanhGiua(10+hoanhdo,Mang[i]->chuyenbay.LayMaChuyen().length());
									cout << Mang[i]->chuyenbay.LayMaChuyen();
									CanhGiua(30+hoanhdo,5);
									if (Mang[i]->chuyenbay.LayGio().hour <= 9)
									{
										cout << "0" << Mang[i]->chuyenbay.LayGio().hour;
									}
									else
									{
										cout << Mang[i]->chuyenbay.LayGio().hour;
									}
									cout << ":";
									if (Mang[i]->chuyenbay.LayGio().min <=9)
									{
										cout << "0" << Mang[i]->chuyenbay.LayGio().min;
									}
									else
									{
										cout << Mang[i]->chuyenbay.LayGio().min;
									}
									CanhGiua(hoanhdo+50,DoDaiSoDuong(SoGheConTrong(Mang[i])));
									cout << SoGheConTrong(Mang[i]);
								}
							}
							else
							{
								for (int i = (trang-1)*10; i < SoLuong; i++)
								{
								//	gotoxy(175,0);
								//	cout << Mang[i]->chuyenbay.LayGio().hour;
									gotoxy(0,2*(i%10)+3+tungdo);
									CanhGiua(10+hoanhdo,Mang[i]->chuyenbay.LayMaChuyen().length());
									cout << Mang[i]->chuyenbay.LayMaChuyen();
									CanhGiua(30+hoanhdo,7);
									if (Mang[i]->chuyenbay.LayGio().hour <= 9)
									{
										cout << "0" << Mang[i]->chuyenbay.LayGio().hour;
									}
									else
									{
										cout << Mang[i]->chuyenbay.LayGio().hour;
									}
									cout << ":";
									if (Mang[i]->chuyenbay.LayGio().min <=9)
									{
										cout << "0" << Mang[i]->chuyenbay.LayGio().min;
									}
									else
									{
										cout << Mang[i]->chuyenbay.LayGio().min;
									}
									CanhGiua(hoanhdo+50,DoDaiSoDuong(SoGheConTrong(Mang[i])));
									cout << SoGheConTrong(Mang[i]);
								}
							}
							gotoxy(0,26);
							CanhGiua(78,9);
							cout << "---" << trang << "/" << maxtrang << "---";
							t = getch();
							if (t == -32 || t == 0)
							{
								t = getch();
								kytu2 = 0;
							}
							else
							{
								kytu2 = 1;
							}
						}
						if (t == 27)
						{
							gotoxy(hoanhdo,tungdo);
							for (int i = 1; i <= 26; i++)
							{
								for (int j = 1; j <= 60; j++)
								{
									cout << " ";
								}
								gotoxy(wherex()-60,wherey()+1);
								kt = 1;
								x = 65;
							}
							break;
						}
					}
				}
		
				break;
			}
		}
		if (!kt)
		{
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
		if (x == 27)
		{
			ChangeColor(15);
			gotoxy(0,30);
			cout << "Ban co muon THOAT?";
			cout  << endl << "Nhan Y de ";
			ChangeColor(12);
			cout << "THOAT";
			ChangeColor(15);
			cout << ", hoac nhan BAT KY phim nao de ";
			ChangeColor(12);
			cout << "HUY";
			ChangeColor(15);
			char s = getch();
			bool kytu1;
			if (s == -32 || s == 0)
			{
				kytu1 = 0;
				s = getch();
			}
			else
			{
				kytu1 = 1;
			}
			if (kytu1 == 1)
			{
				if (InHoa(s) == 89)
				{
					return;
				}
			}
			gotoxy(0,30);
			cout << "                                             " << endl << "                                                     ";
			x = 65;
			kytu = 1;
		}
	}
}
#endif
