#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "pulsa.h"

struct User DBUser[100];
void Cls() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
void loadBiayaAdminPulsa(PembelianPulsa *pulsa) {
    FILE *file = fopen("biaya_admin_pulsa.txt", "r");
    if (file != NULL) {
    	int i = 0;
        while(fscanf(file, "%d", &pulsa[i].transaksi.biaya_admin)!= EOF && i < 2){
        	//printf("%d", pulsa[i].transaksi.biaya_admin);
        	i++;
		}
        fclose(file);
    } else {
        printf("Gagal membuka file untuk biaya admin.\n");
    }
}
void loadBiayaAdminToken(PembelianToken *token) {
    FILE *file = fopen("biaya_admin_token.txt", "r");
    if (file != NULL) {
        int i = 0;
        while(fscanf(file, "%d", &token[i].transaksi.biaya_admin)!= EOF && i < 2){
        	//printf("%d", token[i].transaksi.biaya_admin);
        	i++;
		}
        fclose(file);
    } else {
        printf("Gagal membuka file untuk biaya admin.\n");
    }
}

char kodepromopulsa(PembelianPulsa *pulsa){
	printf("Masukkan kode promo, abaikan jika tidak ada : ");
    scanf("%s", pulsa->promo_codePulsa);
    Cls();
}

char kodepromotoken(PembelianToken *token){
	printf("Masukkan kode promo, abaikan jika tidak ada: ");
    scanf("%s", token->promo_codeToken);
    Cls();
}

float promo(int harga, char *promocode) {
    float diskon = 0.0;
    if (strcmp(promocode, "pulsakita") == 0) {
        diskon = 0.1 * harga;
    } else if (strcmp(promocode, "pulsamurah") == 0) {
        diskon = 0.05 * harga;
    } else if (strcmp(promocode, "metapulsa") == 0) {
        diskon = 0.2 * harga;
    } else if (strcmp(promocode, "tokenkita") == 0) {
        diskon = 0.1 * harga;
    } else if (strcmp(promocode, "tokenmurah") == 0) {
        diskon = 0.05 * harga;
    } else if (strcmp(promocode, "metatoken") == 0) {
        diskon = 0.2 * harga;
    }
    return diskon;
}

void katadiskon(PembelianPulsa *pulsa, PembelianToken *token) {

    if (strcmp(pulsa->promo_codePulsa, "pulsakita") == 0) {
        printf("Selamat!! Anda mendapatkan diskon '10%%' \n");
    } else if (strcmp(pulsa->promo_codePulsa, "pulsamurah") == 0) {
        printf("Selamat!! Anda mendapatkan diskon 5%% \n");
    } else if (strcmp(pulsa->promo_codePulsa, "metapulsa") == 0) {
        printf("Selamat!! Anda mendapatkan diskon 20%% \n");
    } else if (strcmp(token->promo_codeToken, "tokenkita") == 0) {
        printf("Selamat!! Anda mendapatkan diskon 10%% \n");
    } else if (strcmp(token->promo_codeToken, "tokenmurah") == 0) {
        printf("Selamat!! Anda mendapatkan diskon 5%% \n");
    } else if (strcmp(token->promo_codeToken, "metatoken") == 0) {
        printf("Selamat!! Anda mendapatkan diskon 20%% \n");
    }
}

float hitungTotalBiayaPulsa(PembelianPulsa *pulsa) {
	//pulsa->biaya_admin=2000;
    loadBiayaAdminPulsa(pulsa);
    float total_biaya;
    pulsa->diskonpulsa = promo(pulsa->harga_pulsa, pulsa->promo_codePulsa);
    total_biaya = (pulsa->harga_pulsa - pulsa->diskonpulsa) + pulsa->transaksi.biaya_admin;
    return total_biaya;
}

float hitungTotalBiayaToken(PembelianToken *token) {
    //token->biaya_admin=3000;
	loadBiayaAdminToken(token);
    float total_biaya;
    token->diskontoken = promo(token->harga_token, token->promo_codeToken);
    total_biaya = (token->harga_token - token->diskontoken) + token->transaksi.biaya_admin;
    return total_biaya;
}

int generateKodePembayaran(int *kode_pembayaran) {
    srand(time(0));
    *kode_pembayaran = rand() % 1000000 + 100000; // Kode pembayaran antara 100000 dan 999999
    return *kode_pembayaran;
}

