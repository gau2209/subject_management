#include<iostream>
#include<string.h>
#include<string>
#include<Windows.h>
#include<iomanip>
#include<fstream>
#include<conio.h>
#include <stdlib.h>
#include <stdio.h>

#pragma warning(disable : 4996)


HANDLE hOut;

using namespace std;

#define MAX 100



struct MonHoc
{
	char MaMH[50];
	char TenMH[100];
	char LoaiMH[50];
	int SoTC;
	char HeDT[50];
};

struct Node
{
	MonHoc key;
	Node* Left;
	Node* Right;
};

typedef Node* Tree;

//struct Stack
//{
//	char a[MAX][MAX];
//	int top;
//};
//
//void init(Stack &s)
//{
//	s.top = -1;
//}
//
//void push(Stack &s, char x[])
//{
//	//s.top++;
//	/*s.a[++s.top] = x;*/
//	strcpy(s.a[++s.top], x);
//}
//
//char *pop(Stack &s)
//{
//	/*int x = s.a[s.top];
//	s.top--;*/
//
//	return s.a[s.top--];
//}
//
//bool isEmpty(Stack s)
//{
//	//if (s.top < 0)
//	//	return true;
//
//	//return false;
//
//	return s.top < 0;
//}
//
//bool isFull(Stack s)
//{
//	return s.top == MAX;
//}
//
//void output(Stack s)
//{
//	for (int i = 0; i <= s.top; i++)
//		cout << s.a[i] << "\t";
//	//cout << endl;
//}

int compare(MonHoc x, MonHoc y)
{
	return strcmp(x.MaMH, y.MaMH);
}

MonHoc NhapMH()
{
	MonHoc x;

	cout << "Nhap Ma Mon Hoc(Q de thoat): ";
	cin.getline(x.MaMH, 50);
	if (strcmp(x.MaMH, "q") == 0 || strcmp(x.MaMH, "Q") == 0)
	{
		return x;
	}

	cout << "Nhap Ten Mon Hoc: ";
	cin.getline(x.TenMH, 100);

	cout << "Nhap Loai Mon Hoc: ";
	cin.getline(x.LoaiMH, 50);

	cout << "Nhap So Tin Chi: ";
	while (1)
	{
		cin >> x.SoTC;
		if (x.SoTC <= 0 || cin.fail()) {
			cin.clear();
			_flushall();
			cin.ignore();
			cout << "Nhap Lai So Tin Chi: ";
		}
		else
			break;
	}


	while (getchar() != '\n');

	cout << "Nhap He Dao Tao: ";
	cin.getline(x.HeDT, 50);

	return x;

}



Tree SuaMH(Tree P)
{
	cout << "Nhap Ten Mon Hoc(Q de thoat): ";
	cin.getline(P->key.TenMH, 100);
	if (strcmp(P->key.TenMH, "q") == 0 || strcmp(P->key.TenMH, "Q") == 0)
	{
		return P;
	}



	cout << "Nhap Loai Mon Hoc: ";
	cin.getline(P->key.LoaiMH, 50);

	cout << "Nhap So Tin Chi: ";
	while (1)
	{
		cin >> P->key.SoTC;
		if (P->key.SoTC <= 0 || cin.fail()) {
			cin.clear();
			_flushall();
			cin.ignore();
			cout << "Nhap Lai So Tin Chi: ";
		}
		else
			break;
	}

	while (getchar() != '\n');

	cout << "Nhap He Dao Tao: ";
	cin.getline(P->key.HeDT, 50);

	return P;
}

int insertNode(Tree& T, MonHoc x)
{
	if (T != NULL)
	{
		if (compare(T->key, x) == 0)
			return -1;
		else if (compare(T->key, x) > 0) return insertNode(T->Left, x);
		else return insertNode(T->Right, x);
	}
	T = (Node*)malloc(sizeof(Node));
	if (T == NULL) return 0;
	T->key = x;
	T->Left = T->Right = NULL;
	return 1;
}


