# Security Policy — K500 Gatekeeper (K500G)

Der K500 Gatekeeper ist ein **Interface-only Referenzprojekt**.
Er enthält **keine laufende Implementierung** und **keinen operativen Code**.

## Sicherheitsverständnis
Sicherheit im K500G-Kontext bedeutet:
- klare Grenzen
- minimale Angriffsfläche
- Verifizierbarkeit statt Vertrauen
- Verantwortung bei der Umsetzung

## Bedrohungsmodell
Dieses Repository:
- verarbeitet keine Live-Daten
- führt keinen Code aus
- exponiert keine Dienste

Daher existieren hier **keine klassischen Sicherheitslücken** im technischen Sinn.

## Implementierungen
Sicherheit von Implementierungen liegt vollständig bei den jeweiligen Projekten.
Bitte beachtet:
- Offline-Signing wird empfohlen
- Schlüsselmaterial ist strikt zu trennen
- Hash- und Signaturprüfung ist verpflichtend
- Append-only und Read-only sind essenziell

## Meldung von Sicherheitsbedenken
Wenn ihr konzeptionelle Sicherheitsprobleme in:
- Interface
- State Schema
- Trust Layer
findet, könnt ihr diese als **Issue** melden (Beschreibung, kein PoC nötig).

## Keine Bug-Bounty
Dieses Projekt betreibt:
- keinen Dienst
- kein Produkt
- keine Ausführung

Daher gibt es kein Bug-Bounty-Programm.

## Verantwortung
Der K500 Gatekeeper definiert eine **Schwelle**.
Die sichere Nutzung dieser Schwelle erfordert Sachverstand.

Danke für verantwortungsvolles Handeln.