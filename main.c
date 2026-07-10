#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

struct User{
    char username[30];
    char password[30];
    char role[20];
};

struct Barang{
    int kodeBarang;
    char namaBarang[50];
    char kategori[30];
    int stok;
    float hargaBeli;
    float hargaJual;
};

struct Supplier{
    int idSupplier;
    char namaSupplier[50];
    char alamat[100];
};

struct Pelanggan{
    int idPelanggan;
    char namaPelanggan[50];
};

struct Transaksi{
    char idTransaksi[20];

    int idPelanggan;
    char namaPelanggan[50];

    int kodeBarang;
    char namaBarang[50];

    int jumlah;
    float harga;
    float subtotal;
};

int login();

void menuManager();
void menuKasir();

void kelolaBarang();
void kelolaSupplier();
void kelolaPelanggan();
void kelolaKasir();

void searchingBarang();
void sortingBarang();

void laporanStok();
void laporanPendapatan();
void laporanBarangTerlaris();
void laporanTransaksi();

void lihatBarang();
void cariBarang();
void transaksiPenjualan();
void riwayatTransaksi();

void garis();
void pauseProgram();

int main(){
    int role;

    do{
        role = login();

        if(role == 1){
            menuManager();
        }
        else if(role == 2){
            menuKasir();
        }
        else{
            printf("\nLogin gagal!\n");
            pauseProgram();
        }

    }while(role == 0);

    return 0;
}

void garis(){
    printf("============================================================\n");
}

void pauseProgram(){
    printf("\nTekan ENTER untuk melanjutkan...");
    getchar();
    getchar();
}

int login(){
    FILE *fp;
    struct User user;

    char username[30];
    char password[30];

    fp = fopen("user.txt","r");

    if(fp == NULL){
        printf("\nFile user.txt tidak ditemukan!\n");
        return 0;
    }

    system("cls");

    garis();
    printf("                 SISTEM MANAJEMEN TOKO\n");
    garis();
    printf("                        LOGIN\n");
    garis();

    printf("Username : ");
    scanf("%s", username);

    printf("Password : ");
    scanf("%s", password);

    while(fscanf(fp,"%[^;];%[^;];%[^\n]\n",
        user.username,
        user.password,
        user.role) != EOF){

        if(strcmp(username,user.username) == 0 &&
           strcmp(password,user.password) == 0){

            fclose(fp);

            if(strcmp(user.role,"MANAGER") == 0){
                return 1;
            }

            if(strcmp(user.role,"KASIR") == 0){
                return 2;
            }
        }
    }

    fclose(fp);
    return 0;
}

void menuManager(){
    int pilih;

    do{
        system("cls");

        garis();
        printf("                    MENU MANAGER\n");
        garis();

        printf("1. Kelola Barang\n");
        printf("2. Kelola Supplier\n");
        printf("3. Kelola Pelanggan\n");
        printf("4. Kelola Kasir\n");
        printf("5. Searching Barang\n");
        printf("6. Sorting Barang\n");
        printf("7. Laporan Stok\n");
        printf("8. Laporan Pendapatan\n");
        printf("9. Laporan Barang Terlaris\n");
        printf("10. Laporan Transaksi\n");
        printf("11. Logout\n");

        garis();

        printf("Pilih Menu : ");
        scanf("%d",&pilih);

        switch(pilih){

            case 1:
                kelolaBarang();
                break;

            case 2:
                kelolaSupplier();
                break;

            case 3:
                kelolaPelanggan();
                break;

            case 4:
                kelolaKasir();
                break;

            case 5:
                searchingBarang();
                break;

            case 6:
                sortingBarang();
                break;

            case 7:
                laporanStok();
                break;

            case 8:
                laporanPendapatan();
                break;

            case 9:
                laporanBarangTerlaris();
                break;

            case 10:
                laporanTransaksi();
                break;

            case 11:
                printf("\nLogout berhasil...\n");
                break;

            default:
                printf("\nMenu tidak tersedia!\n");
                pauseProgram();
        }

    }while(pilih != 11);
}

void menuKasir(){
    int pilih;

    do{
        system("cls");

        garis();
        printf("                     MENU KASIR\n");
        garis();

        printf("1. Lihat Barang\n");
        printf("2. Cari Barang\n");
        printf("3. Transaksi Penjualan\n");
        printf("4. Riwayat Transaksi\n");
        printf("5. Logout\n");

        garis();

        printf("Pilih Menu : ");
        scanf("%d",&pilih);

        switch(pilih){

            case 1:
                lihatBarang();
                break;

            case 2:
                cariBarang();
                break;

            case 3:
                transaksiPenjualan();
                break;

            case 4:
                riwayatTransaksi();
                break;

            case 5:
                printf("\nLogout berhasil...\n");
                break;

            default:
                printf("\nMenu tidak tersedia!\n");
                pauseProgram();
        }

    }while(pilih != 5);
}

void kelolaBarang(){
    printf("\n[MODUL CRUD BARANG - TAHAP 2]\n");
    pauseProgram();
}

void kelolaSupplier(){
    printf("\n[MODUL CRUD SUPPLIER - TAHAP 4]\n");
    pauseProgram();
}

void kelolaPelanggan(){
    printf("\n[MODUL CRUD PELANGGAN - TAHAP 4]\n");
    pauseProgram();
}

void kelolaKasir(){
    printf("\n[MODUL CRUD KASIR - TAHAP 4]\n");
    pauseProgram();
}

void searchingBarang(){
    printf("\n[MODUL SEARCHING - TAHAP 3]\n");
    pauseProgram();
}

void sortingBarang(){
    printf("\n[MODUL SORTING - TAHAP 3]\n");
    pauseProgram();
}

void laporanStok(){
    printf("\n[LAPORAN STOK - TAHAP 6]\n");
    pauseProgram();
}

void laporanPendapatan(){
    printf("\n[LAPORAN PENDAPATAN - TAHAP 6]\n");
    pauseProgram();
}

void laporanBarangTerlaris(){
    printf("\n[LAPORAN BARANG TERLARIS - TAHAP 6]\n");
    pauseProgram();
}

void laporanTransaksi(){
    printf("\n[LAPORAN TRANSAKSI - TAHAP 6]\n");
    pauseProgram();
}

void lihatBarang(){
    printf("\n[LIHAT BARANG - TAHAP 2]\n");
    pauseProgram();
}

void cariBarang(){
    printf("\n[CARI BARANG - TAHAP 3]\n");
    pauseProgram();
}

void transaksiPenjualan(){
    printf("\n[TRANSAKSI PENJUALAN - TAHAP 5]\n");
    pauseProgram();
}

void riwayatTransaksi(){
    printf("\n[RIWAYAT TRANSAKSI - TAHAP 5]\n");
    pauseProgram();
}