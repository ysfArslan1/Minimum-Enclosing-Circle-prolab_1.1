#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include<ctype.h>
#define MAX_CPTS  500
struct konum{
	int x;
	int y;
};
typedef struct{
  double x, y;
  double r;
} birimler;

double mesafe_hesaplama(double x1, double y1, double x2, double y2){
  double mesafe;
  mesafe = sqrt(pow(x1-x2, 2) + pow(y1 -y2, 2));
  return mesafe;
}
birimler cember_bul(double x1, double y1, double x2, double y2, double x3, double y3) {
    double noktax12 = x1 - x2;
    double noktax13 = x1 - x3;
    double noktay12 = y1 - y2;
    double noktay13 = y1 - y3;
    double noktay31 = y3 - y1;
    double noktay21 = y2 - y1;
    double noktax31 = x3 - x1;
    double noktax21 = x2 - x1;
    birimler degisen_cember;
    double farkx13 = pow(x1, 2) - pow(x3, 2);    // x1^2 - x3^2
    double farky13 = pow(y1, 2) - pow(y3, 2);    // y1^2 - y3^2
    double farkx21 = pow(x2, 2) - pow(x1, 2);
    double farky21 = pow(y2, 2) - pow(y1, 2);
    double f = ((farkx13) * (noktax12)
             + (farky13) * (noktax12)
             + (farkx21) * (noktax13)
             + (farky21) * (noktax13))
            / (2 * ((noktay31) * (noktax12) - (noktay21) * (noktax13)));
    double g = ((farkx13) * (noktay12)
             + (farky13) * (noktay12)
             + (farkx21) * (noktay13)
             + (farky21) * (noktay13))
            / (2 * ((noktax31) * (noktay12) - (noktax21) * (noktay13)));
    double c = -pow(x1, 2) - pow(y1, 2) - 2 * g * x1 - 2 * f * y1;// cember denklemi x^2 + y^2 + 2*g*x + 2*f*y + c = 0// merkez (h = -g, k = -f) ve yaricap r//  r^2 = h^2 + k^2 - c
    double h = -g;
    double k = -f;
    double r_kare = h * h + k * k - c;// yaricap
    double r = sqrt(r_kare);
    degisen_cember.x = h;
    degisen_cember.y = k;
    degisen_cember.r = r;
    return degisen_cember;
}
birimler iki_nokta_verilen(double noktalar[][2], int n, int ilk_nokta_konum, int ikinci_nokta_konum){
  birimler cember;
  float kontrol_nokta;
  cember.x = (noktalar[ilk_nokta_konum][0] + noktalar[ikinci_nokta_konum][0]/2);
  cember.y = (noktalar[ilk_nokta_konum][1] + noktalar[ikinci_nokta_konum][1]/2);
  cember.r = (mesafe_hesaplama(noktalar[ilk_nokta_konum][0], noktalar[ilk_nokta_konum][1], noktalar[ikinci_nokta_konum][0], noktalar[ikinci_nokta_konum][1])/2);
  for(int i=0; i<n; i++){
    kontrol_nokta = pow(noktalar[i][0] - cember.x, 2) + pow(noktalar[i][1] - cember.y, 2) - pow(cember.r, 2);
    if(kontrol_nokta > 0) {
      cember = cember_bul(noktalar[ilk_nokta_konum][0], noktalar[ilk_nokta_konum][1], noktalar[ikinci_nokta_konum][0], noktalar[ikinci_nokta_konum][1], noktalar[i][0], noktalar[i][1]);
    }
  }
  return cember;
}
birimler tek_nokta_verilen(double noktalar[][2], int nokta_konum, int n){
  birimler cember;
  int j;
  double kontrol_nokta;
  cember.x = (noktalar[nokta_konum][0]+noktalar[0][0])/2;
  cember.y = (noktalar[nokta_konum][1]+noktalar[0][1])/2;
  cember.r = (mesafe_hesaplama(noktalar[nokta_konum][0], noktalar[nokta_konum][1], noktalar[0][0], noktalar[0][1])/2);
  for(j=1; j<nokta_konum; j++){
    kontrol_nokta = pow(noktalar[j][0] - cember.x, 2) + pow(noktalar[j][1] - cember.y, 2) - pow(cember.r, 2);
    if(kontrol_nokta > 0){
      cember = iki_nokta_verilen(noktalar, j, j, nokta_konum);
    }
  }
  return cember;
}
birimler rastgele_artimli_yontem(double noktalar[][2], int n){
  birimler cember;
  double kontrol_nokta;
  cember.x = (noktalar[1][0]+noktalar[0][0])/2;
  cember.y = (noktalar[1][1]+noktalar[0][1])/2;
  cember.r = (mesafe_hesaplama(noktalar[0][0], noktalar[0][1], noktalar[1][0], noktalar[1][1])/2);
  for(int i=2; i<n; i++){
    kontrol_nokta = pow(noktalar[i][0] - cember.x, 2) + pow(noktalar[i][1] - cember.y, 2) - pow(cember.r, 2);
    if(kontrol_nokta > 0){
      cember = tek_nokta_verilen(noktalar, i, n);
    }
  }
  return cember;
}
void klavye(unsigned char key, int x, int y);
void matrix_hesaplama(float m[4][4]);
void vektor_carpim(float m[4][4], float v[4][3], float r[4][3]);
GLfloat control_noktalari[MAX_CPTS][3];
int yeni_control_noktasi = 0;
static int width = 600, height = 600;
void vektor_carpim(float m[4][4], float v[4][3], float r[4][3])     //4x4 matrisle 4 noktalari vektorle carpimi
{
    int i, j, k;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 3; j++)
            for (k = 0, r[i][j] = 0.0; k < 4; k++)
                r[i][j] += m[i][k] * v[k][j];
}
static float ara_deger[4][4] =
{
    { 1.0, 0.0, 0.0, 0.0 },
    { -5.0/6.0, 3.0, -3.0/2.0, 1.0/3.0 },
    { 1.0/3.0, -3.0/2.0, 3.0, -5.0/6.0 },
    { 0.0, 0.0, 0.0, 1.0 },
};
void matrix_hesaplama(float m[4][4])            //matris kullanarak control noktalarini hesaplama
{
    int i, j;
            for (i = 0; i < 4; i++)
                for (j = 0; j < 4; j++)
                    m[i][j] = ara_deger[i][j];
}
void metinyaz(float x, float y, char *string) {
  glRasterPos2f(x, y);
glColor3f(122,0,0);
  for (char* c = string; *c != '\0'; c++) {
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, *c);  // konumun yenilenmesi
  }
  glEnd();
  glFlush();
}

