
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

typedef struct Items{ //sebagai list item yang dijual (-oleh Rain)
	char name[25];
	int price;
	int stok;
}items;

struct solditems{ // sebagai catatan penjualan (-oleh Rain)
	char name[25]; 
	int amount;
	
};

struct node{ // sebagai linked list catatan penjualan (-oleh Rain)
	struct solditems *sold;
	int totalprice;
	int itemcount;
	struct node *link;
};

void createFile(){ // agar menbuat file dan data baru jika belum ada/tidak ditemukan (-oleh Rain)
	items *itemptr;
	int itemtotal=0;
	int i;
	int create = 1;
	
	FILE *fptr;
	printf("cant find items.txt file! create new (input 1) or exit program (input 0)\n");
	scanf("%d", &create);
	if(create == 0){
		exit(1);
	}
	
	fptr = fopen("D:\\try\\items.txt","w");
	while(create == 1){ //================================ mendaftarkan item item yang dijual (-oleh Rain) 
		int n;
		printf("\nhow many item u wanna add? (max = 16 items, available = %d item/s)\n= ", 16-itemtotal);
		scanf("%d", &n);
		itemptr = (items*)calloc(n, sizeof(items));
		
		while(itemtotal+n > 16){ //======================= memaksa user hanya dapat mendaftarkan 16 merek item agar program lebih mudah dikerjakan (-oleh Rain)
			printf("\ncant add that many, input again\n");
			scanf("%d", &n);
		}
		for(i=itemtotal; i<itemtotal+n; i++){ //========== user menginput item (-oleh Rain)
			printf("\n#%d product\nname : ", i+1);
			scanf("%s", &itemptr[i].name);
			printf("price, stok = ");
			scanf("%d %d", &itemptr[i].price, &itemptr[i].stok);
			fwrite(&itemptr[i], sizeof(items), 1, fptr);
		}
		itemtotal += n;
			
		if(itemtotal == 16){
			printf("\n==Has reached its max, cant add no more==\n");
			break;
		}
		printf("\nwanna add more? yes (input 1) or no (input 0)\n");
		scanf("%d", &create);
	}
	fclose(fptr);
}

void readFile(items item[]){ // ========================== mengcopy isi file ke array item[] (-oleh Rain)

	items product;
	int i=0;
	
	FILE *fptr;
	fptr = fopen("D:\\try\\items.txt","r");
	
	while(fread(&product,sizeof(items),1,fptr)){
		strcpy(item[i].name, product.name);
		item[i].price = product.price;
		item[i].stok = product.stok;
		i++;
	}
	fclose(fptr);
}

void writeFile(int itemtotal, items item[]){ // =============== meng-rewrite isi array item[] ke file (-oleh Rain)
	items *itemptr;
	
	FILE *fptr;
	fptr = fopen("D:\\try\\items.txt","w");
	
	itemptr = (items*)calloc(itemtotal, sizeof(items));
	int i;
	for(i=0; i<itemtotal; i++){
		strcpy(itemptr[i].name, item[i].name);
		itemptr[i].price = item[i].price;
		itemptr[i].stok = item[i].stok;
		fwrite(&itemptr[i], sizeof(items), 1, fptr);
	}
	fclose(fptr);
}

void displayFile(){ // ====================================== menampilkan data dari isi file
	items product;
	int i=0;
	
	FILE *fptr;
	fptr = fopen("D:\\try\\items.txt","r");
	
	printf("\n#\tproduct\tprice\tstok\n");
	while(fread(&product,sizeof(items),1,fptr)){
		printf("#%d\t%s\t%d\t%d\n", i+1, product.name, product.price, product.stok);
		i++;
	}
	fclose(fptr);
}

void addData(){ //============================================ menambahkan item item ke file (-oleh Rain)
	items *itemptr;
	int itemtotal;
	int i;
	int create = 1;
	
	FILE *fptr;
	fptr = fopen("D:\\try\\items.txt","a");
	fseek(fptr,0,SEEK_END);
	itemtotal = ftell(fptr)/sizeof(items);
	
	
	while(create == 1){
		int n;
		printf("\nhow many item u wanna add? (max = 16 items, available = %d item/s)\n= ", 16-itemtotal);
		scanf("%d", &n);
		itemptr = (items*)calloc(n, sizeof(items));
		
		while(itemtotal+n > 16){
			printf("\ncant add that many, input again\n");
			scanf("%d", &n);
		}
		for(i=0; i<n; i++){  
			printf("\n#%d product\nname : ", i+itemtotal+1);
			scanf("%s", &itemptr[i].name);
			printf("price, stok = ");
			scanf("%d %d", &itemptr[i].price, &itemptr[i].stok);
			fwrite(&itemptr[i], sizeof(items), 1, fptr);
		}
		itemtotal += n;
			
		if(itemtotal == 16){
			printf("\n==Has reached its max, cant add no more==\n");
			break;
		}
		printf("\nwanna add more? yes (input 1) or back (input 0)\n");
		scanf("%d", &create);
	}
	fclose(fptr);
}

