# 🚀 Joc Nave – Proiect POO

Acesta este un joc realizat in POO in care doua echipe de nave se lupta intre ele. Fiecare echipa are nave cu forme si comportamente diferite, iar proiectilele se deplaseaza automat spre zona inamica. Jocul afiseaza la final cine castiga in functie de navele ramase.

---

## 🎮 Descrierea jocului

Exista **doua echipe**:
- echipa din stanga
- echipa din dreapta

Fiecare echipa are propriile nave si propria zona de joc. Lupta este frontala, iar proiectilele celor doua parti se ciocnesc pe mijloc.

### Tipuri de nave

### 🔴 Nava Mama
- Trage proiectile verticale.
- Are mai multa viata si poate sa-si regenereze o viata cand ajunge la 2.
- Este cea mai rezistenta nava din echipa.

### 🔵 Nava Cerc
- Sta in colt (dreapta/stanga).
- Proiectilele merg spre dreapta/stanga.
- Trage automat.

### 🟢 Nava Triunghi
- Pozitionata in lateral, pe stanga sau dreapta.
- Tot cu proiectile automate.
- Este o nava usoara de atac constant.

---

## 💥 Proiectile si coliziuni

Am facut un sistem simplu de coliziuni:
- proiectilul loveste nava → scade viata
- cand o nava ramane fara viata → este eliminata
- proiectilele au directii diferite in functie de tipul navei

Pentru proiectile am folosit **template-uri**, ca sa pot genera rapid proiectile de tipuri diferite.


