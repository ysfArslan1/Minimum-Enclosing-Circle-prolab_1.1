# Prolab1 1.Proje

# Minumum Çevreleyen Çember 

# Özet

Klasör içerisinde .txt uzantılı dosyada bulunan noktaların alınıp bu noktaları kapsayan en küçük çemberi ve bu noktaların üzerinden geçen B-Spline eğrisini çizdirmemiz istenmektedir.Projenin ilk kısmında dosya kontrol işlemiyle noktalar alınır .Bundan sonra bu noktalar gerekli olan hesaplamaları yapmak için fonksiyonlara gönderilir.Hesaplamaları yaptıktan sonra Glut kütüphanesi yardımıyla ekrana koordinat sistemi,noktalar,bu noktaları kapsayacak olan yarıçapı çizilmiş en küçük çember ve en son B-spline eğrisi çizdirilir.

## Anahtar kelimeler-
Nokta,dosya,B-spline,çember,koordinat sistemi

# 1-GİRİŞ

Proje klasörünün içinde bulunan proje.txt dosyasından okunarak bellekte tutulur.Bundan sonra noktalar belli hesaplamalar doğrultusunda uzun matametiksel işlemler yaptırtılır.Bu işlemler bittikten sonra yaptığımız işlemlerin görsel tarafına geçilir.Görsel tarafında önce noktaların koordinatlarını göstereceğimiz bir koordinat sistemi,sonra noktalar ve minimum çevreleyen çember çizilir.Kullanıcı istediği durumda klavyeden herhangi bir tuşa basarak B-spline eğrisini çizdirebilir.Çizdirdiği çemberin üzerinde bir merkez ve yarıçap belirgin halde görülmektedir. Projenin yazımında “C” dili tercih edilmiştir.


# 2- TEMEL BİLGİLER

Bu proje C programlama dilinde geliştirilmiş olup, geliştirme ortamı olarak ise “Code Blocks ver.17.12” kullanılmıştır. İlk olarak projenin bir yol haritasını
çıkarmış olamakla birlikte çalışmalarımıza ön hazırlık yaptık.Projenin isterleri,isterlere yönelik araştırmalar,grup içerisinde gerekli olan iş bölümü yapılmış olup gerekli olan tüm bilgilerin ışığında proje ana hatları ile belirginleşmiş oldu.Bize geriye kalan çıkabilecek hataların saptanıp çözümleri yapıldıktan sonra
derleyici ortamımızda ilk adımları atmış bulunduk.Proje yaklaşık 2 hafta gibi kısa bir süre de ana hatlarıyla birlikte bitmiş oldu.

# 3- YÖNTEM

Main fonksiyonumuzun yardımıyla klasörün içinde bulunan .txt dosyasına ulaşımı sağladık.Bundan sonra alınan noktalar fonksiyonlara gönderildi ve tüm hesaplamalar yaptırtıldı. GL/glut.h
kütüphanemizi kullanarak ekrana çizdirme işlemini başarıyla yaptık.Böylece bizden
istenen isterleri net bir şekilde göstermiş olduk.Aynı zamanda klavyeden herhangi bir tuşa bastırarak b-spline çizgilerini çizdirip kullanıcıdan da aktif bir rol oynamasını istedik.

## Projede kullanılan fonksiyonlar ve zaman karmaşıklığı:
## Çember için kullanılan fonksiyonlar:
### mesafe_hesaplama():
Noktalar arasındaki mesafeleri hesaplayarak çember fonksiyonlarının içine gönderir.Fonksiyonun içinde döngüleryada farklı fonksiyonlar olmadığı için zaman karmaşıklığı O(1).
### cember_bul():
Yapılan hesaplamalara göre olabilmesi muhtemel çemberler arasında arama yapar. .Fonksiyonun içinde döngüler yada farklı fonksiyonlar olmadığı için zaman karmaşıklığı O(1).
### iki_nokta_verilen():
İki nokta arasında matematiksel işlem yapar ve bu işlemlerin sonucunu çember_bul() fonksiyonuna göderir.Fonksiyonun içinde for döngüsü bulunduğu için zaman karmaşıklığı O(n).
### tek_nokta_verilen():
Rastgele artımlı yöntem fonksiyonda hesaplanan değerleri kullanarak belli değerleri hesaplar ve tutar, bu noktalar üzerinde belli işlemleri yapar ardından bu noktaları iki_nokta_verilen() fonksiyonuna gönderir.Fonksiyonun içinde for döngüsü bulunmaktadır.Döngünün içinde iki_nokta_verilen fonksiyonu çağrıldığı için zaman karmaşıklığı O(n^2)
### rastgele_artimli_yontem():
Verilen noktaları tutar,bu noktalar üzerinde belli işlemleri yapar ardından bu noktaları tek_nota_verilen() fonksiyonuna gönderir.Döngünün içinde tek_nokta_verilen fonksiyonu çağrıldığı için (zaman karmaşıklığı O(n^3))
## B-spline için kullanılan fonksiyonlar:
### vektor_carpim():
Verilen nokta değerlerini hesaplayıp bu noktalar arasında vektörel bir çarpım hesaplatır. Fonksiyonun içinde döngüler yada farklı fonksiyonlar olmadığı için zaman karmaşıklığı O(1).
### matrix_hesaplama():
Ara değer olarak tuttuğumuz 4*4 lük değerlerimizi kullanarak noktaları matrix olarak hesaplar. Fonksiyonun içinde döngüler yada farklı fonksiyonlar olmadığı için zaman karmaşıklığı O(1).

