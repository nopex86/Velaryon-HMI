# SRS — Software Requirements Specification
# Velaryon V3

| Champ          | Valeur                  |
|----------------|-------------------------|
| Document ID    | VEL-SRS-001             |
| Version        | 1.0                     |
| Statut         | Draft / Released        |
| Auteur         | Prénom Nom              |
| Date           | 2026-04-27              |
| Niveau DAL     | DAL-D (recommandé asso) |

---

## 1. Objet et domaine d'application

### 1.1 Objet
Ce document spécifie les exigences logicielles de haut niveau (HLR)
du logiciel Velaryon V3, IHM de contrôle du banc d'essai moteur
ETH/LOX de [nom asso].

### 1.2 Périmètre
- Réception et décodage des trames UDP du contrôleur embarqué
- Logging binaire haute fréquence au format .bdf
- Affichage temps réel des données capteurs
- Commande des vannes haute pression (SV11..SV63)
- Séquences automatisées et arrêt d'urgence

### 1.3 Documents de référence
| ID  | Document                              |
|-----|---------------------------------------|
| [1] | Protocole UDP embarqué v2.3           |
| [2] | Plan de test banc moteur              |
| [3] | Schéma P&ID du banc                   |

---

## 2. Exigences générales

### 2.1 Exigences de performance

\requirement HLR-PERF-001
Le logiciel SHALL traiter les trames UDP entrantes à une
fréquence minimale de 500 Hz sans perte.

\requirement HLR-PERF-002
La latence entre réception d'une trame et affichage à
l'écran SHALL être inférieure à 50 ms.

### 2.2 Exigences de sécurité

\requirement HLR-SAFE-001
Le logiciel SHALL déclencher une procédure d'arrêt
d'urgence (ABORT) en moins de 100 ms après activation
de la commande opérateur.

\requirement HLR-SAFE-002
En cas de perte de communication UDP supérieure à 500 ms,
le logiciel SHALL afficher une alarme visuelle critique
et passer en état SAFE.

\requirement HLR-SAFE-003
Le logiciel SHALL interdire toute commande de vanne
lorsque le système est en état FAULT.

---

## 3. Exigences fonctionnelles

### 3.1 Acquisition de données

\requirement HLR-ACQ-001
Le logiciel SHALL recevoir les trames UDP sur un thread
dédié indépendant du thread d'interface graphique.

\requirement HLR-ACQ-002
Le logiciel SHALL décoder les headers 4 octets (0xFF×4)
et router les données vers le sous-système approprié.

\requirement HLR-ACQ-003
Le logiciel SHALL horodater chaque trame à la réception
avec une précision minimale de 1 ms.

### 3.2 Logging

\requirement HLR-LOG-001
Le logiciel SHALL enregistrer l'intégralité des trames
reçues dans un fichier .bdf sans perte de données.

\requirement HLR-LOG-002
Le fichier .bdf SHALL être écrit de manière continue
sans interruption pendant toute la durée du test.

\requirement HLR-LOG-003
Le logiciel SHALL créer un nouveau fichier .bdf horodaté
à chaque début de session d'acquisition.

### 3.3 Interface graphique

\requirement HLR-UI-001
L'IHM SHALL afficher l'état (OPEN/CLOSED/FAULT) de
chacune des 18 vannes SV11 à SV63 en temps réel.

\requirement HLR-UI-002
L'IHM SHALL afficher les valeurs de tous les capteurs
(PS, TS, FM, FS, LC) avec leur unité et leur statut.

\requirement HLR-UI-003
Le rafraîchissement de l'IHM SHALL être limité à 60 Hz
afin de ne pas perturber le thread d'acquisition.

### 3.4 Commande des actionneurs

\requirement HLR-CMD-001
Le logiciel SHALL permettre l'ouverture et la fermeture
individuelle de chaque vanne via l'IHM.

\requirement HLR-CMD-002
Le logiciel SHALL implémenter le mode bang-bang pour
la pressurisation automatique des réservoirs.

\requirement HLR-CMD-003
Le logiciel SHALL permettre l'exécution de séquences
de test prédéfinies avec confirmation opérateur.

### 3.5 TVC

\requirement HLR-TVC-001
Le logiciel SHALL transmettre les consignes de Thrust
Vector Control au contrôleur embarqué.

---

## 4. Exigences d'interface

### 4.1 Interface réseau

\requirement HLR-IF-001
Le logiciel SHALL communiquer avec le contrôleur
embarqué via UDP sur le port [PORT] en IPv4.

\requirement HLR-IF-002
Le logiciel SHALL détecter et signaler toute trame
malformée ou avec checksum invalide.

### 4.2 Interface opérateur

\requirement HLR-IF-003
Le logiciel SHALL fonctionner sur une résolution
minimale de 1920×1080 pixels.

---

## 5. Exigences de fiabilité et maintenance

\requirement HLR-REL-001
Le logiciel SHALL logger les erreurs internes dans un
fichier de log dédié avec horodatage.

\requirement HLR-REL-002
Le logiciel SHALL être redémarrable sans perte de
configuration entre deux sessions de test.

---

## 6. Exigences de non-régression

\requirement HLR-NR-001
Toute modification du logiciel SHALL faire l'objet
d'une revue et d'une mise à jour de la matrice de
traçabilité.