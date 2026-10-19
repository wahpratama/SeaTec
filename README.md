## SeaTection
 ![Build Status](https://img.shields.io/badge/build-CommingSoon-brightgreen)
Prototipe IoT untuk membantu mendeteksi potensi kebocoran air pada perahu nelayan.

## 1. Fungsi
- Membaca kondisi melalui sensor pada perangkat.
- Memproses data untuk mengenali indikasi kebocoran.
- Mendukung pemantauan kondisi se4cara realtme.

## 2. Cara Kerja
```mermaid
flowchart TD
    A([Mulai]) --> B[Sensor membaca kondisi air]
    B --> C[Perangkat memproses data sensor]
    C --> D{Indikasi kebocoran?}
    D -- Tidak --> E[Monitoring berlanjut]
    E --> B
    D -- Ya --> F[Kirim data melalui koneksi IoT]
    F --> G[Tampilkan informasi pada web]
    G --> H[Pengguna memeriksa kondisi perahu]
    H --> B
```

## 3. Struktur Program
- `Device/` — kode perangkat IoT dan pemrosesan sensor.
- `web/` — komponen antarmuka pemantauan.


