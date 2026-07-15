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

void tampilkanSemuaBarang();
void tambahBarang();
void editBarang();
void hapusBarang();
int cariBarangByKode(int kode, struct Barang *hasil);
int cariSupplierById(int id, struct Supplier *hasil);

void tampilkanSemuaSupplier();
void tambahSupplier();
void editSupplier();
void hapusSupplier();

void tampilkanSemuaPelanggan();
void tambahPelanggan();
void editPelanggan();
void hapusPelanggan();

void tampilkanSemuaKasir();
void tambahKasir();
void editKasir();
void hapusKasir();

int cariPelangganById(int id, struct Pelanggan *hasil);
int kurangiStokBarang(int kode, int jumlah);
void cetakStruk(struct Transaksi t);

int inputInt(char pesan[]);
float inputFloat(char pesan[]);
void inputString(char pesan[], char data[], int ukuran);
void bersihkanBuffer();

void tampilkanSemuaTransaksi();
int cariTransaksiById(char idCari[], struct Transaksi *hasil);
void editTransaksi();
void hapusTransaksi();

int tambahStokBarang(int kode,int jumlah);

int main()
{
    int role;

    while(1)
    {
        role = login();

        if(role == 1)
        {
            menuManager();
        }
        else if(role == 2)
        {
            menuKasir();
        }
        else
        {
            printf("\nLogin gagal!\n");
            pauseProgram();
        }
    }

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

void bersihkanBuffer()
{
    while(getchar() != '\n');
}

int inputInt(char pesan[])
{
    int angka;

    while(1)
    {
        printf("%s", pesan);

        if(scanf("%d", &angka) == 1)
        {
            bersihkanBuffer();
            return angka;
        }

        printf("\nInput harus berupa angka!\n");

        bersihkanBuffer();
    }
}

float inputFloat(char pesan[])
{
    float angka;

    while(1)
    {
        printf("%s", pesan);

        if(scanf("%f", &angka) == 1)
        {
            bersihkanBuffer();
            return angka;
        }

        printf("\nInput harus berupa angka!\n");

        bersihkanBuffer();
    }
}

void inputString(char pesan[], char data[], int ukuran)
{
    while(1)
    {
        printf("%s", pesan);

        fgets(data, ukuran, stdin);

        data[strcspn(data, "\n")] = '\0';

        if(strlen(data) == 0)
        {
            printf("\nInput tidak boleh kosong!\n");
            continue;
        }

        return;
    }
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

        pilih = inputInt("Pilih Menu : ");

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
        printf("4. Edit Transaksi\n");
        printf("5. Hapus Transaksi\n");
        printf("6. Riwayat Transaksi\n");
        printf("7. Logout\n");

        garis();

        pilih = inputInt("Pilih Menu : ");

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
                editTransaksi();
                break;

            case 5:
                hapusTransaksi();
                break;

            case 6:
                riwayatTransaksi();
                break;

            case 7:
                printf("\nLogout berhasil...\n");
                break;

            default:
                printf("\nMenu tidak tersedia!\n");
                pauseProgram();
        }
    }while(pilih != 7);
}

void tampilkanSemuaBarang(){
    FILE *fp;
    struct Barang b;
    int no = 1;

    fp = fopen("barang.txt","r");
    if(fp == NULL){
        printf("\nData barang belum ada.\n");
        return;
    }

    garis();
    printf("%-4s%-8s%-20s%-15s%-8s%-12s%-12s\n",
        "No","Kode","Nama Barang","Kategori","Stok","Harga Beli","Harga Jual");
    garis();

    while(fscanf(fp,"%d;%[^;];%[^;];%d;%f;%f\n",
        &b.kodeBarang, b.namaBarang, b.kategori,
        &b.stok, &b.hargaBeli, &b.hargaJual) != EOF){

        printf("%-4d%-8d%-20s%-15s%-8d%-12.0f%-12.0f\n",
            no++, b.kodeBarang, b.namaBarang, b.kategori,
            b.stok, b.hargaBeli, b.hargaJual);
    }
    garis();

    fclose(fp);
}

