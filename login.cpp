#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "pulsa.h"



struct User usersDatabase[100];
struct Admin Akmal = { "Akmal", "Akmal123", "Admin" };
struct Admin Bandi = { "Bandi", "Bandi123", "Admin" };

void saveUserDataToFile() {
    FILE *file = fopen("user_data.txt", "w");
    if (file != NULL) {
        int i = 0;
        while (i < 100) {
            if (strlen(usersDatabase[i].username) == 0) {
                break;
            }
            fprintf(file, "%s %s %s %s\n", usersDatabase[i].username, usersDatabase[i].password, usersDatabase[i].role, usersDatabase[i].pin);
            i++;
        }
        fclose(file);
    } else {
        printf("Gagal membuka file untuk penyimpanan data pengguna.\n");
    }
}

void BiayaAdminPulsa(PembelianPulsa *pulsa){
	FILE *file = fopen("biaya_admin_pulsa.txt", "w");
    if (file != NULL) {
            fprintf(file, "%d\n", pulsa->biaya_admin);
        fclose(file);
    } else {
        printf("Gagal membuka file untuk mengubah biaya admin.\n");
    }	
}
void BiayaAdminToken(PembelianToken *token){
	FILE *file = fopen("biaya_admin_token.txt", "w");
    if (file != NULL) {
            fprintf(file, "%d\n", token->biaya_admin);
        fclose(file);
    } else {
        printf("Gagal membuka file untuk mengubah biaya admin.\n");
    }	
}

//void ubahUser(){
//	FILE *file = fopen("user_data.txt", "w");
//    if (file != NULL) {
//    	fprintf(file, "%s", usersDatabase.username);
//    	fclose(file);
//    }
//}
//void ubahPass(){
//	FILE *file = fopen("user_data.txt", "w");
//    if (file != NULL) {
//    	fprintf(file, "%s", usersDatabase.password);
//    	fclose(file);
//}
//}
void ubahBiayaAdmin(PembelianPulsa *pulsa, PembelianToken *token){
	int pilih;
	int biaya;
	printf("Mau Ubah Biaya Admin Apa ?\n1. Pulsa\n2. Token\n0.Kembali\n");
	printf("Pilihan Anda : ");
	scanf("%d", &pilih);
	switch(pilih){
		case 1:
			printf("Masukan Biaya Admin Pulsa yang Baru :");
			scanf("%d", &pulsa->biaya_admin);
			BiayaAdminPulsa(pulsa);
			printf("Biaya Admin Berhasil Diperbarui!\n");
			break;
		case 2:
			printf("Masukan Biaya Admin Token yang Baru :");
			scanf("%d", &token->biaya_admin);
			BiayaAdminToken(token);
			printf("Biaya Admin Berhasil Diperbarui!\n");
			break;
		case 0:
			menuAdmin(pulsa, token);
		default:
			printf("Pilihan Tidak Valid");
			break;
	}
}

