#include<iostream>
#include<string>
#include"mylib.h"
#include"object.h"
#include"graph.h"
#include<fstream>
using namespace std;
int main()
{
	fullscreen();
	ListMayBay maybay;
	ifstream infile;
	infile.open("dsmaybay.txt");
	infile >> maybay.n;
	for (int i = 0; i < maybay.n; i++) // Doc du lieu cac may bay tu file
	{
		string SoHieu;
		string Loai;
		int SoCho;
		infile >> SoHieu >> Loai >> SoCho;
		maybay.data[i] = CreateData();
		maybay.data[i]->DatSoHieu(SoHieu);
		maybay.data[i]->DatLoai(Loai);
		maybay.data[i]->DatSoCho(SoCho);
	}
	infile.close();

	ListChuyenBay chuyenbay;
	string MaChuyen = "";
	string SoHieu = "";
	string Den = "";
	Day Ngay;
	Time Gio;
	int TrangThai;
	infile.open("dschuyenbay.txt");
	if (infile.fail())
	{
		cout << "That Bai";
		return 0;
	}
	infile >> chuyenbay.SoLuong;
	CacChuyenBay *p = NULL;
	for (int i = 1; i <= chuyenbay.SoLuong; i++)
	{
	//	CacMayBay *temp;
		CacChuyenBay *p = NewChuyenBay();
		if (chuyenbay.Head == NULL)
		{
			chuyenbay.Head = p;
			chuyenbay.Tail = p;
		}
		else
		{
		//	temp = p;
			chuyenbay.Tail->next = p;
			chuyenbay.Tail = p;
		}
		infile >> MaChuyen;
		infile >> SoHieu;
		infile >> Den;
		infile >> Gio.hour;
		infile >> Gio.min;
		infile >> Ngay.dd;
		infile >> Ngay.mm;
		infile >> Ngay.yy;
		infile >> TrangThai;
		p->chuyenbay.DatMaChuyen(MaChuyen);
		p->chuyenbay.DatSoHieu(SoHieu);
		for (int j = 0; j < maybay.n; j++) // Tim chuyen bay co SoHieu trung de copy du lieu
		{
			if (p->chuyenbay.LaySoHieu() == maybay.data[j]->LaySoHieu())
			{
				p->chuyenbay.DatLoai(maybay.data[j]->LayLoai());
				p->chuyenbay.DatSoCho(maybay.data[j]->LaySoCho());
				p->chuyenbay.TaoDanhSachVe();
			}
		}
		p->chuyenbay.DatDiemDen(Den);
		p->chuyenbay.DatGio(Gio);
		p->chuyenbay.DatNgay(Ngay);
		p->chuyenbay.DatTrangThai(TrangThai);
		p = p->next;
	}
	infile.close();
// ========================= DOC DU LIEU HANG KHACH =================================
	CayKhachHang khachhang;
	infile.open("dskhachhang.txt");
//	infile >> khachhang.SoLuong;
	while (infile.eof() == 0)
	{
		if (khachhang.root == NULL)
		{
			khachhang.root = new NodeKhachHang;
			infile >> khachhang.root->HanhKhach.CMND;
			infile >> khachhang.root->HanhKhach.Name;
		//	cout << khachhang.root->HanhKhach.Name << " ";
			infile >> khachhang.root->HanhKhach.GioiTinh;
		}
		else
		{
			string CMND;
			infile >> CMND;
		//	cout << CMND << endl;
			NodeKhachHang *p = khachhang.root;
		//	cout << SoSanhChuoiSo(CMND,p->HanhKhach.CMND);
			while (1)
			{
				if (SoSanhChuoiSo(CMND, p->HanhKhach.CMND) == 1) // lon hon
				{
					if (p->right == NULL)
					{
						p->right = new NodeKhachHang;
						infile >> p->right->HanhKhach.Name;
						infile >> p->right->HanhKhach.GioiTinh;
						p->right->HanhKhach.CMND = CMND;
						p->right->left = NULL;
						p->right->right = NULL;
						break;
					}
					else
					{
						p = p->right;
					}
				}
				else // Khong can truong hop trung CMND vi doc tu file
				{
					if (p->left == NULL)
					{
						p->left = new NodeKhachHang;
						infile >> p->left->HanhKhach.Name;
					//	cout << p->left->HanhKhach.Name << " ";
						infile >> p->left->HanhKhach.GioiTinh;
						p->left->HanhKhach.CMND = CMND;
						p->left->left = NULL;
						p->left->right = NULL;
						break;
					}
					else
					{
						p = p->left;
					}
				}
			} 
		}
	} 
	infile.close();
// ==================== DOC DANH SACH VE ============================
	infile.open("ve.txt");
	CacChuyenBay *t = chuyenbay.Head;
	while (t != NULL)
	{
		string thu;
		infile >> thu;
		if (thu == "-")
		{
			int soghe;
			string duongdan;
			infile >> soghe;
			infile >> duongdan;
			NodeKhachHang *kh = khachhang.root;
			for (int i = 0; i < duongdan.length(); i++)
			{
				if (duongdan[i] == '0')
				{
					kh = kh->left;
				}
				else
				{
					if (duongdan[i] == '1')
					{
						kh = kh->right;
					}
					else
					{
						t->chuyenbay.LayDanhSachVe()[soghe-1].HanhKhach = kh;
						break;
					}
				}
			}
		}
		else
		{
			t = t->next;
		}
	}
	

	XoaManHinh();
//==================================MAIN MENU=====================================
	int a = 1;
	a = MainMenu(a);
	CapNhatTrangThaiChuyenBay(chuyenbay);
	while (a != 0) // Nguoi dung an Esc
	{
		CapNhatTrangThaiChuyenBay(chuyenbay);
		ChangeColor(15);
		XoaManHinh();
		switch(a)
		{
			case 1: // Them may bay
				{
					XoaManHinh();
					int x = ThemMayBay(maybay);
					while (x != -1 )
					{
						XoaManHinh();
						if (x == 0 )
						{
							XoaManHinh();
							cout << "Danh sach day khong the them" << endl;
							system("pause");
						}
						else
						{
							XoaManHinh();
							cout << "Them thanh cong!!!" << endl;
							system("pause");
							
						}
						x = ThemMayBay(maybay);
					}
					break;
				}
			case 2: // Xoa may bay
				{
					XoaManHinh();
					if (!XoaMayBay(maybay,chuyenbay))
					{
						XoaManHinh();
						cout << "Danh sach day khong the xoa" << endl;
						system("pause");
					}
					ChangeColor(15);
					break;
				}
			case 3: // Chinh sua may bay
				{
					ChinhSuaMayBay(maybay,chuyenbay);
					break;
				}
			case 4:
				{
					int x = ThemChuyenBay(chuyenbay,maybay);
					while (x != 0)
					{
						CapNhatTrangThaiChuyenBay(chuyenbay);
						x = ThemChuyenBay(chuyenbay,maybay);
					}
					break;
				}
			case 5:
				{
					ChinhSuaChuyenBay(chuyenbay,maybay);
				//	system("pause");
					ChangeColor(15);
					break;
				}
			case 6:
				{
					DanhSachChuyenBayDenX(chuyenbay);
					break;
				}
			case 7:
				{
					XoaManHinh();
				
					DatVe(chuyenbay,khachhang);
					ChangeColor(15);
		
					break;
				}
			case 8:
				{
					HuyVe(chuyenbay,khachhang);
				//	system("pause");
					break;
				}
			case 9:
				{
					XoaManHinh();
					string MaChuyenBay = "";
					while(InDanhSachHanhKhachThuocChuyenBay(chuyenbay,MaChuyenBay));
				//	system("pause");
					break;
				}
			case 10: // In danh sach chuyen bay
				{
					// Coming soon
					XoaManHinh();
					string MaChuyenBay = "";
					while (InGheConTrongChuyenBay(chuyenbay,MaChuyenBay) != 0);
				//	system("pause");
					break;
				}
			case 11:  // In danh sach may bay
				{
				/*	system("cls");
					int trang = 1;
					InDanhSachMayBay(maybay,trang);
					bool kytu;
					char x;
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
					while (x != 27) // Chua nhan Esc
					{
						if (x == 75 && !kytu) // Left
						{
							if (trang > 1)
							{
								trang--;
							}
						}
						if (x == 77 && !kytu) // Right
						{
							if (maybay.n % 10 != 0)
							{
								if (trang < maybay.n/30 + 1)
								{
									trang++;
								}
							}
							else
							{
								if (trang < maybay.n/10)
								{
									trang++;
								}
							}
						}
						gotoxy(0,0);
						InDanhSachMayBay(maybay,trang);
						x = getch();
						AnConTro();
						if (x == -32 || x == 0)
						{
							kytu = 0;
							x = getch();
						}
						else
						{
							kytu = 1;
						}
					} */
					XoaManHinh();
					SoLuotThucHien(chuyenbay,maybay);
					break;
				}
		}
		XoaManHinh();
		a = MainMenu(a);
	} 
/*	KhungChuyenBay();
	while (1)v
	{
		AnConTro();
		gotoxy(105,1);
		InThoiGian();
	} */
//	CuaSoChuyenBay();
//	ThemChuyenBay(chuyenbay,maybay);
	
	
	ofstream outfile;
	outfile.open("dschuyenbay.txt");
	CacChuyenBay *q;
	outfile << chuyenbay.SoLuong << endl;
	for (q = chuyenbay.Head; q->next != NULL; q = q->next)
	{
		outfile << q->chuyenbay.LayMaChuyen() << endl << q->chuyenbay.LaySoHieu() << endl <<  q->chuyenbay.LayDiemDen() << endl << q->chuyenbay.LayGio().hour << " " << q->chuyenbay.LayGio().min << " " << q->chuyenbay.LayNgay().dd << " " << q->chuyenbay.LayNgay().mm << " " << q->chuyenbay.LayNgay().yy << endl << q->chuyenbay.LayTrangThai() << endl;
	}
	outfile << q->chuyenbay.LayMaChuyen() << endl << q->chuyenbay.LaySoHieu() << endl <<  q->chuyenbay.LayDiemDen() << endl << q->chuyenbay.LayGio().hour << " " << q->chuyenbay.LayGio().min << " " << q->chuyenbay.LayNgay().dd << " " << q->chuyenbay.LayNgay().mm << " " << q->chuyenbay.LayNgay().yy << endl << q->chuyenbay.LayTrangThai();
	outfile.close();

	outfile.open("dsmaybay.txt");
	outfile << maybay.n << endl;
	for (int i = 0; i < maybay.n-1; i++)
	{
		outfile << maybay.data[i]->LaySoHieu() << endl << maybay.data[i]->LayLoai() << endl << maybay.data[i]->LaySoCho() << endl;
	}
	outfile << maybay.data[maybay.n-1]->LaySoHieu() << endl << maybay.data[maybay.n-1]->LayLoai() << endl << maybay.data[maybay.n-1]->LaySoCho();
	outfile.close();

	outfile.open("ve.txt");
	for (CacChuyenBay *h = chuyenbay.Head; h != NULL; h = h->next)
	{
		if (h != chuyenbay.Head)
		{
			outfile << "@" << endl;
		}
	//	outfile << h->chuyenbay.LayMaChuyen();
		for (int i = 0; i < h->chuyenbay.LaySoCho(); i++)
		{
			if (h->chuyenbay.LayDanhSachVe()[i].HanhKhach != NULL)
			{
				string CMND = h->chuyenbay.LayDanhSachVe()[i].HanhKhach->HanhKhach.CMND;
				string duongdan = "";
				NodeKhachHang *k = khachhang.root;
				while (k != NULL)
				{
					if (SoSanhCMND(k->HanhKhach.CMND,CMND) == 1)
					{
						k = k->left;
						duongdan = duongdan + '0';
					}
					else
					{
						if (SoSanhCMND(k->HanhKhach.CMND,CMND) == -1)
						{
							k = k->right;
							duongdan = duongdan + '1';
						}
						else
						{
							duongdan = duongdan + '2';
							break;
						}
					}
				}
				outfile << "- " << i+1 << " " << duongdan << endl;
			}
		}
	}
	outfile << "@";
}	
