#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>

int nacrtaj_iks(int x, int y , int boja);
int nacrtaj_trougao(int x, int y, int boja);
int nacrtaj_kvadrat(int x, int y, int boja);
int nacrtaj_krug(float x, float y, int boja);
int nacrtaj_smajli(int vrsta_smajlija);
int ocitaj_tastere();

int main(){
	
	int gen_oblici[6];
	int pokusaj[6];
	int stanje = 0;
	int brojac = 0;
	int oblik;
	int i = 0;
	int k = 0;
	int x_k = 0;
	int y_k = 0;
	FILE *fp;
	int kk = 1;
	int greska = 0;
	
	//obrisi_sve();
	nacrtaj_smajli(2);	
	for(y_k=0; y_k<61; y_k++){
		for(x_k=0; x_k<500; x_k++){
			fp = fopen("/dev/vga_dma", "w");
			if(fp == NULL){
				printf("Cannot open /dev/vga for write\n");
				return -1;
			}
			fprintf(fp,"%d,%d,%#04x\n",x_k,y_k,0);
			fclose(fp);
			if(fp==NULL){
				printf("Cannot close /dev/vga\n");
				return -1;
			}
		}	
	}				
	
	while(1){
		switch(stanje){
			
			case 0:
				oblik = rand()%4 + 1;
				gen_oblici[brojac] = oblik;
				printf("%d\n",gen_oblici[brojac]);
				brojac++;
				if(brojac == 6){
					brojac = 0;
					stanje = 1;
				}				
				break;
			
			case 1:
				for(i = 0; i < 6; i++){
					if(gen_oblici[i] == 1){
						nacrtaj_krug((i+1)*70,30,16777215);
					}
					else if(gen_oblici[i] == 2){
						nacrtaj_trougao((i+1)*70, 30,16777215);
					}
					else if(gen_oblici[i] == 3){
						nacrtaj_iks((i+1)*70,30,16777215);
					}
					else if(gen_oblici[i]==4){
						nacrtaj_kvadrat((i+1)*70,30,16777215);
					}
				}				
				sleep(2);
				for(i = 0; i < 6; i++){
					if(gen_oblici[i] == 1){
						nacrtaj_krug((i+1)*70,30,0);
					}
					else if(gen_oblici[i] == 2){
						nacrtaj_trougao((i+1)*70,30,0);
					}
					else if(gen_oblici[i] == 3){
						nacrtaj_iks((i +1)*70,30,0);
					}
					else{
						nacrtaj_kvadrat((i +1)*70,30,0);
					}
				}
				/*for(y_k=0; y_k<61; y_k++){
					for(x_k=0; x_k<420; x_k++){
						fp = fopen("/dev/vga_dma", "w");
						if(fp == NULL){
							printf("Cannot open /dev/vga for write\n");
							return -1;
						}
						fprintf(fp,"%d,%d,%#04x\n",x_k,y_k,0);
						fclose(fp);
						if(fp==NULL){
							printf("Cannot close /dev/vga\n");
							return -1;
						}
					}	
				}*/				
				stanje = 2;
				break;
				
			case 2:				
				k = ocitaj_tastere();
				printf("%d\n", k);
				if(k != 0 && kk == 1){
					kk = 0;
					usleep(10000);
					stanje = 3;
					break;	}
				else if(k==0){
					kk = 1;
					usleep(10000);
				}
				break;
				
			case 3:
				if(k != 0){
					pokusaj[brojac] = k;
					if(gen_oblici[brojac] == pokusaj[brojac]){
						if(gen_oblici[brojac] == 1){
							nacrtaj_krug((brojac+1)*70,30,2016);
						}
						else if(gen_oblici[brojac] == 2){
							nacrtaj_trougao((brojac +1)*70,30,2016);
						}
						else if(gen_oblici[brojac] == 3){
							nacrtaj_iks((brojac +1)*70,30,2016);
						}
						else{
							nacrtaj_kvadrat((brojac+1)*70,30,2016);
						}
					}
					else{
						if(gen_oblici[brojac] == 1){
							nacrtaj_krug((brojac +1)*70,30,63488);
						}
						else if(gen_oblici[brojac] == 2){
							nacrtaj_trougao((brojac+1)*70,30,63488);
						}
						else if(gen_oblici[brojac] == 3){
							nacrtaj_iks((brojac +1)*70,30,63488);
						}
						else{
							nacrtaj_kvadrat((brojac +1)*70,30,63488);
						}
						greska++;
					}
					brojac++;
					if(brojac == 6){
						brojac = 0;
						stanje = 4;
						break;
					}
				}
				stanje = 2;
				break;
			
			case 4: 
				if(greska > 0){
					nacrtaj_smajli(0);
				}
				else{
					nacrtaj_smajli(1);
				}
				greska = 0;
				sleep(5);
				stanje = 0;
				for(i = 0; i < 6; i++){
					if(gen_oblici[i] == 1){
						nacrtaj_krug((i+1)*70,30,0);
					}
					else if(gen_oblici[i] == 2){
						nacrtaj_trougao((i+1)*70,30,0);
					}
					else if(gen_oblici[i] == 3){
						nacrtaj_iks((i +1)*70,30,0);
					}
					else{
						nacrtaj_kvadrat((i +1)*70,30,0);
					}
				}
				/*for(y_k=0; y_k<61; y_k++){
					for(x_k=0; x_k<420; x_k++){
						fp = fopen("/dev/vga_dma", "w");
						if(fp == NULL){
							printf("Cannot open /dev/vga for write\n");
							return -1;
						}
						fprintf(fp,"%d,%d,%#04x\n",x_k,y_k,0);
						fclose(fp);
						if(fp==NULL){
							printf("Cannot close /dev/vga\n");
							return -1;
						}
					}	
				}*/			
				//brisemo smajli
				nacrtaj_smajli(2);
				break;
		}
	}
	return 0;
}