void editUser() {
    FILE *file = fopen("user_data.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    char user[50];
    int i = 0;
    int pilih;

    printf("Masukkan Username yang Mau di Edit : ");
    scanf("%s", user);

    while (i < 100) {
        if (strcmp(user, usersDatabase[i].username) == 0) {
            printf("Apa yang mau di ubah ?\n1. Username\n2. Password\n");
            printf("Pilihan : ");
            scanf("%d", &pilih);  // Corrected the address-of operator

            switch (pilih) {
                case 1:
                    printf("Masukkan Username yang baru : ");
                    scanf("%s", usersDatabase[i].username);
                    fprintf(file, "%s %s\n", usersDatabase[i].username, usersDatabase[i].password);
                    fclose(file);
                    break;
                case 2:
                    printf("Masukkan Password yang baru : ");
                    scanf("%s", usersDatabase[i].password);
                    fprintf(file, "%s %s\n", usersDatabase[i].username, usersDatabase[i].password);
                    fclose(file);
                    break;
                default:
                    printf("Pilihan tidak valid\n");
                    break;
            }
            break;  // Added a break to exit the loop after editing the user
        }
        i++;
    }
}
	
void loadUserDataFromFile() {
    FILE *file = fopen("user_data.txt", "r");
    if (file != NULL) {
        int i = 0;
        while (fscanf(file, "%s %s %s %s", usersDatabase[i].username, usersDatabase[i].password, usersDatabase[i].role, usersDatabase[i].pin) != EOF && i < 100) {
        	//printf("Read Data : %s %s %s", usersDatabase[i].username, usersDatabase[i].password, usersDatabase[i].role);
            i++;
        }
        fclose(file);
    } else {
        printf("Gagal membuka file untuk memuat data pengguna.\n");
    }
}

void showAllUsers(PembelianPulsa *pulsa, PembelianToken *token) {
    printf("Daftar Pengguna:\n==============================\n");
    int i = 0;
    while (i < 100) {
        if (strlen(usersDatabase[i].username) == 0) {
            break;
        }
        printf("Username: %s\nRole: %s\n---------------------------\n", usersDatabase[i].username, usersDatabase[i].role);
        i++;
    }printf("==============================\n");
    menuAdmin(pulsa, token);
}

void removeUser() {
    char username[50];
    printf("Masukkan username pengguna yang ingin dihapus: ");
    scanf("%s", username);

    int i = 0;
    while (i < 100) {
        if (strcasecmp(username, usersDatabase[i].username) == 0) {
            // Hapus pengguna dengan menggeser elemen array
            while (i < 99 && strlen(usersDatabase[i + 1].username) != 0) {
                usersDatabase[i] = usersDatabase[i + 1];
                i++;
            }
            memset(&usersDatabase[i], 0, sizeof(struct User)); // Nolkan elemen terakhir
            printf("Pengguna dengan username %s berhasil dihapus.\n", username);
            return;
        }
        i++;
    }

    printf("Pengguna dengan username %s tidak ditemukan.\n", username);
}



void riwayatTransaksiPulsa(PembelianPulsa *pulsa) {
    FILE *file = fopen("transaksi.txt", "r");
    if (file != NULL) {
        int i = 0;
        while (fscanf(file, "%s %s %lf %s", pulsa[i].transaksi.jenis, pulsa[i].transaksi.nomor_telepon, &pulsa[i].transaksi.harga, pulsa[i].transaksi.day) != EOF && i < 100) {
            //printf("Read data: %s %s %.0lf %s\n", pulsa[i].transaksi.jenis, pulsa[i].transaksi.nomor_telepon, pulsa[i].transaksi.harga, pulsa[i].transaksi.day);
            i++;
        }
        //printf("%d\n", count);
        fclose(file);
    } else {
        printf("Gagal membuka file untuk memuat data transaksi pulsa.\n");
    }
}

void showTransaksi(PembelianPulsa *pulsa, PembelianToken *token) {
	FILE *file = fopen("transaksi.txt", "r");
    printf("===Riwayat Transaksi===\n");
    //printf("%d\n", &count);
    int hari;
    int pilih;
    int jenis;
    int i = 0;
    do{
    	printf("Mau Cari Berdasarkan Apa?\n1. Jenis Transaksi\n2. Hari\n3. Tampilkan Semua\n0. Keluar\n");
	    printf("Pilihan : ");
	    scanf("%d", &pilih);
	    switch(pilih){
	    	case 1:
	    		printf("1. Pulsa\n2. Token\n0. Keluar\n");
	    		printf("Pilihan Anda : ");
	    		scanf("%d", &jenis);
	    		switch(jenis){
	    			case 1:
	    				while (i < 100){
			    			if (strcmp(pulsa[i].transaksi.jenis, "Pulsa") == 0 ) {
				            printf("Jenis: %s | Nomor Telepon: %s | Harga: %.0f | Hari : %s\n",pulsa[i].transaksi.jenis, pulsa[i].transaksi.nomor_telepon, pulsa[i].transaksi.harga, pulsa[i].transaksi.day);   
				        	}
							i++;
							}
						break;
					case 2:
						while (i < 100){
			    			if (strcmp(pulsa[i].transaksi.jenis, "Token") == 0 ){
				        	printf("Jenis: %s | Nomor ID: %s | Harga: %.0f | Hari : %s\n",pulsa[i].transaksi.jenis, pulsa[i].transaksi.nomor_telepon, pulsa[i].transaksi.harga, pulsa[i].transaksi.day);
							}
							i++;
							}
						break;	
				}
				break;
	    	case 2:
	    		printf("Mau Berdasarkan Hari Apa?\n1. Senin\n2. Selasa\n3. Rabu\n4. Kamis\n5. Jumat\n6. Sabtu\n7. Minggu\n");
			    printf("Pilihan Anda : ");
			    scanf("%d", &hari);
			    switch(hari){
			    	case 1:
			    		while (i < 100){
				    			if ((strcmp(pulsa[i].transaksi.day, "Senin") == 0 && (hari == 1 || hari == 8))) {
					            printf("Nomor Telepon: %s | Harga: %.0f | Hari : %s\n", pulsa[i].transaksi.nomor_telepon, pulsa[i].transaksi.harga, pulsa[i].transaksi.day);
					            
					        }else if (strcmp(pulsa[i].transaksi.day, "Senin") == 0 && (hari == 1 || hari == 8)){
					        	printf("Nomor ID: %s | Harga: %.0f | Hari : %s\n", token[i].transaksi.nomor_ID, token[i].transaksi.harga, token[i].transaksi.day);
							}
							i++;
							}
						break;
					case 2:
						while (i < 100){
				    			if ((strcmp(pulsa[i].transaksi.day, "Selasa") == 0 && (hari == 2 || hari == 8))) {
					            printf("Nomor Telepon: %s | Harga: %.0f | Hari : %s\n", pulsa[i].transaksi.nomor_telepon, pulsa[i].transaksi.harga, pulsa[i].transaksi.day);
					            
					        }else if (strcmp(token[i].transaksi.day, "Selasa") == 0 && (hari == 2 || hari == 8)){
					        	printf("Nomor ID: %s | Harga: %.0f | Hari : %s\n", token[i].transaksi.nomor_ID, token[i].transaksi.harga, token[i].transaksi.day);
							}
							i++;
							}
						break;
					case 3:
						while (i < 100){
				    			if ((strcmp(pulsa[i].transaksi.day, "Rabu") == 0 && (hari == 3 || hari == 8))) {
					            printf("Nomor Telepon: %s | Harga: %.0f | Hari : %s\n", pulsa[i].transaksi.nomor_telepon, pulsa[i].transaksi.harga, pulsa[i].transaksi.day);
					            
					        }else if (strcmp(token[i].transaksi.day, "Rabu") == 0 && (hari == 3 || hari == 8)){
					        	printf("Nomor ID: %s | Harga: %.0f | Hari : %s\n", token[i].transaksi.nomor_ID, token[i].transaksi.harga, token[i].transaksi.day);
							}
							i++;
							}
						break;
					case 4:
						while (i < 100){
				    			if ((strcmp(pulsa[i].transaksi.day, "Kamis") == 0 && (hari == 4 || hari == 8) && (strcmp(pulsa[i].transaksi.jenis, "Pulsa")==0))) {
					            printf("Nomor Telepon: %s | Harga: %.0f | Hari : %s\n", pulsa[i].transaksi.nomor_telepon, pulsa[i].transaksi.harga, pulsa[i].transaksi.day);
					            
					        }else if (strcmp(pulsa[i].transaksi.day, "Kamis") == 0 && (hari == 4 || hari == 8) && (strcmp(pulsa[i].transaksi.jenis, "Token")==0)){
					        	printf("Nomor ID: %s | Harga: %.0f | Hari : %s\n", pulsa[i].transaksi.nomor_telepon, pulsa[i].transaksi.harga, pulsa[i].transaksi.day);
							}
							i++;
							}
						break;
					case 5:
						while (i < 100){
				    			if ((strcmp(pulsa[i].transaksi.day, "Jumat") == 0 && (hari == 5 || hari == 8))) {
					            printf("Nomor Telepon: %s | Harga: %.0f | Hari : %s\n", pulsa[i].transaksi.nomor_telepon, pulsa[i].transaksi.harga, pulsa[i].transaksi.day);
					            
					        }else if (strcmp(token[i].transaksi.day, "Jumat") == 0 && (hari == 5 || hari == 8)){
					        	printf("Nomor ID: %s | Harga: %.0f | Hari : %s\n", token[i].transaksi.nomor_ID, token[i].transaksi.harga, token[i].transaksi.day);
							}
							i++;
							}
						break;
					case 6:
						while (i < 100){
				    			if ((strcmp(pulsa[i].transaksi.day, "Sabtu") == 0 && (hari == 6 || hari == 8))) {
					            printf("Nomor Telepon: %s | Harga: %.0f | Hari : %s\n", pulsa[i].transaksi.nomor_telepon, pulsa[i].transaksi.harga, pulsa[i].transaksi.day);
					            
					        }else if (strcmp(token[i].transaksi.day, "Sabtu") == 0 && (hari == 6 || hari == 8)){
					        	printf("Nomor ID: %s | Harga: %.0f | Hari : %s\n", token[i].transaksi.nomor_ID, token[i].transaksi.harga, token[i].transaksi.day);
							}
							i++;
							}
						break;
					case 7:
						while (i < 100){
				    			if ((strcmp(pulsa[i].transaksi.day, "Minggu") == 0 && (hari == 7 || hari == 8))) {
					            printf("Nomor Telepon: %s | Harga: %.0f | Hari : %s\n", pulsa[i].transaksi.nomor_telepon, pulsa[i].transaksi.harga, pulsa[i].transaksi.day);
					            
					        }else if (strcmp(token[i].transaksi.day, "Minggu") == 0 && (hari == 7 || hari == 8)){
					        	printf("Nomor ID: %s | Harga: %.0f | Hari : %s\n", token[i].transaksi.nomor_ID, token[i].transaksi.harga, token[i].transaksi.day);
							}
							i++;
							}
						break;
				}
				break;
			case 3:
				while (i < 100){
	    			if (strcmp(pulsa[i].transaksi.jenis, "Pulsa") == 0 ) {
		            	printf("Jenis: %s | Nomor Telepon : %s | Harga: %.0f | Hari : %s\n",pulsa[i].transaksi.jenis, pulsa[i].transaksi.nomor_telepon, pulsa[i].transaksi.harga, pulsa[i].transaksi.day);   
		        	}else if (strcmp(pulsa[i].transaksi.jenis, "Token") == 0 ){
			        	printf("Jenis: %s | Nomor ID      : %s | Harga: %.0f | Hari : %s\n",pulsa[i].transaksi.jenis, pulsa[i].transaksi.nomor_telepon, pulsa[i].transaksi.harga, pulsa[i].transaksi.day);
					}
					i++;
					}
				break;
			case 0:
	        	printf("Terima kasih telah menggunakan layanan kami.\n");
	        	exit(0);
	    	default:
	    		printf("Pilihan tidak valid. Silakan coba lagi.\n");
                break;
		}
	}while(pilih>3);
    
    

}

int adminLogin() {
    char username[50], password[50];
    int loginSuccess = 0; // Tambahkan variabel untuk menyimpan status login

    do {
        printf("Masukkan username admin: ");
        scanf("%s", username);
        printf("Masukkan password admin: ");
        scanf("%s", password);

        if ((strcmp(username, Akmal.username) == 0 && strcmp(password, Akmal.password) == 0) ||
            (strcmp(username, Bandi.username) == 0 && strcmp(password, Bandi.password) == 0)) {
            printf("Login berhasil sebagai admin!\n");
            loginSuccess = 1;
        } else {
            printf("Login gagal. Username atau password salah. Silakan coba lagi.\n");
        }
    } while (!loginSuccess); // Ulangi proses jika login gagal

    return 1; 
}


int menuAdmin(PembelianPulsa *pulsa, PembelianToken *token){
	int choice;
	printf("=== Selamat datang ===\n");
	do{
        printf("1. Ubah Biaya Admin\n");
        printf("2. Hapus Akun User\n");
        printf("3. Tampilkan semua pengguna\n");
        printf("4. Tampilkan Riwayat Pembelian\n");
        printf("5. Edit User\n");
        printf("6. Logout\n");
        printf("0. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &choice);
        Cls();
        switch(choice){
        	case 1:
        		ubahBiayaAdmin(pulsa, token);
        		menuAdmin(pulsa, token);
        		break;
        	case 2:
        		removeUser();
        		menuAdmin(pulsa, token);
        		break;
        	case 3:
        		showAllUsers(pulsa, token);
        		menuAdmin(pulsa, token);
        		break;
        	case 4:
        		showTransaksi(pulsa, token);
        		menuAdmin(pulsa, token);
        		break;
        	case 5:
        		editUser();
        	case 6:
        		menuLogin(pulsa, token);
        	case 0:
        		return 0;
        	default:
        		printf("Pilihan tidak valid. Silakan coba lagi.\n");
                break;
		}
	}while(choice>4);
	
}

int userLogin() {
    char username[50], password[50];
    printf("Masukkan username: ");
    scanf("%s", username);
    printf("Masukkan password: ");
    scanf("%s", password);

    int i = 0;
    while (i < 100) {
        if (strcmp(username, usersDatabase[i].username) == 0 && strcmp(password, usersDatabase[i].password) == 0) {
            Cls();
			printf("Login berhasil sebagai pengguna!\n");
            
            return 1;
        }
        i++;
    }

    printf("Login gagal. Username atau password salah.\n");
    return 0;
}

void userSignUp() {
    char username[50], password[50], pin[7];
    int usernameExists;
    

    do { // Setel flag ke 0 di awal loop
    	usernameExists = 0;
        printf("Masukkan username baru: ");
        scanf("%s", username);

        int i = 0;
        while (i < 100) {
            if (strcmp(username, usersDatabase[i].username) == 0) {
                printf("Username sudah digunakan. Silakan coba username lain.\n");
                usernameExists = 1; // Setel flag ke 1 jika username sudah ada
                break;
            }
            i++;
        }
    } while (usernameExists); // Ulangi proses jika username sudah ada

    printf("Masukkan password baru: ");
    scanf("%s", password);
    printf("Masukkan PIN : ");
    scanf("%s", pin);

    struct User newUser;
    strcpy(newUser.username, username);
    strcpy(newUser.password, password);
    strcpy(newUser.pin, pin);
    strcpy(newUser.role, "User");

    int i = 0;
    while (i < 100) {
        if (strlen(usersDatabase[i].username) == 0) {
            usersDatabase[i] = newUser;
            break;
        }
        i++;
    }

    printf("Pendaftaran berhasil!\n");
    Cls();
}

//void menuLogin(){
//	
//}

int menuLogin(PembelianPulsa *pulsa, PembelianToken *token) {
    riwayatTransaksiPulsa(pulsa);
    //riwayatTransaksiToken(token, count);
    loadUserDataFromFile();
    int choice;
    char input[4];
    int isLoggedIn = 0; // Tambahkan variabel untuk menyimpan status login
    char akun[2];

    do {
        printf("=== Selamat datang ===\n");
        printf("1. Login sebagai admin\n");
        printf("2. Login atau sign up sebagai pengguna\n");
        printf("0. Keluar\n");
        printf("Pilihan: ");
        scanf("%s", &input);
		int isValidInput = 1;
		int i = 0;
        //for (int i = 0; input[i] != '\0'; i++) 
		while (input[i]!='\0'){
            if (!isdigit(input[i])) {
                isValidInput = 0;
                break;
            }
            i++; 
        }

        if (!isValidInput) {
            Cls();
			printf("Masukkan angka saja. Silakan coba lagi.\n");
            continue;  // Ulangi loop jika input tidak valid
        }

        sscanf(input, "%d", &choice);  // Ubah input menjadi integer

        Cls();
        switch (choice) {
            case 1:
                isLoggedIn = adminLogin();
                if (isLoggedIn) {
                    menuAdmin(pulsa, token);
                }
                break;
            case 2:
                printf("Sudah Punya Akun (Y/T)?");
                scanf("%s", akun);
                if (strcasecmp(akun, "Y") == 0) {
                    isLoggedIn = userLogin();
                    if (isLoggedIn) {
                        pilihTransaksi(pulsa, token);
                    } else {
                        printf("Login gagal. Silakan coba lagi.\n");
                    }
                } else if (strcasecmp(akun, "T") == 0) {
                    userSignUp();
                    saveUserDataToFile();
                    isLoggedIn = userLogin();
                    if (isLoggedIn) {
                        pilihTransaksi(pulsa, token);
                    } else {
                        printf("Login gagal. Silakan coba lagi.\n");
                    }
                } else {
                    printf("Input Tidak Valid\n");
                }
                break;
            case 0:
                saveUserDataToFile();
                printf("Terima kasih telah menggunakan layanan kami.\n");
                return 0;
            default:
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
                break;
        }
    } while (choice > 4 || !isLoggedIn); // Ulangi proses jika pilihan tidak valid atau login gagal
    return 0;
}


