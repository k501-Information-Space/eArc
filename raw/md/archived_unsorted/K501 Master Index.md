## type: system_dashboard status: operational node: K501_NODE_001

# 🛰️ K501 Master Knowledge & Frame Index

## 📟 System-Status

- **Architektur-Version:** v0.4 (Frozen)
- **Letzter Snapshot:** 2026-03-08
- **Node-Typ:** Local Control Node

## 🎞️ Frame-Timeline (Operative Ebene)

_Die letzten 10 Ereignisse im System._

TABLE  
ts_utc as "Zeitstempel",  
action as "Aktion",  
status as "Status"  
FROM "01_Frames"  
SORT file.name DESC  
LIMIT 10  

## 🧠 Knowledge-Ontologie (Theoretische Ebene)

_Status der fünf Wissens-Domänen._

TABLE  
status as "Status",  
tags as "Tags",  
length(file.inlinks) as "Verknüpfungen"  
FROM "00_Meta/Knowledge_Index"  
WHERE type = "domain_index"  
SORT domain ASC  

## 🛠️ Tooling & Scripts (Funktionale Ebene)

_Physische Skripte und ihre Einsatzbereitschaft._

LIST  
FROM "Scripts"  
WHERE contains(file.name, ".py") OR contains(file.name, ".sh")  

## 📚 Dokumentations-Archiv

_Lokale Kopien technischer Spezifikationen._

TABLE  
purpose as "Zweck",  
status as "Status"  
FROM "00_Meta/Docs"  
WHERE type = "technical_reference"  

_K501_ISOS_INDEX_LAYER_V1_