void inputNominalPulsa(PembelianPulsa *pulsa) {
	do {
        printf("Masukkan nomor telepon (minimal 10 angka): ");
        scanf("%s", pulsa->nomor_telepon);

        // Validasi panjang nomor telepon
        if (strlen(pulsa->nomor_telepon) < 10 || (strlen(pulsa->nomor_telepon) > 13 )) {
            printf("Minimal 10 angka dan maksimal 13 angka. Silakan masukkan nomor telepon dengan benar.\n");
        }
    } while (strlen(pulsa->nomor_telepon) < 10 || (strlen(pulsa->nomor_telepon) > 13 ));
    do{
    	printf("Pilih nominal pulsa:\n");
	    printf("1. Rp 5.000\n2. Rp 10.000\n3. Rp 20.000\n4. Rp 50.000\n5. Rp 100.000\n6. Pilihan nominal sendiri\n");
	    printf("Pilihan Anda: ");
	    scanf("%d", &pulsa->nominal);
	
	    switch (pulsa->nominal) {
	        // Logic untuk setiap nominal
	        case 1:
	            pulsa->harga_pulsa = 5000;
	            break;
	        case 2:
	            pulsa->harga_pulsa = 10000;
	            break;
	        case 3:
	            pulsa->harga_pulsa = 20000;
	            break;
	        case 4:
	            pulsa->harga_pulsa = 50000;
	            break;
	        case 5:
	            pulsa->harga_pulsa = 100000;
	            break;
	        case 6:
	            printf("Masukkan nominal pulsa sendiri: ");
	            scanf("%f", &pulsa->harga_pulsa);
	            break;
	        default:
	            printf("Pilihan tidak valid.\n\n");
	    }
	}while (pulsa->nominal > 6);
    
}

void inputNominalToken(PembelianToken *token) {
	do {
        printf("Masukkan nomor ID Pengguna Token Listrik : ");
        scanf("%s", token->nomor_ID);

        // Validasi panjang nomor telepon
        if (strlen(token->nomor_ID) < 12 || (strlen(token->nomor_ID) > 20 )) {
            printf("Minimal 12 angka dan maksimal 20 angka. Silakan masukkan nomor ID Pengguna dengan benar.\n");
        }
    } while (strlen(token->nomor_ID) < 12 || (strlen(token->nomor_ID) > 20 ));
    do{
    	printf("Pilih nominal token:\n");
	    printf("1. Rp 20.000\n2. Rp 50.000\n3. Rp 100.000\n4. Rp 200.000\n5. Rp 500.000\n6. Rp. 1000.000\n7. Pilihan nominal sendiri\n");
	    printf("Pilihan Anda: ");
	    scanf("%d", &token->nominal);
	
	    switch (token->nominal) {
	        // Logic untuk setiap nominal
	        case 1:
	            token->harga_token = 20000;
	            break;
	        case 2:
	            token->harga_token = 50000;
	            break;
	        case 3:
	            token->harga_token = 100000;
	            break;
	        case 4:
	            token->harga_token = 200000;
	            break;
	        case 5:
	            token->harga_token = 500000;
	            break;
	        case 6:
	            token->harga_token = 1000000;
	            break;
	        case 7:
	            printf("Masukkan nominal token sendiri: ");
	            scanf("%f", &token->harga_token);
	            break;
	        default:
	            printf("Pilihan tidak valid.\n\n");
	    }
	}while (token->nominal > 7);
    
}

void pilihMetodeBayaran(PembelianPulsa *pulsa, PembelianToken *token) {
    int pilih;
    int pilihdompet;
    int pilihbank;
    do{
    	printf("Pilih metode pembayaran:\n");
	    printf("1. Dompet Digital\n2. Transfer Bank\n");
	    printf("Pilihan Anda: ");
	    scanf("%d", &pilih);
	    Cls();
	    
	    switch (pilih) {
	        case 1:
	            // Pilihan dompet digital
	            do {
	                printf("Pilih Dompet Digital Anda\n");
	                printf("1. Dana\n2. Gopay\n3. Shopeepay\n4. OVO\n");
	                printf("Masukkan Pilihan Anda :");
	                scanf("%d", &pilihdompet);
	
	                switch (pilihdompet) {
	                    case 1:
	                        strcpy(pulsa->metode_pembayaran, "Dana");
	                        strcpy(token->metode_pembayaran, "Dana");
	                        break;
	                    case 2:
	                        strcpy(pulsa->metode_pembayaran, "Gopay");
	                        strcpy(token->metode_pembayaran, "Gopay");
	                        break;
	                    case 3:
	                        strcpy(pulsa->metode_pembayaran, "Shopeepay");
	                        strcpy(token->metode_pembayaran, "Shopeepay");
	                        break;
	                    case 4:
	                        strcpy(pulsa->metode_pembayaran, "OVO");
	                        strcpy(token->metode_pembayaran, "OVO");
	                        break;
	                    default:
	                        printf("Pilihan metode pembayaran dompet digital tidak valid.\n");
	                }
	            } while (pilihdompet > 4);
	            break;
	
	        case 2:
	            // Pilihan transfer bank
	            do {
	                printf("Pilih Bank Anda\n");
	                printf("1. BRI\n2. BNI\n3. BCA\n4. Mandiri\n");
	                printf("Masukkan Pilihan Anda :");
	                scanf("%d", &pilihbank);
	
	                switch (pilihbank) {
	                    case 1:
	                        strcpy(pulsa->metode_pembayaran, "BRI");
	                        strcpy(token->metode_pembayaran, "BRI");
	                        break;
	                    case 2:
	                        strcpy(pulsa->metode_pembayaran, "BNI");
	                        strcpy(token->metode_pembayaran, "BNI");
	                        break;
	                    case 3:
	                        strcpy(pulsa->metode_pembayaran, "BCA");
	                        strcpy(token->metode_pembayaran, "BCA");
	                        break;
	                    case 4:
	                        strcpy(pulsa->metode_pembayaran, "Mandiri");
	                        strcpy(token->metode_pembayaran, "Mandiri");
	                        break;
	                    default:
	                        printf("Pilihan metode pembayaran bank tidak valid.\n");
	                }
	            } while (pilihbank > 4);
	        	break;
	        default:
	        	printf("Pilihan Tidak Valid\n");
	        	break;
	    }	
	}while(pilih>2);
    
}