int nacrtaj_iks(int x, int y , int boja){
	
	int pomeraj = 0;
	FILE* fp;
	int tmp = y;
	while(tmp < y + 30){
		fp = fopen("/dev/vga_dma", "w");
		if(fp == NULL)
		{
			printf("Cannot open /dev/vga for write\n");
			return -1;
		}
		fprintf(fp,"%d,%d,%#04x\n",x+pomeraj,tmp,boja);
		fclose(fp);
		if(fp==NULL){
			printf("Cannot close /dev/vga\n");
			return -1;
		}
		tmp++;
		pomeraj++;
	}
	
	tmp--;
	pomeraj = 0;
	
	while(tmp > y){
		
		fp = fopen("/dev/vga_dma", "w");
		if(fp == NULL)
		{
			printf("Cannot open /dev/vga for write\n");
			return -1;
		}
		fprintf(fp,"%d,%d,%#04x\n",x+pomeraj,tmp,boja);
		fclose(fp);
		if(fp==NULL){
			printf("Cannot close /dev/vga\n");
			return -1;
		}
		tmp--;
		pomeraj++;
	}
}

int nacrtaj_kvadrat(int x, int y, int boja){
	int pomeraj = 30;
	FILE* fp;
	
	int j;
	for(j=x; j<x+pomeraj; j++){
		fp = fopen("/dev/vga_dma", "w");
		if(fp == NULL)
		{
			printf("Cannot open /dev/vga for write\n");
			return -1;
		}
		fprintf(fp,"%d,%d,%#04x\n",j,y,boja);
		fclose(fp);
		if(fp==NULL){
			printf("Cannot close /dev/vga\n");
			return -1;
		}
	}

	for(j=y; j<y+pomeraj; j++){
		fp = fopen("/dev/vga_dma", "w");
		if(fp == NULL)
		{
			printf("Cannot open /dev/vga for write\n");
			return -1;
		}
		fprintf(fp,"%d,%d,%#04x\n",x,j,boja);
		fclose(fp);
		if(fp==NULL){
			printf("Cannot close /dev/vga\n");
			return -1;
		}
	}

	for(j=x; j<x+pomeraj; j++){
		fp = fopen("/dev/vga_dma", "w");
		if(fp == NULL)
		{
			printf("Cannot open /dev/vga for write\n");
			return -1;
		}
		fprintf(fp,"%d,%d,%#04x\n",j,y+pomeraj,boja);
		fclose(fp);
		if(fp==NULL){
			printf("Cannot close /dev/vga\n");
			return -1;
		}
	}

	for(j=y; j<=y+pomeraj; j++){
		fp = fopen("/dev/vga_dma", "w");
		if(fp == NULL)
		{
			printf("Cannot open /dev/vga for write\n");
			return -1;
		}
		fprintf(fp,"%d,%d,%#04x\n",x+pomeraj,j,boja);
		fclose(fp);
		if(fp==NULL){
			printf("Cannot close /dev/vga\n");
			return -1;
		}
	}

}


