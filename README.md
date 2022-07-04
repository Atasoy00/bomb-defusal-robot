Bomba İmha Robotu v1.0
======

Bu projede 5 DOF robot kol barındıran hareketli bir sistem tasarımı yapılmıştır.

<img src="https://user-images.githubusercontent.com/89063912/177127033-3d346b1d-12f5-4b1c-9e2b-b8bad0f60c66.jpeg" width="550">


## # Robot Kol

- Robot kol 5 DOF hareket eksenine sahiptir.
- Ana ve ara eklem servolarının hareketinde ters kinematik denklemler kullanılmıştır.
- Robot kolun gövde bağlantı bölümünde bir adet rulman kullanılarak sistem bu rulman üzerine oturtulmuştur
- Küçük güçte bir servo kullanılarak tüm sistem rahatça döndürülebilmektedir.
- Robot kol 200g'a kadar ağırlıktaki yükleri sorunsuz kaldırabilmektedir


<img src="https://user-images.githubusercontent.com/89063912/177130384-5452ee08-f2e2-47f9-9e1c-4e41c0ab941e.jpeg" width="550">


## # Palet

- Motorlardan palete 1:256 oranlı redüktör tasarlanmıştır.
- Yüksek güç üreten redüktör için 30 parça kaymaz palet tasarlanmıştır.
- 6x2 destek tekerleri ile palet sabitlenmiştir.
- Sistemin gücü 12V 9600 rpm çift motorla sağlanmaktadır.  

<img src="https://user-images.githubusercontent.com/89063912/177134009-4cbda47f-02f2-45ca-9cdd-4931722d4775.jpeg" width="550">



## # Kontrol Seçenekleri

### 1. TCP Bağlantısı ile Gamepad Kontrolü

- Robot başlatılmadan önce RC kumanda kapalı ise TCP ağına bağlanır.
- TCP/IP bağlantısı kullanılarak gönderilen mesaj kontrol edilmektedir.
- Statik IP adresi kullanılarak adres sabitlenmiştir.
- PC üzerinden kontrol için Python ile TCP kontrol uygulaması yazılmıştır.
- Bilgisayar klavyesinin yetersizliğinden dolayı gamepad driver'ı eklenmiştir.
- Gamepad üzerinden alınan kontroller bir mesaj haline getirilerek gönderilmektedir.

<img src="https://user-images.githubusercontent.com/89063912/177177401-07200d22-0c55-454d-8d8d-df2fb13b14cb.png" width="400">

### 2. RC Kumanda Kontrolü


- Robot başlatılmadan önce kumanda açık ise RC kumanda üzerinden kontrol alır.
- Kullanıcıya kontrol alternatifi sunularak RC alıcı entegre edilmiştir.
- RC Kumanda 2km'ye kadar kontrol mesafesini desteklemektedir.
- Kumandadan verilen kontroller daha hızlı ve doğrudur.
- Kumanda üzerinde yeterince kontrol kanalı olmadığı için switch ile sürüş ve robot kol modları arasında geçiş yapılabilmektedir.
- Ters kinematik özelliği kumanda üzerinden açılıp kapanabilmektedir. 

<img src="https://user-images.githubusercontent.com/89063912/177177572-d5b32afe-c6b1-478d-b2c3-277d69219681.png" width="400">


## # Elektronik Devre Şeması

<img src="https://user-images.githubusercontent.com/89063912/177176860-659068cf-37d0-4ae1-b577-2b7e67a4ee2e.png" width="600">


## # Üretim

Projede kullanılan tüm parçalar piyasada kolayca bulunabilen fiyat performans ürünleridir. Geri kalan parçalar açık kaynaklı şekilde proje dosyalarında .stl formatında sunulmuştur. 3B baskı yöntemleri ile parçalar elde edilebilir, hatta eklemeler yapılarak farklı görevlere yönelik tasarımlar oluşturulabilir. Gerekli parçaların üretimi ve temini sonrası kolayca bir araya getirilebilir ve kodu yüklenerek çalışır hale getirilebiliir. 

<img src="https://user-images.githubusercontent.com/89063912/177177762-647e45ce-49e5-4a17-a53c-07fcf72e5159.jpeg" width="550">