void cetakStrukPulsa(PembelianPulsa *pulsa, PembelianToken *token) {
	loadBiayaAdminPulsa(pulsa);
	loadUserDataFromFile();
	int PINExists;
	char pin[7];
    pulsa->diskonpulsa = promo(pulsa->harga_pulsa, pulsa->promo_codePulsa);
    pulsa->total_biayaPulsa = hitungTotalBiayaPulsa(pulsa);
	katadiskon(pulsa, token);
    printf("Masukkan Nomor Rekening / Akun %s Anda : ", pulsa->metode_pembayaran);
    scanf("%s", pulsa->nomor_akun);
    printf("%s",DBUser->username);
    //Cls();
	
	do { // Setel flag ke 0 di awal loop
    	PINExists = 0;
        printf("Masukkan PIN Rekening / Akun %s Anda : ", pulsa->metode_pembayaran);
        scanf("%s", pin);
		
        int i = 0;
        while (i < 100) {
            if (strcmp(pin, DBUser[i].pin) == 0) {
                printf("PIN salah, Silahkan Masukin PIN yang Benar.\n");
                PINExists = 1; // Setel flag ke 1 jika username sudah ada
                break;
            }
            i++;
        }
    } while (PINExists); 
	
    //Cls();

    int kode_pembayaran;
    int input_pengguna;
    srand(time(0));
    kode_pembayaran = rand() % 1000000 + 100000;
    do {
        printf("Kode Pembayaran: %06d\n", kode_pembayaran);
        printf("Masukkan Kode Pembayaran: ");
        scanf("%d", &input_pengguna);
        if (input_pengguna == kode_pembayaran) {
            Cls();
            printf("Kode pembayaran sesuai. Pembayaran diterima.\n");
            printf("Struk Pembelian Pulsa\n");
            printf("Informasi Pembelian:\n");
            printf("Nomor Telepon  : %s\n", pulsa->nomor_telepon);
            printf("Metode Pembayaran : %s\n", pulsa->metode_pembayaran);
            printf("Nomor Rekening  : %s\n", pulsa->nomor_akun);
            printf("Nominal Pulsa  : Rp %.0f\n", pulsa->harga_pulsa);
            printf("Biaya Admin   : Rp %d\n", pulsa->transaksi.biaya_admin); // Ubah dari %0 menjadi %d
            printf("Diskon    : Rp -%.0f\n", pulsa->diskonpulsa);
            printf("Total Biaya   : Rp %.0f\n", pulsa->total_biayaPulsa);
            strcpy(pulsa->jenis, "Pulsa");
            simpanTransaksiPulsa(pulsa);

        } else {
            printf("Kode pembayaran tidak sesuai. Pembayaran ditolak\n\n");
        }
    } while (input_pengguna != kode_pembayaran);
}