int nacrtaj_trougao(int x, int y, int boja){
	int pomeraj = 1;
	FILE* fp;
	int tmp = y;
	
	fp = fopen("/dev/vga_dma", "w");
	if(fp == NULL)
	{
		printf("Cannot open /dev/vga for write\n");
		return -1;
	}
	fprintf(fp,"%d,%d,%#04x\n",x+16,y,boja);
	fclose(fp);
	if(fp==NULL){
		printf("Cannot close /dev/vga\n");
		return -1;
	}
	
	while(tmp < y + 30){
		tmp++;	
		fp = fopen("/dev/vga_dma", "w");
		if(fp == NULL)
		{
			printf("Cannot open /dev/vga for write\n");
			return -1;
		}
		fprintf(fp,"%d,%d,%#04x\n",x+16+pomeraj,tmp,boja);
		fclose(fp);
		if(fp==NULL){
			printf("Cannot close /dev/vga\n");
			return -1;
		}
		fp = fopen("/dev/vga_dma", "w");
		if(fp == NULL)
		{
			printf("Cannot open /dev/vga for write\n");
			return -1;
		}
		fprintf(fp,"%d,%d,%#04x\n",x+16-pomeraj,tmp,boja);
		fclose(fp);
		if(fp==NULL){
			printf("Cannot close /dev/vga\n");
			return -1;
		}
		pomeraj++;
	}
	pomeraj--;
	int j;
	for(j=x+16-pomeraj; j<x+16+pomeraj; j++){
		fp = fopen("/dev/vga_dma", "w");
		if(fp == NULL)
		{
			printf("Cannot open /dev/vga for write\n");
			return -1;
		}
		fprintf(fp,"%d,%d,%#04x\n",j,tmp,boja);
		fclose(fp);
		if(fp==NULL){
			printf("Cannot close /dev/vga\n");
			return -1;
		}
	}

	
}
int nacrtaj_krug(float x, float y, int boja){
	FILE* fp;
	float ugao=0;
	float korak=2*3.14159265359/100;
	
	fp = fopen("/dev/vga_dma", "w");
	if(fp == NULL)
   	 {	
		printf("Cannot open /dev/vga_dma for write\n");
		return -1;
   	 }
	for(ugao=0; ugao< 2*3.14159265359 ; ugao+=korak){
        	fprintf(fp,"%d,%d,%#04x\n",(int)(x +15 + 15*cos(ugao)),(int)(y+15-15*sin(ugao)),boja);
        	fflush(fp);		
   	 }
  	if(fclose(fp) == EOF)
    	{
     		 printf("Cannot close /dev/vga\n");
     		 return -1;
   	 }

}

