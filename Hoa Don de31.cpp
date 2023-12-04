#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

//hd: hoá đơn
//hoa_donn : hoá đơn

struct Hoa_don
{
	int hoa_donID;
	string hoa_don_ngay;
	string ten_san_pham;
	double gia_san_pham;
	int so_luong_san_pham;
	double thanh_tien;
};
//Nhập danh sách háo đơn và lưu thành tệp hoddon.dat

void nhap_hoa_don()
{
	int n;
	cout << "Nhap so luong hoa don: ";
	cin >> n;
	
	ofstream outFile("hoadon.dat", ios :: binary);//binary : nhị phân
	if(!outFile)
	{
		cout << "Khong the mo tep ghi" << endl;
		return;
	}

    for(int i = 0; i < n; i++)
    {
    	Hoa_don hoa_don;
    	cout << "Hoa don #" << i + 1 << endl;
    	cout << "Ma hoa don: ";
    	cin >> hoa_don.hoa_donID;
    	cout << "Ngay lap hoa don (7/2016): ";
    	cin >> hoa_don.hoa_don_ngay;
    	cout << "Ten san pham: ";
    	cin.ignore();
    	getline(cin, hoa_don.ten_san_pham);
    	cout << "Gia san pham: ";
    	cin >> hoa_don.gia_san_pham;
    	cout << "So luong san pham: ";
    	cin >> hoa_don.so_luong_san_pham;
    	
    	
    	hoa_don.thanh_tien = hoa_don.gia_san_pham * hoa_don.so_luong_san_pham;
    	outFile.write(reinterpret_cast<const char*>(&hoa_don), sizeof(Hoa_don));
    	
	}
	outFile.close();
}

// Hiển thị danh sách hoá đơn từ tệp hoadon.dat
void hien_thi_Hoa_don()
{
	ifstream inFile("hoadon.dat", ios :: binary); // binary là nhị phân
	if(!inFile)
	{
		cout << "Khong the mo tep de doc!" << endl;
		return;
	}
	cout << endl;
	cout << "Danh sach hoa don: " << endl;
	Hoa_don hoa_don;
	while(inFile.read(reinterpret_cast<char*>(&hoa_don), sizeof(Hoa_don)))
	{
		cout << "Ma hoa don: " << hoa_don.hoa_donID << endl;
		cout << "Ngay lap hoa don: " << hoa_don.hoa_don_ngay << endl;
		cout << "Ten san pham: " << hoa_don.ten_san_pham << endl;
		cout << "Gia san pham: " << hoa_don.gia_san_pham << endl;
		cout << "So luong san pham: " << hoa_don.so_luong_san_pham << endl;
		cout << "Thanh tien: " << hoa_don.thanh_tien << endl;
		cout << "------------------------------" << endl;
	}
	inFile.close();
}

//Sắp xếp và lưu thành danh sách hoá đơn vào tệp sapxep.dat
void sap_xep_hoa_don()
{
	
	ifstream inFile("hoadon.dat", ios :: binary);
	if(!inFile)
	{
		cout << "Khong the mo tep de doc" << endl;
		return;
	}
	
	vector<Hoa_don> hoa_donn;
	Hoa_don hoa_don;
	while (inFile.read(reinterpret_cast<char*>(&hoa_don), sizeof(Hoa_don)))
	{
		hoa_donn.push_back(hoa_don);
	}
	inFile.close();
	
    sort(hoa_donn.begin(), hoa_donn.end(), [](const Hoa_don& a, const Hoa_don& b)
    {
        if (a.hoa_don_ngay == b.hoa_don_ngay) 
        {
            return a.ten_san_pham < b.ten_san_pham;
        }
        return a.hoa_don_ngay < b.hoa_don_ngay;
     }
    );
    
    ofstream outFile("sapxep.dat", ios :: binary);
    if(!outFile)
	{
		cout << "Khong the mo tep ghi" << endl;
		return;
	}
    for(const auto& hd : hoa_donn)
    {
    	outFile.write(reinterpret_cast<const char*>(&hd), sizeof(Hoa_don));
	}
	
	outFile.close();
}

// Tìm hoá đơn có tổng tiền cao nhất và in thông tin chi tiết ra màn hình
void tim_tong_tien_max()
{
	ifstream inFile("hoadon.dat", ios::binary);
	if(!inFile)
	{
		cout << "Khong the mo tep de doc!" << endl;
		return;
	}
	double tong_max = 0;
	Hoa_don max_Hoa_don;
	Hoa_don hoa_don;
	while(inFile.read(reinterpret_cast<char*>(&hoa_don), sizeof(Hoa_don)))
	{
		if(hoa_don.thanh_tien > tong_max)
		{
			tong_max = hoa_don.thanh_tien;
			max_Hoa_don = hoa_don;
		}
	}
	inFile.close();
	
	if (tong_max > 0)
	{
		cout << "Hoa don co tong tien cao nhat: " << endl;
		cout << "Ma hoa don: " << max_Hoa_don.hoa_donID << endl;
		cout << "Ngay lap hoa don: " << max_Hoa_don.hoa_don_ngay << endl;
		cout << "Ten san pham: " << max_Hoa_don.ten_san_pham << endl;
		cout << "Gia san pham: " << max_Hoa_don.gia_san_pham << endl;
		cout << "So luong san pham: " << max_Hoa_don.so_luong_san_pham << endl;
		cout << "Thanh tien: " << max_Hoa_don.thanh_tien << endl;
	}
	else{
		cout << "Khong co hoa don nao!" << endl;
	}
}
int main()
{
	// Gọi các chức năng theo yêu cầu
	nhap_hoa_don();
	hien_thi_Hoa_don();
	sap_xep_hoa_don();
	tim_tong_tien_max();
	
	return 0;
}	



