int main(){
	items item[16];
	int customer;

	int itemtotal;
	FILE *fptr;
	
	struct node *head = NULL;
	struct node *current = NULL;
	struct node *previous = NULL;
	struct solditems *soldptr;
	
	if((fptr = fopen("D:\\try\\items.txt","r")) == NULL){ // jika file tidak ditemukan, akan dibuat (-oleh Rain)
		createFile();
	}
	
	
	int run=1; // ============================= loop agar program tidak langsung tertutup, juga agar user dapat secara manual menutup program (-oleh Rain)
	while(run == 1){
		int optionmenu;
		printf("\n===== Menu =====\n1. Items\n2. Cashier\n3. Show Sales Record\n0. Exit\n= ");
		scanf("%d", &optionmenu);


		if(optionmenu == 0){
			run = 0;
		}
		while(optionmenu == 1){
			readFile(item);
			
			fptr = fopen("D:\\try\\items.txt","r"); //}====================================== menghitung item item yang sudah di-list (-oleh Rain)
			fseek(fptr,0,SEEK_END);//                 }
			itemtotal = ftell(fptr)/sizeof(items);//  }
			fclose(fptr);//                           }
			
			printf("\n%d\n", itemtotal);
			
			
			int optionitem;
			printf("\n\n===== items option =====\n1. Display\n2. Add item\n3. Remove Item\n4. Edit price/stok\n0. Back\n= ");
			scanf("%d", &optionitem);

			if(optionitem == 0){ // ============================================= option jika user ingin keluar dari item option;
				break;
			}
			if(optionitem == 1){
				displayFile();
			}
			if(optionitem == 2){
				addData();
			}
			if(optionitem == 3){
				displayFile();
				int selectitem;
				printf("which item u wanna remove? input the number, input 0 cancel/done\n");
				int loop = 1;
				while(loop == 1){
					scanf("%d", &selectitem);
					
					if(selectitem == 0){//=========== loop yang berfungsi sebagai select dan me-replace data yang di-select (-oleh Rain)
						break;
					}
					else{
						int i;
						for(i=selectitem-1; i<itemtotal; i++){ 
							strcpy(item[i].name, item[i+1].name);
							item[i].price = item[i+1].price;
							item[i].stok = item[i+1].stok;
						}
					itemtotal--;
					}
				}
				writeFile(itemtotal, item);
			}
			if(optionitem == 4){//=========== loop yang berfungsi sebagai select dan re-input data yang di-select (-oleh Rain)
				displayFile();
				int selectitem;
				int loop = 1;
				while(loop == 1){
					printf("which item u wanna edit? input the number, input 0 cancel/done\n= ");
					scanf("%d", &selectitem);
					if(selectitem == 0){
						break;
					}
					printf("product name = "); scanf("%s", &item[selectitem-1].name);
					printf("price, stok = "); scanf("%d %d", &item[selectitem-1].price, &item[selectitem-1].stok);
					printf("\nedit again? yes (input 1) back (input 0)\n= ");
					scanf("%d", &loop);
				}
				writeFile(itemtotal, item);
			}
		}
		if(optionmenu == 2){ // kasir dan mencatat hasil penjualan
			
			int number;
			int amount;
			int i=0;
			
			readFile(item);
			displayFile();
			
			int loop = 1;
			
			while(loop == 1){
				int count = 0;
				int totalprice = 0;
				
				printf("\nnumber of product, and amount(input '0 0' if u re done)\n= ");
				
				current = malloc(sizeof(struct node));
				soldptr = (struct solditems*)calloc(itemtotal, sizeof(struct solditems*));
				
				
				int loop2 = 1;
				
				while(loop2 == 1){
					
					
					scanf("%d %d", &number, &amount);
					
					if(number == 0 && amount == 0){
						current->link = NULL;
						break;
					}
					totalprice += item[number-1].price * amount;
					item[number-1].stok = item[number-1].stok - amount;
					
					printf("%s x %d @%d = %d\n\n", item[number-1].name, amount, item[number-1].price, totalprice);
					
					strcpy(soldptr[number-1].name, item[number-1].name);
					soldptr[number-1].amount = amount;
					count++;
				}
				current->sold = soldptr;
				current->totalprice = totalprice;
				current->itemcount = count;
				
				if(i == 0){
					head = current;
					previous = current;
				}
				else{
					previous->link = current;
					previous = current;
				}
				
				printf("\nur total = %d\n", totalprice);
				printf("\nnext customer? yes(1), back to item menu(0)\n= ");
				scanf("%d", &loop);
				i++; customer = i;
				
			}
			//writeFile(itemtotal, item);
			
		}
		if(optionmenu == 3){ // menampilkan catatan penjualan
			int i;
			#pragma omp parallel
			{
				#pragma omp for
				for(i=0; i<customer; i++){
					if(i == 0){
						current = head;
						previous = head;
					}
					else{
						current = current->link;
					}
					
					printf("\nCustomer #%d\n",i+1);
					int j;
					for(j=0; j<current->itemcount; j++){
						printf("name product: %s , amount = %d\n", current->sold->name, current->sold->amount);
					}
					printf("total price = %d\n", current->totalprice);
				}
			}
			
		}
		
	}
	
	
	
}




