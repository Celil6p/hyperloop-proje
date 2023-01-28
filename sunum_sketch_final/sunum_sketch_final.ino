const int BirinciIRSensorPin = 3; // IR sensorun bagli oldugu PIN
const int IkinciIRSensorPin = 2; // IR sensorun bagli oldugu PIN
const int BirinciRenkSensorPin = 4; // IR sensorun bagli oldugu PIN
const int IkinciRenkSensorPin = 5; // IR sensorun bagli oldugu PIN
const float reflektorlerArasiMesafe = 4.0; // metre cinsinden reflektor arasi mesafe
int reflektorSayi = 0; //reflektor sayisi
float gidilenMesafe = 0.0; //gidilen mesafe
float kmHizToplam = 0.0; // Alinan hizlarin toplami
float ortalamaKmHiz = 0.0; // Ortalama hiz
unsigned long ilkReflektorZaman = 0; //Ilk reflektorun gorulme zamani
float kmHiz = 0.0; //Anlik hiz
float enYuksekHiz = 0.0; //En yuksek hiz
void besCmTetik(); //bu fonksiyon 5cmlik reflektor aralıklarinda tetiklenir
void mesafeHesap(); //bu fonksiyon reflektor sayisina gore mesafeyi hesaplar

void setup() {
  Serial.begin(9600);
}

void loop() {

  //ilk reflektoru gordugu anki sureyi al
  if(reflektorSayi == 1){
    ilkReflektorZaman = millis();
    }
  // Sensörlerden en az 1 tanesi reflektoru goruyor
  while (digitalRead(BirinciIRSensorPin) == LOW || digitalRead(IkinciIRSensorPin) == LOW) {} //reflektor goruldugu sure boyunca dongude kalir

  // reflektoru gormeyi biraktigi zamani kaydet
  unsigned long baslangicZaman = millis();

    
  // her iki IR sensör artik reflektoru gormuyor
  while (digitalRead(BirinciIRSensorPin) == HIGH && digitalRead(IkinciIRSensorPin) == HIGH) {}

  // reflektorun artık tesbit edilmediği zamani kaydet
  unsigned long bitisZaman = millis();

  // 5cm aralikli reflektor tesbiti
  // Renk sensörlerinin en az birinin sinyal vermesi halinde fonksiyon tetiklenir
  if(digitalRead(BirinciRenkSensorPin) == HIGH || digitalRead(IkinciRenkSensorPin) == HIGH ){
  besCmTetik();
  }
  
  // gorulen reflektor sayisina gore mesafeyi hesapla
  mesafeHesap();

  // gecen zamani hesapla
  unsigned long gecenZaman = bitisZaman - baslangicZaman; // Anlik hiz icin
  unsigned long ilkRefGecenZaman = millis() - ilkReflektorZaman; // Ortalama hiz icin 
  
  // gecen zamani saniyeye cevir
  float saniyeGecenZaman = (float) gecenZaman / 1000.0; // Anlik hiz icin
  float saniyeIlkRefGecZaman = (float) ilkRefGecenZaman / 1000.0; // Ortalama hiz icin

  // hizi metre/saniye cinsinden hesapla
  float hiz = reflektorlerArasiMesafe / saniyeGecenZaman; // Anlik hiz icin
  float ortalama = gidilenMesafe / saniyeIlkRefGecZaman; // Ortalama hiz icin

  // hizi kilometre/saat cinsine cevir
  kmHiz = hiz * 3.6; // Anlik hiz icin
  ortalamaKmHiz = ortalama * 3.6; // Ortalama hiz icin

    // en yüksek hizi hesapla
  void enYuksekHizHesap();

  //anlik hizi yazdir
  Serial.println("\n"+(String)kmHiz+" km/saat");
  
  //oratalama hizi yazdir
  Serial.println("Ortalama hiz:"+(String)ortalamaKmHiz+" km/saat");

  //reflektor sayisi yazdir
  Serial.println((String)reflektorSayi+".Reflektor");

  //gecen zamana gore lokasyon
  Serial.println((String)gidilenMesafe+".Metre");
  
  //en yuksek hizi yazdir
  Serial.println("En yuksek hiz: "+(String)enYuksekHiz+" km/saat");

  Serial.println(ortalama);
  Serial.println(saniyeIlkRefGecZaman);

  //

  // döngü tekrar baslamadan onceki bekleme suresi
  delay(500);
}

void besCmTetik(){

  // 19.reflektordeki 5cmlik dalga
  
  if(reflektorSayi > 19 && reflektorSayi <= 38 && kmHiz > 200.00){
      reflektorSayi = 38;
  }
  //51.reflektordeki 5cmlik dalga
  else if( reflektorSayi > 39  && reflektorSayi <= 60 && kmHiz > 200.00){ 
      reflektorSayi = 60;
  }
  // reflektor sayisini artir
  else{
    reflektorSayi++;
  }
}

void mesafeHesap(){
  if(reflektorSayi <= 19){
    
    gidilenMesafe = reflektorlerArasiMesafe * (reflektorSayi-1) + 6.0;// ilk reflektor 6.metrede oldugu icin
  
  }else if(reflektorSayi <= 51){

    gidilenMesafe = reflektorlerArasiMesafe * (reflektorSayi-20) + 6.0; // 20 reflektor 2 metrelik mesafede dizildigi icin
    
  }else{
      
    gidilenMesafe = reflektorlerArasiMesafe * (reflektorSayi-29) + 6.0; // 50-60 arası 10 reflektor 1 metrelik mesafede dizildigi icin
  }
}

void enYuksekHizHesap(){
  if(kmHiz < 200.00 && kmHiz > enYuksekHiz){
    enYuksekHiz = kmHiz;
    }
  }