void XuatMH(MonHoc x)
{
	cout << "================================" << endl;
	cout << "Ma Mon Hoc: " << x.MaMH << endl;
	cout << "Ten Mon Hoc: " << x.TenMH << endl;
	cout << "Loai Mon Hoc: " << x.LoaiMH << endl;
	cout << "So Tin Chi: " << x.SoTC << endl;
	cout << "He Dao Tao: " << x.HeDT << endl;
}



void LNR(Tree T)
{
	if (T != NULL)
	{
		LNR(T->Left);
		XuatMH(T->key);
		LNR(T->Right);
	}
}

void LRN(Tree T)
{
	if (T != NULL)
	{
		LNR(T->Left);
		LNR(T->Right);
		XuatMH(T->key);
	}
}

void NLR(Tree T)
{
	if (T != NULL)
	{
		XuatMH(T->key);
		LNR(T->Left);
		LNR(T->Right);
	}
}


void CreateNode(Tree& T)
{
	MonHoc x;
	while (1)
	{
		cout << "--Nhap Thong Tin Mon Hoc Can Them--" << endl << endl;
		x = NhapMH();
		if (strcmp(x.MaMH, "q") == 0 || strcmp(x.MaMH, "Q") == 0)
			break;
		int check = insertNode(T, x);
		if (check == -1)
			cout << "--Ma Mon Hoc Da Co--" << endl;
		else if (check == 0)
			cout << "--Bo Nho Day--" << endl;
		else
			cout << "--Them Thanh Cong--" << endl << endl;
	}
}


Tree searchMH(Tree T, char MaMH[])
{
	Node* P = T;
	if (T != NULL)
	{
		if (strcmp(T->key.MaMH, MaMH) == 0)
		{
			return P;

		}
		else if (strcmp(T->key.MaMH, MaMH) > 0)
		{
			return searchMH(T->Left, MaMH);
		}
		else
			return searchMH(T->Right, MaMH);
	}
	else
		return NULL;
}

int Delete(Tree& T, char MaMH[])
{
	if (T == NULL)
		return 0;
	else if (strcmp(T->key.MaMH, MaMH) > 0)
		return Delete(T->Left, MaMH);
	else if (strcmp(T->key.MaMH, MaMH) < 0)
		return Delete(T->Right, MaMH);
	else // T->key == x
	{
		Node* P = T;
		if (T->Left == NULL)
			T = T->Right;    // Node chi co cay con phai
		else if (T->Right == NULL)
			T = T->Left;   // Node chi co cay con trai
		else // Node co ca 2 con
		{
			Node* S = T, * Q = S->Left;
			// S la cha cua Q, Q la Node phai nhat cua cay con trai cua P
			while (Q->Right != NULL) {
				S = Q;
				Q = Q->Right;
			}
			P->key = Q->key;
			S->Right = Q->Left;
			delete Q;
		}
	}
	return 1;
}

void SearchTC(Tree T, int TC)
{
	if (T == NULL);
	else
	{

		SearchTC(T->Left, TC);
		SearchTC(T->Right, TC);
		if (TC == T->key.SoTC)
		{
			cout << "Tim Thay" << endl;
			cout << "================================" << endl;
			cout << "Ma Mon Hoc: " << T->key.MaMH << endl;
			cout << "Ten Mon Hoc: " << T->key.TenMH << endl;
			cout << "Loai Mon Hoc: " << T->key.LoaiMH << endl;
			cout << "So Tin Chi: " << T->key.SoTC << endl;
			cout << "He Dao Tao: " << T->key.HeDT << endl;
		}
	}
}

int sumTC(Tree T)
{
	if (T == NULL) return 0;
	else
	{
		int left = sumTC(T->Left);
		int right = sumTC(T->Right);
		return (T->key.SoTC + left + right);
	}
	return 0;
}

int CountMH(Tree T, char MH[])
{
	if (T == NULL) return 0;
	else
	{
		int left = CountMH(T->Left, MH);
		int right = CountMH(T->Right, MH);
		if (strcmp(T->key.LoaiMH, MH) == 0) return (1 + left + right);
		else return (left + right);
	}
	return 0;
}

