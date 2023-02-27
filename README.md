# Genetic-Algorithm-Project
Generating main text with genetic algorithm

Bu projede genetik algoritma kullanılarak bozuk bir metinden ana metin üretilmesi sağlanmıştır. Algoritdaki kavramların detaylı açıklaması aşağıdadır.

## Gen
Algoritmamızdaki genler harfleri temsil eder. Metinde yer alabilecek her türlü harf ve özel karakter gen havuzundadır.

## Kromozom
Genlerin yani harflerin meydana getirdiği yapıya kromozom ismini verdim. Kromozomlar yeni metin temsillerini tutmaktadır.

## Birey
Uygunluk fonksiyonu sonucu elde edilen kromozomlardan metinler yani bireyler oluşturulur. Oluşan her birey o nesile eklenerek uygun bireyler saptanmaya çalışılır.

## Nesil
Metinlerden yani bireylerden oluşur. Her nesilde örneklem uzayına bağlı olarak 100 - 500 - 1000 gibi miktarlarda metin yer alabilir. Popülasyonun artması programın hesaplama süresini arttırır fakat daha az birey üreterek ana metni bulmamızı sağlar.

## Çalışma Mantığı
Program çalıştığında aşağıdaki consol çıktılarında görüldüğü üzere ana metni bulana dek metinler üretir. Her neslin en uygun bireylerini ekrana bastırır. Uygunluk puanı 0 olduğunda ana metin bulunmuş olur.
Bozuk metin ana metnin her 3 harfte bir ekle - sil ve güncelle işlemleriyle gen havuzundan yeni harf alması veya silmesi ile üretilir.

## Programın çalıştığında ilk üretilen nesiller.
![image](https://user-images.githubusercontent.com/92461836/221431390-e92ffa6f-6256-4eac-9c28-5f011c7e41c0.png)

## Programın ana metni bulması.
![image](https://user-images.githubusercontent.com/92461836/221431368-8340c87e-61b8-48b5-a08a-532624dfe71e.png)