int cariBarangByKode(int kode, struct Barang *hasil){
    FILE *fp;
    struct Barang b;

    fp = fopen("barang.txt","r");
    if(fp == NULL) return 0;

    while(fscanf(fp,"%d;%[^;];%[^;];%d;%f;%f\n",
        &b.kodeBarang, b.namaBarang, b.kategori,
        &b.stok, &b.hargaBeli, &b.hargaJual) != EOF){

        if(b.kodeBarang == kode){
            *hasil = b;
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

void tambahBarang(){
    FILE *fp;
    struct Barang b;
    struct Barang cek;

    system("cls");
    garis();
    printf("                  TAMBAH BARANG\n");
    garis();

    while(1){
        b.kodeBarang = inputInt("Kode Barang    : ");

        if(b.kodeBarang <= 0){
            printf("\nKode barang harus lebih dari 0!\n\n");
            continue;
        }

        if(cariBarangByKode(b.kodeBarang, &cek)){
            printf("\nKode barang sudah digunakan!\n\n");
            continue;
        }

        break;
    }

    inputString("Nama Barang    : ", b.namaBarang, sizeof(b.namaBarang));

    inputString("Kategori       : ", b.kategori, sizeof(b.kategori));

    while(1){
        b.stok = inputInt("Stok           : ");

        if(b.stok < 0){
            printf("\nStok tidak boleh negatif!\n\n");
        }
        else{
            break;
        }
    }

    while(1){
        b.hargaBeli = inputFloat("Harga Beli     : ");

        if(b.hargaBeli < 0){
            printf("\nHarga beli tidak boleh negatif!\n\n");
        }
        else{
            break;
        }
    }

    while(1){
        b.hargaJual = inputFloat("Harga Jual     : ");

        if(b.hargaJual < 0){
            printf("\nHarga jual tidak boleh negatif!\n\n");
            continue;
        }

        if(b.hargaJual < b.hargaBeli){
            printf("\nHarga jual tidak boleh lebih kecil dari harga beli!\n\n");
            continue;
        }

        break;
    }

    fp = fopen("barang.txt","a");

    if(fp == NULL){
        printf("\nGagal membuka file barang.txt!\n");
        pauseProgram();
        return;
    }

    fprintf(fp,"%d;%s;%s;%d;%.2f;%.2f\n",
            b.kodeBarang,
            b.namaBarang,
            b.kategori,
            b.stok,
            b.hargaBeli,
            b.hargaJual);

    fclose(fp);

    printf("\nBarang berhasil ditambahkan!\n");
    pauseProgram();
}

void editBarang(){
    FILE *fp, *temp;
    struct Barang b;
    int kode, ketemu = 0;

    system("cls");
    garis();
    printf("                   EDIT BARANG\n");
    garis();

    tampilkanSemuaBarang();

    kode = inputInt("\nMasukkan Kode Barang yang akan diedit : ");

    fp = fopen("barang.txt","r");

    if(fp == NULL){
        printf("\nData barang belum ada.\n");
        pauseProgram();
        return;
    }

    temp = fopen("barang_temp.txt","w");

    while(fscanf(fp,"%d;%[^;];%[^;];%d;%f;%f\n",
          &b.kodeBarang,
          b.namaBarang,
          b.kategori,
          &b.stok,
          &b.hargaBeli,
          &b.hargaJual)!=EOF){

        if(b.kodeBarang==kode){

            ketemu=1;

            printf("\nMasukkan data baru\n\n");

            inputString("Nama Barang : ", b.namaBarang, sizeof(b.namaBarang));

            inputString("Kategori    : ", b.kategori, sizeof(b.kategori));

            while(1){

                b.stok=inputInt("Stok         : ");

                if(b.stok>=0)
                    break;

                printf("\nStok tidak boleh negatif!\n\n");
            }

            while(1){

                b.hargaBeli=inputFloat("Harga Beli  : ");

                if(b.hargaBeli>=0)
                    break;

                printf("\nHarga beli tidak boleh negatif!\n\n");
            }

            while(1){

                b.hargaJual=inputFloat("Harga Jual  : ");

                if(b.hargaJual<0){

                    printf("\nHarga jual tidak boleh negatif!\n\n");
                    continue;
                }

                if(b.hargaJual<b.hargaBeli){

                    printf("\nHarga jual tidak boleh lebih kecil dari harga beli!\n\n");
                    continue;
                }

                break;
            }

        }

        fprintf(temp,"%d;%s;%s;%d;%.2f;%.2f\n",
                b.kodeBarang,
                b.namaBarang,
                b.kategori,
                b.stok,
                b.hargaBeli,
                b.hargaJual);
    }

    fclose(fp);
    fclose(temp);

    remove("barang.txt");
    rename("barang_temp.txt","barang.txt");

    if(ketemu)
        printf("\nBarang berhasil diperbarui!\n");
    else
        printf("\nKode barang tidak ditemukan!\n");

    pauseProgram();
}

void hapusBarang(){
    FILE *fp, *temp;
    struct Barang b;
    int kode, ketemu = 0;

    system("cls");
    garis();
    printf("                  HAPUS BARANG\n");
    garis();

    tampilkanSemuaBarang();

    printf("\nMasukkan Kode Barang yang akan dihapus : ");
    scanf("%d",&kode);

    fp = fopen("barang.txt","r");
    if(fp == NULL){
        printf("\nData barang belum ada.\n");
        pauseProgram();
        return;
    }

    temp = fopen("barang_temp.txt","w");

    while(fscanf(fp,"%d;%[^;];%[^;];%d;%f;%f\n",
        &b.kodeBarang, b.namaBarang, b.kategori,
        &b.stok, &b.hargaBeli, &b.hargaJual) != EOF){

        if(b.kodeBarang == kode){
            ketemu = 1;
            continue;
        }

        fprintf(temp,"%d;%s;%s;%d;%.2f;%.2f\n",
            b.kodeBarang, b.namaBarang, b.kategori,
            b.stok, b.hargaBeli, b.hargaJual);
    }

    fclose(fp);
    fclose(temp);

    remove("barang.txt");
    rename("barang_temp.txt","barang.txt");

    if(ketemu){
        printf("\nBarang berhasil dihapus!\n");
    }else{
        printf("\nKode barang tidak ditemukan!\n");
    }

    pauseProgram();
}

void kelolaBarang(){
    int pilih;

    do{
        system("cls");
        garis();
        printf("                  KELOLA BARANG\n");
        garis();

        printf("1. Lihat Semua Barang\n");
        printf("2. Tambah Barang\n");
        printf("3. Edit Barang\n");
        printf("4. Hapus Barang\n");
        printf("5. Kembali ke Menu Manager\n");
        garis();

        pilih = inputInt("Pilih Menu : ");

        switch(pilih){
            case 1:
                system("cls");
                garis();
                printf("                DAFTAR BARANG\n");
                tampilkanSemuaBarang();
                pauseProgram();
                break;
            case 2:
                tambahBarang();
                break;
            case 3:
                editBarang();
                break;
            case 4:
                hapusBarang();
                break;
            case 5:
                break;
            default:
                printf("\nMenu tidak tersedia!\n");
                pauseProgram();
        }

    }while(pilih != 5);
}

void tampilkanSemuaSupplier(){
    FILE *fp;
    struct Supplier s;
    int no = 1;

    fp = fopen("supplier.txt","r");
    if(fp == NULL){
        printf("\nData supplier belum ada.\n");
        return;
    }

    garis();
    printf("%-4s%-6s%-25s%-30s\n","No","ID","Nama Supplier","Alamat");
    garis();

    while(fscanf(fp,"%d;%[^;];%[^\n]\n",
        &s.idSupplier, s.namaSupplier, s.alamat) != EOF){

        printf("%-4d%-6d%-25s%-30s\n",
            no++, s.idSupplier, s.namaSupplier, s.alamat);
    }
    garis();

    fclose(fp);
}

int cariSupplierById(int id, struct Supplier *hasil)
{
    FILE *fp;
    struct Supplier s;

    fp = fopen("supplier.txt", "r");

    if(fp == NULL)
        return 0;

    while(fscanf(fp,"%d;%[^;];%[^\n]\n",
          &s.idSupplier,
          s.namaSupplier,
          s.alamat)!=EOF)
    {

        if(s.idSupplier==id)
        {
            *hasil=s;
            fclose(fp);
            return 1;
        }

    }

    fclose(fp);

    return 0;
}

void tambahSupplier()
{
    FILE *fp;
    struct Supplier s;
    struct Supplier cek;

    system("cls");
    garis();
    printf("                TAMBAH SUPPLIER\n");
    garis();

    while(1)
    {
        s.idSupplier=inputInt("ID Supplier    : ");

        if(s.idSupplier<=0)
        {
            printf("\nID Supplier harus lebih dari 0!\n\n");
            continue;
        }

        if(cariSupplierById(s.idSupplier,&cek))
        {
            printf("\nID Supplier sudah digunakan!\n\n");
            continue;
        }

        break;
    }

    inputString("Nama Supplier  : ",
                s.namaSupplier,
                sizeof(s.namaSupplier));

    inputString("Alamat         : ",
                s.alamat,
                sizeof(s.alamat));

    fp=fopen("supplier.txt","a");

    if(fp==NULL)
    {
        printf("\nGagal membuka file supplier.txt!\n");
        pauseProgram();
        return;
    }

    fseek(fp,0,SEEK_END);

    long ukuran=ftell(fp);

    if(ukuran>0)
    {
        fseek(fp,-1,SEEK_END);

        if(fgetc(fp)!='\n')
            fprintf(fp,"\n");
    }

    fprintf(fp,"%d;%s;%s",
            s.idSupplier,
            s.namaSupplier,
            s.alamat);

    fclose(fp);

    printf("\nSupplier berhasil ditambahkan!\n");

    pauseProgram();
}

void editSupplier()
{
    FILE *fp,*temp;
    struct Supplier s;
    int id;
    int ketemu=0;

    system("cls");
    garis();
    printf("                 EDIT SUPPLIER\n");
    garis();

    tampilkanSemuaSupplier();

    id=inputInt("\nMasukkan ID Supplier yang akan diedit : ");

    fp=fopen("supplier.txt","r");

    if(fp==NULL)
    {
        printf("\nData supplier belum ada.\n");
        pauseProgram();
        return;
    }

    temp=fopen("supplier_temp.txt","w");

    while(fscanf(fp,"%d;%[^;];%[^\n]\n",
          &s.idSupplier,
          s.namaSupplier,
          s.alamat)!=EOF)
    {

        if(s.idSupplier==id)
        {
            ketemu=1;

            printf("\nMasukkan data baru\n\n");

            inputString("Nama Supplier : ",
                        s.namaSupplier,
                        sizeof(s.namaSupplier));

            inputString("Alamat        : ",
                        s.alamat,
                        sizeof(s.alamat));
        }

        fprintf(temp,"%d;%s;%s\n",
                s.idSupplier,
                s.namaSupplier,
                s.alamat);
    }

    fclose(fp);
    fclose(temp);

    remove("supplier.txt");
    rename("supplier_temp.txt","supplier.txt");

    if(ketemu)
        printf("\nSupplier berhasil diperbarui!\n");
    else
        printf("\nID Supplier tidak ditemukan!\n");

    pauseProgram();
}

void hapusSupplier(){
    FILE *fp, *temp;
    struct Supplier s;
    int id, ketemu = 0;

    system("cls");
    garis();
    printf("                HAPUS SUPPLIER\n");
    garis();

    tampilkanSemuaSupplier();

    id = inputInt("\nMasukkan ID Supplier yang akan dihapus : ");

    fp = fopen("supplier.txt","r");
    if(fp == NULL){
        printf("\nData supplier belum ada.\n");
        pauseProgram();
        return;
    }

    temp = fopen("supplier_temp.txt","w");

    while(fscanf(fp,"%d;%[^;];%[^\n]\n",
        &s.idSupplier, s.namaSupplier, s.alamat) != EOF){

        if(s.idSupplier == id){
            ketemu = 1;
            continue;
        }

        fprintf(temp,"%d;%s;%s\n", s.idSupplier, s.namaSupplier, s.alamat);
    }

    fclose(fp);
    fclose(temp);

    remove("supplier.txt");
    rename("supplier_temp.txt","supplier.txt");

    if(ketemu){
        printf("\nSupplier berhasil dihapus!\n");
    }else{
        printf("\nID supplier tidak ditemukan!\n");
    }

    pauseProgram();
}

void kelolaSupplier(){
    int pilih;

    do{
        system("cls");
        garis();
        printf("                 KELOLA SUPPLIER\n");
        garis();

        printf("1. Lihat Semua Supplier\n");
        printf("2. Tambah Supplier\n");
        printf("3. Edit Supplier\n");
        printf("4. Hapus Supplier\n");
        printf("5. Kembali ke Menu Manager\n");
        garis();

        pilih = inputInt("Pilih Menu : ");

        switch(pilih){
            case 1:
                system("cls");
                garis();
                printf("               DAFTAR SUPPLIER\n");
                tampilkanSemuaSupplier();
                pauseProgram();
                break;
            case 2:
                tambahSupplier();
                break;
            case 3:
                editSupplier();
                break;
            case 4:
                hapusSupplier();
                break;
            case 5:
                break;
            default:
                printf("\nMenu tidak tersedia!\n");
                pauseProgram();
        }

    }while(pilih != 5);
}

void tampilkanSemuaPelanggan(){
    FILE *fp;
    struct Pelanggan p;
    int no = 1;

    fp = fopen("pelanggan.txt","r");
    if(fp == NULL){
        printf("\nData pelanggan belum ada.\n");
        return;
    }

    garis();
    printf("%-4s%-6s%-25s\n","No","ID","Nama Pelanggan");
    garis();

    while(fscanf(fp,"%d;%[^\n]\n",
        &p.idPelanggan, p.namaPelanggan) != EOF){

        printf("%-4d%-6d%-25s\n", no++, p.idPelanggan, p.namaPelanggan);
    }
    garis();

    fclose(fp);
}

void tambahPelanggan()
{
    FILE *fp;
    struct Pelanggan p;
    struct Pelanggan cek;

    system("cls");
    garis();
    printf("               TAMBAH PELANGGAN\n");
    garis();

    while(1)
    {
        p.idPelanggan = inputInt("ID Pelanggan    : ");

        if(p.idPelanggan <= 0)
        {
            printf("\nID pelanggan harus lebih dari 0!\n\n");
            continue;
        }

        if(cariPelangganById(p.idPelanggan, &cek))
        {
            printf("\nID pelanggan sudah digunakan!\n\n");
            continue;
        }

        break;
    }

    inputString("Nama Pelanggan  : ",
                p.namaPelanggan,
                sizeof(p.namaPelanggan));

    fp = fopen("pelanggan.txt","a");

    if(fp == NULL)
    {
        printf("\nGagal membuka file pelanggan.txt!\n");
        pauseProgram();
        return;
    }

    fseek(fp,0,SEEK_END);

    if(ftell(fp) > 0)
    {
        fseek(fp,-1,SEEK_END);

        if(fgetc(fp)!='\n')
            fprintf(fp,"\n");
    }

    fprintf(fp,"%d;%s",
            p.idPelanggan,
            p.namaPelanggan);

    fclose(fp);

    printf("\nPelanggan berhasil ditambahkan!\n");

    pauseProgram();
}

void editPelanggan()
{
    FILE *fp,*temp;
    struct Pelanggan p;
    int id;
    int ketemu = 0;

    system("cls");
    garis();
    printf("                EDIT PELANGGAN\n");
    garis();

    tampilkanSemuaPelanggan();

    id = inputInt("\nMasukkan ID Pelanggan yang akan diedit : ");

    fp = fopen("pelanggan.txt","r");

    if(fp == NULL)
    {
        printf("\nData pelanggan belum ada.\n");
        pauseProgram();
        return;
    }

    temp = fopen("pelanggan_temp.txt","w");

    while(fscanf(fp,"%d;%[^\n]\n",
          &p.idPelanggan,
          p.namaPelanggan)!=EOF)
    {

        if(p.idPelanggan == id)
        {
            ketemu = 1;

            printf("\nMasukkan data baru\n\n");

            inputString("Nama Pelanggan : ",
                        p.namaPelanggan,
                        sizeof(p.namaPelanggan));
        }

        fprintf(temp,"%d;%s\n",
                p.idPelanggan,
                p.namaPelanggan);
    }

    fclose(fp);
    fclose(temp);

    remove("pelanggan.txt");
    rename("pelanggan_temp.txt","pelanggan.txt");

    if(ketemu)
        printf("\nPelanggan berhasil diperbarui!\n");
    else
        printf("\nID pelanggan tidak ditemukan!\n");

    pauseProgram();
}

void hapusPelanggan(){
    FILE *fp, *temp;
    struct Pelanggan p;
    int id, ketemu = 0;

    system("cls");
    garis();
    printf("               HAPUS PELANGGAN\n");
    garis();

    tampilkanSemuaPelanggan();

    id = inputInt("\nMasukkan ID Pelanggan yang akan dihapus : ");

    fp = fopen("pelanggan.txt","r");
    if(fp == NULL){
        printf("\nData pelanggan belum ada.\n");
        pauseProgram();
        return;
    }

    temp = fopen("pelanggan_temp.txt","w");

    while(fscanf(fp,"%d;%[^\n]\n",
        &p.idPelanggan, p.namaPelanggan) != EOF){

        if(p.idPelanggan == id){
            ketemu = 1;
            continue;
        }

        fprintf(temp,"%d;%s\n", p.idPelanggan, p.namaPelanggan);
    }

    fclose(fp);
    fclose(temp);

    remove("pelanggan.txt");
    rename("pelanggan_temp.txt","pelanggan.txt");

    if(ketemu){
        printf("\nPelanggan berhasil dihapus!\n");
    }else{
        printf("\nID pelanggan tidak ditemukan!\n");
    }

    pauseProgram();
}

void kelolaPelanggan(){
    int pilih;

    do{
        system("cls");
        garis();
        printf("                KELOLA PELANGGAN\n");
        garis();

        printf("1. Lihat Semua Pelanggan\n");
        printf("2. Tambah Pelanggan\n");
        printf("3. Edit Pelanggan\n");
        printf("4. Hapus Pelanggan\n");
        printf("5. Kembali ke Menu Manager\n");
        garis();

        pilih = inputInt("Pilih Menu : ");

        switch(pilih){
            case 1:
                system("cls");
                garis();
                printf("              DAFTAR PELANGGAN\n");
                tampilkanSemuaPelanggan();
                pauseProgram();
                break;
            case 2:
                tambahPelanggan();
                break;
            case 3:
                editPelanggan();
                break;
            case 4:
                hapusPelanggan();
                break;
            case 5:
                break;
            default:
                printf("\nMenu tidak tersedia!\n");
                pauseProgram();
        }

    }while(pilih != 5);
}

void tampilkanSemuaKasir(){
    FILE *fp;
    struct User u;
    int no = 1;

    fp = fopen("user.txt","r");
    if(fp == NULL){
        printf("\nData user belum ada.\n");
        return;
    }

    garis();
    printf("%-4s%-20s%-20s\n","No","Username","Password");
    garis();

    while(fscanf(fp,"%[^;];%[^;];%[^\n]\n",
        u.username, u.password, u.role) != EOF){

        if(strcmp(u.role,"KASIR") == 0){
            printf("%-4d%-20s%-20s\n", no++, u.username, u.password);
        }
    }
    garis();

    fclose(fp);
}

void tambahKasir()
{
    FILE *fp;
    struct User u;
    struct User cek;
    int adaSama = 0;

    system("cls");
    garis();
    printf("                  TAMBAH KASIR\n");
    garis();

    while(1)
    {
        inputString("Username  : ",
                    u.username,
                    sizeof(u.username));

        fp = fopen("user.txt","r");

        adaSama = 0;

        if(fp != NULL)
        {
            while(fscanf(fp,"%[^;];%[^;];%[^\n]\n",
                  cek.username,
                  cek.password,
                  cek.role)!=EOF)
            {
                if(strcmp(cek.username,u.username)==0)
                {
                    adaSama = 1;
                    break;
                }
            }

            fclose(fp);
        }

        if(adaSama)
        {
            printf("\nUsername sudah digunakan!\n\n");
        }
        else
        {
            break;
        }
    }

    inputString("Password  : ",
                u.password,
                sizeof(u.password));

    strcpy(u.role,"KASIR");

    fp = fopen("user.txt","a");

    if(fp==NULL)
    {
        printf("\nGagal membuka user.txt\n");
        pauseProgram();
        return;
    }

    fseek(fp,0,SEEK_END);

    if(ftell(fp)>0)
    {
        fseek(fp,-1,SEEK_END);

        if(fgetc(fp)!='\n')
            fprintf(fp,"\n");
    }

    fprintf(fp,"%s;%s;%s",
            u.username,
            u.password,
            u.role);

    fclose(fp);

    printf("\nKasir berhasil ditambahkan!\n");

    pauseProgram();
}

void editKasir()
{
    FILE *fp,*temp;
    struct User u;

    char username[30];

    int ketemu = 0;

    system("cls");
    garis();
    printf("                   EDIT KASIR\n");
    garis();

    tampilkanSemuaKasir();

    inputString("\nMasukkan Username Kasir : ",
                username,
                sizeof(username));

    fp = fopen("user.txt","r");

    if(fp==NULL)
    {
        printf("\nData user belum ada.\n");
        pauseProgram();
        return;
    }

    temp = fopen("user_temp.txt","w");

    while(fscanf(fp,"%[^;];%[^;];%[^\n]\n",
          u.username,
          u.password,
          u.role)!=EOF)
    {

        if(strcmp(u.role,"KASIR")==0 &&
           strcmp(u.username,username)==0)
        {
            ketemu = 1;

            printf("\nMasukkan Password Baru\n\n");

            inputString("Password : ",
                        u.password,
                        sizeof(u.password));
        }

        fprintf(temp,"%s;%s;%s\n",
                u.username,
                u.password,
                u.role);
    }

    fclose(fp);
    fclose(temp);

    remove("user.txt");
    rename("user_temp.txt","user.txt");

    if(ketemu)
        printf("\nKasir berhasil diperbarui!\n");
    else
        printf("\nUsername tidak ditemukan!\n");

    pauseProgram();
}

void hapusKasir(){
    FILE *fp, *temp;
    struct User u;
    char username[30];
    int ketemu = 0;

    system("cls");
    garis();
    printf("                  HAPUS KASIR\n");
    garis();

    tampilkanSemuaKasir();

    inputString("\nMasukkan Username Kasir yang akan dihapus : ",
            username,
            sizeof(username));

    fp = fopen("user.txt","r");
    if(fp == NULL){
        printf("\nData user belum ada.\n");
        pauseProgram();
        return;
    }

    temp = fopen("user_temp.txt","w");

    while(fscanf(fp,"%[^;];%[^;];%[^\n]\n",
        u.username, u.password, u.role) != EOF){

        if(strcmp(u.role,"KASIR") == 0 && strcmp(u.username, username) == 0){
            ketemu = 1;
            continue;
        }

        fprintf(temp,"%s;%s;%s\n", u.username, u.password, u.role);
    }

    fclose(fp);
    fclose(temp);

    remove("user.txt");
    rename("user_temp.txt","user.txt");

    if(ketemu){
        printf("\nKasir berhasil dihapus!\n");
    }else{
        printf("\nUsername kasir tidak ditemukan!\n");
    }

    pauseProgram();
}

void kelolaKasir(){
    int pilih;

    do{
        system("cls");
        garis();
        printf("                   KELOLA KASIR\n");
        garis();

        printf("1. Lihat Semua Kasir\n");
        printf("2. Tambah Kasir\n");
        printf("3. Edit Kasir\n");
        printf("4. Hapus Kasir\n");
        printf("5. Kembali ke Menu Manager\n");
        garis();

        pilih = inputInt("Pilih Menu : ");

        switch(pilih){
            case 1:
                system("cls");
                garis();
                printf("                 DAFTAR KASIR\n");
                tampilkanSemuaKasir();
                pauseProgram();
                break;
            case 2:
                tambahKasir();
                break;
            case 3:
                editKasir();
                break;
            case 4:
                hapusKasir();
                break;
            case 5:
                break;
            default:
                printf("\nMenu tidak tersedia!\n");
                pauseProgram();
        }

    }while(pilih != 5);
}

void searchingBarang(){
    int pilih;

    system("cls");
    garis();
    printf("                 SEARCHING BARANG\n");
    garis();

    printf("Cari berdasarkan:\n");
    printf("1. Kode Barang\n");
    printf("2. Nama Barang\n");
    printf("Pilih : ");
    scanf("%d",&pilih);

    if(pilih == 1){
        int kode;
        struct Barang b;

        printf("Masukkan Kode Barang : ");
        scanf("%d",&kode);

        if(cariBarangByKode(kode, &b)){
            printf("\nData ditemukan!\n");
            garis();
            printf("Kode Barang : %d\n", b.kodeBarang);
            printf("Nama Barang : %s\n", b.namaBarang);
            printf("Kategori    : %s\n", b.kategori);
            printf("Stok        : %d\n", b.stok);
            printf("Harga Beli  : %.0f\n", b.hargaBeli);
            printf("Harga Jual  : %.0f\n", b.hargaJual);
            garis();
        }else{
            printf("\nBarang dengan kode %d tidak ditemukan!\n", kode);
        }
    }
    else if(pilih == 2){
        FILE *fp;
        struct Barang b;
        char kataKunci[50];
        int ketemu = 0;

        printf("Masukkan Nama/Kata Kunci Barang : ");
        scanf(" %[^\n]", kataKunci);

        fp = fopen("barang.txt","r");
        if(fp == NULL){
            printf("\nData barang belum ada.\n");
            pauseProgram();
            return;
        }

        garis();
        printf("%-8s%-20s%-15s%-8s%-12s%-12s\n",
            "Kode","Nama Barang","Kategori","Stok","Harga Beli","Harga Jual");
        garis();

        while(fscanf(fp,"%d;%[^;];%[^;];%d;%f;%f\n",
            &b.kodeBarang, b.namaBarang, b.kategori,
            &b.stok, &b.hargaBeli, &b.hargaJual) != EOF){

            if(strstr(b.namaBarang, kataKunci) != NULL){
                ketemu = 1;
                printf("%-8d%-20s%-15s%-8d%-12.0f%-12.0f\n",
                    b.kodeBarang, b.namaBarang, b.kategori,
                    b.stok, b.hargaBeli, b.hargaJual);
            }
        }
        garis();

        fclose(fp);

        if(!ketemu){
            printf("\nTidak ada barang dengan kata kunci \"%s\"\n", kataKunci);
        }
    }
    else{
        printf("\nPilihan tidak tersedia!\n");
    }

    pauseProgram();
}

void sortingBarang(){
    FILE *fp;
    struct Barang data[MAX];
    int n = 0;
    int i, j, pilihField, pilihUrut;
    struct Barang tmp;

    system("cls");
    garis();
    printf("                  SORTING BARANG\n");
    garis();

    fp = fopen("barang.txt","r");
    if(fp == NULL){
        printf("\nData barang belum ada.\n");
        pauseProgram();
        return;
    }

    while(fscanf(fp,"%d;%[^;];%[^;];%d;%f;%f\n",
        &data[n].kodeBarang, data[n].namaBarang, data[n].kategori,
        &data[n].stok, &data[n].hargaBeli, &data[n].hargaJual) != EOF){
        n++;
        if(n >= MAX) break;
    }
    fclose(fp);

    if(n == 0){
        printf("\nData barang kosong.\n");
        pauseProgram();
        return;
    }

    printf("Urutkan berdasarkan:\n");
    printf("1. Nama Barang\n");
    printf("2. Stok\n");
    printf("3. Harga Jual\n");
    printf("Pilih : ");
    scanf("%d",&pilihField);

    printf("\nUrutan:\n");
    printf("1. A-Z / Kecil ke Besar\n");
    printf("2. Z-A / Besar ke Kecil\n");
    printf("Pilih : ");
    scanf("%d",&pilihUrut);

    for(i = 0; i < n-1; i++){
        for(j = 0; j < n-1-i; j++){
            int tukar = 0;

            if(pilihField == 1){
                int cmp = strcmp(data[j].namaBarang, data[j+1].namaBarang);
                if((pilihUrut == 1 && cmp > 0) || (pilihUrut == 2 && cmp < 0)){
                    tukar = 1;
                }
            }
            else if(pilihField == 2){
                if((pilihUrut == 1 && data[j].stok > data[j+1].stok) ||
                   (pilihUrut == 2 && data[j].stok < data[j+1].stok)){
                    tukar = 1;
                }
            }
            else if(pilihField == 3){
                if((pilihUrut == 1 && data[j].hargaJual > data[j+1].hargaJual) ||
                   (pilihUrut == 2 && data[j].hargaJual < data[j+1].hargaJual)){
                    tukar = 1;
                }
            }

            if(tukar){
                tmp = data[j];
                data[j] = data[j+1];
                data[j+1] = tmp;
            }
        }
    }

    system("cls");
    garis();
    printf("             HASIL SORTING BARANG\n");
    garis();
    printf("%-8s%-20s%-15s%-8s%-12s%-12s\n",
        "Kode","Nama Barang","Kategori","Stok","Harga Beli","Harga Jual");
    garis();

    for(i = 0; i < n; i++){
        printf("%-8d%-20s%-15s%-8d%-12.0f%-12.0f\n",
            data[i].kodeBarang, data[i].namaBarang, data[i].kategori,
            data[i].stok, data[i].hargaBeli, data[i].hargaJual);
    }
    garis();

    pauseProgram();
}

void laporanStok(){
    FILE *fp;
    struct Barang b;
    int totalStok = 0;
    int adaData = 0;

    system("cls");
    garis();
    printf("                   LAPORAN STOK\n");
    garis();

    fp = fopen("barang.txt","r");
    if(fp == NULL){
        printf("\nData barang belum ada.\n");
        pauseProgram();
        return;
    }

    printf("%-8s%-20s%-15s%-8s\n","Kode","Nama Barang","Kategori","Stok");
    garis();

    while(fscanf(fp,"%d;%[^;];%[^;];%d;%f;%f\n",
        &b.kodeBarang, b.namaBarang, b.kategori,
        &b.stok, &b.hargaBeli, &b.hargaJual) != EOF){

        adaData = 1;
        totalStok += b.stok;

        printf("%-8d%-20s%-15s%-8d", b.kodeBarang, b.namaBarang, b.kategori, b.stok);

        if(b.stok <= 10){
            printf("  <-- STOK MENIPIS!");
        }
        printf("\n");
    }

    fclose(fp);

    garis();
    if(adaData){
        printf("Total Seluruh Stok Barang : %d\n", totalStok);
    }else{
        printf("Tidak ada data barang.\n");
    }
    garis();

    pauseProgram();
}

void laporanPendapatan(){
    FILE *fp;
    struct Transaksi t;
    float totalPendapatan = 0;
    int jumlahTransaksi = 0;

    system("cls");
    garis();
    printf("                 LAPORAN PENDAPATAN\n");
    garis();

    fp = fopen("transaksi.txt","r");
    if(fp == NULL){
        printf("\nBelum ada data transaksi.\n");
        pauseProgram();
        return;
    }

    printf("%-12s%-20s%-20s%-8s%-12s\n",
        "ID Transaksi","Nama Pelanggan","Nama Barang","Jumlah","Subtotal");
    garis();

    while(fscanf(fp,"%[^;];%d;%[^;];%d;%[^;];%d;%f;%f\n",
        t.idTransaksi, &t.idPelanggan, t.namaPelanggan,
        &t.kodeBarang, t.namaBarang, &t.jumlah,
        &t.harga, &t.subtotal) != EOF){

        jumlahTransaksi++;
        totalPendapatan += t.subtotal;

        printf("%-12s%-20s%-20s%-8d%-12.0f\n",
            t.idTransaksi, t.namaPelanggan, t.namaBarang,
            t.jumlah, t.subtotal);
    }

    fclose(fp);

    garis();
    printf("Jumlah Transaksi   : %d\n", jumlahTransaksi);
    printf("Total Pendapatan   : %.0f\n", totalPendapatan);
    garis();

    pauseProgram();
}

void laporanBarangTerlaris(){
    FILE *fp;
    struct Transaksi t;

    int kodeUnik[MAX];
    char namaUnik[MAX][50];
    int totalJual[MAX];
    int jumlahUnik = 0;

    int i, idxMax;

    system("cls");
    garis();
    printf("              LAPORAN BARANG TERLARIS\n");
    garis();

    fp = fopen("transaksi.txt","r");
    if(fp == NULL){
        printf("\nBelum ada data transaksi.\n");
        pauseProgram();
        return;
    }

    while(fscanf(fp,"%[^;];%d;%[^;];%d;%[^;];%d;%f;%f\n",
        t.idTransaksi, &t.idPelanggan, t.namaPelanggan,
        &t.kodeBarang, t.namaBarang, &t.jumlah,
        &t.harga, &t.subtotal) != EOF){

        int ketemu = 0;

        for(i = 0; i < jumlahUnik; i++){
            if(kodeUnik[i] == t.kodeBarang){
                totalJual[i] += t.jumlah;
                ketemu = 1;
                break;
            }
        }

        if(!ketemu && jumlahUnik < MAX){
            kodeUnik[jumlahUnik] = t.kodeBarang;
            strcpy(namaUnik[jumlahUnik], t.namaBarang);
            totalJual[jumlahUnik] = t.jumlah;
            jumlahUnik++;
        }
    }

    fclose(fp);

    if(jumlahUnik == 0){
        printf("\nBelum ada transaksi untuk direkap.\n");
        pauseProgram();
        return;
    }

    for(i = 0; i < jumlahUnik-1; i++){
        idxMax = i;
        int j;
        for(j = i+1; j < jumlahUnik; j++){
            if(totalJual[j] > totalJual[idxMax]){
                idxMax = j;
            }
        }
        if(idxMax != i){
            int tmpKode = kodeUnik[i];
            int tmpJual = totalJual[i];
            char tmpNama[50];
            strcpy(tmpNama, namaUnik[i]);

            kodeUnik[i] = kodeUnik[idxMax];
            totalJual[i] = totalJual[idxMax];
            strcpy(namaUnik[i], namaUnik[idxMax]);

            kodeUnik[idxMax] = tmpKode;
            totalJual[idxMax] = tmpJual;
            strcpy(namaUnik[idxMax], tmpNama);
        }
    }

    printf("%-6s%-8s%-20s%-15s\n","No","Kode","Nama Barang","Total Terjual");
    garis();
    for(i = 0; i < jumlahUnik; i++){
        printf("%-6d%-8d%-20s%-15d\n",
            i+1, kodeUnik[i], namaUnik[i], totalJual[i]);
    }
    garis();

    pauseProgram();
}

void laporanTransaksi(){
    FILE *fp;
    struct Transaksi t;
    int no = 1;

    system("cls");
    garis();
    printf("                 LAPORAN TRANSAKSI\n");
    garis();

    fp = fopen("transaksi.txt","r");
    if(fp == NULL){
        printf("\nBelum ada data transaksi.\n");
        pauseProgram();
        return;
    }

    printf("%-4s%-12s%-20s%-20s%-8s%-10s%-12s\n",
        "No","ID Trans","Nama Pelanggan","Nama Barang","Jml","Harga","Subtotal");
    garis();

    while(fscanf(fp,"%[^;];%d;%[^;];%d;%[^;];%d;%f;%f\n",
        t.idTransaksi, &t.idPelanggan, t.namaPelanggan,
        &t.kodeBarang, t.namaBarang, &t.jumlah,
        &t.harga, &t.subtotal) != EOF){

        printf("%-4d%-12s%-20s%-20s%-8d%-10.0f%-12.0f\n",
            no++, t.idTransaksi, t.namaPelanggan, t.namaBarang,
            t.jumlah, t.harga, t.subtotal);
    }

    fclose(fp);
    garis();

    pauseProgram();
}

int cariPelangganById(int id, struct Pelanggan *hasil){
    FILE *fp;
    struct Pelanggan p;

    fp = fopen("pelanggan.txt","r");
    if(fp == NULL) return 0;

    while(fscanf(fp,"%d;%[^\n]\n",
        &p.idPelanggan, p.namaPelanggan) != EOF){

        if(p.idPelanggan == id){
            *hasil = p;
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

int kurangiStokBarang(int kode, int jumlah){
    FILE *fp, *temp;
    struct Barang b;
    int ketemu = 0;

    fp = fopen("barang.txt","r");
    if(fp == NULL) return 0;

    temp = fopen("barang_temp.txt","w");

    while(fscanf(fp,"%d;%[^;];%[^;];%d;%f;%f\n",
        &b.kodeBarang, b.namaBarang, b.kategori,
        &b.stok, &b.hargaBeli, &b.hargaJual) != EOF){

        if(b.kodeBarang == kode){
            ketemu = 1;
            b.stok -= jumlah;
            if(b.stok < 0) b.stok = 0;
        }

        fprintf(temp,"%d;%s;%s;%d;%.2f;%.2f\n",
            b.kodeBarang, b.namaBarang, b.kategori,
            b.stok, b.hargaBeli, b.hargaJual);
    }

    fclose(fp);
    fclose(temp);

    remove("barang.txt");
    rename("barang_temp.txt","barang.txt");

    return ketemu;
}

int tambahStokBarang(int kode,int jumlah)
{
    FILE *fp,*temp;
    struct Barang b;

    int ketemu=0;

    fp=fopen("barang.txt","r");

    if(fp==NULL)
        return 0;

    temp=fopen("barang_temp.txt","w");

    while(fscanf(fp,"%d;%[^;];%[^;];%d;%f;%f\n",
          &b.kodeBarang,
          b.namaBarang,
          b.kategori,
          &b.stok,
          &b.hargaBeli,
          &b.hargaJual)!=EOF)
    {

        if(b.kodeBarang==kode)
        {
            ketemu=1;
            b.stok+=jumlah;
        }

        fprintf(temp,"%d;%s;%s;%d;%.2f;%.2f\n",
                b.kodeBarang,
                b.namaBarang,
                b.kategori,
                b.stok,
                b.hargaBeli,
                b.hargaJual);
    }

    fclose(fp);
    fclose(temp);

    remove("barang.txt");
    rename("barang_temp.txt","barang.txt");

    return ketemu;
}

void cetakStruk(struct Transaksi t){
    garis();
    printf("                     STRUK TRANSAKSI\n");
    garis();
    printf("ID Transaksi   : %s\n", t.idTransaksi);
    printf("Nama Pelanggan : %s\n", t.namaPelanggan);
    printf("Nama Barang    : %s\n", t.namaBarang);
    printf("Jumlah         : %d\n", t.jumlah);
    printf("Harga Satuan   : %.0f\n", t.harga);
    printf("Subtotal       : %.0f\n", t.subtotal);
    garis();
}

void lihatBarang(){
    FILE *fp;
    struct Barang b;
    int no = 1;

    system("cls");
    garis();
    printf("                   DAFTAR BARANG\n");
    garis();

    fp = fopen("barang.txt","r");
    if(fp == NULL){
        printf("\nData barang belum ada.\n");
        pauseProgram();
        return;
    }

    printf("%-4s%-8s%-20s%-15s%-8s%-12s\n",
        "No","Kode","Nama Barang","Kategori","Stok","Harga Jual");
    garis();

    while(fscanf(fp,"%d;%[^;];%[^;];%d;%f;%f\n",
        &b.kodeBarang, b.namaBarang, b.kategori,
        &b.stok, &b.hargaBeli, &b.hargaJual) != EOF){

        printf("%-4d%-8d%-20s%-15s%-8d%-12.0f\n",
            no++, b.kodeBarang, b.namaBarang, b.kategori,
            b.stok, b.hargaJual);
    }
    garis();

    fclose(fp);
    pauseProgram();
}

void cariBarang(){
    FILE *fp;
    struct Barang b;
    char kataKunci[50];
    int ketemu = 0;

    system("cls");
    garis();
    printf("                   CARI BARANG\n");
    garis();

    printf("Masukkan Kode atau Nama Barang : ");
    scanf(" %[^\n]", kataKunci);

    fp = fopen("barang.txt","r");
    if(fp == NULL){
        printf("\nData barang belum ada.\n");
        pauseProgram();
        return;
    }

    printf("\n%-8s%-20s%-15s%-8s%-12s\n",
        "Kode","Nama Barang","Kategori","Stok","Harga Jual");
    garis();

    while(fscanf(fp,"%d;%[^;];%[^;];%d;%f;%f\n",
        &b.kodeBarang, b.namaBarang, b.kategori,
        &b.stok, &b.hargaBeli, &b.hargaJual) != EOF){

        char kodeStr[10];
        sprintf(kodeStr, "%d", b.kodeBarang);

        if(strcmp(kodeStr, kataKunci) == 0 ||
           strstr(b.namaBarang, kataKunci) != NULL){
            ketemu = 1;
            printf("%-8d%-20s%-15s%-8d%-12.0f\n",
                b.kodeBarang, b.namaBarang, b.kategori,
                b.stok, b.hargaJual);
        }
    }
    garis();

    fclose(fp);

    if(!ketemu){
        printf("\nBarang dengan kata kunci \"%s\" tidak ditemukan!\n", kataKunci);
    }

    pauseProgram();
}

void transaksiPenjualan(){
    FILE *fp;
    struct Pelanggan p;
    struct Barang b;
    struct Transaksi t;
    int idPelanggan, kodeBarang, jumlahBeli;
    int jumlahTransaksiSaatIni = 0;
    char temp[20];

    system("cls");
    garis();
    printf("                TRANSAKSI PENJUALAN\n");
    garis();

    idPelanggan = inputInt("ID Pelanggan : ");

    if(!cariPelangganById(idPelanggan, &p)){
        printf("\nID Pelanggan tidak ditemukan!\n");
        pauseProgram();
        return;
    }

    printf("Nama Pelanggan        : %s\n", p.namaPelanggan);

    kodeBarang = inputInt("Masukkan Kode Barang : ");

    if(!cariBarangByKode(kodeBarang, &b)){
        printf("\nKode Barang tidak ditemukan!\n");
        pauseProgram();
        return;
    }

    printf("Nama Barang : %s\n", b.namaBarang);
    printf("Stok Saat Ini : %d\n", b.stok);
    printf("Harga Jual  : %.0f\n", b.hargaJual);

    if(b.stok <= 0){
        printf("\nStok barang habis!\n");
        pauseProgram();
        return;
    }

    jumlahBeli = inputInt("Masukkan Jumlah Beli : ");

    if(jumlahBeli <= 0){
        printf("\nJumlah tidak valid!\n");
        pauseProgram();
        return;
    }

    if(jumlahBeli > b.stok){
        printf("\nStok tidak mencukupi! Stok tersedia: %d\n", b.stok);
        pauseProgram();
        return;
    }

    fp = fopen("transaksi.txt","r");
    if(fp != NULL){
        while(fscanf(fp,"%[^;];%d;%[^;];%d;%[^;];%d;%f;%f\n",
            t.idTransaksi, &t.idPelanggan, t.namaPelanggan,
            &t.kodeBarang, t.namaBarang, &t.jumlah,
            &t.harga, &t.subtotal) != EOF){
            jumlahTransaksiSaatIni++;
        }
        fclose(fp);
    }

    sprintf(temp, "TRX%03d", jumlahTransaksiSaatIni + 1);
    strcpy(t.idTransaksi, temp);

    t.idPelanggan = p.idPelanggan;
    strcpy(t.namaPelanggan, p.namaPelanggan);
    t.kodeBarang = b.kodeBarang;
    strcpy(t.namaBarang, b.namaBarang);
    t.jumlah = jumlahBeli;
    t.harga = b.hargaJual;
    t.subtotal = jumlahBeli * b.hargaJual;

    fp = fopen("transaksi.txt","a");
    if(fp == NULL){
        printf("\nGagal membuka file transaksi.txt!\n");
        pauseProgram();
        return;
    }

    fprintf(fp,"%s;%d;%s;%d;%s;%d;%.2f;%.2f\n",
        t.idTransaksi, t.idPelanggan, t.namaPelanggan,
        t.kodeBarang, t.namaBarang, t.jumlah, t.harga, t.subtotal);

    fclose(fp);

    kurangiStokBarang(b.kodeBarang, jumlahBeli);

    printf("\nTransaksi berhasil!\n");
    cetakStruk(t);

    pauseProgram();
}

void riwayatTransaksi(){
    FILE *fp;
    struct Transaksi t;
    int no = 1;
    float totalSemua = 0;

    system("cls");
    garis();
    printf("                 RIWAYAT TRANSAKSI\n");
    garis();

    fp = fopen("transaksi.txt","r");
    if(fp == NULL){
        printf("\nBelum ada data transaksi.\n");
        pauseProgram();
        return;
    }

    printf("%-4s%-10s%-20s%-20s%-8s%-10s%-12s\n",
        "No","ID Trans","Nama Pelanggan","Nama Barang","Jml","Harga","Subtotal");
    garis();

    while(fscanf(fp,"%[^;];%d;%[^;];%d;%[^;];%d;%f;%f\n",
        t.idTransaksi, &t.idPelanggan, t.namaPelanggan,
        &t.kodeBarang, t.namaBarang, &t.jumlah,
        &t.harga, &t.subtotal) != EOF){

        printf("%-4d%-10s%-20s%-20s%-8d%-10.0f%-12.0f\n",
            no++, t.idTransaksi, t.namaPelanggan, t.namaBarang,
            t.jumlah, t.harga, t.subtotal);

        totalSemua += t.subtotal;
    }

    fclose(fp);
    garis();
    printf("Total Seluruh Transaksi : %.0f\n", totalSemua);
    garis();

    pauseProgram();
}

/* ======================================================================
   FITUR BARU: TAMPIL, EDIT, DAN HAPUS TRANSAKSI (khusus Menu Kasir)
   ====================================================================== */

/*
   Menampilkan seluruh data transaksi TANPA pauseProgram() di akhir,
   supaya bisa dipakai sebagai referensi tampilan sebelum user
   memasukkan ID Transaksi pada fitur edit/hapus (pola yang sama
   seperti tampilkanSemuaBarang/tampilkanSemuaSupplier/tampilkanSemuaPelanggan).
*/
void tampilkanSemuaTransaksi(){
    FILE *fp;
    struct Transaksi t;
    int no = 1;

    fp = fopen("transaksi.txt","r");
    if(fp == NULL){
        printf("\nBelum ada data transaksi.\n");
        return;
    }

    printf("%-4s%-10s%-20s%-20s%-8s%-10s%-12s\n",
        "No","ID Trans","Nama Pelanggan","Nama Barang","Jml","Harga","Subtotal");
    garis();

    while(fscanf(fp,"%[^;];%d;%[^;];%d;%[^;];%d;%f;%f\n",
        t.idTransaksi, &t.idPelanggan, t.namaPelanggan,
        &t.kodeBarang, t.namaBarang, &t.jumlah,
        &t.harga, &t.subtotal) != EOF){

        printf("%-4d%-10s%-20s%-20s%-8d%-10.0f%-12.0f\n",
            no++, t.idTransaksi, t.namaPelanggan, t.namaBarang,
            t.jumlah, t.harga, t.subtotal);
    }
    garis();

    fclose(fp);
}

/*
   Mencari satu transaksi berdasarkan idTransaksi.
   Mengembalikan 1 jika ketemu (data disalin ke *hasil), 0 jika tidak.
*/
int cariTransaksiById(char idCari[], struct Transaksi *hasil){
    FILE *fp;
    struct Transaksi t;

    fp = fopen("transaksi.txt","r");
    if(fp == NULL) return 0;

    while(fscanf(fp,"%[^;];%d;%[^;];%d;%[^;];%d;%f;%f\n",
        t.idTransaksi, &t.idPelanggan, t.namaPelanggan,
        &t.kodeBarang, t.namaBarang, &t.jumlah,
        &t.harga, &t.subtotal) != EOF){

        if(strcmp(t.idTransaksi, idCari) == 0){
            *hasil = t;
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

/*
   EDIT TRANSAKSI
   ---------------
   Yang bisa diedit: jumlah beli.
   Algoritma:
   1. Tampilkan semua transaksi + minta ID Transaksi yang ingin diedit.
   2. Baca transaksi.txt baris per baris, tulis ulang ke file sementara
      (transaksi_temp.txt) -- pola yang sama dengan editBarang/editSupplier.
   3. Saat baris yang idTransaksi-nya cocok ditemukan:
        - Ambil data barang terkait (cariBarangByKode) untuk tahu stok saat ini.
        - Hitung "stok efektif" = stok saat ini + jumlah lama transaksi ini,
          karena jumlah lama sudah pernah dipotong dari stok saat transaksi
          dibuat, sehingga validasi jumlah baru harus dibandingkan terhadap
          stok efektif tersebut, bukan stok yang sudah terpotong.
        - Minta jumlah beli baru, validasi (>0 dan <= stok efektif).
        - Hitung selisih = jumlah baru - jumlah lama.
            selisih > 0 -> stok barang dikurangi sebesar selisih (kurangiStokBarang)
            selisih < 0 -> stok barang ditambah sebesar |selisih| (tambahStokBarang)
        - Update jumlah & subtotal (harga satuan tetap sama).
   4. Timpa transaksi.txt dengan file sementara (remove + rename).
*/
void editTransaksi(){
    FILE *fp, *temp;
    struct Transaksi t;
    struct Barang b;
    char idCari[20];
    int ketemu = 0;
    int jumlahBaru;
    int stokEfektif;
    int selisih;

    system("cls");
    garis();
    printf("                  EDIT TRANSAKSI\n");
    garis();

    tampilkanSemuaTransaksi();

    inputString("\nMasukkan ID Transaksi yang akan diedit : ", idCari, sizeof(idCari));

    fp = fopen("transaksi.txt","r");
    if(fp == NULL){
        printf("\nBelum ada data transaksi.\n");
        pauseProgram();
        return;
    }

    temp = fopen("transaksi_temp.txt","w");

    while(fscanf(fp,"%[^;];%d;%[^;];%d;%[^;];%d;%f;%f\n",
        t.idTransaksi, &t.idPelanggan, t.namaPelanggan,
        &t.kodeBarang, t.namaBarang, &t.jumlah,
        &t.harga, &t.subtotal) != EOF){

        if(strcmp(t.idTransaksi, idCari) == 0){
            ketemu = 1;

            printf("\nData transaksi ditemukan:\n");
            printf("Nama Pelanggan : %s\n", t.namaPelanggan);
            printf("Nama Barang    : %s\n", t.namaBarang);
            printf("Jumlah Lama    : %d\n", t.jumlah);
            printf("Harga Satuan   : %.0f\n", t.harga);

            if(!cariBarangByKode(t.kodeBarang, &b)){
                printf("\nData barang terkait tidak ditemukan di master barang,\n");
                printf("transaksi tidak dapat diedit dan dibiarkan seperti semula!\n\n");

                fprintf(temp,"%s;%d;%s;%d;%s;%d;%.2f;%.2f\n",
                    t.idTransaksi, t.idPelanggan, t.namaPelanggan,
                    t.kodeBarang, t.namaBarang, t.jumlah, t.harga, t.subtotal);
                continue;
            }

            stokEfektif = b.stok + t.jumlah;

            while(1){
                jumlahBaru = inputInt("Jumlah Beli Baru : ");

                if(jumlahBaru <= 0){
                    printf("\nJumlah harus lebih dari 0!\n\n");
                    continue;
                }

                if(jumlahBaru > stokEfektif){
                    printf("\nStok tidak mencukupi! Stok tersedia (efektif) : %d\n\n", stokEfektif);
                    continue;
                }

                break;
            }

            selisih = jumlahBaru - t.jumlah;

            if(selisih > 0){
                kurangiStokBarang(t.kodeBarang, selisih);
            }
            else if(selisih < 0){
                tambahStokBarang(t.kodeBarang, -selisih);
            }

            t.jumlah = jumlahBaru;
            t.subtotal = t.jumlah * t.harga;

            printf("\nTransaksi berhasil diperbarui!\n\n");
        }

        fprintf(temp,"%s;%d;%s;%d;%s;%d;%.2f;%.2f\n",
            t.idTransaksi, t.idPelanggan, t.namaPelanggan,
            t.kodeBarang, t.namaBarang, t.jumlah, t.harga, t.subtotal);
    }

    fclose(fp);
    fclose(temp);

    remove("transaksi.txt");
    rename("transaksi_temp.txt","transaksi.txt");

    if(!ketemu){
        printf("\nID Transaksi tidak ditemukan!\n");
    }

    pauseProgram();
}

/*
   HAPUS TRANSAKSI
   ----------------
   Algoritma:
   1. Tampilkan semua transaksi + minta ID Transaksi yang ingin dihapus.
   2. Baca transaksi.txt baris per baris, tulis ulang ke file sementara,
      KECUALI baris yang idTransaksi-nya cocok (baris itu tidak ditulis
      ulang -> otomatis terhapus dari transaksi.txt yang baru).
   3. Sebelum baris yang cocok "dibuang", stok barang yang terkait
      dikembalikan (tambahStokBarang) sejumlah t.jumlah pada transaksi
      tersebut, karena stok itu sebelumnya sudah dipotong saat transaksi
      dibuat di transaksiPenjualan().
   4. Timpa transaksi.txt dengan file sementara (remove + rename).
*/
void hapusTransaksi(){
    FILE *fp, *temp;
    struct Transaksi t;
    char idCari[20];
    int ketemu = 0;

    system("cls");
    garis();
    printf("                 HAPUS TRANSAKSI\n");
    garis();

    tampilkanSemuaTransaksi();

    inputString("\nMasukkan ID Transaksi yang akan dihapus : ", idCari, sizeof(idCari));

    fp = fopen("transaksi.txt","r");
    if(fp == NULL){
        printf("\nBelum ada data transaksi.\n");
        pauseProgram();
        return;
    }

    temp = fopen("transaksi_temp.txt","w");

    while(fscanf(fp,"%[^;];%d;%[^;];%d;%[^;];%d;%f;%f\n",
        t.idTransaksi, &t.idPelanggan, t.namaPelanggan,
        &t.kodeBarang, t.namaBarang, &t.jumlah,
        &t.harga, &t.subtotal) != EOF){

        if(strcmp(t.idTransaksi, idCari) == 0){
            ketemu = 1;

            tambahStokBarang(t.kodeBarang, t.jumlah);

            continue;
        }

        fprintf(temp,"%s;%d;%s;%d;%s;%d;%.2f;%.2f\n",
            t.idTransaksi, t.idPelanggan, t.namaPelanggan,
            t.kodeBarang, t.namaBarang, t.jumlah, t.harga, t.subtotal);
    }

    fclose(fp);
    fclose(temp);

    remove("transaksi.txt");
    rename("transaksi_temp.txt","transaksi.txt");

    if(ketemu){
        printf("\nTransaksi berhasil dihapus dan stok barang telah dikembalikan!\n");
    }else{
        printf("\nID Transaksi tidak ditemukan!\n");
    }

    pauseProgram();
}
