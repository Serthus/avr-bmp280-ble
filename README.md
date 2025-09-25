# AVR BMP280 + BLE Project

Projekt embedded realizowany na mikrokontrolerze AVR (np. ATmega328P), którego celem jest:
- odczyt temperatury i ciśnienia atmosferycznego z czujnika **BMP280** (I2C),
- przesyłanie wyników przez interfejs **UART** do modułu Bluetooth Low Energy (BLE),
- odbiór danych na smartfonie / komputerze.

## Funkcjonalności
- Komunikacja z czujnikiem BMP280 przez magistralę **I2C (TWI)**.
- Odczyt i obliczanie wartości **temperatury [°C]** oraz **ciśnienia [hPa]**.
- Wysyłanie danych w formie tekstowej przez **UART → BLE**.
- Możliwość odbioru pomiarów w terminalu Bluetooth na telefonie.

## Wymagania sprzętowe
- Mikrokontroler AVR (np. ATmega328P @ 16 MHz).
- Czujnik **BMP280** (I2C).
- Moduł Bluetooth 4.0 BLE – HM-10 / AT-09 – MLT-BT05 (3,3V/5V) [inne kompatybilne moduły: HC-05, HC-06, BLE UART]
- Zasilanie 5V / 3.3V.

## Wymagania programowe
- Atmel Studio / avr-gcc + avrdude.
- Narzędzia do obsługi Git.
- Terminal Bluetooth na telefonie (np. *nRF Connect*).

## Jak działa program?
1. Inicjalizacja UART, I2C i czujnika BMP280.
2. Reset i konfiguracja BMP280.
3. Pobranie danych kalibracyjnych z pamięci czujnika.
4. W pętli głównej:
   - Odczyt surowych wartości temperatury i ciśnienia.
   - Obliczenie wartości w jednostkach fizycznych.
   - Wysłanie ich w formacie tekstowym przez UART (BLE).
   - Przykładowy log na terminalu:
     
```
Temperatura: 21.02 C 
Cisnienie: 1028.50 hPa
```

5. Powtarzanie pomiaru co 5 sekund.

## Struktura repozytorium
```
.
├── main.c # główny kod programu
├── bmp280.c/.h # obsługa BMP280
├── twi.c/.h # obsługa I2C (TWI)
├── uart.c/.h # obsługa UART
├── config.h # konfiguracja
└── README.md # dokumentacja
```

## Możliwe ulepszenia
- Dodanie obsługi wyświetlacza LCD / OLED.
- Wysyłanie danych w formacie JSON.
- Logowanie wyników na kartę SD.
- Implementacja przerwań dla dokładniejszej obsługi czujnika.

## Autor
Projekt stworzony w celach edukacyjnych – **[Serthus](https://github.com/Serthus)**.