## Ortak kullanılan fonksiyonlar:

### metinyaz():
Koordinat da noktaların yerini belirlememize yarıyacak sayıları yazmamızı saylayan fonksiyon. Fonksiyonun içinde for döngüsü bulunduğu için zaman
karmaşıklığı O(n).
### egri_ciz():
B-spline’ı glut fonksiyonları ile ekrana çizdirir. Fonksiyonun içinde for döngüsü bulunduğu için zaman karmaşıklığı O(n).
### goster():
Çemberi,koordinat düzlemini ve üzerindeki bütün bilgileri glut fonksiyonları ile ekrana yazdırır. Döngünün içinde rastgele_artimli_artan fonksiyonu
çağrıldığı için zaman karmaşıklığı O(n^3)
### nokta_gir():
Girilen noktaları alır sıralar ve gereken fonksiyonlara gönderir.Fonksiyon içinde iç içe 2 tane for döngüsü olduğu için zaman karmaşıklığı O(n^2).
### klavye():
Sadece klavyeyi çalıştırarak Bspline’ı çizdirmeyi sağlar. Döngünün
içinde egri_ciz fonksiyonu çağrıldığı için zaman karmaşıklığı O(n).
## Zaman karmaşıklığı
Kodun zaman karmaşıklığını O(n^3) bulduk.Her fonksiyonun kendi zaman karmaşıklığını ayrı olarak hesaplayıp yukarıda gösterdik.

# 4- SÖZDE(PSEUDO) KOD

Verilen proje için yazdığımız kodun Pseudo kodları şu şekildedir:

1- Program çalıştı.

2- Program,içerisinde yer aldığı dosya yolunda bulunan txt verileri okudu ve string'e attı.

3- Alınan string'i tekrardan biçimlendirip int degerlerinin bulundugu basla bir structa attı.

4- Structta bulunan noktaları tekrardan işlemlerden geçirerel x ve y konumlarına göre tekrardan sıralandırdı.

5- Noktaların grafik ekranına yerleştirilmesi için gerekli matematiksel hesaplamalar yapıldı.

6- Noktaların doğru girilip girilmediği kontrol edilir

7- Noktaların cizimi yapılır.

8- Verilen noktalarla yapılan işlemler sonucu cember cizilir.

9- Analitik düzlem cizimi yapılır.

10- Çemberin merkezi ve yarıcapı cizdirilir.

11- Bir tuşa basıldıktan sonra b spline cizimi başlar.

12- Gerekli matematiksel işlemler sonrası egri cizimleri yapılır.

13.Program sonlanır.

# 5- KULLANILAN KÜTÜPHANELER VE EKLER

#include <stdio.h> 

#include <stdlib.h>

#include <math.h>:Matematiksel işlemler için kullanıldı

#include <string.h>:Dizi işlemleri için kullanıldı.

#include<ctype.h>:isdigit fonksiyonunu çağırmak için kullanılmıştır.

#include <GL/glut.h>:Aldığımız ve hesapladığımız değerleri görselleştirmek için kullanıldı.


# 6- KAYNAKÇA:

http://bilgisayarkavramlari.sadievrenseker.com/

https://www.youtube.com/watch?v=hqO Nlh0YTeA&list=PL34fQ24a1TlHkImnzkfdZ9 ckqZBnPN2nx&index=26

https://en.wikipedia.org/wiki/De_Boor%2 7s_algorithm

https://www.geeksforgeeks.org/minimum-enclosing-circle-set-1/ 

https://github.com

# Deneysel Sonuçlar:

![image](https://user-images.githubusercontent.com/58952369/180423578-35d3ac28-01eb-4245-aef5-b8d59d3fca13.png)

![image](https://user-images.githubusercontent.com/58952369/180423676-744a154d-de79-472b-b3a1-47aa4f61a9e4.png)

![image](https://user-images.githubusercontent.com/58952369/180423713-9d953f7f-af68-42af-8a89-eb55cdc5d121.png)

![image](https://user-images.githubusercontent.com/58952369/180423858-320e5970-0e2e-4284-aed3-147479e9a846.png)






