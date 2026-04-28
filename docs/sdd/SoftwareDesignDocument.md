# SDD — Software Design Document
# Velaryon V3

| Champ          | Valeur                  |
|----------------|-------------------------|
| Document ID    | VEL-SDD-001             |
| Version        | 1.0                     |
| Statut         | Draft / Released        |
| Référence SRS  | VEL-SRS-001             |

---

## 1. Vue d'ensemble de l'architecture

### 1.1 Pattern architectural

Le logiciel adopte le pattern **MVVM** (Model-View-ViewModel)
avec injection de dépendances par IoC container type-safe.

\image html architecture_overview.svg "Vue d'ensemble MVVM" width=900px

### 1.2 Décomposition en threads

| Thread         | Rôle                          | Priorité  |
|----------------|-------------------------------|-----------|
| Main / UI      | Rendu Qt, événements IHM      | Normale   |
| UdpWorker      | Réception et décodage UDP     | Haute     |
| BdfWriter      | Écriture fichier .bdf         | Haute     |

---

## 2. Low-Level Requirements

### 2.1 Sous-système UDP

\requirement LLR-UDP-001
Le `UdpWorker` SHALL s'exécuter sur un `QThread` dédié
séparé du thread principal Qt.
\satisfies HLR-ACQ-001

\requirement LLR-UDP-002
Le `UdpWorker` SHALL utiliser `QUdpSocket` en mode
bloquant avec timeout de 100 ms.
\satisfies HLR-ACQ-001
\satisfies HLR-SAFE-002

\requirement LLR-UDP-003
Le décodage des trames SHALL vérifier le header
`0xFF 0xFF 0xFF 0xFF` avant tout traitement du payload.
\satisfies HLR-ACQ-002
\satisfies HLR-IF-002

\requirement LLR-UDP-004
Chaque trame décodée SHALL être horodatée via
`std::chrono::steady_clock` immédiatement après réception.
\satisfies HLR-ACQ-003

### 2.2 Ring Buffer

\requirement LLR-BUF-001
Le ring buffer SHALL être de type SPSC (Single Producer
Single Consumer) sans verrou (lock-free).
\satisfies HLR-PERF-001
\satisfies HLR-LOG-001

\requirement LLR-BUF-002
Les index de lecture et d'écriture SHALL être de type
`std::atomic<uint32_t>` avec ordering
`memory_order_release` (écriture) et
`memory_order_acquire` (lecture).
\satisfies HLR-LOG-001

\requirement LLR-BUF-003
La capacité du ring buffer SHALL être d'au moins
`RING_BUFFER_SIZE = 2048` éléments, dimensionnée pour
absorber 4 secondes de données à 500 Hz.
\satisfies HLR-LOG-001
\satisfies HLR-PERF-001

\requirement LLR-BUF-004
En cas de saturation (buffer plein), la politique SHALL
être **drop-oldest** et un compteur d'overflow SHALL
être incrémenté de manière atomique.
\satisfies HLR-REL-001

### 2.3 BdfWriter

\requirement LLR-WRT-001
Le `BdfWriter` SHALL consommer le ring buffer sur son
propre thread avec une boucle de polling à 1 kHz.
\satisfies HLR-LOG-001
\satisfies HLR-LOG-002

\requirement LLR-WRT-002
Le `BdfWriter` SHALL utiliser un buffer d'écriture
intermédiaire de 64 Ko avant flush vers le fichier.
\satisfies HLR-PERF-001

\requirement LLR-WRT-003
Le nom du fichier .bdf SHALL suivre le format :
`velaryon_YYYYMMDD_HHMMSS.bdf`
\satisfies HLR-LOG-003

### 2.4 Décimation UI

\requirement LLR-DEC-001
Un décimateur SHALL transmettre au ViewModel une trame
sur N où `N = floor(f_udp / 60)`, préservant le logging
de toutes les trames.
\satisfies HLR-UI-003
\satisfies HLR-LOG-001

### 2.5 Arrêt d'urgence

\requirement LLR-EMG-001
La commande ABORT SHALL être traitée en priorité absolue,
court-circuitant toute séquence en cours.
\satisfies HLR-SAFE-001

\requirement LLR-EMG-002
L'état ABORT SHALL envoyer une trame de commande dédiée
au contrôleur embarqué puis fermer toutes les vannes
dans un ordre prédéfini.
\satisfies HLR-SAFE-001

---

## 3. Décisions de conception

> C'est ici que va l'équivalent de tes ADR en DO-178C.

### 3.1 Choix du ring buffer SPSC lock-free

**Problème :** Le thread UDP produit des données à 500 Hz.
Un mutex introduirait une contention inacceptable.

**Décision :** Ring buffer SPSC implémenté manuellement
avec atomics C++11.

**Alternatives rejetées :**

| Alternative         | Raison du rejet                          |
|---------------------|------------------------------------------|
| `QQueue` + `QMutex` | Contention mutex, latence non bornée     |
| `boost::lockfree`   | Dépendance externe, code non auditable   |

**Justification formelle :** En SPSC strict, un seul
producteur et un seul consommateur garantissent l'absence
de data race sans mutex. Démontrable par inspection.

### 3.2 Choix de Qt comme framework

**Décision :** Qt 6.x pour l'IHM, les threads et le réseau.

**Justification :** Portabilité Linux/Windows, écosystème
mature, `QThread` avec event loop adapté à l'architecture
MVVM, `QUdpSocket` testé en production industrielle.

---

## 4. Diagrammes

### 4.1 Flux de données

\startuml
skinparam style strictuml

participant "UdpWorker\n(Thread 2)" as UDP
participant "RingBuffer\n(SPSC)" as RB
participant "BdfWriter\n(Thread 3)" as BDF
participant "Decimator" as DEC
participant "ViewModel\n(Thread 1)" as VM

UDP -> RB   : push(SensorFrame)
UDP -> DEC  : every Nth frame
DEC -> VM   : emit signal (Qt)
RB  -> BDF  : pop() @ 1kHz
BDF -> BDF  : write to .bdf
\enduml

---

## 5. Matrice de traçabilité

> Générée automatiquement par Doxygen via les balises
> \requirement / \satisfies / \verifies.

| LLR            | HLR satisfait                        |
|----------------|--------------------------------------|
| LLR-UDP-001    | HLR-ACQ-001                          |
| LLR-BUF-001    | HLR-PERF-001, HLR-LOG-001            |
| LLR-BUF-003    | HLR-LOG-001, HLR-PERF-001            |
| LLR-EMG-001    | HLR-SAFE-001                         |
| ...            | ...                                  |