void SearchTMH(Tree T, char TMH[])
{
	if (T == NULL);
	else
	{
		SearchTMH(T->Left, TMH);
		SearchTMH(T->Right, TMH);
		char* p = strstr(T->key.TenMH, TMH);
		if (p)
		{
			cout << "Tim Thay" << endl;
			cout << "================================" << endl;
			cout << "Ma Mon Hoc: " << T->key.MaMH << endl;
			cout << "Ten Mon Hoc: " << T->key.TenMH << endl;
			cout << "Loai Mon Hoc: " << T->key.LoaiMH << endl;
			cout << "So Tin Chi: " << T->key.SoTC << endl;
			cout << "He Dao Tao: " << T->key.HeDT << endl;
		}
		else
			cout << "Khong Tim Thay" << endl;
	}
}

void WayNLR(Tree T)
{
	if (T != NULL)
	{
		cout << T->key.MaMH << "\t";
		WayNLR(T->Left);
		WayNLR(T->Right);
	}
}

void WayLNR(Tree T)
{
	if (T != NULL)
	{
		WayLNR(T->Left);
		cout << T->key.MaMH << "\t";
		WayLNR(T->Right);
	}
}

void WayLRN(Tree T)
{
	if (T != NULL)
	{
		WayLRN(T->Left);
		WayLRN(T->Right);
		cout << T->key.MaMH << "\t";
	}
}


//Node *Array(Tree T, int TC, Node *a[])
//{
//	while (1) {
//		if (T == NULL) break;
//		Node *P = T;
//		if (T != NULL) {
//			SearchTC(T, TC);
//			for (int i = 0; T != NULL; i++)
//			{
//				a[i] = P;
//			}
//			return P;
//		}
//	}
//	return NULL;
//}

//void inputFromFile(Tree &T)
//{
//	MonHoc x;
//	ifstream f;
//	f.open("MonHoc.txt");
//	if (f.is_open())
//	{
//		while (!f.eof())
//		{
//			f.getline(x.MaMH, 50);
//			f.getline(x.TenMH, 100);
//			f.getline(x.LoaiMH, 50);
//			f >> x.SoTC;
//			f.ignore();
//			f.getline(x.HeDT, 50);
//			insertNode(T, x);
//		}
//		f.close();
//		cout << "doc  file thanh cong!\n";
//	}
//	else
//	{
//		cout << "File rong chua co Mon Hoc!" << endl;
//		CreateNode(T);
//	}
//}
//
//int count()
//{
//	int dem = 0;
//	ifstream f;
//	f.open("MonHoc.txt");
//	if (f.is_open())
//	{
//		string tmp; //Dem tam thoi
//		while (getline(f, tmp))
//			if (tmp.length() > 0) //Neu doc duoc 1 dong du lieu thi tmp.length() phai > 0
//				++dem;
//		f.close();
//		return dem;
//	}
//	else return -1;
//}
//
//
//void outputFile(Tree &T)
//{
//	ofstream f("MonHoc.txt");
//	f.open("MonHoc.txt");
//	if (T != NULL) 
//	{
//		f << T->key.MaMH << endl;
//		f << T->key.TenMH << endl;
//		f << T->key.LoaiMH << endl;
//		f << T->key.SoTC << endl;
//		f << T->key.HeDT << endl;
//		outputFile(T->Left);
//		outputFile(T->Right);
//		f.close();
//	}
//
//}



//void Menu()
//{
//	Tree T;
//	int luachon;
//	string tmp;
//	cout << "==================================" << endl << endl;
//	cout << "1. Them Mon Hoc \n"
//		<< "2. Xoa Mon Hoc \n"
//		<< "3. Tim Mon Hoc \n"
//		<< "4. Thong ke Mon Hoc Theo TC \n"
//		<< "5. Dem So Luong Mon Hoc Tung Loai \n"
//		<< "6. Tinh Tong So Tin Chi Cac Mon Hoc \n"
//		<< "0. Thoat \n\n"
//		<< "==================================" << endl << endl;
//	cout << "Lua Chon Cua Ban La: ";
//	while (true)
//	{
//		char c = getch();
//		if (c == '\r')
//		{
//			if (tmp.length() > 0)
//				luachon = stoi(tmp);
//			else continue; //Neu trong truong hop tmp khong nhan so nao thi tiep tuc
//			cout << endl;
//			break;
//		}
//		if (c == '\b') //ma ky tu backspace = 8
//		{
//			if (tmp.length() > 0)
//			{
//				cout << "\b \b";
//				tmp.pop_back();
//			}
//			continue;
//		}
//		if (isdigit(c))
//		{
//			cout << c;
//			tmp += c;
//		}
//	}
//	if (T == NULL && luachon != 1)
//	{
//		cout << "Hien tai khong co Mon Hoc nao !!" << endl;
//		luachon = 1;
//	}
//}