static void egri_ciz()         //kontrol noktalarini kullanarak  belirtilen egrilerin cizimi yapilir
{
    int i;
    int basamak=3;
    GLfloat yeni_control_noktalari[4][3];
    float m[4][4];             //basamak ve matrix kullanarak control noktalarini hesaplama
    matrix_hesaplama( m);
   //egrilerin cizimi
    i = 0;
    while (i + 3 < yeni_control_noktasi)
    {
        vektor_carpim(m, &control_noktalari[i], yeni_control_noktalari);
        glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &yeni_control_noktalari[0][0]);
        glMapGrid1f(30, 0.0, 1.0);
        glEvalMesh1(GL_LINE, 0, 30);
        i += basamak;
    }
    glFlush();
}
static void goster(void)
{
    int i;
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(5.0);
    glBegin(GL_POINTS);
    for (i = 0; i < yeni_control_noktasi; i++)     // noktaların cizimi yapilir
        glVertex3fv(control_noktalari[i]);
     glEnd();
     glFlush();
     double noktalar[50][2];
     birimler cember;
     for(i=0;i<yeni_control_noktasi;i++){
        noktalar[i][0]=control_noktalari[i][0];
        noktalar[i][1]=control_noktalari[i][1];
     }
    cember = rastgele_artimli_yontem(noktalar, yeni_control_noktasi);
    printf("\n Merkez -> (%.2lf, %.2lf), Yaricap -> %.2lf\n", cember.x*10, cember.y*10, cember.r*10);
    printf("B-spline icin her hangi bir tusa basin...\n");
    float cx=cember.x,cy=cember.y,r=cember.r;
    int num_bolumleri=100;
    glBegin(GL_LINE_LOOP);
    for (int ii = 0; ii < num_bolumleri; ii++)   {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_bolumleri);   //cember degerleri
        float x = r * cosf(theta);       //x elemanini hesaplar
        float y = r * sinf(theta);       //y elemanini hesaplar
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
float k=-1;
glColor3ub(122,0,0);
glLineWidth(1);      // analitik duzlemin x ve y cizgilerini cizer
glBegin(GL_LINES);
glVertex2f(0.0,1.0);
glVertex2f(0.0,-1.0);
glVertex2f(1.0,0.0);
glVertex2f(-1.0,0.0);
for(;k<=1.0;k=k+0.1){
glVertex2f(k,0.01);      //analitik duzlemdeki x ve y uzerindeki sayi konularini gosteren cizgileri cizer
glVertex2f(k,-0.01);
glVertex2f(0.01,k);
glVertex2f(-0.01,k);
}
glEnd();
    glColor3f(0.0, 1.0, 0.0);
    glPointSize(5.0);
    glBegin(GL_POINTS);
    glVertex3f(cember.x, cember.y, 1.0);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(0.0, 1.0, 0.0);
    glVertex2f(cember.x,cember.y);
    glVertex2f(cember.x+cember.r,cember.y);
    glEnd();
    glFlush();
char koordinat_yaz[25][5]= {{"-10"},{"-9"},{"-8"},{"-7"},{"-6"},{"-5"},{"-4"},{"-3"},{"-2"},{"-1"},{"0"},{"1"},{"2"},{"3"},{"4"},{"5"},{"6"},{"7"},{"8"},{"-9"},{"10"}};
char koordinat_yaz1[25][5]= {{"-10"},{"-9"},{"-8"},{"-7"},{"-6"},{"-5"},{"-4"},{"-3"},{"-2"},{"-1"},{" "},{"1"},{"2"},{"3"},{"4"},{"5"},{"6"},{"7"},{"8"},{"-9"},{"10"}};

    int o=0;
        for(float l=-1.012; l<=1; l=l+0.1) {     //analitik duzlemdeki sayilari ciziyor
            metinyaz(l,-0.030,koordinat_yaz[o]);
            o++;
        }
        int t=0;
         for(float l=-1.015; l<=1; l=l+0.1) {
            metinyaz(-0.030,l,koordinat_yaz1[t]);
            t++;
        }
}
int nokta_gir(){

    FILE *dosya;
	dosya=fopen("C:\\Users\\Arslan\\Desktop\\codlamalar\\odevler\\proje\\proje.txt","r");

    float wx, wy;
    int kontrol=1;
    int noktax,noktay;
	struct konum nokta[100];
	int i=1,j=0,a=0,b,temp,key=0,x1=0,y1=0;
	char krkt[300],sayi,dizi[30];
	fgets(krkt,300,dosya);

	a=strlen(krkt);
	printf("Notalar= %s\n",krkt);

	while(key!=-1){                             //Alinan stringin icindeki sayilardan farkli karakterleri siler.
		for(i=0;i<a;i++){
			sayi=krkt[i];
			if(isdigit(sayi)){}
			else if(krkt[i]=='-'){}
			else{
                krkt[i]=' ';
			}
		}
		if(i==a){
			key=-1;
		}
	}
    b=0;                                     //   b  sayilarin x'emi y'emi yazilmasi anlamak icin kullanilir
	for(i=0;i<a;i++){                               //  sayilari karakter dizisinden alip structta atar
		if(krkt[i]!=' '){
			j=0;
			while(krkt[i]!=' '){
				dizi[j]=krkt[i];            //  for dongusunde anlik sayilari turarak structa atilmasini saglar
				i++;
				j++;
			}
			dizi[j]='\0';
			temp=atoi(dizi);
			if(b%2==0){
			nokta[x1].x=temp;
			x1++;
			}else{
			nokta[y1].y=temp;
			y1++;
			}
			b++;
        }
	}

    for(i=0;i<(b/2)-1;i++){
        for(j=0;j<(b/2)-1-i;j++){
            if(nokta[j].x>nokta[j+1].x){     //  diziyi yeniden siralandirir  x leri ve y leri kucukten buyuge dogru
                temp=nokta[j].x;
                nokta[j].x=nokta[j+1].x;
                nokta[j+1].x=temp;
                temp=nokta[j].y;
                nokta[j].y=nokta[j+1].y;
                nokta[j+1].y=temp;
            }
             else if(nokta[j].x==nokta[j+1].x && nokta[j].y>nokta[j+1].y){
                temp=nokta[j].x;
                nokta[j].x=nokta[j+1].x;
                nokta[j+1].x=temp;
                temp=nokta[j].y;
                nokta[j].y=nokta[j+1].y;
                nokta[j+1].y=temp;
                }

            if(nokta[j].x==nokta[j+1].x && nokta[j].y==nokta[j+1].y){    //  noktalarin eşit olup olmadigini kontrol ediyor
                kontrol=0;
                }
        }
    }

    i=0;
    while(i<(b/2)){
    noktax=(nokta[i].x*30)+300;                         //noktalari degerlerine gore kordinat sistemine tekrardan degerlendirir
    wx = (2 * noktax) / (float)(width - 1) - 1.0;      //  30 ikisayi birimi arasindaki piksel farki     merkez=390-390
    noktay=300-(nokta[i].y*30);
    wy = (2 * (height - 1 -noktay)) / (float)(height - 1) - 1.0;

    control_noktalari[yeni_control_noktasi][0] = wx;        //noktalar kayit edilir
    control_noktalari[yeni_control_noktasi][1] = wy;
    control_noktalari[yeni_control_noktasi][2] = 0.0;
    yeni_control_noktasi++;



    glColor3f(0.0, 0.0, 0.0);        // nokta cizimi     // renk atamasi
    glPointSize(5.0);                // nokta boyutu
    glBegin(GL_POINTS);
    glVertex3f(wx, wy, 0.0);         // konumlarin verilmesi
    glEnd();
    glFlush();
    i++;

    }
    int yeni_dizi[4][2],p;
    p=(b/2);

    for(i=0; i<4; i++)                          //  bspline cizen fonksiyon cizim yaparken 4 sayi aliyor
    {                                           //  cizimde karisiklik olmamasi icin velilen noktalarin son 4 sayisi tekrardan gonderir
        yeni_dizi[i][0]=nokta[p-i-1].x;
        yeni_dizi[i][1]=nokta[p-i-1].y;
    }
    for(int i=0; i<2; i++)
    {
        noktax=(yeni_dizi[i][0]*30)+300;
        wx = (2.0 * noktax) / (float)(width - 1) - 1.0;
        noktay=300-(yeni_dizi[i][1]*30);
        wy = (2.0 * (height - 1 -noktay)) / (float)(height - 1) - 1.0;

        control_noktalari[yeni_control_noktasi][0] = wx;
        control_noktalari[yeni_control_noktasi][1] = wy;
        control_noktalari[yeni_control_noktasi][2] = 0.0;
        yeni_control_noktasi++;
    }
    if(b%2==1){    //noktalarin dogru bir şekilde girilip girilmedigini kontrol eder
        return 0;
    }
    if(kontrol==0){
         return 0;
    }
return 1;
}

void klavye(unsigned char key, int x, int y)   // cizim yapilirken bspline cizmesi icin klavyeden onay bekler
{egri_ciz();}

main(int argc, char **argv)
{
    int key=1;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(width, height);
    glutCreateWindow("Minimum Encolising Circle and B-spline ");
    key =nokta_gir();
    if(key==0){
        printf("Noktalari yanlis girdiniz.\n\n\n");

    }else{
        glutDisplayFunc(goster);
    glutKeyboardFunc(klavye);
    }

	glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_MAP1_VERTEX_3);
    glutMainLoop();
}