void cetakStrukToken(PembelianPulsa *pulsa, PembelianToken *token) {
	loadBiayaAdminToken(token);
    token->diskontoken = promo(token->harga_token, token->promo_codeToken);
    token->total_biayaToken = hitungTotalBiayaToken(token);
	katadiskon(pulsa, token);
    printf("Masukkan Nomor Rekening / Akun %s Anda : ", token->metode_pembayaran);
    scanf("%s", token->nomor_akun);
    Cls();

    printf("Masukkan PIN Rekening / Akun %s Anda : ", token->metode_pembayaran);
    scanf("%d", &token->pin);
    Cls();

    int kode_pembayaran;
    int input_pengguna;
    srand(time(0));
    kode_pembayaran = rand() % 1000000 + 100000;
    do {
        printf("Kode Pembayaran: %06d\n", kode_pembayaran);
        printf("Masukkan Kode Pembayaran: ");
        scanf("%d", &input_pengguna);
        if (input_pengguna == kode_pembayaran) {
            Cls();
            printf("Kode pembayaran sesuai. Pembayaran diterima.\n");
            printf("Struk Pembelian Token\n");
            printf("Informasi Pembelian:\n");
            printf("Nomor Telepon  : %s\n", token->nomor_ID);
            printf("Metode Pembayaran : %s\n", token->metode_pembayaran);
            printf("Nomor Rekening  : %s\n", token->nomor_akun);
            printf("Nominal Pulsa  : Rp %.0f\n", token->harga_token);
            printf("Biaya Admin   : Rp %d\n", token->transaksi.biaya_admin); // Ubah dari %0 menjadi %d
            printf("Diskon    : Rp -%.0f\n", token->diskontoken);
            printf("Total Biaya   : Rp %.0f\n", token->total_biayaToken);
            strcpy(token->jenis, "Token");
            simpanTransaksiToken(token);
        } else {
            printf("Kode pembayaran tidak sesuai. Pembayaran ditolak\n\n");
        }
    } while (input_pengguna != kode_pembayaran);
}

void ulang(PembelianPulsa *pulsa, PembelianToken *token){
	char ulg[3];
	printf("Mau Melakukan Transaksi Lagi (Y/T) ? ");
	scanf("%s", ulg);
	
	if(strcasecmp(ulg, "y")==0){
		Cls();
		pilihTransaksi(pulsa, token);
	}else{
		printf("Terima Kasih");
	}
}

void beliPulsa(PembelianPulsa *pulsa, PembelianToken *token) {
    printf("Anda memilih pembelian pulsa.\n");
    inputNominalPulsa(pulsa);
    kodepromopulsa(pulsa);
    pilihMetodeBayaran(pulsa, token);
    cetakStrukPulsa(pulsa, token);
    ulang(pulsa, token);
}

void beliTokenListrik(PembelianPulsa *pulsa, PembelianToken *token) {
    printf("Anda memilih pembelian token listrik.\n");
    inputNominalToken(token);
    kodepromotoken(token);
    pilihMetodeBayaran(pulsa, token);
    cetakStrukToken(pulsa, token);
    ulang(pulsa, token);
}

const char* getRandomDay() {
    const char *days[8] = {"Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu", "Minggu"};

    srand((unsigned int)time(NULL));  // Seed generator dengan waktu

    int randomIndex = rand() % 7;
    return days[randomIndex];
}

void simpanTransaksiPulsa(PembelianPulsa *pulsa) {
    FILE *file = fopen("transaksi.txt", "a");  // Membuka file untuk ditambahkan (write mode)
	const char *randomDay;
	pulsa->day = getRandomDay();
    if (file != NULL) {
    	int i = 0;
        //while (i < 100){
        	fprintf(file, "%s %s %f %s\n", pulsa[i].jenis, pulsa[i].nomor_telepon, pulsa[i].harga_pulsa, pulsa[i].day);
        //	i++;
		//}
        fclose(file);
    } else {
        printf("Gagal membuka file untuk penyimpanan riwayat transaksi.\n");
    }
}
void simpanTransaksiToken(PembelianToken *token) {
    FILE *file = fopen("transaksi.txt", "a");  // Membuka file untuk ditambahkan (write mode)
	const char *randomDay;
	token->day = getRandomDay();
    if (file != NULL) {
    	int i = 0;
        //while (i < 100){
        fprintf(file, "%s %s %f %s\n", token[i].jenis, token[i].nomor_ID, token[i].harga_token, token[i].day);
        //i++;
		
        fclose(file);
    } else {
        printf("Gagal membuka file untuk penyimpanan riwayat transaksi.\n");
    }
}


int pilihTransaksi(PembelianPulsa *pulsa, PembelianToken *token) {
    int pilihan;
    loadBiayaAdminPulsa(pulsa);
    loadBiayaAdminToken(token);
    do{
    	printf("Selamat Datang\n");
	    printf("1. Pembelian Pulsa\n2. Pembelian Token Listrik\n0. Keluar\n");
	    printf("Pilihan Anda: ");
	    scanf("%d", &pilihan);
	    Cls();	
	    switch (pilihan) {
	        case 1: 
	            beliPulsa(pulsa, token);
	            break;
	        case 2:
	            beliTokenListrik(pulsa, token);
	            break;
	        case 0:
	        	printf("Terima kasih telah menggunakan layanan kami.\n");
	        	return 0;
	        default:
	            printf("Pilihan tidak valid.\n\n");
	            break;
	    }
	} while (pilihan > 2 || pilihan < 1);
}