int main()
{
	Tree T = NULL;
	//inputFromFile(T);
	int luachon;
	while (1) {
		string tmp;
		cout << "==================================" << endl << endl;
		cout << "1. Them Mon Hoc \n"
			<< "2. Tim Mon Hoc \n"
			<< "3. Thong ke Mon Hoc Theo TC \n"
			<< "4. Dem So Luong Mon Hoc Tung Loai \n"
			<< "5. Tinh Tong So Tin Chi Cac Mon Hoc \n"
			<< "6. In danh sach Mon Hoc \n"
			<< "7. Tim kiem bang Ten Mon Hoc \n"
			<< "8. Duong di Mon Hoc theo 3 kieu \n"
			<< "9. Luu Mon Hoc \n"
			<< "0. Thoat \n\n"
			<< "==================================" << endl << endl;
		cout << "Lua Chon Cua Ban La: ";
		while (true)
		{
			char c = getch();
			if (c == '\r')
			{
				if (tmp.length() > 0)
					luachon = stoi(tmp);
				else continue; //Neu trong truong hop tmp khong nhan so nao thi tiep tuc
				cout << endl;
				break;
			}
			if (c == '\b') //ma ky tu backspace = 8
			{
				if (tmp.length() > 0)
				{
					cout << "\b \b";
					tmp.pop_back();
				}
				continue;
			}
			if (isdigit(c))
			{
				cout << c;
				tmp += c;
			}
		}
		if (T == NULL && luachon != 1 && luachon != 0)
		{
			cout << "Hien tai khong co Mon Hoc nao !!" << endl;
			luachon = 1;
		}
		switch (luachon)
		{
		case 0:
			system("cls");
			cout << fixed << setw(10) << "======Member======" << endl;
			cout << "1. Trinh Minh Hieu" << endl;
			cout << "2. Tang Phuc Hoang Tai" << endl;
			cout << "3. Vo Huu Anh Tuan" << endl;
			cout << "4. Tang Thi My Lien" << endl;
			cout << fixed << setw(10) << "==================" << endl;
			cout << "Thank For Using Our Service" << endl;
			break;

		case 1:
			cout << "1. Them Mon Hoc" << endl;
			CreateNode(T);
			LNR(T);
			system("pause");
			system("cls");
			break;

		case 2:
		{
			cout << "2. Tim Mon Hoc" << endl;
			char MaMH[50];
			cin.ignore();
			LNR(T);
			cout << endl;
			cout << "Nhap Ma Mon Hoc Can Tim: ";
			cin.getline(MaMH, 50);
			Tree P = searchMH(T, MaMH);

			if (P != NULL)
			{
				int flag;
				string mh;
				cout << "------Tim Thay Mon Hoc " << MaMH << "------" << endl;
				cout << "1. Hien Thi Thong Tin Mon Hoc " << MaMH << endl;
				cout << "2. Sua Thong Tin Mon Hoc " << MaMH << endl;
				cout << "3. Xoa Thong Tin Mon Hoc " << MaMH << endl;
				cout << "4. Quay lai menu chinh " << endl;
				cout << "-------------------------------------------" << endl;
				cout << "Ban chon: ";
				while (true)
				{
					char f = getch();
					if (f == '\r')
					{
						if (mh.length() > 0)
							flag = stoi(mh);
						else continue; //Neu trong truong hop tmp khong nhan so nao thi tiep tuc
						cout << endl;
						break;
					}
					if (f == '\b') //ma ky tu backspace = 8
					{
						if (mh.length() > 0)
						{
							cout << "\b \b";
							mh.pop_back();
						}
						continue;
					}
					if (isdigit(f))
					{
						cout << f;
						mh += f;
					}
				}
				switch (flag)
				{
				case 1:
					cout << "================================" << endl;
					cout << "Ma Mon Hoc: " << P->key.MaMH << endl;
					cout << "Ten Mon Hoc: " << P->key.TenMH << endl;
					cout << "Loai Mon Hoc: " << P->key.LoaiMH << endl;
					cout << "So Tin Chi: " << P->key.SoTC << endl;
					cout << "He Dao Tao: " << P->key.HeDT << endl;

					break;

				case 2:
					cout << "Nhap Thong Tin Can Sua: " << endl;
					cin.ignore();
					SuaMH(P);
					break;

				case 3:
				{
					int del = 1;
					while (1) {
						if (P != NULL)
						{
							cout << "---Xoa Thanh Cong---" << endl;
							del = Delete(T, P->key.MaMH);
						}
						else
						{
							cout << "Khong Co Du Lieu" << endl;
							del = 0;
						}

						system("pause");
						break;
					}
					break;
				}
				case 4:
					cout << "Thoat" << endl;
					system("pause");
					system("cls");
					break;

				default:
					break;
				}

			}
			else
			{
				cout << "Khong Ton Tai Ma Mon Hoc Nay" << endl;
			}

			system("pause");
			system("cls");
			break;
		}
		case 3:
		{
			/*	Node *a[MAX];*/
			int TC;
			cout << "Nhap so TC: ";
			cin >> TC;
			SearchTC(T, TC);
			system("pause");
			system("cls");
			break;
		}
		case 4:
		{
			char MH[50];
			cout << "Nhap Loai Mon Hoc can tim: ";
			cin.getline(MH, 50);
			int countMH = CountMH(T, MH);
			cout << "Loai Mon Hoc " << MH << " Co " << countMH << " Mon" << endl;
			system("pause");
			system("cls");
			break;
		}
		case 5:
		{
			cout << endl;
			cout << "5. Tinh Tong So Tin Chi Cac Mon Hoc \n";
			int sum = sumTC(T);
			cout << "Tong So Tin Chi la: " << sum << endl;
			system("pause");
			system("cls");
			break;
		}
		case 6:
		{
			system("cls");
			cout << "6. In Danh Sach Mon Hoc" << endl;
			cout << "In Mon Hoc theo 3 kieu: " << endl;
			cout << endl;
			cout << "Kieu 1: \n\n";
			LNR(T);
			cout << "\n\n";

			cout << "Kieu 2: \n\n";
			LRN(T);
			cout << "\n\n";

			cout << "Kieu 3: \n\n";
			NLR(T);
			system("pause");
			system("cls");
			break;
		}
		case 7:
		{
			cout << "7. Tim kiem bang Ten Mon Hoc" << endl;
			cout << endl;
			char TMH[50];
			cout << "Nhap Ten MH: ";
			cin.getline(TMH, 50);
			SearchTMH(T, TMH);
			system("pause");
			system("cls");
			break;
		}
		case 8:
		{
			cout << "8. Duong di Mon Hoc theo 3 kieu" << endl;
			cout << endl;
			cout << "Theo kieu Tuan tu: ";
			WayNLR(T);
			cout << endl;
			cout << endl;
			cout << "Theo kieu Trung Tu: ";
			WayLNR(T);
			cout << endl;
			cout << endl;
			cout << "Theo kieu Hau Tu: ";
			WayLRN(T);
			cout << endl;
			system("pause");
			system("cls");
			break;
		}
		default:
		{
			cout << "Khong co chuc nang !!" << endl;
			cout << "Moi Nhap Lai !!" << endl;
			system("pause");
			system("cls");
		}
		/*case 6:
		{
			outputFile(T);
			system("pause");
			break;
		}*/
		}
		if (luachon == 0) break;
	}
	_getch();
	return 0;
}