int nacrtaj_smajli(int vrsta_smajlija){ //0 za tuznog, 1 za srecnog, 2 za brisanje
	FILE* fp;
	float ugao=0;
	float korak=2*3.14159265359/200;
	int boja;
	float x;
	float y;
	
	if(vrsta_smajlija == 0 || vrsta_smajlija == 1){
		boja = 16766720; //zlatni smajli
	}
	else{
		boja=0; //crni smajli-brisanje
	}	
	//lice
	fp = fopen("/dev/vga_dma", "w");
	if(fp == NULL){	
		printf("Cannot open /dev/vga_dma for write\n");
		return -1;
   	}
	for(ugao=0; ugao< 2*3.14159265359 ; ugao+=korak){
        	fprintf(fp,"%d,%d,%#04x\n",(int)(320 + 30*cos(ugao)),(int)(300-30*sin(ugao)),boja);
        	fflush(fp);		
   	}
  	if(fclose(fp) == EOF){
     		 printf("Cannot close /dev/vga\n");
     		 return -1;
   	}
	 
	//oko 1-levo
	fp = fopen("/dev/vga_dma", "w");
	if(fp == NULL)
   	 {	
		printf("Cannot open /dev/vga_dma for write\n");
		return -1;
   	 }
	for(ugao=0; ugao< 2*3.14159265359 ; ugao+=korak){
        	fprintf(fp,"%d,%d,%#04x\n",(int)(305 + 3*cos(ugao)),(int)(285-3*sin(ugao)),boja);
        	fflush(fp);		
   	 }
  	if(fclose(fp) == EOF)
    	{
     		 printf("Cannot close /dev/vga\n");
     		 return -1;
   	 }
	 
	//oko 2-desno 
	fp = fopen("/dev/vga_dma", "w");
	if(fp == NULL)
   	 {	
		printf("Cannot open /dev/vga_dma for write\n");
		return -1;
   	 }
	for(ugao=0; ugao< 2*3.14159265359 ; ugao+=korak){
        	fprintf(fp,"%d,%d,%#04x\n",(int)(335 + 3*cos(ugao)),(int)(285 -3*sin(ugao)),boja);
        	fflush(fp);		
   	 }
  	if(fclose(fp) == EOF)
    	{
     		 printf("Cannot close /dev/vga\n");
     		 return -1;
   	 }
	
	
	
	fp = fopen("/dev/vga_dma", "w");
	if(fp == NULL){
			printf("Cnnot open\n");
			return -1;
	}
	if(vrsta_smajlija == 0){
		for(ugao=0.5235987756; ugao< 2.617993878 ; ugao+=korak){
        		fprintf(fp,"%d,%d,%#04x\n",(int)(320 + 15*cos(ugao)),(int)(320 -15*sin(ugao)),boja);
        		fflush(fp);		
		}
		if(fclose(fp) == EOF)
    	{
     			 printf("Cannot close /dev/vga\n");
     		 return -1;
		}
	}
	else if(vrsta_smajlija == 1){
		for(ugao=3.6651914292; ugao< 5.7595865316 ; ugao+=korak){
        		fprintf(fp,"%d,%d,%#04x\n",(int)(320 + 15*cos(ugao)),(int)(305 -15*sin(ugao)),boja);
        		fflush(fp);		
		}
		if(fclose(fp) == EOF)
    		{
     			 printf("Cannot close /dev/vga\n");
     			 return -1;
		}
	}
	
	//brisanje smeska za oba slucaja
	else{
		for(ugao=0.5235987756; ugao< 2.617993878 ; ugao+=korak){
        		fprintf(fp,"%d,%d,%#04x\n",(int)(320 + 15*cos(ugao)),(int)(320 -15*sin(ugao)),boja);
        		fflush(fp);		
		}
		for(ugao=3.6651914292; ugao< 5.7595865316 ; ugao+=korak){
        		fprintf(fp,"%d,%d,%#04x\n",(int)(320 + 15*cos(ugao)),(int)(305 -15*sin(ugao)),boja);
        		fflush(fp);		
		}
	}
	
}


int ocitaj_tastere(){
	/*static*/ FILE *fp;
	/*static*/ char tval1,tval2,tval3,tval4;
	/*static*/ size_t num_of_bytes = 6;
	char *str;
	fp = fopen ("/dev/button", "r");
		if(fp==NULL)
		{
			puts("Problem pri otvaranju /dev/button");
			return -1;
		}


	str = (char *)malloc(num_of_bytes+1); 
	getline(&str, &num_of_bytes, fp); 

	if(fclose(fp))
	{
		puts("Problem pri zatvaranju /dev/button");
		return -1;
	}


	tval1 = str[2] - 48;
	tval2 = str[3] - 48;
	tval3 = str[4] - 48;
	tval4 = str[5] - 48;
	free(str);
//	printf("Vrednosti tastera: %d %d %d %d \n",tval1,tval2,tval3,tval4);
	usleep(100000);
	if(tval1 == 1 ){
		return 4;
	}
	else if(tval2 == 1){
		return 3;
	}
	else if(tval3 == 1){
		return 2;
	}
	else if(tval4== 1 ){
		return 1;
	}
	else{
		return 0;
	}
}
