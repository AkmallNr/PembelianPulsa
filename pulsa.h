#ifndef PULSA_H
#define PULSA_H


struct Transaksi {
    char jenis[50];
    char nomor_telepon[20];
    char nomor_ID[20];
    double harga;
    char day[10];
    int biaya_admin;
};

typedef struct {
    int nominal;
    char nomor_telepon[15];
    char nomor_akun[15];
    char pin[6];
    char promo_codePulsa[20];
    float harga_pulsa, diskonpulsa, total_biayaPulsa;
    int biaya_admin;
    char metode_pembayaran[20];
    int kode_pembayaran;
    char jenis[10];
    const char* day;
    struct Transaksi transaksi;
} PembelianPulsa;

typedef struct {
    int nominal;
    char nomor_ID[21];
    char nomor_akun[15];
    char pin[6];
    char promo_codeToken[20];
    float harga_token, diskontoken, total_biayaToken;
    int biaya_admin;
    char metode_pembayaran[20];
    int kode_pembayaran;
    char jenis[10];
    const char* day;
    struct Transaksi transaksi;
} PembelianToken;

struct User {
    char username[50];
    char password[50];
    char pin[7];
    char role[10];
};

struct Admin {
    char username[50];
    char password[50];
    char role[10];
};



/*==================================FUNGSI DAN PROSEDUR==============================================*/
void Cls();
char kodepromopulsa(PembelianPulsa *pulsa);
char kodepromotoken(PembelianToken *token);
float promo(int harga, char *promocode);
void loadBiayaAdminToken(PembelianToken *token);
void loadBiayaAdminPulsa(PembelianPulsa *pulsa);
void katadiskon(PembelianPulsa *pulsa, PembelianToken *token);
float hitungTotalBiayaPulsa(PembelianPulsa *pulsa);
float hitungTotalBiayaToken(PembelianToken *token);
int generateKodePembayaran(int *kode_pembayaran);
void inputNominalPulsa(PembelianPulsa *pulsa);
void inputNominalToken(PembelianToken *token);
void pilihMetodeBayaran(PembelianPulsa *pulsa, PembelianToken *token);
void cetakStrukPulsa(PembelianPulsa *pulsa, PembelianToken *token);
void cetakStrukToken(PembelianPulsa *pulsa, PembelianToken *token);
void ulang(PembelianPulsa *pulsa, PembelianToken *token);
void beliPulsa(PembelianPulsa *pulsa, PembelianToken *token);
void beliTokenListrik(PembelianPulsa *pulsa, PembelianToken *token);
void simpanTransaksiPulsa(PembelianPulsa *pulsa);
void simpanTransaksiToken(PembelianToken *token);
const char* getRandomDay();
void riwayatTransaksiPulsa(PembelianPulsa *pulsa);
void riwayatTransaksiToken(PembelianToken *token);
int pilihTransaksi(PembelianPulsa *pulsa, PembelianToken *token);
void loadBiayaAdmin(PembelianPulsa *pulsa, PembelianToken *token);

void saveUserDataToFile();
void loadUserDataFromFile();
void showAllUsers(PembelianPulsa *pulsa, PembelianToken *token);
int adminLogin();
int menuAdmin(PembelianPulsa *pulsa, PembelianToken *token);
void showTransaksi(PembelianPulsa *pulsa, PembelianToken *token);
int userLogin();
void userSignUp();
void login() ;
int menuLogin(PembelianPulsa *pulsa, PembelianToken *token);



#endif // BURUH_H
